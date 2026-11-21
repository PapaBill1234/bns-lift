// CliSession.obj (LobbyDaemon PDB, 2019 + PDB). Source: hr/LobbyDaemon/CliSession.c.
// ld-2 lifted part 1 (0x329d0..0x35eb0). The other functions are still stubs. A stub is not a lift.
#include <string.h>
#include <wchar.h>
#include "CliSession.h"
#include "CliSessionTable.h"
#include "LobbyMessage.h"
#include "Log.h"
#include "Memory.h"
#include "LiftStub.h"

// PDB public ?TLobbyError@@3W4LobbyError@@A. enter (0x359c0) writes it at TLS +0x60.
// LIFT: the PDB module of TLobbyError is not known. ❓ CliSession.obj is a guess.
__declspec(thread) LobbyError TLobbyError;

// LIFT: Presence::~Presence has no own RVA (empty; folded). The out-of-line definition gives the key function.
Presence::~Presence()
{
}

// 0x329d0
ServiceLocation::~ServiceLocation()
{
}

// 0x329f0
void CliSession::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x329f0);
}

// 0x32a40
// LIFT: the PDB has this private default ctor. It sets only the base, the members with own ctors and the lock.
CliSession::CliSession()
    : _acb(), _jumpingCharacterCreationQuota(), _characters(), _serviceEntries(), _auth(), _bans(), _quotaList(),
      _recycleTimeList(), _gradeService(), _lock()
{
}

// 0x32b60
CliSessionStopPcCafeChargeMessage::~CliSessionStopPcCafeChargeMessage()
{
    LIFT_STUB(0x32b60);
}

// 0x32bb0
TimeBasedPlayInfoList::~TimeBasedPlayInfoList()
{
    memset(_timeBasedPlayInfo, 0, sizeof(_timeBasedPlayInfo));
}

// 0x32be0
void TimeBasedPlayInfoList::ValidateDurations()
{
    LIFT_STUB(0x32be0);
}

// 0x32e20
void TimeBasedPlayInfoList::SetPlayInfoFromGame(TimeBasedPlayInfoList const& infoList)
{
    for (int i = 0; i < 2; ++i)
    {
        TimeBasedPlayInfo& info = _timeBasedPlayInfo[i];
        TimeBasedPlayInfo const& src = infoList._timeBasedPlayInfo[i];
        info.scheduleNumber = src.scheduleNumber;
        info.duration = src.duration;
        info.expireTimeUTC = src.expireTimeUTC;
        info.acknowledgedPlayTime = src.acknowledgedPlayTime;
        for (char j = 0; j < 4; ++j)
            info.rewardList[j] = src.rewardList[j];
        // Keep the old update time when the game sends no update time for a set schedule.
        if (info.scheduleNumber == 0 || src.lastUpdateTimeUTC != 0)
            info.lastUpdateTimeUTC = src.lastUpdateTimeUTC;
    }
}

// 0x32ed0
bool TimeBasedPlayInfoList::Compose(FragmentPacket&) const
{
    LIFT_STUB(0x32ed0);
}

// 0x33070
bool TimeBasedPlayInfoList::Compose(RepeatPacketComposer&, Packet&) const
{
    LIFT_STUB(0x33070);
}

// 0x331e0
bool TimeBasedPlayInfoList::Decompose(RepeatPacketDecomposer&, Packet const*)
{
    LIFT_STUB(0x331e0);
}

// 0x33360
// LIFT: _id and _userid copy ID128_ID_ZERO (0x14012d870, PDB public ?ID128_ID_ZERO@@3Tid128@@B). The loads are at
// 0x14003336a and 0x140033389. The HR shows only zero stores, so the disassembly gives the global.
GameAccount::GameAccount() : _id(ID128_ID_ZERO), _userid(ID128_ID_ZERO)
{
    memset(&_dbfield, 0, sizeof(_dbfield));
    _userName[0] = L'\0';
}

// 0x33450
GameAccount::~GameAccount()
{
}

