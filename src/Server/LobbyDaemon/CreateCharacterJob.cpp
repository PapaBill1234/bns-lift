// CreateCharacterJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <string.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "CreateCharacterJob.h"
#include "AlertSender.h"
#include "Character.h"
#include "CliSession.h"
#include "Daemon.h"
#include "GameWorld.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyConfig.h"
#include "LobbyDB.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "LobbyJobParams.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"
#include "RuleSet.h"
#include "TencentUIC.h"
#include "TransactionChannel.h"

// LIFT: PDB public LobbyErrorDesc (.data 0003:2032). LobbyGamePacketHandler.cpp has the definition (placeholder).
extern wchar_t const* LobbyErrorDesc[28];

static wchar_t const kFile[] = L"CreateCharacterJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// The "== CRASH ==" form: the log and then the alert with the same text. Each call reads its arguments again.
#define JOB_CRASH(line, msg, fmt, ...)                                                                               \
    do                                                                                                               \
    {                                                                                                                \
        JOB_LOG(Log::LT_ERROR, line, msg, fmt, ##__VA_ARGS__);                                                       \
        AlertSender::Write(kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt, \
                           this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                 \
                           this != nullptr ? _state : -1,                                                            \
                           this != nullptr && _owner != nullptr ? _owner->_clikey : 0,                              \
                           HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                       \
                           LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__);       \
    } while (0)

#define SLOTID_FMT L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"
#define SLOTID_ARGS(s)                                                                                               \
    (s).guid.id1, (s).guid.id2, (s).guid.id3, (s).guid.id4[0], (s).guid.id4[1], (s).guid.id4[2], (s).guid.id4[3],    \
        (s).guid.id4[4], (s).guid.id4[5], (s).guid.id4[6], (s).guid.id4[7]
#define GUID_ARGS(g)                                                                                                 \
    (g).Data1, (g).Data2, (g).Data3, (g).Data4[0], (g).Data4[1], (g).Data4[2], (g).Data4[3], (g).Data4[4],           \
        (g).Data4[5], (g).Data4[6], (g).Data4[7]

// The request suffix of the init logs.
#define REQ_FMT L", slot-id:" SLOTID_FMT L", wid:%d, name:%s, make-data-size:%d, jumping-character:%d"
#define REQ_ARGS(r)                                                                                                  \
    SLOTID_ARGS((r)->slotid), (r)->wid, (r)->characterName, (r)->characterMakeDataSize, (r)->jumpingCharacter

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000, CSS_FIN = 0x60000.

namespace StsMsgLib
{
// PDB StsMsgLib::_StsMsgResponseSlotGetSlot (sizeof 0xa0).
struct _StsMsgResponseSlotGetSlot : public _StsMsgResponse
{
    struct _SlotData
    {
        long long serviceId;
    };

    GUID guidSlotId;
    wchar_t* pwszSlotType;
    bool bSystemSlot;
    _SlotData slotData;
    wchar_t* pwszSlotData;
    long long tChanged;
    long long tRegistered;
};
static_assert(sizeof(_StsMsgResponseSlotGetSlot) == 0xA0, "sizeof StsMsgLib::_StsMsgResponseSlotGetSlot");
static_assert(offsetof(_StsMsgResponseSlotGetSlot, guidSlotId) == 0x60, "_StsMsgResponseSlotGetSlot::guidSlotId");
static_assert(offsetof(_StsMsgResponseSlotGetSlot, pwszSlotType) == 0x70, "_StsMsgResponseSlotGetSlot::pwszSlotType");
static_assert(offsetof(_StsMsgResponseSlotGetSlot, bSystemSlot) == 0x78, "_StsMsgResponseSlotGetSlot::bSystemSlot");
static_assert(offsetof(_StsMsgResponseSlotGetSlot, slotData) == 0x80, "_StsMsgResponseSlotGetSlot::slotData");
}  // namespace StsMsgLib

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"GET_SLOT"}, {2, L"CREATE_CHARACTER"}, {3, L"FIN"}};  // 0x12e0a0

// LIFT: the PDB Character() is inline. The original writes the same fields after Alloc (0x43b90).
Character* ConstructCharacter(void* mem)
{
    if (mem == nullptr)
        return nullptr;
    Character* const pc = static_cast<Character*>(mem);
    pc->_right = 0;
    memset(&pc->_db, 0, sizeof(pc->_db));
    pc->_slotattr.dummy = 0;
    memset(&pc->_status, 0, sizeof(pc->_status));
    return pc;
}

