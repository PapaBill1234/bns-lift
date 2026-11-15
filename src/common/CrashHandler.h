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
};
