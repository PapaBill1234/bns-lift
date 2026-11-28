// contentquota.cpp: contentquota.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "contentquota.h"
#include "pc.h"
#include "Memory.h"
#include "LiftStub.h"

#define CONTENTQUOTA_STLMEMORY_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\StlMemory.h"

#pragma comment(linker, "/INCLUDE:??0ContentQuotaManager@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Top@ContentQuotaPriorityQueue@@QEAAPEAVContentQuota@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x85060
__cdecl ContentQuota::ContentQuota(void)
{
    LIFT_STUB(0x85060);
}

// 0x85160
bool __cdecl ContentQuota::Initialize(::Data::ContentQuotaRecordPtr)
{
    LIFT_STUB(0x85160);
}

// 0x85220
bool __cdecl ContentQuota::InitializeProp(::Pc const *)
{
    LIFT_STUB(0x85220);
}

// 0x85390
bool __cdecl ContentQuota::InitializeProp(::Pc const *, short, __int64, __int64)
{
    LIFT_STUB(0x85390);
}

// 0x85490
void __cdecl ContentQuota::UpdateByAccountContentQuota(::Pc *, short, short, __int64, __int64)
{
    LIFT_STUB(0x85490);
}

// 0x85570
bool __cdecl ContentQuota::UpdateByChangedVersion(::Pc *)
{
    LIFT_STUB(0x85570);
}

// 0x85760
short __cdecl ContentQuota::FetchDb(char *, short) const
{
    LIFT_STUB(0x85760);
}

// 0x857e0
short __cdecl ContentQuota::FetchAll(char *, short) const
{
    LIFT_STUB(0x857e0);
}

// 0x85870
void __cdecl ContentQuota::Recharge(::Pc *)
{
    LIFT_STUB(0x85870);
}

// 0x85a60
void __cdecl ContentQuota::UpdateByCustomValue(::Pc *, short, __int64, __int64)
{
    LIFT_STUB(0x85a60);
}

// 0x85c00
bool __cdecl ContentQuota::IsCharged(void)
{
    LIFT_STUB(0x85c00);
}

// 0x85e00
void __cdecl ContentQuota::UpdateExpireTime(void)
{
    LIFT_STUB(0x85e00);
}

// 0x85fc0
__int64 __cdecl ContentQuota::Consume(::Pc *, __int64)
{
    LIFT_STUB(0x85fc0);
}

// 0x86180
__cdecl ContentQuotaPriorityQueue::~ContentQuotaPriorityQueue(void)
{
    LIFT_STUB(0x86180);
}

// 0x861e0
bool __cdecl ContentQuotaPriorityQueue::Push(::ContentQuota *)
{
    LIFT_STUB(0x861e0);
}

// 0x86300
void __cdecl ContentQuotaPriorityQueue::Clear(void)
{
    LIFT_STUB(0x86300);
}

// 0x86390
__cdecl ContentQuotaManager::ContentQuotaManager(void)
{
    // Partial PDB offsets of ContentQuotaManager:
    //   _contentQuotaList (std::map) +0: _Myhead +8, _Mysize +16
    //   _contentQuotaPQ +32: _quotaPQ.c._Myfirst +40, _Mylast +48, _Myend +56, comp +64
    //   _owner +72
    // The tree node is 48 bytes: _Left +0, _Parent +8, _Right +16, _Color +24, _Isnil +25.
    char *self = reinterpret_cast<char *>(this);
    *reinterpret_cast<unsigned __int64 *>(self + 16) = 0;
    char *node = static_cast<char *>(Memory::_Manager[2]->Alloc(48, CONTENTQUOTA_STLMEMORY_FILE, 60));
    *reinterpret_cast<char **>(self + 8) = node;
    *reinterpret_cast<char **>(node) = node;
    *reinterpret_cast<char **>(*reinterpret_cast<char **>(self + 8) + 8) = *reinterpret_cast<char **>(self + 8);
    *reinterpret_cast<char **>(*reinterpret_cast<char **>(self + 8) + 16) = *reinterpret_cast<char **>(self + 8);
    *(*reinterpret_cast<char **>(self + 8) + 24) = 1;
    *(*reinterpret_cast<char **>(self + 8) + 25) = 1;
    *reinterpret_cast<void **>(self + 40) = nullptr;
    *reinterpret_cast<void **>(self + 48) = nullptr;
    *reinterpret_cast<void **>(self + 56) = nullptr;
    *(self + 64) = 0;
    *reinterpret_cast<void **>(self + 72) = nullptr;
}

// 0x86410
__cdecl ContentQuotaManager::~ContentQuotaManager(void)
{
    LIFT_STUB(0x86410);
}

// 0x86530
int __cdecl ContentQuotaManager::SetDbData(short, char const *, int)
{
    LIFT_STUB(0x86530);
}

// 0x867b0
bool __cdecl ContentQuotaManager::ConfirmAcquire(__int64)
{
    LIFT_STUB(0x867b0);
}

// 0x869c0
::ContentQuota * __cdecl ContentQuotaManager::findEntry(int)
{
    LIFT_STUB(0x869c0);
}

