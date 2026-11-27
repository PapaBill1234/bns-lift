// skill.h: skill.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include <map>
#include "GameDaemonFwd.h"

// LIFT: view of the PDB struct SkillPage::__default__ (size 0x190). Only the fields up to the job styles are declared.
struct SkillPageDefaultView
{
    int skill_version;  // +0x0
    char current_skill_page;  // +0x4
    unsigned char skill_page_enable1 : 1;  // +0x5
    wchar_t skill_page_name1[33];  // +0x6
    unsigned char skill_page_enable2 : 1;  // +0x48
    wchar_t skill_page_name2[33];  // +0x4A
    unsigned char skill_page_enable3 : 1;  // +0x8C
    wchar_t skill_page_name3[33];  // +0x8E
    unsigned char skill_page_enable4 : 1;  // +0xD0
    wchar_t skill_page_name4[33];  // +0xD2
    unsigned char skill_page_enable5 : 1;  // +0x114
    wchar_t skill_page_name5[33];  // +0x116
    short skill_statpoint_attacker;  // +0x158
    short skill_statpoint_defender;  // +0x15A
    short skill_statpoint_additional;  // +0x15C
    char skill_statpoint_selection_1;  // +0x15E
    char skill_statpoint_selection_2;  // +0x15F
    char skill_statpoint_selection_3;  // +0x160
    char skill_statpoint_selection_4;  // +0x161
    char skill_statpoint_selection_5;  // +0x162
    char skill_page_job_style1;  // +0x163
    char skill_page_job_style2;  // +0x164
    char skill_page_job_style3;  // +0x165
    char skill_page_job_style4;  // +0x166
    char skill_page_job_style5;  // +0x167
    char lift_pad_168[0x190 - 0x168];  // LIFT: skill_page_trait_selection1..5 (f_bin<5>) are not declared yet
};
static_assert(sizeof(SkillPageDefaultView) == 0x190, "sizeof SkillPage::__default__");

// LIFT: view of the PDB class SkillPage (base Property, size 0x1C0).
class SkillPageView
{
public:
    char lift_pad_0[0x30];  // LIFT: base Property is not declared yet
    ::SkillPageDefaultView Default;  // +0x30 (PDB: SkillPage::__default__ const)
};
static_assert(sizeof(SkillPageView) == 0x1C0, "sizeof SkillPage");

