// smartcoupongamepackethandler.h: smartcoupongamepackethandler.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

bool __cdecl HandleSmartCoupon_HelloOk(::Session const *, ::Packet const *);  // 0x1bfed0
bool __cdecl HandleSmartCoupon_HelloFail(::Session const *, ::Packet const *);  // 0x1bffd0
bool __cdecl HandleSmartCoupon_GameEventByCharacterOk(::Session const *, ::Packet const *);  // 0x1c00d0
bool __cdecl HandleSmartCoupon_GameEventByCharacterFail(::Session const *, ::Packet const *);  // 0x1c0140
bool __cdecl HandleSmartCoupon_GameEventByAccountOk(::Session const *, ::Packet const *);  // 0x1c01b0
bool __cdecl HandleSmartCoupon_GameEventByAccountFail(::Session const *, ::Packet const *);  // 0x1c0220
