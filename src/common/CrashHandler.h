// CrashHandler (CacheGate PDB). Declarations only. The bodies are in a later card.
#pragma once

class CrashHandler
{
public:
    // 0x8450 TODO(lift-crashhandler)
    // ❓ LTCG removed the arguments. The call in BloodDaemonMain sets no registers.
    static bool Initialize(int, bool);
    // 0x8530 TODO(lift-crashhandler)
    static void SetMailInfo(wchar_t const* to, wchar_t const* from, wchar_t const* mailServer);
    // 0x8790 TODO(lift-crashhandler)
    static void MakeCrash(char const* file, int line, wchar_t const* format, ...);
    // 0x1E570 (SmartCouponDaemon) TODO(lift-crashhandler)
    static void SetLogPath(wchar_t const* logPath);

    static CrashHandler* Instance;  // SmartCouponDaemon. TODO(lift-crashhandler)

    // SmartCouponDaemon layout (sizeof 0x840). Only the members that the app code uses.
    unsigned char _pad0[0x218];             // ❓ members not lifted
    int _option;                            // 0x218
    int _dumpType;                          // 0x21C
    unsigned char _pad1[0x840 - 0x220];     // ❓ members not lifted
};
