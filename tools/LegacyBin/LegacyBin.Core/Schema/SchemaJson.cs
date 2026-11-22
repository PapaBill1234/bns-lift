using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Encodings.Web;
using System.Text.Json;

namespace LegacyBin.Core.Schema
{
    /// <summary>
    /// Reads and writes the "TableDefs" folder format: one <c>&lt;table&gt;.json</c> per table.
    /// The keys copy the in-memory structs, so dumps from other tools with the same keys load too.
    /// </summary>
    public static class SchemaJson
    {
        const string MetaFile = "_schema.json";

        public static void Save(Schema schema, string folder)
        {
            Directory.CreateDirectory(folder);
            var opt = new JsonWriterOptions { Indented = true, Encoder = JavaScriptEncoder.UnsafeRelaxedJsonEscaping };
            foreach (var t in schema.Tables.Values.OrderBy(t => t.Type))
            {
                using (var fs = File.Create(Path.Combine(folder, t.Name + ".json")))
                using (var w = new Utf8JsonWriter(fs, opt))
                    WriteTable(w, t);
            }
            using (var fs = File.Create(Path.Combine(folder, MetaFile)))
            using (var w = new Utf8JsonWriter(fs, opt))
            {
                w.WriteStartObject();
                w.WriteString("source", schema.Source);
                w.WriteString("layout", schema.Layout);
                w.WriteBoolean("is64", schema.Is64);
                w.WriteString("array_va", "0x" + schema.ArrayVa.ToString("X"));
                w.WriteNumber("tables", schema.Tables.Count);
                w.WriteEndObject();
            }
        }

        static void WriteDefRec(Utf8JsonWriter w, DefaultRecord d)
        {
            if (d == null) { w.WriteNull("defaultRecord"); return; }
            w.WriteStartObject("defaultRecord");
            w.WriteNumber("type", d.Type); w.WriteNumber("subtype", d.SubType); w.WriteNumber("size", d.Size);
            w.WriteEndObject();
        }

        static void WriteAttrs(Utf8JsonWriter w, List<AttrDef> attrs)
        {
            if (attrs.Count == 0) { w.WriteNull("attr"); return; }
            w.WriteStartArray("attr");
            foreach (var a in attrs)
            {
                w.WriteStartObject();
                w.WriteString("name", a.Name);
                if (a.NameHash.HasValue)
                {
                    w.WriteStartObject("namehash");
                    w.WriteNumber("namehash", a.NameHash.Value); w.WriteString("name", a.NameHashName);
                    w.WriteEndObject();
                }
                else w.WriteNull("namehash");
                w.WriteString("type", a.Type);
                w.WriteBoolean("key", a.Key);
                w.WriteNumber("repeat", a.Repeat);
                w.WriteNumber("required", a.Required);
                w.WriteString("defvalue", a.DefValue);
                w.WriteNumber("min", a.Min); w.WriteNumber("max", a.Max);
                w.WriteNumber("fmin", a.FMin); w.WriteNumber("fmax", a.FMax);
                if (a.Seq == null) w.WriteNull("seq");
                else { w.WriteStartArray("seq"); foreach (var s in a.Seq) w.WriteStringValue(s); w.WriteEndArray(); }
                w.WriteNumber("seqcount", a.SeqCount);
                w.WriteNumber("reftable", a.RefTable);
                w.WriteNumber("refel", a.RefEl);
                w.WriteBoolean("deprecated", a.Deprecated);
                w.WriteBoolean("hidden", a.Hidden);
                w.WriteNumber("offset", a.Offset);
                w.WriteNumber("size", a.Size);
                w.WriteNumber("propfield", a.PropField);
                w.WriteEndObject();
            }
            w.WriteEndArray();
        }

