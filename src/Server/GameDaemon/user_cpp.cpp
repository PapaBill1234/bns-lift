// user_cpp.cpp: user.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "user.h"
#include "pc.h"
#include "gamedaemon.h"
#include "gamedconfig.h"
#include "contentsruleconfigdefinition_gd.h"
#include <time.h>
#include <wchar.h>
#include "Channel.h"
#include "Log.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1TimeBasedPlayInfoList@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetLastCheckTimeUTC@TimeBasedPlayInfoList@@QEAAX_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetValidCheckTimeUTC@TimeBasedPlayInfoList@@QEAA?B_JD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetData@TimeBasedPlayInfoList@@QEAAXAEBV1@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetDurationForDebug@TimeBasedPlayInfoList@@QEAA_NDH@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetPcCafeDebugCode@User@@QEAAXPEA_WD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetSession@User@@UEAAXPEBVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?resetPc@User@@CAXPEAVRefCntObject@@00@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?resetPc@User@@AEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: view of TimeBasedPlayInfo (size 0x20). The skeleton class has no members. Offsets are from the PDB.
struct TimeBasedPlayInfoView
{
    int scheduleNumber;            // +0x0
    int duration;                  // +0x4
    __int64 startTimeUTC;          // +0x8
    __int64 expireTimeUTC;         // +0x10
    __int64 acknowledgedPlayTime;  // +0x18 (short acknowledgedPlayTime, filled to 8 bytes)
};

// LIFT: view of TimeBasedPlayInfoList (size 0x80).
struct TimeBasedPlayInfoListView
{
    bool _isPcCafe;                          // +0x0
    bool _useLock;                           // +0x1
    char lift_pad_0[6];
    ::_RTL_SRWLOCK _timeLock;                // +0x8
    __int64 _lastCheckTimeUTC;               // +0x10
    __int64 _lastResetTimeUTC[2];            // +0x18
    __int64 _nextResetTimeUTC[2];            // +0x28
    ::_RTL_SRWLOCK _infoLock;                // +0x38
    TimeBasedPlayInfoView _timeBasedPlayInfo[2];  // +0x40
};
static_assert(sizeof(TimeBasedPlayInfoListView) == 0x80, "TimeBasedPlayInfoListView");

// LIFT: User members by PDB offset (the skeleton class has no members).
template <class T>
inline T *UserAt(void const *self, unsigned offset)
{
    return reinterpret_cast<T *>(const_cast<char *>(static_cast<char const *>(self)) + offset);
}

#define USER_CPP_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\User.cpp"
#define USER_PC_CPP_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\Pc.cpp"

enum
{
    USER_PcDbId = 216,
    USER_PcId = 224,
    USER_pc = 720,
    USER_SendHashKey = 728,
    USER_botScoreState = 1072,
    USER_ChargeBaseType = 400,
    USER_PcCafeCode = 676,
    USER_contentsBanList = 872,
    USER_existContentsBan = 1016,
    USER_tencentPcCafeType = 1032,
    USER_tencentPcCafeLevel = 1036,
    USER_timeBasedPlayInfoList = 1280,
};

// LIFT: GamedConfig::_useContentsBan is bool at +0x2D1 (PDB). GameDaemon::publisherCode is char at +0x15341 (PDB).
// LIFT: GameDaemon::config is at +0xAA8 (PDB, private). Read it by offset.
inline GamedConfig *GamedConfigOf() { return *reinterpret_cast<GamedConfig **>(reinterpret_cast<char *>(GameDaemon::GamedInstance) + 0xAA8); }
inline bool UseContentsBan() { return *reinterpret_cast<bool *>(reinterpret_cast<char *>(GamedConfigOf()) + 721); }
inline char PublisherCode() { return *(reinterpret_cast<char *>(GameDaemon::GamedInstance) + 86849); }
}  // namespace

// 0x3e1fc0
__cdecl TimeBasedPlayInfoList::TimeBasedPlayInfoList(void)
{
    LIFT_STUB(0x3e1fc0);
}

