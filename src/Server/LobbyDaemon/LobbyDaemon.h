// LobbyDaemon.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include <vector>
#include "Daemon.h"
#include "Lock.h"
#include "LobbyLocale.h"
#include "ObjectPoolLobbyDaemon.h"
#include "StlMemory.h"
#include "../../External/BannedWordFilter/STLMemory.h"
#include "TimerQueue.h"

struct EventContext;
class EventObject;
class GameWorldReporter;
class Packet;
class RepeatPacketComposer;
class Session;
class AccountInventoryChannel;
class AccountInventorySessionHandler;
class BLDaemonInfoTable;
class BannedWordFilterLib;
class CliSessionManager;
class GameTimeScheduler;
class GameWorldRegistry;
class GamedChannelManager;
class InfoGateChannelManager;
class LobbyCharacterDeletionScheduler;
class LobbyConfig;
class LobbyGateChannelManager;
class LobbyJobManager;
class LobbyStats;
class LobbyTick;
class LobbyTokenDesk;
class ManageSessionHandler;
class MileageInterimDepositTimer;
class MileageManager;
class NPServiceChannelManager;
class PostOfficeChannel;
class PostOfficeSessionHandler;
class SystemPerfMonitor;
class TencentUIC;

class BannedWordFilterMemoryAllocator : public BannedWordFilterMemoryManager
{
public:
    virtual void* Alloc(unsigned long long, wchar_t const*, int);  // 0x99380
    virtual void* Realloc(void*, unsigned long long, wchar_t const*, int);  // 0x99390
    virtual void Free(void*, wchar_t const*, int);  // 0x993b0
};
extern BannedWordFilterMemoryAllocator BannedWordFilterMemoryAllocatorInstance;  // PDB global, rva 0x2056A0.

// Layout: include/pdb/LobbyDaemon/types.h (sizeof 0x50).
class CoolDown : public Timer
{
public:
    // LIFT: the constructor is inline at the allocation site (LobbyDaemon::cooldown 0x9ef40).
    CoolDown() : _run(false), _period(0), _end(0), _duration(0) {}
    // LIFT: ~CoolDown is compiler-generated. TimerClass and TimerId have no LD RVA in the index: vftable
    // ??_7CoolDown@@6B@ (rva 0x19f550) slots 6 and 7 point to the folded 0x5a0a0 (return 0).
    virtual unsigned int TimerClass() const;
    virtual unsigned long long TimerId() const;
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x995c0
    // LIFT: the PDB name (QEAA) is a member function. IDA shows no this at 0x99880: LTCG drops it, and the body reads
    // the global GCoolDown. ❓ whether the original source used this.
    bool Start(long, long);  // 0x99880

    bool _run;
    long _period;
    long long _end;
    long _duration;
};
static_assert(sizeof(CoolDown) == 0x50, "sizeof CoolDown");
static_assert(offsetof(CoolDown, _run) == 0x38, "CoolDown::_run");
static_assert(offsetof(CoolDown, _period) == 0x3C, "CoolDown::_period");
static_assert(offsetof(CoolDown, _end) == 0x40, "CoolDown::_end");
static_assert(offsetof(CoolDown, _duration) == 0x48, "CoolDown::_duration");
extern CoolDown* GCoolDown;

// Layout: include/pdb/LobbyDaemon/types.h (sizeof 0x18).
class RandomStoreInitializationSchedule
{
public:
    long long scheduleNumber;
    long long slotCountInitScheduleNumber;
    long long premiumDrawCountInitScheduleNumber;
};
static_assert(sizeof(RandomStoreInitializationSchedule) == 0x18, "sizeof RandomStoreInitializationSchedule");

