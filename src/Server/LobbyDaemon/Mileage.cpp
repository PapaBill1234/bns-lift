// Mileage.obj (LobbyDaemon PDB, 2019 + PDB).
// LIFT: the original Memory.h (line 181) gives its own placement array new and delete. This stops <new> from giving them.
#define __PLACEMENT_VEC_NEW_INLINE
#include "PlacementNew.h"
#include "Mileage.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "Daemon.h"
#include "LobbyDB.h"
#include "MembershipMileage.h"
#include "PcCafeMileage.h"
#include "LiftStub.h"
#include "LobbyMessage.h"
#include "Log.h"
#include "Memory.h"
#include <string.h>
#include <time.h>
#if defined(__clang__)
#include "crt_cpp_overload.h"
#endif

// PDB S_GTHREAD32 (void*). Defined in CliSessionTable.cpp.
extern __declspec(thread) void* __delv_buf__;

// LIFT: inlined in MileageManager::Initialize 0x5f5a0. Same form as CliSessionTable.cpp and LobbyJob.cpp.
inline void __cdecl operator delete[](void* p)
{
    __delv_buf__ = p;
}

inline void* __cdecl operator new[](size_t, void* buf) throw()
{
    return buf;
}

inline void __cdecl operator delete[](void*, void*)
{
    Log::Write(Log::LT_ERROR,
               L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Memory.h",
               181, L"== CRASH == [memory], DO NOT USE THIS DEL OPERATOR");
    AlertSender::Write(
        L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Memory.h",
        181, L"== CRASH == [memory], DO NOT USE THIS DEL OPERATOR");
}

#pragma comment(linker, "/INCLUDE:??$swprintf_s@$0CAB@@@YAHAEAY0CAB@_WPEB_WZZ")  // LIFT: keep until the caller is lifted (0x614d0)
template int __cdecl swprintf_s<513>(wchar_t (&)[513], wchar_t const*, ...);

// 0x5d370
LobbyMessageAcceptor::~LobbyMessageAcceptor()
{
}

// 0x5d390
bool MileageInfo::check() const
{
    if (id != 0 && policyId > 0)
    {
        if (effectiveStartTime < effectiveEndTime && effectiveStartTime > 0)
        {
            if (effectiveStartTime < accumulateEndTime && accumulateEndTime > 0)
            {
                return accumulateFrequencyType > 0 && accumulateFrequencyType < 3 &&
                    accumulateFrequency > 0 && virtualCurrencyId > 0 &&
                    virtualCurrencyAmount >= 0 && virtualCurrencyExpireTime > 0 &&
                    accumulateMinuteLimitPerDay >= 0;
            }
        }
    }
    return false;
}

// 0x5d410
MileageConfig::MileageConfig()
    : policyConditions(nullptr), policyConditionCount(0), fevers(nullptr), feverCount(0)
{
    memset(&mileage, 0, sizeof(mileage));
    memset(&policy, 0, sizeof(policy));
}

// 0x5d460
MileageConfig::~MileageConfig()
{
    if (policyConditions != nullptr)
    {
        for (int i = 0; i < policyConditionCount; ++i)
        {
            if (policyConditions[i] != nullptr)
            {
                Memory::_Manager[Memory::DYNAMIC]->Free(policyConditions[i], L"Mileage.cpp", 103);
                policyConditions[i] = nullptr;
            }
        }
        Memory::_Manager[Memory::DYNAMIC]->Free(policyConditions, L"Mileage.cpp", 104);
        policyConditions = nullptr;
    }
    if (fevers != nullptr)
    {
        for (int i = 0; i < feverCount; ++i)
        {
            if (fevers[i] != nullptr)
            {
                Memory::_Manager[Memory::DYNAMIC]->Free(fevers[i], L"Mileage.cpp", 109);
                fevers[i] = nullptr;
            }
        }
        Memory::_Manager[Memory::DYNAMIC]->Free(fevers, L"Mileage.cpp", 110);
        fevers = nullptr;
    }
}

