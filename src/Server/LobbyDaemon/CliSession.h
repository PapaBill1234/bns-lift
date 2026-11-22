// CliSession.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from include/pdb/LobbyDaemon/types.h.
// LIFT: ld-2 added the layouts of CliSession, GameAccount, Presence, ServiceLocation and the member types.
// LIFT: the presence classes and GameServiceLocation have no bases yet. A later card adds them.
#pragma once
#include <new>
#include <stddef.h>
#include <string.h>
#include <vector>
#include "AuctionDeliverJob.h"
#include "GradeService.h"
#include "Lock.h"
#include "StlMemory.h"
#include "StringUtil.h"

class Character;
class CliSession;
class CliSessionTable;
class FragmentPacket;
class GameTimeScheduleNode;
class GamedChannel;
struct GoodsInventoryChangedNotifyParam;
class LobbyGateChannel;
class LobbyService;
class MileageSlot;
class Packet;
class PacketComposer;
class PcCafe;
class Presence;
class RenameUserService;
class RepeatPacketComposer;
class RepeatPacketDecomposer;
class ServiceLocation;
class StopPlayTimerEvent;
class TimeBasedPlayInfoList;
struct UserPromotionReward;
union id128;

namespace StsMsgLib
{
struct _StsMsgNotifyGradeNotifyGradeChanged;
struct _StsMsgNotifyGradeNotifyScoreChanged;
struct _StsMsgResponseListUserBans;
struct _StsMsgResponseRiskMgmtInquiry;
}

// PDB enum LobbyError (types.h:3429).
enum LobbyError
{
    LOBERR_UNKNOWN = 0,
    LOBERR_SYSTEM = 1,
    LOBERR_DB_FAIL = 2,
    LOBERR_INVALID_PARAMETER = 3,
    LOBERR_NOT_INITAILIZED = 4,
    LOBERR_INVALID_SESSION_STATE = 5,
    LOBERR_NO_SUCH_CHARACTER = 6,
    LOBERR_GAMEWORLD_NOT_FOUND = 7,
    LOBERR_GAMEWORLD_NOT_ALIVE = 8,
    LOBERR_GAMEWORLD_NOT_USABLE = 9,
    LOBERR_GAMEWORLD_ENTRANCE_NOT_ALLOWED = 10,
    LOBERR_GAMEWORLD_PRE_CHARACTER_CREATION_MODE = 11,
    LOBERR_GAMEWORLD_FULL = 12,
    LOBERR_GAMEWORLD_CHARACTER_MANAGEMENT_NOT_ALLOWED = 13,
    LOBERR_GAMEWORLD_NEW_ACCOUNT_CHARACTER_CREATION_NOT_ALLOWED = 14,
    LOBERR_CHARGE_NOT_STARTED = 15,
    LOBERR_IN_LOBBY_SERVICE = 16,
    LOBERR_INVALID_STATE = 17,
    LOBERR_NAME_DUPLICATED = 18,
    LOBERR_NAME_LIMITED = 19,
    LOBERR_VIP_NOT_AVAILABLE = 20,
    LOBERR_VIP_UNKNOWN_ID = 21,
    LOBERR_INSUFFICIENT_BUFFER = 22,
    LOBERR_ALREADY_INITIALIZED = 23,
    LOBERR_NOT_FOUND = 24,
    LOBERR_STOP_PLAY_ALREADY_RESERVED = 25,
    LOBERR_GAME_TIME_SCHEDULE_NO_NEED_TO_SCHEDULE = 26,
    LOBERR_GAME_TIME_SCHEDULE_IN_SCHEDULED_BLOCK_TIME = 27,
    LOBERR_MAX = 28,
};

// PDB public ?TLobbyError@@3W4LobbyError@@A (thread-local).
// LIFT: the PDB module of TLobbyError is not known. CliSession.cpp has the definition. ❓
extern __declspec(thread) LobbyError TLobbyError;

// LIFT: constructor not in the PDB. Inlined in GameAccount::GameAccount (0x33360): each field is set to zero.
struct TimeBasedPlayInfo
{
    TimeBasedPlayInfo()
        : scheduleNumber(0), duration(0), expireTimeUTC(0), lastUpdateTimeUTC(0), rewardList(), acknowledgedPlayTime(0)
    {
    }

