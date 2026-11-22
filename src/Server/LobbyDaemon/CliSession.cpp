// CliSession.obj (LobbyDaemon PDB, 2019 + PDB). Source: hr/LobbyDaemon/CliSession.c.
// ld-2 lifts part 1. ld-7 lifts part 2. A stub is not a lift.
#include <string.h>
#include <wchar.h>
#include "Character.h"
#include "CliSession.h"
#include "CliSessionTable.h"
#include "FragmentPacket.h"
#include "LobbyDB.h"
#include "LobbyGateChannel.h"
#include "LobbyMessage.h"
#include "LobbyService.h"
#include "PcCafe.h"
#include "AlertSender.h"
#include "StsMsgGrade.h"
#include "Log.h"
#include "Memory.h"
#include "LiftStub.h"

// PDB public ?TLobbyError@@3W4LobbyError@@A. enter (0x359c0) writes it at TLS +0x60.
// LIFT: the PDB module of TLobbyError is not known. ❓ CliSession.obj is a guess.
__declspec(thread) LobbyError TLobbyError;

// PDB global GRoleAuthorityTable (.data rva 0x201d70, 32 bytes). Data from LobbyDaemon.exe (2019 + PDB).
// LIFT: the PDB module of GRoleAuthorityTable is not known ([globals]). ❓ CliSession.obj is a guess.
// The field order is Authority::Operation (manage character, create character, enter on entrance, enter on full).
Authority::Table GRoleAuthorityTable[Role::ROLE_COUNT] = {
    {{false, false, false, false}},  // 0
    {{true, true, true, true}},      // ROLE_ADMIN
    {{false, false, false, false}},  // ROLE_CBT
    {{false, false, false, true}},   // ROLE_VIP
    {{false, false, false, false}},  // ROLE_IN_COMPANY
    {{false, false, false, false}},  // ROLE_CBT_PC_CAFE
    {{false, false, false, false}},  // ROLE_FULL_CBT
    {{true, true, true, true}},      // ROLE_QA
};

// LIFT: Presence::~Presence has no own RVA (empty; folded). The out-of-line definition gives the key function.
Presence::~Presence()
{
}

// 0x329d0
ServiceLocation::~ServiceLocation()
{
}

// LIFT: CliSession::_pool (.data RVA 0x2042b0) has no definition yet. Its dynamic init (0x11dd50) and atexit dtor
// (0x11ebc0) are Not done in card ld-13. The original arguments are id 1, objsize 0x8d0 and desc L"CliSession".
// ObjectPool.cpp is the SmartCouponDaemon form and is not in lift_lobbydaemon. A definition here does not link in the
// VS2010 build (no ObjPool::ObjPool, ObjPool::~ObjPool). Define it when the LobbyDaemon ObjectPool module is lifted.

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

#pragma comment(linker, "/INCLUDE:?NotifyChangedGrade@CliSession@@QEAA_NAEBU_StsMsgNotifyGradeNotifyGradeChanged@StsMsgLib@@@Z") // LIFT: keep until the caller is lifted (0x360a0).
// 0x360a0
bool CliSession::NotifyChangedGrade(StsMsgLib::_StsMsgNotifyGradeNotifyGradeChanged const& msg)
{
    bool result = true;
    _lock.Enter();
    int state = _state;
    if (_gradeService._initGradeList)
    {
        result = _gradeService.ApplyChangedGrade(this, &msg);
        if (result && (state == 0x10003 || state == 0x20000 ||
                       (state > 0x30000 && (state <= 0x30002 || state == 0x40000))) && _presence != nullptr)
            _presence->NotifyChangedGrade(this, msg);
    }
    _lock.Leave();
    return result;
}

#pragma comment(linker, "/INCLUDE:?NotifyChangedGradeLevel@CliSession@@QEAA_NAEBU_StsMsgNotifyGradeNotifyScoreChanged@StsMsgLib@@@Z") // LIFT: keep until the caller is lifted (0x36170).
// 0x36170
bool CliSession::NotifyChangedGradeLevel(StsMsgLib::_StsMsgNotifyGradeNotifyScoreChanged const& msg)
{
    bool result = true;
    _lock.Enter();
    int state = _state;
    if (_gradeService._initGradeLevel)
    {
        result = _gradeService.ApplyChangedGradeLevel(this, &msg);
        if (result && (state == 0x10003 || state == 0x20000 ||
                       (state > 0x30000 && (state <= 0x30002 || state == 0x40000))) && _presence != nullptr)
            _presence->NotifyChangedGradeLevel(this, msg);
    }
    _lock.Leave();
    return result;
}

// 0x36240
void CliSession::HandleGameGetGradeList(GamedChannel*, unsigned long long, char, unsigned long long, int) const
{
    LIFT_STUB(0x36240);
}

