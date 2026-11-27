// rankingseason.h: rankingseason.cpp, rankingseason.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

struct RankingSeasonInfo
{
public:
    void __cdecl CopySeasonInfo(::RankingSeasonInfo &);  // 0x180910
    __cdecl ~RankingSeasonInfo(void);  // 0x1b4030

    // LIFT: card lift-gamedaemon-e12 adds the PDB data members (size 0xE0).
    char seasonContentsType;                    // +0x00
    int seasonContentsScheduleNumber;           // +0x04
    wchar_t seasonContentsSeasonName[71];       // +0x08
    char seasonType;                            // +0x96
    short playerType;                           // +0x98
    long long startTime;                        // +0xA0
    long long endTime;                          // +0xA8
    long long resultExpirationTime;             // +0xB0
    short rewardGroupId;                        // +0xB8
    int defaultRatingScore;                     // +0xBC
    std::vector<RankingSeasonResultScheduleInfo*, StlAllocator<RankingSeasonResultScheduleInfo*, 2> > resultScheduleList;  // +0xC0
};
static_assert(sizeof(RankingSeasonInfo) == 0xE0, "sizeof RankingSeasonInfo");

class RankingSeasonManager
{
private:
    bool __cdecl isClosedSeason(char);  // 0x1809b0
public:
    __cdecl RankingSeasonManager(void);  // 0x1b39e0
    virtual __cdecl ~RankingSeasonManager(void);  // 0x1b3ac0
private:
    void __cdecl finalize(void);  // 0x1b3b90
public:
    bool __cdecl AddSeasonInfo(bool, ::RankingSeasonInfo &);  // 0x1b4080
    bool __cdecl AddScheduleInfo(bool, char, int, ::RankingSeasonResultScheduleInfo &);  // 0x1b4810
    bool __cdecl CheckReward(char, int, char, __int64, bool &, bool &);  // 0x1b5250
    bool __cdecl ComposeSeasonInfoToClient(void);  // 0x1b54b0
    __int64 __cdecl GetResultExpirationTime(char, int, char);  // 0x1b5b30
    void __cdecl AddSeasonContentsSchedule(::SeasonContentsSchedule &);  // 0x1b5c80
    bool __cdecl GetSeasonContentsSchedule(char, ::SeasonContentsSchedule &);  // 0x1b5e40
    void __cdecl DumpSeasonContentsSchedule(void);  // 0x1b5ef0
    void __cdecl ChangeSeasonContentsSchedule(void);  // 0x1b5fa0
private:
    void __cdecl searchCurrentSeason(char, ::SeasonContentsSchedule &);  // 0x1b6da0
public:
    bool __cdecl DecomposeSeasonInfoFromRanking(::FragmentPacketConcatenater *);  // 0x1b7040
};

