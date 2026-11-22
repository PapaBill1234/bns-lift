// LobbyService.obj (LobbyDaemon PDB, 2019 + PDB).
#include "LobbyService.h"
#include "AlertSender.h"
#include "Character.h"
#include "CliSession.h"
#include "FragmentPacket.h"
#include "LiftStub.h"
#include "LobbyDB.h"
#include "Log.h"
#include "StringUtil.h"

// LIFT: Shared note for 0x6f1b0 to 0x71350 (45 log calls). The original Start, ConsumeItemTried, TaskDone,
// ConsumeItemFinished and Finish logs write "cli-key:0x%I64X" with owner->_clikey. The client session key
// authenticates the client session, so this lift keeps it out of the log files. The rest of each message is
// the original text. The client cannot see this change. Restoring the key needs an owner decision.

// LIFT: The original null-owner paths test this for null before each _db read for a log argument (for example 0x70040).
#define LOBBY_SERVICE_DB_LOG_ARGS(s) \
    ((s) != nullptr ? (s)->_db.serviceId : 0ULL), ((s) != nullptr ? (s)->_db.serviceType : 0), \
    ((s) != nullptr ? (s)->_db.serviceState : 0), ((s) != nullptr ? (s)->_db.itemInstanceId : 0ULL)

#pragma comment(linker, "/INCLUDE:?Setup@CharacterCosmesisService@@QEAA_NPEAUDB@LobbyService@@PEAU21@@Z")  // LIFT: Keep 0x6c4a0 until its caller is lifted.
#pragma comment(linker, "/INCLUDE:?Setup@AddSlotService@@QEAA_NPEAUDB@LobbyService@@PEAU21@@Z")  // LIFT: Keep 0x6d180 until its caller is lifted.
#pragma comment(linker, "/INCLUDE:?IsServiceTarget@AddSlotService@@UEAA_NAEBTid128@@@Z")  // LIFT: Keep 0x6d3e0 until its caller is lifted.
#pragma comment(linker, "/INCLUDE:?Setup@RenameCharacterService@@QEAA_NPEAUDB@LobbyService@@PEAU21@@Z")  // LIFT: Keep 0x6deb0 until its caller is lifted.
#pragma comment(linker, "/INCLUDE:?Fetch@RenameUserService@@UEBA_NPEAVCliSession@@PEAVFragmentPacket@@@Z")  // LIFT: Keep 0x6ec40 until its caller is lifted.

bool LobbyService::setup(DB* sedb)
{
    if (sedb != nullptr)
    {
        _db = *sedb;
        return true;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 30, L"== CRASH == [lobby-service], setup fail; invalid param");
    AlertSender::Write(L"LobbyService.cpp", 30, L"== CRASH == [lobby-service], setup fail; invalid param");
    return false;
}

// 0x6c4a0
bool CharacterCosmesisService::Setup(LobbyService::DB* sedb, DB* db)
{
    if (sedb == nullptr)
        return setup(sedb);
    if (db == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 85, L"== CRASH == [lobby-service], setup character cosmesis service entry fail; invalid param");
        AlertSender::Write(L"LobbyService.cpp", 85, L"== CRASH == [lobby-service], setup character cosmesis service entry fail; invalid param");
        return false;
    }
    // LIFT: 0x6c4a0. Check both inputs before changing either record.
    setup(sedb);
    _characterCosmesisServiceDB = *db;
    return true;
}

// 0x6d180
bool AddSlotService::Setup(LobbyService::DB* sedb, DB* db)
{
    if (sedb == nullptr)
        return setup(sedb);
    if (db == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 302, L"== CRASH == [lobby-service], setup add slot service entry fail; invalid param");
        AlertSender::Write(L"LobbyService.cpp", 302, L"== CRASH == [lobby-service], setup add slot service entry fail; invalid param");
        return false;
    }
    // LIFT: 0x6d180. Check both inputs before changing either record.
    setup(sedb);
    _dbAddSlotService = *db;
    return true;
}

// 0x6deb0
bool RenameCharacterService::Setup(LobbyService::DB* sedb, DB* db)
{
    if (sedb == nullptr)
        return setup(sedb);
    if (db == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 512, L"== CRASH == [lobby-service], setup rename character service entry fail; invalid param");
        AlertSender::Write(L"LobbyService.cpp", 512, L"== CRASH == [lobby-service], setup rename character service entry fail; invalid param");
        return false;
    }
    // LIFT: 0x6deb0. Check both inputs before changing either record.
    setup(sedb);
    _dbRenameCharacterService = *db;
    return true;
}

