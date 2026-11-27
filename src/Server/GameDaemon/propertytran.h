// propertytran.h: propertytran.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class PropertyTransactionSyncFetch
{
public:
    struct ItemData {};
    struct SyncItem {};
public:
    bool __cdecl FetchSyncList(::FragmentPacket &);  // 0x19f5e0
    bool __cdecl FetchSyncListEx(::FragmentPacket &);  // 0x19f770
    bool __cdecl FetchSyncListWithSyncCodeInsert(::FragmentPacket &, bool const *const);  // 0x19f8d0
    bool __cdecl FetchItemList(::FragmentPacket &);  // 0x19fa30
    bool __cdecl FetchBrandItemList(::FragmentPacket &);  // 0x19fc60
private:
    bool __cdecl fetchSyncMoneyData(::FragmentPacket &);  // 0x19fdc0
    bool __cdecl fetchSyncItemData(::FragmentPacket &, int, bool, unsigned __int64);  // 0x19ff70
};

class PropertyTransactionSyncFetchEx
{
public:
    __cdecl ~PropertyTransactionSyncFetchEx(void);  // 0x1a0720
    bool __cdecl AddSyncData(::PropertyTransactionSyncData const *);  // 0x1a07f0
    bool __cdecl FetchSyncList(::FragmentPacket &);  // 0x1a08d0
private:
    bool __cdecl fetchSyncItemData(::FragmentPacket &);  // 0x1a0970
};

