// guilduniform.h: guilduniform.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include <stddef.h>

// PDB enum GuildUniformState.
enum GuildUniformState
{
    GUILDUNIFORMSTATE_INVALID = 0x0,
    GUILDUNIFORMSTATE_CONTRACTED = 0x1,
    GUILDUNIFORMSTATE_READY_TO_MAKE = 0x2,
    GUILDUNIFORMSTATE_IN_MAKING = 0x3,
    GUILDUNIFORMSTATE_MAKED = 0x4,
    GUILDUNIFORMSTATE_REGISTERED = 0x5,
};

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

// LIFT: partial view of the PDB class GuildUniform (size 0x438). The bodies read it with reinterpret_cast.
// Only the fields that the lifted bodies read are declared.
struct GuildUniformView
{
    char lift_pad_0[0x62];  // PDB fields +0 to +0x61 (DynamicRefCntObj base to _uniformName)
    char _state;  // +98 (0x62)
    char lift_pad_63[0x430 - 0x63];  // PDB fields +0x63 to +0x42F (_registrationTime to _material)
    ::_RTL_SRWLOCK _srwLock;  // +1072 (0x430)
};
static_assert(offsetof(GuildUniformView, _state) == 0x62, "GuildUniform::_state");
static_assert(offsetof(GuildUniformView, _srwLock) == 0x430, "GuildUniform::_srwLock");

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
public:
    // LIFT: PDB layout of GuildUniformManager (size 0x60).
    ::_RTL_SRWLOCK _srwLock;  // +0 (0x0)
    ::GuildUniform *_uniformList[10];  // +8 (0x8)
    char _uniformTotalCount;  // +88 (0x58)
};
static_assert(offsetof(GuildUniformManager, _uniformTotalCount) == 0x58, "GuildUniformManager::_uniformTotalCount");
static_assert(sizeof(GuildUniformManager) == 0x60, "sizeof GuildUniformManager");

class NamingRule
{
public:
    enum CheckNameResult {};
public:
    static ::NamingRule::CheckNameResult __cdecl CheckName(::GameLocaleSet const &, wchar_t const *, int, int, int, bool, bool, bool, wchar_t const *);  // 0x130c50
};

