// boardgacha.cpp: boardgacha.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "boardgacha.h"
#include "pc.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?SendFail@BoardGachaRetrieveSeasonInfoWSO@@SAXPEAVPc@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SendFail@BoardGachaSessionCloseWSO@@SAXPEAVPc@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SendFail@BoardGachaBoardInfoReqWSO@@SAXPEAVPc@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SendFail@BoardGachaRetrieveParticipationInfoAllWSO@@SAXPEAVPc@@F@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0xb3e0
__cdecl BoardGacha::~BoardGacha(void)
{
    LIFT_STUB(0xb3e0);
}

// 0xb4b0
bool __cdecl BoardGacha::Init(void)
{
    LIFT_STUB(0xb4b0);
}

// 0xb6e0
bool __cdecl BoardGacha::setEmptyBoardParticipationInfoPacket(__int64)
{
    LIFT_STUB(0xb6e0);
}

// 0xb8f0
void __cdecl BoardGacha::broadcast(::Packet const *)
{
    LIFT_STUB(0xb8f0);
}

// 0xbac0
bool __cdecl BoardGacha::SetSeasonInfoPacketFromNotifyPacket(::FragmentPacket *)
{
    LIFT_STUB(0xbac0);
}

// 0xbb50
bool __cdecl BoardGacha::SendSeasonInfoPacket(::Pc *)
{
    LIFT_STUB(0xbb50);
}

// 0xbbd0
short __cdecl BoardGacha::SessionOpen(::Pc *)
{
    LIFT_STUB(0xbbd0);
}

// 0xbe10
bool __cdecl BoardGacha::SessionClose(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0xbe10);
}

// 0xbfc0
void __cdecl BoardGacha::BoardStart(::FragmentPacket *, __int64, int)
{
    LIFT_STUB(0xbfc0);
}

// 0xc0d0
void __cdecl BoardGacha::BoardEnd(__int64, int, ::FragmentPacket *)
{
    LIFT_STUB(0xc0d0);
}

// 0xc300
void __cdecl BoardGacha::ScheduleEnd(void)
{
    LIFT_STUB(0xc300);
}

// 0xc3b0
bool __cdecl BoardGacha::SendBoardInfo(::Pc *)
{
    LIFT_STUB(0xc3b0);
}

// 0xc430
bool __cdecl BoardGacha::SetBoardParticipationInfoPacket(::Packet *)
{
    LIFT_STUB(0xc430);
}

// 0xc4e0
void __cdecl BoardGacha::SendPacketToWorldPc(::Packet const *)
{
    LIFT_STUB(0xc4e0);
}

// 0xc580
void __cdecl BoardGacha::PostSessionClose(::Pc *)
{
    LIFT_STUB(0xc580);
}

// 0xc6f0
bool __cdecl BoardGachaUpdateSeasonScheduleWSO::Initialize(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0xc6f0);
}

// 0xc780
bool __cdecl BoardGachaUpdateSeasonScheduleWSO::initialize(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0xc780);
}

// 0xcc10
void __cdecl BoardGachaUpdateSeasonScheduleWSO::TimerExpired(long)
{
    LIFT_STUB(0xcc10);
}

// 0xcc80
__cdecl BoardGachaBoardStartWSO::BoardGachaBoardStartWSO(void)
{
    LIFT_STUB(0xcc80);
}

// 0xccf0
bool __cdecl BoardGachaBoardStartWSO::Initialize(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0xccf0);
}

// 0xce00
bool __cdecl BoardGachaBoardStartWSO::initializeBoardPacket(::FragmentPacketConcatenater *, __int64, __int64)
{
    LIFT_STUB(0xce00);
}

// 0xd160
void __cdecl BoardGachaBoardStartWSO::TimerExpired(long)
{
    LIFT_STUB(0xd160);
}

// 0xd1d0
bool __cdecl BoardGachaBoardEndWSO::Initialize(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0xd1d0);
}

// 0xd2d0
void __cdecl BoardGachaBoardEndWSO::TimerExpired(long)
{
    LIFT_STUB(0xd2d0);
}

// 0xd370
void __cdecl BoardGachaScheduleEndWSO::TimerExpired(long)
{
    LIFT_STUB(0xd370);
}

// 0xd400
bool __cdecl BoardGachaBoardParticipationInfoNotifyWSO::Initialize(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0xd400);
}

// 0xd790
void __cdecl BoardGachaBoardParticipationInfoNotifyWSO::TimerExpired(long)
{
    LIFT_STUB(0xd790);
}

// 0xd800
void __cdecl BoardGachaRetrieveSeasonInfoWSO::TimerExpired(long)
{
    LIFT_STUB(0xd800);
}

// 0xd9e0
void __cdecl BoardGachaRetrieveSeasonInfoWSO::SendFail(::Pc *pc, short failReason)
{
    // ❓ failReason is not used. The original sends the constant 2.
    if (pc != nullptr)
        pc->Send("hE", 1120, 2);
}

// 0xda10
void __cdecl BoardGachaSessionOpenWSO::TimerExpired(long)
{
    LIFT_STUB(0xda10);
}

// 0xdc20
void __cdecl BoardGachaSessionCloseWSO::TimerExpired(long)
{
    LIFT_STUB(0xdc20);
}

// 0xde40
void __cdecl BoardGachaSessionCloseWSO::SendFail(::Pc *pc, short failReason)
{
    // ❓ failReason is not used. The original sends the constant 2.
    if (pc != nullptr)
        pc->Send("hE", 1130, 2);
}

// 0xde70
void __cdecl BoardGachaBoardInfoReqWSO::TimerExpired(long)
{
    LIFT_STUB(0xde70);
}

// 0xdff0
void __cdecl BoardGachaBoardInfoReqWSO::SendFail(::Pc *pc, short failReason)
{
    // ❓ failReason is not used. The original sends the constant 2.
    if (pc != nullptr)
        pc->Send("hE", 1132, 2);
}

// 0xe020
void __cdecl BoardGachaRetrieveParticipationInfoAllWSO::TimerExpired(long)
{
    LIFT_STUB(0xe020);
}

// 0xe200
void __cdecl BoardGachaRetrieveParticipationInfoAllWSO::SendFail(::Pc *pc, short failReason)
{
    // ❓ failReason is not used. The original sends the constant 2.
    if (pc != nullptr)
        pc->Send("hE", 1141, 2);
}
