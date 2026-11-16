// SmartCouponManagerPacketSmartCouponSideHandlerList.obj (SmartCouponDaemon PDB, data only).
#include "ManagerChannel.h"

// 0x836b0
bool (*SmartCouponManagerPacketSmartCouponSideHandlerList[10])(Session const* session, Packet const* packet) = {
    nullptr,
    HandleSmartCouponManager_HelloReq,
    nullptr,
    nullptr,
    HandleSmartCouponManager_RetryCouponPublicationReq,
    nullptr,
    nullptr,
    HandleSmartCouponManager_LoadRetryReadyGameEventLogListReq,
    nullptr,
    nullptr,
};

// 0x84a10 (bss, all slots are zero)
// ❓ element type. The PDB slot type is not checked. It uses the same type as the list above.
bool (*SmartCouponManagerPacketSmartCouponSideFragmentHandlerList[10])(Session const* session, Packet const* packet) = {};
