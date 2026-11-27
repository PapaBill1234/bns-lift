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
class FilterSet
{
public:
    __cdecl FilterSet(void);  // 0x467060
    __cdecl ~FilterSet(void);  // 0x467080
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
class ReactionSet
{
public:
    __cdecl ReactionSet(void);  // 0x4670f0
    __cdecl ~ReactionSet(void);  // 0x467110
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

