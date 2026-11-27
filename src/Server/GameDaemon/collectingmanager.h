// collectingmanager.h: collectingmanager.cpp, collectingmanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class CollectingEntry
{
public:
    struct CollectingGameLogInfo {};
public:
    __cdecl CollectingEntry(::Pc *const, ::Data::CollectingRecordPtr);  // 0x277b0
    virtual __cdecl ~CollectingEntry(void);  // 0x814b0
    short __cdecl FetchAll(char *, short) const;  // 0x81540
    short __cdecl FetchDb(char *, short) const;  // 0x81600
    bool __cdecl FetchXmlData(wchar_t *, short) const;  // 0x81780
    bool __cdecl SetSyncContext(::SyncContext &);  // 0x819b0
    bool __cdecl GetCollectingPropertyTransaction(::PropertyTransactionSyncData &);  // 0x81ab0
};

class CollectingContainer
{
public:
    struct CollectingOrder {};
public:
    __cdecl ~CollectingContainer(void);  // 0x81c50
    int __cdecl SetDbList(short, char const *, int);  // 0x81d20
    void __cdecl SendCollectingList(void);  // 0x82200
private:
    void __cdecl notifyAcquire(::CollectingEntry const *);  // 0x82470
    ::CollectingEntry * __cdecl getCollectingByIndex(short, int, int);  // 0x82630
    bool __cdecl addCollecting(::CollectingEntry *, int &);  // 0x82840
    bool __cdecl checkItemEquipFilter(::Data::ItemRecordPtr, int);  // 0x82aa0
    bool __cdecl checkClosetCollectingItem(::Data::CollectingRecordClosetPtr, short, ::CollectingContainer::CollectingOrder *const, ::CollectingEntry::CollectingGameLogInfo &);  // 0x82cb0
public:
    ::GameFailReason __cdecl TryToCompleteClosetCollecting(int, short, ::CollectingContainer::CollectingOrder *const);  // 0x837a0
    ::GameFailReason __cdecl CompleteClosetCollectingOk(::CompleteClosetCollectingOkParam &);  // 0x84030
    void __cdecl CompleteClosetCollectingFail(::CompleteClosetCollectingFailParam &);  // 0x84a10
    int __cdecl GetClosetCollectingGrade(void);  // 0x84ee0
    bool __cdecl CheckEquipCharacteristics(::Data::CollectingRecordPtr const &);  // 0x84fb0
};

