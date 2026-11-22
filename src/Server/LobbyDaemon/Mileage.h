// Mileage.obj (LobbyDaemon PDB, 2019 + PDB).
// LIFT: classes for deferred functions still have partial PDB layouts.
#pragma once

#include <stddef.h>
#include <vector>
#include "LobbyTick.h"
#include "Lock.h"
#include "StlMemory.h"

class CliSession;
class FragmentPacket;
class LobbyMessage;
class Mileage;
class MileageConfig;
class MileageLimit;
class MileageSlot;
union id128;

class LobbyMessageAcceptor
{
public:
    virtual ~LobbyMessageAcceptor();  // 0x5d370
    virtual void Accept(LobbyMessage*) = 0;
};

template<class T> struct Section
{
    T start;
    T end;

    template<class U, template<class, class> class Container, class Allocator>
    static void Intersect(Container<Section<U>, Allocator> const&,
        Container<Section<U>, Allocator> const&, Container<Section<U>, Allocator>&);  // 0x5d240
};
static_assert(sizeof(Section<long long>) == 0x10, "sizeof Section<__int64>");

class MileageBatchRetryDeposit
{
public:
    virtual bool Tick(long long);  // 0x61060
};

struct MileageInfo
{
    bool check() const;  // 0x5d390
    int id;
    wchar_t name[201];
    wchar_t description[2001];
    int policyId;
    long long effectiveStartTime;
    long long effectiveEndTime;
    long long accumulateEndTime;
    char accumulateFrequencyType;
    char accumulateFrequency;
    short virtualCurrencyId;
    long long virtualCurrencyAmount;
    long long virtualCurrencyExpireTime;
    short accumulateMinuteLimitPerDay;
    long accumulateLimitStandardHour;
};
static_assert(sizeof(MileageInfo) == 0x1178, "sizeof MileageInfo");

struct MileagePolicy
{
    int id;
    char mileageType;
    wchar_t name[201];
};
static_assert(sizeof(MileagePolicy) == 0x198, "sizeof MileagePolicy");

struct MileagePolicyCondition
{
    char type;
    wchar_t value[51];
};
static_assert(sizeof(MileagePolicyCondition) == 0x68, "sizeof MileagePolicyCondition");

struct MileageFeverTimeInfo
{
    int id;
    int mileageId;
    wchar_t name[201];
    long long effectiveStartTime;
    long long effectiveEndTime;
    long long virtualCurrencyAmount;
    char repeatType;
    long long repeatStartTime;
    int repeatDuration;
    char daysOfWeek;
};
static_assert(sizeof(MileageFeverTimeInfo) == 0x1d0, "sizeof MileageFeverTimeInfo");

class MileageConfig
{
public:
    MileageConfig();  // 0x5d410
    ~MileageConfig();  // 0x5d460
    bool Check() const;  // 0x5d760

    MileageInfo mileage;
    MileagePolicy policy;
    MileagePolicyCondition** policyConditions;
    int policyConditionCount;
    MileageFeverTimeInfo** fevers;
    int feverCount;

private:
    // LIFT: Prevent shallow copies until the deep copy at 0x5d5a0 is available.
    MileageConfig(MileageConfig const&);
    MileageConfig& operator=(MileageConfig const&);
};
static_assert(sizeof(MileageConfig) == 0x1330, "sizeof MileageConfig");

class Mileage : public LobbyMessageAcceptor
{
public:
    class FeverTime
    {
    public:
        long long _pointsInUnitTime;
        Section<long long> _effectiveSectionInUnitTime;
        Section<long long>* _sectionsInUnitTime;
        int _countofSectionsInUnitTime;
    };