// 0x33490
CliSession::CliSession(unsigned long long clikey, CliSessionTable* table)
    : _state(0), _clikey(clikey), _ipv4(0), _acb(), _jumpingCharacterCreationQuota(), _authProviderCodeSize(0),
      _externalAccountKeySize(0), _externalAccountNameSize(0), _externalAccountDataSize(0), _characters(),
      _serviceEntries(), _auth(), _bans(), _quotaList(), _recycleTimeList(), _table(table), _npLogin(false),
      _login(false), _isMobile(false), _teen(false), _scheduledEndTime(nullptr), _presence(nullptr), _srvloc(nullptr),
      _reservedStopPlay(nullptr), _chargeKey(nullptr), _chargeStopRequestTxnId(0),
      // LIFT: 0x33490 is the only caller of GradeService(int) 0x534d0, so LTCG removed the argument (no edx load at
      // 0x1400335bc; the HR shows an uninitialised edx). The callee stores the constant in
      // `_gradeLevel.level = defaultLevel` (0x140053539, `mov dword ptr [rbx+4], 1`). So the argument is 1.
      _gradeService(1),
      _pcCafeCode(nullptr), _pcCafe(nullptr), _pcCafeCharged(false), _mileageSlot(nullptr),
      // LIFT: _infoGateToken copies ID128_GUID_ZERO (0x14012d880, PDB public ?ID128_GUID_ZERO@@3Tid128@@B). The
      // loads are at 0x1400335dd and 0x1400335eb. GameAccount() uses ID128_ID_ZERO (0x14012d870) instead.
      _infoGateToken(ID128_GUID_ZERO), _renameUserServiceEntry(nullptr), _lock()
{
    memset(_authProviderCode, 0, sizeof(_authProviderCode));
    memset(_externalAccountKey, 0, sizeof(_externalAccountKey));
    memset(_externalAccountName, 0, sizeof(_externalAccountName));
    memset(_externalAccountData, 0, sizeof(_externalAccountData));
    _jumpingCharacterCreationQuota.Clear();
}

// 0x336b0
CliSession::~CliSession()
{
    LIFT_STUB(0x336b0);
}

// 0x33cc0
void CliSession::finalize()
{
    cleanupCharge();
    leave();
    // LIFT: setPresence(nullptr) is inlined here (the Free line 1313 is the setPresence line). 0x33cc0
    setPresence(nullptr);
    logout();
    _table->Delete(_clikey);
}

// 0x33d60
bool CliSession::npLogin(id128 const& userId)
{
    if (userId.id[0] == 0 && userId.id[1] == 0)
    {
        // LIFT: the original tests this for null before it reads _state and _clikey. 0x33d60
        CliSession const* cs = this;
        unsigned int state = (cs != nullptr) ? static_cast<unsigned int>(cs->_state) : 0;
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 761,
                   L"[cs], np login fail; invalid parameter, cli-key:0x%I64X, cli-state:%d.%d",
                   (cs != nullptr) ? cs->_clikey : 0ULL, state >> 16, state & 0xFFFF);
        return false;
    }
    _acb._userid = userId;
    _npLogin = true;
    Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 769,
               L"[cs], np login ok, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, cli-key:0x%I64X, "
               L"cli-state:%d.%d",
               userId.guid.id1, userId.guid.id2, userId.guid.id3, userId.guid.id4[0], userId.guid.id4[1],
               userId.guid.id4[2], userId.guid.id4[3], userId.guid.id4[4], userId.guid.id4[5], userId.guid.id4[6],
               userId.guid.id4[7], _clikey, static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
    return true;
}

// 0x33f00
bool CliSession::login(id128 const&, wchar_t const*, char, wchar_t const*)
{
    LIFT_STUB(0x33f00);
}

// 0x34750
bool CliSession::logout()
{
    LIFT_STUB(0x34750);
}

// 0x349a0
bool CliSession::loadDB()
{
    LIFT_STUB(0x349a0);
}

