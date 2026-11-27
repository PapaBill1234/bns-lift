// filter_gd.h: filter.cpp, filter.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ActiveFactionFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277a20
};

class CompareObjectIdFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277eb0
};

class DeactivatedFactionFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277af0
};

class EffectAttributeFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277d60
};

class EffectFlagFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277870
};

class EnvFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278c10
};

class EnvHpPercenctFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278f50
};

class EnvIdFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278c80
};

class EnvPreStateFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278e50
};

class EnvStateFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278d50
};

class EventBroadcastedFilter
{
private:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278bf0
};

class FactionFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277960
};

class FactionLevelFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277c80
};

class FactionReputationFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277bb0
};

class FieldItemFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278480
};

class FilterFactory
{
private:
    void __cdecl clear(void);  // 0x2796e0
public:
    bool __cdecl Initialize(void);  // 0x279760
    ::Filter * __cdecl CreateFilter(short) const;  // 0x27a150
};

class FilterRecordEffectStackCountFilter
{
public:
    virtual bool __cdecl Check1(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x279360
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x2794b0
};

class InventoryFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x2783c0
};

class JobStyleFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x2771f0
};

class LinkLaserTerminateReasonFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x2792f0
};

class NotNpcFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x2785b0
};

class NotSummonedFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x279270
};

class NpcBrainFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278b30
};

class NpcCombatFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x2786d0
};

class NpcConvoyFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278a70
};

class NpcFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278540
};

class NpcIdFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278620
};

class NpcPartyFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x2787a0
};

class NpcSpawnFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x2789e0
};

class NumberFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277180
};

class PartyLeaderFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278110
};

class PartyMemberFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x2781a0
};

class PartyMemberStateFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x278250
};

class PcFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277f50
};

class PropFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x2772e0
};

class PropFlagFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277770
};

class PropPercentFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277540
};

class QuestCompleteFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x279020
};

class QuestNotCompleteFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x279170
};

class SummonedFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x2791f0
};

class WeaponTypeFilter
{
public:
    virtual bool __cdecl Check(::Data::FilterRecord const *, ::Zone *, ::ScriptParam const *, ::ScriptParam const *, bool) const;  // 0x277fc0
};

