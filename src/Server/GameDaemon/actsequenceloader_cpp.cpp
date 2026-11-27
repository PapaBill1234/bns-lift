// actsequenceloader_cpp.cpp: actsequenceloader.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "actsequenceloader.h"
#include "LiftStub.h"

// 0x3fe060
int __cdecl ActSequenceLoader::getChildrenCount(::XmlElement const *, wchar_t const *)
{
    LIFT_STUB(0x3fe060);
}

// 0x3fe0f0
bool __cdecl ActSequenceLoader::addSocials(::ActSequenceLoader::LoaderContext &, ::XmlElement const *, ::ActRandomSocial &)
{
    LIFT_STUB(0x3fe0f0);
}

// 0x3fe360
::ActRandomSocial * __cdecl ActSequenceLoader::createRandomSocial(::ActSequenceLoader::LoaderContext &, ::XmlElement const *)
{
    LIFT_STUB(0x3fe360);
}

// 0x3fe4e0
bool __cdecl ActSequenceLoader::setupActionSeq(::ActSequenceLoader::LoaderContext &, ::XmlElement const *, ::ActActionSeq &)
{
    LIFT_STUB(0x3fe4e0);
}

// 0x3fe6f0
bool __cdecl ActSequenceLoader::addActions(::ActSequenceLoader::LoaderContext &, ::XmlElement const *, ::ActActionSeq &)
{
    LIFT_STUB(0x3fe6f0);
}

// 0x3fe880
bool __cdecl ActSequenceLoader::LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x3fe880);
}

// 0x3fe960
bool __cdecl ActSequenceLoader::LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &)
{
    LIFT_STUB(0x3fe960);
}
