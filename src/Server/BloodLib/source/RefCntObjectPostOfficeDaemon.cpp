// LIFT: Build wrapper, no PDB module. The PostOfficeDaemon project builds RefCntObject.cpp with its own
// __FILE__ path for include\RefCntObject.h (pseudocode of PostOfficeDaemon).
#define REFCNT_HEADER \
    L"e:\\dailybuild02\\postofficedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\RefCntObject.h"
#include "RefCntObject.cpp"