// 0x35730
bool CliSession::setPresence(Presence* presence)
{
    if (_presence != nullptr)
    {
        _presence->OnUnset(_table, this);
        // LIFT: the original global operator delete(void*) (0x32b50) is empty. The class operator delete is empty too
        // (CliSession.h). Free gives the memory back.
        delete _presence;
        Memory::_Manager[2]->Free(_presence, L"CliSession.cpp", 1313);
        _presence = nullptr;
    }
    if (presence != nullptr)
    {
        if (!presence->OnSet(_table, this))
        {
            Log::Write(Log::LT_ERROR, L"CliSession.cpp", 1319,
                       L"[cs], set presence fail; on set fail, cli-key:0x%I64X, cli-state:%d.%d", _clikey,
                       static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
            return false;
        }
        _presence = presence;
    }
    return true;
}

// 0x35810
void CliSession::closePresence()
{
    if (_presence != nullptr)
    {
        _presence->Close(this);
        Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 1340,
                   L"[cs], close cli-session presence, presence:%d, cli-key:0x%I64X, cli-state:%d.%d",
                   _presence->GetKind(), _clikey, static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
    }
    else
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 1343,
                   L"[cs], close cli-session presence fail; no presence exists, cli-key:0x%I64X, cli-state:%d.%d",
                   _clikey, static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
    }
}

// 0x358e0
void CliSession::kickPresence(int reason)
{
    if (_presence != nullptr)
    {
        _presence->Kick(this, reason);
        Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 1350,
                   L"[cs], kick cli-session presence, reason:%d, presence:%d, cli-key:0x%I64X, cli-state:%d.%d",
                   reason, _presence->GetKind(), _clikey, static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
    }
    else
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 1353,
                   L"[cs], kick cli-session presence fail; no presence exists, cli-key:0x%I64X, cli-state:%d.%d",
                   _clikey, static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
    }
}

// 0x359c0
bool CliSession::enter(ServiceLocation* srvloc)
{
    if (srvloc == nullptr)
    {
        // LIFT: the original log macro tests the session pointer for null (0x359c0). Keep the test.
        CliSession const* cs = this;
        unsigned int state = (cs != nullptr) ? static_cast<unsigned int>(cs->_state) : 0;
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 1359,
                   L"[cs], enter service location fail; invalid parameter, cli-key:0x%I64X, cli-state:%d.%d",
                   (cs != nullptr) ? cs->_clikey : 0ULL, state >> 16, state & 0xFFFF);
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }
    if (_srvloc != nullptr)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 1373,
                   L"[cs], enter service location exception; already has service location; force to leave service "
                   L"location and continue, old-service-location-kind:%d, old-service-location:%d, "
                   L"new-service-location-kind:%d, new-service-location:%d, cli-key:0x%I64X, cli-state:%d.%d",
                   _srvloc->GetKind(), static_cast<int>(_srvloc->_wid), srvloc->GetKind(),
                   static_cast<int>(srvloc->_wid), _clikey, static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
        _srvloc->Leave(this);
        // LIFT: the original global operator delete(void*) (0x32b50) is empty. The class operator delete is empty too
        // (CliSession.h). Free gives the memory back.
        delete _srvloc;
        Memory::_Manager[2]->Free(_srvloc, L"CliSession.cpp", 1375);
        _srvloc = nullptr;
    }
    if (!srvloc->Enter(this))
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 1379,
                   L"[cs], enter service location fail; enter fail, kind:%d, wid:%d, cli-key:0x%I64X, cli-state:%d.%d",
                   srvloc->GetKind(), static_cast<int>(srvloc->_wid), _clikey,
                   static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
        return false;
    }
    _srvloc = srvloc;
    Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 1385,
               L"[cs], enter service location ok, kind:%d, wid:%d, cli-key:0x%I64X, cli-state:%d.%d",
               srvloc->GetKind(), static_cast<int>(srvloc->_wid), _clikey, static_cast<unsigned int>(_state) >> 16,
               _state & 0xFFFF);
    return true;
}

// 0x35c10
void CliSession::leave()
{
    if (_srvloc != nullptr)
    {
        _srvloc->Leave(this);
        Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 1394,
                   L"[cs], leave service location ok, kind:%d, wid:%d, cli-key:0x%I64X, cli-state:%d.%d",
                   _srvloc->GetKind(), static_cast<int>(_srvloc->_wid), _clikey,
                   static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
        // LIFT: the original global operator delete(void*) (0x32b50) is empty. The class operator delete is empty too
        // (CliSession.h). Free gives the memory back.
        delete _srvloc;
        Memory::_Manager[2]->Free(_srvloc, L"CliSession.cpp", 1396);
        _srvloc = nullptr;
    }
}

// 0x35cf0
Character* CliSession::getCharacter(unsigned long long)
{
    LIFT_STUB(0x35cf0);
}

// 0x35d30
void CliSession::removeCharacter(unsigned long long)
{
    LIFT_STUB(0x35d30);
}