// LIFT: Character::~Character (scalar deleting destructor 0x33c80) is not declared in Character.h. This is its body:
// it frees the showcase buffer. ❓ Move it to Character when Character.h gets the destructor.
void DestroyCharacter(Character* pc)
{
    if (pc == nullptr)
        return;
    if (pc->_db.showcase != nullptr)
    {
        Memory::_Manager[2]->Free(pc->_db.showcase, L"Character.cpp", 51);
        pc->_db.showcase = nullptr;
    }
}

// LIFT: the original inlines CliSession::getCharacter (0x35cf0) here.
Character* FindCharacter(CliSession* owner, unsigned long long pcid)
{
    if (pcid == 0)
        return nullptr;
    for (std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator i = owner->_characters.begin();
         i != owner->_characters.end(); ++i)
    {
        if (*i != nullptr && (*i)->_db.pcid == pcid)
            return *i;
    }
    return nullptr;
}

// The quota rollback of the fail paths. The original repeats it inline.
void RollbackReservedQuota(CliSession* owner, bool jumpingCharacter)
{
    if (jumpingCharacter)
    {
        LobbyConfig const* const config = LobbyDaemon::_instance->_config;
        if (config->_useJumpingCharacterCreationQuota && !config->_useJumpingCharacterCreationQuotaInWorld)
            --owner->_jumpingCharacterCreationQuota._reservedCreationCount;
    }
}
}  // namespace

LobbyJobDef CreateCharacterJob::_def = {5, StateDef, 3, L"CreateCharacterJob"};  // 0x201d50

#include "ObjectPoolLobbyDaemon.h"

// .data 0x204360, dynamic init 0x11dda0, atexit dtor 0x11ec00.
// The exe .data holds id 1, objsize 0xb0, desc L"CreateCharacterJob".
ObjPool CreateCharacterJob::_pool(1, 0xb0, L"CreateCharacterJob");

// LIFT: no RVA. LTCG inlined it into LobbyDaemon::initialize (0x9b300). The original constructs a job on the stack
// and returns its vfptr. It does not run the destructor.
void* CreateCharacterJob::_vtbl()
{
    char buf[sizeof(CreateCharacterJob)];
    CreateCharacterJob* job = ::new (buf) CreateCharacterJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x41840
LobbyJobDef const* CreateCharacterJob::GetDefinition() const
{
    return &_def;
}

// 0x41850
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void CreateCharacterJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x41850);
}

// 0x418a0
CreateCharacterJob::CreateCharacterJob(CliSession* owner)
    : CliSessionJob(owner), _lgate(nullptr), _gamed(nullptr), _pcid(0), _wid(0), _characterName(nullptr),
      _characterNameLen(0), _characterMakeData(nullptr), _characterMakeDataSize(0), _jumpingCharacter(false),
      _tran(nullptr)
{
    _slotid.id[0] = 0;
    _slotid.id[1] = 0;
}

// 0x41940 (scalar deleting destructor)
CreateCharacterJob::~CreateCharacterJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 87);
    if (_gamed != nullptr)
        _gamed->removeReferenceCount(kFile, 89);
    if (_characterName != nullptr)
    {
        Memory::_Manager[2]->Free(_characterName, kFile, 91);
        _characterName = nullptr;
    }
    if (_characterMakeData != nullptr)
    {
        Memory::_Manager[2]->Free(_characterMakeData, kFile, 93);
        _characterMakeData = nullptr;
    }
    if (_tran != nullptr)
    {
        _tran->removeReferenceCount(kFile, 95);
        _tran = nullptr;
    }
}

// 0x41a30
bool CreateCharacterJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT)
    {
        result = init(task, param);
        task = 0;
    }
    if (_state == GET_SLOT)
    {
        if (task == 0)
        {
            result = reqGetSlot();
        }
        else if (task == 37)
        {
            result = responseGetSlot(param);
            task = 0;
        }
        else if (task == 38)
        {
            result = expireGetSlot();
            task = 0;
        }
    }
    if (_state == CREATE_CHARACTER)
    {
        if (task == 0)
            return tryCreateCharacter();
        else if (task == 105)
            return createCharacterOk(param);
        else if (task == 106)
            return createCharacterFail(*static_cast<short*>(param));
        else if (task == 107)
            return createCharacterExpire();
    }
    return result;
}