    virtual ~Mileage();  // 0x5d8a0
    virtual bool Initialize(MileageConfig const&, long long);  // 0x5d940
    virtual bool Start(CliSession*, long long) = 0;
    virtual bool Stop(CliSession*, long long, long long*) = 0;
    bool FetchFeverTimeList(FragmentPacket*) const;  // 0x5dbf0
protected:
    bool deposit(id128 const&, long long, long long, long long, MileageLimit*, bool);  // 0x5e1a0

public:
    int _slotId;
    long long _unitTime;
    MileageConfig _config;
    Section<long long> _effectiveAccumulateSection;
    FeverTime* _fevers;
    int _feverCount;
};
static_assert(sizeof(Mileage) == 0x1368, "sizeof Mileage");
static_assert(offsetof(Mileage, _config) == 0x18, "Mileage::_config");
static_assert(sizeof(Mileage::FeverTime) == 0x28, "sizeof Mileage::FeverTime");

class MileageLimit
{
public:
    virtual ~MileageLimit() {}
    virtual long long Fillin(Section<long long> const&, long long);  // 0x5f2c0
    virtual long long getBoundary(long long) = 0;

    // LIFT: The original delete does not free storage. The caller frees it at 0x60950.
    static void operator delete(void*) {}

    long long const _limit;
    long long _amount;
    long long _boundary;
};
static_assert(sizeof(MileageLimit) == 0x20, "sizeof MileageLimit");

class MileageInterimDepositTimer : public LobbyTick::Listener
{
public:
    class Node : public RefCntListNode
    {
    public:
        // LIFT: The PDB ctor is inline in Register (0x60be0).
        Node(unsigned long long clikey, unsigned long long sessionId, long long expire)
            : _clikey(clikey), _sessionId(sessionId), _expire(expire) {}

        // LIFT: The PDB method is inline in Tick (0x60d00).
        bool IsExpired(long long elapsed) const
        {
            return static_cast<long long>(static_cast<unsigned long long>(elapsed) - _expire) >= 0;
        }

        void Expire(long long);  // 0x60f20

    private:
        unsigned long long _clikey;
        unsigned long long _sessionId;
        long long _expire;
    };
    static_assert(sizeof(Node) == 0x48, "sizeof MileageInterimDepositTimer::Node");

    MileageInterimDepositTimer(long long);  // 0x60a80
    virtual ~MileageInterimDepositTimer();  // 0x60b20
    Node* Register(unsigned long long, unsigned long long);  // 0x60be0
    virtual bool Tick(long long);  // 0x60d00

private:
    CriticalSection _lock;
    long long _period;
    RefCntList _sessions;
};
static_assert(sizeof(MileageInterimDepositTimer) == 0x80, "sizeof MileageInterimDepositTimer");

class MileageManager : public LobbyMessageAcceptor
{
public:
    virtual ~MileageManager();  // 0x5f480
    bool Initialize(long long);  // 0x5f5a0
    MileageSlot* CreateSlot(id128 const&, unsigned long long);  // 0x5fc30
    virtual void Accept(LobbyMessage*);  // 0x60660

private:
    std::vector<Mileage*> _mileages;
    int* _limitedIdList;
    int* _limitedSlotList;
    int _limitedCount;
};
static_assert(sizeof(MileageManager) == 0x40, "sizeof MileageManager");

class MileageSession
{
public:
    MileageSession(Mileage*, long long);  // 0x606b0
    virtual ~MileageSession();  // 0x60770
    void ReserveInterimDeposit(unsigned long long);  // 0x60800

    // LIFT: The original delete does not free storage. The caller frees it at 0x60950.
    static void operator delete(void*) {}

protected:
    unsigned long long _id;
    Mileage* _owner;
    long long _startTime;

private:
    MileageInterimDepositTimer::Node* _timerNode;
};
static_assert(sizeof(MileageSession) == 0x28, "sizeof MileageSession");

class MileageSlot
{
public:
    MileageSlot(int);  // 0x608d0
    ~MileageSlot();  // 0x60950

    MileageLimit** _limits;
    MileageSession** _sessions;
    int _size;
};
static_assert(sizeof(MileageSlot) == 0x18, "sizeof MileageSlot");
