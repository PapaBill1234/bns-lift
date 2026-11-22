using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using LegacyBin.Core.Schema;

namespace LegacyBin.Core.Data
{
    public sealed class FieldValue
    {
        public string Name;
        public string Type;
        public string Value;
    }

    /// <summary>A table body bound to its definition.</summary>
    public sealed class DecodedTable
    {
        public RawTable Raw;
        public TableDef Def;
        public TableBody Body;
        /// <summary>Null when the table decodes; otherwise why it was left raw.</summary>
        public string Problem;
        public int SizeMismatches;
        public string Name => Def?.Name ?? $"table-{Raw.Type}";
    }

    /// <summary>
    /// Turns raw records into named field values. Resolves strings, native text, seq labels and
    /// references (ref -> "table:alias" when the target has an alias, else "table:key").
    /// </summary>
    public sealed class RecordDecoder
    {
        readonly Schema.Schema schema;
        readonly bool is64;
        readonly Dictionary<int, DecodedTable> byType = new Dictionary<int, DecodedTable>();
        readonly Dictionary<int, Dictionary<ulong, string>> aliasIndex = new Dictionary<int, Dictionary<ulong, string>>();
        public bool ResolveRefs = true;
        /// <summary>Non-zero references seen, and those whose target record was not found.</summary>
        public long RefsTotal, RefsMissing;
        public readonly Dictionary<string, long> MissingByTarget = new Dictionary<string, long>();

        public RecordDecoder(Schema.Schema schema, bool is64, IEnumerable<DecodedTable> tables)
        {
            this.schema = schema; this.is64 = is64;
            foreach (var t in tables) byType[t.Raw.Type] = t;
            iconTable = schema?.Tables.Values.FirstOrDefault(t => t.Name == "icontexture")?.Type ?? 0;
        }

        readonly short iconTable;

        /// <summary>Bind every table of one or more files to the schema.</summary>
        public static List<DecodedTable> Bind(Schema.Schema schema, Datafile df)
        {
            var list = new List<DecodedTable>();
            foreach (var raw in df.Tables)
            {
                var d = new DecodedTable { Raw = raw, Def = schema?.Find(raw.Type) };
                try { d.Body = TableBody.Parse(raw, df.Is64); }
                catch (Exception e) { d.Problem = "body: " + e.Message; list.Add(d); continue; }
                if (d.Def == null) d.Problem = "no definition for this table type in the schema";
                else if (d.Def.Major != raw.Major || d.Def.Minor != raw.Minor)
                    d.Problem = $"version mismatch: file {raw.Version}, schema {d.Def.Version}";
                else
                {
                    foreach (var r in d.Body.Records)
                    {
                        var (el, sub) = Element(d.Def, r);
                        int expect = sub?.Size ?? el?.Size ?? -1;
                        if (expect != r.Size) d.SizeMismatches++;
                    }
                    if (d.SizeMismatches > 0) d.Problem = $"{d.SizeMismatches} records do not match the schema size (wrong width or build?)";
                }
                list.Add(d);
            }
            return list;
        }

        static (ElementDef, SubDef) Element(TableDef def, Record r)
        {
            int t = r.ElementType;
            if (t < 0 || t >= def.Elements.Count) return (null, null);
            var el = def.Elements[t];
            SubDef sub = r.SubType >= 0 && r.SubType < el.Subs.Count ? el.Subs[r.SubType] : null;
            return (el, sub);
        }

        public static string ElementName(TableDef def, Record r)
        {
            var (el, _) = Element(def, r);
            return el?.Name ?? "record";
        }

        public static string SubTypeName(TableDef def, Record r)
        {
            var (_, sub) = Element(def, r);
            return sub?.Name;
        }

        public static ulong Key(TableDef def, Record r)
        {
            var (el, _) = Element(def, r);
            int o = el?.KeyOffset ?? 8;
            return o + 8 <= r.Fixed.Length ? BitConverter.ToUInt64(r.Fixed, o) : 0;
        }

