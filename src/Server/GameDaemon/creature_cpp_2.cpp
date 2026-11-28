// creature_cpp_2.cpp: creature.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "creature.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetActivatedBadgeEquipSlot@Creature@@QEAADXZ")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: view of Creature (PDB: Prop at +0x30, CreatureProperty::State at +0xD8, __state__::activated_badge_page at +0x270).
struct CreatureBadgeView
{
    char lift_pad_0[0x30 + 0xD8 + 0x270];
    char activated_badge_page;  // +0x378 (Prop.State.activated_badge_page)
};

// LIFT: badge equip slot values (pseudocode). ❓ PDB enumerator names.
const char BADGE_EQUIP_SLOT_NONE = 0;
const char BADGE_EQUIP_SLOT_PAGE1 = 10;
const char BADGE_EQUIP_SLOT_PAGE2 = 11;
const char BADGE_EQUIP_SLOT_PAGE3 = 12;
}

// 0x26d4f0
bool __cdecl Creature::HandleDebugFlag(unsigned short, ::f_flag8::Operation, ::ChangedProperty *)
{
    LIFT_STUB(0x26d4f0);
}

// 0x26d640
bool __cdecl Creature::HandleTarget(__int64, ::ChangedProperty *)
{
    LIFT_STUB(0x26d640);
}

// 0x26d810
bool __cdecl Creature::HandleEquipment(unsigned short, int, ::ChangedProperty *)
{
    LIFT_STUB(0x26d810);
}

// 0x26d970
bool __cdecl Creature::HandleEquipmentBodyGuildId(unsigned __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x26d970);
}

// 0x26da50
bool __cdecl Creature::handleEquipmentCustom(unsigned short, char, char *const, char, ::ChangedProperty *)
{
    LIFT_STUB(0x26da50);
}

// 0x26dbc0
bool __cdecl Creature::HandleInventorySize(char, char, ::ChangedProperty *)
{
    LIFT_STUB(0x26dbc0);
}

// 0x26dd10
bool __cdecl Creature::CheckToJoinFaction(char)
{
    LIFT_STUB(0x26dd10);
}

// 0x26ddd0
bool __cdecl Creature::HandleJoinFaction(char, ::ChangedProperty *)
{
    LIFT_STUB(0x26ddd0);
}

// 0x26e2d0
bool __cdecl Creature::HandleTransferFaction(char, ::ChangedProperty *, char)
{
    LIFT_STUB(0x26e2d0);
}

// 0x26e550
bool __cdecl Creature::HandleLeaveFaction(::ChangedProperty *)
{
    LIFT_STUB(0x26e550);
}

// 0x26e740
bool __cdecl Creature::HandleFactionReputation(int, ::ChangedProperty *, short)
{
    LIFT_STUB(0x26e740);
}

// 0x26ebe0
bool __cdecl Creature::HandleFactionScore(int, ::ChangedProperty *const)
{
    LIFT_STUB(0x26ebe0);
}

// 0x26ee40
bool __cdecl Creature::HandleFactionScoreNpc(int, int, ::ChangedProperty *)
{
    LIFT_STUB(0x26ee40);
}

// 0x26ef50
bool __cdecl Creature::HandleActivatedFaction(char, ::ChangedProperty *, bool, unsigned short)
{
    LIFT_STUB(0x26ef50);
}

// 0x26f020
bool __cdecl Creature::CheckToJoinFaction2(char)
{
    LIFT_STUB(0x26f020);
}

// 0x26f0e0
bool __cdecl Creature::HandleJoinFaction2(char, ::ChangedProperty *)
{
    LIFT_STUB(0x26f0e0);
}

// 0x26f5b0
bool __cdecl Creature::CheckToTransferFaction2(char)
{
    LIFT_STUB(0x26f5b0);
}

// 0x26f6a0
bool __cdecl Creature::HandleTransferFaction2(char, ::ChangedProperty *)
{
    LIFT_STUB(0x26f6a0);
}

// 0x26f880
bool __cdecl Creature::HandleLeaveFaction2(::ChangedProperty *)
{
    LIFT_STUB(0x26f880);
}

// 0x26fad0
bool __cdecl Creature::IsJoinedFaction(unsigned __int64)
{
    LIFT_STUB(0x26fad0);
}

// 0x26fb80
bool __cdecl Creature::increaseEffectAttrCount(bool, ::Data::EffectAttributeType)
{
    LIFT_STUB(0x26fb80);
}

// 0x26fc40
bool __cdecl Creature::decreaseEffectAttrCount(bool, ::Data::EffectAttributeType)
{
    LIFT_STUB(0x26fc40);
}

// 0x26fd10
bool __cdecl Creature::decreaseEffectAttrCount2(int, bool, ::Data::EffectAttributeType)
{
    LIFT_STUB(0x26fd10);
}

// 0x26fdc0
bool __cdecl Creature::AttachEffectAttr(bool, short *, short, unsigned __int64, unsigned __int64, unsigned __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x26fdc0);
}