// 0x41b10
bool CreateCharacterJob::init(int task, void* param)
{
    if (_owner->_state != 0x20000)  // CSS_LOBBY
    {
        JOB_LOG(Log::LT_ERROR, 147, L"[job], cli-session not in lobby", L"");
        transit(FIN);
        return true;
    }
    if (task != 10 || param == nullptr)
    {
        JOB_CRASH(153, L"== CRASH == [job], invalid task parameter", L", task:%d, param:%p", task, param);
        transit(FIN);
        return true;
    }

    CreateCharacterReqParam* const req = static_cast<CreateCharacterReqParam*>(param);
    GamedChannel* gamed = nullptr;
    int dbrtn = 0;
    short reason = 0;
    LobbyConfig const* config = nullptr;
    GameWorld* gw = nullptr;
    RuleSet::CheckNameResult checkName = RuleSet::CHECKNAME_OK;

    // LIFT: safety check (not in the original). The handler (0xc5b10) caps the size at 256 and ends the name with
    // NUL. This check keeps the memcpy below and wcslen inside the param buffers.
    if (req->characterMakeDataSize < 0 || req->characterMakeDataSize > static_cast<short>(sizeof(req->characterMakeData)) ||
        wmemchr(req->characterName, L'\0', sizeof(req->characterName) / sizeof(req->characterName[0])) == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 172, L"[job], invalid parameter", L"");
        reason = 6;
        goto initfail;
    }

    if (req->lgate == nullptr || (req->slotid.id[0] == ID128_ID_ZERO.id[0] && req->slotid.id[1] == ID128_ID_ZERO.id[1]) || req->wid == 0 ||
        wcslen(req->characterName) == 0 || req->characterMakeDataSize == 0)
    {
        JOB_LOG(Log::LT_ERROR, 172, L"[job], invalid parameter", REQ_FMT, REQ_ARGS(req));
        reason = 6;
        goto initfail;
    }

    config = LobbyDaemon::_instance->_config;
    if (!config->_enableJumpingCharacterCreation && req->jumpingCharacter == true)
    {
        JOB_LOG(Log::LT_ERROR, 182, L"[job], jumping character creation is disabled", REQ_FMT, REQ_ARGS(req));
        reason = 2;
        goto initfail;
    }
    if (req->jumpingCharacter)
    {
        int const banId = config->_contentBanIdForJumpingCharacter;
        if (banId != 0 && config->_enableContentBan)
        {
            // The original stops at the first ban with this id.
            for (std::vector<ContentBan, StlAllocator<ContentBan, 2> >::const_iterator i = _owner->_bans.begin();
                 i != _owner->_bans.end(); ++i)
            {
                if (i->id != banId)
                    continue;
                if (i->from <= Daemon::Now && Daemon::Now <= i->to)
                {
                    JOB_LOG(Log::LT_ERROR, 198, L"[job], restricted by content ban", REQ_FMT, REQ_ARGS(req));
                    reason = 132;
                    goto initfail;
                }
                break;
            }
        }
        if (config->_useJumpingCharacterCreationQuota && !config->_useJumpingCharacterCreationQuotaInWorld)
        {
            JumpingCharacterCreationQuota const& quota = _owner->_jumpingCharacterCreationQuota;
            if (quota._reservedCreationCount + quota._db.creationCount >= quota._db.creationQuota)
            {
                JOB_LOG(Log::LT_ERROR, 213, L"[job], restricted by quota",
                        REQ_FMT L", creationQuota:%d, creationCount:%d, reservedCreationCount:%d", REQ_ARGS(req),
                        quota._db.creationQuota, quota._db.creationCount, quota._reservedCreationCount);
                reason = 133;
                goto initfail;
            }
        }
    }

    gw = LobbyDaemon::_instance->_gameWorldRegistry->Get(req->wid);
    if (gw == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 225, L"[job], unkown game-world", REQ_FMT, REQ_ARGS(req));
        reason = 128;
        goto initfail;
    }
    if (!gw->PermitCharacterManagement(_owner, true))
    {
        int const error = TLobbyError;
        JOB_LOG(Log::LT_ERROR, 233, L"[job], world denied", L", error:%s" REQ_FMT,
                static_cast<unsigned int>(error) >= 28 ? L"LOBERR_UNDEFINED" : LobbyErrorDesc[error], REQ_ARGS(req));
        if (error == 9)
            reason = 128;
        else if (error == 13)
            reason = 130;
        else if (error == 14)
            reason = 131;
        else
            reason = 2;
        goto initfail;
    }

    gamed = LobbyDaemon::_instance->_gamedchmgr->Acquire(req->wid);
    if (gamed == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 255, L"[job], game-world not available", REQ_FMT, REQ_ARGS(req));
        reason = 129;
        goto initfail;
    }

    if (LobbyDaemon::_instance->_config->_tencentUICEnable)
    {
        if (_owner->_externalAccountKeySize <= 0)
        {
            reason = 130;
            goto initfail;
        }
        unsigned int const qqid = *reinterpret_cast<unsigned int const*>(_owner->_externalAccountKey);
        if (!LobbyDaemon::_instance->_tencentUIC->CheckNameFilter(qqid, req->characterName))
        {
            reason = 123;
            goto initfail;
        }
    }

    config = LobbyDaemon::_instance->_config;
    checkName = RuleSet::CheckName(LobbyDaemon::_instance->_localeset, req->characterName,
                                   config->_allowedCharacterNameLenMin, config->_allowedCharacterNameLenMax,
                                   config->_allowedCharacterNameSpaceAmount, config->_enableNumericForCharacterName,
                                   config->_forceSentenceCaseForCharacterName,
                                   config->_enableMultilingualCharacterName,
                                   config->_forbiddenCharactersForCharacterName);
    if (checkName != RuleSet::CHECKNAME_OK)
    {
        JOB_LOG(Log::LT_ERROR, 290, L"[job], check name fail", L", error:%d" REQ_FMT, checkName, REQ_ARGS(req));
        if (checkName == RuleSet::CHECKNAME_INVALID_PARAMTER)
            reason = 6;
        else if (checkName > RuleSet::CHECKNAME_INVALID_PARAMTER && checkName <= RuleSet::CHECKNAME_MULTILINGUAL)
            reason = 122;
        else if (checkName == RuleSet::CHECKNAME_FORBIDDEN)
            reason = 123;
        else
            reason = 2;
        goto initfail;
    }
    if (!LobbyDB::CheckValidityOfCharacterName(dbrtn, req->characterName,
                                               config->_forceSentenceCaseForCharacterName))
    {
        JOB_LOG(Log::LT_ERROR, 318, L"[job], check db name validity fail", L", dbrtn:%d" REQ_FMT, dbrtn,
                REQ_ARGS(req));
        if (dbrtn == 1)
            reason = 6;
        else if (dbrtn == 2)
            reason = 124;
        else if (dbrtn == 3)
            reason = 125;
        else
            reason = 2;
        goto initfail;
    }

    {
        _gamed = gamed;
        _lgate = req->lgate;
        _slotid = req->slotid;
        _wid = req->wid;
        _characterNameLen = static_cast<short>(wcslen(req->characterName));
        _characterName = static_cast<wchar_t*>(
            Memory::_Manager[2]->AllocZero(sizeof(wchar_t) * (_characterNameLen + 1), kFile, 343));
        wcscpy_s(_characterName, _characterNameLen + 1, req->characterName);
        _characterMakeDataSize = req->characterMakeDataSize;
        _characterMakeData = static_cast<char*>(Memory::_Manager[2]->AllocZero(_characterMakeDataSize, kFile, 346));
        memcpy(_characterMakeData, req->characterMakeData, _characterMakeDataSize);
        _jumpingCharacter = req->jumpingCharacter;
        _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 350)) LobbyJobTransaction;
        _lgate->addReferenceCount(false, kFile, 352);
        JOB_LOG(Log::LT_DEBUG, 354, L"[job], init ok", REQ_FMT, REQ_ARGS(req));
        transit(GET_SLOT);
        return true;
    }