#pragma comment(linker, "/INCLUDE:?setContentBans@CliSession@@QEAAXPEAU_StsMsgResponseListUserBans@StsMsgLib@@@Z") // LIFT: keep until the caller is lifted (0x366e0).
// 0x366e0
void CliSession::setContentBans(StsMsgLib::_StsMsgResponseListUserBans* bans)
{
    _bans.clear();
    if (bans == nullptr || bans->nUserBanCount <= 0)
        return;
    _bans.reserve(static_cast<size_t>(bans->nUserBanCount) + 1);
    for (int i = 0; i < bans->nUserBanCount; ++i)
    {
        StsMsgLib::UserBan const& ban = bans->pUserBanList[i];
        if (ban.nContentBanId <= 0)
        {
            Log::Write(Log::LT_ERROR, L"CliSession.cpp", 1726,
                       L"[cs], set content-ban fail; invalid content-ban-id, id:%d, policy-id:%s, from:%I64d, "
                       L"to:%I64d, cli-key:0x%I64X, cli-state:%d.%d",
                       ban.nContentBanId, ban.pwszContenBanPolicyId != nullptr ? ban.pwszContenBanPolicyId : L"(null)",
                       ban.tEffectiveFrom, ban.tEffectiveUntil, _clikey,
                       static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
            continue;
        }
        std::vector<ContentBan, StlAllocator<ContentBan, 2> >::iterator item = _bans.begin();
        for (; item != _bans.end(); ++item)
        {
            if (item->id == ban.nContentBanId)
                break;
        }
        if (item == _bans.end())
        {
            ContentBan newBan = {};
            newBan.id = ban.nContentBanId;
            newBan.from = ban.tEffectiveFrom;
            newBan.to = ban.tEffectiveUntil;
            _bans.push_back(newBan);
        }
        else if (item->to < ban.tEffectiveUntil)
        {
            item->to = ban.tEffectiveUntil;
        }
        Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 1747,
                   L"[cs], set content-ban, id:%d, policy-id:%s, from:%I64d, to:%I64d, cli-key:0x%I64X, cli-state:%d.%d",
                   ban.nContentBanId, ban.pwszContenBanPolicyId != nullptr ? ban.pwszContenBanPolicyId : L"(null)",
                   ban.tEffectiveFrom, ban.tEffectiveUntil, _clikey,
                   static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
    }
}

#pragma comment(linker, "/INCLUDE:?setRMSInquiryResult@CliSession@@QEAAXPEAU_StsMsgResponseRiskMgmtInquiry@StsMsgLib@@@Z") // LIFT: keep until the caller is lifted (0x36960).
// 0x36960
void CliSession::setRMSInquiryResult(StsMsgLib::_StsMsgResponseRiskMgmtInquiry* resp)
{
    if (resp != nullptr && resp->pszResult != nullptr && strcmp(resp->pszResult, "decline") == 0)
    {
        for (std::vector<ContentBan, StlAllocator<ContentBan, 2> >::const_iterator i = _bans.begin(); i != _bans.end(); ++i)
        {
            if (i->id == CONTENT_BAN_ID_RMS_INQUIRY)
            {
                Log::Write(Log::LT_ERROR, L"CliSession.cpp", 1777,
                           L"[rms], rms inquiry failed, content ban id already exists; content-ban id:%d", i->id);
                return;
            }
        }
        ContentBan newBan = {};
        newBan.id = CONTENT_BAN_ID_RMS_INQUIRY;
        newBan.to = 0x7FFFFFFFFFFFFFFFLL;
        _bans.push_back(newBan);
    }
}

#pragma comment(linker, "/INCLUDE:?fetchContentBans@CliSession@@QEAA_NPEAVFragmentPacket@@@Z") // LIFT: keep until the caller is lifted (0x36df0).
// 0x36df0
bool CliSession::fetchContentBans(FragmentPacket* fp)
{
    if (fp == nullptr)
    {
        CliSession const* cs = this;
        unsigned int state = (cs != nullptr) ? static_cast<unsigned int>(cs->_state) : 0;
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 1896,
                   L"[cs], fetch content bans fail; invalid parameter, cli-key:0x%I64X, cli-state:%d.%d",
                   (cs != nullptr) ? cs->_clikey : 0ULL, state >> 16, state & 0xFFFF);
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }

    fp->StartRepeat();
    for (std::vector<ContentBan, StlAllocator<ContentBan, 2> >::const_iterator i = _bans.begin(); i != _bans.end(); ++i)
    {
        if (fp->FreeSize() < 20)
            fp->packet.Allocate(&fp->composer);
        if (fp->Compose(3, i->id, i->from, i->to) == 0)
        {
            TLobbyError = LOBERR_SYSTEM;
            return false;
        }
        fp->IncRepeatCount();
    }
    fp->composer.PopRepeatCount();
    return true;
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

#pragma comment(linker, "/INCLUDE:?addLobbyService@CliSession@@QEAA_NPEAVLobbyService@@@Z") // LIFT: keep until the caller is lifted (0x373a0).
// 0x373a0
bool CliSession::addLobbyService(LobbyService* serviceEntry)
{
    CliSession const* cs = this;
    if (serviceEntry == nullptr)
    {
        unsigned int state = (cs != nullptr) ? static_cast<unsigned int>(cs->_state) : 0;
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2008,
                   L"[cs], add lobby-service fail; invalid param, cli-key:0x%I64X, cli-state:%d.%d",
                   (cs != nullptr) ? cs->_clikey : 0ULL, state >> 16, state & 0xFFFF);
        return false;
    }
    _serviceEntries.push_back(serviceEntry);
    unsigned int state = (cs != nullptr) ? static_cast<unsigned int>(cs->_state) : 0;
    Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 2014,
               L"[cs], add lobby-service ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X, "
               L"cli-key:0x%I64X, cli-state:%d.%d",
               serviceEntry->GetDB().serviceId, serviceEntry->GetDB().serviceType, serviceEntry->GetDB().serviceState,
               serviceEntry->GetDB().itemInstanceId, (cs != nullptr) ? cs->_clikey : 0ULL, state >> 16, state & 0xFFFF);
    return true;
}

#pragma comment(linker, "/INCLUDE:?removeLobbyService@CliSession@@QEAAX_K@Z") // LIFT: keep until the caller is lifted (0x37530).
// 0x37530
void CliSession::removeLobbyService(unsigned long long serviceId)
{
    if (serviceId == 0)
    {
        CliSession const* cs = this;
        unsigned int state = (cs != nullptr) ? static_cast<unsigned int>(cs->_state) : 0;
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2023,
                   L"[cs], remove service entry fail; invalid parameter, cli-key:0x%I64X, cli-state:%d.%d",
                   (cs != nullptr) ? cs->_clikey : 0ULL, state >> 16, state & 0xFFFF);
        return;
    }
    for (std::vector<LobbyService*, StlAllocator<LobbyService*, 2> >::iterator i = _serviceEntries.begin();
         i != _serviceEntries.end(); ++i)
    {
        if (*i != nullptr && serviceId == (*i)->GetDB().serviceId)
        {
            _serviceEntries.erase(i);
            Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 2040,
                       L"[cs], remove service entry ok, lobby-service-id:0x%I64X, cli-key:0x%I64X, cli-state:%d.%d",
                       serviceId, _clikey, static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
            return;
        }
    }
    Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2042,
               L"[cs], remove service entry fail; no such entry exists, lobby-service-id:0x%I64X, "
               L"cli-key:0x%I64X, cli-state:%d.%d",
               serviceId, _clikey, static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
}

#pragma comment(linker, "/INCLUDE:?getLobbyServiceByType@CliSession@@QEAAPEAVLobbyService@@_KH@Z") // LIFT: keep until the caller is lifted (0x37670).
// 0x37670
LobbyService* CliSession::getLobbyServiceByType(unsigned long long serviceId, int type)
{
    for (std::vector<LobbyService*, StlAllocator<LobbyService*, 2> >::iterator i = _serviceEntries.begin();
         i != _serviceEntries.end(); ++i)
    {
        LobbyService* serviceEntry = *i;
        if (serviceEntry != nullptr && serviceEntry->GetDB().serviceId == serviceId)
        {
            if (serviceEntry->GetDB().serviceType == type)
                return *i;
            return nullptr;
        }
    }
    return nullptr;
}

#pragma comment(linker, "/INCLUDE:?queryLobbyService@CliSession@@QEAAPEAVLobbyService@@PEAVCharacter@@@Z") // LIFT: keep until the caller is lifted (0x376b0).
// 0x376b0
LobbyService* CliSession::queryLobbyService(Character* pc)
{
    if (pc == nullptr)
    {
        CliSession const* cs = this;
        unsigned int state = (cs != nullptr) ? static_cast<unsigned int>(cs->_state) : 0;
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2076,
                   L"[cs], query service entry fail; invalid parameter, cli-key:0x%I64X, cli-state:%d.%d",
                   (cs != nullptr) ? cs->_clikey : 0ULL, state >> 16, state & 0xFFFF);
        return nullptr;
    }
    for (std::vector<LobbyService*, StlAllocator<LobbyService*, 2> >::iterator i = _serviceEntries.begin();
         i != _serviceEntries.end(); ++i)
    {
        LobbyService* serviceEntry = *i;
        if (serviceEntry != nullptr && serviceEntry->IsServiceTarget(pc))
            return serviceEntry;
    }
    return nullptr;
}

