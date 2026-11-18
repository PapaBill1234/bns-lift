// LIFT: Build wrapper, no PDB module. The SmartCouponDaemon project builds RefCntObject.cpp with its own
// __FILE__ path for include\RefCntObject.h (pseudocode of SmartCouponDaemon).
#define REFCNT_HEADER \
    L"e:\\dailybuild02\\smartcoupondaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\RefCntObject.h"
#define REFCNT_HEADER_ALT \
    L"E:\\DailyBuild02\\SmartCouponDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\RefCntObject.h"
#include "RefCntObject.cpp"
