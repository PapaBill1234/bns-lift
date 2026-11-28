// scripttable.h: scripttable.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

namespace Data {
class DecisionContents
{
public:
    __cdecl ~DecisionContents(void);  // 0x467180
};
}

namespace Data {
// LIFT: flat view of the PDB record Data::ScriptFilterSet (base DrEl, size 0x10). A POD, so that the
// value-initialization in the constructor of FilterSet clears all of it (as the original does).
struct ScriptFilterSetView
{
    char type;  // +0 (0x0) DrEl::type
    short subtype;  // +2 (0x2) DrEl::subtype
    unsigned short size;  // +4 (0x4) DrEl::size
    wchar_t *name;  // +8 (0x8)
};

class FilterSet
{
public:
    __cdecl FilterSet(void);  // 0x467060
    __cdecl ~FilterSet(void);  // 0x467080
public:
    ::Data::ScriptFilterSetView _filterSetRecord;  // +0 (0x0) PDB type Data::ScriptFilterSet
    char *_filterRecords;  // +16 (0x10)
    ::Data::FilterRecord **_filters;  // +24 (0x18)
    int _filterCount;  // +32 (0x20)
};
}

namespace Data {
class ObjectScript
{
public:
    virtual __cdecl ~ObjectScript(void);  // 0x4672d0
    virtual ::Data::DecisionSequence const * __cdecl GetDecisionSequence(char, ::dr_tref const *) const;  // 0x467380
private:
    ::Data::QuestDecision const * __cdecl getQuestDecision(::Data::ObjectScript const *, wchar_t const *) const;  // 0x4673b0
public:
    struct EventSearchNode
    {
        char _event;  // +0 (0x0)
        ::Data::DecisionSequence *_decisionSequence;  // +8 (0x8)
    };
};

// LIFT: partial view of the PDB class Data::ObjectScript. The bodies read it with reinterpret_cast.
// Only the fields that the lifted bodies read are declared.
struct ObjectScriptView
{
    void *lift_vfptr;  // +0 (0x0) vfptr
    char lift_pad_8[0x20];  // PDB field +8 to +0x27 (_scriptRecord, Data::ScriptScript)
    int _eventNum;  // +40 (0x28)
    ::Data::ObjectScript::EventSearchNode *_eventSearchArray;  // +48 (0x30)
    int _questDecisionNum;  // +56 (0x38)
    ::Data::QuestDecision *_questDecisionArray;  // +64 (0x40)
};
}

namespace Data {
class QuestDecision
{
public:
    __cdecl ~QuestDecision(void);  // 0x467260
};
}

namespace Data {
// LIFT: flat view of the PDB record Data::ScriptReactionSet (base DrEl, size 0x20). A POD (see ScriptFilterSetView).
struct ScriptReactionSetView
{
    char type;  // +0 (0x0) DrEl::type
    short subtype;  // +2 (0x2) DrEl::subtype
    unsigned short size;  // +4 (0x4) DrEl::size
    char probability;  // +6 (0x6)
    short probability10000;  // +8 (0x8)
    wchar_t *name;  // +16 (0x10)
    int line;  // +24 (0x18)
};

class ReactionSet
{
public:
    __cdecl ReactionSet(void);  // 0x4670f0
    __cdecl ~ReactionSet(void);  // 0x467110
public:
    ::Data::ScriptReactionSetView _reactionSetRecord;  // +0 (0x0) PDB type Data::ScriptReactionSet
    char *_reactionRecords;  // +32 (0x20)
    ::Data::ScriptReaction **_reactions;  // +40 (0x28)
    int _reactionCount;  // +48 (0x30)
};
}

namespace Data {
class ScriptTable
{
public:
    virtual __cdecl ~ScriptTable(void);  // 0x4674a0
    virtual bool __cdecl LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x467550
    virtual bool __cdecl LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x467560
};
}