        /// <summary>All column names a table can produce, in schema order (base fields, then sub-type fields).</summary>
        public static List<string> Columns(TableDef def)
        {
            var cols = new List<string>();
            var seen = new HashSet<string>();
            foreach (var el in def.Elements.Skip(1).DefaultIfEmpty(def.Elements.FirstOrDefault()))
            {
                if (el == null) continue;
                foreach (var a in el.Attrs.Concat(el.Subs.SelectMany(s => s.Attrs)))
                {
                    if (a.Size == 0) continue;
                    int rep = Math.Max(1, a.Repeat);
                    for (int i = 0; i < rep; i++)
                    {
                        string n = rep > 1 ? $"{a.Name}-{i + 1}" : a.Name;
                        if (seen.Add(n)) cols.Add(n);
                    }
                }
            }
            return cols;
        }

        public List<FieldValue> Decode(DecodedTable t, Record r)
        {
            var list = new List<FieldValue>();
            var (el, sub) = Element(t.Def, r);
            if (el == null) return list;
            IEnumerable<AttrDef> attrs = el.Attrs;
            if (sub != null) attrs = attrs.Concat(sub.Attrs);
            var seen = new HashSet<string>();
            foreach (var a in attrs)
            {
                if (a.Size == 0) continue; // server-only column, no bytes in client records
                int rep = Math.Max(1, a.Repeat);
                for (int i = 0; i < rep; i++)
                {
                    int off = a.Offset + i * a.Size;
                    if (off + a.Size > r.Fixed.Length) break;
                    string name = rep > 1 ? $"{a.Name}-{i + 1}" : a.Name;
                    // The schema can declare the same name twice (base + sub-type, e.g. "effect"). Keep both.
                    if (!seen.Add(name)) name = $"{name}.at{off}";
                    list.Add(new FieldValue
                    {
                        Name = name,
                        Type = a.Type,
                        Value = Format(a, r, off),
                    });
                }
            }
            return list;
        }

        static long SInt(byte[] f, int o, int n)
        {
            switch (n)
            {
                case 1: return (sbyte)f[o];
                case 2: return BitConverter.ToInt16(f, o);
                case 4: return BitConverter.ToInt32(f, o);
                default: return BitConverter.ToInt64(f, o);
            }
        }

        static ulong UInt(byte[] f, int o, int n)
        {
            ulong v = 0;
            for (int i = n - 1; i >= 0; i--) v = (v << 8) | f[o + i];
            return v;
        }

        static string Hex(byte[] f, int o, int n)
        {
            var sb = new StringBuilder(n * 2);
            for (int i = 0; i < n; i++) sb.Append(f[o + i].ToString("x2"));
            return sb.ToString();
        }

        static string Pool(Record r, long offset)
        {
            if (offset < 0 || offset >= r.PoolLength) return null;
            int start = r.PoolOffset + (int)offset, end = r.PoolOffset + r.PoolLength;
            int p = start;
            while (p + 1 < end && (r.Pool[p] | r.Pool[p + 1]) != 0) p += 2;
            return Encoding.Unicode.GetString(r.Pool, start, p - start);
        }

        static string Seq(AttrDef a, ulong v) => a.Seq != null && v < (ulong)a.Seq.Count && a.Seq[(int)v] != null ? a.Seq[(int)v] : v.ToString(CultureInfo.InvariantCulture);

