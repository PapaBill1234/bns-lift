// tendencymanager_cpp.cpp: tendencymanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "tendencymanager.h"
#include "pc.h"
#include "LiftStub.h"

// 0x21f560
__cdecl TendencyField::TendencyField(void)
{
    LIFT_STUB(0x21f560);
}

// 0x21f660
__cdecl TendencyField::~TendencyField(void)
{
    LIFT_STUB(0x21f660);
}

// 0x21f750
bool __cdecl TendencyField::Initialize(unsigned __int64)
{
    LIFT_STUB(0x21f750);
}

// 0x21f880
void __cdecl TendencyField::DelZones(unsigned __int64 const *, int)
{
    LIFT_STUB(0x21f880);
}

// 0x21fa30
wchar_t const * __cdecl TendencyField::getStateStr(void)
{
    LIFT_STUB(0x21fa30);
}

// 0x21fa70
void __cdecl TendencyField::AddScore(unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x21fa70);
}

// 0x21fb60
void __cdecl TendencyField::SetScore(__int64, __int64, __int64)
{
    LIFT_STUB(0x21fb60);
}

// 0x21fc40
void __cdecl TendencyField::SetPlayValueForDebug(char)
{
    LIFT_STUB(0x21fc40);
}

// 0x21fd20
void __cdecl TendencyField::GetJackpotInfo(int, bool, int &, char &)
{
    LIFT_STUB(0x21fd20);
}

// 0x21fe40
bool __cdecl TendencyField::PublishTendencyQuestPack(char, ::Pc *, int, short *)
{
    LIFT_STUB(0x21fe40);
}

// 0x21ff20
bool __cdecl TendencyField::CheckManifestTendency(__int64 &)
{
    LIFT_STUB(0x21ff20);
}

// 0x21ffb0
void __cdecl TendencyField::setTendencyInfo(int, __int64)
{
    LIFT_STUB(0x21ffb0);
}

// 0x220230
void __cdecl TendencyField::resetTendencyInfo(void)
{
    LIFT_STUB(0x220230);
}

// 0x2202d0
void __cdecl TendencyField::OnTimer(__int64, __int64)
{
    LIFT_STUB(0x2202d0);
}

// 0x2204a0
bool __cdecl TendencyField::timeCheck(::Data::TendencyFieldTendencyStateType, __int64)
{
    LIFT_STUB(0x2204a0);
}

// 0x2205b0
bool __cdecl TendencyField::postNotifyEvent(unsigned __int64, ::TendencyField::EventData const &)
{
    LIFT_STUB(0x2205b0);
}

// 0x2207c0
bool __cdecl TendencyField::postManifestTendencyTask(unsigned __int64)
{
    LIFT_STUB(0x2207c0);
}

// 0x220a50
void __cdecl TendencyField::collectScore(void)
{
    LIFT_STUB(0x220a50);
}

// 0x220c80
bool __cdecl TendencyField::onScoreCheck(__int64, __int64)
{
    LIFT_STUB(0x220c80);
}

// 0x2211e0
bool __cdecl TendencyField::eventStandBy(__int64, int, int)
{
    LIFT_STUB(0x2211e0);
}

// 0x2218c0
bool __cdecl TendencyField::onStandBy(__int64, __int64)
{
    LIFT_STUB(0x2218c0);
}

// 0x2219c0
bool __cdecl TendencyField::onInProgress(__int64, __int64)
{
    LIFT_STUB(0x2219c0);
}

// 0x221a50
bool __cdecl TendencyField::eventFinish(__int64)
{
    LIFT_STUB(0x221a50);
}

// 0x221d50
void __cdecl TendencyManager::FinalizeInstance(void)
{
    LIFT_STUB(0x221d50);
}

// 0x221df0
__cdecl TendencyManager::TendencyManager(void)
{
    LIFT_STUB(0x221df0);
}

// 0x221ec0
void __cdecl TendencyManager::cleanupData(void)
{
    LIFT_STUB(0x221ec0);
}

// 0x221ff0
void __cdecl TendencyManager::TimerExpired(long)
{
    LIFT_STUB(0x221ff0);
}

// 0x2220b0
void __cdecl TendencyManager::CreateTendencyField(void)
{
    LIFT_STUB(0x2220b0);
}

