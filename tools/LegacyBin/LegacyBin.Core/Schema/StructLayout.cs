namespace LegacyBin.Core.Schema
{
    /// <summary>
    /// Byte offsets of the in-memory definition structs (DrTableDef, DrElDef, DrElBodyDef, DrSubDef, DrAttrDef).
    /// x86: 2020 Client.exe 0.0.381 (verified field-by-field against TableDefs 0.0.381.8876 x86).
    /// x64p4: BNSR_116.exe 2026 (4-byte packed x64).
    /// </summary>
    public sealed class StructLayout
    {
        public string Name; public int P;
        // DrTableDef
        public int TdName, TdType, TdMajor, TdMinor, TdEl, TdElCount, TdMaxId, TdAutoKey, TdModule;
        // DrElDef
        public int ElStride, ElName, ElType, ElTypeSize, ElBody, ElChild;
        // DrElBodyDef
        public int BdStride, BdAttr, BdSub, BdDefRec, BdAttrCount, BdSubCount, BdSize, BdKeyOffset;
        // DrSubDef
        public int SbStride, SbName, SbAttr, SbDefRec, SbAttrCount, SbSize;
        // DrAttrDef
        public int AStride, AName, ANameHash, AType, AKey, ARepeat, ARequired, ADefValue, AMin, AMax, AFMin, AFMax,
            ASeq, ASeqCount, ARefTable, ARefEl, ADeprecated, AHidden, AOffset, ASize, APropField;
        // {u32 hash, wchar* name}
        public int NhHash, NhName;

        public static readonly StructLayout X86 = new StructLayout
        {
            Name = "x86", P = 4,
            TdName = 0, TdType = 4, TdMajor = 6, TdMinor = 8, TdEl = 12, TdElCount = 16, TdMaxId = 20, TdAutoKey = 28, TdModule = 32,
            ElStride = 44, ElName = 0, ElType = 4, ElTypeSize = 1, ElBody = 8, ElChild = 12,
            BdStride = 20, BdAttr = 0, BdSub = 4, BdDefRec = 8, BdAttrCount = 12, BdSubCount = 14, BdSize = 16, BdKeyOffset = 18,
            SbStride = 16, SbName = 0, SbAttr = 4, SbDefRec = 8, SbAttrCount = 12, SbSize = 14,
            AStride = 64, AName = 0, ANameHash = 4, AType = 8, AKey = 9, ARepeat = 10, ARequired = 11, ADefValue = 12,
            AMin = 16, AMax = 24, AFMin = 32, AFMax = 36, ASeq = 40, ASeqCount = 44, ARefTable = 46, ARefEl = 48,
            ADeprecated = 49, AHidden = 50, AOffset = 52, ASize = 54, APropField = 56,
            NhHash = 0, NhName = 4,
        };

        public static readonly StructLayout X64P4 = new StructLayout
        {
            Name = "x64p4", P = 8,
            TdName = 0, TdType = 8, TdMajor = 10, TdMinor = 12, TdEl = 16, TdElCount = 24, TdMaxId = 28, TdAutoKey = 36, TdModule = 40,
            ElStride = 52, ElName = 0, ElType = 8, ElTypeSize = 4, ElBody = 12, ElChild = 20,
            BdStride = 32, BdAttr = 0, BdSub = 8, BdDefRec = 16, BdAttrCount = 24, BdSubCount = 26, BdSize = 28, BdKeyOffset = 30,
            SbStride = 28, SbName = 0, SbAttr = 8, SbDefRec = 16, SbAttrCount = 24, SbSize = 26,
            AStride = 84, AName = 0, ANameHash = 8, AType = 16, AKey = 17, ARepeat = 18, ARequired = 19, ADefValue = 20,
            AMin = 28, AMax = 36, AFMin = 44, AFMax = 48, ASeq = 52, ASeqCount = 60, ARefTable = 62, ARefEl = 64,
            ADeprecated = 65, AHidden = 66, AOffset = 68, ASize = 70, APropField = 72,
            NhHash = 0, NhName = 4,
        };
    }
}