// 0x5d760
bool MileageConfig::Check() const
{
    if (!mileage.check() || policy.id <= 0 || policy.mileageType <= 0 || policy.mileageType >= 3)
        return false;

    // LIFT: Reject incomplete arrays before 0x5d940 copies and sorts the records.
    if (policyConditionCount < 0 || (policyConditionCount > 0 && policyConditions == nullptr))
        return false;
    for (int i = 0; i < policyConditionCount; ++i)
    {
        MileagePolicyCondition const* condition = policyConditions[i];
        if (condition == nullptr || condition->type <= 0 || condition->type >= 4)
            return false;
    }

    if (feverCount < 0 || (feverCount > 0 && fevers == nullptr))
        return false;
    for (int i = 0; i < feverCount; ++i)
    {
        MileageFeverTimeInfo const* fever = fevers[i];
        if (fever == nullptr || fever->mileageId == 0 ||
            fever->effectiveStartTime >= fever->effectiveEndTime || fever->repeatStartTime >= 86400 ||
            fever->virtualCurrencyAmount <= 0)
            return false;

        char repeatType = fever->repeatType;
        if (repeatType <= 0 || repeatType >= 4 ||
            (repeatType >= 2 && (fever->repeatStartTime < 0 || fever->repeatDuration <= 0)))
            return false;
        if (repeatType >= 3 && fever->daysOfWeek == 0)
            return false;
    }
    return true;
}

// 0x5d8a0
Mileage::~Mileage()
{
    LIFT_STUB(0x5d8a0);
}

// 0x5d940
bool Mileage::Initialize(MileageConfig const&, long long)
{
    LIFT_STUB(0x5d940);
}

// 0x5dbf0
bool Mileage::FetchFeverTimeList(FragmentPacket*) const
{
    LIFT_STUB(0x5dbf0);
}

// 0x5e1a0
bool Mileage::deposit(id128 const&, long long, long long, long long, MileageLimit*, bool)
{
    LIFT_STUB(0x5e1a0);
}

// 0x5f480
MileageManager::~MileageManager()
{
    LIFT_STUB(0x5f480);
}