#pragma comment(linker, "/INCLUDE:?addRenameUserService@CliSession@@QEAA_NPEAVRenameUserService@@@Z") // LIFT: keep until the caller is lifted (0x37790).
// 0x37790
bool CliSession::addRenameUserService(RenameUserService* serviceEntry)
{
    if (serviceEntry == nullptr)
    {
        CliSession const* cs = this;
        unsigned int state = (cs != nullptr) ? static_cast<unsigned int>(cs->_state) : 0;
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2132,
                   L"[cs], add rename user service fail; invalid param, cli-key:0x%I64X, cli-state:%d.%d",
                   (cs != nullptr) ? cs->_clikey : 0ULL, state >> 16, state & 0xFFFF);
        return false;
    }
    if (_renameUserServiceEntry != nullptr)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2137,
                   L"[cs], add rename user service fail; already exists, cli-key:0x%I64X, cli-state:%d.%d",
                   _clikey, static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
        return false;
    }
    unsigned int state = static_cast<unsigned int>(_state);
    _renameUserServiceEntry = serviceEntry;
    Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 2143,
               L"[cs], add rename user service ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X, "
               L"cli-key:0x%I64X, cli-state:%d.%d",
               serviceEntry->GetDB().serviceId, serviceEntry->GetDB().serviceType, serviceEntry->GetDB().serviceState,
               serviceEntry->GetDB().itemInstanceId, _clikey, state >> 16, state & 0xFFFF);
    return true;
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

#pragma comment(linker, "/INCLUDE:?FetchCharacterInfoList@CliSession@@QEBA?AW4ErrCode@1@PEAVFragmentPacket@@@Z") // LIFT: keep until the caller is lifted (0x379b0).
// 0x379b0
CliSession::ErrCode CliSession::FetchCharacterInfoList(FragmentPacket* fp) const
{
    // LIFT: the const PDB function enters and leaves the session lock (0x379b0).
    CriticalSection& lock = const_cast<CriticalSection&>(_lock);
    lock.Enter();
    if ((_state & 0xFFFF0000) != 0x20000 && _state != 0x10003)
    {
        lock.Leave();
        return ERR_INVALID_STATE;
    }
    fp->StartRepeat();
    for (std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator i = _characters.begin();
         i != _characters.end(); ++i)
    {
        Character* pc = *i;
        if (pc != nullptr)
        {
            int state = pc->_db.state;
            if (state == Character::IN_NORMAL || state == Character::IN_TRY_DELETE ||
                state == Character::IN_WAIT_DELETE || state == Character::IN_TRY_RESTORE)
            {
                if (!pc->FetchCharacterInfo(fp))
                {
                    lock.Leave();
                    return ERR_SYSTEM;
                }
                fp->IncRepeatCount();
            }
        }
    }
    fp->composer.PopRepeatCount();
    lock.Leave();
    return ERR_OK;
}

#pragma comment(linker, "/INCLUDE:?FetchCharacterInfo@CliSession@@QEBA_NAEBTid128@@PEAVPacket@@PEAVPacketComposer@@@Z") // LIFT: keep until the caller is lifted (0x37af0).
// 0x37af0
bool CliSession::FetchCharacterInfo(id128 const& slotid, Packet* p, PacketComposer* pcr) const
{
    if (p == nullptr || pcr == nullptr)
    {
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }
    // LIFT: the const PDB function enters and leaves the session lock (0x37af0).
    CriticalSection& lock = const_cast<CriticalSection&>(_lock);
    lock.Enter();
    bool result = false;
    if ((_state & 0xFFFF0000) == 0x20000 || _state == 0x10003)
    {
        id128 id = slotid;
        Character* pc = nullptr;
        if (id.id[0] != ID128_ID_ZERO.id[0] || id.id[1] != ID128_ID_ZERO.id[1])
        {
            for (std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator i = _characters.begin();
                 i != _characters.end(); ++i)
            {
                if (*i != nullptr && (*i)->_db.slotid.id[0] == id.id[0] && (*i)->_db.slotid.id[1] == id.id[1])
                {
                    pc = *i;
                    break;
                }
            }
        }
        if (pc == nullptr)
            TLobbyError = LOBERR_NO_SUCH_CHARACTER;
        else if (!pc->FetchCharacterInfo(p, pcr))
            TLobbyError = LOBERR_SYSTEM;
        else
            result = true;
    }
    else
    {
        TLobbyError = LOBERR_INVALID_SESSION_STATE;
    }
    lock.Leave();
    return result;
}

#pragma comment(linker, "/INCLUDE:?FetchServiceEntryList@CliSession@@QEBA_NPEAVFragmentPacket@@@Z") // LIFT: keep until the caller is lifted (0x37c70).
// 0x37c70
bool CliSession::FetchServiceEntryList(FragmentPacket* fp) const
{
    if (fp == nullptr)
    {
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }
    // LIFT: the const PDB function enters and leaves the session lock (0x37c70).
    CriticalSection& lock = const_cast<CriticalSection&>(_lock);
    lock.Enter();
    int state = _state;
    if (state != 0x20000 && state != 0x10003)
    {
        lock.Leave();
        TLobbyError = LOBERR_INVALID_SESSION_STATE;
        return false;
    }
    fp->StartRepeat();
    for (std::vector<LobbyService*, StlAllocator<LobbyService*, 2> >::const_iterator i = _serviceEntries.begin();
         i != _serviceEntries.end(); ++i)
    {
        if (*i != nullptr)
        {
            if (!(*i)->Fetch(const_cast<CliSession*>(this), fp))
            {
                lock.Leave();
                TLobbyError = LOBERR_SYSTEM;
                return false;
            }
            fp->IncRepeatCount();
        }
    }
    fp->composer.PopRepeatCount();
    lock.Leave();
    return true;
}

#pragma comment(linker, "/INCLUDE:?UpdateBotScore@CliSession@@QEAA_N_KH@Z") // LIFT: keep until the caller is lifted (0x37de0).
// 0x37de0
bool CliSession::UpdateBotScore(unsigned long long pcid, int botScore)
{
    if (pcid != 0 && botScore >= 0)
    {
        _lock.Enter();
        _acb._dbfield.botScore = botScore;
        _lock.Leave();
        return true;
    }
    CliSession const* cs = this;
    unsigned int state = (cs != nullptr) ? static_cast<unsigned int>(cs->_state) : 0;
    Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2324,
               L"[cs], update bot-score fail; invalid parameter, pcid:0x%I64X, bot-score:%dcli-key:0x%I64X, "
               L"cli-state:%d.%d",
               pcid, botScore, (cs != nullptr) ? cs->_clikey : 0ULL, state >> 16, state & 0xFFFF);
    TLobbyError = LOBERR_INVALID_PARAMETER;
    return false;
}

