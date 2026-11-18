// LIFT: Build wrapper, no PDB module. The SmartCouponDaemon project builds Timer.cpp with its own
// path for include\StlMemory.h (pseudocode of SmartCouponDaemon).
#define LIFT_STLMEMORY_FILE \
    L"e:\\dailybuild02\\smartcoupondaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\StlMemory.h"
#include "Timer.cpp"
