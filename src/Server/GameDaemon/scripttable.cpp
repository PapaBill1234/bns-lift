// scripttable.cpp: scripttable.cpp (GameDaemon PDB, 2019 + PDB).
#include "scripttable.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "LiftStub.h"

// LIFT: per-exe path literal (lessons A6).
#define SCRIPTTABLE_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\ScriptTable.cpp"

#pragma comment(linker, "/INCLUDE:??0FilterSet@Data@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1FilterSet@Data@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??0ReactionSet@Data@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1ReactionSet@Data@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDecisionSequence@ObjectScript@Data@@UEBAPEBVDecisionSequence@2@DPEBUdr_tref@@@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x42e430 Data::SlateScrollCache::SlateScrollCache: LIFT: no body in wave 0 (member of a class template).
// LIFT: 0x42e430 is also Data::QuestDecision::QuestDecision (identical code folded with a std::vector constructor). Not lifted.

// 0x467060
__cdecl Data::FilterSet::FilterSet(void)
    : _filterSetRecord()
    , _filterRecords(NULL)
    , _filters(NULL)
    , _filterCount(0)
{
}

// 0x467080
__cdecl Data::FilterSet::~FilterSet(void)
{
    if (_filterRecords != NULL)
    {
        Memory::_Manager[1]->Free(_filterRecords, SCRIPTTABLE_FILE, 28);
        _filterRecords = NULL;
    }
    if (_filters != NULL)
    {
        Memory::_Manager[1]->Free(_filters, SCRIPTTABLE_FILE, 29);
        _filters = NULL;
    }
}

// 0x4670f0
__cdecl Data::ReactionSet::ReactionSet(void)
    : _reactionSetRecord()
    , _reactionRecords(NULL)
    , _reactions(NULL)
    , _reactionCount(0)
{
}

// 0x467110
__cdecl Data::ReactionSet::~ReactionSet(void)
{
    if (_reactionRecords != NULL)
    {
        Memory::_Manager[1]->Free(_reactionRecords, SCRIPTTABLE_FILE, 43);
        _reactionRecords = NULL;
    }
    if (_reactions != NULL)
    {
        Memory::_Manager[1]->Free(_reactions, SCRIPTTABLE_FILE, 44);
        _reactions = NULL;
    }
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
::Data::DecisionSequence const * __cdecl Data::ObjectScript::GetDecisionSequence(char event, ::dr_tref const *) const
{
    for (int i = 0; i < _eventNum; ++i)
    {
        if (_eventSearchArray[i]._event == event)
            return _eventSearchArray[i]._decisionSequence;
    }
    return NULL;
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
