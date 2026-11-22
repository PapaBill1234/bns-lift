// PostOfficeClientSideHandlerList.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "PostOfficeClientSideHandlerList.h"
#include "Daemon.h"
#include "LiftStub.h"
#include "PostOfficePacketHandler.h"

// 0x32b50 (PDB: operator delete, folded with Console::Flush). The body is empty: one ret.
// LIFT: the lifted code has no own function here. The empty Console::Flush (BloodLib) and the empty
// virtual and class operator delete bodies cover this address.

// 0x203770 (data, RVA). Index = command. Entries 0, 1 and 4 are empty in the original.
Daemon::PacketHandler PostOfficePacketClientSideHandlerList[7] = {
    nullptr,
    nullptr,
    HandlePostOfficeHelloOk,
    HandlePostOfficeHelloFail,
    nullptr,
    HandlePostOfficeRegisterPostOk,
    HandlePostOfficeRegisterPostFail,
};
