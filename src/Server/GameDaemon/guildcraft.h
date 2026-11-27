// guildcraft.h: guildcraft.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GuildCraft
{
public:
    struct Product {};
public:
    __cdecl GuildCraft(void);  // 0x1133d0
    void __cdecl Initialize(unsigned __int64, unsigned int, char, char, char, unsigned __int64, wchar_t const *, __int64);  // 0x1134f0
    bool __cdecl InitializeFromDBData(::GuildCraftInfo const *);  // 0x113810
    bool __cdecl TakeGuildCraft(short, int &);  // 0x113f00
    bool __cdecl FetchGuildCraftInfo(::FragmentPacket &);  // 0x113ff0
private:
    bool __cdecl fetchGuildCraftInfo(::FragmentPacket &);  // 0x1140e0
    bool __cdecl fetchGuildCraftAssentients(::FragmentPacket &);  // 0x114200
    bool __cdecl fetchDonationNormalMaterials(::FragmentPacket &);  // 0x1143f0
    bool __cdecl fetchDonationBrandMaterials(::FragmentPacket &);  // 0x114580
public:
    short __cdecl EnableAssentGuildCraft(unsigned __int64, char, short);  // 0x114710
    char __cdecl GetAsseintGuildCraftQuota(char);  // 0x114960
    void __cdecl AddAssentient(unsigned __int64, char, wchar_t const *);  // 0x1149f0
    bool __cdecl EnableMakeGuildCraft(char, ::GuildCraft::Product &);  // 0x114ad0
    void __cdecl MakeGuildCraft(int, short, int, __int64, __int64);  // 0x114b90
    bool __cdecl EnableDonationGuildCraft(void);  // 0x114c30
    bool __cdecl EnableDonationItem(unsigned int, short);  // 0x114c80
    bool __cdecl EnableDonationBrandItem(unsigned __int64, char);  // 0x114d20
    short __cdecl GetDonationItemQuota(unsigned int, short);  // 0x114dc0
    short __cdecl GetDonationBrandItemQuota(unsigned __int64, char);  // 0x114e70
    bool __cdecl EnableDonationNormalMaterial(unsigned int, short, int);  // 0x114f20
    unsigned __int64 __cdecl AddDonationNormalMaterial(unsigned int, short, int);  // 0x115020
    unsigned __int64 __cdecl AddDonationBrandMaterial(unsigned int, char, int);  // 0x1150d0
    bool __cdecl IsCompletedGuildCraftDonation(void);  // 0x115190
    short __cdecl TryAbandonGuildCraft(unsigned __int64, unsigned __int64, unsigned __int64);  // 0x115210
    bool __cdecl EnableDonationBrandMaterial(unsigned __int64, char, int);  // 0x115330
};

class GuildCraftManager
{
public:
    __cdecl ~GuildCraftManager(void);  // 0x115430
    bool __cdecl InitializeFromDBData(short, ::GuildCraftInfo const *const);  // 0x115580
    ::Pointer2< ::GuildCraft> __cdecl AcquireGuildCraft(unsigned __int64);  // 0x115720
    ::Pointer2< ::GuildCraft> __cdecl AcquireGuildCraft(int);  // 0x1158d0
    bool __cdecl AddGuildCraft(::GuildCraft *);  // 0x115a80
    bool __cdecl DelGuildCraft(unsigned __int64);  // 0x115b00
    char __cdecl GetGuildCraftCount(char, char);  // 0x115bf0
    bool __cdecl FetchGuildCraftList(::FragmentPacket &);  // 0x115c70
};