// Layout: include/pdb/LobbyDaemon/types.h (sizeof 0x408).
class TimeBasedPlaySeasonSchedule
{
public:
    enum RewardType : int
    {
        REWARDTYPE_NORMAL = 0,
        REWARDTYPE_PREMIUM = 1,
        REWARDTYPE_NEWBIE = 2,
        REWARDTYPE_RETURN = 3,
        REWARDTYPE_COUNT = 4,
    };
    struct Period
    {
        long long startTimeUTC;
        long long endTimeUTC;
    };
    struct Reward
    {
        int id;
        int goodsId;
        int quantity;
    };
    struct Rule
    {
        // LIFT: 0x72d50 (SetupNpScheduleInfoJob.obj) is this body. It is inline here, because the 0x99df0
        // constructor inlines it. The card of 0x72d50 must not define Rule::Rule a second time.
        Rule() : minutes(-1)
        {
            for (int i = 0; i < 4; ++i)
            {
                rewardList[i].id = 0;
                rewardList[i].goodsId = 0;
                rewardList[i].quantity = 0;
            }
        }
        short minutes;
        Reward rewardList[4];
    };
    struct Data
    {
        // LIFT: no symbol in the PDB. The 0x99df0 constructor inlines this body.
        Data() : scheduleNumber(0), resetHour(0), resetHourTimeZoneBiasSecond(0), targetType(-1)
        {
            scheduleTime.startTimeUTC = 0;
            scheduleTime.endTimeUTC = 0;
        }
        void GetNextResetTimeUTC(long long conditionTimeUTC, long long& prevResetTimeUTC,
                                 long long& nextResetTimeUTC) const;  // 0x99d20
        int scheduleNumber;
        int resetHour;
        int resetHourTimeZoneBiasSecond;
        char targetType;
        Period scheduleTime;
        Rule rule[6];
    };

    TimeBasedPlaySeasonSchedule();  // 0x99df0
    bool Compose(RepeatPacketComposer&, Packet&) const;  // 0x99ef0

    Data _scheduleData[2];
    Data _invalidScheduleData;
};
static_assert(sizeof(TimeBasedPlaySeasonSchedule::Period) == 0x10, "sizeof TimeBasedPlaySeasonSchedule::Period");
static_assert(sizeof(TimeBasedPlaySeasonSchedule::Reward) == 0xC, "sizeof TimeBasedPlaySeasonSchedule::Reward");
static_assert(sizeof(TimeBasedPlaySeasonSchedule::Rule) == 0x34, "sizeof TimeBasedPlaySeasonSchedule::Rule");
static_assert(sizeof(TimeBasedPlaySeasonSchedule::Data) == 0x158, "sizeof TimeBasedPlaySeasonSchedule::Data");
static_assert(offsetof(TimeBasedPlaySeasonSchedule::Data, targetType) == 0xC, "Data::targetType");
static_assert(offsetof(TimeBasedPlaySeasonSchedule::Data, scheduleTime) == 0x10, "Data::scheduleTime");
static_assert(offsetof(TimeBasedPlaySeasonSchedule::Data, rule) == 0x20, "Data::rule");
static_assert(sizeof(TimeBasedPlaySeasonSchedule) == 0x408, "sizeof TimeBasedPlaySeasonSchedule");
static_assert(offsetof(TimeBasedPlaySeasonSchedule, _invalidScheduleData) == 0x2B0, "_invalidScheduleData");

// Layout: include/pdb/LobbyDaemon/types.h (sizeof 0xC80).
class LobbyDaemon : public Daemon
{
public:
    enum BannedWordFilterResult : int
    {
        SWF_OK = 0,
        SWF_ERROR = 1,
        SWF_INVALID_PARAMETER = 2,
        SWF_FORBIDDEN = 3,
    };
    enum DB : int
    {
        LOBBY_DB_ID = 1,
    };
    enum EventId : int
    {
        EVENT_MT_PACKET_HANDLE = 0,
    };
    enum ServiceItemType : int
    {
        SERVICEITEMTYPE_CHANGE_CHARACTER_APPEARANCE = 0,
        SERVICEITEMTYPE_RENAME_CHARACTER = 1,
        SERVICEITEMTYPE_ADD_SLOT = 2,
        SERVICEITEMTYPE_CHANGE_USER_NAME = 3,
        SERVICEITEMTYPE_EXTEND_JUMPING_CHARACTER_CREATION_QUOTA = 4,
        SERVICEITEMTYPE_CHANGE_CHARACTER_SEX = 5,
        SERVICEITEMTYPE_CHANGE_CHARACTER_RACE = 6,
        SERVICEITEMTYPE_RENAME_CHARACTER_BY_SYSTEM = 7,
        SERVICEITEMTYPE_MAX = 8,
    };

