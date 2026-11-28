// smartcoupongamepackethandler.cpp: smartcoupongamepackethandler.cpp (GameDaemon PDB, 2019 + PDB).
#include "smartcoupongamepackethandler.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?HandleSmartCoupon_GameEventByCharacterOk@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandleSmartCoupon_GameEventByCharacterFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandleSmartCoupon_GameEventByAccountOk@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandleSmartCoupon_GameEventByAccountFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)

#define SCGPH_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\SmartCouponGamePacketHandler.cpp"

// 0x1bfed0
bool __cdecl HandleSmartCoupon_HelloOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1bfed0);
}

// 0x1bffd0
bool __cdecl HandleSmartCoupon_HelloFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1bffd0);
}

// 0x1c00d0
bool __cdecl HandleSmartCoupon_GameEventByCharacterOk(::Session const *, ::Packet const *packet)
{
    short c;
    __int64 gameTid;
    __int64 acceptLogId;
    packet->Decompose("hqq", &c, &gameTid, &acceptLogId);
    Log::Write(Log::LT_DEBUG, SCGPH_FILE, 56, L"[game-smart] GameEventByCharacterOk, tid:%I64d, acceptLogId:%I64d", gameTid,
               acceptLogId);
    return true;
}

// 0x1c0140
bool __cdecl HandleSmartCoupon_GameEventByCharacterFail(::Session const *, ::Packet const *packet)
{
    short c;
    __int64 gameTid;
    short errorReason;
    packet->Decompose("hqE", &c, &gameTid, &errorReason);
    Log::Write(Log::LT_ERROR, SCGPH_FILE, 67, L"[game-smart] GameEventByCharacterFail, tid:%I64d, errorCode:%d", gameTid,
               static_cast<int>(errorReason));
    return true;
}

// 0x1c01b0
bool __cdecl HandleSmartCoupon_GameEventByAccountOk(::Session const *, ::Packet const *packet)
{
    short c;
    __int64 gameTid;
    __int64 acceptLogId;
    packet->Decompose("hqq", &c, &gameTid, &acceptLogId);
    Log::Write(Log::LT_DEBUG, SCGPH_FILE, 80, L"[game-smart] GameEventByAccountOk, tid:%I64d, acceptLogId:%I64d", gameTid,
               acceptLogId);
    return true;
}

// 0x1c0220
bool __cdecl HandleSmartCoupon_GameEventByAccountFail(::Session const *, ::Packet const *packet)
{
    short c;
    __int64 gameTid;
    short errorReason;
    packet->Decompose("hqE", &c, &gameTid, &errorReason);
    Log::Write(Log::LT_ERROR, SCGPH_FILE, 91, L"[game-smart] GameEventByAccountFail, tid:%I64d, errorCode:%d", gameTid,
               static_cast<int>(errorReason));
    return true;
}