initfail:
    if (req->lgate != nullptr)
        req->lgate->SendCreateCharacterFail(_owner->_clikey, req->slotid, reason);
    if (gamed != nullptr)
        gamed->removeReferenceCount(kFile, 367);
    transit(FIN);
    return true;
}

// 0x43260
bool CreateCharacterJob::reqGetSlot()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    NPLobbyJobTransaction* const tr =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 375)) NPLobbyJobTransaction;
    if (gs->SendRequestSlotGetSlot(tr->Set(this, 38), _owner->_acb._id, _slotid))
        return true;

    JOB_LOG(Log::LT_ERROR, 377, L"[job], req get slot fail; unsent", L"");
    _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, 2);
    // LIFT: the original calls the scalar deleting destructor (flag 1) and then Free. Its operator delete is empty.
    tr->~NPLobbyJobTransaction();
    Memory::_Manager[2]->Free(tr, kFile, 379);
    // LIFT: the original returns false here and does not transit to FIN.
    return false;
}

// 0x433f0
bool CreateCharacterJob::responseGetSlot(void* param)
{
    short reason = 0;
    if (_owner->_state == 0x60000)  // CSS_FIN
    {
        JOB_LOG(Log::LT_ERROR, 388, L"[job], cli-session finished", L"");
        reason = 5;
        goto fail;
    }
    if (param == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 395, L"[job], null param", L"");
        reason = 2;
        goto fail;
    }

    {
        StsMsgLib::_StsMsgResponseSlotGetSlot* const res = static_cast<StsMsgLib::_StsMsgResponseSlotGetSlot*>(param);
        unsigned int const statusCode = res->msgInfo.errInfo.nStatusCode;
        wchar_t const* const statusReason = res->msgInfo.errInfo.pwszReason;
        if (!(statusCode == 200 ||
              (statusCode == 400 && _wcsicmp(L"Success", statusReason != nullptr ? statusReason : L"null") == 0)))
        {
            JOB_LOG(Log::LT_ERROR, 404, L"[job], get slot fail",
                    L",np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
                    res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                    res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                    res->msgInfo.errInfo.nErrorCode);
            reason = 126;
            goto fail;
        }
        if (memcmp(&res->guidSlotId, &_slotid, sizeof(_slotid)) != 0)
        {
            JOB_LOG(Log::LT_ERROR, 412, L"[job], slot-id mismatch", L",recv:slot-id:" SLOTID_FMT,
                    GUID_ARGS(res->guidSlotId));
            reason = 2;
            goto fail;
        }
        // The original compares 5 wide chars (with the NUL). LIFT: null check added (not in the original).
        if (res->pwszSlotType == nullptr || wcscmp(res->pwszSlotType, L"char") != 0)
        {
            JOB_LOG(Log::LT_ERROR, 419, L"[job], not character slot", L", slot-type:%s", res->pwszSlotType);
            reason = 126;
            goto fail;
        }
        JOB_LOG(Log::LT_DEBUG, 425, L"[job], get slot ok", L", slot-id:" SLOTID_FMT, GUID_ARGS(res->guidSlotId));
        if (!res->bSystemSlot &&
            _owner->getLobbyServiceByType(static_cast<unsigned long long>(res->slotData.serviceId), 1) != nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 431, L"[job], slot stuck by lobby-service", L", lobby-service-id:0x%I64X",
                    res->slotData.serviceId);
            reason = 126;
            goto fail;
        }
        transit(CREATE_CHARACTER);
        return true;
    }