// 0x5f5a0
bool MileageManager::Initialize(long long scheduleTo)
{
    if (scheduleTo <= 0)
    {
        Log::Write(Log::LT_ERROR, L"Mileage.cpp", 966,
            L"[mileage], init mileage manager fail; invalid parameter, schedule-to:%d", scheduleTo);
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }
    MileageConfig* configs = nullptr;
    MileageInfo** mileageList = nullptr;
    int mileageCount = 0;
    int dbrtn = 0;
    if (!LobbyDB::LoadMileage(dbrtn, mileageList, mileageCount))
    {
        Log::Write(Log::LT_ERROR, L"Mileage.cpp", 979,
            L"[mileage], init mileage manager fail; load mileage fail, dbrtn:%d", dbrtn);
        TLobbyError = LOBERR_DB_FAIL;
        return false;
    }
    bool result = false;
    if (mileageList != nullptr)
    {
        // The count is in the 8 bytes in front of the array.
        configs = new (Memory::_Manager[2]->Alloc(sizeof(MileageConfig) * mileageCount + 8, L"Mileage.cpp", 985))
            MileageConfig[mileageCount];
        // BUG: 0x5f5a0 does not free mileageList and its records. The lift keeps the original behavior.
        for (int i = 0; i < mileageCount; ++i)
            memcpy(&configs[i].mileage, mileageList[i], sizeof(MileageInfo));
        _limitedIdList = static_cast<int*>(
            Memory::_Manager[2]->AllocZero(sizeof(int) * mileageCount, L"Mileage.cpp", 989));
        _limitedSlotList = static_cast<int*>(
            Memory::_Manager[2]->AllocZero(sizeof(int) * mileageCount, L"Mileage.cpp", 990));
        _limitedCount = 0;
        for (int i = 0; i < mileageCount; ++i)
        {
            MileageConfig& config = configs[i];
            dbrtn = 0;
            if (!LobbyDB::LoadMileagePolicy(dbrtn, config.mileage.policyId, config.policy, config.policyConditions,
                                            config.policyConditionCount) ||
                config.policy.id <= 0)
            {
                Log::Write(Log::LT_ERROR, L"Mileage.cpp", 1008,
                    L"[mileage], init mileage manager fail; load policy fail, dbrtn:%d, mileage-id:%d, policy-id:%d",
                    dbrtn, config.mileage.id, config.mileage.policyId);
                TLobbyError = LOBERR_DB_FAIL;
                goto cleanup;
            }
            dbrtn = 0;
            if (!LobbyDB::LoadMileageFeverTime(dbrtn, config.mileage.id, scheduleTo, config.fevers, config.feverCount))
            {
                Log::Write(Log::LT_ERROR, L"Mileage.cpp", 1023,
                    L"[mileage], init mileage manager fail; load fever time fail, dbrtn:%d, mileage-id:%d", dbrtn,
                    config.mileage.id);
                TLobbyError = LOBERR_DB_FAIL;
                goto cleanup;
            }
            Mileage* mileage;
            if (config.policy.mileageType == 1)
            {
                void* mem = Memory::_Manager[2]->Alloc(sizeof(PcCafeMileage), L"Mileage.cpp", 1033);
                mileage = mem != nullptr ? ::new (mem) PcCafeMileage(i) : nullptr;
            }
            else if (config.policy.mileageType == 2)
            {
                void* mem = Memory::_Manager[2]->Alloc(sizeof(MembershipMileage), L"Mileage.cpp", 1036);
                mileage = mem != nullptr ? ::new (mem) MembershipMileage(i) : nullptr;
            }
            else
            {
                Log::Write(Log::LT_ERROR, L"Mileage.cpp", 1042,
                    L"== CRASH == [mileage], init mileage manager fail; invalid mileage type, mileage-id:%d, mileage-type:%d",
                    config.mileage.id, config.policy.mileageType);
                AlertSender::Write(L"Mileage.cpp", 1042,
                    L"== CRASH == [mileage], init mileage manager fail; invalid mileage type, mileage-id:%d, mileage-type:%d",
                    config.mileage.id, config.policy.mileageType);
                goto cleanup;
            }
            if (!mileage->Initialize(config, scheduleTo))
            {
                delete mileage;
                Memory::_Manager[2]->Free(mileage, L"Mileage.cpp", 1047);
                goto cleanup;
            }
            if (config.mileage.accumulateMinuteLimitPerDay > 0)
            {
                _limitedIdList[_limitedCount] = config.mileage.id;
                _limitedSlotList[_limitedCount++] = i;
            }
            _mileages.push_back(mileage);
        }
    }
    Log::Write(Log::LT_DEBUG, L"Mileage.cpp", 1064, L"[mileage], init mileage manager ok, mileage-count:%d",
        mileageCount);
    result = true;
cleanup:
    if (configs != nullptr)
    {
        delete[] configs;
        Memory::_Manager[2]->Free(__delv_buf__, L"Mileage.cpp", 1068);
    }
    return result;
}

// 0x5fc30
MileageSlot* MileageManager::CreateSlot(id128 const&, unsigned long long)
{
    LIFT_STUB(0x5fc30);
}

#pragma comment(linker, "/INCLUDE:?Accept@MileageManager@@UEAAXPEAVLobbyMessage@@@Z")  // LIFT: keep until the caller is lifted (0x60660)
void MileageManager::Accept(LobbyMessage* message)
{
    for (std::vector<Mileage*, StlAllocator<Mileage*, 2> >::iterator it = _mileages.begin(); it != _mileages.end(); ++it)
    {
        if (*it != nullptr)
            (*it)->Accept(message);
    }
}

// LIFT: The PDB has no name for the counter at 0x209b40. The ctor at 0x606b0 owns it.
static long long volatile mileageSessionId;

#pragma comment(linker, "/INCLUDE:??0MileageSession@@QEAA@PEAVMileage@@_J@Z")  // LIFT: keep until the caller is lifted (0x606b0)
MileageSession::MileageSession(Mileage* owner, long long startTime)
{
    unsigned long long id = _InterlockedIncrement64(&mileageSessionId);
    if (id == 0)
    {
        id = _InterlockedIncrement64(&mileageSessionId);
        Log::Write(Log::LT_ERROR, L"Mileage.cpp", 1256, L"[mileage], session id overflow");
    }
    _owner = owner;
    _startTime = startTime;
    _id = id;
    _timerNode = nullptr;
}

