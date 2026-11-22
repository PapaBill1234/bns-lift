using System;
using System.Collections.Generic;
using System.IO;
using LegacyBin.Core.Pe;

namespace LegacyBin.Core.Schema
{
    /// <summary>
    /// Reads the table definition array that is compiled into an unpacked client executable.
    /// The array is: slot 0 = null, slot i = pointer to DrTableDef with type == i and a UTF-16 name.
    /// </summary>
    public static class SchemaDumper
    {
        const int MaxSlots = 4096;

        public static Schema Dump(string exePath, ulong? arrayVa = null, IProgress<string> log = null)
        {
            var pe = PeImage.Load(exePath);
            string packed = pe.PackedReason();
            if (packed != null)
                throw new InvalidDataException($"The executable looks packed or protected ({packed}). Use an unpacked client executable.");
            var l = pe.Is64 ? StructLayout.X64P4 : StructLayout.X86;
            log?.Report($"{Path.GetFileName(exePath)}: PE32{(pe.Is64 ? "+" : "")}, layout {l.Name}, link time {DateTimeOffset.FromUnixTimeSeconds(pe.TimeDateStamp):yyyy-MM-dd}");
            var (va, defs) = arrayVa.HasValue ? Walk(pe, l, arrayVa.Value) : Find(pe, l);
            if (defs.Count == 0) throw new InvalidDataException("No table definition array was found.");
            log?.Report($"Definition array at VA 0x{va:X}, {defs.Count} tables.");
            var schema = new Schema { Is64 = pe.Is64, Source = Path.GetFileName(exePath), Layout = l.Name, ArrayVa = va };
            var r = new Reader(pe, l);
            foreach (var td in defs)
            {
                var t = r.Table(td);
                schema.Tables[t.Type] = t;
            }
            return schema;
        }

        static bool SafeName(string s)
        {
            if (string.IsNullOrEmpty(s)) return false;
            foreach (char c in s) if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_' || c == '-')) return false;
            return true;
        }

        static bool Valid(PeImage pe, StructLayout l, ulong td, int i)
        {
            try
            {
                if (!pe.TryU(td, l.TdType, 2, out var t) || (short)t != (short)i) return false;
                return SafeName(pe.WStr(pe.Ptr(td, l.TdName)));
            }
            catch (InvalidDataException) { return false; }
        }

        static (ulong, List<ulong>) Walk(PeImage pe, StructLayout l, ulong va)
        {
            var list = new List<ulong>();
            if (!pe.TryU(va, 0, l.P, out var s0) || s0 != 0) return (va, list);
            for (int i = 1; i < MaxSlots; i++)
            {
                if (!pe.TryU(va, i * l.P, l.P, out var td) || !Valid(pe, l, td, i)) break;
                list.Add(td);
            }
            return (va, list);
        }

        static (ulong, List<ulong>) Find(PeImage pe, StructLayout l)
        {
            (ulong va, List<ulong> defs) best = (0, new List<ulong>());
            foreach (var (start, size) in pe.DataSections())
            {
                ulong off = ((ulong)l.P - start % (ulong)l.P) % (ulong)l.P;
                for (; off + (ulong)(2 * l.P) <= size; off += (ulong)l.P)
                {
                    ulong va = start + off;
                    if (pe.U(va, 0, l.P) != 0) continue;
                    if (!Valid(pe, l, pe.U(va, l.P, l.P), 1)) continue;
                    var cand = Walk(pe, l, va);
                    if (cand.Item2.Count >= 16 && cand.Item2.Count > best.defs.Count) best = cand;
                }
            }
            return best;
        }

        sealed class Reader
        {
            readonly PeImage pe; readonly StructLayout l;
            public Reader(PeImage pe, StructLayout l) { this.pe = pe; this.l = l; }

            ulong U(ulong v, int o, int n) => pe.U(v, o, n);
            ulong P(ulong v, int o) => pe.Ptr(v, o);
            string Name(ulong v, int o) => pe.WStr(P(v, o));

            DefaultRecord DefRec(ulong v) => pe.IsMapped(v)
                ? new DefaultRecord { Type = (sbyte)U(v, 0, 1), SubType = (short)U(v, 2, 2), Size = (int)U(v, 4, 2) }
                : null;