// 0x3e2040
__cdecl TimeBasedPlayInfoList::~TimeBasedPlayInfoList(void)
{
    TimeBasedPlayInfoListView *self = reinterpret_cast<TimeBasedPlayInfoListView *>(this);
    self->_isPcCafe = false;
    self->_useLock = false;
    self->_lastCheckTimeUTC = 0;
    self->_lastResetTimeUTC[0] = 0;
    self->_lastResetTimeUTC[1] = 0;
    self->_nextResetTimeUTC[0] = 0;
    self->_nextResetTimeUTC[1] = 0;
    for (int i = 0; i < 2; ++i)
    {
        self->_timeBasedPlayInfo[i].scheduleNumber = 0;
        self->_timeBasedPlayInfo[i].duration = 0;
        self->_timeBasedPlayInfo[i].startTimeUTC = 0;
        self->_timeBasedPlayInfo[i].expireTimeUTC = 0;
        self->_timeBasedPlayInfo[i].acknowledgedPlayTime = 0;
    }
}

// 0x3e2080
bool __cdecl TimeBasedPlayInfoList::RenewDailyPlayInfo(__int64, __int64)
{
    LIFT_STUB(0x3e2080);
}

// 0x3e2260
void __cdecl TimeBasedPlayInfoList::SetLastCheckTimeUTC(__int64 checkTimeUTC)
{
    TimeBasedPlayInfoListView *self = reinterpret_cast<TimeBasedPlayInfoListView *>(this);
    if (self->_useLock)
    {
        AcquireSRWLockExclusive(&self->_timeLock);
        self->_lastCheckTimeUTC = checkTimeUTC;
        ReleaseSRWLockExclusive(&self->_timeLock);
    }
}

// 0x3e22b0
__int64 const __cdecl TimeBasedPlayInfoList::GetValidCheckTimeUTC(char targetType)
{
    TimeBasedPlayInfoListView *self = reinterpret_cast<TimeBasedPlayInfoListView *>(this);
    if (self->_useLock)
        AcquireSRWLockShared(&self->_infoLock);
    __int64 expireTimeUTC = self->_timeBasedPlayInfo[targetType].expireTimeUTC;
    int scheduleNumber = self->_timeBasedPlayInfo[targetType].scheduleNumber;
    if (self->_useLock)
        ReleaseSRWLockShared(&self->_infoLock);
    if (scheduleNumber == 0 || expireTimeUTC == 0)
        return 0;
    if (self->_useLock)
        AcquireSRWLockShared(&self->_timeLock);
    __int64 nextResetTimeUTC = self->_nextResetTimeUTC[targetType];
    if (self->_useLock)
        ReleaseSRWLockShared(&self->_timeLock);
    __int64 validTimeUTC = nextResetTimeUTC - 1;
    if (_time64(nullptr) < nextResetTimeUTC - 1)
        return _time64(nullptr);
    return validTimeUTC;
}

// 0x3e2370
void __cdecl TimeBasedPlayInfoList::SetData(::TimeBasedPlayInfoList const &infoList)
{
    TimeBasedPlayInfoListView *self = reinterpret_cast<TimeBasedPlayInfoListView *>(this);
    TimeBasedPlayInfoListView const *src = reinterpret_cast<TimeBasedPlayInfoListView const *>(&infoList);
    if (!src->_useLock)
    {
        if (self->_useLock)
            AcquireSRWLockExclusive(&self->_infoLock);
        for (int i = 0; i < 2; ++i)
        {
            // LIFT: the original copies scheduleNumber and duration as one 8-byte value.
            *reinterpret_cast<__int64 *>(&self->_timeBasedPlayInfo[i].scheduleNumber) =
                *reinterpret_cast<__int64 const *>(&src->_timeBasedPlayInfo[i].scheduleNumber);
            self->_timeBasedPlayInfo[i].startTimeUTC = src->_timeBasedPlayInfo[i].startTimeUTC;
            self->_timeBasedPlayInfo[i].expireTimeUTC = src->_timeBasedPlayInfo[i].expireTimeUTC;
            self->_timeBasedPlayInfo[i].acknowledgedPlayTime = src->_timeBasedPlayInfo[i].acknowledgedPlayTime;
        }
        if (self->_useLock)
            ReleaseSRWLockExclusive(&self->_infoLock);
    }
}

