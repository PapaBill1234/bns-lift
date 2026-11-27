// scriptloader.cpp: scriptloader.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "scriptloader.h"
#include "scripttable.h"
#include "LiftStub.h"

// 0x465990
bool __cdecl Data::ScriptLoader::getDecisionRecordArray(::XmlElement const *, ::Data::ScriptScript *, ::Data::ScriptDecision **, int *, ::XmlReader const &, ::DrElReader const &, ::DrTableDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x465990);
}

// 0x465b00
bool __cdecl Data::ScriptLoader::loadScriptData(::Data::ObjectScript *, ::Data::ScriptDecision *, int, ::XmlElement const *, ::XmlReader const &, ::DrElReader const &, ::DrTableDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x465b00);
}

// 0x465d80
bool __cdecl Data::ScriptLoader::loadDecisionContents(::Data::DecisionContents *&, ::XmlElement const *, ::XmlReader const &, ::DrElReader const &, ::DrTableDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x465d80);
}

// 0x466890
bool __cdecl Data::ScriptLoader::constructSearchStructure(::Data::ObjectScript *, ::Data::ScriptDecision *, int)
{
    LIFT_STUB(0x466890);
}

// 0x466b50
bool __cdecl Data::ScriptLoader::LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x466b50);
}

// 0x466cb0
bool __cdecl Data::ScriptLoader::LoadTable(::Data::ScriptTable *, ::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &, ::DrMemory *)
{
    LIFT_STUB(0x466cb0);
}
