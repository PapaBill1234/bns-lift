// scriptloader.h: scriptloader.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

namespace Data {
class ScriptLoader
{
private:
    static bool __cdecl getDecisionRecordArray(::XmlElement const *, ::Data::ScriptScript *, ::Data::ScriptDecision **, int *, ::XmlReader const &, ::DrElReader const &, ::DrTableDef const &, ::DrAliasMap &);  // 0x465990
    static bool __cdecl loadScriptData(::Data::ObjectScript *, ::Data::ScriptDecision *, int, ::XmlElement const *, ::XmlReader const &, ::DrElReader const &, ::DrTableDef const &, ::DrAliasMap &);  // 0x465b00
    static bool __cdecl loadDecisionContents(::Data::DecisionContents *&, ::XmlElement const *, ::XmlReader const &, ::DrElReader const &, ::DrTableDef const &, ::DrAliasMap &);  // 0x465d80
    static bool __cdecl constructSearchStructure(::Data::ObjectScript *, ::Data::ScriptDecision *, int);  // 0x466890
public:
    static bool __cdecl LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x466b50
    static bool __cdecl LoadTable(::Data::ScriptTable *, ::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &, ::DrMemory *);  // 0x466cb0
};
}

