// winserviceconsole_gd.h: winserviceconsole.cpp, winserviceconsole.h (GameDaemon PDB, 2019 + PDB).
// LIFT: 0x455420 is ActSequenceLoader::ReadFromBuffer in the PDB. It is declared in actsequenceloader.h.
#pragma once
#include "GameDaemonFwd.h"

// PDB layout (size 0x8): vfptr only. The slot order follows the PDB.
// LIFT: no lifted class derives from DrTable yet and nothing constructs it. Thus the non-pure members have no definition here.
class DrTable
{
public:
    virtual __cdecl ~DrTable(void);  // slot 0
    virtual int __cdecl GetTableType(void) = 0;  // slot 1. LIFT: the PDB return type is TableType.
    virtual void __cdecl PrepareLoadAlias(void);  // slot 2
    virtual bool __cdecl LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &) = 0;  // slot 3
    virtual void __cdecl FinishLoadAlias(void);  // slot 4
    virtual void __cdecl PrepareLoadTable(void);  // slot 5
    virtual bool __cdecl LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &) = 0;  // slot 6
    virtual void __cdecl FinishLoadTable(::DrElReader const &, ::DrLoaderDef const &);  // slot 7
    virtual bool __cdecl LoadTableMT_PreProc(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &) = 0;  // slot 8
    virtual bool __cdecl LoadTableMT_PostProc(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &) = 0;  // slot 9
    virtual bool __cdecl ReadFromBuffer(::DrElReader const &, ::DrLoaderDef const &, unsigned char const *, unsigned __int64) = 0;  // slot 10
    virtual void __cdecl GetTableSummary(::DrTableSummary &) = 0;  // slot 11
    virtual void __cdecl UseLegacyElHeader(bool) = 0;  // slot 12
    virtual bool __cdecl ReloadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &) = 0;  // slot 13
    virtual bool __cdecl ReplaceL10NData(::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &) = 0;  // slot 14
    virtual void __cdecl PrintTable(::DrElReader const &, ::DrLoaderDef const &, ::DrLog *) = 0;  // slot 15
    virtual unsigned __int64 __cdecl WriteSize(void) const = 0;  // slot 16
    virtual bool __cdecl WriteToBuffer(::DrElReader const &, ::DrLoaderDef const &, unsigned char *, unsigned __int64) = 0;  // slot 17
    virtual bool __cdecl CanBeLoadedPieceByPiece(void);  // slot 18
};