    int scheduleNumber;
    int duration;
    long long expireTimeUTC;
    long long lastUpdateTimeUTC;
    unsigned char rewardList[4];
    short acknowledgedPlayTime;
};
static_assert(sizeof(TimeBasedPlayInfo) == 0x20, "sizeof TimeBasedPlayInfo");
static_assert(offsetof(TimeBasedPlayInfo, rewardList) == 0x18, "TimeBasedPlayInfo::rewardList");
static_assert(offsetof(TimeBasedPlayInfo, acknowledgedPlayTime) == 0x1C, "TimeBasedPlayInfo::acknowledgedPlayTime");

class Role
{
public:
    Role() : _roles(0) {}  // LIFT: inlined in GameAccount::GameAccount (0x33360)

    unsigned char _roles;
};
static_assert(sizeof(Role) == 0x1, "sizeof Role");

class GameAccountExpInfo
{
public:
    struct ExpInfo
    {
        long long exp;
        int expQuotaPerDay;
        long long lastUpdateTime;
    };

    GameAccountExpInfo() { memset(&_info, 0, sizeof(_info)); }  // LIFT: inlined in GameAccount::GameAccount (0x33360)

    ExpInfo _info;
};
static_assert(sizeof(GameAccountExpInfo) == 0x18, "sizeof GameAccountExpInfo");

class JumpingCharacterCreationQuota
{
public:
    struct DB
    {
        int creationQuota;
        int creationCount;
    };

    // LIFT: inlined in CliSession::CliSession (0x32a40, 0x33490). Name not in the PDB.
    JumpingCharacterCreationQuota() { Clear(); }
    void Clear()
    {
        memset(&_db, 0, sizeof(_db));
        _reservedCreationCount = 0;
    }

    DB _db;
    int _reservedCreationCount;
};
static_assert(sizeof(JumpingCharacterCreationQuota) == 0xC, "sizeof JumpingCharacterCreationQuota");

class Authority
{
public:
    enum Operation
    {
        OP_MANAGE_CHARACTER_ON_NOT_ALLOWED = 0,
        OP_CREATE_CHARACTER_ON_NEW_ACCOUNT_CREATION_NOT_ALLOWED = 1,
        OP_ENTER_GAMEWORLD_ON_ENTRANCE_NOT_ALLOWED = 2,
        OP_ENTER_GAMEWORLD_ON_FULL = 3,
        OP_MAX = 4,
    };
    struct Table
    {
        bool field[4];
    };

    Authority() { memset(&_table, 0, sizeof(_table)); }  // LIFT: inlined in CliSession::CliSession (0x33490)

    Table _table;
};
static_assert(sizeof(Authority) == 0x4, "sizeof Authority");

struct ContentBan
{
    int id;
    long long from;
    long long to;
};
static_assert(sizeof(ContentBan) == 0x18, "sizeof ContentBan");

struct AccountContentQuota
{
    int dataId;
    short version;
    long long quantity;
    long long lastUpdateTime;
};
static_assert(sizeof(AccountContentQuota) == 0x18, "sizeof AccountContentQuota");

struct AccountRecycleTime
{
    short groupId;
    long long time;
};
static_assert(sizeof(AccountRecycleTime) == 0x10, "sizeof AccountRecycleTime");

class Presence
{
public:
    enum Kind
    {
        Invalid = 0,
        AnonymousLobbyGate = 1,
        LobbyGate = 2,
        GameWorld = 3,
    };

    // LIFT: the original global operator delete(void*) (0x32b50) is empty (ICF with Console::Flush). The callers
    // do "delete p;" and then Memory::_Manager[2]->Free(p, ...). This empty class operator delete keeps that shape
    // and frees the memory only once (in Free).
    static void operator delete(void*) {}

    virtual ~Presence();                                                                // slot 0
    virtual Kind GetKind() const = 0;                                                   // slot 1
    virtual bool IsEqual(Presence const* presence) const = 0;                           // slot 2
    virtual bool OnSet(CliSessionTable* table, CliSession* cs) = 0;                     // slot 3
    virtual void OnUnset(CliSessionTable* table, CliSession* cs) = 0;                   // slot 4
    virtual void Close(CliSession* cs) = 0;                                             // slot 5
    virtual void Kick(CliSession* cs, int reason) = 0;                                  // slot 6
    virtual void NotifyChangedGrade(CliSession* cs, StsMsgLib::_StsMsgNotifyGradeNotifyGradeChanged const& msg) = 0;       // slot 7
    virtual void NotifyChangedGradeLevel(CliSession* cs, StsMsgLib::_StsMsgNotifyGradeNotifyScoreChanged const& msg) = 0;  // slot 8
};
static_assert(sizeof(Presence) == 0x8, "sizeof Presence");