    virtual wchar_t const* ShortName();  // 0x99220
    virtual wchar_t const* Name();  // 0x99230
    virtual wchar_t const* ServiceName();  // 0x99240
    virtual wchar_t const* Descriptions();  // 0x99250
    LobbyDaemon();  // 0x9a230
    virtual ~LobbyDaemon();  // 0x9a3c0
    virtual void PrintDependency();  // 0x9ae30
    virtual long GetTimerInterval();  // 0x9af60
    virtual long GetTimerMaxTime();  // 0x9af70
    bool SetTimeZoneBias();  // 0x9af80
    static void FailedEventObjectHandler(EventObject*);  // 0x9b0c0
    BannedWordFilterResult FilterBannedWord(wchar_t const*);  // 0x9f240
    bool CheckServiceItemDataId(ServiceItemType, unsigned int);  // 0x9f340
    static wchar_t const* GetAddressStringWForLogs(unsigned long);  // 0x9f3c0
    // LIFT: ❓ LobbyDaemon::setArgument has no LD RVA in the index. The vftable slot folds with another
    // function. SmartCouponDaemon 0x14a90 returns false. This body is the same ❓ and not verified in the LD vftable.
    virtual bool setArgument(int, wchar_t const**) { return false; }

    static LobbyDaemon* _instance;

protected:
    virtual bool initLog();  // 0x9b1b0
    virtual bool initialize();  // 0x9b300
    virtual bool initNetwork();  // 0x9d520
    virtual bool onStart();  // 0x9dca0
    virtual void shutdown();  // 0x9e2f0
    virtual bool reload(wchar_t**, int);  // 0x9e5b0
    virtual bool cooldown();  // 0x9ef40
private:
    bool startNPChannel();  // 0x9f010
    bool setupNpScheduleInfo();  // 0x9f130

public:
    LobbyConfig const* _config;
    LobbyLocaleSet _localeset;
    long long _timeZoneBias;
    class ServiceItems* _serviceItems;
    LobbyTick* _tick;
    BLDaemonInfoTable* _daemonInfoTable;
    GameWorldRegistry* _gameWorldRegistry;
    GameWorldReporter* _gameWorldReporter;
    BannedWordFilterLib* _bannedWordFilter;
    LobbyCharacterDeletionScheduler* _charaterDeletionScheduler;
    LobbyStats* _stats;
    TencentUIC* _tencentUIC;
    CliSessionManager* _clisessionMgr;
    LobbyJobManager* _jobMgr;
    LobbyTokenDesk* _tokenDesk;
    NPServiceChannelManager* _npServchmgr;
    AccountInventoryChannel* _accountInventoryChannel;
    AccountInventorySessionHandler* _accountInventorySessionHandler;
    GamedChannelManager* _gamedchmgr;
    LobbyGateChannelManager* _lgatechmgr;
    ManageSessionHandler* _manageSessionHandler;
    InfoGateChannelManager* _infogatechmgr;
    PostOfficeChannel* _postOfficeChannel;
    PostOfficeSessionHandler* _postOfficeSessionHandler;
    SystemEvent _npInitialConnectEvent;
    SystemEvent _setupNpScheduleInfoEvent;
    SystemEvent _accountInventoryInitialConnectEvent;
    SystemEvent _postOfficeInitialConnectEvent;
    SystemPerfMonitor* _systemPerfMon;
    RandomStoreInitializationSchedule _currentRandomStoreInitSchedule;
    MileageManager* _mileageManager;
    MileageInterimDepositTimer* _mileageInterimDepositTimer;
    GameTimeScheduler* _gameTimeScheduler;
    TimeBasedPlaySeasonSchedule _timeBasedPlaySeasonSchedule;
    Timer* _restoreReloadTimer;
};
static_assert(sizeof(LobbyDaemon) == 0xC80, "sizeof LobbyDaemon");
static_assert(offsetof(LobbyDaemon, _config) == 0x748, "LobbyDaemon::_config");
static_assert(offsetof(LobbyDaemon, _clisessionMgr) == 0x7B8, "LobbyDaemon::_clisessionMgr");
static_assert(offsetof(LobbyDaemon, _lgatechmgr) == 0x7F0, "LobbyDaemon::_lgatechmgr");
static_assert(offsetof(LobbyDaemon, _timeBasedPlaySeasonSchedule) == 0x870, "LobbyDaemon::_timeBasedPlaySeasonSchedule");
static_assert(offsetof(LobbyDaemon, _restoreReloadTimer) == 0xC78, "LobbyDaemon::_restoreReloadTimer");

