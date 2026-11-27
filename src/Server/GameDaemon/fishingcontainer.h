// fishingcontainer.h: fishingcontainer.cpp, fishingcontainer.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class FishingContainer
{
public:
    __cdecl ~FishingContainer(void);  // 0xbb480
    int __cdecl SetDbList(short, char const *, int);  // 0xbb610
    void __cdecl SendFishingList(void);  // 0xbbac0
private:
    void __cdecl notifyAcquire(::FishingEntry const *);  // 0xbbd80
    void __cdecl notifyChange(::FishingEntry const *);  // 0xbbf40
    ::FishingEntry * __cdecl getEntry(short);  // 0xbc100
    bool __cdecl addEntry(::FishingEntry *);  // 0xbc240
    bool __cdecl acquire(::Data::FishRecordPtr, int);  // 0xbc4b0
    bool __cdecl update(::FishingEntry *, int, ::FishInfoStatus &);  // 0xbc7a0
    void __cdecl writeGameLog(short, int, int);  // 0xbc860
public:
    bool __cdecl UpdateFishingInfo(::Data::FishRecordPtr, int, ::FishInfoStatus &);  // 0xbc9e0
    bool __cdecl ConfirmAcquire(short);  // 0xbcae0
};

class FishingEntry
{
public:
    __cdecl FishingEntry(void);  // 0x97090
    bool __cdecl Initialize(::Pc *const, ::Data::FishRecordPtr);  // 0xbae40
    bool __cdecl Initialize(::Pc *const, ::Data::FishRecordPtr, int);  // 0xbaec0
    short __cdecl FetchAll(char *, short) const;  // 0xbaf70
    short __cdecl FetchDb(char *, short) const;  // 0xbb030
    bool __cdecl IncreaseFishCount(int);  // 0xbb1c0
};

