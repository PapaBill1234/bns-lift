// rankingreward.h: rankingreward.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class RankingResult
{
public:
    __cdecl RankingResult(void);  // 0x1b2230
    __cdecl ~RankingResult(void);  // 0x1b2300
    void __cdecl DecomposeRankingResult(::FragmentPacketConcatenater *&);  // 0x1b2510
    void __cdecl DecomposeRankingRewardList(::FragmentPacketConcatenater *&);  // 0x1b2a60
    void __cdecl VerifyRankingResults(void);  // 0x1b2dc0
    void __cdecl TakeRewardGuildBuff(void);  // 0x1b3200
    bool __cdecl TakeRewardReq(int);  // 0x1b33c0
};