class SkillContainer
{
public:
    struct SkillBuildUp {};
public:
    __cdecl SkillContainer(void);  // 0x58d9f0
    __cdecl ~SkillContainer(void);  // 0x58dab0
    int __cdecl SetDbData(char, short, char const *, int);  // 0x58dcc0
    bool __cdecl FetchAllPageList(::Packet *, ::RepeatPacketComposer *);  // 0x58ded0
    bool __cdecl FetchAllPageList(::FragmentPacket *);  // 0x58dfe0
    bool __cdecl FetchSkillPageList2(char, ::Packet *, ::RepeatPacketComposer *);  // 0x58e0e0
    bool __cdecl FetchSkillPageList2(char, ::FragmentPacket *);  // 0x58e1a0
    bool __cdecl FetchSkillPageList2ForDuelBot(::FragmentPacket *);  // 0x58e240
    bool __cdecl FetchSkillList(char, ::Packet *, ::RepeatPacketComposer *);  // 0x58e2d0
    bool __cdecl FetchSkillList(char, ::FragmentPacket *);  // 0x58e400
    bool __cdecl ConfirmAcquire(int, unsigned __int64, unsigned __int64, __int64, char const *, short);  // 0x58e570
    bool __cdecl FailConfirmAcquire(int, unsigned __int64, unsigned __int64, __int64, short);  // 0x58e630
    bool __cdecl DisposeAcquire(char, int);  // 0x58e7c0
    bool __cdecl Find(int);  // 0x58e8a0
    bool __cdecl FindInPassiveSkills(int);  // 0x58e8f0
    bool __cdecl CheckUse(unsigned __int64);  // 0x58e960
    char __cdecl GetVariationId(int);  // 0x58e9b0
    void __cdecl HandleBuildUpLevelByItem(int, char);  // 0x58ea30
    bool __cdecl GetSkillPage2(char, bool &, wchar_t const *&, char &);  // 0x58eaf0
    bool __cdecl GetSkillPageEnable(char);  // 0x58ebe0
    bool __cdecl GetSkillPageTraitSelection(char, unsigned char *);  // 0x58ec40
    bool __cdecl SetSkillPageTraitSelection(char, unsigned char *);  // 0x58f040
    bool __cdecl GetSkillStatPointSelection(char, char &) const;  // 0x58f0b0
    void __cdecl SendSkillPageTotalOk(void);  // 0x58f180
    void __cdecl SendSkillList2Ok(void);  // 0x58f510
    void __cdecl FetchSkillPageTotalOkForBuilder(::FragmentPacket *);  // 0x58f680
    bool __cdecl ModifySkillPage2(char, bool, wchar_t const *);  // 0x58fa30
    char __cdecl GetCurrentSkillPageJobStyle(void);  // 0x58fc70
    bool __cdecl ChangeSkillPageJobStyle(char, char);  // 0x58fcc0
    bool __cdecl InitializeTrainTrait(bool);  // 0x58fe00
    bool __cdecl MakeCandidateSkillList(char);  // 0x590020
    short __cdecl TrainTrait(char, char, unsigned char *const, ::SkillContainer::SkillBuildUp const *const, char, bool, bool);  // 0x590620
private:
    bool __cdecl updateSkill(char, int, char, char, bool);  // 0x592570
    void __cdecl refreshPassiveSkill(char);  // 0x592630
public:
    bool __cdecl ChangeCurrentSkillPage2(char);  // 0x5926e0
    bool __cdecl RenameSkillPage2(char, wchar_t const *);  // 0x592c70
    bool __cdecl SwitchOnToggleSkill(unsigned __int64);  // 0x592d40
    bool __cdecl SwitchOffToggleSkill(unsigned __int64);  // 0x592e50
private:
    ::SkillEntry * __cdecl findEntry(char, int);  // 0x592f20
    void __cdecl responseAcquire2(char, int, char, char);  // 0x592fa0
    void __cdecl responseDispose(char, int);  // 0x593020
    void __cdecl addSkill(char, int, ::SkillEntry *);  // 0x593090
    bool __cdecl collapsePassiveSkill(char, int);  // 0x593120
    bool __cdecl addPassiveSkill(int, ::SkillEntry *);  // 0x593240
    void __cdecl deleteSkill(char, int);  // 0x593320
public:
    bool __cdecl Acquire2(char, int, char, char, bool, bool);  // 0x593640
private:
    ::SkillEntry * __cdecl acquireSkill(char, int, char, char, bool);  // 0x593bf0
public:
    void __cdecl AddSkillByGrowth(char, int, char);  // 0x593d40
    void __cdecl AddSkillByGrowth(int, char);  // 0x593e20
    void __cdecl RefreshSkillList(char, bool);  // 0x593f80
    bool __cdecl SetMasteryStatPoint(short, short, char *const, char);  // 0x5940c0
    bool __cdecl InvokeMasteryStatBonusEffects(void);  // 0x594440
    bool __cdecl CheckToAddMasteryStatAdditionalPoint(short);  // 0x594d80
    bool __cdecl AddMasteryStatAdditionalPoint(short, short &, short &);  // 0x594e80
private:
    void __cdecl collapsePassiveEffects(void);  // 0x594fc0
    void __cdecl clearCandidateSkill(char);  // 0x595180
    bool __cdecl addCandidateSkill(char, int, char);  // 0x5952e0
    bool __cdecl isCandidateSkill(char, int);  // 0x595430
    ::SkillEntry * __cdecl findCandidateSkill(char, int);  // 0x5954b0
    bool __cdecl copyCurrentSkillPageTo2(char);  // 0x595530
    // LIFT: PDB layout (size 0x328).
    typedef std::map<unsigned int, ::SkillEntry *, std::less<unsigned int>, StlAllocator<std::pair<unsigned int, ::SkillEntry *>, 2> > SkillList;
    ::Creature *owner;  // +0x0
    SkillList acquiredSkillList[5];  // +0x8
    SkillList candidateSkillList[5];  // +0xA8
    SkillList passiveSkillList;  // +0x148
    ::SkillPageView skillPageProperty;  // +0x168 (PDB type: SkillPage)
};
static_assert(sizeof(SkillContainer) == 0x328, "sizeof SkillContainer");

class SkillEntry
{
public:
    __cdecl SkillEntry(void);  // 0x58d640
    void __cdecl HandleBuildUpLevelByItem(char);  // 0x58d6a0
    void __cdecl CollapsePassiveEffects(void);  // 0x58d740
    void __cdecl InvokePassiveEffects(void);  // 0x58d800
private:
    void __cdecl invokeEffects(unsigned __int64 const *, short);  // 0x58d8d0
};