fail:
    _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, reason);
    transit(FIN);
    return true;
}

// 0x43a80
bool CreateCharacterJob::expireGetSlot()
{
    JOB_LOG(Log::LT_ERROR, 444, L"[job], get slot expired", L"");
    _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, 2);
    transit(FIN);
    return true;
}

// 0x43b90
bool CreateCharacterJob::tryCreateCharacter()
{
    if (_owner->getCharacterInSlot(_slotid) != nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 453, L"[job], slot already occupied", L"");
        _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, 127);
        transit(FIN);
        return true;
    }

    if (_jumpingCharacter)
    {
        LobbyConfig const* const config = LobbyDaemon::_instance->_config;
        if (config->_useJumpingCharacterCreationQuota && !config->_useJumpingCharacterCreationQuotaInWorld)
        {
            JumpingCharacterCreationQuota& quota = _owner->_jumpingCharacterCreationQuota;
            int const creationCount = quota._db.creationCount;
            int const creationQuota = quota._db.creationQuota;
            if (quota._reservedCreationCount + creationCount >= creationQuota)
            {
                JOB_LOG(Log::LT_ERROR, 467, L"[job], restricted by quota",
                        L", creationQuota:%d, creationCount:%d, reservedCreationCount:%d", quota._db.creationQuota,
                        quota._db.creationCount, quota._reservedCreationCount);
                _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, 133);
                transit(FIN);
                return true;
            }
            ++quota._reservedCreationCount;
            JOB_LOG(Log::LT_DEBUG, 475, L"[job], reserved quota",
                    L", creationQuota:%d, creationCount:%d, new-reservedCreationCount:%d", creationQuota,
                    creationCount, _owner->_jumpingCharacterCreationQuota._reservedCreationCount);
        }
    }

    Character* const pc = ConstructCharacter(Memory::_Manager[2]->Alloc(sizeof(Character), kFile, 478));
    // LIFT: the original calls TryCreation without a null check. Here a failed Alloc gives ERR_SYSTEM.
    Character::ErrCode const err =
        pc != nullptr ? pc->TryCreation(_owner->_acb, _slotid, _wid, _characterName, _characterNameLen)
                      : Character::ERR_SYSTEM;
    if (err != Character::ERR_OK)
    {
        JOB_LOG(Log::LT_ERROR, 483, L"[job], new pc cannot be created", L", error:%d", err);
        short reason = 2;
        if (err == Character::ERR_NAME_IN_USE)
            reason = 124;
        else if (err == Character::ERR_LIMITED_NAME)
            reason = 125;
        _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, reason);
        if (pc != nullptr)
        {
            DestroyCharacter(pc);
            Memory::_Manager[2]->Free(pc, kFile, 497);
        }
    }
    else if (pc != nullptr)  // the inlined addCharacter
    {
        _owner->_characters.push_back(pc);
        _pcid = pc->_db.pcid;
        JOB_LOG(Log::LT_DEBUG, 514, L"[job], try create character ok", L", pcid:0x%I64X", _pcid);

        CliSession* const owner = _owner;
        short topCharacterLevel = 0;
        for (std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator i = owner->_characters.begin();
             i != owner->_characters.end(); ++i)
        {
            if (*i != nullptr && topCharacterLevel < (*i)->_db.level)
                topCharacterLevel = (*i)->_db.level;
        }
        _gamed->SendCreateCharacterReq(_tran->Set(this, 107), _pcid, owner->_acb._id, owner->_externalAccountKey,
                                       owner->_externalAccountKeySize, static_cast<int>(owner->_ipv4), _characterName,
                                       _characterMakeData, _characterMakeDataSize, _jumpingCharacter,
                                       topCharacterLevel);
        return true;
    }
    else
    {
        // LIFT: not reachable here (the null pc takes the error path above). The original logs pc->_db.pcid from
        // the null pc. Here the log gets 0.
        JOB_LOG(Log::LT_ERROR, 504, L"[job], add character fail", L", pcid:0x%I64X", 0ULL);
        _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, 2);
        Memory::_Manager[2]->Free(pc, kFile, 506);
    }

    RollbackReservedQuota(_owner, _jumpingCharacter);
    transit(FIN);
    return true;
}