// 0x3e2400
void __cdecl TimeBasedPlayInfoList::SetRewardInfo(::TimeBasedPlayInfoList const &)
{
    LIFT_STUB(0x3e2400);
}

// 0x3e24a0
bool __cdecl TimeBasedPlayInfoList::SetDurationForDebug(char targetType, int duration)
{
    TimeBasedPlayInfoListView *self = reinterpret_cast<TimeBasedPlayInfoListView *>(this);
    if (!self->_useLock)
        return false;
    AcquireSRWLockExclusive(&self->_infoLock);
    self->_timeBasedPlayInfo[targetType].duration = duration;
    ReleaseSRWLockExclusive(&self->_infoLock);
    AcquireSRWLockExclusive(&self->_timeLock);
    self->_lastResetTimeUTC[targetType] = _time64(nullptr);
    ReleaseSRWLockExclusive(&self->_timeLock);
    return true;
}

// 0x3e2530
bool __cdecl TimeBasedPlayInfoList::CheckSchedule(__int64, bool &)
{
    LIFT_STUB(0x3e2530);
}

// 0x3e2770
bool __cdecl TimeBasedPlayInfoList::firstSyncSchedule(__int64)
{
    LIFT_STUB(0x3e2770);
}

// 0x3e29c0
bool __cdecl TimeBasedPlayInfoList::CheckRemainRewards(__int64)
{
    LIFT_STUB(0x3e29c0);
}

// 0x3e2aa0
short __cdecl TimeBasedPlayInfoList::CheckRewards(char, __int64, int &, int &)
{
    LIFT_STUB(0x3e2aa0);
}

// 0x3e2c30
bool __cdecl TimeBasedPlayInfoList::GetPlayTimeDurationSec(__int64, bool, int &, int &, int &, int &)
{
    LIFT_STUB(0x3e2c30);
}

// 0x3e2de0
int __cdecl TimeBasedPlayInfoList::GetPlayTimeDurationSec(char, __int64, bool)
{
    LIFT_STUB(0x3e2de0);
}

// 0x3e2f10
bool __cdecl TimeBasedPlayInfoList::ComposeToClient(::FragmentPacket &)
{
    LIFT_STUB(0x3e2f10);
}

// 0x3e3170
bool __cdecl TimeBasedPlayInfoList::ComposeToClient(::RepeatPacketComposer &, ::Packet &)
{
    LIFT_STUB(0x3e3170);
}

// 0x3e3380
bool __cdecl TimeBasedPlayInfoList::Decompose(::FragmentPacketConcatenater *)
{
    LIFT_STUB(0x3e3380);
}

// 0x3e3520
bool __cdecl TimeBasedPlayInfoList::Compose(::RepeatPacketComposer &, ::Packet &, bool, __int64)
{
    LIFT_STUB(0x3e3520);
}

// 0x3e3740
bool __cdecl TimeBasedPlayInfoList::Decompose(::RepeatPacketDecomposer &, ::Packet const *)
{
    LIFT_STUB(0x3e3740);
}

// 0x3e38e0
void __cdecl TimeBasedPlayInfoList::Dump(__int64, wchar_t *, int)
{
    LIFT_STUB(0x3e38e0);
}

// 0x3e3c30
// LIFT: feature off (owner scope)
__cdecl GameGuardAuth::~GameGuardAuth(void)
{
}

// 0x3e3d00
// LIFT: feature off (owner scope)
void __cdecl GameGuardAuth::Init(unsigned __int64)
{
}

// 0x3e3e90
// LIFT: feature off (owner scope)
bool __cdecl GameGuardAuth::AvailableCheck(void)
{
    return false;
}

// 0x3e40e0
// LIFT: feature off (owner scope)
unsigned int __cdecl GameGuardAuth::CheckValueFromClient(unsigned char const *, unsigned int)
{
    return 0;
}

// 0x3e41a0
__cdecl User::User(void)
{
    LIFT_STUB(0x3e41a0);
}