#pragma comment(linker, "/INCLUDE:?BindCharacterSlot@CliSession@@QEAA_N_KAEBTid128@@@Z") // LIFT: keep until the caller is lifted (0x37eb0).
// 0x37eb0
bool CliSession::BindCharacterSlot(unsigned long long pcid, id128 const& slotid)
{
    // LIFT: Compare with ID128_ID_ZERO (0x14012d870). The loads are at 0x37ed2 and 0x37ede.
    if (pcid == 0 || (slotid.id[0] == ID128_ID_ZERO.id[0] && slotid.id[1] == ID128_ID_ZERO.id[1]))
    {
        CliSession const* cs = this;
        unsigned int state = (cs != nullptr) ? static_cast<unsigned int>(cs->_state) : 0;
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2341,
                   L"[cs], bind character slot fail; invalid parameter, pcid:0x%I64X, "
                   L"slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, cli-key:0x%I64X, cli-state:%d.%d",
                   pcid, slotid.guid.id1, slotid.guid.id2, slotid.guid.id3, slotid.guid.id4[0], slotid.guid.id4[1],
                   slotid.guid.id4[2], slotid.guid.id4[3], slotid.guid.id4[4], slotid.guid.id4[5], slotid.guid.id4[6],
                   slotid.guid.id4[7], (cs != nullptr) ? cs->_clikey : 0ULL, state >> 16, state & 0xFFFF);
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }
    _lock.Enter();
    Character* pc = nullptr;
    // LIFT: 0x37eb0 inlines the pcid search. The out-of-line getCharacter at 0x35cf0 is still a stub.
    for (std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator i = _characters.begin();
         i != _characters.end(); ++i)
    {
        if (*i != nullptr && (*i)->_db.pcid == pcid)
        {
            pc = *i;
            break;
        }
    }
    if (pc == nullptr)
    {
        TLobbyError = LOBERR_NO_SUCH_CHARACTER;
        _lock.Leave();
        return false;
    }
    // LIFT: Compare with ID128_ID_ZERO (0x14012d870). The loads are at 0x37f58 and 0x37f69.
    if (pc->_db.slotid.id[0] != ID128_ID_ZERO.id[0] || pc->_db.slotid.id[1] != ID128_ID_ZERO.id[1])
    {
        TLobbyError = LOBERR_NOT_FOUND;
        _lock.Leave();
        return false;
    }
    int dbrtn = 0;
    if (LobbyDB::BindCharacterSlot(dbrtn, pcid, slotid))
    {
        pc->SetSlotId(slotid);
        _lock.Leave();
        return true;
    }
    Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2366,
               L"[cs], bind character slot db fail; dbrtn:%d, pcid:0x%I64X, "
               L"slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
               dbrtn, pcid, slotid.guid.id1, slotid.guid.id2, slotid.guid.id3, slotid.guid.id4[0], slotid.guid.id4[1],
               slotid.guid.id4[2], slotid.guid.id4[3], slotid.guid.id4[4], slotid.guid.id4[5], slotid.guid.id4[6],
               slotid.guid.id4[7]);
    TLobbyError = LOBERR_DB_FAIL;
    _lock.Leave();
    return false;
}

// 0x381c0
#pragma comment(linker, "/INCLUDE:?UpdateCharacterData@CliSession@@QEAA_N_KFPEADF@Z") // LIFT: keep until the caller is lifted (0x381c0).
// 0x381c0
bool CliSession::UpdateCharacterData(unsigned long long pcid, short level, char* showcase, short showcaseSize)
{
    // LIFT: the original tests only showcaseSize != 0 (0x381c0). The range guard keeps a negative or oversized
    // length away from LobbyDB::UpdateCharacterData. It is the same bound as Character::SetShowcase (0x32510).
    if (pcid == 0 || level <= 0 || showcase == nullptr || static_cast<unsigned short>(showcaseSize - 1) > 0x1FF)
    {
        CliSession const* cs = this;
        unsigned int state = (cs != nullptr) ? static_cast<unsigned int>(cs->_state) : 0;
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2382,
                   L"[cs], update pc showcase fail; invalid parameter, pcid:0x%I64X, level:%d, showcase:%p, showcase-size:%d, cli-key:0x%I64X, cli-state:%d.%d",
                   pcid, level, showcase, showcaseSize, (cs != nullptr) ? cs->_clikey : 0ULL, state >> 16,
                   state & 0xFFFF);
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }
    bool result = false;
    _lock.Enter();
    Character* pc = getCharacter(pcid);
    if (pc != nullptr)
    {
        int dbrtn = 0;
        if (LobbyDB::UpdateCharacterData(dbrtn, pcid, pc->_db.job, level, showcase, showcaseSize))
        {
            pc->SetLevel(level);
            pc->SetShowcase(showcase, showcaseSize);
            result = true;
        }
        else
        {
            TLobbyError = dbrtn != 0 ? LOBERR_DB_FAIL : LOBERR_SYSTEM;
        }
    }
    else
    {
        TLobbyError = LOBERR_NO_SUCH_CHARACTER;
    }
    _lock.Leave();
    return result;
}

#pragma comment(linker, "/INCLUDE:?UpdateCharacterLevel@CliSession@@QEAA_N_KF@Z") // LIFT: keep until the caller is lifted (0x38380).
// 0x38380
bool CliSession::UpdateCharacterLevel(unsigned long long pcid, short level)
{
    if (pcid == 0 || level <= 0)
    {
        CliSession const* cs = this;
        unsigned int state = (cs != nullptr) ? static_cast<unsigned int>(cs->_state) : 0;
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2419,
                   L"[cs], update character level fail; invalid parameter, pcid:0x%I64X, level:%d, cli-key:0x%I64X, cli-state:%d.%d",
                   pcid, level, (cs != nullptr) ? cs->_clikey : 0ULL, state >> 16, state & 0xFFFF);
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }
    bool result = false;
    _lock.Enter();
    Character* pc = nullptr;
    // LIFT: 0x38380 inlines the pcid search. The out-of-line getCharacter at 0x35cf0 is still a stub.
    for (std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator i = _characters.begin();
         i != _characters.end(); ++i)
    {
        if (*i != nullptr && (*i)->_db.pcid == pcid)
        {
            pc = *i;
            break;
        }
    }
    if (pc != nullptr)
    {
        int dbrtn = 0;
        if (LobbyDB::UpdateCharacterLevel(dbrtn, pcid, level))
        {
            pc->SetLevel(level);
            result = true;
        }
        else
        {
            TLobbyError = dbrtn != 0 ? LOBERR_DB_FAIL : LOBERR_SYSTEM;
        }
    }
    else
    {
        TLobbyError = LOBERR_NO_SUCH_CHARACTER;
    }
    _lock.Leave();
    return result;
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
// LIFT: not lifted in card ld-13 (0x39820). The body uses LobbyDaemon::_instance->GlobalTimerQueue and _config.
// The LobbyDaemon layout belongs to cards ld-15 and ld-20.
bool CliSession::ReserveStopPlay(bool, int, int)
{
    LIFT_STUB(0x39820);
}

// 0x39a70
#pragma comment(linker, "/INCLUDE:?TimeoutStopPlay@CliSession@@QEAA_NPEAVStopPlayTimerEvent@@@Z")  // LIFT: keep until the caller is lifted (0x39a70).
bool CliSession::TimeoutStopPlay(StopPlayTimerEvent* event)
{
    if (event == nullptr)
    {
        CliSession const* cs = this;
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2943,
                   L"== CRASH == [cs], timeout stop play fail; invalid parameter, event:%p, cli-key:0x%I64X, cli-state:%d.%d",
                   event, (cs != nullptr) ? cs->_clikey : 0ULL,
                   (cs != nullptr) ? static_cast<unsigned int>(cs->_state) >> 16 : 0,
                   (cs != nullptr) ? cs->_state & 0xFFFF : 0);
        AlertSender::Write(L"CliSession.cpp", 2943,
                           L"== CRASH == [cs], timeout stop play fail; invalid parameter, event:%p, cli-key:0x%I64X, cli-state:%d.%d",
                           event, (cs != nullptr) ? cs->_clikey : 0ULL,
                           (cs != nullptr) ? static_cast<unsigned int>(cs->_state) >> 16 : 0,
                           (cs != nullptr) ? cs->_state & 0xFFFF : 0);
        return false;
    }
    bool result = false;
    _lock.Enter();
    if (_reservedStopPlay == event)
    {
        result = true;
        _reservedStopPlay = nullptr;
    }
    else if (_srvloc != nullptr)
    {
        result = _srvloc->TimeoutStopPlay(this, event);
    }
    else
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 2959,
                   L"[cs], timeout stop play fail; not in service location, reserved:%p, event:%p, cli-key:0x%I64X, cli-state:%d.%d",
                   _reservedStopPlay, event, _clikey, static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
    }
    _lock.Leave();
    return result;
}

