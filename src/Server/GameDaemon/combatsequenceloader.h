// combatsequenceloader.h: combatsequenceloader.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class CombatSequenceLoader
{
public:
    struct LoaderContext {};
public:
    virtual bool __cdecl LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x40a410
    virtual bool __cdecl LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x40a4f0
protected:
    bool __cdecl addActions(::CombatSequenceLoader::LoaderContext &, ::XmlElement const *, ::CombatSeqActionArray &, ::Data::CombatSequenceElType, ::Data::CombatSequenceElType);  // 0x40b110
};

