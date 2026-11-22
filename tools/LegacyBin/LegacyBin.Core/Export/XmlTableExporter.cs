using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using LegacyBin.Core.Data;

namespace LegacyBin.Core.Export
{
    public sealed class ExportStats
    {
        public int Tables, DecodedTables, RawTables;
        public long Records, Fields;
        public List<string> Problems = new List<string>();
    }

    /// <summary>Writes one readable XML file per table: named fields, resolved strings and references.</summary>
    public static class XmlTableExporter
    {
        public static ExportStats Export(IList<DecodedTable> tables, RecordDecoder decoder, string folder, IProgress<string> log = null)
        {
            Directory.CreateDirectory(folder);
            var st = new ExportStats();
            var settings = new XmlWriterSettings { Indent = true, Encoding = new UTF8Encoding(false) };
            foreach (var t in tables)
            {
                st.Tables++;
                string file = Path.Combine(folder, Safe(t.Name) + ".xml");
                using (var w = XmlWriter.Create(file, settings))
                {
                    w.WriteStartDocument();
                    w.WriteStartElement("table");
                    w.WriteAttributeString("name", t.Name);
                    w.WriteAttributeString("type", t.Raw.Type.ToString());
                    w.WriteAttributeString("version", t.Raw.Version);
                    w.WriteAttributeString("kind", t.Raw.Kind == 1 ? "auto-key" : "multi-key");
                    if (t.Body != null)
                    {
                        w.WriteAttributeString("compressed", t.Body.Compressed ? "y" : "n");
                        w.WriteAttributeString("records", t.Body.Records.Count.ToString());
                    }
                    if (t.Problem != null)
                    {
                        st.RawTables++;
                        st.Problems.Add($"{t.Name} ({t.Raw.Type}): {t.Problem}");
                        w.WriteAttributeString("problem", t.Problem);
                        if (t.Body != null)
                            foreach (var r in t.Body.Records)
                            {
                                w.WriteStartElement("raw");
                                w.WriteAttributeString("hex", BitConverter.ToString(r.Fixed).Replace("-", ""));
                                w.WriteEndElement();
                            }
                    }
                    else
                    {
                        st.DecodedTables++;
                        foreach (var r in t.Body.Records)
                        {
                            st.Records++;
                            w.WriteStartElement(RecordDecoder.ElementName(t.Def, r));
                            var sub = RecordDecoder.SubTypeName(t.Def, r);
                            if (sub != null) w.WriteAttributeString("type", sub);
                            foreach (var f in decoder.Decode(t, r))
                            {
                                st.Fields++;
                                if (f.Value.Length == 0) continue;
                                if (sub != null && f.Name == "type") continue;
                                w.WriteAttributeString(f.Name, Clean(f.Value));
                            }
                            w.WriteEndElement();
                        }
                    }
                    w.WriteEndElement();
                    w.WriteEndDocument();
                }
                log?.Report($"{t.Name}: {(t.Problem == null ? t.Body.Records.Count + " records" : "RAW - " + t.Problem)}");
            }
            return st;
        }

        static string Safe(string s) => new string(s.Select(c => Path.GetInvalidFileNameChars().Contains(c) ? '_' : c).ToArray());

        /// <summary>Replace characters that XML 1.0 cannot hold with \uXXXX.</summary>
        static string Clean(string s)
        {
            StringBuilder sb = null;
            for (int i = 0; i < s.Length; i++)
            {
                char c = s[i];
                bool ok = c == 0x9 || c == 0xA || c == 0xD || (c >= 0x20 && c <= 0xD7FF) || (c >= 0xE000 && c <= 0xFFFD)
                    || (char.IsHighSurrogate(c) && i + 1 < s.Length && char.IsLowSurrogate(s[i + 1]))
                    || (char.IsLowSurrogate(c) && i > 0 && char.IsHighSurrogate(s[i - 1]));
                if (ok) { sb?.Append(c); continue; }
                if (sb == null) sb = new StringBuilder(s, 0, i, s.Length + 16);
                sb.Append("\\u").Append(((int)c).ToString("x4"));
            }
            return sb?.ToString() ?? s;
        }
    }
}
