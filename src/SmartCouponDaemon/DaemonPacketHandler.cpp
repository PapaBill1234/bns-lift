// DaemonPacketHandler.obj (SmartCouponDaemon PDB). Source: .scratch/hr/DaemonPacketHandler.c
// Not done in this file: HandleSmartCoupon_HelloReq 0x7DC0, HandleSmartCoupon_GameEventByCharacterReq 0x8360,
// HandleSmartCoupon_GameEventByAccountReq 0x8E80, GameEventLogEvent::EventId 0x7D80.
#include "DaemonChannel.h"

// 0x7d30
unsigned long long DChannel::GetId()
{
    return static_cast<unsigned int>(((_daemonId._wid + (_daemonId._type << 16)) << 8) + _daemonId._reserved);
}

// 0x7d50
DChannel::~DChannel()
{
}
