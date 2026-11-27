// partymatchmaker_cpp.cpp: partymatchmaker.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "partymatchmaker.h"
#include "pc.h"
#include "LiftStub.h"

// 0x18ad50
__cdecl PartyMatchQueue::~PartyMatchQueue(void)
{
    LIFT_STUB(0x18ad50);
}

// 0x18add0
void __cdecl PartyMatchQueue::clearGarbages(void)
{
    LIFT_STUB(0x18add0);
}

// 0x18aff0
::Pc * __cdecl PartyMatchQueue::pop(int)
{
    LIFT_STUB(0x18aff0);
}

// 0x18b0e0
void __cdecl PartyMatchQueue::push(int, ::Pc *)
{
    LIFT_STUB(0x18b0e0);
}

// 0x18b1a0
__cdecl PartyMatchPoint::PartyMatchPoint(void)
{
    LIFT_STUB(0x18b1a0);
}

// 0x18b1f0
__cdecl PartyMatchPoint::~PartyMatchPoint(void)
{
    LIFT_STUB(0x18b1f0);
}

// 0x18b200
void __cdecl PartyMatchPoint::add(::Pc *)
{
    LIFT_STUB(0x18b200);
}

// 0x18b250
void __cdecl PartyMatchPoint::matchPartyToPc(void)
{
    LIFT_STUB(0x18b250);
}

// 0x18b3b0
void __cdecl PartyMatchPoint::matchPcToPc(void)
{
    LIFT_STUB(0x18b3b0);
}

// 0x18b490
bool __cdecl PartyMatchPoint::findJobInParty(::Pc *, bool *const)
{
    LIFT_STUB(0x18b490);
}

// 0x18b710
void __cdecl PartyMatchPoint::sendFail(::Pc *, short)
{
    LIFT_STUB(0x18b710);
}

// 0x18b800
void __cdecl PartyMatchPoint::sendMatch(::Pc *, ::Pc *)
{
    LIFT_STUB(0x18b800);
}

// 0x18bb40
void __cdecl PartyMatchPoint::sendMatch2(::Pc *, ::Pc *)
{
    LIFT_STUB(0x18bb40);
}

// 0x18be80
bool __cdecl PartyMatchPoint::send(::Pc *, ::Pc *, bool)
{
    LIFT_STUB(0x18be80);
}

// 0x18bfa0
__cdecl PartyMatchMaker::PartyMatchMaker(void)
{
    LIFT_STUB(0x18bfa0);
}

// 0x18c080
__cdecl PartyMatchMaker::~PartyMatchMaker(void)
{
    LIFT_STUB(0x18c080);
}

// 0x18c140
void __cdecl PartyMatchMaker::run(void)
{
    LIFT_STUB(0x18c140);
}

// 0x18c600
::PartyMatchMaker::RegisterResult __cdecl PartyMatchMaker::Register(unsigned int, ::Pc *)
{
    LIFT_STUB(0x18c600);
}
