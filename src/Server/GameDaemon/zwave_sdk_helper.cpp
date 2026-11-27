// zwave_sdk_helper.cpp: zwave_sdk_helper.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GameDaemonFwd.h"
#include "LiftStub.h"

// 0x1ee490
// LIFT: feature off (owner scope). The off form returns a null function pointer.
// LIFT: helper typedef, no PDB name. It is the return type from the PDB procedure record.
class IXigncodeServer2;
typedef int (*LoadHelperDll2WResult)(IXigncodeServer2**, int (*)(unsigned __int64, void*, const char*, unsigned long),
                                     void (*)(unsigned __int64, void*, int, const wchar_t*));
static LoadHelperDll2WResult LoadHelperDll2W(const wchar_t*)
{
    return 0;
}
