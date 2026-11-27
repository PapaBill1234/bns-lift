// actsequenceloader_h.cpp: actsequenceloader.h (GameDaemon PDB, 2019 + PDB).
#include "actsequenceloader.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetTableType@ActSequenceLoader@@UEAA?AW4TableType@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x35f50
::TableType __cdecl ActSequenceLoader::GetTableType(void)
{
    // LIFT: TableType has no enumerators in GameDaemonFwd.h yet. 10 is the PDB value TABLE_TYPE_CUSTOM.
    return static_cast< ::TableType>(10);
}

// 0x3fee30
bool __cdecl ActSequenceLoader::LoadTableMT_PreProc(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x3fee30);
}