        static void WriteTable(Utf8JsonWriter w, TableDef t)
        {
            w.WriteStartObject();
            w.WriteString("name", t.Name);
            w.WriteNumber("type", t.Type);
            w.WriteNumber("major_ver", t.Major);
            w.WriteNumber("minor_ver", t.Minor);
            w.WriteStartArray("el");
            foreach (var e in t.Elements)
            {
                w.WriteStartObject();
                w.WriteString("name", e.Name);
                w.WriteNumber("type", e.Type);
                w.WriteStartObject("body");
                WriteAttrs(w, e.Attrs);
                if (e.Subs.Count == 0) w.WriteNull("sub");
                else
                {
                    w.WriteStartArray("sub");
                    foreach (var s in e.Subs)
                    {
                        w.WriteStartObject();
                        w.WriteString("name", s.Name);
                        WriteAttrs(w, s.Attrs);
                        WriteDefRec(w, s.DefaultRecord);
                        w.WriteNumber("attrcount", s.Attrs.Count);
                        w.WriteNumber("size", s.Size);
                        w.WriteEndObject();
                    }
                    w.WriteEndArray();
                }
                WriteDefRec(w, e.DefaultRecord);
                w.WriteNumber("attrcount", e.Attrs.Count);
                w.WriteNumber("subcount", e.Subs.Count);
                w.WriteNumber("size", e.Size);
                w.WriteNumber("keyoffset", e.KeyOffset);
                w.WriteEndObject();
                w.WriteStartArray("child");
                foreach (var c in e.Child) w.WriteNumberValue(c);
                w.WriteEndArray();
                w.WriteEndObject();
            }
            w.WriteEndArray();
            w.WriteNumber("elcount", t.Elements.Count);
            w.WriteNumber("maxid", t.MaxId);
            w.WriteBoolean("autokey", t.AutoKey);
            w.WriteNumber("module", t.Module);
            w.WriteEndObject();
        }

        // ---------------- load ----------------

        public static Schema Load(string folder)
        {
            var schema = new Schema { Source = folder, Layout = "json" };
            string meta = Path.Combine(folder, MetaFile);
            bool? is64 = null;
            if (File.Exists(meta))
            {
                using (var d = JsonDocument.Parse(File.ReadAllBytes(meta)))
                {
                    if (d.RootElement.TryGetProperty("is64", out var v)) is64 = v.GetBoolean();
                    if (d.RootElement.TryGetProperty("source", out var s)) schema.Source = s.GetString();
                    if (d.RootElement.TryGetProperty("layout", out var l)) schema.Layout = l.GetString();
                }
            }
            foreach (var f in Directory.GetFiles(folder, "*.json"))
            {
                if (Path.GetFileName(f) == MetaFile) continue;
                using (var d = JsonDocument.Parse(File.ReadAllBytes(f)))
                {
                    var t = ReadTable(d.RootElement);
                    if (schema.Tables.ContainsKey(t.Type)) throw new InvalidDataException($"Duplicate table type {t.Type} in {f}.");
                    schema.Tables[t.Type] = t;
                }
            }
            if (schema.Tables.Count == 0) throw new InvalidDataException($"No table definitions in {folder}.");
            // Without metadata: guess the width from the size of string fields (4 = x86, 8 = x64).
            schema.Is64 = is64 ?? schema.Tables.Values.SelectMany(t => t.Elements).SelectMany(AllAttrs)
                .Where(a => a.Type == "string" && a.Size > 0).Select(a => a.Size).DefaultIfEmpty(4).First() == 8;
            return schema;
        }

        static IEnumerable<AttrDef> AllAttrs(ElementDef e) => e.Attrs.Concat(e.Subs.SelectMany(s => s.Attrs));

