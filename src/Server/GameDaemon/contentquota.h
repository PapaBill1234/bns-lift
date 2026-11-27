// contentquota.h: contentquota.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ContentQuota
{
public:
    __cdecl ContentQuota(void);  // 0x85060
    bool __cdecl Initialize(::Data::ContentQuotaRecordPtr);  // 0x85160
    bool __cdecl InitializeProp(::Pc const *);  // 0x85220
    bool __cdecl InitializeProp(::Pc const *, short, __int64, __int64);  // 0x85390
    void __cdecl UpdateByAccountContentQuota(::Pc *, short, short, __int64, __int64);  // 0x85490
    bool __cdecl UpdateByChangedVersion(::Pc *);  // 0x85570
    short __cdecl FetchDb(char *, short) const;  // 0x85760
    short __cdecl FetchAll(char *, short) const;  // 0x857e0
    void __cdecl Recharge(::Pc *);  // 0x85870
    void __cdecl UpdateByCustomValue(::Pc *, short, __int64, __int64);  // 0x85a60
    bool __cdecl IsCharged(void);  // 0x85c00
    void __cdecl UpdateExpireTime(void);  // 0x85e00
    __int64 __cdecl Consume(::Pc *, __int64);  // 0x85fc0
};

class ContentQuotaManager
{
public:
    __cdecl ContentQuotaManager(void);  // 0x86390
    __cdecl ~ContentQuotaManager(void);  // 0x86410
    int __cdecl SetDbData(short, char const *, int);  // 0x86530
    bool __cdecl ConfirmAcquire(__int64);  // 0x867b0
    ::ContentQuota * __cdecl findEntry(int);  // 0x869c0
    ::Data::ContentQuotaRecordPtr __cdecl GetDataByConsumeOrder(::Data::ContentQuotaRecordSubType, ::ConsumeOrder);  // 0x86a20
    ::ContentQuota * __cdecl GetContentQuota(::Data::ContentQuotaRecordSubType, ::ConsumeOrder);  // 0x86b70
    void __cdecl ApplyNewData(void);  // 0x86bb0
    void __cdecl ApplyChangedVersion(void);  // 0x86d60
    void __cdecl ApplyAccountContentQuota(::std::vector< ::AccountContentQuota, ::StlAllocator< ::AccountContentQuota, 2> >);  // 0x86f30
    bool __cdecl AddContentQuotaInList(::Data::ContentQuotaRecordPtr, bool, char const *, short);  // 0x870d0
    bool __cdecl AddAccountContentQuotaInList(::Data::ContentQuotaRecordPtr, short, __int64, __int64);  // 0x87360
    void __cdecl AddContentQuotaInPQ(::ContentQuota *);  // 0x87590
    void __cdecl InitializePQ(void);  // 0x87660
    bool __cdecl IsQuantityEnoughForConsumption(::Data::ContentQuotaRecordSubType, __int64);  // 0x876f0
    ::ErrorCode __cdecl CheckQuantityForConsumption(::Data::ContentQuotaRecordSubType, __int64);  // 0x87810
    bool __cdecl IsRestricted(::Data::ContentQuotaRecordSubType);  // 0x879d0
    void __cdecl SetFirstRestriction(::Data::ContentQuotaRecordSubType);  // 0x87ad0
    bool __cdecl CheckContentQuotaExists(::Data::ContentQuotaRecordSubType);  // 0x87be0
    __int64 __cdecl Consume(::Data::ContentQuotaRecordSubType, __int64);  // 0x87c70
    void __cdecl Recharge(::ContentQuota *);  // 0x87e00
    void __cdecl ProcessExpiredQuotaInPQ(void);  // 0x87ea0
    void __cdecl ForceQuotaToBeExpired(int);  // 0x87f80
    bool __cdecl SendPropertyList(int, ...);  // 0x880c0
    bool __cdecl SendPropertyList(void);  // 0x88360
    bool __cdecl SendAllPropertyList(char);  // 0x88660
    short __cdecl FillNotifyPacketBody(::ContentQuota *, char *, short);  // 0x88950
    void __cdecl RechargeVitality(::ContentQuota *);  // 0x88a40
    ::ContentQuota * __cdecl GetVitalityQuota(::VitalityType);  // 0x88e80
    void __cdecl FetchAllAccountContentQuota(::std::vector< ::AccountContentQuota, ::StlAllocator< ::AccountContentQuota, 2> > &);  // 0x88f80
};

class ContentQuotaPriorityQueue
{
public:
    __cdecl ~ContentQuotaPriorityQueue(void);  // 0x86180
    bool __cdecl Push(::ContentQuota *);  // 0x861e0
    void __cdecl Clear(void);  // 0x86300
    ::ContentQuota * __cdecl Top(void);  // 0x3fb920
};

