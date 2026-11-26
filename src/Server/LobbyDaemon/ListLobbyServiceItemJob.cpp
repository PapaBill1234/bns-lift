// ListLobbyServiceItemJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "ListLobbyServiceItemJob.h"
#include "AccountInventoryChannel.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "LobbyJobParams.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "TransactionChannel.h"

static wchar_t const kFile[] = L"ListLobbyServiceItemJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// PDB enum ECliSessionState (CliSession.h has no copy yet): CSS_LOBBY = 0x20000, CSS_INIT_create_initial_user_name = 0x10003.

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"LIST_LOBBY_SERVICE_ITEM"}, {2, L"FIN"}};  // 0x12de70
}

LobbyJobDef ListLobbyServiceItemJob::_def = {24, StateDef, 2, L"ListLobbyServiceItemJob"};  // 0x201c10

#include "ObjectPoolLobbyDaemon.h"

// .data 0x204a40, dynamic init 0x11e0c0, atexit dtor 0x11ee80.
// The exe .data holds id 1, objsize 0x80, desc L"ListLobbyServiceItemJob".
ObjPool ListLobbyServiceItemJob::_pool(1, 0x80, L"ListLobbyServiceItemJob");

// 0x55b20
LobbyJobDef const* ListLobbyServiceItemJob::GetDefinition() const
{
    return &_def;
}

// 0x55b30
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void ListLobbyServiceItemJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x55b30);
}

// 0x55b80
// The original constructs a job on the stack (null owner, null lobby-gate) and returns its vfptr. It does not run
// the destructor.
void* ListLobbyServiceItemJob::_vtbl()
{
    char buf[sizeof(ListLobbyServiceItemJob)];
    ListLobbyServiceItemJob* job = ::new (buf) ListLobbyServiceItemJob(nullptr, nullptr, 0, 0);
    return *reinterpret_cast<void**>(job);
}

// 0x55c00
ListLobbyServiceItemJob::ListLobbyServiceItemJob(CliSession* owner, LobbyGateChannel* lgate, char searchType, unsigned long long searchKey) : CliSessionJob(owner), _lgate(lgate), _acciv(nullptr), _tran(nullptr), _searchType(searchType), _searchKey(searchKey)
{
    if (lgate != nullptr)
        lgate->addReferenceCount(false, kFile, 65);
}

// 0x55cb0 (scalar deleting destructor)
ListLobbyServiceItemJob::~ListLobbyServiceItemJob()
{
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 71);
    if (_tran != nullptr)
        _tran->removeReferenceCount(kFile, 73);
}

// 0x55d20
bool ListLobbyServiceItemJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 22)
    {
        result = init();
        task = 0;
    }
    if (_state == LIST_LOBBY_SERVICE_ITEM)
    {
        if (task == 0)
            return listLobbyServiceItemReq();
        else if (task == 153)
            return listLobbyServiceItemOk(param);
        else if (task == 154)
            return listLobbyServiceItemFail(param);
        else if (task == 155)
            return listLobbyServiceItemTimeout();
    }
    return result;
}

// 0x55dc0
bool ListLobbyServiceItemJob::init()
{
    JOB_LOG(Log::LT_DEBUG, 111, L"[job], init param", L", gate-wid:%d", _lgate != nullptr ? (_lgate->_rawChannel != nullptr ? static_cast<short>(_lgate->_rawChannel->GetId()) : 0) : 0);
    short reason = 0;
    int const cliState = _owner->_state;
    if (cliState != 0x20000 && cliState != 0x10003)  // CSS_LOBBY, CSS_INIT_create_initial_user_name
    {
        JOB_LOG(Log::LT_ERROR, 116, L"[job], cli-session not in lobby", L"");
        reason = 5;
    }
    else
    {
        _acciv = LobbyDaemon::_instance->_accountInventoryChannel;
        if (_acciv == nullptr)
        {
            JOB_LOG(Log::LT_ERROR, 125, L"[job], init fail; account-inventory N/A", L"");
            reason = 7;
        }
        else
        {
            _tran = new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobTransaction), kFile, 131)) LobbyJobTransaction;
            JOB_LOG(Log::LT_DEBUG, 133, L"[job], init ok", L"");
        }
    }
    int next = LIST_LOBBY_SERVICE_ITEM;
    if (reason != 0)
    {
        _lgate->SendListLobbyServiceItemInfoFail(_owner->_clikey, _searchType, reason);
        next = FIN;
    }
    transit(next);
    return true;
}

// 0x560f0
bool ListLobbyServiceItemJob::listLobbyServiceItemReq()
{
    if (!_acciv->SendRetrieveLobbyServiceItemListReq(_tran->Set(this, 155), _owner->_acb._id, _searchType, _searchKey))
    {
        JOB_LOG(Log::LT_ERROR, 142, L"[job], unsent", L"");
        _lgate->SendListLobbyServiceItemInfoFail(_owner->_clikey, _searchType, 7);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 148, L"[job], list item req sent", L"");
    }
    return true;
}

// 0x56280
bool ListLobbyServiceItemJob::listLobbyServiceItemOk(void* param)
{
    _acciv->TRecv(_tran);
    RetrieveLobbyServiceItemListOkParam* const ok = static_cast<RetrieveLobbyServiceItemListOkParam*>(param);
    if (ok == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 158, L"[job], invalid param on ok ack", L"");
        _lgate->SendListLobbyServiceItemInfoFail(_owner->_clikey, _searchType, 2);
        transit(FIN);
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 168, L"[job], ok recv", L", item-count:%d", ok->itemCount);
        _lgate->SendListLobbyServiceItemInfoOk(_owner->_clikey, _searchType, ok->searchCount, ok->items, ok->itemCount);
        transit(FIN);
    }
    return true;
}

// 0x56490
bool ListLobbyServiceItemJob::listLobbyServiceItemFail(void* param)
{
    _acciv->TRecv(_tran);
    short* const fail = static_cast<short*>(param);
    short reason;
    if (fail == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 181, L"[job], invalid param on fail ack", L"");
        reason = 2;
    }
    else
    {
        JOB_LOG(Log::LT_DEBUG, 188, L"[job], fail recv", L", reason:%d", *fail);
        reason = *fail == 3 ? 7 : 2;
    }
    _lgate->SendListLobbyServiceItemInfoFail(_owner->_clikey, _searchType, reason);
    transit(FIN);
    return true;
}

// 0x56670
bool ListLobbyServiceItemJob::listLobbyServiceItemTimeout()
{
    JOB_LOG(Log::LT_ERROR, 208, L"[job], timeout", L"");
    _lgate->SendListLobbyServiceItemInfoFail(_owner->_clikey, _searchType, 2);
    transit(FIN);
    return true;
}
