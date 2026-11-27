// skill.cpp: skill.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "skill.h"
#include "raiddungeon.h"
#include "LiftStub.h"

// 0x1ab1d0
short __cdecl RaidDungeonUnbindPropertyEntry::FetchDb(char *, short) const
{
    LIFT_STUB(0x1ab1d0);
}

// 0x58d640
__cdecl SkillEntry::SkillEntry(void)
{
    LIFT_STUB(0x58d640);
}

// 0x58d6a0
void __cdecl SkillEntry::HandleBuildUpLevelByItem(char)
{
    LIFT_STUB(0x58d6a0);
}

// 0x58d740
void __cdecl SkillEntry::CollapsePassiveEffects(void)
{
    LIFT_STUB(0x58d740);
}

// 0x58d800
void __cdecl SkillEntry::InvokePassiveEffects(void)
{
    LIFT_STUB(0x58d800);
}

// 0x58d8d0
void __cdecl SkillEntry::invokeEffects(unsigned __int64 const *, short)
{
    LIFT_STUB(0x58d8d0);
}

// 0x58d9f0
__cdecl SkillContainer::SkillContainer(void)
{
    LIFT_STUB(0x58d9f0);
}

// 0x58dab0
__cdecl SkillContainer::~SkillContainer(void)
{
    LIFT_STUB(0x58dab0);
}

// 0x58dcc0
int __cdecl SkillContainer::SetDbData(char, short, char const *, int)
{
    LIFT_STUB(0x58dcc0);
}

// 0x58ded0
bool __cdecl SkillContainer::FetchAllPageList(::Packet *, ::RepeatPacketComposer *)
{
    LIFT_STUB(0x58ded0);
}

// 0x58dfe0
bool __cdecl SkillContainer::FetchAllPageList(::FragmentPacket *)
{
    LIFT_STUB(0x58dfe0);
}

// 0x58e0e0
bool __cdecl SkillContainer::FetchSkillPageList2(char, ::Packet *, ::RepeatPacketComposer *)
{
    LIFT_STUB(0x58e0e0);
}

// 0x58e1a0
bool __cdecl SkillContainer::FetchSkillPageList2(char, ::FragmentPacket *)
{
    LIFT_STUB(0x58e1a0);
}

// 0x58e240
bool __cdecl SkillContainer::FetchSkillPageList2ForDuelBot(::FragmentPacket *)
{
    LIFT_STUB(0x58e240);
}

// 0x58e2d0
bool __cdecl SkillContainer::FetchSkillList(char, ::Packet *, ::RepeatPacketComposer *)
{
    LIFT_STUB(0x58e2d0);
}

// 0x58e400
bool __cdecl SkillContainer::FetchSkillList(char, ::FragmentPacket *)
{
    LIFT_STUB(0x58e400);
}

// 0x58e570
bool __cdecl SkillContainer::ConfirmAcquire(int, unsigned __int64, unsigned __int64, __int64, char const *, short)
{
    LIFT_STUB(0x58e570);
}

// 0x58e630
bool __cdecl SkillContainer::FailConfirmAcquire(int, unsigned __int64, unsigned __int64, __int64, short)
{
    LIFT_STUB(0x58e630);
}

// 0x58e7c0
bool __cdecl SkillContainer::DisposeAcquire(char, int)
{
    LIFT_STUB(0x58e7c0);
}

// 0x58e8a0
bool __cdecl SkillContainer::Find(int)
{
    LIFT_STUB(0x58e8a0);
}

// 0x58e8f0
bool __cdecl SkillContainer::FindInPassiveSkills(int)
{
    LIFT_STUB(0x58e8f0);
}

// 0x58e960
bool __cdecl SkillContainer::CheckUse(unsigned __int64)
{
    LIFT_STUB(0x58e960);
}

// 0x58e9b0
char __cdecl SkillContainer::GetVariationId(int)
{
    LIFT_STUB(0x58e9b0);
}

// 0x58ea30
void __cdecl SkillContainer::HandleBuildUpLevelByItem(int, char)
{
    LIFT_STUB(0x58ea30);
}

// 0x58eaf0
bool __cdecl SkillContainer::GetSkillPage2(char, bool &, wchar_t const *&, char &)
{
    LIFT_STUB(0x58eaf0);
}

// 0x58ebe0
bool __cdecl SkillContainer::GetSkillPageEnable(char)
{
    LIFT_STUB(0x58ebe0);
}

// 0x58ec40
bool __cdecl SkillContainer::GetSkillPageTraitSelection(char, unsigned char *)
{
    LIFT_STUB(0x58ec40);
}

// 0x58f040
bool __cdecl SkillContainer::SetSkillPageTraitSelection(char, unsigned char *)
{
    LIFT_STUB(0x58f040);
}

// 0x58f0b0
bool __cdecl SkillContainer::GetSkillStatPointSelection(char, char &) const
{
    LIFT_STUB(0x58f0b0);
}

// 0x58f180
void __cdecl SkillContainer::SendSkillPageTotalOk(void)
{
    LIFT_STUB(0x58f180);
}

// 0x58f510
void __cdecl SkillContainer::SendSkillList2Ok(void)
{
    LIFT_STUB(0x58f510);
}

// 0x58f680
void __cdecl SkillContainer::FetchSkillPageTotalOkForBuilder(::FragmentPacket *)
{
    LIFT_STUB(0x58f680);
}

