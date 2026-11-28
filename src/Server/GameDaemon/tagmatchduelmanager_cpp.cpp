// tagmatchduelmanager_cpp.cpp: tagmatchduelmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "tagmatchduelmanager.h"
#include "duelmanager.h"
#include "pc.h"
#include "zone.h"
#include "gamedaemon.h"
#include "AlertSender.h"
#include "Log.h"
#include "LiftStub.h"

// LIFT: per-exe path literal (lessons A6).
#define TAGMATCHDUELMANAGER_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\TagMatchDuelManager.cpp"

#pragma comment(linker, "/INCLUDE:?ResetRound@TagMatchDuelTeam@@UEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?resetRound@TagMatchDuelManager@@EEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?getOppositeFightMember@TagMatchDuelManager@@AEBAQEBVTagMatchDuelMember@@H@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x1d04b0
bool __cdecl TagMatchDuelMember::ReadyRound(short &)
{
    LIFT_STUB(0x1d04b0);
}

// 0x1d0560
void __cdecl TagMatchDuelMember::ResetRound(void)
{
    LIFT_STUB(0x1d0560);
}

// 0x1d05c0
void __cdecl TagMatchDuelTeam::GiveTagToken(::TagMatchDuelMember const *const)
{
    LIFT_STUB(0x1d05c0);
}

// 0x1d0670
void __cdecl TagMatchDuelTeam::SetTagTokenOwnerMember(::TagMatchDuelMember *const, wchar_t const *, int)
{
    LIFT_STUB(0x1d0670);
}

// 0x1d0800
void __cdecl TagMatchDuelTeam::Dump(wchar_t *, unsigned __int64)
{
    LIFT_STUB(0x1d0800);
}

// 0x1d0a60
void __cdecl TagMatchDuelTeam::onLeave(::DuelMember *const)
{
    LIFT_STUB(0x1d0a60);
}

// 0x1d0ae0
void __cdecl TagMatchDuelTeam::ResetRound(void)
{
    // Partial PDB offsets. DuelTeam::_teamAttackDamage +64. TagMatchDuelTeam: _fightMember +72, _tagTokenOwnerMember +80, _interferenceMember +88.
    char *self = reinterpret_cast<char *>(this);
    *reinterpret_cast<__int64 *>(self + 64) = 0;
    *reinterpret_cast<void **>(self + 72) = nullptr;
    *reinterpret_cast<void **>(self + 80) = nullptr;
    *reinterpret_cast<void **>(self + 88) = nullptr;
}

// 0x1d0b00
::DuelRoundResult const __cdecl TagMatchDuelRule::CalcRoundResult(::Zone *const)
{
    LIFT_STUB(0x1d0b00);
}

// 0x1d0cb0
bool __cdecl TagMatchDuelManager::ChooseDuelOrder(unsigned __int64, char, short &)
{
    LIFT_STUB(0x1d0cb0);
}

// 0x1d10c0
bool __cdecl TagMatchDuelManager::TakeTagToken(unsigned __int64, short &)
{
    LIFT_STUB(0x1d10c0);
}

// 0x1d14d0
bool __cdecl TagMatchDuelManager::CanChangeFighter(::Pc const *const, ::TagMatchDuelManager::FighterChangeReason) const
{
    LIFT_STUB(0x1d14d0);
}

// 0x1d15d0
bool __cdecl TagMatchDuelManager::CanChangeFighter(::TagMatchDuelMember const *const, ::TagMatchDuelManager::FighterChangeReason) const
{
    LIFT_STUB(0x1d15d0);
}

// 0x1d17c0
bool __cdecl TagMatchDuelManager::CanInterfere(::Pc const *const) const
{
    LIFT_STUB(0x1d17c0);
}

// 0x1d18a0
bool __cdecl TagMatchDuelManager::CanInterfere(::TagMatchDuelMember const *const) const
{
    LIFT_STUB(0x1d18a0);
}

// 0x1d1a40
bool __cdecl TagMatchDuelManager::CanStopInterference(::TagMatchDuelMember const *const) const
{
    LIFT_STUB(0x1d1a40);
}

// 0x1d1b50
bool __cdecl TagMatchDuelManager::ChangeFighter(::Pc const *const, ::TagMatchDuelManager::FighterChangeReason)
{
    LIFT_STUB(0x1d1b50);
}

// 0x1d2d10
bool __cdecl TagMatchDuelManager::InterfereInFight(::Pc const *const)
{
    LIFT_STUB(0x1d2d10);
}

// 0x1d3390
bool __cdecl TagMatchDuelManager::StopInterference(::Pc const *const, bool)
{
    LIFT_STUB(0x1d3390);
}

// 0x1d36d0
void __cdecl TagMatchDuelManager::OnEventTimer(void)
{
    LIFT_STUB(0x1d36d0);
}

// 0x1d3920
void __cdecl TagMatchDuelManager::handleOnDead(::DuelMember *const)
{
    LIFT_STUB(0x1d3920);
}

// 0x1d39c0
void __cdecl TagMatchDuelManager::handleOnLeave(::DuelMember *const)
{
    LIFT_STUB(0x1d39c0);
}

// 0x1d3a60
void __cdecl TagMatchDuelManager::onEliminate(::DuelMember *const, ::TagMatchDuelManager::FighterChangeReason)
{
    LIFT_STUB(0x1d3a60);
}

