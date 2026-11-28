// defmemory_h.cpp: defmemory.h (GameDaemon PDB, 2019 + PDB).
#include "defmemory.h"
#include "LiftStub.h"

// LIFT: both Instance bodies stay stubs. LTCG + ICF folds the DrHeapMemory vftable with the derived
// vftables (the original keeps a separate derived deleting dtor at 0x6eb430). A later card lifts them.

// 0x6ecf90
::DrBaseStaticMemory * __cdecl DrBaseStaticMemory::Instance(void)
{
    LIFT_STUB(0x6ecf90);
}

// 0x6ecff0
::DrBaseDynamicMemory * __cdecl DrBaseDynamicMemory::Instance(void)
{
    LIFT_STUB(0x6ecff0);
}
