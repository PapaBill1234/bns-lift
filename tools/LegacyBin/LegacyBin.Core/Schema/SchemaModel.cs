using System.Collections.Generic;

namespace LegacyBin.Core.Schema
{
    /// <summary>Field type codes of the client (<c>DrAttrType</c>, GM client 2021 PDB).</summary>
    public static class AttrTypes
    {
        static readonly Dictionary<int, string> Names = new Dictionary<int, string>
        {
            [1] = "int8", [2] = "int16", [3] = "int32", [4] = "int64", [5] = "float32", [6] = "bool",
            [7] = "string", [8] = "seq", [9] = "seq16", [10] = "ref", [11] = "tref", [12] = "sub",
            [13] = "su", [14] = "vector16", [15] = "vector32", [16] = "icolor", [17] = "fcolor", [18] = "box",
            [19] = "angle", [20] = "msec", [21] = "distance", [22] = "velocity", [23] = "prop_seq",
            [24] = "prop_field", [25] = "script_obj", [26] = "native", [27] = "version", [28] = "icon",
            [29] = "time32", [30] = "time64", [31] = "timeutc", [32] = "asset",
        };
        public static string Name(int code) => Names.TryGetValue(code, out var n) ? n : "type_" + code;
    }

    public sealed class AttrDef
    {
        public string Name;
        public uint? NameHash;
        public string NameHashName;
        public string Type;
        public bool Key;
        public int Repeat;
        public int Required;
        public string DefValue;
        public long Min, Max;
        public float FMin, FMax;
        public List<string> Seq;
        public int SeqCount;
        public short RefTable;
        public int RefEl;
        public bool Deprecated, Hidden;
        public int Offset, Size;
        public uint PropField;
    }

    public sealed class DefaultRecord { public int Type, SubType, Size; }

    public sealed class SubDef
    {
        public string Name;
        public List<AttrDef> Attrs = new List<AttrDef>();
        public DefaultRecord DefaultRecord;
        public int Size;
    }

    public sealed class ElementDef
    {
        public string Name;
        public int Type;
        public List<AttrDef> Attrs = new List<AttrDef>();
        public List<SubDef> Subs = new List<SubDef>();
        public DefaultRecord DefaultRecord;
        public int Size;
        public int KeyOffset;
        public byte[] Child = new byte[32];
    }

    public sealed class TableDef
    {
        public string Name;
        public short Type;
        public short Major, Minor;
        public List<ElementDef> Elements = new List<ElementDef>();
        public ulong MaxId;
        public bool AutoKey;
        public uint Module;
        public string Version => $"{Major}.{Minor}";
    }

    /// <summary>All table definitions of one client build and one pointer width.</summary>
    public sealed class Schema
    {
        public bool Is64;
        public string Source;
        public string Layout;
        public ulong ArrayVa;
        public Dictionary<int, TableDef> Tables = new Dictionary<int, TableDef>();
        public TableDef Find(int type) => Tables.TryGetValue(type, out var t) ? t : null;
    }
}