// 0x39be0
#pragma comment(linker, "/INCLUDE:?OnChargeStopRequested@CliSession@@QEAA_NI@Z")  // LIFT: keep until the caller is lifted (0x39be0).
bool CliSession::OnChargeStopRequested(unsigned int txnid)
{
    bool result = false;
    _lock.Enter();
    if (_state == 0x40000)
    {
        if (_chargeKey != nullptr)
        {
            _chargeStopRequestTxnId = txnid;
            Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 2977,
                       L"[cs], response reserved for charge stop request, txn-id:%u, cli-key:0x%I64X, cli-state:%d.%d",
                       txnid, _clikey, static_cast<unsigned int>(_state) >> 16, _state & 0xFFFF);
            result = true;
        }
        else
        {
            TLobbyError = LOBERR_CHARGE_NOT_STARTED;
        }
    }
    else
    {
        TLobbyError = LOBERR_INVALID_SESSION_STATE;
    }
    _lock.Leave();
    return result;
}

// 0x39cc0
// LIFT: not lifted in card ld-13 (0x39cc0). The body uses LobbyDaemon::_instance->_gamedchmgr.
// The LobbyDaemon layout belongs to cards ld-15 and ld-20.
bool CliSession::ApplyNewChargeItem(wchar_t const*, long, unsigned int, short)
{
    LIFT_STUB(0x39cc0);
}

// 0x39e50
// LIFT: not lifted in card ld-13 (0x39e50). The body uses LobbyDaemon::_instance->_gamedchmgr.
// The LobbyDaemon layout belongs to cards ld-15 and ld-20.
bool CliSession::NotifyChargeRemainTime(long, short, unsigned int)
{
    LIFT_STUB(0x39e50);
}

// 0x39f70
#pragma comment(linker, "/INCLUDE:?setRole@CliSession@@QEAA_NQEBIH@Z")  // LIFT: keep until the caller is lifted (0x39f70).
bool CliSession::setRole(unsigned int const* const roles, int const roleCount)
{
    _acb._roles.Reset();
    for (long long i = 0; i < roleCount; ++i)
    {
        _acb._roles.Set(roles[i]);
        if (roles[i] < Role::ROLE_COUNT)
            _auth.Merge(GRoleAuthorityTable[roles[i]]);
    }
    return true;
}

// 0x3a000
#pragma comment(linker, "/INCLUDE:?setPcCafeCode@CliSession@@QEAA_NPEB_W@Z")  // LIFT: keep until the caller is lifted (0x3a000).
bool CliSession::setPcCafeCode(wchar_t const* pcCafeCode)
{
    if (_pcCafeCode != nullptr)
    {
        Memory::_Manager[2]->Free(_pcCafeCode, L"CliSession.cpp", 3132);
        _pcCafeCode = nullptr;
    }
    if (pcCafeCode != nullptr)
    {
        size_t const len = wcslen(pcCafeCode);
        _pcCafeCode = static_cast<wchar_t*>(
            Memory::_Manager[2]->AllocZero(sizeof(wchar_t) * (len + 1), L"CliSession.cpp", 3137));
        wcscpy_s(_pcCafeCode, len + 1, pcCafeCode);
    }
    Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 3141,
               L"[cs], set pc-cafe-code, pc-cafe-code:%s, cli-key:0x%I64X, cli-state:%d.%d",
               (pcCafeCode != nullptr) ? pcCafeCode : L"N/A", _clikey, static_cast<unsigned int>(_state) >> 16,
               _state & 0xFFFF);
    return true;
}

// 0x3a100
#pragma comment(linker, "/INCLUDE:?setPcCafe@CliSession@@QEAAXPEAVPcCafe@@@Z")  // LIFT: keep until the caller is lifted (0x3a100).
void CliSession::setPcCafe(PcCafe* pcCafe)
{
    if (_pcCafe != nullptr)
    {
        _pcCafe->onUnset(this);
        // LIFT: the class operator delete is empty (PcCafe.h). Free gives the memory back.
        delete _pcCafe;
        Memory::_Manager[2]->Free(_pcCafe, L"CliSession.cpp", 3161);
        _pcCafe = nullptr;
    }
    if (pcCafe != nullptr)
    {
        _pcCafe = pcCafe;
        pcCafe->onSet(this);
    }
}

// 0x3a190
// LIFT: not lifted in card ld-13 (0x3a190). The body uses LobbyDaemon::_instance->_mileageManager.
// The LobbyDaemon layout belongs to cards ld-15 and ld-20.
void CliSession::onPcCafeChargeStart()
{
    LIFT_STUB(0x3a190);
}

// 0x3a2c0
// LIFT: not lifted in card ld-13 (0x3a2c0). The body uses LobbyDaemon::_instance->_mileageManager.
// The LobbyDaemon layout belongs to cards ld-15 and ld-20.
void CliSession::onPcCafeChargeStop()
{
    LIFT_STUB(0x3a2c0);
}

// 0x3a3f0
// LIFT: not lifted in card ld-13 (0x3a3f0). The body calls _lgate->addReferenceCount(L"CliSession.cpp", 3212).
// LobbyGateChannel has no PDB base (RefCntObject) in LobbyGateChannel.h yet.
AnonymousLobbyGatePresence::AnonymousLobbyGatePresence(LobbyGateChannel*, unsigned long long)
{
    LIFT_STUB(0x3a3f0);
}

// 0x3a450 (scalar deleting destructor)
// LIFT: declared in ld-13 with the PDB layout of AnonymousLobbyGatePresence. Not in batch 1.
AnonymousLobbyGatePresence::~AnonymousLobbyGatePresence()
{
    LIFT_STUB(0x3a450);
}

// 0xe3ec0 (folded)
#pragma comment(linker, "/INCLUDE:?GetKind@AnonymousLobbyGatePresence@@UEBA?AW4Kind@Presence@@XZ")  // LIFT: keep until the caller is lifted (0xe3ec0).
Presence::Kind AnonymousLobbyGatePresence::GetKind() const
{
    return AnonymousLobbyGate;
}

// 0x3a4a0
#pragma comment(linker, "/INCLUDE:?IsEqual@AnonymousLobbyGatePresence@@UEBA_NPEBVPresence@@@Z")  // LIFT: keep until the caller is lifted (0x3a4a0).
bool AnonymousLobbyGatePresence::IsEqual(Presence const* presence) const
{
    if (presence == nullptr)
        return false;
    if (this == presence)
        return true;
    if (presence->GetKind() != GetKind())
        return false;
    AnonymousLobbyGatePresence const* other = static_cast<AnonymousLobbyGatePresence const*>(presence);
    return _lgate == other->_lgate && _gatekey == other->_gatekey;
}

