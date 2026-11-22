using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;

namespace LegacyBin.Core.Data
{
    /// <summary>One element (record). <see cref="Fixed"/> starts with the 6-byte DrEl header.</summary>
    public sealed class Record
    {
        public byte[] Fixed;
        /// <summary>String pool for this record. Plain tables: shared table extra region. Compressed tables: the record's own span.</summary>
        public byte[] Pool;
        public int PoolOffset, PoolLength;
        public sbyte ElementType => (sbyte)Fixed[0];
        public short SubType => BitConverter.ToInt16(Fixed, 2);
        public int Size => BitConverter.ToUInt16(Fixed, 4);
    }

    /// <summary>
    /// Client table body: u8 compressed flag, then plain or block-compressed variant.
    /// Spec: slopemulator bns-server/Docs/DataFile/06-client-body.md, 08-strings.md.
    /// </summary>
    public sealed class TableBody
    {
        public bool Compressed;
        public long StoredCount;
        public List<Record> Records = new List<Record>();

        public static TableBody Parse(RawTable t, bool is64)
        {
            var b = t.Body;
            if (b.Length == 0) throw new InvalidDataException("Empty table body.");
            var body = new TableBody { Compressed = b[0] != 0 };
            return body.Compressed ? body.ParseCompressed(b) : body.ParsePlain(b, t.Kind == 1 && is64);
        }

        TableBody ParsePlain(byte[] b, bool wideCount)
        {
            int p = 1;
            StoredCount = wideCount ? BitConverter.ToInt64(b, p) : BitConverter.ToUInt32(b, p);
            p += wideCount ? 8 : 4;
            int fixedSize = BitConverter.ToInt32(b, p), extraSize = BitConverter.ToInt32(b, p + 4);
            p += 9; // + low-memory byte
            if ((long)p + fixedSize + extraSize != b.Length) throw new InvalidDataException("Plain table sizes do not match the body size.");
            int end = p + fixedSize;
            int extraStart = end;
            while (p < end)
            {
                if (p + 6 > end) throw new InvalidDataException("Truncated record header.");
                int size = BitConverter.ToUInt16(b, p + 4);
                if (size < 6 || p + size > end) throw new InvalidDataException("Record size out of range.");
                var f = new byte[size];
                Buffer.BlockCopy(b, p, f, 0, size);
                Records.Add(new Record { Fixed = f, Pool = b, PoolOffset = extraStart, PoolLength = extraSize });
                p += size;
            }
            return this;
        }

        TableBody ParseCompressed(byte[] b)
        {
            int p = 1;
            uint blocks = BitConverter.ToUInt32(b, p); p += 4;
            p += 2; // u16 constant (8)
            for (uint i = 0; i < blocks; i++)
            {
                p += 16; // first key, last key
                int cs = BitConverter.ToUInt16(b, p); p += 2;
                int csStart = p; p += cs;
                int ds = BitConverter.ToUInt16(b, p); p += 2;
                int rc = BitConverter.ToInt32(b, p); p += 4;
                var offs = new int[rc];
                for (int k = 0; k < rc; k++, p += 2) offs[k] = BitConverter.ToUInt16(b, p);
                var data = Inflate(b, csStart, cs, ds);
                for (int k = 0; k < rc; k++)
                {
                    int start = offs[k], stop = k + 1 < rc ? offs[k + 1] : ds;
                    int size = BitConverter.ToUInt16(data, start + 4);
                    if (size < 6 || start + size > stop) throw new InvalidDataException("Compressed record size out of range.");
                    var f = new byte[size];
                    Buffer.BlockCopy(data, start, f, 0, size);
                    Records.Add(new Record { Fixed = f, Pool = data, PoolOffset = start + size, PoolLength = stop - start - size });
                }
            }
            StoredCount = Records.Count;
            if (p != b.Length) throw new InvalidDataException("Compressed table does not end at the body size.");
            return this;
        }

        static byte[] Inflate(byte[] b, int off, int len, int expected)
        {
            // zlib: 2-byte header, deflate stream, 4-byte Adler-32 trailer.
            if (len < 6) throw new InvalidDataException("zlib stream too short.");
            var outBuf = new byte[expected];
            using (var ms = new MemoryStream(b, off + 2, len - 2))
            using (var ds = new DeflateStream(ms, CompressionMode.Decompress))
            {
                int n = 0, r;
                while (n < expected && (r = ds.Read(outBuf, n, expected - n)) > 0) n += r;
                if (n != expected) throw new InvalidDataException($"Block inflated to {n} bytes, expected {expected}.");
            }
            return outBuf;
        }
    }
}