// 0x3e4530
__cdecl User::~User(void)
{
    LIFT_STUB(0x3e4530);
}

// 0x3e4610
void __cdecl User::SetSession(::Session const *session)
{
    if (session != nullptr)
    {
        GamedConfig *config = GamedConfigOf();
        // LIFT: Session::_id is at +0x68 (PDB). The arena id compare is unsigned in the original.
        if (!config->_arenaEnabled || static_cast<unsigned>(config->_arenaId) <= 0u)
            *UserAt<unsigned __int64>(this, USER_SendHashKey) = *UserAt<unsigned __int64>(session, 0x68);
    }
    reinterpret_cast<Channel *>(this)->Channel::SetSession(session);  // LIFT: User has no declared base yet. Channel is the base at +0.
}

// 0x3e4650
void __cdecl User::SetPcCafeDebugCode(wchar_t *sCode, char level)
{
    char publisherCode = PublisherCode();
    if (publisherCode == 1 || publisherCode == 4 || publisherCode == 8)
    {
        wcsncpy(UserAt<wchar_t>(this, USER_PcCafeCode), sCode, 0x11u);
        *UserAt<char>(this, USER_ChargeBaseType) = 2;
    }
    else if (publisherCode == 2)
    {
        *UserAt<unsigned int>(this, USER_tencentPcCafeType) = 1;
        *UserAt<unsigned int>(this, USER_tencentPcCafeLevel) = level;
    }
    // LIFT: ContentsRuleConfig::_useTimeBasedPlaySchedule is bool at +0x752 (PDB).
    if (*reinterpret_cast<bool *>(reinterpret_cast<char *>(ContentsRuleConfig::Config) + 1874))
        reinterpret_cast<TimeBasedPlayInfoListView *>(UserAt<char>(this, USER_timeBasedPlayInfoList))->_isPcCafe = true;
}

// 0x3e46d0
bool __cdecl User::Initialize(short, unsigned __int64, ::id128 const &, wchar_t const *, wchar_t const *, unsigned __int64, int, int, int, int, int, ::User::ChargeApplyType, wchar_t const *const, int, char, wchar_t const *, __int64, int, int, __int64, int, int, int, __int64, __int64, ::LobbyCharacterSlot *, short, ::ContentsBan const *, int, int)
{
    LIFT_STUB(0x3e46d0);
}

// 0x3e4d60
bool __cdecl User::SetCharacterInfo(unsigned __int64, __int64, ::id128 const &, wchar_t const *, wchar_t const *, int, int, int, int, bool, int, int, ::User::ChargeApplyType, wchar_t const *, ::LobbyCharacterSlot *, short, ::ContentsBan const *, __int64)
{
    LIFT_STUB(0x3e4d60);
}

// 0x3e5330
bool __cdecl User::SetChargeInfo(wchar_t const *const, int, char)
{
    LIFT_STUB(0x3e5330);
}

// 0x3e54e0
void __cdecl User::SetPc(::Pc *)
{
    LIFT_STUB(0x3e54e0);
}

// 0x3e55c0
void __cdecl User::ResetPc(bool)
{
    LIFT_STUB(0x3e55c0);
}

// 0x3e56f0
void __cdecl User::resetPc(::RefCntObject *ref1, ::RefCntObject *, ::RefCntObject *)
{
    // LIFT: thunk. The first argument is the User (Channel base at +0). It jumps to resetPc(void).
    reinterpret_cast<User *>(ref1)->resetPc();
}

// 0x3e5700
void __cdecl User::resetPc(void)
{
    LIFT_STUB(0x3e5700);
}

// 0x3e5770
void __cdecl User::logCutOffAccessDelayEnterZoneTask(wchar_t const *)
{
    LIFT_STUB(0x3e5770);
}

// 0x3e5d40
::Pointer2< ::Pc> __cdecl User::GetPcPtr(void)
{
    LIFT_STUB(0x3e5d40);
}

// 0x3e5da0
void __cdecl User::SetContentsBanDebugCode(int, __int64, __int64)
{
    LIFT_STUB(0x3e5da0);
}