// 0x58fa30
bool __cdecl SkillContainer::ModifySkillPage2(char, bool, wchar_t const *)
{
    LIFT_STUB(0x58fa30);
}

// 0x58fc70
char __cdecl SkillContainer::GetCurrentSkillPageJobStyle(void)
{
    LIFT_STUB(0x58fc70);
}

// 0x58fcc0
bool __cdecl SkillContainer::ChangeSkillPageJobStyle(char, char)
{
    LIFT_STUB(0x58fcc0);
}

// 0x58fe00
bool __cdecl SkillContainer::InitializeTrainTrait(bool)
{
    LIFT_STUB(0x58fe00);
}

// 0x590020
bool __cdecl SkillContainer::MakeCandidateSkillList(char)
{
    LIFT_STUB(0x590020);
}

// 0x590620
short __cdecl SkillContainer::TrainTrait(char, char, unsigned char *const, ::SkillContainer::SkillBuildUp const *const, char, bool, bool)
{
    LIFT_STUB(0x590620);
}

// 0x592570
bool __cdecl SkillContainer::updateSkill(char, int, char, char, bool)
{
    LIFT_STUB(0x592570);
}

// 0x592630
void __cdecl SkillContainer::refreshPassiveSkill(char)
{
    LIFT_STUB(0x592630);
}

// 0x5926e0
bool __cdecl SkillContainer::ChangeCurrentSkillPage2(char)
{
    LIFT_STUB(0x5926e0);
}

// 0x592c70
bool __cdecl SkillContainer::RenameSkillPage2(char, wchar_t const *)
{
    LIFT_STUB(0x592c70);
}

// 0x592d40
bool __cdecl SkillContainer::SwitchOnToggleSkill(unsigned __int64)
{
    LIFT_STUB(0x592d40);
}

// 0x592e50
bool __cdecl SkillContainer::SwitchOffToggleSkill(unsigned __int64)
{
    LIFT_STUB(0x592e50);
}

// 0x592f20
::SkillEntry * __cdecl SkillContainer::findEntry(char, int)
{
    LIFT_STUB(0x592f20);
}

// 0x592fa0
void __cdecl SkillContainer::responseAcquire2(char, int, char, char)
{
    LIFT_STUB(0x592fa0);
}

// 0x593020
void __cdecl SkillContainer::responseDispose(char, int)
{
    LIFT_STUB(0x593020);
}

// 0x593090
void __cdecl SkillContainer::addSkill(char, int, ::SkillEntry *)
{
    LIFT_STUB(0x593090);
}

// 0x593120
bool __cdecl SkillContainer::collapsePassiveSkill(char, int)
{
    LIFT_STUB(0x593120);
}

// 0x593240
bool __cdecl SkillContainer::addPassiveSkill(int, ::SkillEntry *)
{
    LIFT_STUB(0x593240);
}

// 0x593320
void __cdecl SkillContainer::deleteSkill(char, int)
{
    LIFT_STUB(0x593320);
}

// 0x593640
bool __cdecl SkillContainer::Acquire2(char, int, char, char, bool, bool)
{
    LIFT_STUB(0x593640);
}

// 0x593bf0
::SkillEntry * __cdecl SkillContainer::acquireSkill(char, int, char, char, bool)
{
    LIFT_STUB(0x593bf0);
}

// 0x593d40
void __cdecl SkillContainer::AddSkillByGrowth(char, int, char)
{
    LIFT_STUB(0x593d40);
}

// 0x593e20
void __cdecl SkillContainer::AddSkillByGrowth(int, char)
{
    LIFT_STUB(0x593e20);
}

// 0x593f80
void __cdecl SkillContainer::RefreshSkillList(char, bool)
{
    LIFT_STUB(0x593f80);
}

// 0x5940c0
bool __cdecl SkillContainer::SetMasteryStatPoint(short, short, char *const, char)
{
    LIFT_STUB(0x5940c0);
}

// 0x594440
bool __cdecl SkillContainer::InvokeMasteryStatBonusEffects(void)
{
    LIFT_STUB(0x594440);
}

// 0x594d80
bool __cdecl SkillContainer::CheckToAddMasteryStatAdditionalPoint(short)
{
    LIFT_STUB(0x594d80);
}

// 0x594e80
bool __cdecl SkillContainer::AddMasteryStatAdditionalPoint(short, short &, short &)
{
    LIFT_STUB(0x594e80);
}

// 0x594fc0
void __cdecl SkillContainer::collapsePassiveEffects(void)
{
    LIFT_STUB(0x594fc0);
}

// 0x595180
void __cdecl SkillContainer::clearCandidateSkill(char)
{
    LIFT_STUB(0x595180);
}

// 0x5952e0
bool __cdecl SkillContainer::addCandidateSkill(char, int, char)
{
    LIFT_STUB(0x5952e0);
}

// 0x595430
bool __cdecl SkillContainer::isCandidateSkill(char, int)
{
    LIFT_STUB(0x595430);
}

// 0x5954b0
::SkillEntry * __cdecl SkillContainer::findCandidateSkill(char, int)
{
    LIFT_STUB(0x5954b0);
}

// 0x595530
bool __cdecl SkillContainer::copyCurrentSkillPageTo2(char)
{
    LIFT_STUB(0x595530);
}
