// duelbottrainingroomscorecontainer.cpp: duelbottrainingroomscorecontainer.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "duelbottrainingroomscorecontainer.h"
#include "pc.h"
#include "Log.h"
#include "AlertSender.h"
#include "Daemon.h"
#include "LiftStub.h"

#define DUELBOTTRAININGROOMSCORECONTAINER_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\DuelBotTrainingRoomScoreContainer.cpp"

namespace
{
// LIFT: view of GameObject (Id at +0x28). Pc has no declared Id member yet.
struct GameObjectView
{
    char lift_pad_0[0x28];
    unsigned __int64 Id;  // +40 (0x28)
};
}

// 0xae7b0
__cdecl DuelBotTrainingRoomScoreEntry::DuelBotTrainingRoomScoreEntry(void)
{
    LIFT_STUB(0xae7b0);
}

// 0xae800
__cdecl DuelBotTrainingRoomScoreEntry::~DuelBotTrainingRoomScoreEntry(void)
{
    LIFT_STUB(0xae800);
}

// 0xae820
void __cdecl DuelBotTrainingRoomScoreEntry::Initialize(short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short, short)
{
    LIFT_STUB(0xae820);
}

// 0xaeab0
void __cdecl DuelBotTrainingRoomScoreContainer::DuelBotTrainingRoomScoreValue::SetAchievementValue(short, char)
{
    LIFT_STUB(0xaeab0);
}

// 0xaeb90
__cdecl DuelBotTrainingRoomScoreContainer::~DuelBotTrainingRoomScoreContainer(void)
{
    LIFT_STUB(0xaeb90);
}

// 0xaec30
void __cdecl DuelBotTrainingRoomScoreContainer::syncToClient(::DuelBotTrainingRoomScoreEntry *) const
{
    LIFT_STUB(0xaec30);
}

// 0xaee80
bool __cdecl DuelBotTrainingRoomScoreContainer::Initialize(::Pc *)
{
    LIFT_STUB(0xaee80);
}

// 0xaef40
bool __cdecl DuelBotTrainingRoomScoreContainer::GetNewRecordValue(short, ::DuelBotTrainingRoomScoreContainer::DuelBotTrainingRoomScoreValue &, bool &) const
{
    LIFT_STUB(0xaef40);
}

// 0xaf0c0
bool __cdecl DuelBotTrainingRoomScoreContainer::SetRecordValue(short, ::DuelBotTrainingRoomScoreContainer::DuelBotTrainingRoomScoreValue &, bool, bool)
{
    LIFT_STUB(0xaf0c0);
}

// 0xaf420
::DuelBotTrainingRoomScoreEntry const * __cdecl DuelBotTrainingRoomScoreContainer::GetRecordEntry(short duelBotJob)
{
    LIFT_STUB(0xaf420);
}

// 0xaf480
char __cdecl DuelBotTrainingRoomScoreContainer::GetAchievementValue(short, char)
{
    LIFT_STUB(0xaf480);
}

// 0xaf670
bool __cdecl DuelBotTrainingRoomScoreContainer::SetRewardValueToRecord(::DuelBotTrainingRoomScoreContainer::DuelBotTrainingRoomScoreValue &, char, char)
{
    LIFT_STUB(0xaf670);
}

// 0xaf770
void __cdecl DuelBotTrainingRoomScoreContainer::FetchList(::Packet *, ::RepeatPacketComposer *)
{
    LIFT_STUB(0xaf770);
}

// 0xafa40
bool __cdecl DuelBotTrainingRoomScoreContainer::SetReceiveRewardFlag(void)
{
    LIFT_STUB(0xafa40);
}
