// guildbattlefieldmanager.h: guildbattlefieldmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GuildBattleFieldManager
{
public:
    struct GateInfoList {};
    struct ZoneOpenCloseInfo {};
public:
    bool __cdecl Initialize(::Zone *, __int64);  // 0x111bf0
    bool __cdecl GetNearRespawnArea(::Pc *, unsigned int &, unsigned __int64 &);  // 0x111cc0
    bool __cdecl CheckAvailableAirDash(::Env *, ::Pc *);  // 0x112030
    void __cdecl OnRevived(::Pc *);  // 0x112270
    void __cdecl OnActivated(::Pc *);  // 0x112310
    void __cdecl OnDeactivated(::Pc *);  // 0x112430
private:
    bool __cdecl checkAllOccupiedRefiner(unsigned __int64 &);  // 0x112520
    bool __cdecl invokeOccupiedEffect(unsigned __int64);  // 0x112670
    void __cdecl setEffectRegionEnable(bool);  // 0x1128d0
public:
    void __cdecl CheckZoneClosed(void);  // 0x112970
    static bool __cdecl CheckZoneAvailableTime(unsigned __int64);  // 0x112a50
    static bool __cdecl GetTodayOpenCloseTime(::Data::GuildBattleFieldZoneRecordPtr, __int64, __int64 &, __int64 &);  // 0x112b00
    static bool __cdecl GetTodayZoneOpenCloseInfo(::Data::GuildBattleFieldZoneRecordPtr, ::tm const &, ::GuildBattleFieldManager::ZoneOpenCloseInfo &);  // 0x112c60
    static bool __cdecl GetTodayGateInfo(::Data::GuildBattleFieldZoneRecordPtr, ::tm const &, ::GuildBattleFieldManager::GateInfoList &);  // 0x112e10
    static bool __cdecl IsGateOpenReadyTime(::Data::GuildBattleFieldZoneRecordPtr const &, __int64);  // 0x112f70
    static bool __cdecl IsGateOpenTime(::Data::GuildBattleFieldZoneRecordPtr, __int64, __int64 &);  // 0x1131a0
};

