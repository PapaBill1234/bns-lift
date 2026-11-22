using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace LegacyBin.Core.Pe
{
    public sealed class PeSection
    {
        public string Name;
        public uint VirtualAddress, VirtualSize, RawOffset, RawSize, Characteristics;
        public double Entropy;
        public bool Executable => (Characteristics & 0x20000000) != 0;
        public bool Writable => (Characteristics & 0x80000000) != 0;
        public bool Initialized => (Characteristics & 0x40) != 0;
    }

    /// <summary>Read-only view of a PE32 / PE32+ file on disk. No code is run.</summary>
    public sealed class PeImage
    {
        public byte[] Bytes { get; }
        public bool Is64 { get; private set; }
        public ulong ImageBase { get; private set; }
        public uint EntryPoint { get; private set; }
        public uint TimeDateStamp { get; private set; }
        public List<PeSection> Sections { get; } = new List<PeSection>();
        public int PointerSize => Is64 ? 8 : 4;

        PeImage(byte[] bytes) { Bytes = bytes; }

        public static PeImage Load(string path) => Parse(File.ReadAllBytes(path));

        public static PeImage Parse(byte[] b)
        {
            if (b.Length < 0x40 || b[0] != 'M' || b[1] != 'Z') throw new InvalidDataException("Not a PE file (no MZ).");
            int pe = BitConverter.ToInt32(b, 0x3C);
            if (pe < 0 || pe + 24 > b.Length || BitConverter.ToUInt32(b, pe) != 0x4550) throw new InvalidDataException("Not a PE file (no PE header).");
            var img = new PeImage(b);
            int nsec = BitConverter.ToUInt16(b, pe + 6);
            img.TimeDateStamp = BitConverter.ToUInt32(b, pe + 8);
            int optSize = BitConverter.ToUInt16(b, pe + 20);
            int opt = pe + 24;
            ushort magic = BitConverter.ToUInt16(b, opt);
            if (magic == 0x10B) { img.Is64 = false; img.ImageBase = BitConverter.ToUInt32(b, opt + 28); }
            else if (magic == 0x20B) { img.Is64 = true; img.ImageBase = BitConverter.ToUInt64(b, opt + 24); }
            else throw new InvalidDataException($"Unknown optional header magic 0x{magic:X}.");
            img.EntryPoint = BitConverter.ToUInt32(b, opt + 16);
            int sh = opt + optSize;
            for (int i = 0; i < nsec; i++, sh += 40)
            {
                if (sh + 40 > b.Length) throw new InvalidDataException("Section table is truncated.");
                var s = new PeSection
                {
                    Name = Encoding.ASCII.GetString(b, sh, 8).TrimEnd('\0'),
                    VirtualSize = BitConverter.ToUInt32(b, sh + 8),
                    VirtualAddress = BitConverter.ToUInt32(b, sh + 12),
                    RawSize = BitConverter.ToUInt32(b, sh + 16),
                    RawOffset = BitConverter.ToUInt32(b, sh + 20),
                    Characteristics = BitConverter.ToUInt32(b, sh + 36),
                };
                if ((ulong)s.RawOffset + s.RawSize > (ulong)b.Length) s.RawSize = (uint)Math.Max(0, b.Length - (long)s.RawOffset);
                s.Entropy = Entropy(b, (int)s.RawOffset, (int)s.RawSize);
                img.Sections.Add(s);
            }
            return img;
        }

        static double Entropy(byte[] b, int off, int len)
        {
            if (len <= 0) return 0;
            var counts = new long[256];
            for (int i = 0; i < len; i++) counts[b[off + i]]++;
            double e = 0;
            foreach (var c in counts) if (c != 0) { double p = (double)c / len; e -= p * Math.Log(p, 2); }
            return e;
        }

        static readonly string[] PackerSections =
        {
            ".themida", ".winlice", ".vmp0", ".vmp1", ".vmp2", ".enigma1", ".enigma2", "upx0", "upx1",
            ".aspack", ".adata", ".mpress1", ".mpress2", ".petite", ".nsp0", ".nsp1", ".perplex", ".boom", ".arxan",
        };

        /// <summary>Returns null when the file looks unpacked, otherwise the reason. Packed files have no readable schema.</summary>
        public string PackedReason()
        {
            foreach (var s in Sections)
                foreach (var n in PackerSections)
                    if (string.Equals(s.Name, n, StringComparison.OrdinalIgnoreCase)) return $"packer/protector section {s.Name}";
            int first = Sections.FindIndex(s => s.Executable);
            int entry = Sections.FindIndex(s => EntryPoint >= s.VirtualAddress && EntryPoint < s.VirtualAddress + Math.Max(s.VirtualSize, s.RawSize));
            if (entry < 0) return "entry point is outside all sections";
            if (entry != first) return "entry point is not in the first code section";
            if (Sections[entry].Writable) return "entry-point section is writable";
            foreach (var s in Sections)
            {
                if (s.RawSize >= 65536 && s.Entropy >= 7.4) return $"section {s.Name} is encrypted/compressed (entropy {s.Entropy:F2})";
                if (s.Executable && s.RawSize == 0 && s.VirtualSize > 0) return $"code section {s.Name} has no raw bytes";
            }
            return null;
        }

        public long VaToOffset(ulong va, int size = 1)
        {
            if (va == 0 || va < ImageBase) return -1;
            ulong rva = va - ImageBase;
            foreach (var s in Sections)
            {
                if (rva < s.VirtualAddress) continue;
                ulong d = rva - s.VirtualAddress;
                if (d < s.RawSize && (ulong)size <= s.RawSize - d) return (long)(s.RawOffset + d);
            }
            return -1;
        }

        public bool IsMapped(ulong va) => VaToOffset(va) >= 0;

        public ulong U(ulong va, int off, int n)
        {
            long o = VaToOffset(va + (ulong)off, n);
            if (o < 0) throw new InvalidDataException($"VA 0x{va + (ulong)off:X} is not mapped.");
            ulong v = 0;
            for (int i = n - 1; i >= 0; i--) v = (v << 8) | Bytes[o + i];
            return v;
        }

        public bool TryU(ulong va, int off, int n, out ulong v)
        {
            v = 0;
            if (VaToOffset(va + (ulong)off, n) < 0) return false;
            v = U(va, off, n);
            return true;
        }

        public ulong Ptr(ulong va, int off) => U(va, off, PointerSize);

        /// <summary>UTF-16 zero-terminated string at <paramref name="va"/>; null when the pointer is not mapped.</summary>
        public string WStr(ulong va)
        {
            long o = VaToOffset(va);
            if (o < 0) return null;
            var sb = new StringBuilder();
            for (int i = 0; i <= 4096; i++)
            {
                long p = VaToOffset(va + (ulong)(i * 2), 2);
                if (p < 0) throw new InvalidDataException("UTF-16 string runs out of the image.");
                char c = (char)BitConverter.ToUInt16(Bytes, (int)p);
                if (c == 0) return sb.ToString();
                sb.Append(c);
            }
            throw new InvalidDataException("UTF-16 string exceeds 4096 units.");
        }

        public IEnumerable<(ulong start, uint size)> DataSections()
        {
            foreach (var s in Sections)
                if (!s.Executable && s.Initialized) yield return (ImageBase + s.VirtualAddress, s.RawSize);
        }
    }
}
