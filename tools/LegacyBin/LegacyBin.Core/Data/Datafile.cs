using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace LegacyBin.Core.Data
{
    /// <summary>
    /// TADBOSLB version 5 container (datafile.bin, datafile64.bin, localfile.bin, localfile64.bin).
    /// Spec: slopemulator bns-server/Docs/DataFile/02-tadboslb.md.
    /// </summary>
    public sealed class DatafileHeader
    {
        public const string Magic = "TADBOSLB";
        public byte Version;
        public ushort[] GameVersion = new ushort[4];
        public long TotalTableSize, TableCount, AliasSize, AliasCount, MaxBufferSize;
        public uint SaveTime;
        public byte Compressed, Encrypted;
        public byte[] Reserved = new byte[56];
        public string GameVersionText => string.Join(".", GameVersion);
        public DateTime SaveTimeUtc => DateTimeOffset.FromUnixTimeSeconds(SaveTime).UtcDateTime;
        public static int Size(bool is64) => is64 ? 119 : 99;
    }

    /// <summary>One table record: 11-byte header + body.</summary>
    public sealed class RawTable
    {
        public byte Kind;          // 1 = auto-key, 2 = multi-key
        public ushort Type;
        public ushort Major, Minor;
        public byte[] Body;
        public string Version => $"{Major}.{Minor}";
    }

    public sealed class Datafile
    {
        public DatafileHeader Header;
        public bool Is64;
        /// <summary>True when the file carries the alias block (main datafile). Localfiles have none.</summary>
        public bool HasAliasBlock;
        public byte[] AliasBlock = Array.Empty<byte>();
        public List<RawTable> Tables = new List<RawTable>();

        /// <summary>Load and auto-detect width (32/64) and role (main/local) by an exact structural walk.</summary>
        public static Datafile Load(string path) => Parse(File.ReadAllBytes(path));

        public static Datafile Parse(byte[] b)
        {
            if (b.Length < 99 || Encoding.ASCII.GetString(b, 0, 8) != DatafileHeader.Magic)
                throw new InvalidDataException("Not a TADBOSLB datafile.");
            string last = null;
            foreach (bool is64 in new[] { false, true })
                foreach (bool alias in new[] { true, false })
                {
                    try
                    {
                        var df = TryParse(b, is64, alias);
                        if (df != null) return df;
                    }
                    catch (Exception e) when (e is InvalidDataException || e is ArgumentException || e is IndexOutOfRangeException) { last = e.Message; }
                }
            throw new InvalidDataException("The table walk does not end at the file size in any layout." + (last != null ? " Last error: " + last : ""));
        }

        static Datafile TryParse(byte[] b, bool is64, bool alias)
        {
            int p = 8;
            var h = new DatafileHeader { Version = b[p++] };
            for (int i = 0; i < 4; i++, p += 2) h.GameVersion[i] = BitConverter.ToUInt16(b, p);
            long Wide() { long v = is64 ? BitConverter.ToInt64(b, p) : BitConverter.ToInt32(b, p); p += is64 ? 8 : 4; return v; }
            h.TotalTableSize = Wide(); h.TableCount = Wide(); h.AliasSize = Wide(); h.AliasCount = Wide(); h.MaxBufferSize = Wide();
            h.SaveTime = BitConverter.ToUInt32(b, p); p += 4;
            h.Compressed = b[p++]; h.Encrypted = b[p++];
            Buffer.BlockCopy(b, p, h.Reserved, 0, 56); p += 56;
            if (h.Version != 5) throw new InvalidDataException($"Unsupported datafile version {h.Version} (expected 5).");
            if (h.Compressed != 0 || h.Encrypted != 0) throw new InvalidDataException("Container compression/encryption flags are set; not supported.");
            if (h.TableCount < 0 || h.TableCount > 100000) return null;

            var df = new Datafile { Header = h, Is64 = is64 };
            if (alias)
            {
                if (h.AliasSize <= 0 || h.AliasCount <= 0 || p + h.AliasSize > b.Length) return null;
                df.HasAliasBlock = true;
                df.AliasBlock = new byte[h.AliasSize];
                Buffer.BlockCopy(b, p, df.AliasBlock, 0, (int)h.AliasSize);
                p += (int)h.AliasSize;
            }
            for (long i = 0; i < h.TableCount; i++)
            {
                if (p + 11 > b.Length) return null;
                var t = new RawTable
                {
                    Kind = b[p], Type = BitConverter.ToUInt16(b, p + 1),
                    Major = BitConverter.ToUInt16(b, p + 3), Minor = BitConverter.ToUInt16(b, p + 5),
                };
                uint size = BitConverter.ToUInt32(b, p + 7);
                if (t.Kind != 1 && t.Kind != 2) return null;
                p += 11;
                if ((long)p + size > b.Length) return null;
                t.Body = new byte[size];
                Buffer.BlockCopy(b, p, t.Body, 0, (int)size);
                p += (int)size;
                df.Tables.Add(t);
            }
            return p == b.Length ? df : null;
        }

        /// <summary>Write the container back. Unchanged input gives identical bytes.</summary>
        public void Save(string path)
        {
            using (var fs = File.Create(path))
            using (var w = new BinaryWriter(fs))
            {
                var h = Header;
                w.Write(Encoding.ASCII.GetBytes(DatafileHeader.Magic));
                w.Write(h.Version);
                foreach (var v in h.GameVersion) w.Write(v);
                void Wide(long v) { if (Is64) w.Write(v); else w.Write((int)v); }
                Wide(h.TotalTableSize); Wide(Tables.Count);
                Wide(HasAliasBlock ? AliasBlock.Length : h.AliasSize); Wide(h.AliasCount); Wide(h.MaxBufferSize);
                w.Write(h.SaveTime); w.Write(h.Compressed); w.Write(h.Encrypted); w.Write(h.Reserved);
                if (HasAliasBlock) w.Write(AliasBlock);
                foreach (var t in Tables)
                {
                    w.Write(t.Kind); w.Write(t.Type); w.Write(t.Major); w.Write(t.Minor);
                    w.Write((uint)t.Body.Length); w.Write(t.Body);
                }
            }
        }
    }
}
