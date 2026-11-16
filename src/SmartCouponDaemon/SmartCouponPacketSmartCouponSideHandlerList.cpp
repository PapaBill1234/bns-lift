// SmartCouponPacketSmartCouponSideHandlerList.obj (SmartCouponDaemon PDB, data only).
#include "DaemonChannel.h"

// 0x83660
// ❓ Slots 1, 4 and 7 point to HandleSmartCoupon_HelloReq (0x7DC0), HandleSmartCoupon_GameEventByCharacterReq
// (0x8360) and HandleSmartCoupon_GameEventByAccountReq (0x8E80). These handlers are not lifted yet, so the slots are null.
bool (*SmartCouponPacketSmartCouponSideHandlerList[10])(Session const* session, Packet const* packet) = {
    nullptr,
    nullptr,  // ❓ HandleSmartCoupon_HelloReq 0x7DC0
    nullptr,
    nullptr,
    nullptr,  // ❓ HandleSmartCoupon_GameEventByCharacterReq 0x8360
    nullptr,
    nullptr,
    nullptr,  // ❓ HandleSmartCoupon_GameEventByAccountReq 0x8E80
    nullptr,
    nullptr,
};