// 0x3a530
// LIFT: not lifted in card ld-13 (0x3a530). The body reads _lgate->_rawChannel->GetId().
// LobbyGateChannel has no PDB base (with _rawChannel) in LobbyGateChannel.h yet.
bool AnonymousLobbyGatePresence::OnSet(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3a530);
}

// 0x3a600
// LIFT: not lifted in card ld-13 (0x3a600). Same reason as OnSet 0x3a530 (_lgate->_rawChannel->GetId()).
void AnonymousLobbyGatePresence::OnUnset(CliSessionTable*, CliSession*)
{
    LIFT_STUB(0x3a600);
}

// 0x3a650
#pragma comment(linker, "/INCLUDE:?Close@AnonymousLobbyGatePresence@@UEAAXPEAVCliSession@@@Z")  // LIFT: keep until the caller is lifted (0x3a650).
void AnonymousLobbyGatePresence::Close(CliSession*)
{
    if (_lgate != nullptr)
        _lgate->SendCloseAnonymousSessionNotify(_gatekey);
}

// 0x3a670
#pragma comment(linker, "/INCLUDE:?Kick@AnonymousLobbyGatePresence@@UEAAXPEAVCliSession@@H@Z")  // LIFT: keep until the caller is lifted (0x3a670).
void AnonymousLobbyGatePresence::Kick(CliSession* owner, int)
{
    Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3261,
               L"== CRASH == [cs], kick anonymous lobby-gate presence is forbidden, cli-key:0x%I64X, cli-state:%d.%d",
               (owner != nullptr) ? owner->_clikey : 0ULL,
               (owner != nullptr) ? static_cast<unsigned int>(owner->_state) >> 16 : 0,
               (owner != nullptr) ? owner->_state & 0xFFFF : 0);
    AlertSender::Write(L"CliSession.cpp", 3261,
                       L"== CRASH == [cs], kick anonymous lobby-gate presence is forbidden, cli-key:0x%I64X, cli-state:%d.%d",
                       (owner != nullptr) ? owner->_clikey : 0ULL,
                       (owner != nullptr) ? static_cast<unsigned int>(owner->_state) >> 16 : 0,
                       (owner != nullptr) ? owner->_state & 0xFFFF : 0);
}

// 0x3a710 (scalar deleting destructor)
// LIFT: declared in ld-13 with the PDB layout of LobbyGatePresence. Not in batch 2.
LobbyGatePresence::~LobbyGatePresence()
{
    LIFT_STUB(0x3a710);
}

// 0x99980
#pragma comment(linker, "/INCLUDE:?GetKind@LobbyGatePresence@@UEBA?AW4Kind@Presence@@XZ")  // LIFT: keep until the caller is lifted (0x99980).
Presence::Kind LobbyGatePresence::GetKind() const
{
    return LobbyGate;
}

// 0x3a760
#pragma comment(linker, "/INCLUDE:?IsEqual@LobbyGatePresence@@UEBA_NPEBVPresence@@@Z")  // LIFT: keep until the caller is lifted (0x3a760).
bool LobbyGatePresence::IsEqual(Presence const* presence) const
{
    if (presence == nullptr)
        return false;
    if (this == presence)
        return true;
    if (presence->GetKind() != GetKind())
        return false;
    return _gatewid == static_cast<LobbyGatePresence const*>(presence)->_gatewid;
}

// LIFT: inlined GateNode ctor (in LobbyGatePresence::OnSet 0x3a7d0). The addReferenceCount line is 19
// (CliSessionTable.cpp). The body is here because CliSession is incomplete in CliSessionTable.h.
inline GateNode::GateNode(CliSession* clisession)
    : _clisession(clisession)
{
    _clisession->addReferenceCount(L"CliSessionTable.cpp", 19);
}

// 0x3a7d0
#pragma comment(linker, "/INCLUDE:?OnSet@LobbyGatePresence@@UEAA_NPEAVCliSessionTable@@PEAVCliSession@@@Z")  // LIFT: keep until the caller is lifted (0x3a7d0).
bool LobbyGatePresence::OnSet(CliSessionTable* table, CliSession* owner)
{
    if (table == nullptr || owner == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3309,
                   L"== CRASH == [cs], on set lobby-gate presence fail; invalid parameter, table:%p, owner:%p",
                   table, owner);
        AlertSender::Write(L"CliSession.cpp", 3309,
                           L"== CRASH == [cs], on set lobby-gate presence fail; invalid parameter, table:%p, owner:%p",
                           table, owner);
        return false;
    }
    if (_node != nullptr)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3314,
                   L"== CRASH == [cs], on set lobby-gate presence fail; already set into gate-index table, cli-key:0x%I64X, cli-state:%d.%d",
                   owner->_clikey, static_cast<unsigned int>(owner->_state) >> 16, owner->_state & 0xFFFF);
        AlertSender::Write(L"CliSession.cpp", 3314,
                           L"== CRASH == [cs], on set lobby-gate presence fail; already set into gate-index table, cli-key:0x%I64X, cli-state:%d.%d",
                           owner->_clikey, static_cast<unsigned int>(owner->_state) >> 16, owner->_state & 0xFFFF);
        return false;
    }
    if (_gatewid == 0)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3319,
                   L"== CRASH == [cs], on set lobby-gate presence fail; invalid lobby-gate wid, cli-key:0x%I64X, cli-state:%d.%d",
                   owner->_clikey, static_cast<unsigned int>(owner->_state) >> 16, owner->_state & 0xFFFF);
        AlertSender::Write(L"CliSession.cpp", 3319,
                           L"== CRASH == [cs], on set lobby-gate presence fail; invalid lobby-gate wid, cli-key:0x%I64X, cli-state:%d.%d",
                           owner->_clikey, static_cast<unsigned int>(owner->_state) >> 16, owner->_state & 0xFFFF);
        return false;
    }
    _node = new (Memory::_Manager[2]->Alloc(sizeof(GateNode), L"CliSession.cpp", 3323)) GateNode(owner);
    if (table->Insert_index_gate(_gatewid, _node))
        return true;
    Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3325,
               L"[cs], on set lobby-gate presence fail; insert index on gate fail, cli-key:0x%I64X, cli-state:%d.%d",
               owner->_clikey, static_cast<unsigned int>(owner->_state) >> 16, owner->_state & 0xFFFF);
    _node->removeReferenceCount(L"CliSession.cpp", 3326);
    _node = nullptr;
    return false;
}

