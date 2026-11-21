// Mileage.obj (LobbyDaemon PDB, 2019 + PDB).
#include "Mileage.h"
#include "LiftStub.h"
#include "Memory.h"
#include <string.h>

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
bool MileageManager::Initialize(long long)
{
    LIFT_STUB(0x5f5a0);
}

// 0x5fc30
MileageSlot* MileageManager::CreateSlot(id128 const&, unsigned long long)
{
    LIFT_STUB(0x5fc30);
}

// 0x60660
void MileageManager::Accept(LobbyMessage*)
{
    LIFT_STUB(0x60660);
}

// 0x606b0
MileageSession::MileageSession(Mileage*, long long)
{
    LIFT_STUB(0x606b0);
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

// 0x608d0
MileageSlot::MileageSlot(int)
{
    LIFT_STUB(0x608d0);
}

// 0x60950
MileageSlot::~MileageSlot()
{
    LIFT_STUB(0x60950);
}

// 0x60a80
MileageInterimDepositTimer::MileageInterimDepositTimer(long long)
{
    LIFT_STUB(0x60a80);
}

// 0x60b20
MileageInterimDepositTimer::~MileageInterimDepositTimer()
{
    LIFT_STUB(0x60b20);
}

// 0x60d00
bool MileageInterimDepositTimer::Tick(long long)
{
    LIFT_STUB(0x60d00);
}

// 0x61060
bool MileageBatchRetryDeposit::Tick(long long)
{
    LIFT_STUB(0x61060);
}
