// achievementdata.cpp: achievementdata.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "achievementdata.h"
#include "pc.h"
#include "LiftStub.h"

// 0x34780
void __cdecl AchievementData::MakeNewbieCareCompletePacket(void)
{
    LIFT_STUB(0x34780);
}

// 0x34aa0
void __cdecl AchievementData::SendNewbieCareCompleteRegister(::Pc *)
{
    // LIFT: Not done. The skeleton has no Packet class (inline ctor, Copy, Clear), no static _newbieCareCompletePacket and no virtual Pc::Send(Packet const *).
    LIFT_STUB(0x34aa0);
}

// 0x34b20
__cdecl AchievementData::~AchievementData(void)
{
    LIFT_STUB(0x34b20);
}

// 0x34be0
bool __cdecl AchievementData::Init(__int64, ::Pc *, ::FragmentPacketConcatenater &)
{
    LIFT_STUB(0x34be0);
}

// 0x35130
bool __cdecl AchievementData::IsCompleted(short, short, char) const
{
    LIFT_STUB(0x35130);
}

// 0x35210
bool __cdecl AchievementData::CompleteReward(::Data::AchievementRecord const *, char)
{
    LIFT_STUB(0x35210);
}

// 0x35330
short __cdecl AchievementData::AvailableTakeReward(::Data::AchievementRecord const *, char)
{
    LIFT_STUB(0x35330);
}

// 0x354e0
void __cdecl AchievementData::Update(char, ::AchievementData const &)
{
    LIFT_STUB(0x354e0);
}

// 0x35900
bool __cdecl AchievementData::Send(::Pc &, char)
{
    LIFT_STUB(0x35900);
}