// 0x44270
bool CreateCharacterJob::createCharacterOk(void* param)
{
    JOB_LOG(Log::LT_DEBUG, 534, L"[job], create character ok recv", L"");
    _gamed->TRecv(_tran);

    short reason = 0;
    Character* pc = nullptr;
    if (_owner->_state == 0x60000)  // CSS_FIN
    {
        JOB_LOG(Log::LT_ERROR, 539, L"[job], cli-session finished", L"");
        reason = 5;
        goto fail;
    }
    if (param == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 548, L"[job], invalid parameter", L"");
        reason = 2;
        goto fail;
    }
    pc = FindCharacter(_owner, _pcid);
    if (pc == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 558, L"[job], no such character", L",pcid:0x%I64X", _pcid);
        reason = 2;
        goto fail;
    }

    {
        CreateCharacterOkParam* const ok = static_cast<CreateCharacterOkParam*>(param);
        LobbyConfig const* const config = LobbyDaemon::_instance->_config;
        char jumpingCharacterState = 0;
        bool useQuota = false;
        if (_jumpingCharacter)
        {
            if (!config->_useJumpingCharacterCreationQuota)
            {
                jumpingCharacterState = 2;
            }
            else if (!config->_useJumpingCharacterCreationQuotaInWorld)
            {
                useQuota = true;
                jumpingCharacterState = 2;
            }
            else
            {
                jumpingCharacterState = 1;
            }
        }
        Character::ErrCode const err = pc->FinishCreation(ok->job, ok->level, jumpingCharacterState, useQuota,
                                                          ok->showcaseData, ok->showcaseDataSize);
        if (err != Character::ERR_OK)
        {
            JOB_LOG(Log::LT_ERROR, 584, L"[job], finish character creation fail",
                    L", error:%d, level:%d, jumpingCharacter:%d, showcase:%p, size:%d", err, ok->level,
                    _jumpingCharacter, ok->showcaseData, ok->showcaseDataSize);
            _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, 2);
            _owner->removeCharacter(_pcid);
            DestroyCharacter(pc);
            Memory::_Manager[2]->Free(pc, kFile, 587);
            RollbackReservedQuota(_owner, _jumpingCharacter);
            transit(FIN);
            return true;
        }

        if (_jumpingCharacter)
        {
            LobbyConfig const* const cfg = LobbyDaemon::_instance->_config;
            if (cfg->_useJumpingCharacterCreationQuota && !cfg->_useJumpingCharacterCreationQuotaInWorld)
            {
                --_owner->_jumpingCharacterCreationQuota._reservedCreationCount;
                ++_owner->_jumpingCharacterCreationQuota._db.creationCount;
            }
        }
        int const remain = _owner->_jumpingCharacterCreationQuota._db.creationQuota -
                           _owner->_jumpingCharacterCreationQuota._db.creationCount;
        // ❓ The pseudocode shows only the job argument. The other arguments follow the format string.
        JOB_LOG(Log::LT_DEBUG, 601, L"[job], finish character creation ok",
                L", job:%d, level:%d, jumping-character:%d, jumping-character-state:%d, "
                L"remain-jumping-character-creation-quota:%d, showcase-size:%d",
                ok->job, ok->level, _jumpingCharacter, pc->_db.jumpingCharacterState, remain, ok->showcaseDataSize);
        // The original passes the remaining quota as deleteRemainTime and the level as the last (unused) int.
        _lgate->SendCreateCharacterOk(_owner->_clikey, pc->_db.pcid, pc->_db.slotid, pc->_db.belongingWorld,
                                      pc->_db.name, pc->_db.showcase, pc->_db.showcaseSize, pc->_db.lastPlayEndTime,
                                      pc->_db.jumpingCharacterState, remain, ok->level);
        transit(FIN);
        return true;
    }

