// scripttable.cpp: scripttable.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "scripttable.h"
#include "LiftStub.h"

// 0x42e430 Data::SlateScrollCache::SlateScrollCache: LIFT: no body in wave 0 (member of a class template).

// 0x467060
__cdecl Data::FilterSet::FilterSet(void)
{
    LIFT_STUB(0x467060);
}

// 0x467080
__cdecl Data::FilterSet::~FilterSet(void)
{
    LIFT_STUB(0x467080);
}

// 0x4670f0
__cdecl Data::ReactionSet::ReactionSet(void)
{
    LIFT_STUB(0x4670f0);
}

// 0x467110
__cdecl Data::ReactionSet::~ReactionSet(void)
{
    LIFT_STUB(0x467110);
}

// 0x467180
__cdecl Data::DecisionContents::~DecisionContents(void)
{
    LIFT_STUB(0x467180);
}

// 0x467260
__cdecl Data::QuestDecision::~QuestDecision(void)
{
    LIFT_STUB(0x467260);
}

// 0x4672d0
__cdecl Data::ObjectScript::~ObjectScript(void)
{
    LIFT_STUB(0x4672d0);
}

// 0x467380
::Data::DecisionSequence const * __cdecl Data::ObjectScript::GetDecisionSequence(char, ::dr_tref const *) const
{
    LIFT_STUB(0x467380);
}

// 0x4673b0
::Data::QuestDecision const * __cdecl Data::ObjectScript::getQuestDecision(::Data::ObjectScript const *, wchar_t const *) const
{
    LIFT_STUB(0x4673b0);
}

// 0x4674a0
__cdecl Data::ScriptTable::~ScriptTable(void)
{
    LIFT_STUB(0x4674a0);
}

// 0x467550
bool __cdecl Data::ScriptTable::LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x467550);
}

// 0x467560
bool __cdecl Data::ScriptTable::LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x467560);
}
