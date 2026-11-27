// combatsequenceloader.cpp: combatsequenceloader.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "combatsequenceloader.h"
#include "LiftStub.h"

// 0x40a410
bool __cdecl CombatSequenceLoader::LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x40a410);
}

// 0x40a4f0
bool __cdecl CombatSequenceLoader::LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x40a4f0);
}

// 0x40b110
bool __cdecl CombatSequenceLoader::addActions(::CombatSequenceLoader::LoaderContext &, ::XmlElement const *, ::CombatSeqActionArray &, ::Data::CombatSequenceElType, ::Data::CombatSequenceElType)
{
    LIFT_STUB(0x40b110);
}

// 0x40b900
static void DestroyCombatActions(CombatSeqActionArray&)
{
    LIFT_STUB(0x40b900);
}

// 0x40b990
static void DestroyCombatSequence(CombatSeq*, int)
{
    LIFT_STUB(0x40b990);
}