// 0x6c330
// LIFT: 0x6f000, 0x6fc10 and 0x70900 call this stub first. /LTCG sees that the stub does not return, so it
// removes the rest of each caller, and /OPT:ICF folds the three callers into one body. Their funcdiff score
// stays 0.0 until 0x6c330 is lifted (Not done in lift-lobbydaemon-6). noinline does not stop this.
bool LobbyService::Fetch(CliSession*, FragmentPacket*) const
{
    LIFT_STUB(0x6c330);
}

// 0x6c550
bool CharacterCosmesisService::Fetch(CliSession*, FragmentPacket*) const
{
    LIFT_STUB(0x6c550);
}

// 0x6c760
bool ChangeCharacterRaceService::IsServiceTarget(Character*)
{
    LIFT_STUB(0x6c760);
}

// 0x6c760 (folded)
bool ChangeCharacterSexService::IsServiceTarget(Character*)
{
    LIFT_STUB(0x6c760);
}

// 0x6c760 (folded)
bool CharacterCosmesisService::IsServiceTarget(Character*)
{
    LIFT_STUB(0x6c760);
}

// 0x6c780
bool CharacterCosmesisService::Start(CliSession*, unsigned int, char*, int)
{
    LIFT_STUB(0x6c780);
}

// 0x6c980
bool CharacterCosmesisService::ConsumeItemTried(CliSession*)
{
    LIFT_STUB(0x6c980);
}

// 0x6cb80
bool CharacterCosmesisService::TaskDone(CliSession*)
{
    LIFT_STUB(0x6cb80);
}

// 0x6cd80
bool CharacterCosmesisService::ConsumeItemFinished(CliSession*)
{
    LIFT_STUB(0x6cd80);
}

// 0x6cf80
bool CharacterCosmesisService::Finish(CliSession*)
{
    LIFT_STUB(0x6cf80);
}

// 0x6d240
bool AddSlotService::Fetch(CliSession*, FragmentPacket*) const
{
    LIFT_STUB(0x6d240);
}

// 0x6d3e0
bool AddSlotService::IsServiceTarget(id128 const& slotid)
{
    if (slotid.id[0] == 0 && slotid.id[1] == 0)
        return false;
    return _dbAddSlotService.slotid.id[0] == slotid.id[0] && _dbAddSlotService.slotid.id[1] == slotid.id[1];
}

// 0x6d420
bool AddSlotService::Start(CliSession*, unsigned int)
{
    LIFT_STUB(0x6d420);
}

// 0x6d5d0
bool AddSlotService::ConsumeItemTried(CliSession*)
{
    LIFT_STUB(0x6d5d0);
}

// 0x6d7d0
bool AddSlotService::TaskDone(CliSession*, id128 const&)
{
    LIFT_STUB(0x6d7d0);
}

// 0x6dab0
bool AddSlotService::ConsumeItemFinished(CliSession*)
{
    LIFT_STUB(0x6dab0);
}

// 0x6dcb0
bool AddSlotService::Finish(CliSession*)
{
    LIFT_STUB(0x6dcb0);
}

// 0x6df60
bool RenameCharacterService::Fetch(CliSession*, FragmentPacket*) const
{
    LIFT_STUB(0x6df60);
}

// 0x6e170
bool RenameCharacterService::IsServiceTarget(Character*)
{
    LIFT_STUB(0x6e170);
}

// 0x6e190
bool RenameCharacterService::Start(CliSession*, unsigned int, wchar_t const*, int)
{
    LIFT_STUB(0x6e190);
}

// 0x6e440
bool RenameCharacterService::ConsumeItemTried(CliSession*)
{
    LIFT_STUB(0x6e440);
}

// 0x6e640
bool RenameCharacterService::TaskDone(CliSession*)
{
    LIFT_STUB(0x6e640);
}

// 0x6e840
bool RenameCharacterService::ConsumeItemFinished(CliSession*)
{
    LIFT_STUB(0x6e840);
}

// 0x6ea40
bool RenameCharacterService::Finish(CliSession*)
{
    LIFT_STUB(0x6ea40);
}