// 0x3aa30
#pragma comment(linker, "/INCLUDE:?OnUnset@LobbyGatePresence@@UEAAXPEAVCliSessionTable@@PEAVCliSession@@@Z")  // LIFT: keep until the caller is lifted (0x3aa30).
void LobbyGatePresence::OnUnset(CliSessionTable* table, CliSession* owner)
{
    if (_node == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3337,
                   L"== CRASH == [cs], on unset lobby-gate presence fail; not ever set into gate-index table, cli-key:0x%I64X, cli-state:%d.%d",
                   (owner != nullptr) ? owner->_clikey : 0ULL,
                   (owner != nullptr) ? static_cast<unsigned int>(owner->_state) >> 16 : 0,
                   (owner != nullptr) ? owner->_state & 0xFFFF : 0);
        AlertSender::Write(L"CliSession.cpp", 3337,
                           L"== CRASH == [cs], on unset lobby-gate presence fail; not ever set into gate-index table, cli-key:0x%I64X, cli-state:%d.%d",
                           (owner != nullptr) ? owner->_clikey : 0ULL,
                           (owner != nullptr) ? static_cast<unsigned int>(owner->_state) >> 16 : 0,
                           (owner != nullptr) ? owner->_state & 0xFFFF : 0);
        return;
    }
    if (_gatewid == 0)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3342,
                   L"== CRASH == [cs], on unset lobby-gate presence fail; invalid lobby-gate wid, cli-key:0x%I64X, cli-state:%d.%d",
                   (owner != nullptr) ? owner->_clikey : 0ULL,
                   (owner != nullptr) ? static_cast<unsigned int>(owner->_state) >> 16 : 0,
                   (owner != nullptr) ? owner->_state & 0xFFFF : 0);
        AlertSender::Write(L"CliSession.cpp", 3342,
                           L"== CRASH == [cs], on unset lobby-gate presence fail; invalid lobby-gate wid, cli-key:0x%I64X, cli-state:%d.%d",
                           (owner != nullptr) ? owner->_clikey : 0ULL,
                           (owner != nullptr) ? static_cast<unsigned int>(owner->_state) >> 16 : 0,
                           (owner != nullptr) ? owner->_state & 0xFFFF : 0);
        return;
    }
    if (table == nullptr || owner == nullptr)
        return;
    table->Delete_index_gate(_gatewid, _node);
    _node->removeReferenceCount(L"CliSession.cpp", 3348);
    _node = nullptr;
}

// 0x3abc0
// LIFT: not lifted in card ld-13 (0x3abc0). The body uses LobbyDaemon::_instance->_lgatechmgr and
// removeReferenceCount on LobbyGateChannel. LobbyDaemon.h and LobbyGateChannel.h have no PDB layout yet.
void LobbyGatePresence::Close(CliSession*)
{
    LIFT_STUB(0x3abc0);
}

// 0x3ac20
// LIFT: not lifted in card ld-13 (0x3ac20). Same reason as Close 0x3abc0.
void LobbyGatePresence::Kick(CliSession*, int)
{
    LIFT_STUB(0x3ac20);
}

// 0x3aca0
// LIFT: not lifted in card ld-13 (0x3aca0). Same reason as Close 0x3abc0.
void LobbyGatePresence::NotifyChangedGrade(CliSession*, StsMsgLib::_StsMsgNotifyGradeNotifyGradeChanged const&)
{
    LIFT_STUB(0x3aca0);
}

// 0x3ad60
// LIFT: not lifted in card ld-13 (0x3ad60). Same reason as Close 0x3abc0.
void LobbyGatePresence::NotifyChangedGradeLevel(CliSession*, StsMsgLib::_StsMsgNotifyGradeNotifyScoreChanged const&)
{
    LIFT_STUB(0x3ad60);
}

// 0x329e0 (scalar deleting destructor)
// LIFT: declared in ld-13 with the PDB layout of GameWorldPresence. Not in batch 2.
GameWorldPresence::~GameWorldPresence()
{
    LIFT_STUB(0x329e0);
}

// 0xe51f0 (folded)
#pragma comment(linker, "/INCLUDE:?GetKind@GameWorldPresence@@UEBA?AW4Kind@Presence@@XZ")  // LIFT: keep until the caller is lifted (0xe51f0).
Presence::Kind GameWorldPresence::GetKind() const
{
    return GameWorld;
}

// 0x3adf0
#pragma comment(linker, "/INCLUDE:?IsEqual@GameWorldPresence@@UEBA_NPEBVPresence@@@Z")  // LIFT: keep until the caller is lifted (0x3adf0).
bool GameWorldPresence::IsEqual(Presence const* presence) const
{
    if (presence == nullptr)
        return false;
    if (this == presence)
        return true;
    if (presence->GetKind() != GetKind())
        return false;
    GameWorldPresence const* other = static_cast<GameWorldPresence const*>(presence);
    return _wid == other->_wid && _pcid != 0 && other->_pcid != 0 && _gamekey == other->_gamekey;
}

// 0x3ae90
#pragma comment(linker, "/INCLUDE:?OnSet@GameWorldPresence@@UEAA_NPEAVCliSessionTable@@PEAVCliSession@@@Z")  // LIFT: keep until the caller is lifted (0x3ae90).
bool GameWorldPresence::OnSet(CliSessionTable* table, CliSession* owner)
{
    if (table == nullptr || owner == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3431,
                   L"== CRASH == [cs], on set game-world presence fail; invalid paramter, table:%p, owner:%p",
                   table, owner);
        AlertSender::Write(L"CliSession.cpp", 3431,
                           L"== CRASH == [cs], on set game-world presence fail; invalid paramter, table:%p, owner:%p",
                           table, owner);
        return false;
    }
    if (_wid == 0)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3436,
                   L"== CRASH == [cs], on set game-world presence fail; invalid game-world wid, cli-key:0x%I64X, cli-state:%d.%d",
                   owner->_clikey, static_cast<unsigned int>(owner->_state) >> 16, owner->_state & 0xFFFF);
        AlertSender::Write(L"CliSession.cpp", 3436,
                           L"== CRASH == [cs], on set game-world presence fail; invalid game-world wid, cli-key:0x%I64X, cli-state:%d.%d",
                           owner->_clikey, static_cast<unsigned int>(owner->_state) >> 16, owner->_state & 0xFFFF);
        return false;
    }
    if (!table->Insert_index_pcid(_wid, _pcid, owner))
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3442,
                   L"[cs], on set game-world presence exception; insert pc-id index fail, cli-key:0x%I64X, cli-state:%d.%d",
                   owner->_clikey, static_cast<unsigned int>(owner->_state) >> 16, owner->_state & 0xFFFF);
        return false;
    }
    return true;
}

// 0x3aff0
#pragma comment(linker, "/INCLUDE:?OnUnset@GameWorldPresence@@UEAAXPEAVCliSessionTable@@PEAVCliSession@@@Z")  // LIFT: keep until the caller is lifted (0x3aff0).
void GameWorldPresence::OnUnset(CliSessionTable* table, CliSession* owner)
{
    if (_wid == 0)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3456,
                   L"== CRASH == [cs], on unset game-world presence fail; invalid game-world wid, cli-key:0x%I64X, cli-state:%d.%d",
                   (owner != nullptr) ? owner->_clikey : 0ULL,
                   (owner != nullptr) ? static_cast<unsigned int>(owner->_state) >> 16 : 0,
                   (owner != nullptr) ? owner->_state & 0xFFFF : 0);
        AlertSender::Write(L"CliSession.cpp", 3456,
                           L"== CRASH == [cs], on unset game-world presence fail; invalid game-world wid, cli-key:0x%I64X, cli-state:%d.%d",
                           (owner != nullptr) ? owner->_clikey : 0ULL,
                           (owner != nullptr) ? static_cast<unsigned int>(owner->_state) >> 16 : 0,
                           (owner != nullptr) ? owner->_state & 0xFFFF : 0);
        return;
    }
    if (table != nullptr && owner != nullptr)
        table->Delete_index_pcid(_wid, _pcid);
}

// 0x3b0c0
// LIFT: not lifted in card ld-13 (0x3b0c0). The body uses LobbyDaemon::_instance->_gamedchmgr.
// LobbyDaemon.h has no PDB layout yet.
void GameWorldPresence::Close(CliSession*)
{
    LIFT_STUB(0x3b0c0);
}

