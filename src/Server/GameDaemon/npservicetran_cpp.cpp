// npservicetran_cpp.cpp: npservicetran.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npservicetran.h"
#include "LiftStub.h"

namespace
{
// LIFT: PDB enumerators of NPCustomProtocolType. The skeleton enum in GameDaemonFwd.h has no enumerators yet.
enum
{
    NP_CUSTOM_PROTOCOL_TYPE_GAME = 1,
    NP_CUSTOM_PROTOCOL_TYPE_WORLD = 2,
    NP_CUSTOM_PROTOCOL_TYPE_GAMEWAREHOUSE = 3,
    NP_CUSTOM_PROTOCOL_TYPE_AUCTION = 4,
    NP_CUSTOM_PROTOCOL_TYPE_GAMEGROUP = 5
};
}  // namespace

// 0x16f4e0
#pragma comment(linker, "/INCLUDE:?GetNPCustomProtocolStr@@YAPEADW4NPCustomProtocolType@@@Z")  // LIFT: dead-strip keep (no live caller yet)
char * __cdecl GetNPCustomProtocolStr(::NPCustomProtocolType type)
{
    switch (static_cast<int>(type))
    {
    case NP_CUSTOM_PROTOCOL_TYPE_GAME:
        return "Srv2Game";
    case NP_CUSTOM_PROTOCOL_TYPE_WORLD:
        return "Srv2World";
    case NP_CUSTOM_PROTOCOL_TYPE_GAMEWAREHOUSE:
        return "Srv2GameWarehouse";
    case NP_CUSTOM_PROTOCOL_TYPE_AUCTION:
        return "Srv2GameAuction";
    case NP_CUSTOM_PROTOCOL_TYPE_GAMEGROUP:
        return "Srv2GameGroup";
    default:
        return "Invalid";
    }
}

// 0x16f530
__cdecl NPRegisterServiceTran::NPRegisterServiceTran(void)
{
    LIFT_STUB(0x16f530);
}

// 0x16f5a0
bool __cdecl NPRegisterServiceTran::init(int, void *)
{
    LIFT_STUB(0x16f5a0);
}

// 0x16f640
bool __cdecl NPRegisterServiceTran::work(int, void *)
{
    LIFT_STUB(0x16f640);
}

// 0x16f6c0
bool __cdecl NPRegisterServiceTran::request(void *)
{
    LIFT_STUB(0x16f6c0);
}

// 0x16fa00
bool __cdecl NPRegisterServiceTran::response(void *)
{
    LIFT_STUB(0x16fa00);
}

// 0x16fc40
bool __cdecl NPRegisterServiceTran::expire(void *)
{
    LIFT_STUB(0x16fc40);
}

// 0x16fcc0
bool __cdecl NPValidateGroupTran::work(int, void *)
{
    LIFT_STUB(0x16fcc0);
}

// 0x16fd10
bool __cdecl NPValidateGroupTran::validateGroup(void *)
{
    LIFT_STUB(0x16fd10);
}

// 0x170690
__cdecl NPGetChannelPropertyTran::NPGetChannelPropertyTran(void)
{
    LIFT_STUB(0x170690);
}

// 0x170730
bool __cdecl NPGetChannelPropertyTran::work(int, void *)
{
    LIFT_STUB(0x170730);
}

// 0x170780
bool __cdecl NPGetChannelPropertyTran::getChannelProperty(void *)
{
    LIFT_STUB(0x170780);
}

// 0x170a10
bool __cdecl NPGroupInfoTran::work(int, void *)
{
    LIFT_STUB(0x170a10);
}

// 0x170a60
bool __cdecl NPGroupInfoTran::groupInfo(void *)
{
    LIFT_STUB(0x170a60);
}
