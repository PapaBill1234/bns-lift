// duelbottrainingroomscore.cpp: duelbottrainingroomscore.h (GameDaemon PDB, 2019 + PDB).
#include "duelbottrainingroomscore.h"
#include "propertysync.h"
#include "LiftStub.h"

// 0x197e0
wchar_t const * __cdecl DuelBotTrainingRoomScore::Name(void) const
{
    return L"DuelBotTrainingRoomScore";
}

// 0x197f0
int __cdecl DuelBotTrainingRoomScore::FieldMax(void) const
{
    return fieldMax;
}

// 0x19800
::Field::Def const * __cdecl DuelBotTrainingRoomScore::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19810
int __cdecl DuelBotTrainingRoomScore::SyncMax(void) const
{
    return syncMax;
}

// 0x19820
::SyncBuffer::Def const * __cdecl DuelBotTrainingRoomScore::SyncDefine(void) const
{
    return syncDefine;
}

// 0x1a050
int const __cdecl DuelBotTrainingRoomScore::TypeId(void) const
{
    return 33;
}

// LIFT: definitions of the PDB static data members (set at start-up by Property::initInstance, a later wave).
int DuelBotTrainingRoomScore::fieldMax;
::Field::Def const * DuelBotTrainingRoomScore::fieldDefine;
int DuelBotTrainingRoomScore::syncMax;
::SyncBuffer::Def const * DuelBotTrainingRoomScore::syncDefine;
