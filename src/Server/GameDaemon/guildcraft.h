// guildcraft.h: guildcraft.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include <windows.h>

class GuildCraft : public ::DynamicRefCntObj
{
public:
    struct Product {};
    // PDB nested types (NormalMaterial 0x10, BrandMaterial 0x18, PCInfo 0x50).
    struct NormalMaterial
    {
        unsigned int itemDataID;  // +0
        short itemLevel;  // +4
        int itemAmount;  // +8
        short itemDataAmount;  // +12
    };
    struct BrandMaterial
    {
        unsigned int itemDataId;  // +0
        short itemLevel;  // +4
        unsigned int brandID;  // +8
        char conditionType;  // +12
        int amount;  // +16
        short dataAmount;  // +20
    };
    struct PCInfo
    {
        unsigned __int64 pcDbId;  // +0
        wchar_t pcName[33];  // +8
    };
    struct Assentient
    {
        char productionType;  // +0
        char pcNameCount;  // +1
        ::GuildCraft::PCInfo pcList[10];  // +8
        char quota;  // +808
        short productionExp;  // +810
    };
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
private:
    // PDB layout of GuildCraft (size 0x1848).
    unsigned __int64 _guildCraftID;  // +0x18
    char _craftType;  // +0x20
    char _state;  // +0x21
    void *_recipeData;  // +0x28 LIFT: Data::GuildCraftRecipeRecordPtr view
    unsigned int _recipeID;  // +0x30
    char _contractType;  // +0x34
    char _recvType;  // +0x35
    unsigned __int64 _recvPcId;  // +0x38
    wchar_t _recvPCName[33];  // +0x40
    int _productDataId;  // +0x84
    short _productLevel;  // +0x88
    int _productTotalAmount;  // +0x8C
    int _productRemainAmount;  // +0x90
    __int64 _registrationTime;  // +0x98
    __int64 _startTime;  // +0xA0
    __int64 _endTime;  // +0xA8
    ::GuildCraft::NormalMaterial _normalMaterial[15];  // +0xB0
    ::GuildCraft::BrandMaterial _brandMaterial[3];  // +0x1A0
    ::GuildCraft::Assentient _assentients[7];  // +0x1E8
    char _normalMaterialsCount;  // +0x1838
    char _brandMaterialsCount;  // +0x1839
    char _assentientsCount;  // +0x183A
    char _assentientsCompletedCount;  // +0x183B
    char _normalMaterialsCompletedCount;  // +0x183C
    char _brandMaterialsCompletedCount;  // +0x183D
    _RTL_SRWLOCK _srwLock;  // +0x1840
};
static_assert(sizeof(GuildCraft::Assentient) == 0x330, "sizeof GuildCraft::Assentient");

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

