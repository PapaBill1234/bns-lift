// Mileage.obj (LobbyDaemon PDB, 2019 + PDB).
// LIFT: classes for deferred functions still have partial PDB layouts.
#pragma once

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

class Mileage
{
public:
    virtual ~Mileage();  // 0x5d8a0
    virtual bool Initialize(MileageConfig const&, long long);  // 0x5d940
    bool FetchFeverTimeList(FragmentPacket*) const;  // 0x5dbf0
protected:
    bool deposit(id128 const&, long long, long long, long long, MileageLimit*, bool);  // 0x5e1a0
};

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

class MileageInterimDepositTimer
{
public:
    MileageInterimDepositTimer(long long);  // 0x60a80
    virtual ~MileageInterimDepositTimer();  // 0x60b20
    virtual bool Tick(long long);  // 0x60d00
};

class MileageManager
{
public:
    virtual ~MileageManager();  // 0x5f480
    bool Initialize(long long);  // 0x5f5a0
    MileageSlot* CreateSlot(id128 const&, unsigned long long);  // 0x5fc30
    virtual void Accept(LobbyMessage*);  // 0x60660
};

class MileageSession
{
public:
    MileageSession(Mileage*, long long);  // 0x606b0
    virtual ~MileageSession();  // 0x60770
    void ReserveInterimDeposit(unsigned long long);  // 0x60800
};

class MileageSlot
{
public:
    MileageSlot(int);  // 0x608d0
    ~MileageSlot();  // 0x60950
};