            List<AttrDef> Attrs(ulong v, int n)
            {
                var list = new List<AttrDef>(n);
                for (int i = 0; i < n; i++)
                {
                    ulong a = v + (ulong)(i * l.AStride);
                    var d = new AttrDef
                    {
                        Name = Name(a, l.AName),
                        Type = AttrTypes.Name((int)U(a, l.AType, 1)),
                        Key = U(a, l.AKey, 1) != 0,
                        Repeat = (int)U(a, l.ARepeat, 1),
                        Required = (int)U(a, l.ARequired, 1),
                        DefValue = Name(a, l.ADefValue),
                        Min = (long)U(a, l.AMin, 8),
                        Max = (long)U(a, l.AMax, 8),
                        FMin = BitConverter.ToSingle(BitConverter.GetBytes((uint)U(a, l.AFMin, 4)), 0),
                        FMax = BitConverter.ToSingle(BitConverter.GetBytes((uint)U(a, l.AFMax, 4)), 0),
                        SeqCount = (int)U(a, l.ASeqCount, 2),
                        RefTable = (short)U(a, l.ARefTable, 2),
                        RefEl = (int)U(a, l.ARefEl, 1),
                        Deprecated = U(a, l.ADeprecated, 1) != 0,
                        Hidden = U(a, l.AHidden, 1) != 0,
                        Offset = (int)U(a, l.AOffset, 2),
                        Size = (int)U(a, l.ASize, 2),
                        PropField = (uint)U(a, l.APropField, 4),
                    };
                    ulong hv = P(a, l.ANameHash);
                    if (pe.IsMapped(hv)) { d.NameHash = (uint)U(hv, l.NhHash, 4); d.NameHashName = Name(hv, l.NhName); }
                    ulong sv = P(a, l.ASeq);
                    if (pe.IsMapped(sv))
                    {
                        d.Seq = new List<string>(d.SeqCount);
                        for (int k = 0; k < d.SeqCount; k++) d.Seq.Add(pe.WStr(P(sv, k * l.P)));
                    }
                    list.Add(d);
                }
                return list;
            }

            public TableDef Table(ulong v)
            {
                var t = new TableDef
                {
                    Name = Name(v, l.TdName),
                    Type = (short)U(v, l.TdType, 2),
                    Major = (short)U(v, l.TdMajor, 2),
                    Minor = (short)U(v, l.TdMinor, 2),
                    MaxId = U(v, l.TdMaxId, 4),
                    AutoKey = U(v, l.TdAutoKey, 1) != 0,
                    Module = (uint)U(v, l.TdModule, 4),
                };
                ulong elv = P(v, l.TdEl);
                int elc = (int)U(v, l.TdElCount, 1);
                for (int i = 0; i < elc; i++)
                {
                    ulong ev = elv + (ulong)(i * l.ElStride);
                    ulong bv = P(ev, l.ElBody);
                    int ac = (short)U(bv, l.BdAttrCount, 2), sc = (short)U(bv, l.BdSubCount, 2);
                    if (ac < 0 || sc < 0) throw new InvalidDataException($"Negative attribute/subtype count in table {t.Name}.");
                    var e = new ElementDef
                    {
                        Name = Name(ev, l.ElName),
                        Type = (int)U(ev, l.ElType, l.ElTypeSize),
                        Attrs = Attrs(P(bv, l.BdAttr), ac),
                        DefaultRecord = DefRec(P(bv, l.BdDefRec)),
                        Size = (int)U(bv, l.BdSize, 2),
                        KeyOffset = (int)U(bv, l.BdKeyOffset, 2),
                    };
                    ulong sv = P(bv, l.BdSub);
                    for (int j = 0; j < sc; j++)
                    {
                        ulong s = sv + (ulong)(j * l.SbStride);
                        e.Subs.Add(new SubDef
                        {
                            Name = Name(s, l.SbName),
                            Attrs = Attrs(P(s, l.SbAttr), (int)U(s, l.SbAttrCount, 2)),
                            DefaultRecord = DefRec(P(s, l.SbDefRec)),
                            Size = (int)U(s, l.SbSize, 2),
                        });
                    }
                    for (int k = 0; k < 32; k++) e.Child[k] = (byte)U(ev, l.ElChild + k, 1);
                    t.Elements.Add(e);
                }
                return t;
            }
        }
    }
}
