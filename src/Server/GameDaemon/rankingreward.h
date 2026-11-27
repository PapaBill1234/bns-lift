// rankingreward.h: rankingreward.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

// PDB: struct RankingResultID, size 0xE (seasonContentsScheduleNumber at +9: packed).
#pragma pack(push, 1)
struct RankingResultID
{
    RankingResultID();
    RankingResultID(unsigned __int64, char, int, char);
    bool operator==(RankingResultID const &) const;
    bool operator<(RankingResultID const &) const;

    unsigned __int64 guildId;  // +0
    char seasonContentsType;  // +8
    int seasonContentsScheduleNumber;  // +9
    char seasonContentsResultScheduleNumber;  // +13
};
#pragma pack(pop)

class RankingResult
{
public:
    enum ResultState
    {
        RESULT_STATE_NONE = 0,
        RESULT_STATE_RECV_TO_RANKING = 1,
        RESULT_STATE_RECV_TO_CACHE = 2,
        RESULT_STATE_TAKEN_REWARD = 3,
        RESULT_STATE_MAX = 4,
    };
    typedef std::map<RankingResultID, ::RankingResultInfo *, std::less<RankingResultID>,
                     StlAllocator<std::pair<RankingResultID const, ::RankingResultInfo *>, 2> > RankingResultList;
    typedef std::map<__int64, __int64, std::less<__int64>, StlAllocator<std::pair<__int64 const, __int64>, 2> > ResultInfoList;

public:
    __cdecl RankingResult(void);  // 0x1b2230
    __cdecl ~RankingResult(void);  // 0x1b2300
    void __cdecl DecomposeRankingResult(::FragmentPacketConcatenater *&);  // 0x1b2510
    void __cdecl DecomposeRankingRewardList(::FragmentPacketConcatenater *&);  // 0x1b2a60
    void __cdecl VerifyRankingResults(void);  // 0x1b2dc0
    void __cdecl TakeRewardGuildBuff(void);  // 0x1b3200
    bool __cdecl TakeRewardReq(int);  // 0x1b33c0

private:
    SRWLOCK lock;  // +0
    RankingResultList list;  // +8
    ResultInfoList resultInfoList;  // +40
    ResultState state;  // +72
    char resultSeasonCount;  // +76
};
