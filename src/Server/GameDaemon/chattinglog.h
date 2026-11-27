// chattinglog.h: chattinglog.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ChattingLog
{
public:
    static void __cdecl MessageByItemDistrict(__int64, wchar_t const *, __int64, __int64, __int64, wchar_t const *, wchar_t const *, __int64, __int64, wchar_t const *, __int64, __int64);  // 0x291490
    static void __cdecl MessageByItemWorld(__int64, wchar_t const *, __int64, __int64, __int64, wchar_t const *, wchar_t const *, __int64, __int64, wchar_t const *, __int64, __int64);  // 0x291630
    static void __cdecl Normal(__int64, wchar_t const *, __int64, __int64, __int64, wchar_t const *, wchar_t const *, __int64, __int64, wchar_t const *);  // 0x5d48a0
    static void __cdecl Whisper(__int64, wchar_t const *, __int64, __int64, __int64, wchar_t const *, wchar_t const *, __int64, __int64, wchar_t const *, __int64, wchar_t const *, wchar_t const *);  // 0x5d4a30
};

