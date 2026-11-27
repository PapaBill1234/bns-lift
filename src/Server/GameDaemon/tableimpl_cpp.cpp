// tableimpl_cpp.cpp: tableimpl.cpp (GameDaemon PDB, 2019 + PDB).
#include "tableimpl.h"
#include "LiftStub.h"

// LIFT: keep the lifted functions until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops them). Card lift-gamedaemon-gap-005-e5.
#pragma comment(linker, "/INCLUDE:?ReferenceCopiedEl@DrDataTableImpl@@UEAAPEAUDrEl@@PEAU2@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??0DrDataTableImpl@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x6f7430
// LIFT: not lifted. The body writes the vftable of the base DrTable. The class has no base yet.
__cdecl DrDataTableImpl::~DrDataTableImpl(void)
{
    LIFT_STUB(0x6f7430);
}

// 0x6feec0
::DrEl * __cdecl DrDataTableImpl::ReferenceCopiedEl(::DrEl * elPtr)
{
    return elPtr;
}

// 0x6feed0
::DrEl *const __cdecl DrDataTableImpl::Find(wchar_t const *, ::DrAliasMap const &) const
{
    LIFT_STUB(0x6feed0);
}

// 0x6fefa0
__cdecl DrDataTableImpl::DrDataTableImpl(void)
{
    _tabledef = nullptr;
    _uselowmemory = false;
    _useLegacyElHeader = false;
}