fail:
    _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, reason);
    RollbackReservedQuota(_owner, _jumpingCharacter);
    transit(FIN);
    return true;
}

// 0x44900
bool CreateCharacterJob::createCharacterFail(short reason)
{
    JOB_LOG(Log::LT_ERROR, 612, L"[job], create character fail recv", L", reason:%d", reason);
    _gamed->TRecv(_tran);
    if (_owner->_state == 0x60000)  // CSS_FIN
    {
        JOB_LOG(Log::LT_ERROR, 617, L"[job], cli-session finished", L"");
    }
    else
    {
        Character* const pc = FindCharacter(_owner, _pcid);
        if (pc == nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 626, L"[job], no such character", L", pcid:0x%I64X", _pcid);
            _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, 2);
        }
        else
        {
            Character::ErrCode const err = pc->CancelCreation();
            if (err != Character::ERR_OK)
                JOB_LOG(Log::LT_ERROR, 637, L"[job], cancel creation fail", L", error:%d, pcid:0x%I64X", err, _pcid);
            else
                JOB_LOG(Log::LT_DEBUG, 635, L"[job], cancel creation ok", L", pcid:0x%I64X", _pcid);
            _owner->removeCharacter(_pcid);
            _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, 2);
            DestroyCharacter(pc);
            Memory::_Manager[2]->Free(pc, kFile, 643);
        }
    }
    RollbackReservedQuota(_owner, _jumpingCharacter);
    transit(FIN);
    return true;
}

// 0x44d40
bool CreateCharacterJob::createCharacterExpire()
{
    JOB_LOG(Log::LT_ERROR, 651, L"[job], create character expired", L"");
    if (_owner->_state == 0x60000)  // CSS_FIN
    {
        JOB_LOG(Log::LT_ERROR, 654, L"[job], cli-session finished", L"");
        _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, 2);
    }
    else
    {
        Character* const pc = FindCharacter(_owner, _pcid);
        if (pc == nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 665, L"[job], no such character", L", pcid:0x%I64X", _pcid);
            _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, 2);
        }
        else
        {
            _owner->removeCharacter(_pcid);
            _lgate->SendCreateCharacterFail(_owner->_clikey, _slotid, 2);
            DestroyCharacter(pc);
            Memory::_Manager[2]->Free(pc, kFile, 676);
        }
    }
    RollbackReservedQuota(_owner, _jumpingCharacter);
    transit(FIN);
    return true;
}
