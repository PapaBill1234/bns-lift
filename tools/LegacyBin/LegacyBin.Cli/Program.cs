using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using LegacyBin.Core.Data;
using LegacyBin.Core.Export;
using LegacyBin.Core.Schema;

static class Program
{
    const string Usage = @"legacybin - Blade & Soul datafile tool

  legacybin schema <Client.exe> <outFolder> [--array 0xVA]
      Dump the table definitions from an UNPACKED client executable (PE32 or PE32+).

  legacybin info <file.bin>
      Show header and table list.

  legacybin unpack <schemaFolder|Client.exe> <out> <datafile.bin> [localfile.bin ...]
      Decode every table with the schema and write one XML per table.
      Give the datafile and the localfile together so references into 'text' resolve.

  legacybin roundtrip <file.bin>
      Read and write the container in memory; check the bytes are identical.";

    static int Main(string[] args)
    {
        var log = new Progress<string>(Console.WriteLine);
        try
        {
            switch (args.FirstOrDefault())
            {
                case "schema" when args.Length >= 3:
                {
                    ulong? va = null;
                    int i = Array.IndexOf(args, "--array");
                    if (i > 0 && i + 1 < args.Length) va = Convert.ToUInt64(args[i + 1], 16);
                    var s = SchemaDumper.Dump(args[1], va, new SyncLog());
                    SchemaJson.Save(s, args[2]);
                    Console.WriteLine($"Wrote {s.Tables.Count} table definitions to {args[2]}");
                    return 0;
                }
                case "info" when args.Length >= 2:
                {
                    var df = Datafile.Load(args[1]);
                    var h = df.Header;
                    Console.WriteLine($"{(df.Is64 ? "64" : "32")}-bit, {(df.HasAliasBlock ? "main (alias block)" : "local (no alias block)")}, game {h.GameVersionText}, saved {h.SaveTimeUtc:u}, {df.Tables.Count} tables");
                    foreach (var t in df.Tables)
                        Console.WriteLine($"  type {t.Type,4} v{t.Version,-6} kind {t.Kind} {(t.Body[0] != 0 ? "zlib " : "plain")} {t.Body.Length,10} B");
                    return 0;
                }
                case "unpack" when args.Length >= 4:
                {
                    var sw = Stopwatch.StartNew();
                    var files = args.Skip(3).Select(f => (f, df: Datafile.Load(f))).ToList();
                    var schema = LoadSchema(args[1]);
                    var all = new List<DecodedTable>();
                    foreach (var (f, df) in files)
                    {
                        if (df.Is64 != schema.Is64)
                            Console.WriteLine($"WARNING: {Path.GetFileName(f)} is {(df.Is64 ? 64 : 32)}-bit, schema is {(schema.Is64 ? 64 : 32)}-bit.");
                        all.AddRange(RecordDecoder.Bind(schema, df));
                    }
                    var dec = new RecordDecoder(schema, files[0].df.Is64, all);
                    var st = XmlTableExporter.Export(all, dec, args[2]);
                    Console.WriteLine($"{st.Tables} tables: {st.DecodedTables} decoded, {st.RawTables} raw; {st.Records} records, {st.Fields} fields; {sw.Elapsed.TotalSeconds:F1} s");
                    Console.WriteLine($"references: {dec.RefsTotal} non-zero, {dec.RefsMissing} target not found");
                    foreach (var kv in dec.MissingByTarget.OrderByDescending(k => k.Value).Take(10)) Console.WriteLine($"  missing in {kv.Key}: {kv.Value}");
                    foreach (var p in st.Problems) Console.WriteLine("  RAW " + p);
                    return st.RawTables == 0 ? 0 : 2;
                }
                case "roundtrip" when args.Length >= 2:
                {
                    var orig = File.ReadAllBytes(args[1]);
                    var df = Datafile.Parse(orig);
                    string tmp = Path.GetTempFileName();
                    try
                    {
                        df.Save(tmp);
                        bool same = orig.AsSpan().SequenceEqual(File.ReadAllBytes(tmp));
                        Console.WriteLine(same ? "identical" : "DIFFERENT");
                        return same ? 0 : 1;
                    }
                    finally { File.Delete(tmp); }
                }
                default:
                    Console.WriteLine(Usage);
                    return 1;
            }
        }
        catch (Exception e) when (e is InvalidDataException || e is IOException)
        {
            Console.Error.WriteLine("error: " + e.Message);
            return 1;
        }
    }

    static Schema LoadSchema(string path) =>
        Directory.Exists(path) ? SchemaJson.Load(path) : SchemaDumper.Dump(path, null, new SyncLog());

    sealed class SyncLog : IProgress<string> { public void Report(string v) => Console.WriteLine(v); }
}
