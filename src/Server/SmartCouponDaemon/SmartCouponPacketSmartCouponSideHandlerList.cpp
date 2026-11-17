// SmartCouponPacketSmartCouponSideHandlerList.obj (SmartCouponDaemon PDB, data only).
#include "DaemonChannel.h"

// 0x83660
bool (*SmartCouponPacketSmartCouponSideHandlerList[10])(Session const* session, Packet const* packet) = {
    nullptr,
    HandleSmartCoupon_HelloReq,  // 0x7DC0
    nullptr,
    nullptr,
    HandleSmartCoupon_GameEventByCharacterReq,  // 0x8360
    nullptr,
    nullptr,
    HandleSmartCoupon_GameEventByAccountReq,  // 0x8E80
    nullptr,
    nullptr,
};
