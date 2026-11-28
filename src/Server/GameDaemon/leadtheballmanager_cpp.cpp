// leadtheballmanager_cpp.cpp: leadtheballmanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "leadtheballmanager.h"
#include "creature.h"
#include "envobj.h"
#include "npc.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x137a90
__cdecl LeadTheBallManager::LeadTheBallManager(void)
{
    LIFT_STUB(0x137a90);
}

// 0x137b50
bool __cdecl LeadTheBallManager::Init(::Zone *, unsigned __int64)
{
    LIFT_STUB(0x137b50);
}

// 0x137f40
void __cdecl LeadTheBallManager::OnTimer(void)
{
    LIFT_STUB(0x137f40);
}

// 0x1381d0
bool __cdecl LeadTheBallManager::EnterNpc(::Npc *)
{
    LIFT_STUB(0x1381d0);
}

// 0x1382d0
bool __cdecl LeadTheBallManager::TryToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr &)
{
    LIFT_STUB(0x1382d0);
}

// 0x138380
void __cdecl LeadTheBallManager::OnDead(unsigned __int64, ::Pc *)
{
    LIFT_STUB(0x138380);
}

// 0x138550
void __cdecl LeadTheBallManager::OnEnvManipulated(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &, char, char)
{
    LIFT_STUB(0x138550);
}

namespace
{
// LIFT: view of the PDB class PartyBattleManager (base of LeadTheBallManager). Only _step is declared.
struct LtbPartyBattleManagerView
{
    char lift_pad_0[0x18];
    char _step;  // +24 (0x18)
};

// LIFT: view of DrEl (PDB: subtype at +2), the base of Data::ZoneEnv2Record.
struct LtbZoneEnv2RecordView
{
    short type;     // +0
    short subtype;  // +2
};

// LIFT: view of Data::ZoneEnv2RecordPtr (PDB: DrRecordPtr::_record at +0).
struct LtbZoneEnv2PtrView
{
    LtbZoneEnv2RecordView *_record;  // +0
};
}

// 0x138720
#pragma comment(linker, "/INCLUDE:?OnCanceledEnvManipulation@LeadTheBallManager@@UEAAXPEAVEnv@@AEAVZoneEnv2RecordPtr@Data@@DD@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl LeadTheBallManager::OnCanceledEnvManipulation(::Env * env, ::Data::ZoneEnv2RecordPtr & envData, char preState, char state)
{
    LtbPartyBattleManagerView *self = reinterpret_cast<LtbPartyBattleManagerView *>(this);
    LtbZoneEnv2PtrView &data = reinterpret_cast<LtbZoneEnv2PtrView &>(envData);
    // LIFT: ❓ PDB names of step 2 and env subtype 6 (and states 8, 9) are not known.
    if (env != nullptr && data._record != nullptr && self->_step == 2 && data._record->subtype == 6 && state >= 8 && state <= 9)
        env->ChangeState(preState);
}

// 0x138770
void __cdecl LeadTheBallManager::OnEnterFootSwitch(::Creature *, ::Env *, ::Data::ZoneEnv2RecordPtr const &)
{
    LIFT_STUB(0x138770);
}

// 0x138970
void __cdecl LeadTheBallManager::Reset(void)
{
    LIFT_STUB(0x138970);
}

// 0x138bb0
int __cdecl LeadTheBallManager::getRatingRevise(short)
{
    LIFT_STUB(0x138bb0);
}

// 0x138c00
void __cdecl LeadTheBallManager::setEnvInitState(void)
{
    LIFT_STUB(0x138c00);
}

// 0x138d30
void __cdecl LeadTheBallManager::setEnvInitEnable(void)
{
    LIFT_STUB(0x138d30);
}

// 0x138f40
void __cdecl LeadTheBallManager::changeInGameSubStep(void)
{
    LIFT_STUB(0x138f40);
}

// 0x139040
bool __cdecl LeadTheBallManager::invokeEffect(unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x139040);
}

// 0x1390f0
bool __cdecl LeadTheBallManager::checkSpawnBall(void)
{
    LIFT_STUB(0x1390f0);
}

// 0x139200
void __cdecl LeadTheBallManager::spawnBall(void)
{
    LIFT_STUB(0x139200);
}

// 0x1394e0
void __cdecl LeadTheBallManager::addZoneScoreGoalIn(char, bool)
{
    LIFT_STUB(0x1394e0);
}

// 0x139760
void __cdecl LeadTheBallManager::sendGoalInCountInfo(void)
{
    LIFT_STUB(0x139760);
}
