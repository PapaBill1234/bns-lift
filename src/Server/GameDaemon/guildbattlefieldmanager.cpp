// guildbattlefieldmanager.cpp: guildbattlefieldmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "guildbattlefieldmanager.h"
#include "envobj.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x111bf0
bool __cdecl GuildBattleFieldManager::Initialize(::Zone *, __int64)
{
    LIFT_STUB(0x111bf0);
}

// 0x111cc0
bool __cdecl GuildBattleFieldManager::GetNearRespawnArea(::Pc *, unsigned int &, unsigned __int64 &)
{
    LIFT_STUB(0x111cc0);
}

// 0x112030
bool __cdecl GuildBattleFieldManager::CheckAvailableAirDash(::Env *, ::Pc *)
{
    LIFT_STUB(0x112030);
}

// 0x112270
void __cdecl GuildBattleFieldManager::OnRevived(::Pc *)
{
    LIFT_STUB(0x112270);
}

// 0x112310
void __cdecl GuildBattleFieldManager::OnActivated(::Pc *)
{
}

// 0x112430
void __cdecl GuildBattleFieldManager::OnDeactivated(::Pc *)
{
    LIFT_STUB(0x112430);
}

// 0x112520
bool __cdecl GuildBattleFieldManager::checkAllOccupiedRefiner(unsigned __int64 &)
{
    LIFT_STUB(0x112520);
}

// 0x112670
bool __cdecl GuildBattleFieldManager::invokeOccupiedEffect(unsigned __int64)
{
    LIFT_STUB(0x112670);
}

// 0x1128d0
void __cdecl GuildBattleFieldManager::setEffectRegionEnable(bool)
{
    LIFT_STUB(0x1128d0);
}

// 0x112970
void __cdecl GuildBattleFieldManager::CheckZoneClosed(void)
{
    LIFT_STUB(0x112970);
}

// 0x112a50
bool __cdecl GuildBattleFieldManager::CheckZoneAvailableTime(unsigned __int64)
{
    LIFT_STUB(0x112a50);
}

// 0x112b00
bool __cdecl GuildBattleFieldManager::GetTodayOpenCloseTime(::Data::GuildBattleFieldZoneRecordPtr, __int64, __int64 &, __int64 &)
{
    LIFT_STUB(0x112b00);
}

// 0x112c60
bool __cdecl GuildBattleFieldManager::GetTodayZoneOpenCloseInfo(::Data::GuildBattleFieldZoneRecordPtr, ::tm const &, ::GuildBattleFieldManager::ZoneOpenCloseInfo &)
{
    LIFT_STUB(0x112c60);
}

// 0x112e10
bool __cdecl GuildBattleFieldManager::GetTodayGateInfo(::Data::GuildBattleFieldZoneRecordPtr, ::tm const &, ::GuildBattleFieldManager::GateInfoList &)
{
    LIFT_STUB(0x112e10);
}

// 0x112f70
bool __cdecl GuildBattleFieldManager::IsGateOpenReadyTime(::Data::GuildBattleFieldZoneRecordPtr const &, __int64)
{
    LIFT_STUB(0x112f70);
}

// 0x1131a0
bool __cdecl GuildBattleFieldManager::IsGateOpenTime(::Data::GuildBattleFieldZoneRecordPtr, __int64, __int64 &)
{
    LIFT_STUB(0x1131a0);
}