// 0x26ffe0
bool __cdecl Creature::DetachEffectAttr(int, bool, short *, short, unsigned __int64, unsigned __int64, unsigned __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x26ffe0);
}

// 0x270330
bool __cdecl Creature::HandleEffectAttribute(unsigned __int64, unsigned __int64, unsigned __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x270330);
}

// 0x2704a0
bool __cdecl Creature::HandleStyleScore(short, ::ChangedProperty *)
{
    LIFT_STUB(0x2704a0);
}

// 0x270550
bool __cdecl Creature::HandleImmuneEffectAttribute(unsigned __int64, unsigned __int64, unsigned __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x270550);
}

// 0x2706c0
bool __cdecl Creature::HandleImmuneBreakerAttribute(short, short, ::ChangedProperty *)
{
    LIFT_STUB(0x2706c0);
}

// 0x2707e0
bool __cdecl Creature::HandleEffectFlag(short, bool, ::ChangedProperty *)
{
    LIFT_STUB(0x2707e0);
}

// 0x270cc0
bool __cdecl Creature::HandleFieldItem(unsigned __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x270cc0);
}

// 0x270dc0
bool __cdecl Creature::HandleSummoned(unsigned __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x270dc0);
}

// 0x270ed0
bool __cdecl Creature::HandleAchievementTitle(short, short, ::ChangedProperty *)
{
    LIFT_STUB(0x270ed0);
}

// 0x271070
bool __cdecl Creature::HandleAchievementAbility(short, short, ::ChangedProperty *)
{
    LIFT_STUB(0x271070);
}

// 0x271210
int const __cdecl Creature::GetMaxFactionScore(void) const
{
    LIFT_STUB(0x271210);
}

// 0x2712e0
bool __cdecl Creature::CheckToLockMasteryLevel(void)
{
    LIFT_STUB(0x2712e0);
}

// 0x271330
void __cdecl Creature::validateLevel(int, ::ChangedProperty *, bool)
{
    LIFT_STUB(0x271330);
}

// 0x271650
void __cdecl Creature::validateMasteryLevel(__int64, ::ChangedProperty *, bool)
{
    LIFT_STUB(0x271650);
}

// 0x2718a0
bool __cdecl Creature::HandleConvoy(char, bool, ::ChangedProperty *)
{
    LIFT_STUB(0x2718a0);
}

// 0x271990
bool __cdecl Creature::HandleSurvey(char, ::SurveyResult, ::ChangedProperty *)
{
    LIFT_STUB(0x271990);
}

// 0x271b40
bool __cdecl Creature::HandleGMMode(char, ::ChangedProperty *)
{
    LIFT_STUB(0x271b40);
}

// 0x271c10
bool __cdecl Creature::HandleGuildId(__int64, ::ChangedProperty *)
{
    LIFT_STUB(0x271c10);
}

// 0x271dc0
bool __cdecl Creature::HandleGradeLevel(char, ::ChangedProperty *)
{
    LIFT_STUB(0x271dc0);
}

// 0x271ec0
bool __cdecl Creature::HandleBindRaidDungeon(unsigned __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x271ec0);
}

// 0x272080
bool __cdecl Creature::HandlePvPSafeArea(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x272080);
}

// 0x272160
bool __cdecl Creature::HandlePvPMode(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x272160);
}

// 0x272240
bool __cdecl Creature::HandlePvPModeCoolTime(__int64, ::ChangedProperty *)
{
    LIFT_STUB(0x272240);
}

// 0x272360
bool __cdecl Creature::HandleUnbindRaidDungeon(unsigned __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x272360);
}

// 0x272520
bool __cdecl Creature::HandleVitality(unsigned short, int, ::ChangedProperty *)
{
    LIFT_STUB(0x272520);
}

// 0x2727c0
bool __cdecl Creature::HandleTopContributionGroupId(__int64, ::ChangedProperty *)
{
    LIFT_STUB(0x2727c0);
}

// 0x272870
bool __cdecl Creature::HandleSkillSkinId(short, ::ChangedProperty *)
{
    LIFT_STUB(0x272870);
}

// 0x272b40
bool __cdecl Creature::HandleGuildInvitationRefusal(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x272b40);
}

// 0x272c50
bool __cdecl Creature::HandleGhostType(char, ::ChangedProperty *)
{
    LIFT_STUB(0x272c50);
}

// 0x272d90
bool __cdecl Creature::AddDamageValue(__int64)
{
    LIFT_STUB(0x272d90);
}

// 0x272f60
bool __cdecl Creature::AddDamagedValue(unsigned __int64, __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x272f60);
}

// 0x273070
bool __cdecl Creature::HandleAccumulatedDamage(::Data::EffectAccumulateDamageSlotType, __int64, __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x273070);
}

// 0x273180
char __cdecl Creature::GetSurveyState(char)
{
    LIFT_STUB(0x273180);
}

// 0x273290
bool __cdecl Creature::HandleFactionKilledCount(char, ::ChangedProperty *)
{
    LIFT_STUB(0x273290);
}

