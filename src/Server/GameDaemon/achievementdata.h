// achievementdata.h: achievementdata.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class AchievementData
{
public:
    static void __cdecl MakeNewbieCareCompletePacket(void);  // 0x34780
    static void __cdecl SendNewbieCareCompleteRegister(::Pc *);  // 0x34aa0
    __cdecl ~AchievementData(void);  // 0x34b20
    bool __cdecl Init(__int64, ::Pc *, ::FragmentPacketConcatenater &);  // 0x34be0
    bool __cdecl IsCompleted(short, short, char) const;  // 0x35130
    bool __cdecl CompleteReward(::Data::AchievementRecord const *, char);  // 0x35210
    short __cdecl AvailableTakeReward(::Data::AchievementRecord const *, char);  // 0x35330
    void __cdecl Update(char, ::AchievementData const &);  // 0x354e0
    bool __cdecl Send(::Pc &, char);  // 0x35900
};

