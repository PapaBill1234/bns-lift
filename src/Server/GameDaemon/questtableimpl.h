// questtableimpl.h: questtableimpl.cpp, questtableimpl.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class QuestTableImpl
{
public:
    struct LoaderContext {};
private:
    bool __cdecl loadFilterSet(::QuestFilterSet *, ::XmlElement const *, ::QuestTableImpl::LoaderContext &);  // 0x6f7440
    bool __cdecl loadReactionSet(::QuestReactionSet *, ::XmlElement const *, ::QuestTableImpl::LoaderContext &);  // 0x6f76b0
    bool __cdecl loadCase(::QuestCase *, ::QuestCase::Category, ::XmlElement const *, ::QuestTableImpl::LoaderContext &);  // 0x6f7920
    bool __cdecl loadMissionStepFail(::Quest *, char, ::XmlElement const *, ::QuestTableImpl::LoaderContext &);  // 0x6f7c00
    bool __cdecl loadCompletion(::Completion *, ::XmlElement const *, ::QuestTableImpl::LoaderContext &);  // 0x6f7f20
    bool __cdecl loadTransit(::Transit *, ::XmlElement const *, ::QuestTableImpl::LoaderContext &);  // 0x6f8130
    bool __cdecl allocQuestRewardContents(::QuestReward *, int, int, int);  // 0x6f83d0
    void __cdecl clearBuffer(void);  // 0x6f8490
public:
    virtual void __cdecl GetTableSummary(::DrTableSummary &);  // 0x6f8550
    virtual ::Quest const * __cdecl GetQuest(unsigned short) const;  // 0x6f86a0
    virtual ::TableType __cdecl GetTableType(void);  // 0x6f86d0
    virtual unsigned short __cdecl GetMaxQuestId(void) const;  // 0x6f86e0
    virtual ::Quest const * __cdecl GetQuestByIndex(int) const;  // 0x6f86f0
    virtual unsigned short __cdecl GetMaxQuestNum(void) const;  // 0x6f8700
private:
    bool __cdecl loadAcquisition(::Acquisition *, ::XmlElement const *, ::QuestTableImpl::LoaderContext &);  // 0x6f8710
    bool __cdecl loadMission(::Quest *, char, ::XmlElement const *, ::QuestTableImpl::LoaderContext &);  // 0x6f8e60
    bool __cdecl loadQuest(::XmlElement const *, ::QuestTableImpl::LoaderContext &);  // 0x6f9790
public:
    virtual bool __cdecl LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x6fa160
    __cdecl QuestTableImpl(void);  // 0x6fa2f0
private:
    // LIFT: PDB members. The class has no base yet, so the members start at +8 after the vftable (PDB: base QuestTable, same offsets).
    unsigned short _maxQuestId;  // +8
    unsigned short _questListSize;  // +10
    ::Quest * * _questArray;  // +16
    ::Quest * * _questListArray;  // +24
    ::DrEl _el;  // +32
};