class TimeBasedPlayInfoList
{
public:
    // LIFT: inlined in GameAccount::GameAccount (0x33360). Same body as the destructor 0x32bb0.
    TimeBasedPlayInfoList() { memset(_timeBasedPlayInfo, 0, sizeof(_timeBasedPlayInfo)); }
    ~TimeBasedPlayInfoList();  // 0x32bb0
    void ValidateDurations();  // 0x32be0
    void SetPlayInfoFromGame(TimeBasedPlayInfoList const& infoList);  // 0x32e20
    bool Compose(FragmentPacket&) const;  // 0x32ed0
    bool Compose(RepeatPacketComposer&, Packet&) const;  // 0x33070
    bool Decompose(RepeatPacketDecomposer&, Packet const*);  // 0x331e0

    TimeBasedPlayInfo _timeBasedPlayInfo[2];
};
static_assert(sizeof(TimeBasedPlayInfoList) == 0x40, "sizeof TimeBasedPlayInfoList");

class GameAccount
{
public:
    struct DB
    {
        wchar_t name[65];
        char right;
        int botScore;
        bool botScoreIgnore;
        unsigned long long representativePcid;
    };
    enum Right
    {
        RIGHT_INVALID = 0,
        RIGHT_NOMALITY = 1,
    };

    GameAccount();  // 0x33360
    ~GameAccount();  // 0x33450

    id128 _id;
    DB _dbfield;
    id128 _userid;
    wchar_t _userName[65];
    Role _roles;
    TimeBasedPlayInfoList _timeBasedPlayInfoList;
    GameAccountExpInfo _accountExp;
};
static_assert(offsetof(GameAccount, _userid) == 0xA8, "GameAccount::_userid");
static_assert(offsetof(GameAccount, _roles) == 0x13A, "GameAccount::_roles");
static_assert(offsetof(GameAccount, _timeBasedPlayInfoList) == 0x140, "GameAccount::_timeBasedPlayInfoList");
static_assert(offsetof(GameAccount, _accountExp) == 0x180, "GameAccount::_accountExp");
static_assert(sizeof(GameAccount) == 0x198, "sizeof GameAccount");

class ServiceLocation
{
public:
    enum Kind
    {
        KIND_GAMEWORLD = 0,
    };

    // LIFT: the original global operator delete(void*) (0x32b50) is empty (ICF with Console::Flush). The callers
    // do "delete p;" and then Memory::_Manager[2]->Free(p, ...). This empty class operator delete keeps that shape
    // and frees the memory only once (in Free).
    static void operator delete(void*) {}

    virtual ~ServiceLocation();  // 0x329d0, slot 0
    virtual Kind GetKind() const = 0;                                                     // slot 1
    virtual bool Enter(CliSession* cs) = 0;                                               // slot 2
    virtual bool Leave(CliSession* cs) = 0;                                               // slot 3
    virtual void OnEnter(CliSession* cs) = 0;                                             // slot 4
    virtual void OnLeave(CliSession* cs) = 0;                                             // slot 5
    virtual bool ReserveStopPlay(CliSession* cs, StopPlayTimerEvent* event) = 0;          // slot 6
    virtual bool TimeoutStopPlay(CliSession* cs, StopPlayTimerEvent* event) = 0;          // slot 7
    virtual void NotifyStopPlay(CliSession* cs, int reason) = 0;                          // slot 8

    short _wid;
};
static_assert(sizeof(ServiceLocation) == 0x10, "sizeof ServiceLocation");

class AnonymousLobbyGatePresence
{
public:
    AnonymousLobbyGatePresence(LobbyGateChannel*, unsigned long long);  // 0x3a3f0
    virtual bool IsEqual(Presence const*) const;  // 0x3a4a0
    virtual bool OnSet(CliSessionTable*, CliSession*);  // 0x3a530
    virtual void OnUnset(CliSessionTable*, CliSession*);  // 0x3a600
    virtual void Close(CliSession*);  // 0x3a650
    virtual void Kick(CliSession*, int);  // 0x3a670
};

class CliSession : public RefCntPoolObj
{
public:
    enum ErrCode
    {
        ERR_OK = 0,
        ERR_UNKNOWN = 1,
        ERR_SYSTEM = 2,
        ERR_INVALID_STATE = 3,
        ERR_INVALID_PARAMETER = 4,
        ERR_NO_SUCH_CHARACTER = 5,
        ERR_NOT_IN_WAIT = 6,
    };
    enum ReservedContentBanID
    {
        CONTENT_BAN_ID_RMS_INQUIRY = 7,
    };

