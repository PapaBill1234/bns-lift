// rankingseason_cpp.cpp: rankingseason.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "rankingseason.h"
#include "LiftStub.h"

// 0x1b39e0
__cdecl RankingSeasonManager::RankingSeasonManager(void)
{
    LIFT_STUB(0x1b39e0);
}

// 0x1b3ac0
__cdecl RankingSeasonManager::~RankingSeasonManager(void)
{
    LIFT_STUB(0x1b3ac0);
}

// 0x1b3b90
void __cdecl RankingSeasonManager::finalize(void)
{
    LIFT_STUB(0x1b3b90);
}

// 0x1b4080
bool __cdecl RankingSeasonManager::AddSeasonInfo(bool, ::RankingSeasonInfo &)
{
    LIFT_STUB(0x1b4080);
}

// 0x1b4810
bool __cdecl RankingSeasonManager::AddScheduleInfo(bool, char, int, ::RankingSeasonResultScheduleInfo &)
{
    LIFT_STUB(0x1b4810);
}

// 0x1b5250
bool __cdecl RankingSeasonManager::CheckReward(char, int, char, __int64, bool &, bool &)
{
    LIFT_STUB(0x1b5250);
}

// 0x1b54b0
bool __cdecl RankingSeasonManager::ComposeSeasonInfoToClient(void)
{
    LIFT_STUB(0x1b54b0);
}

// 0x1b5b30
__int64 __cdecl RankingSeasonManager::GetResultExpirationTime(char, int, char)
{
    LIFT_STUB(0x1b5b30);
}

// 0x1b5c80
void __cdecl RankingSeasonManager::AddSeasonContentsSchedule(::SeasonContentsSchedule &)
{
    LIFT_STUB(0x1b5c80);
}

// 0x1b5e40
#pragma comment(linker, "/INCLUDE:?GetSeasonContentsSchedule@RankingSeasonManager@@QEAA_NDAEAUSeasonContentsSchedule@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl RankingSeasonManager::GetSeasonContentsSchedule(const char seasonContentsType, ::SeasonContentsSchedule &schedule)
{
    bool result = false;
    // LIFT: the valid range is 1..15; type 2 has no schedule (enum names are not in the PDB facts).
    if (seasonContentsType <= 0 || seasonContentsType >= 16 || seasonContentsType == 2)
        return false;

    ::AcquireSRWLockShared(&_lock);
    if (_schedule[seasonContentsType] != nullptr)
    {
        schedule = *_schedule[seasonContentsType];
        result = true;
    }
    ::ReleaseSRWLockShared(&_lock);
    return result;
}

// 0x1b5ef0
void __cdecl RankingSeasonManager::DumpSeasonContentsSchedule(void)
{
    LIFT_STUB(0x1b5ef0);
}

// 0x1b5fa0
void __cdecl RankingSeasonManager::ChangeSeasonContentsSchedule(void)
{
    LIFT_STUB(0x1b5fa0);
}

// 0x1b6da0
void __cdecl RankingSeasonManager::searchCurrentSeason(char, ::SeasonContentsSchedule &)
{
    LIFT_STUB(0x1b6da0);
}

// 0x1b7040
bool __cdecl RankingSeasonManager::DecomposeSeasonInfoFromRanking(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x1b7040);
}
