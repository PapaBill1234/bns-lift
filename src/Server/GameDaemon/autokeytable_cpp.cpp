// autokeytable_cpp.cpp: autokeytable.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "autokeytable.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?FinishLoadAlias@DrAutoKeyTable@@UEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Find@DrAutoKeyTable@@UEBAQEAUDrEl@@_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?destroy@DrAutoKeyElMap@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x6fd320
bool __cdecl DrAutoKeyTable::LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x6fd320);
}

// 0x6fd410
void __cdecl DrAutoKeyTable::FinishLoadAlias(void)
{
    _nextAutoKey = 1;
}

// 0x6fd4c0
void __cdecl DrAutoKeyTable::constructExtraBuffer(::DrElReader const &, ::DrLoaderDef const &, bool)
{
    LIFT_STUB(0x6fd4c0);
}

// 0x6fd620
void __cdecl DrAutoKeyTable::FinishLoadTable(::DrElReader const &, ::DrLoaderDef const &)
{
    LIFT_STUB(0x6fd620);
}

// 0x6fd630
bool __cdecl DrAutoKeyTable::LoadTableMT_PostProc(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x6fd630);
}

// 0x6fd6c0
void __cdecl DrAutoKeyTable::GetTableSummary(::DrTableSummary &)
{
    LIFT_STUB(0x6fd6c0);
}

// 0x6fd790
::DrEl *const __cdecl DrAutoKeyTable::Find(unsigned __int64 key) const
{
    if (key >= _elMap.elCount)
        return nullptr;
    return _elMap.elArray[key];
}

// 0x6fd7b0
::DrInnerIter * __cdecl DrAutoKeyTable::createInnerIter(::DrEl *const) const
{
    LIFT_STUB(0x6fd7b0);
}

// 0x6fd8d0
void __cdecl DrAutoKeyTable::removeInnerIter(::DrInnerIter *) const
{
    LIFT_STUB(0x6fd8d0);
}

// 0x6fd920
::DrInnerIter * __cdecl DrAutoKeyTable::createInnerIter(void) const
{
    LIFT_STUB(0x6fd920);
}

// 0x6fda40
void __cdecl DrAutoKeyElMap::destroy(void)
{
    elArray.clear();
    elCount = 0;
}

// 0x6fdab0
void __cdecl DrAutoKeyTable::clearElMap(void)
{
    LIFT_STUB(0x6fdab0);
}

// 0x6fdb30
__cdecl DrAutoKeyElMap::~DrAutoKeyElMap(void)
{
    LIFT_STUB(0x6fdb30);
}

// 0x6fdf80
void __cdecl DrAutoKeyTable::PrepareLoadTable(void)
{
    LIFT_STUB(0x6fdf80);
}

// 0x6fe030
__cdecl DrAutoKeyTable::DrAutoKeyTable(void)
{
    LIFT_STUB(0x6fe030);
}

// 0x6fe090
__cdecl DrAutoKeyTable::~DrAutoKeyTable(void)
{
    LIFT_STUB(0x6fe090);
}

// 0x6fe150
void __cdecl DrAutoKeyElMap::construct(unsigned __int64)
{
    LIFT_STUB(0x6fe150);
}

// 0x6fe220
bool __cdecl DrAutoKeyTable::setup(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &)
{
    LIFT_STUB(0x6fe220);
}

// 0x6fe3d0
bool __cdecl DrAutoKeyTable::LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x6fe3d0);
}

// 0x6fe600
bool __cdecl DrAutoKeyTable::LoadTableMT_PreProc(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x6fe600);
}

// 0x6fe7f0
bool __cdecl DrAutoKeyTable::ReadFromBuffer(::DrElReader const &, ::DrLoaderDef const &, unsigned char const *, unsigned __int64)
{
    LIFT_STUB(0x6fe7f0);
}