        static string Str(JsonElement o, string k) => o.TryGetProperty(k, out var v) && v.ValueKind == JsonValueKind.String ? v.GetString() : null;
        static long Num(JsonElement o, string k) => o.TryGetProperty(k, out var v) && v.ValueKind == JsonValueKind.Number ? (v.TryGetInt64(out var n) ? n : (long)v.GetDouble()) : 0;
        static ulong UNum(JsonElement o, string k) => o.TryGetProperty(k, out var v) && v.ValueKind == JsonValueKind.Number ? (v.TryGetUInt64(out var n) ? n : (ulong)Num(o, k)) : 0;
        static bool Bool(JsonElement o, string k) => o.TryGetProperty(k, out var v) && (v.ValueKind == JsonValueKind.True || (v.ValueKind == JsonValueKind.Number && v.GetInt64() != 0));
        static float Flt(JsonElement o, string k) => o.TryGetProperty(k, out var v) && v.ValueKind == JsonValueKind.Number ? v.GetSingle() : 0f;
        static IEnumerable<JsonElement> Arr(JsonElement o, string k) => o.TryGetProperty(k, out var v) && v.ValueKind == JsonValueKind.Array ? v.EnumerateArray() : Enumerable.Empty<JsonElement>();

        static DefaultRecord DefRec(JsonElement o)
        {
            if (!o.TryGetProperty("defaultRecord", out var d) || d.ValueKind != JsonValueKind.Object) return null;
            return new DefaultRecord { Type = (int)Num(d, "type"), SubType = (int)Num(d, "subtype"), Size = (int)Num(d, "size") };
        }

        static List<AttrDef> ReadAttrs(JsonElement o) => Arr(o, "attr").Select(a =>
        {
            var d = new AttrDef
            {
                Name = Str(a, "name"), Type = Str(a, "type"), Key = Bool(a, "key"), Repeat = (int)Num(a, "repeat"),
                Required = (int)Num(a, "required"), DefValue = Str(a, "defvalue"), Min = Num(a, "min"), Max = Num(a, "max"),
                FMin = Flt(a, "fmin"), FMax = Flt(a, "fmax"), SeqCount = (int)Num(a, "seqcount"), RefTable = (short)Num(a, "reftable"),
                RefEl = (int)Num(a, "refel"), Deprecated = Bool(a, "deprecated"), Hidden = Bool(a, "hidden"),
                Offset = (int)Num(a, "offset"), Size = (int)Num(a, "size"), PropField = (uint)Num(a, "propfield"),
            };
            if (a.TryGetProperty("namehash", out var nh) && nh.ValueKind == JsonValueKind.Object)
            { d.NameHash = (uint)Num(nh, "namehash"); d.NameHashName = Str(nh, "name"); }
            if (a.TryGetProperty("seq", out var sq) && sq.ValueKind == JsonValueKind.Array)
                d.Seq = sq.EnumerateArray().Select(x => x.ValueKind == JsonValueKind.String ? x.GetString() : null).ToList();
            return d;
        }).ToList();

        static TableDef ReadTable(JsonElement o)
        {
            var t = new TableDef
            {
                Name = Str(o, "name"), Type = (short)Num(o, "type"), Major = (short)Num(o, "major_ver"), Minor = (short)Num(o, "minor_ver"),
                MaxId = UNum(o, "maxid"), AutoKey = Bool(o, "autokey"), Module = (uint)Num(o, "module"),
            };
            foreach (var e in Arr(o, "el"))
            {
                var b = e.GetProperty("body");
                var ed = new ElementDef
                {
                    Name = Str(e, "name"), Type = (int)Num(e, "type"), Attrs = ReadAttrs(b), DefaultRecord = DefRec(b),
                    Size = (int)Num(b, "size"), KeyOffset = (int)Num(b, "keyoffset"),
                    Subs = Arr(b, "sub").Select(s => new SubDef { Name = Str(s, "name"), Attrs = ReadAttrs(s), DefaultRecord = DefRec(s), Size = (int)Num(s, "size") }).ToList(),
                };
                ed.Child = Arr(e, "child").Select(c => (byte)c.GetInt32()).ToArray();
                t.Elements.Add(ed);
            }
            return t;
        }
    }
}
