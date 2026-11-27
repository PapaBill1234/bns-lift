// npmessagehandler.cpp: npmessagehandler.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npmessagehandler.h"
#include "npchannel2.h"
#include "LiftStub.h"

// 0x16e400
bool __cdecl Handle_SrvGate_RegisterService(::NPChannel *, ::StsMsgLib::_StsMsg *, ::NPTransaction *)
{
    LIFT_STUB(0x16e400);
}

// 0x16e470
bool __cdecl Handle_SrvPres_GetUserInfo(::NPChannel *, ::StsMsgLib::_StsMsg *, ::NPTransaction *)
{
    LIFT_STUB(0x16e470);
}

// 0x16e4e0
bool __cdecl Handle_SrvGameGroup_RequestValidateGroup(::NPChannel *, ::StsMsgLib::_StsMsg *, ::NPTransaction *)
{
    LIFT_STUB(0x16e4e0);
}

// 0x16e630
bool __cdecl Handle_SrvGameGroup_RequestGetChannelProperty(::NPChannel *, ::StsMsgLib::_StsMsg *, ::NPTransaction *)
{
    LIFT_STUB(0x16e630);
}

// 0x16e720
bool __cdecl Handle_SrvGameGroup_RequestGroupInfo(::NPChannel *, ::StsMsgLib::_StsMsg *, ::NPTransaction *)
{
    LIFT_STUB(0x16e720);
}