// 0x3e5e60
void __cdecl User::setExistContentsBan(void)
{
    LIFT_STUB(0x3e5e60);
}

// 0x3e5eb0
bool __cdecl User::IsBannedContents(char banId) const
{
    LIFT_STUB(0x3e5eb0);
}

// 0x3e5f50
bool __cdecl User::IsExistBannedContentsForReward(void) const
{
    LIFT_STUB(0x3e5f50);
}

// 0x3e5fe0
void __cdecl User::CheckBotMovePacketReceived(::Pc *)
{
    LIFT_STUB(0x3e5fe0);
}

// 0x3e60c0
void __cdecl User::CheckBotSummonedMovePacketReceived(::Pc *)
{
    LIFT_STUB(0x3e60c0);
}

// 0x3e6190
void __cdecl User::CheckBotEnterZone(wchar_t const *, int)
{
    LIFT_STUB(0x3e6190);
}

// 0x3e6320
void __cdecl User::checkBotPartyRecvCount(void)
{
    LIFT_STUB(0x3e6320);
}

// 0x3e69c0
void __cdecl User::SetExternalInfo(short, char const *, short, char const *, short, char const *, short, char const *)
{
    LIFT_STUB(0x3e69c0);
}

// 0x3e6cf0
void __cdecl User::TouchEnterWorld(void)
{
    LIFT_STUB(0x3e6cf0);
}

// 0x3e6f50
void __cdecl User::OnTimeBasedPlayTimeExpired(bool, bool, bool)
{
    LIFT_STUB(0x3e6f50);
}

// 0x3e70a0
void __cdecl User::SendToClientTimeBasedPlayInfoOk(void)
{
    LIFT_STUB(0x3e70a0);
}

// 0x3e7270
bool __cdecl User::CalcTimeBasedPlay(bool, bool &)
{
    LIFT_STUB(0x3e7270);
}

// 0x3e7420
bool __cdecl User::AutoTakeTimeBasedReward(__int64, bool, bool, bool)
{
    LIFT_STUB(0x3e7420);
}

// 0x3e7850
__cdecl User::BotScoreInfo::BotScoreInfo(void)
{
    LIFT_STUB(0x3e7850);
}

// 0x3e78e0
void __cdecl User::UpdateBotScoreLevel(void)
{
    LIFT_STUB(0x3e78e0);
}

// 0x3e7b80
void __cdecl User::DumpBotState(wchar_t *, int)
{
    LIFT_STUB(0x3e7b80);
}

// 0x3e7ea0
bool __cdecl User::UpdateAccountExpInfo(::AccountExpInfo const &)
{
    LIFT_STUB(0x3e7ea0);
}

// 0x3e8030
bool __cdecl User::SendUpdateAccountExpToLobby(::AccountExpInfo const &)
{
    LIFT_STUB(0x3e8030);
}

// 0x3e8170
bool __cdecl User::SendUpdateAccountContentQuotaToLobby(::AccountContentQuota const &)
{
    LIFT_STUB(0x3e8170);
}

// 0x3e8280
bool __cdecl User::SendUpdateAccountRecycleTimeToLobby(::AccountRecycleTime const &)
{
    LIFT_STUB(0x3e8280);
}

// 0x3e8390
void __cdecl User::AddBotState(::Data::BotScoringConditionConditionTypeType, __int64, wchar_t const *, int)
{
    LIFT_STUB(0x3e8390);
}

// 0x3e8440
void __cdecl User::ClearBotState(wchar_t const *, int)
{
    LIFT_STUB(0x3e8440);
}

// 0x3e84d0
void __cdecl User::addBotScore(int)
{
    LIFT_STUB(0x3e84d0);
}

// 0x3e8520
void __cdecl User::UpdateCombatForBotScore(bool, bool)
{
    LIFT_STUB(0x3e8520);
}

// 0x3e8620
void __cdecl User::StartCombatForBotScore(__int64, bool)
{
    LIFT_STUB(0x3e8620);
}

// 0x3e86f0
void __cdecl User::FinishCombatForBotScore(__int64, bool, bool)
{
    LIFT_STUB(0x3e86f0);
}

