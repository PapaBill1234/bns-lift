// datamanager_h.cpp: datamanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "datamanager.h"
#include "LiftStub.h"

// 0x1eddc0
::Data::RandomStoreDrawRewardRecordPtr const __cdecl Data::DataManager::GetNextRandomStoreDrawReward(char, int)
{
    LIFT_STUB(0x1eddc0);
}

// 0x34ef90
bool __cdecl Data::DataManager::CheckJumpingCharacterTicketItemDataId(unsigned int)
{
    LIFT_STUB(0x34ef90);
}

// 0x453bc0
bool __cdecl Data::AdditionalServiceItems::Add(::Data::AdditionalServiceItems::AdditionalServiceItemType, wchar_t const *)
{
    LIFT_STUB(0x453bc0);
}

// 0x453e30
::std::map<unsigned short, ::Data::AcquireSkillByQuestMission *, ::std::less<unsigned short>, ::StlAllocator< ::std::pair<unsigned short, ::Data::AcquireSkillByQuestMission *>, 2> > const __cdecl Data::DataManager::GetSkillByQuestMissionList(void)
{
    LIFT_STUB(0x453e30);
}

// 0x453e60
char __cdecl Data::DataManager::IsRankingPvEStageStartInfo(short, unsigned __int64)
{
    LIFT_STUB(0x453e60);
}
