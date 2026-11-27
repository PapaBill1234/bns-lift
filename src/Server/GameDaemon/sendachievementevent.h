// sendachievementevent.h: sendachievementevent.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class SendAchievementEvent
{
public:
    static void __cdecl DuelResult(__int64, __int64, __int64, char, char, char, char);  // 0xa37c0
    static void __cdecl DuelBotChallengeAttractionResult(__int64, __int64, __int64, int);  // 0xa3880
    static void __cdecl DetachPostAttachment(__int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, int, int, int, int, int, int, int, int, int, int, char, __int64, __int64);  // 0x180ef0
    static void __cdecl PartyBattleResult(__int64, __int64, __int64, char, char, char);  // 0x1810d0
    static void __cdecl SkillTraningSubjectComplete(__int64, __int64, __int64, int);  // 0x181190
    static void __cdecl LeadTheBallGoalIn(__int64, __int64, __int64, short);  // 0x181220
    static void __cdecl CompleteTakeReward(__int64, __int64, __int64, __int64, short, short, short);  // 0x1812b0
    static void __cdecl UseGrocery(__int64, __int64, __int64, __int64);  // 0x260590
    static void __cdecl ExpandInventory(__int64, __int64, __int64, char, char, char);  // 0x260620
    static void __cdecl GetFieldPlayPoint(__int64, __int64, __int64, int, int, int);  // 0x2606e0
    static void __cdecl GetFactionScore(__int64, __int64, __int64, int, int);  // 0x260790
    static void __cdecl PcLogin(__int64, __int64, __int64, short, short, short, char, char, char, char, char, char, char, char, __int64, char, char, char, char, char, wchar_t const *);  // 0x260830
    static void __cdecl DebugCommandAddRegister(__int64, __int64, __int64, short, __int64);  // 0x260a40
    static void __cdecl DebugCommandSetRegister(__int64, __int64, __int64, short, __int64);  // 0x260af0
    static void __cdecl DebugCommandDeleteAchievement(__int64, __int64, __int64, short);  // 0x260ba0
    static void __cdecl DebugCommandDeleteAll(__int64, __int64, __int64, short);  // 0x260c40
    static void __cdecl KillBossNpc(__int64, __int64, __int64, __int64, __int64, __int64, char, char, char, __int64, char, char, __int64, char, char, __int64, char, char, __int64, char, char, __int64, char, char, __int64, char, char, __int64);  // 0x3512c0
    static void __cdecl KillNpc(__int64, __int64, __int64, __int64);  // 0x351540
    static void __cdecl GetContributionScore(__int64, __int64, __int64, __int64, __int64);  // 0x3515d0
    static void __cdecl KillPc(__int64, __int64, __int64, char, char, __int64, __int64, char, char, char, char, char, int);  // 0x46d990
    static void __cdecl EquipItem(__int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64);  // 0x46dac0
    static void __cdecl QuestAcquire(__int64, __int64, __int64, short);  // 0x46dd90
    static void __cdecl QuestProgress(__int64, __int64, __int64, short, short);  // 0x46de30
    static void __cdecl QuestComplete(__int64, __int64, __int64, short);  // 0x46dee0
    static void __cdecl QuestDispose(__int64, __int64, __int64, short);  // 0x46df80
    static void __cdecl UseSkillToNpc(__int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, char, char);  // 0x46e020
    static void __cdecl DefendNpcSkill(__int64, __int64, __int64, __int64, __int64, char, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64);  // 0x46e110
    static void __cdecl PcLevelUp(__int64, __int64, __int64, char, char, short, short);  // 0x46e270
    static void __cdecl PcExhaustion(__int64, __int64, __int64, char);  // 0x46e330
    static void __cdecl PcDead(__int64, __int64, __int64, char, char);  // 0x46e3c0
    static void __cdecl ExchangeFactionScore(__int64, __int64, __int64, __int64, int, int, int, int, int);  // 0x46e470
    static void __cdecl Teleport(__int64, __int64, __int64, __int64);  // 0x46e550
    static void __cdecl ManipulateEnv2(__int64, __int64, __int64, __int64, char);  // 0x46e5e0
    static void __cdecl HelpRestoration(__int64, __int64, __int64, __int64, int);  // 0x46e680
    static void __cdecl HelpResurrect(__int64, __int64, __int64, __int64, int);  // 0x46e720
    static void __cdecl GiveFactionScoreToRefiner(__int64, __int64, __int64, __int64, __int64);  // 0x46e7c0
    static void __cdecl TakeCraft(__int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, int, int, int, int, int, char);  // 0x46e860
    static void __cdecl AcquireFish(__int64, __int64, __int64, __int64, int, short);  // 0x46e980
    static void __cdecl GrowthItem(__int64, __int64, __int64, __int64, __int64, __int64, __int64, int, __int64);  // 0x46ea30
    static void __cdecl AwakeningItem(__int64, __int64, __int64, __int64, __int64, __int64, __int64, char, __int64);  // 0x46eb10
    static void __cdecl AttachEquipGemPiece(__int64, __int64, __int64, __int64, __int64, char, short, short);  // 0x46ebf0
    static void __cdecl DecomposeItem(__int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, short, short, short, short, short, short, short, short, short, short, __int64);  // 0x46ecc0
    static void __cdecl AttachGemToWeapon(__int64, __int64, __int64, __int64, __int64);  // 0x46eed0
    static void __cdecl TransformItem(__int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, __int64, short, short, short, short, short, short, short, short, short, short, __int64, char);  // 0x46ef70
    static void __cdecl ZeroDurability(__int64, __int64, __int64, __int64);  // 0x46f1a0
    static void __cdecl RepairItem(__int64, __int64, __int64, __int64, short, short);  // 0x46f230
    static void __cdecl DisposeItemBuyPrice(__int64, __int64, __int64, __int64, short);  // 0x46f2e0
    static void __cdecl PcLogout(__int64, __int64, __int64, short, wchar_t const *);  // 0x46f380
};