// 0x1d4640
::TagMatchDuelMember *const __cdecl TagMatchDuelManager::getReplacementMember(int, ::TagMatchDuelManager::FighterChangeReason)
{
    LIFT_STUB(0x1d4640);
}

// 0x1d46d0
::TagMatchDuelMember const *const __cdecl TagMatchDuelManager::getOppositeFightMember(int myTeamIndex) const
{
    // Partial PDB offsets. DuelManager::_teams[2] +40. TagMatchDuelTeam::_fightMember +72.
    if (static_cast<unsigned int>(myTeamIndex) <= 1)
    {
        const char *const *teams = reinterpret_cast<const char *const *>(reinterpret_cast<const char *>(this) + 40);
        return *reinterpret_cast< ::TagMatchDuelMember const *const *>(teams[myTeamIndex == 0] + 72);
    }
    Log::Write(Log::LT_ERROR, TAGMATCHDUELMANAGER_FILE, 995,
               L"== CRASH == [duel], TagMatchDuelManager::getOppositeFightMember; invalid parameter, myTeamIndex:%d", myTeamIndex);
    AlertSender::Write(TAGMATCHDUELMANAGER_FILE, 995,
                       L"== CRASH == [duel], TagMatchDuelManager::getOppositeFightMember; invalid parameter, myTeamIndex:%d", myTeamIndex);
    return nullptr;
}

// 0x1d4740
void __cdecl TagMatchDuelManager::readyByForce(void)
{
    LIFT_STUB(0x1d4740);
}

// 0x1d47f0
void __cdecl TagMatchDuelManager::arrangeDuelOrder(bool)
{
    LIFT_STUB(0x1d47f0);
}

// 0x1d4ce0
void __cdecl TagMatchDuelManager::startRound(void)
{
    LIFT_STUB(0x1d4ce0);
}

// 0x1d4d60
void __cdecl TagMatchDuelManager::enterToArena(void)
{
    LIFT_STUB(0x1d4d60);
}

// 0x1d4fa0
void __cdecl TagMatchDuelManager::leaveFromArena(void)
{
    LIFT_STUB(0x1d4fa0);
}

// 0x1d51b0
void __cdecl TagMatchDuelManager::rearrangeDuelMember(::DuelTeam *const)
{
    LIFT_STUB(0x1d51b0);
}

// 0x1d5570
void __cdecl TagMatchDuelManager::resetRound(void)
{
    // Partial PDB offsets. DuelManager::_lastAttackTeam +54146. TagMatchDuelManager::_interferenceBonusIndex +54448.
    char *self = reinterpret_cast<char *>(this);
    self[54146] = -1;
    *reinterpret_cast<int *>(self + 54448) = 0;
}

// 0x1d5590
bool __cdecl TagMatchDuelManager::replaceAbsentFighter(::TagMatchDuelMember *const)
{
    LIFT_STUB(0x1d5590);
}

// 0x1d5810
void __cdecl TagMatchDuelManager::prepareMoveInto(::TagMatchDuelMember *const, bool)
{
    LIFT_STUB(0x1d5810);
}

// 0x1d5b30
void __cdecl TagMatchDuelManager::prepareMoveOut(::TagMatchDuelMember *const, bool)
{
    LIFT_STUB(0x1d5b30);
}

// 0x1d5fa0
bool __cdecl TagMatchDuelManager::setInsideMoveDest(int, int, ::DuelMoveInfo &)
{
    LIFT_STUB(0x1d5fa0);
}

// 0x1d6130
bool __cdecl TagMatchDuelManager::setOutsideMoveDest(int, int, ::DuelMoveInfo &)
{
    LIFT_STUB(0x1d6130);
}

// 0x1d6350
void __cdecl TagMatchDuelManager::moveDuelMember(::Pc *const, ::DuelMoveInfo const &)
{
    LIFT_STUB(0x1d6350);
}

// 0x1d6980
void __cdecl TagMatchDuelManager::invokeFighterTimeLimitEffect(::TagMatchDuelMember *const) const
{
    LIFT_STUB(0x1d6980);
}

// 0x1d6ae0
void __cdecl TagMatchDuelManager::invokeArenaOutsideRoundStartEffect(::DuelMember *const) const
{
    LIFT_STUB(0x1d6ae0);
}

// 0x1d6d10
void __cdecl TagMatchDuelManager::invokeTagIntoEffectBySkill(::TagMatchDuelMember *const) const
{
    LIFT_STUB(0x1d6d10);
}

// 0x1d6f10
void __cdecl TagMatchDuelManager::invokeTagIntoEffectBySystem(::TagMatchDuelMember *const) const
{
    LIFT_STUB(0x1d6f10);
}

// 0x1d7110
void __cdecl TagMatchDuelManager::invokeTagOutEffect(::TagMatchDuelMember *const) const
{
    LIFT_STUB(0x1d7110);
}

// 0x1d7310
void __cdecl TagMatchDuelManager::invokeInterferenceIntoEffect(::TagMatchDuelMember *const) const
{
    LIFT_STUB(0x1d7310);
}

// 0x1d7510
void __cdecl TagMatchDuelManager::invokeInterferenceOutEffect(::TagMatchDuelMember *const) const
{
    LIFT_STUB(0x1d7510);
}

// 0x1d7710
::Data::ZonePcSpawnRecordPtr const __cdecl TagMatchDuelManager::getRoundStartPcSpawn(int, int) const
{
    LIFT_STUB(0x1d7710);
}