// 0x3e87b0
void __cdecl User::InitBotScore(bool, int)
{
    LIFT_STUB(0x3e87b0);
}

// 0x3e8900
bool __cdecl User::UpdateDeductionScore(bool, __int64)
{
    LIFT_STUB(0x3e8900);
}

// 0x3e8bc0
void __cdecl User::UpdateBotScore(bool)
{
    LIFT_STUB(0x3e8bc0);
}

// 0x3e9340
// LIFT: feature off (owner scope)
unsigned __int64 __cdecl User::GetGameGuardAuthCount(void)
{
    return 0;
}

// 0x3e9390
__cdecl UserManager::UserManager(void)
{
    LIFT_STUB(0x3e9390);
}

// 0x3e9440
__cdecl UserManager::~UserManager(void)
{
    LIFT_STUB(0x3e9440);
}

// 0x3e9530
bool __cdecl UserManager::add(::User *)
{
    LIFT_STUB(0x3e9530);
}

// 0x3e9790
::Pointer2< ::User> __cdecl UserManager::GetUserPtr(unsigned __int64)
{
    LIFT_STUB(0x3e9790);
}

// 0x3e9870
::User * __cdecl UserManager::RemoveWaitingUser(unsigned __int64)
{
    LIFT_STUB(0x3e9870);
}

// 0x3e9930
::Pointer2< ::User> __cdecl UserManager::GetWaitingUserPtr(unsigned __int64)
{
    LIFT_STUB(0x3e9930);
}

// 0x3e9a20
::User * __cdecl UserManager::CreateArenaReservedUser(short, __int64, unsigned __int64, ::Pc *, ::id128 const &, wchar_t const *, wchar_t const *, unsigned __int64, int, int, int, int, int, ::User::ChargeApplyType, wchar_t const *const, int, char, wchar_t const *, __int64, int, int, __int64, int, int, int, __int64, __int64, ::LobbyCharacterSlot *, short, ::ContentsBan const *, unsigned __int64 *, int, int)
{
    LIFT_STUB(0x3e9a20);
}

// 0x3ea130
::User * __cdecl UserManager::ConfirmArenaReservedUser(unsigned __int64, short, __int64)
{
    LIFT_STUB(0x3ea130);
}

// 0x3ea2c0
void __cdecl UserManager::RemoveTimeoutReservedUser(__int64, __int64)
{
    LIFT_STUB(0x3ea2c0);
}

// 0x3ea430
void __cdecl UserManager::Kick(unsigned __int64, short)
{
    LIFT_STUB(0x3ea430);
}

// 0x3ea7e0
bool __cdecl UserManager::CreateWaitingUser(short, unsigned __int64, ::Session *)
{
    LIFT_STUB(0x3ea7e0);
}

// 0x3ea960
::User * __cdecl UserManager::ConfirmUser(bool &, ::Pc *, unsigned __int64)
{
    LIFT_STUB(0x3ea960);
}

// 0x3eac50
::User * __cdecl UserManager::RemoveUser(unsigned __int64, unsigned __int64, __int64)
{
    LIFT_STUB(0x3eac50);
}

// 0x3eae90
bool __cdecl UserManager::LogoutUser(::User *, bool)
{
    LIFT_STUB(0x3eae90);
}

// 0x3eb0e0
::Pointer2< ::User> __cdecl UserManager::LogoutArenaUser(unsigned __int64)
{
    LIFT_STUB(0x3eb0e0);
}

// 0x3eb360
void __cdecl UserManager::LogoutArenaUsers(short)
{
    LIFT_STUB(0x3eb360);
}

// 0x3ebb80
void __cdecl UserManager::removeReservedUser(::User *, wchar_t const *)
{
    LIFT_STUB(0x3ebb80);
}

// 0x3ebca0
bool __cdecl CloseWaitManager::Add(::Session const *)
{
    LIFT_STUB(0x3ebca0);
}

// 0x3ebdf0
void __cdecl CloseWaitManager::Expire(void)
{
    LIFT_STUB(0x3ebdf0);
}
