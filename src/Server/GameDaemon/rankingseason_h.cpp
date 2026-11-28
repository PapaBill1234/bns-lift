// rankingseason_h.cpp: rankingseason.h (GameDaemon PDB, 2019 + PDB).
#include "rankingseason.h"
#include "LiftStub.h"
#include <wchar.h>

namespace
{
// LIFT: view of the PDB class RankingSeasonManager (size 0x98, base DynamicRefCntObj at +0). The skeleton class has no members yet.
struct RankingSeasonManagerView
{
    char lift_pad_0[0x88];
    ::_RTL_SRWLOCK _closedSeasonBitFlagLock;  // +136 (0x88)
    long long _closedSeasonBitFlag;           // +144 (0x90)
};
}

// 0x180910
#pragma comment(linker, "/INCLUDE:?CopySeasonInfo@RankingSeasonInfo@@QEAAXAEAU1@@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl RankingSeasonInfo::CopySeasonInfo(::RankingSeasonInfo & rsi)
{
    seasonContentsType = rsi.seasonContentsType;
    seasonContentsScheduleNumber = rsi.seasonContentsScheduleNumber;
    wcsncpy(seasonContentsSeasonName, rsi.seasonContentsSeasonName, 71);
    seasonType = rsi.seasonType;
    playerType = rsi.playerType;
    startTime = rsi.startTime;
    endTime = rsi.endTime;
    resultExpirationTime = rsi.resultExpirationTime;
    rewardGroupId = rsi.rewardGroupId;
    defaultRatingScore = rsi.defaultRatingScore;
}

// 0x1809b0
#pragma comment(linker, "/INCLUDE:?isClosedSeason@RankingSeasonManager@@AEAA_ND@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl RankingSeasonManager::isClosedSeason(char seasonContentsType)
{
    RankingSeasonManagerView *self = reinterpret_cast<RankingSeasonManagerView *>(this);
    // LIFT: valid season contents types are 1..15. ❓ PDB enumerator names of the range ends and of the value 2.
    if (seasonContentsType < 1 || seasonContentsType > 15 || seasonContentsType == 2)
        return false;
    AcquireSRWLockShared(&self->_closedSeasonBitFlagLock);
    bool closed = (self->_closedSeasonBitFlag & (1LL << (seasonContentsType - 1))) != 0;
    ReleaseSRWLockShared(&self->_closedSeasonBitFlagLock);
    return closed;
}
