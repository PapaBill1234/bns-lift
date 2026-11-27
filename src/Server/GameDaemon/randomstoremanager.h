// randomstoremanager.h: randomstoremanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class RandomStoreEntry
{
public:
    enum DrawProbApplyType {};
public:
    short const __cdecl FetchDbByCurrentSlotCount(char *const, short) const;  // 0x1acbc0
    void __cdecl SetPremiumDrawCountForDebug(int);  // 0x1acd70
    __int64 const __cdecl DrawItemGroup(::RandomStoreEntry::DrawProbApplyType);  // 0x1ace60
    void __cdecl FillSlot(char, __int64, __int64);  // 0x1ad3d0
    void __cdecl DecreaseFreeDrawCount(void);  // 0x1adaf0
    void __cdecl ResetPurchaseIndex(char);  // 0x1adbc0
    void __cdecl SetPurchaseSlotIndex(char, char);  // 0x1adcb0
    void __cdecl ExpandSlot(void);  // 0x1addd0
    void __cdecl InitProperty(char);  // 0x1adea0
    bool __cdecl IsDailyInitialized(void) const;  // 0x1adf40
    void __cdecl DailyReset(void);  // 0x1ae0b0
    void __cdecl ClearDraw(char);  // 0x1ae300
    void __cdecl AddDrawRewardAccumulateCount(int);  // 0x1ae3c0
};

class RandomStoreManager
{
public:
    __cdecl ~RandomStoreManager(void);  // 0x1ae4b0
    void __cdecl InitializeProperty(void);  // 0x1ae530
    int __cdecl SetDbData(short, char const *const, int);  // 0x1ae640
    void __cdecl SendLatestRandomStoreList(bool);  // 0x1aeae0
};