// 0x222300
bool __cdecl TendencyManager::AddTendencyFieldTargetZone(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x222300);
}

// 0x2225b0
bool __cdecl TendencyManager::AddTendencyFieldNonTargetZone(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x2225b0);
}

// 0x2228a0
void __cdecl TendencyManager::SetTendencyScores(unsigned __int64, __int64, __int64, __int64)
{
    LIFT_STUB(0x2228a0);
}

// 0x2229e0
void __cdecl TendencyManager::SetPlayValue(unsigned __int64, char)
{
    LIFT_STUB(0x2229e0);
}

// 0x222b10
bool __cdecl TendencyManager::CheckManifestTendency(unsigned __int64, __int64 &)
{
    LIFT_STUB(0x222b10);
}

// 0x222bb0
bool __cdecl TendencyManager::IsPlayable(unsigned __int64)
{
    LIFT_STUB(0x222bb0);
}

// 0x222c40
bool __cdecl TendencyManager::AddQuest(::dr_tref, char, short, char)
{
    LIFT_STUB(0x222c40);
}

// 0x222de0
void __cdecl TendencyManager::Shake(void)
{
    LIFT_STUB(0x222de0);
}

// 0x222e70
bool __cdecl TendencyManager::PublishTendencyQuestPack(::dr_tref, char, ::Pc *, int, short *)
{
    LIFT_STUB(0x222e70);
}

// 0x222f80
__cdecl NormalTendencyAttractionQuestPack::NormalTendencyAttractionQuestPack(void)
{
    LIFT_STUB(0x222f80);
}

// 0x223010
bool __cdecl NormalTendencyAttractionQuestPack::GetNextQuests(::Pc *, char, char, char, unsigned __int64, int, short const *const, int, short *)
{
    LIFT_STUB(0x223010);
}

// 0x223090
bool __cdecl NormalTendencyAttractionQuestPack::getNextSimpleQuests(unsigned __int64, int, short const *const, int, short *)
{
    LIFT_STUB(0x223090);
}

// 0x223270
bool __cdecl NormalTendencyAttractionQuestPack::getNextTendencyQuests(char, unsigned __int64, int, short *)
{
    LIFT_STUB(0x223270);
}

// 0x223360
void __cdecl NormalTendencyAttractionQuestPack::Shake(void)
{
    LIFT_STUB(0x223360);
}

// 0x223680
bool __cdecl NormalTendencyAttractionQuestPack::Init(::Data::TendencyFieldRecordPtr)
{
    LIFT_STUB(0x223680);
}

// 0x2236a0
bool __cdecl NormalTendencyAttractionQuestPack::AddQuest(char, short, char)
{
    LIFT_STUB(0x2236a0);
}

// 0x223940
__cdecl BuyuDoTendencyAttractionQuestPack::BuyuDoTendencyAttractionQuestPack(void)
{
    LIFT_STUB(0x223940);
}

// 0x223a20
bool __cdecl BuyuDoTendencyAttractionQuestPack::Init(::Data::TendencyFieldRecordPtr)
{
    LIFT_STUB(0x223a20);
}

// 0x223a40
bool __cdecl BuyuDoTendencyAttractionQuestPack::GetNextQuests(::Pc *, char, char, char, unsigned __int64, int, short const *const, int, short *)
{
    LIFT_STUB(0x223a40);
}

// 0x223ad0
bool __cdecl BuyuDoTendencyAttractionQuestPack::getNextSimpleQuests(::Pc *, unsigned __int64, int, short const *const, int, short *)
{
    LIFT_STUB(0x223ad0);
}

// 0x223cc0
bool __cdecl BuyuDoTendencyAttractionQuestPack::getNextTendencyQuests(::Pc *, char, char, unsigned __int64, int, short *)
{
    LIFT_STUB(0x223cc0);
}

// 0x223e80
void __cdecl BuyuDoTendencyAttractionQuestPack::Shake(void)
{
    LIFT_STUB(0x223e80);
}

// 0x224050
bool __cdecl BuyuDoTendencyAttractionQuestPack::AddQuest(char, short, char)
{
    LIFT_STUB(0x224050);
}
