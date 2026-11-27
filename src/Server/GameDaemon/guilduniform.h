// guilduniform.h: guilduniform.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GuildUniform
{
public:
    struct Material {};
public:
    __cdecl GuildUniform(void);  // 0x130fd0
    void __cdecl Initialize(unsigned __int64, wchar_t const *, __int64, char const *const, char const *const, int const *const, short, ::GuildUniform::Material const *const);  // 0x1310b0
    bool __cdecl InitializeFromDBData(::GuildUniformInfo const *);  // 0x131260
private:
    bool __cdecl fetchUniformInfo(::FragmentPacket &);  // 0x131560
    bool __cdecl fetchUniformParams(::FragmentPacket &);  // 0x131610
    bool __cdecl fetchUniformMaterials(::FragmentPacket &);  // 0x131920
public:
    bool __cdecl FetchGuildUniformInfo(::FragmentPacket &);  // 0x131aa0
    short __cdecl EnableDonation(unsigned int, short, int, short &);  // 0x131b30
    short __cdecl TryAbandonGuildUniform(unsigned __int64, unsigned __int64, unsigned __int64);  // 0x131ca0
    bool __cdecl EnableRegisterGuildUniform(void);  // 0x131db0
    unsigned __int64 __cdecl AddDonationMaterial(unsigned int, short, int);  // 0x131e00
};

class GuildUniformManager
{
public:
    __cdecl ~GuildUniformManager(void);  // 0x131eb0
    bool __cdecl InitializeFromDBData(short, ::GuildUniformInfo *const);  // 0x131ff0
    ::Pointer2< ::GuildUniform> __cdecl AcquireGuildUniform(unsigned __int64);  // 0x132190
    bool __cdecl AddGuildUniform(::GuildUniform *);  // 0x132340
    bool __cdecl DelGuildUniform(unsigned __int64);  // 0x1323c0
    int __cdecl GetRegisteredUniformCount(void);  // 0x1324a0
    bool __cdecl FetchGuildUniformList(::FragmentPacket &);  // 0x132500
};

class NamingRule
{
public:
    enum CheckNameResult {};
public:
    static ::NamingRule::CheckNameResult __cdecl CheckName(::GameLocaleSet const &, wchar_t const *, int, int, int, bool, bool, bool, wchar_t const *);  // 0x130c50
};