// 0x60770
MileageSession::~MileageSession()
{
    LIFT_STUB(0x60770);
}

// 0x60800
void MileageSession::ReserveInterimDeposit(unsigned long long)
{
    LIFT_STUB(0x60800);
}

#pragma comment(linker, "/INCLUDE:??0MileageSlot@@QEAA@H@Z")  // LIFT: keep until the caller is lifted (0x608d0)
MileageSlot::MileageSlot(int size) : _limits(nullptr), _sessions(nullptr), _size(0)
{
    unsigned long long bytes = sizeof(void*) * static_cast<unsigned long long>(size);
    _limits = static_cast<MileageLimit**>(Memory::_Manager[Memory::DYNAMIC]->AllocZero(bytes, L"Mileage.cpp", 1304));
    MileageSession** sessions = static_cast<MileageSession**>(
        Memory::_Manager[Memory::DYNAMIC]->AllocZero(bytes, L"Mileage.cpp", 1305));
    _size = size;
    _sessions = sessions;
}

#pragma comment(linker, "/INCLUDE:??1MileageSlot@@QEAA@XZ")  // LIFT: keep until the caller is lifted (0x60950)
MileageSlot::~MileageSlot()
{
    if (_limits != nullptr)
    {
        for (int i = 0; i < _size; ++i)
        {
            if (_limits[i] != nullptr)
            {
                delete _limits[i];
                Memory::_Manager[Memory::DYNAMIC]->Free(_limits[i], L"Mileage.cpp", 1314);
                _limits[i] = nullptr;
            }
        }
        Memory::_Manager[Memory::DYNAMIC]->Free(_limits, L"Mileage.cpp", 1316);
        _limits = nullptr;
    }
    if (_sessions != nullptr)
    {
        for (int i = 0; i < _size; ++i)
        {
            if (_sessions[i] != nullptr)
            {
                delete _sessions[i];
                Memory::_Manager[Memory::DYNAMIC]->Free(_sessions[i], L"Mileage.cpp", 1321);
                _sessions[i] = nullptr;
            }
        }
        Memory::_Manager[Memory::DYNAMIC]->Free(_sessions, L"Mileage.cpp", 1323);
        _sessions = nullptr;
    }
}

#pragma comment(linker, "/INCLUDE:??0MileageInterimDepositTimer@@QEAA@_J@Z")  // LIFT: keep until the caller is lifted (0x60a80)
MileageInterimDepositTimer::MileageInterimDepositTimer(long long period) : _period(period)
{
}

// 0x60b20
MileageInterimDepositTimer::~MileageInterimDepositTimer()
{
    RefCntListNode* node;
    while ((node = _sessions.Popfront()) != nullptr)
        node->removeReferenceCount(L"Mileage.cpp", 1376);
}

// 0x60be0
MileageInterimDepositTimer::Node* MileageInterimDepositTimer::Register(unsigned long long, unsigned long long)
{
    LIFT_STUB(0x60be0);
}

// 0x60d00
bool MileageInterimDepositTimer::Tick(long long elapsed)
{
    RefCntList expiredlist;
    _lock.Enter();
    for (RefCntListNode* head = _sessions.Begin(); head != nullptr; head = _sessions.Begin())
    {
        Node* node = static_cast<Node*>(head);
        if (!node->IsExpired(elapsed))
            break;
        _sessions.Popfront();
        expiredlist.Pushback(node);
        node->removeReferenceCount(L"Mileage.cpp", 1421);
    }
    _lock.Leave();
    if (expiredlist.Size() > 0)
    {
        long long expiredTime = _time64(nullptr);
        for (RefCntListNode* head = expiredlist.Popfront(); head != nullptr; head = expiredlist.Popfront())
        {
            Node* node = static_cast<Node*>(head);
            node->Expire(expiredTime);
            node->removeReferenceCount(L"Mileage.cpp", 1432);
        }
    }
    return true;
}

// 0x60f20
void MileageInterimDepositTimer::Node::Expire(long long)
{
    LIFT_STUB(0x60f20);
}

// 0x61060
bool MileageBatchRetryDeposit::Tick(long long)
{
    LIFT_STUB(0x61060);
}
