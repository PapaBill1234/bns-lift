// LobbyInfoGatePacketLobbySideHandlerList (LobbyDaemon PDB, 2019 + PDB, data only).
// LIFT: PDB global at .data rva 0x202D30. The original is a data-only definition, so the compiler cannot fold the entries
// into InfoGateChannelManager::PacketHandler. This file keeps it in its own translation unit.
#include "LobbyInfoGatePacketHandler.h"

#define LD_H(f) reinterpret_cast<void*>(&(f))
// Entries read from .data at rva 0x202D30: 1 HelloReq (auth 0), 4 AuthTokenReq (auth 1), 7 GetWorldInfoListReq (auth 1).
// No entry is a fragment handler. All other entries are null.
LobbyInfoGatePacketHandlerDef LobbyInfoGatePacketLobbySideHandlerList[11] = {
    /*  0 */ {nullptr, false, false},
    /*  1 */ {LD_H(HandleLobbyInfoGate_HelloReq), false, false},
    /*  2 */ {nullptr, false, false},
    /*  3 */ {nullptr, false, false},
    /*  4 */ {LD_H(HandleLobbyInfoGate_AuthTokenReq), true, false},
    /*  5 */ {nullptr, false, false},
    /*  6 */ {nullptr, false, false},
    /*  7 */ {LD_H(HandleLobbyInfoGate_GetWorldInfoListReq), true, false},
    /*  8 */ {nullptr, false, false},
    /*  9 */ {nullptr, false, false},
    /* 10 */ {nullptr, false, false}};
#undef LD_H