// Layout: include/pdb/LobbyDaemon/types.h (sizeof 0x100).
class ServiceItems
{
public:
    bool Add(LobbyDaemon::ServiceItemType, wchar_t const*);  // 0x99ac0

    std::vector<unsigned int, StlAllocator<unsigned int, 2> > _idList[8];
};
static_assert(sizeof(ServiceItems) == 0x100, "sizeof ServiceItems");

// LIFT: LobbyObjPoolMemAllocator is declared in ObjectPool.h (LobbyDaemon form).

// Layout: include/pdb/LobbyDaemon/types.h (sizeof 0x40).
class LobbydReloadInvalidRestoreTimer : public Timer
{
public:
    enum ReloadInvalidReason : int
    {
        RELOAD_INVALID_REASON_DAEMON_CONFIG_RELOAD_FAILED = 0,
        RELOAD_INVALID_REASON_DAEMON_LIST_RELOAD_FAILED = 1,
        RELOAD_INVALID_REASON_WORLD_LIST_RELOAD_FAILED = 2,
        RELOAD_INVALID_REASON_CONTENTS_RULE_CONFIG_RELOAD_FAILED = 3,
        RELOAD_INVALID_REASON_BNS_COMMON_CONFIG_RELOAD_FAILED = 4,
        RELOAD_INVALID_REASON_MAX = 5,
    };
    // LIFT: ~LobbydReloadInvalidRestoreTimer, TimerClass and TimerId have no LD RVA in the index (folded).
    // A later card lifts them. The constructor is inline at the allocation site (LobbyDaemon::reload).
    virtual unsigned int TimerClass() const;
    virtual unsigned long long TimerId() const;
    virtual unsigned int EventId() const;  // 0x99990
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x999a0

    static wchar_t const* INVALID_REASON_STR[5];

    bool _isExecuted;

private:
    void restoreInvalid();  // 0x999b0
};
static_assert(sizeof(LobbydReloadInvalidRestoreTimer) == 0x40, "sizeof LobbydReloadInvalidRestoreTimer");
static_assert(offsetof(LobbydReloadInvalidRestoreTimer, _isExecuted) == 0x38, "_isExecuted");

unsigned long long GenerateClikey();  // 0x993c0
unsigned long long GenerateJobid();  // 0x99410
unsigned long long GenerateLobbyTokenkey();  // 0x99460
void GameWorldReporterListener(GameWorldReporter*);  // 0x994b0
bool ConcatenatePacket(Session const*, Packet const*, bool&);  // 0x9f3f0