    CliSession(unsigned long long clikey, CliSessionTable* table);  // 0x33490
    virtual ~CliSession();  // 0x336b0
    void finalize();  // 0x33cc0
    bool npLogin(id128 const&);  // 0x33d60
    bool login(id128 const&, wchar_t const*, char, wchar_t const*);  // 0x33f00
    bool logout();  // 0x34750
    bool loadDB();  // 0x349a0
    bool setPresence(Presence* presence);  // 0x35730
    void closePresence();  // 0x35810
    void kickPresence(int reason);  // 0x358e0
    bool enter(ServiceLocation* srvloc);  // 0x359c0
    void leave();  // 0x35c10
    Character* getCharacter(unsigned long long);  // 0x35cf0
    void removeCharacter(unsigned long long);  // 0x35d30
    Character* getPlayingCharacter();  // 0x35d90
    void setChargeKey(wchar_t const* chargeKey);  // 0x35e20
    void completeRequestChargeStop(bool);  // 0x35eb0
    void cleanupCharge();  // 0x35fc0
    bool NotifyChangedGrade(StsMsgLib::_StsMsgNotifyGradeNotifyGradeChanged const&);  // 0x360a0
    bool NotifyChangedGradeLevel(StsMsgLib::_StsMsgNotifyGradeNotifyScoreChanged const&);  // 0x36170
    void HandleGameGetGradeList(GamedChannel*, unsigned long long, char, unsigned long long, int) const;  // 0x36240
    void setContentBans(StsMsgLib::_StsMsgResponseListUserBans*);  // 0x366e0
    void setRMSInquiryResult(StsMsgLib::_StsMsgResponseRiskMgmtInquiry*);  // 0x36960
    bool fetchContentBans(FragmentPacket*);  // 0x36df0
    bool fetchAccountContentQuotaList(FragmentPacket*);  // 0x36fa0
    bool fetchAccountRecycleTimeList(FragmentPacket*);  // 0x371b0
    bool addLobbyService(LobbyService*);  // 0x373a0
    void removeLobbyService(unsigned long long);  // 0x37530
    LobbyService* getLobbyServiceByType(unsigned long long, int);  // 0x37670
    LobbyService* queryLobbyService(Character*);  // 0x376b0
    bool addRenameUserService(RenameUserService*);  // 0x37790
    void setScheduledEndTime(GameTimeScheduleNode*);  // 0x37890
    void releaseScheduledEndTime();  // 0x37950
    ErrCode FetchCharacterInfoList(FragmentPacket*) const;  // 0x379b0
    bool FetchCharacterInfo(id128 const&, Packet*, PacketComposer*) const;  // 0x37af0
    bool FetchServiceEntryList(FragmentPacket*) const;  // 0x37c70
    bool UpdateBotScore(unsigned long long, int);  // 0x37de0
    bool BindCharacterSlot(unsigned long long, id128 const&);  // 0x37eb0
    bool UpdateCharacterData(unsigned long long, short, char*, short);  // 0x381c0
    bool UpdateCharacterLevel(unsigned long long, short);  // 0x38380
    bool UpdateAccountData(unsigned long long, int, TimeBasedPlayInfoList&);  // 0x38500
    bool UpdateTimeBasedPlayReward(unsigned long long, int, char, short, UserPromotionReward&, long long);  // 0x38670
    bool NotifyGoodsInventoryChangedAlongPresence(GoodsInventoryChangedNotifyParam&);  // 0x392c0
    bool ReserveStopPlay(bool, int, int);  // 0x39820
    bool TimeoutStopPlay(StopPlayTimerEvent*);  // 0x39a70
    bool OnChargeStopRequested(unsigned int);  // 0x39be0
    bool ApplyNewChargeItem(wchar_t const*, long, unsigned int, short);  // 0x39cc0
    bool NotifyChargeRemainTime(long, short, unsigned int);  // 0x39e50
    bool setRole(unsigned int const* const, int);  // 0x39f70
    bool setPcCafeCode(wchar_t const*);  // 0x3a000
    void setPcCafe(PcCafe*);  // 0x3a100
    void onPcCafeChargeStart();  // 0x3a190
    void onPcCafeChargeStop();  // 0x3a2c0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x329f0
    CliSession();  // 0x32a40

public:
    int _state;
    unsigned long long _clikey;
    unsigned long _ipv4;
    GameAccount _acb;
    JumpingCharacterCreationQuota _jumpingCharacterCreationQuota;
    short _authProviderCodeSize;
    char _authProviderCode[17];
    short _externalAccountKeySize;
    char _externalAccountKey[65];
    short _externalAccountNameSize;
    char _externalAccountName[257];
    short _externalAccountDataSize;
    char _externalAccountData[1025];
    std::vector<Character*, StlAllocator<Character*, 2> > _characters;
    std::vector<LobbyService*, StlAllocator<LobbyService*, 2> > _serviceEntries;
    Authority _auth;
    std::vector<ContentBan, StlAllocator<ContentBan, 2> > _bans;
    int _bansCount;
    std::vector<AccountContentQuota, StlAllocator<AccountContentQuota, 2> > _quotaList;
    std::vector<AccountRecycleTime, StlAllocator<AccountRecycleTime, 2> > _recycleTimeList;
    CliSessionTable* _table;
    bool _npLogin;
    bool _login;
    bool _isMobile;
    bool _teen;
    GameTimeScheduleNode* _scheduledEndTime;
    long long _closestEndTime;
    Presence* _presence;
    ServiceLocation* _srvloc;
    StopPlayTimerEvent* _reservedStopPlay;
    wchar_t* _chargeKey;
    unsigned int _chargeStopRequestTxnId;
    GradeService _gradeService;
    wchar_t* _pcCafeCode;
    PcCafe* _pcCafe;
    bool _pcCafeCharged;
    MileageSlot* _mileageSlot;
    id128 _infoGateToken;
    LobbyService* _renameUserServiceEntry;
    CriticalSection _lock;
};
static_assert(offsetof(CliSession, _state) == 0x18, "CliSession::_state");
static_assert(offsetof(CliSession, _acb) == 0x30, "CliSession::_acb");
static_assert(offsetof(CliSession, _jumpingCharacterCreationQuota) == 0x1C8, "CliSession::_jumpingCharacterCreationQuota");
static_assert(offsetof(CliSession, _externalAccountData) == 0x332, "CliSession::_externalAccountData");
static_assert(offsetof(CliSession, _characters) == 0x738, "CliSession::_characters");
static_assert(offsetof(CliSession, _auth) == 0x778, "CliSession::_auth");
static_assert(offsetof(CliSession, _recycleTimeList) == 0x7C8, "CliSession::_recycleTimeList");
static_assert(offsetof(CliSession, _table) == 0x7E8, "CliSession::_table");
static_assert(offsetof(CliSession, _presence) == 0x808, "CliSession::_presence");
static_assert(offsetof(CliSession, _chargeKey) == 0x820, "CliSession::_chargeKey");
static_assert(offsetof(CliSession, _gradeService) == 0x830, "CliSession::_gradeService");
static_assert(offsetof(CliSession, _infoGateToken) == 0x890, "CliSession::_infoGateToken");
static_assert(offsetof(CliSession, _lock) == 0x8A8, "CliSession::_lock");
static_assert(sizeof(CliSession) == 0x8D0, "sizeof CliSession");