        string Format(AttrDef a, Record r, int o)
        {
            var f = r.Fixed;
            int n = a.Size;
            switch (a.Type)
            {
                case "int8": case "int16": case "int32": case "int64":
                case "msec": case "distance": case "velocity": case "prop_field": case "sub":
                case "time32": case "time64": case "angle":
                    return n <= 8 ? SInt(f, o, n).ToString(CultureInfo.InvariantCulture) : Hex(f, o, n);
                case "bool":
                    return f[o] == 0 ? "n" : f[o] == 1 ? "y" : f[o].ToString(CultureInfo.InvariantCulture);
                case "float32":
                    return n == 4 ? BitConverter.ToSingle(f, o).ToString("R", CultureInfo.InvariantCulture) : Hex(f, o, n);
                case "seq": case "prop_seq": case "seq16":
                    return n <= 2 ? Seq(a, UInt(f, o, n)) : Hex(f, o, n);
                case "string":
                {
                    long off = (long)UInt(f, o, n);
                    return Pool(r, off) ?? "";
                }
                case "native":
                {
                    long off = BitConverter.ToUInt32(f, o + 4);
                    return Pool(r, off) ?? "";
                }
                case "ref":
                    return n == 8 ? Ref(a.RefTable, BitConverter.ToUInt64(f, o)) : Hex(f, o, n);
                case "tref":
                    // 12 bytes: i16 table type, pad, then 8 key bytes.
                    return n == 12 ? TRef(f, o) : Hex(f, o, n);
                case "icon":
                    // 12 bytes: 8-byte ref to the icon texture table, then i16 icon index.
                    return n == 12 ? Icon(a.RefTable, f, o) : Hex(f, o, n);
                case "vector32":
                    return n == 12 ? $"{BitConverter.ToInt32(f, o)},{BitConverter.ToInt32(f, o + 4)},{BitConverter.ToInt32(f, o + 8)}" : Hex(f, o, n);
                case "icolor":
                    return n == 3 ? $"{f[o]},{f[o + 1]},{f[o + 2]}" : Hex(f, o, n);
                default:
                    return Hex(f, o, n);
            }
        }

        string TRef(byte[] f, int o)
        {
            int type = BitConverter.ToInt16(f, o);
            ulong key = BitConverter.ToUInt64(f, o + 4);
            if (type == 0 && key == 0) return "";
            // A tref can point to any table, so keep the table name: "item:General_Grocery_Box_3334".
            string v = Ref((short)type, key);
            string table = schema?.Find(type)?.Name ?? type.ToString(CultureInfo.InvariantCulture);
            return v.StartsWith(table + ":", StringComparison.Ordinal) ? v : $"{table}:{v}";
        }

        string Icon(short refTable, byte[] f, int o)
        {
            ulong key = BitConverter.ToUInt64(f, o);
            int idx = BitConverter.ToInt16(f, o + 8);
            if (key == 0) return "";
            // The icon attribute has reftable 0; its target is the icon texture table.
            if (refTable == 0) refTable = iconTable;
            return $"{Ref(refTable, key)},{idx}";
        }

        string Ref(short table, ulong key)
        {
            if (key == 0) return "";
            RefsTotal++;
            if (!ResolveRefs || !byType.TryGetValue(table, out var target) || target.Def == null || target.Body == null)
                return $"{schema?.Find(table)?.Name ?? table.ToString(CultureInfo.InvariantCulture)}:{key}";
            var idx = AliasIndex(target);
            if (idx.TryGetValue(key, out var alias)) return alias ?? $"{target.Name}:{key}";
            RefsMissing++;
            MissingByTarget[target.Name] = (MissingByTarget.TryGetValue(target.Name, out var c) ? c : 0) + 1;
            return $"{target.Name}:{key}";
        }

        /// <summary>Key -> alias for every record of a table (alias null when the record has none).</summary>
        Dictionary<ulong, string> AliasIndex(DecodedTable t)
        {
            if (aliasIndex.TryGetValue(t.Raw.Type, out var idx)) return idx;
            idx = new Dictionary<ulong, string>();
            if (t.Problem == null)
            {
                foreach (var r in t.Body.Records)
                {
                    var (el, _) = Element(t.Def, r);
                    var aliasAttr = el?.Attrs.FirstOrDefault(a => a.Name == "alias" && a.Type == "string" && a.Size > 0);
                    string alias = aliasAttr == null ? null : Pool(r, (long)UInt(r.Fixed, aliasAttr.Offset, aliasAttr.Size));
                    idx[Key(t.Def, r)] = string.IsNullOrEmpty(alias) ? null : alias;
                }
            }
            aliasIndex[t.Raw.Type] = idx;
            return idx;
        }
    }
}
