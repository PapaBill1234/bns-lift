// LIFT: Build wrapper, no PDB module. The PostOfficeDaemon project builds Port.cpp with its own
// path for include\StlMemory.h (pseudocode of PostOfficeDaemon).
#define LIFT_STLMEMORY_FILE \
    L"e:\\dailybuild02\\postofficedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\StlMemory.h"
#include "Port.cpp"