class GameServiceLocation
{
public:
    virtual ~GameServiceLocation();  // 0x3b360
    virtual void OnEnter(CliSession*);  // 0x3b3d0
    virtual void OnLeave(CliSession*);  // 0x3b540
    virtual bool Enter(CliSession*);  // 0x3b6f0
    virtual bool Leave(CliSession*);  // 0x3b9a0
    virtual bool ReserveStopPlay(CliSession*, StopPlayTimerEvent*);  // 0x3bb60
    virtual bool TimeoutStopPlay(CliSession*, StopPlayTimerEvent*);  // 0x3bc80
    virtual void NotifyStopPlay(CliSession*, int);  // 0x3bda0
};

class GameWorldPresence
{
public:
    virtual bool IsEqual(Presence const*) const;  // 0x3adf0
    virtual bool OnSet(CliSessionTable*, CliSession*);  // 0x3ae90
    virtual void OnUnset(CliSessionTable*, CliSession*);  // 0x3aff0
    virtual void Close(CliSession*);  // 0x3b0c0
    virtual void Kick(CliSession*, int);  // 0x3b120
};

class LobbyGatePresence
{
public:
    virtual bool IsEqual(Presence const*) const;  // 0x3a760
    virtual bool OnSet(CliSessionTable*, CliSession*);  // 0x3a7d0
    virtual void OnUnset(CliSessionTable*, CliSession*);  // 0x3aa30
    virtual void Close(CliSession*);  // 0x3abc0
    virtual void Kick(CliSession*, int);  // 0x3ac20
};

