// LobbyPredefine.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyPredefine.h"
#include "LiftStub.h"

// 0x96480
// LIFT: not in the gap-03 ID list. LobbyGatePresence::Kick (0x3ac20) calls it. Lifted so that Kick is not noreturn.
// The values map the kick reason to the lobby-gate kick reason (9 is skipped).
char GetLobbyGateKickReason(int reason)
{
    switch (reason)
    {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 6;
    case 7:
        return 7;
    case 8:
        return 8;
    case 10:
        return 9;
    case 11:
        return 10;
    case 12:
        return 11;
    default:
        return 0;
    }
}

// 0x96500
// LIFT: owned by gap-25-misc. KickJob::worldKickReq (0x87010) calls it. Lifted so that worldKickReq is not noreturn.
char GetGameWorldKickReason(int reason)
{
    switch (reason)
    {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 6;
    case 7:
        return 7;
    case 8:
        return 8;
    case 9:
        return 9;
    case 10:
        return 10;
    case 11:
        return 11;
    case 12:
        return 12;
    default:
        return 0;
    }
}

// 0x96580
bool GetId128FromGuidString(wchar_t const*, id128*)
{
    LIFT_STUB(0x96580);
}

// 0x966a0
bool CreateNewId128(id128*)
{
    LIFT_STUB(0x966a0);
}