// 0x86a20
::Data::ContentQuotaRecordPtr __cdecl ContentQuotaManager::GetDataByConsumeOrder(::Data::ContentQuotaRecordSubType, ::ConsumeOrder)
{
    LIFT_STUB(0x86a20);
}

// 0x86b70
::ContentQuota * __cdecl ContentQuotaManager::GetContentQuota(::Data::ContentQuotaRecordSubType, ::ConsumeOrder)
{
    LIFT_STUB(0x86b70);
}

// 0x86bb0
void __cdecl ContentQuotaManager::ApplyNewData(void)
{
    LIFT_STUB(0x86bb0);
}

// 0x86d60
void __cdecl ContentQuotaManager::ApplyChangedVersion(void)
{
    LIFT_STUB(0x86d60);
}

// 0x86f30
void __cdecl ContentQuotaManager::ApplyAccountContentQuota(::std::vector< ::AccountContentQuota, ::StlAllocator< ::AccountContentQuota, 2> >)
{
    LIFT_STUB(0x86f30);
}

// 0x870d0
bool __cdecl ContentQuotaManager::AddContentQuotaInList(::Data::ContentQuotaRecordPtr, bool, char const *, short)
{
    LIFT_STUB(0x870d0);
}

// 0x87360
bool __cdecl ContentQuotaManager::AddAccountContentQuotaInList(::Data::ContentQuotaRecordPtr, short, __int64, __int64)
{
    LIFT_STUB(0x87360);
}

// 0x87590
void __cdecl ContentQuotaManager::AddContentQuotaInPQ(::ContentQuota *)
{
    LIFT_STUB(0x87590);
}

// 0x87660
void __cdecl ContentQuotaManager::InitializePQ(void)
{
    LIFT_STUB(0x87660);
}

// 0x876f0
bool __cdecl ContentQuotaManager::IsQuantityEnoughForConsumption(::Data::ContentQuotaRecordSubType, __int64)
{
    LIFT_STUB(0x876f0);
}

// 0x87810
::ErrorCode __cdecl ContentQuotaManager::CheckQuantityForConsumption(::Data::ContentQuotaRecordSubType, __int64)
{
    LIFT_STUB(0x87810);
}

// 0x879d0
bool __cdecl ContentQuotaManager::IsRestricted(::Data::ContentQuotaRecordSubType)
{
    LIFT_STUB(0x879d0);
}

// 0x87ad0
void __cdecl ContentQuotaManager::SetFirstRestriction(::Data::ContentQuotaRecordSubType)
{
    LIFT_STUB(0x87ad0);
}

// 0x87be0
bool __cdecl ContentQuotaManager::CheckContentQuotaExists(::Data::ContentQuotaRecordSubType)
{
    LIFT_STUB(0x87be0);
}

// 0x87c70
__int64 __cdecl ContentQuotaManager::Consume(::Data::ContentQuotaRecordSubType, __int64)
{
    LIFT_STUB(0x87c70);
}

// 0x87e00
void __cdecl ContentQuotaManager::Recharge(::ContentQuota *)
{
    LIFT_STUB(0x87e00);
}

// 0x87ea0
void __cdecl ContentQuotaManager::ProcessExpiredQuotaInPQ(void)
{
    LIFT_STUB(0x87ea0);
}

// 0x87f80
void __cdecl ContentQuotaManager::ForceQuotaToBeExpired(int)
{
    LIFT_STUB(0x87f80);
}

// 0x880c0
bool __cdecl ContentQuotaManager::SendPropertyList(int, ...)
{
    LIFT_STUB(0x880c0);
}

// 0x88360
bool __cdecl ContentQuotaManager::SendPropertyList(void)
{
    LIFT_STUB(0x88360);
}

// 0x88660
bool __cdecl ContentQuotaManager::SendAllPropertyList(char)
{
    LIFT_STUB(0x88660);
}

// 0x88950
short __cdecl ContentQuotaManager::FillNotifyPacketBody(::ContentQuota *, char *, short)
{
    LIFT_STUB(0x88950);
}

// 0x88a40
void __cdecl ContentQuotaManager::RechargeVitality(::ContentQuota *)
{
    LIFT_STUB(0x88a40);
}

// 0x88e80
::ContentQuota * __cdecl ContentQuotaManager::GetVitalityQuota(::VitalityType)
{
    LIFT_STUB(0x88e80);
}

// 0x88f80
void __cdecl ContentQuotaManager::FetchAllAccountContentQuota(::std::vector< ::AccountContentQuota, ::StlAllocator< ::AccountContentQuota, 2> > &)
{
    LIFT_STUB(0x88f80);
}

// 0x3fb920
::ContentQuota * __cdecl ContentQuotaPriorityQueue::Top(void)
{
    // Partial PDB offsets: _quotaPQ.c._Myfirst +8, _Mylast +16.
    ::ContentQuota *const *first = *reinterpret_cast< ::ContentQuota *const *const *>(reinterpret_cast<const char *>(this) + 8);
    ::ContentQuota *const *last = *reinterpret_cast< ::ContentQuota *const *const *>(reinterpret_cast<const char *>(this) + 16);
    if (first == last)
        return nullptr;
    return *first;
}
