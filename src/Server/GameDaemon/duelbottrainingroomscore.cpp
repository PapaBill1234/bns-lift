// duelbottrainingroomscore.cpp: duelbottrainingroomscore.h (GameDaemon PDB, 2019 + PDB).
#include "duelbottrainingroomscore.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted (card lift-gamedaemon-gap-003-e3).
#pragma comment(linker, "/INCLUDE:?TypeId@DuelBotTrainingRoomScore@@UEBA?BHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@DuelBotTrainingRoomScore@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@DuelBotTrainingRoomScore@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@DuelBotTrainingRoomScore@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@DuelBotTrainingRoomScore@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@DuelBotTrainingRoomScore@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

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
