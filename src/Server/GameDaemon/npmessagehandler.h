// npmessagehandler.h: npmessagehandler.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

bool __cdecl Handle_SrvGate_RegisterService(::NPChannel *, ::StsMsgLib::_StsMsg *, ::NPTransaction *);  // 0x16e400
bool __cdecl Handle_SrvPres_GetUserInfo(::NPChannel *, ::StsMsgLib::_StsMsg *, ::NPTransaction *);  // 0x16e470
bool __cdecl Handle_SrvGameGroup_RequestValidateGroup(::NPChannel *, ::StsMsgLib::_StsMsg *, ::NPTransaction *);  // 0x16e4e0
bool __cdecl Handle_SrvGameGroup_RequestGetChannelProperty(::NPChannel *, ::StsMsgLib::_StsMsg *, ::NPTransaction *);  // 0x16e630
bool __cdecl Handle_SrvGameGroup_RequestGroupInfo(::NPChannel *, ::StsMsgLib::_StsMsg *, ::NPTransaction *);  // 0x16e720