// 0x3b120
#pragma comment(linker, "/INCLUDE:?Kick@GameWorldPresence@@UEAAXPEAVCliSession@@H@Z")  // LIFT: keep until the caller is lifted (0x3b120).
void GameWorldPresence::Kick(CliSession* owner, int)
{
    Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3482,
               L"== CRASH == [cs], kick world presence is forbidden, cli-key:0x%I64X, cli-state:%d.%d",
               (owner != nullptr) ? owner->_clikey : 0ULL,
               (owner != nullptr) ? static_cast<unsigned int>(owner->_state) >> 16 : 0,
               (owner != nullptr) ? owner->_state & 0xFFFF : 0);
    AlertSender::Write(L"CliSession.cpp", 3482,
                       L"== CRASH == [cs], kick world presence is forbidden, cli-key:0x%I64X, cli-state:%d.%d",
                       (owner != nullptr) ? owner->_clikey : 0ULL,
                       (owner != nullptr) ? static_cast<unsigned int>(owner->_state) >> 16 : 0,
                       (owner != nullptr) ? owner->_state & 0xFFFF : 0);
}

// 0x3b1c0
// LIFT: not lifted in card ld-13 (0x3b1c0). Same reason as Close 0x3b0c0.
void GameWorldPresence::NotifyChangedGrade(CliSession*, StsMsgLib::_StsMsgNotifyGradeNotifyGradeChanged const&)
{
    LIFT_STUB(0x3b1c0);
}

// 0x3b290
// LIFT: not lifted in card ld-13 (0x3b290). Same reason as Close 0x3b0c0.
void GameWorldPresence::NotifyChangedGradeLevel(CliSession*, StsMsgLib::_StsMsgNotifyGradeNotifyScoreChanged const&)
{
    LIFT_STUB(0x3b290);
}

// 0x3b360
// LIFT: not lifted in card ld-13 (0x3b360). The body uses LobbyDaemon::_instance->GlobalTimerQueue.
// LobbyDaemon.h has no PDB layout yet.
GameServiceLocation::~GameServiceLocation()
{
    LIFT_STUB(0x3b360);
}

// 0x5a0a0 (folded)
#pragma comment(linker, "/INCLUDE:?GetKind@GameServiceLocation@@UEBA?AW4Kind@ServiceLocation@@XZ")  // LIFT: keep until the caller is lifted (0x5a0a0).
ServiceLocation::Kind GameServiceLocation::GetKind() const
{
    return KIND_GAMEWORLD;
}

// 0x3b3d0
// LIFT: not lifted in card ld-13 (0x3b3d0). The body uses LobbyDaemon::_instance->_gameWorldRegistry and _mileageManager.
// LobbyDaemon.h has no PDB layout yet.
void GameServiceLocation::OnEnter(CliSession*)
{
    LIFT_STUB(0x3b3d0);
}

// 0x3b540
// LIFT: not lifted in card ld-13 (0x3b540). The body uses LobbyDaemon::_instance->_gameWorldRegistry, GlobalTimerQueue and _mileageManager.
// LobbyDaemon.h has no PDB layout yet.
void GameServiceLocation::OnLeave(CliSession*)
{
    LIFT_STUB(0x3b540);
}

// 0x3b6f0
// LIFT: not lifted in card ld-13 (0x3b6f0). The body uses LobbyDaemon::_instance->_gameWorldRegistry.
// LobbyDaemon.h has no PDB layout yet.
bool GameServiceLocation::Enter(CliSession*)
{
    LIFT_STUB(0x3b6f0);
}

// 0x3b9a0
// LIFT: not lifted in card ld-13 (0x3b9a0). The body uses LobbyDaemon::_instance->_gameWorldRegistry.
// LobbyDaemon.h has no PDB layout yet.
bool GameServiceLocation::Leave(CliSession*)
{
    LIFT_STUB(0x3b9a0);
}

// 0x3bb60
#pragma comment(linker, "/INCLUDE:?ReserveStopPlay@GameServiceLocation@@UEAA_NPEAVCliSession@@PEAVStopPlayTimerEvent@@@Z")  // LIFT: keep until the caller is lifted (0x3bb60).
bool GameServiceLocation::ReserveStopPlay(CliSession* owner, StopPlayTimerEvent* event)
{
    if (owner == nullptr || event == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3658,
                   L"== CRASH == [wr], reserve stop play fail; invalid parameter, owner:%p, event:%p", owner, event);
        AlertSender::Write(L"CliSession.cpp", 3658,
                           L"== CRASH == [wr], reserve stop play fail; invalid parameter, owner:%p, event:%p", owner, event);
        return false;
    }
    if (_reservedStopPlay != nullptr)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3663,
                   L"[wr], reserve stop play fail; already reserved, wid:%d, cli-key:0x%I64X, cli-state:%d.%d",
                   _wid, owner->_clikey, static_cast<unsigned int>(owner->_state) >> 16, owner->_state & 0xFFFF);
        return false;
    }
    _reservedStopPlay = event;
    Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 3669,
               L"[wr], reserve stop play ok, event:%p, wid:%d, cli-key:0x%I64X, cli-state:%d.%d",
               event, _wid, owner->_clikey, static_cast<unsigned int>(owner->_state) >> 16, owner->_state & 0xFFFF);
    return true;
}

// 0x3bc80
#pragma comment(linker, "/INCLUDE:?TimeoutStopPlay@GameServiceLocation@@UEAA_NPEAVCliSession@@PEAVStopPlayTimerEvent@@@Z")  // LIFT: keep until the caller is lifted (0x3bc80).
bool GameServiceLocation::TimeoutStopPlay(CliSession* owner, StopPlayTimerEvent* event)
{
    if (owner == nullptr || event == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3677,
                   L"== CRASH == [wr], timeout stop play fail; invalid parameter, owner:%p, event:%p", owner, event);
        AlertSender::Write(L"CliSession.cpp", 3677,
                           L"== CRASH == [wr], timeout stop play fail; invalid parameter, owner:%p, event:%p", owner, event);
        return false;
    }
    if (_reservedStopPlay != event)
    {
        Log::Write(Log::LT_ERROR, L"CliSession.cpp", 3683,
                   L"[wr], timeout stop play fail; event mismatch, reserved-event:%p, event:%p, cli-key:0x%I64X, cli-state:%d.%d",
                   _reservedStopPlay, event, owner->_clikey, static_cast<unsigned int>(owner->_state) >> 16,
                   owner->_state & 0xFFFF);
        return false;
    }
    _reservedStopPlay = nullptr;
    Log::Write(Log::LT_DEBUG, L"CliSession.cpp", 3687,
               L"[wr], timeout stop play ok, event:%p, cli-key:0x%I64X, cli-state:%d.%d",
               event, owner->_clikey, static_cast<unsigned int>(owner->_state) >> 16, owner->_state & 0xFFFF);
    return true;
}

// 0x3bda0
// LIFT: not lifted in card ld-13 (0x3bda0). The body uses LobbyDaemon::_instance->_gamedchmgr.
// LobbyDaemon.h has no PDB layout yet.
void GameServiceLocation::NotifyStopPlay(CliSession*, int)
{
    LIFT_STUB(0x3bda0);
}