// 0x2733a0
bool __cdecl Creature::HandleCombatSide(char, ::ChangedProperty *)
{
    LIFT_STUB(0x2733a0);
}

// 0x2735d0
bool __cdecl Creature::HandleDuelGrade(::ChangedProperty *)
{
    LIFT_STUB(0x2735d0);
}

// 0x273830
bool __cdecl Creature::HandleDuelPoint(int, ::ChangedProperty *)
{
    LIFT_STUB(0x273830);
}

// 0x2738f0
bool __cdecl Creature::HandlePartyBattlePoint(int, ::ChangedProperty *)
{
    LIFT_STUB(0x2738f0);
}

// 0x2739b0
bool __cdecl Creature::HandleFieldPlayPoint(int, ::ChangedProperty *, short, int, int, int)
{
    LIFT_STUB(0x2739b0);
}

// 0x273d30
bool __cdecl Creature::HandleUsableSkillBuildUpPoint(short, ::ChangedProperty *, short, __int64, __int64, __int64, wchar_t *)
{
    LIFT_STUB(0x273d30);
}

// 0x274180
short __cdecl Creature::InitUsableSkillBuildUpPoint(::ChangedProperty *)
{
    LIFT_STUB(0x274180);
}

// 0x274380
bool __cdecl Creature::handleAcquiredSkillBuildUpPoint(short, ::ChangedProperty *, short)
{
    LIFT_STUB(0x274380);
}

// 0x2744e0
bool __cdecl Creature::HandleInstantHeartCount(char, ::ChangedProperty *)
{
    LIFT_STUB(0x2744e0);
}

// 0x274600
bool __cdecl Creature::HandleHeartCount(char, ::ChangedProperty *)
{
    LIFT_STUB(0x274600);
}

// 0x2746f0
bool __cdecl Creature::HandleActivatedBadgePage(char, ::ChangedProperty *)
{
    LIFT_STUB(0x2746f0);
}

// 0x2749f0
char __cdecl Creature::GetActivatedBadgeEquipSlot(void)
{
    switch (reinterpret_cast<CreatureBadgeView const *>(this)->activated_badge_page)
    {
    case 1:
        return BADGE_EQUIP_SLOT_PAGE1;
    case 2:
        return BADGE_EQUIP_SLOT_PAGE2;
    case 3:
        return BADGE_EQUIP_SLOT_PAGE3;
    default:
        return BADGE_EQUIP_SLOT_NONE;
    }
}

// 0x274a10
bool __cdecl Creature::IsActivatedBadgeEquipSlot(unsigned char)
{
    LIFT_STUB(0x274a10);
}

// 0x274a60
bool __cdecl Creature::HandleEquipBadgeGearScore(int, ::ChangedProperty *)
{
    LIFT_STUB(0x274a60);
}

// 0x274c20
bool __cdecl Creature::FetchChangedProperty(short &, short &, char *, short &, short &, char *, short &, short &, char *, short &, short &, char *)
{
    LIFT_STUB(0x274c20);
}

// 0x275020
void __cdecl Creature::Regeneration(::ChangedProperty &)
{
    LIFT_STUB(0x275020);
}

// 0x275160
bool __cdecl Creature::InitAccountExp(::AccountExpInfo const &)
{
    LIFT_STUB(0x275160);
}

// 0x275320
bool __cdecl Creature::HandleAccountExpToAdd(__int64, ::ChangedProperty *, short)
{
    LIFT_STUB(0x275320);
}

// 0x275760
void __cdecl Creature::validateAccountLevel(__int64, ::ChangedProperty *, bool, short)
{
    LIFT_STUB(0x275760);
}

// 0x275a10
bool __cdecl Creature::HandleAccountExpQuota(int, __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x275a10);
}

// 0x275c20
bool __cdecl Creature::HandleAccountExpForApplyToLobby(__int64, ::ChangedProperty *, bool &)
{
    LIFT_STUB(0x275c20);
}

// 0x275ff0
bool __cdecl Creature::HandleAccountExpAddedForRecover(::ChangedProperty *)
{
    LIFT_STUB(0x275ff0);
}

// 0x276400
bool __cdecl Creature::checkAccountExpQuota(__int64 &)
{
    LIFT_STUB(0x276400);
}

// 0x2764f0
bool __cdecl Creature::HandleAccountExpWithoutConsumeQuota(__int64, ::ChangedProperty *, short)
{
    LIFT_STUB(0x2764f0);
}

// 0x276930
bool __cdecl ChangedProperty::AddProperty(::Creature *, unsigned short)
{
    LIFT_STUB(0x276930);
}

// 0x276b10
bool __cdecl ChangedProperty::AddExtraProperty(::Creature *, unsigned short)
{
    LIFT_STUB(0x276b10);
}

// 0x276ca0
void __cdecl CreatureStateKeeper::ReplaceCreatureState(void)
{
    LIFT_STUB(0x276ca0);
}