// 0x35d90
Character* CliSession::getPlayingCharacter()
{
    LIFT_STUB(0x35d90);
}

// 0x35e20
void CliSession::setChargeKey(wchar_t const* chargeKey)
{
    if (_chargeKey != nullptr)
    {
        Memory::_Manager[2]->Free(_chargeKey, L"CliSession.cpp", 1496);
        _chargeKey = nullptr;
    }
    if (chargeKey != nullptr)
    {
        _chargeKey = static_cast<wchar_t*>(Memory::_Manager[2]->AllocZero(130, L"CliSession.cpp", 1499));
        wcscpy_s(_chargeKey, 65, chargeKey);
    }
}

// 0x35eb0
void CliSession::completeRequestChargeStop(bool)
{
    LIFT_STUB(0x35eb0);
}

// 0x35fc0
void CliSession::cleanupCharge()
{
    LIFT_STUB(0x35fc0);
}

// 0x36240
void CliSession::HandleGameGetGradeList(GamedChannel*, unsigned long long, char, unsigned long long, int) const
{
    LIFT_STUB(0x36240);
}

// 0x36df0
bool CliSession::fetchContentBans(FragmentPacket*)
{
    LIFT_STUB(0x36df0);
}

// 0x36fa0
bool CliSession::fetchAccountContentQuotaList(FragmentPacket*)
{
    LIFT_STUB(0x36fa0);
}

// 0x371b0
bool CliSession::fetchAccountRecycleTimeList(FragmentPacket*)
{
    LIFT_STUB(0x371b0);
}

// 0x373a0
bool CliSession::addLobbyService(LobbyService*)
{
    LIFT_STUB(0x373a0);
}

// 0x37530
void CliSession::removeLobbyService(unsigned long long)
{
    LIFT_STUB(0x37530);
}

// 0x37670
LobbyService* CliSession::getLobbyServiceByType(unsigned long long, int)
{
    LIFT_STUB(0x37670);
}

// 0x376b0
LobbyService* CliSession::queryLobbyService(Character*)
{
    LIFT_STUB(0x376b0);
}

// 0x37790
bool CliSession::addRenameUserService(RenameUserService*)
{
    LIFT_STUB(0x37790);
}

// 0x37890
void CliSession::setScheduledEndTime(GameTimeScheduleNode*)
{
    LIFT_STUB(0x37890);
}

// 0x37950
void CliSession::releaseScheduledEndTime()
{
    LIFT_STUB(0x37950);
}

// 0x37af0
bool CliSession::FetchCharacterInfo(id128 const&, Packet*, PacketComposer*) const
{
    LIFT_STUB(0x37af0);
}

// 0x37c70
bool CliSession::FetchServiceEntryList(FragmentPacket*) const
{
    LIFT_STUB(0x37c70);
}

// 0x37de0
bool CliSession::UpdateBotScore(unsigned long long, int)
{
    LIFT_STUB(0x37de0);
}

// 0x37eb0
bool CliSession::BindCharacterSlot(unsigned long long, id128 const&)
{
    LIFT_STUB(0x37eb0);
}

// 0x381c0
bool CliSession::UpdateCharacterData(unsigned long long, short, char*, short)
{
    LIFT_STUB(0x381c0);
}

// 0x38380
bool CliSession::UpdateCharacterLevel(unsigned long long, short)
{
    LIFT_STUB(0x38380);
}

// 0x38500
bool CliSession::UpdateAccountData(unsigned long long, int, TimeBasedPlayInfoList&)
{
    LIFT_STUB(0x38500);
}

// 0x38670
bool CliSession::UpdateTimeBasedPlayReward(unsigned long long, int, char, short, UserPromotionReward&, long long)
{
    LIFT_STUB(0x38670);
}

// 0x392c0
bool CliSession::NotifyGoodsInventoryChangedAlongPresence(GoodsInventoryChangedNotifyParam&)
{
    LIFT_STUB(0x392c0);
}

// 0x39820
bool CliSession::ReserveStopPlay(bool, int, int)
{
    LIFT_STUB(0x39820);
}

// 0x39a70
bool CliSession::TimeoutStopPlay(StopPlayTimerEvent*)
{
    LIFT_STUB(0x39a70);
}

