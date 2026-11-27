// actsequenceloader.h: actsequenceloader.cpp, actsequenceloader.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ActSequenceLoader
{
public:
    struct LoaderContext {};
public:
    virtual ::TableType __cdecl GetTableType(void);  // 0x35f50
protected:
    int __cdecl getChildrenCount(::XmlElement const *, wchar_t const *);  // 0x3fe060
    bool __cdecl addSocials(::ActSequenceLoader::LoaderContext &, ::XmlElement const *, ::ActRandomSocial &);  // 0x3fe0f0
    ::ActRandomSocial * __cdecl createRandomSocial(::ActSequenceLoader::LoaderContext &, ::XmlElement const *);  // 0x3fe360
    bool __cdecl setupActionSeq(::ActSequenceLoader::LoaderContext &, ::XmlElement const *, ::ActActionSeq &);  // 0x3fe4e0
    bool __cdecl addActions(::ActSequenceLoader::LoaderContext &, ::XmlElement const *, ::ActActionSeq &);  // 0x3fe6f0
public:
    virtual bool __cdecl ReadFromBuffer(::DrElReader const &, ::DrLoaderDef const &, unsigned char const *, unsigned __int64);  // 0x455420
    virtual bool __cdecl LoadAlias(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x3fe880
    virtual bool __cdecl LoadTable(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x3fe960
    virtual bool __cdecl LoadTableMT_PreProc(::XmlReader const &, ::DrElReader const &, ::DrLoaderDef const &, ::DrAliasMap &);  // 0x3fee30
};