// 0x6ec40
bool RenameUserService::Fetch(CliSession* owner, FragmentPacket*) const
{
    unsigned int state = 0;
    if (owner != nullptr)
        state = static_cast<unsigned int>(owner->_state);
    // LIFT: 0x6ec40. Do not write client session identifiers to logs or alerts.
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 746,
               L"== CRASH == [lobby-service], rename user service must not be fetched, cli-state:%d.%d",
               static_cast<int>(state >> 16), static_cast<int>(state & 0xffff));
    AlertSender::Write(L"LobbyService.cpp", 746,
                       L"== CRASH == [lobby-service], rename user service must not be fetched, cli-state:%d.%d",
                       static_cast<int>(state >> 16), static_cast<int>(state & 0xffff));
    return false;
}

// 0x6ece0
bool RenameUserService::Start(CliSession*, wchar_t const*, wchar_t const*)
{
    LIFT_STUB(0x6ece0);
}

// 0x6edf0
#pragma comment(linker, "/INCLUDE:?Finish@RenameUserService@@QEAA_NPEAVCliSession@@_KI@Z")  // LIFT: Keep 0x6edf0 until its caller is lifted.
bool RenameUserService::Finish(CliSession* owner, unsigned long long itemInstanceId, unsigned int itemDataId)
{
    if (owner == nullptr)
    {
        RenameUserService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 775,
            L"== CRASH == [lobby-service], finish rename user service fail; null owner, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 775,
            L"== CRASH == [lobby-service], finish rename user service fail; null owner, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 1)
    {
        int dbrtn = 0;
        if (LobbyDB::WriteUserRenameServiceLog(dbrtn, owner->_acb._id, itemInstanceId, itemDataId,
                                          _oldUserName, sizeof(_oldUserName), _newUserName, sizeof(_newUserName)))
        {
            _db.serviceState = 5;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 795,
                L"[lobby-service], finish rename user service ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 789,
            L"[lobby-service], finish rename user service fail; db fail, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 780,
        L"[lobby-service], finish rename user service fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x6ef90
#pragma comment(linker, "/INCLUDE:?Setup@ExtendJumpingCharacterCreationQuotaService@@QEAA_NPEAUDB@LobbyService@@@Z")  // LIFT: Keep 0x6ef90 until its caller is lifted.
bool ExtendJumpingCharacterCreationQuotaService::Setup(LobbyService::DB* sedb)
{
    return setup(sedb);
}

// 0x6f000
#pragma comment(linker, "/INCLUDE:?Fetch@ExtendJumpingCharacterCreationQuotaService@@UEBA_NPEAVCliSession@@PEAVFragmentPacket@@@Z")  // LIFT: Keep 0x6f000 until its caller is lifted.
bool ExtendJumpingCharacterCreationQuotaService::Fetch(CliSession* owner, FragmentPacket* fp) const
{
    if (!LobbyService::Fetch(owner, fp))
        return false;
    if (owner == nullptr || fp == nullptr)
    {
        ExtendJumpingCharacterCreationQuotaService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 826,
            L"== CRASH == [lobby-service], fetch extend jumping character creation quota service entry fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 826,
            L"== CRASH == [lobby-service], fetch extend jumping character creation quota service entry fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    // LIFT: 0x6f000. The entry has no slot id. The original composes ID128_GUID_ZERO and two zeros.
    if (fp->FreeSize() < 0x1A)
        fp->packet.Allocate(&fp->composer);
    if (fp->Compose(3, ID128_GUID_ZERO, 0, 0) == 0)
    {
        ExtendJumpingCharacterCreationQuotaService const* s = this;  // LIFT: The original tests this for null here too (0x6f000, line 845).
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 845,
            L"[lobby-service], fetch extend jumping character creation quota service entry fail; compose fail, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    return true;
}

// 0x6f1b0
#pragma comment(linker, "/INCLUDE:?Start@ExtendJumpingCharacterCreationQuotaService@@QEAA_NPEAVCliSession@@I@Z")  // LIFT: Keep 0x6f1b0 until its caller is lifted.
bool ExtendJumpingCharacterCreationQuotaService::Start(CliSession* owner, unsigned int itemDataId)
{
    // LIFT: 0x6f1b0 to 0x6f560. The original also logs owner->_clikey. This lift does not log the client session key.
    if (owner == nullptr)
    {
        ExtendJumpingCharacterCreationQuotaService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 856,
            L"[lobby-service], start fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 0)
    {
        int dbrtn = 0;
        if (LobbyDB::TryExtendJumpingCharacterCreationQuota(dbrtn, owner->_acb._id, _db.itemInstanceId, itemDataId, &_db.serviceId))
        {
            _db.serviceState = 1;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 875,
                L"[lobby-service], register ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 869,
            L"[lobby-service], start fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 862,
        L"[lobby-service], start fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x6f360
#pragma comment(linker, "/INCLUDE:?ConsumeItemTried@ExtendJumpingCharacterCreationQuotaService@@QEAA_NPEAVCliSession@@@Z")  // LIFT: Keep 0x6f360 until its caller is lifted.
bool ExtendJumpingCharacterCreationQuotaService::ConsumeItemTried(CliSession* owner)
{
    if (owner == nullptr)
    {
        ExtendJumpingCharacterCreationQuotaService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 884,
            L"== CRASH == [lobby-service], consume-item-tried fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 884,
            L"== CRASH == [lobby-service], consume-item-tried fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 1)
    {
        int dbrtn = 0;
        if (LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_ExtendJumpingCharacterCreationQuota(dbrtn, _db.serviceId, owner->_acb._id))
        {
            _db.serviceState = 2;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 903,
                L"[lobby-service], consume-item-tried ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 897,
            L"[lobby-service], consume-item-tried fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 890,
        L"[lobby-service], consume-item-tried fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x6f560
#pragma comment(linker, "/INCLUDE:?TaskDone@ExtendJumpingCharacterCreationQuotaService@@QEAA_NPEAVCliSession@@@Z")  // LIFT: Keep 0x6f560 until its caller is lifted.
bool ExtendJumpingCharacterCreationQuotaService::TaskDone(CliSession* owner)
{
    if (owner == nullptr)
    {
        ExtendJumpingCharacterCreationQuotaService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 912,
            L"== CRASH == [lobby-service], task done fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 912,
            L"== CRASH == [lobby-service], task done fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 2)
    {
        int dbrtn = 0;
        if (LobbyDB::UpdateLobbyServiceStateToTaskDoneState_ExtendJumpingCharacterCreationQuota(dbrtn, _db.serviceId, owner->_acb._id))
        {
            _db.serviceState = 3;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 931,
                L"[lobby-service], task done ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 925,
            L"[lobby-service], task done fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 918,
        L"[lobby-service], task done fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x6f760
#pragma comment(linker, "/INCLUDE:?ConsumeItemFinished@ExtendJumpingCharacterCreationQuotaService@@QEAA_NPEAVCliSession@@@Z")  // LIFT: Keep 0x6f760 until its caller is lifted.
bool ExtendJumpingCharacterCreationQuotaService::ConsumeItemFinished(CliSession* owner)
{
    // LIFT: 0x6f760. The original also logs owner->_clikey. This lift does not log the client session key.
    if (owner == nullptr)
    {
        ExtendJumpingCharacterCreationQuotaService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 940,
            L"== CRASH == [lobby-service], consume-item-finished fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 940,
            L"== CRASH == [lobby-service], consume-item-finished fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 3)
    {
        int dbrtn = 0;
        if (LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_ExtendJumpingCharacterCreationQuota(dbrtn, _db.serviceId, owner->_acb._id))
        {
            _db.serviceState = 4;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 959,
                L"[lobby-service], consume-item-finished ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 953,
            L"[lobby-service], consume-item-finished fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 946,
        L"[lobby-service], consume-item-finished fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x6f960
#pragma comment(linker, "/INCLUDE:?Finish@ExtendJumpingCharacterCreationQuotaService@@QEAA_NPEAVCliSession@@@Z")  // LIFT: Keep 0x6f960 until its caller is lifted.
bool ExtendJumpingCharacterCreationQuotaService::Finish(CliSession* owner)
{
    // LIFT: 0x6f960. The original also logs owner->_clikey. This lift does not log the client session key.
    if (owner == nullptr)
    {
        ExtendJumpingCharacterCreationQuotaService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 968,
            L"== CRASH == [lobby-service], finish fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 968,
            L"== CRASH == [lobby-service], finish fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 4)
    {
        int dbrtn = 0;
        if (LobbyDB::FinishExtendJumpingCharacterCreationQuota(dbrtn, _db.serviceId, owner->_acb._id))
        {
            _db.serviceState = 5;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 987,
                L"[lobby-service], finish ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 981,
            L"[lobby-service], finish fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 974,
        L"[lobby-service], finish fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x6fb60
#pragma comment(linker, "/INCLUDE:?Setup@ChangeCharacterSexService@@QEAA_NPEAUDB@LobbyService@@PEAU21@@Z")  // LIFT: Keep 0x6fb60 until its caller is lifted.
bool ChangeCharacterSexService::Setup(LobbyService::DB* sedb, DB* db)
{
    if (sedb == nullptr)
        return setup(sedb);
    // BUG: 0x6fb60 copies the base record even if the derived record is absent.
    _db = *sedb;
    if (db != nullptr)
    {
        _changeCharacterSexServiceDB = *db;
        return true;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1012, L"== CRASH == [lobby-service], setup change character sex service entry fail; invalid param");
    AlertSender::Write(L"LobbyService.cpp", 1012, L"== CRASH == [lobby-service], setup change character sex service entry fail; invalid param");
    return false;
}

// 0x6fc10
#pragma comment(linker, "/INCLUDE:?Fetch@ChangeCharacterSexService@@UEBA_NPEAVCliSession@@PEAVFragmentPacket@@@Z")  // LIFT: Keep 0x6fc10 until its caller is lifted.
bool ChangeCharacterSexService::Fetch(CliSession* owner, FragmentPacket* fp) const
{
    if (!LobbyService::Fetch(owner, fp))
        return false;
    if (owner == nullptr || fp == nullptr)
    {
        ChangeCharacterSexService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1028,
            L"== CRASH == [lobby-service], fetch change character sex service entry fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 1028,
            L"== CRASH == [lobby-service], fetch change character sex service entry fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    // LIFT: 0x6fc10 inlines CliSession::getCharacter (0x35cf0).
    unsigned long long pcid = _changeCharacterSexServiceDB.pcid;
    Character* pc = nullptr;
    if (pcid != 0)
    {
        for (std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator it = owner->_characters.begin();
             it != owner->_characters.end(); ++it)
        {
            if (*it != nullptr && (*it)->_db.pcid == pcid)
            {
                pc = *it;
                break;
            }
        }
    }
    if (pc == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1041,
            L"[lobby-service], fetch change character sex service entry fail; no such pc, pcid:0x%I64X, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            pcid, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    id128 slotid = pc->_db.slotid;
    if (fp->FreeSize() < 0x1A)
        fp->packet.Allocate(&fp->composer);
    if (fp->Compose(3, slotid, 0, 0) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1054,
            L"[lobby-service], fetch change character sex service entry fail; compose fail, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    return true;
}

// 0x6fe20
#pragma comment(linker, "/INCLUDE:?Start@ChangeCharacterSexService@@QEAA_NPEAVCliSession@@IDPEADH@Z")  // LIFT: Keep 0x6fe20 until its caller is lifted.
bool ChangeCharacterSexService::Start(CliSession* owner, unsigned int itemDataId,
                                      char newSex, char* newAppearanceData, int newAppearanceDataSize)
{
    // LIFT: 0x6fe20 to 0x70040. The original also logs owner->_clikey. This lift does not log the client session key.
    // BUG: 0x6fe20 tests only newAppearanceDataSize != 0.
    // LIFT: Safety guard (0x6fe20). The lift rejects newAppearanceDataSize <= 0. See "Safety differences" in the handoff.
    if (owner == nullptr || newSex <= 0 ||
        newAppearanceData == nullptr || newAppearanceDataSize <= 0)
    {
        ChangeCharacterSexService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1073,
            L"[lobby-service], start fail; invalid param, owner:%p, new-sex:%d, new-appearance-data:%p, new-apperance-data-size:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            owner, static_cast<int>(newSex), newAppearanceData, newAppearanceDataSize,
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 0)
    {
        int dbrtn = 0;
        if (LobbyDB::TryChangeCharacterSexService(dbrtn, owner->_acb._id, _changeCharacterSexServiceDB.pcid,
                                          _db.itemInstanceId, itemDataId, newSex,
                                          newAppearanceData, newAppearanceDataSize, &_db.serviceId))
        {
            _db.serviceState = 1;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 1092,
                L"[lobby-service], register ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1086,
            L"[lobby-service], start fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1079,
        L"[lobby-service], start fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x70040
#pragma comment(linker, "/INCLUDE:?ConsumeItemTried@ChangeCharacterSexService@@QEAA_NPEAVCliSession@@@Z")  // LIFT: Keep 0x70040 until its caller is lifted.
bool ChangeCharacterSexService::ConsumeItemTried(CliSession* owner)
{
    // LIFT: 0x70040. The original also logs owner->_clikey. This lift does not log the client session key.
    if (owner == nullptr)
    {
        ChangeCharacterSexService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1101,
            L"== CRASH == [lobby-service], consume-item-tried fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 1101,
            L"== CRASH == [lobby-service], consume-item-tried fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 1)
    {
        int dbrtn = 0;
        if (LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_ChangeCharacterSexService(dbrtn, _db.serviceId, owner->_acb._id))
        {
            _db.serviceState = 2;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 1120,
                L"[lobby-service], consume-item-tried ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1114,
            L"[lobby-service], consume-item-tried fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1107,
        L"[lobby-service], consume-item-tried fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x70240
#pragma comment(linker, "/INCLUDE:?TaskDone@ChangeCharacterSexService@@QEAA_NPEAVCliSession@@@Z")  // LIFT: Keep 0x70240 until its caller is lifted.
bool ChangeCharacterSexService::TaskDone(CliSession* owner)
{
    // LIFT: 0x70240. The original also logs owner->_clikey. This lift does not log the client session key.
    if (owner == nullptr)
    {
        ChangeCharacterSexService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1129,
            L"== CRASH == [lobby-service], task done fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 1129,
            L"== CRASH == [lobby-service], task done fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 2)
    {
        int dbrtn = 0;
        if (LobbyDB::UpdateLobbyServiceStateToTaskDoneState_ChangeCharacterSexService(dbrtn, _db.serviceId, owner->_acb._id))
        {
            _db.serviceState = 3;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 1148,
                L"[lobby-service], task done ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1142,
            L"[lobby-service], task done fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1135,
        L"[lobby-service], task done fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x70440
#pragma comment(linker, "/INCLUDE:?ConsumeItemFinished@ChangeCharacterSexService@@QEAA_NPEAVCliSession@@@Z")  // LIFT: Keep 0x70440 until its caller is lifted.
bool ChangeCharacterSexService::ConsumeItemFinished(CliSession* owner)
{
    // LIFT: 0x70440. The original also logs owner->_clikey. This lift does not log the client session key.
    if (owner == nullptr)
    {
        ChangeCharacterSexService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1157,
            L"== CRASH == [lobby-service], consume-item-finished fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 1157,
            L"== CRASH == [lobby-service], consume-item-finished fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 3)
    {
        int dbrtn = 0;
        if (LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_ChangeCharacterSexService(dbrtn, _db.serviceId, owner->_acb._id))
        {
            _db.serviceState = 4;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 1176,
                L"[lobby-service], consume-item-finished ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1170,
            L"[lobby-service], consume-item-finished fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1163,
        L"[lobby-service], consume-item-finished fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x70640
#pragma comment(linker, "/INCLUDE:?Finish@ChangeCharacterSexService@@QEAA_NPEAVCliSession@@@Z")  // LIFT: Keep 0x70640 until its caller is lifted.
bool ChangeCharacterSexService::Finish(CliSession* owner)
{
    // LIFT: 0x70640. The original also logs owner->_clikey. This lift does not log the client session key.
    if (owner == nullptr)
    {
        ChangeCharacterSexService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1185,
            L"== CRASH == [lobby-service], finish fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 1185,
            L"== CRASH == [lobby-service], finish fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 4)
    {
        int dbrtn = 0;
        if (LobbyDB::FinishChangeCharacterSexService(dbrtn, _db.serviceId, owner->_acb._id))
        {
            _db.serviceState = 5;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 1204,
                L"[lobby-service], finish ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1198,
            L"[lobby-service], finish fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1191,
        L"[lobby-service], finish fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x70850
#pragma comment(linker, "/INCLUDE:?Setup@ChangeCharacterRaceService@@QEAA_NPEAUDB@LobbyService@@PEAU21@@Z")  // LIFT: Keep 0x70850 until its caller is lifted.
bool ChangeCharacterRaceService::Setup(LobbyService::DB* sedb, DB* db)
{
    if (sedb == nullptr)
        return setup(sedb);
    // BUG: 0x70850 copies the base record even if the derived record is absent.
    _db = *sedb;
    if (db != nullptr)
    {
        _changeCharacterRaceServiceDB = *db;
        return true;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1229, L"== CRASH == [lobby-service], setup change character race service entry fail; invalid param");
    AlertSender::Write(L"LobbyService.cpp", 1229, L"== CRASH == [lobby-service], setup change character race service entry fail; invalid param");
    return false;
}

// 0x70900
#pragma comment(linker, "/INCLUDE:?Fetch@ChangeCharacterRaceService@@UEBA_NPEAVCliSession@@PEAVFragmentPacket@@@Z")  // LIFT: Keep 0x70900 until its caller is lifted.
bool ChangeCharacterRaceService::Fetch(CliSession* owner, FragmentPacket* fp) const
{
    if (!LobbyService::Fetch(owner, fp))
        return false;
    if (owner == nullptr || fp == nullptr)
    {
        ChangeCharacterRaceService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1245,
            L"== CRASH == [lobby-service], fetch change character race service entry fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 1245,
            L"== CRASH == [lobby-service], fetch change character race service entry fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    // LIFT: 0x70900 inlines CliSession::getCharacter (0x35cf0).
    unsigned long long pcid = _changeCharacterRaceServiceDB.pcid;
    Character* pc = nullptr;
    if (pcid != 0)
    {
        for (std::vector<Character*, StlAllocator<Character*, 2> >::const_iterator it = owner->_characters.begin();
             it != owner->_characters.end(); ++it)
        {
            if (*it != nullptr && (*it)->_db.pcid == pcid)
            {
                pc = *it;
                break;
            }
        }
    }
    if (pc == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1258,
            L"[lobby-service], fetch change character race service entry fail; no such pc, pcid:0x%I64X, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            pcid, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    id128 slotid = pc->_db.slotid;
    if (fp->FreeSize() < 0x1A)
        fp->packet.Allocate(&fp->composer);
    if (fp->Compose(3, slotid, 0, 0) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1271,
            L"[lobby-service], fetch change character race service entry fail; compose fail, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    return true;
}

// 0x70b10
#pragma comment(linker, "/INCLUDE:?Start@ChangeCharacterRaceService@@QEAA_NPEAVCliSession@@IDDPEADH@Z")  // LIFT: Keep 0x70b10 until its caller is lifted.
bool ChangeCharacterRaceService::Start(CliSession* owner, unsigned int itemDataId, char newRace,
                                      char newSex, char* newAppearanceData, int newAppearanceDataSize)
{
    // LIFT: 0x70b10 to 0x70d50. The original also logs owner->_clikey. This lift does not log the client session key.
    // BUG: 0x70b10 tests only newAppearanceDataSize != 0.
    // LIFT: Safety guard (0x70b10). The lift rejects newAppearanceDataSize <= 0. See "Safety differences" in the handoff.
    if (owner == nullptr || newRace <= 0 || newSex <= 0 ||
        newAppearanceData == nullptr || newAppearanceDataSize <= 0)
    {
        ChangeCharacterRaceService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1290,
            L"[lobby-service], start fail; invalid param, owner:%p, new-race:%d, new-sex:%d, new-appearance-data:%p, new-apperance-data-size:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            owner, static_cast<int>(newRace), static_cast<int>(newSex), newAppearanceData, newAppearanceDataSize,
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 0)
    {
        int dbrtn = 0;
        if (LobbyDB::TryChangeCharacterRaceService(dbrtn, owner->_acb._id, _changeCharacterRaceServiceDB.pcid,
                                          _db.itemInstanceId, itemDataId, newRace, newSex,
                                          newAppearanceData, newAppearanceDataSize, &_db.serviceId))
        {
            _db.serviceState = 1;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 1309,
                L"[lobby-service], register ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1303,
            L"[lobby-service], start fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1296,
        L"[lobby-service], start fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x70d50
#pragma comment(linker, "/INCLUDE:?ConsumeItemTried@ChangeCharacterRaceService@@QEAA_NPEAVCliSession@@@Z")  // LIFT: Keep 0x70d50 until its caller is lifted.
bool ChangeCharacterRaceService::ConsumeItemTried(CliSession* owner)
{
    // LIFT: 0x70d50. The original also logs owner->_clikey in the state, db and ok logs. This lift does not log the client session key.
    if (owner == nullptr)
    {
        ChangeCharacterRaceService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1318,
            L"== CRASH == [lobby-service], consume-item-tried fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 1318,
            L"== CRASH == [lobby-service], consume-item-tried fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 1)
    {
        int dbrtn = 0;
        if (LobbyDB::UpdateLobbyServiceStateToItemConsumptionTryState_ChangeCharacterRaceService(dbrtn, _db.serviceId, owner->_acb._id))
        {
            _db.serviceState = 2;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 1337,
                L"[lobby-service], consume-item-tried ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1331,
            L"[lobby-service], consume-item-tried fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1324,
        L"[lobby-service], consume-item-tried fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x70f50
#pragma comment(linker, "/INCLUDE:?TaskDone@ChangeCharacterRaceService@@QEAA_NPEAVCliSession@@@Z")  // LIFT: Keep 0x70f50 until its caller is lifted.
bool ChangeCharacterRaceService::TaskDone(CliSession* owner)
{
    // LIFT: 0x70f50. The original also logs owner->_clikey in the state, db and ok logs. This lift does not log the client session key.
    if (owner == nullptr)
    {
        ChangeCharacterRaceService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1346,
            L"== CRASH == [lobby-service], task done fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 1346,
            L"== CRASH == [lobby-service], task done fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 2)
    {
        int dbrtn = 0;
        if (LobbyDB::UpdateLobbyServiceStateToTaskDoneState_ChangeCharacterRaceService(dbrtn, _db.serviceId, owner->_acb._id))
        {
            _db.serviceState = 3;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 1365,
                L"[lobby-service], task done ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1359,
            L"[lobby-service], task done fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1352,
        L"[lobby-service], task done fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x71150
#pragma comment(linker, "/INCLUDE:?ConsumeItemFinished@ChangeCharacterRaceService@@QEAA_NPEAVCliSession@@@Z")  // LIFT: Keep 0x71150 until its caller is lifted.
bool ChangeCharacterRaceService::ConsumeItemFinished(CliSession* owner)
{
    // LIFT: 0x71150. The original also logs owner->_clikey in the state, db and ok logs. This lift does not log the client session key.
    if (owner == nullptr)
    {
        ChangeCharacterRaceService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1374,
            L"== CRASH == [lobby-service], consume-item-finished fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 1374,
            L"== CRASH == [lobby-service], consume-item-finished fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 3)
    {
        int dbrtn = 0;
        if (LobbyDB::UpdateLobbyServiceStateToItemConsumptionFinishState_ChangeCharacterRaceService(dbrtn, _db.serviceId, owner->_acb._id))
        {
            _db.serviceState = 4;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 1393,
                L"[lobby-service], consume-item-finished ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1387,
            L"[lobby-service], consume-item-finished fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1380,
        L"[lobby-service], consume-item-finished fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0x71350
#pragma comment(linker, "/INCLUDE:?Finish@ChangeCharacterRaceService@@QEAA_NPEAVCliSession@@@Z")  // LIFT: Keep 0x71350 until its caller is lifted.
bool ChangeCharacterRaceService::Finish(CliSession* owner)
{
    // LIFT: 0x71350. The original also logs owner->_clikey in the state, db and ok logs. This lift does not log the client session key.
    if (owner == nullptr)
    {
        ChangeCharacterRaceService const* s = this;  // LIFT: The original tests this for null before it reads _db for the log arguments.
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1402,
            L"== CRASH == [lobby-service], finish fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        AlertSender::Write(L"LobbyService.cpp", 1402,
            L"== CRASH == [lobby-service], finish fail; invalid param, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            LOBBY_SERVICE_DB_LOG_ARGS(s));
        return false;
    }
    if (_db.serviceState == 4)
    {
        int dbrtn = 0;
        if (LobbyDB::FinishChangeCharacterRaceService(dbrtn, _db.serviceId, owner->_acb._id))
        {
            _db.serviceState = 5;
            Log::Write(Log::LT_DEBUG, L"LobbyService.cpp", 1421,
                L"[lobby-service], finish ok, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
                _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
            return true;
        }
        Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1415,
            L"[lobby-service], finish fail; db error, dbrtn:%d, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
            dbrtn, _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
        return false;
    }
    Log::Write(Log::LT_ERROR, L"LobbyService.cpp", 1408,
        L"[lobby-service], finish fail; invalid state, lobby-service-id:0x%I64X, type:%d, state:%d, item-instance-id:0x%I64X",
        _db.serviceId, _db.serviceType, _db.serviceState, _db.itemInstanceId);
    return false;
}

// 0xefb20
#pragma comment(linker, "/INCLUDE:?IsServiceTarget@LobbyService@@UEAA_NAEBTid128@@@Z")  // LIFT: Keep 0xefb20 until its caller is lifted.
bool LobbyService::IsServiceTarget(id128 const&)
{
    // LIFT: 0xefb20. The linker folds this body with other "return false" functions. IDA shows it as WinServiceConsole::IsServiceTarget.
    return false;
}