// 0x39be0
bool CliSession::OnChargeStopRequested(unsigned int)
{
    LIFT_STUB(0x39be0);
}

// 0x39cc0
bool CliSession::ApplyNewChargeItem(wchar_t const*, long, unsigned int, short)
{
    LIFT_STUB(0x39cc0);
}

// 0x39e50
bool CliSession::NotifyChargeRemainTime(long, short, unsigned int)
{
    LIFT_STUB(0x39e50);
}

// 0x39f70
bool CliSession::setRole(unsigned int const* const, int)
{
    LIFT_STUB(0x39f70);
}

// 0x3a000
bool CliSession::setPcCafeCode(wchar_t const*)
{
    LIFT_STUB(0x3a000);
}

// 0x3a100
void CliSession::setPcCafe(PcCafe*)
{
    LIFT_STUB(0x3a100);
}

// 0x3a190
void CliSession::onPcCafeChargeStart()
{
    LIFT_STUB(0x3a190);
}

// 0x3a2c0
void CliSession::onPcCafeChargeStop()
{
    LIFT_STUB(0x3a2c0);
}

// 0x3a3f0
AnonymousLobbyGatePresence::AnonymousLobbyGatePresence(LobbyGateChannel*, unsigned long long)
{
    LIFT_STUB(0x3a3f0);
}

// 0x3a4a0
bool AnonymousLobbyGatePresence::IsEqual(Presence const*) const
{
    LIFT_STUB(0x3a4a0);
}

// 0x3a530
bool AnonymousLobbyGatePresence::OnSet(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3a530);
}

// 0x3a600
void AnonymousLobbyGatePresence::OnUnset(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3a600);
}

// 0x3a650
void AnonymousLobbyGatePresence::Close(CliSession*)
{
    LIFT_STUB(0x3a650);
}

// 0x3a670
void AnonymousLobbyGatePresence::Kick(CliSession*, int)
{
    LIFT_STUB(0x3a670);
}

// 0x3a760
bool LobbyGatePresence::IsEqual(Presence const*) const
{
    LIFT_STUB(0x3a760);
}

// 0x3a7d0
bool LobbyGatePresence::OnSet(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3a7d0);
}

// 0x3aa30
void LobbyGatePresence::OnUnset(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3aa30);
}

// 0x3abc0
void LobbyGatePresence::Close(CliSession*)
{
    LIFT_STUB(0x3abc0);
}

// 0x3ac20
void LobbyGatePresence::Kick(CliSession*, int)
{
    LIFT_STUB(0x3ac20);
}

// 0x3adf0
bool GameWorldPresence::IsEqual(Presence const*) const
{
    LIFT_STUB(0x3adf0);
}

// 0x3ae90
bool GameWorldPresence::OnSet(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3ae90);
}

// 0x3aff0
void GameWorldPresence::OnUnset(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3aff0);
}

// 0x3b0c0
void GameWorldPresence::Close(CliSession*)
{
    LIFT_STUB(0x3b0c0);
}

// 0x3b120
void GameWorldPresence::Kick(CliSession*, int)
{
    LIFT_STUB(0x3b120);
}

// 0x3b360
GameServiceLocation::~GameServiceLocation()
{
    LIFT_STUB(0x3b360);
}

// 0x3b3d0
void GameServiceLocation::OnEnter(CliSession*)
{
    LIFT_STUB(0x3b3d0);
}

// 0x3b540
void GameServiceLocation::OnLeave(CliSession*)
{
    LIFT_STUB(0x3b540);
}

// 0x3b6f0
bool GameServiceLocation::Enter(CliSession*)
{
    LIFT_STUB(0x3b6f0);
}

// 0x3b9a0
bool GameServiceLocation::Leave(CliSession*)
{
    LIFT_STUB(0x3b9a0);
}

// 0x3bb60
bool GameServiceLocation::ReserveStopPlay(CliSession*, StopPlayTimerEvent*)
{
    LIFT_STUB(0x3bb60);
}

// 0x3bc80
bool GameServiceLocation::TimeoutStopPlay(CliSession*, StopPlayTimerEvent*)
{
    LIFT_STUB(0x3bc80);
}

// 0x3bda0
void GameServiceLocation::NotifyStopPlay(CliSession*, int)
{
    LIFT_STUB(0x3bda0);
}
