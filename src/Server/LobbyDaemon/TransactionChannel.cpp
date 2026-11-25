// TransactionChannel.obj (LobbyDaemon PDB, 2019 + PDB). Source file name from log strings: "TransactionChannel.cpp".
// Logic from the 2019 + PDB Hex-Rays pseudocode.
#include <windows.h>
#include <new>
#include "TransactionChannel.h"
#include "LobbyDaemon.h"
#include "LobbyJob.h"
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "MemoryManager.h"

static wchar_t const* const kFile = L"TransactionChannel.cpp";

// 0x7b0d0
unsigned long long LobbyJobTransaction::GetTid() const
{
    return _jobid;
}

// 0x7b100
TransactionChannel::~TransactionChannel()
{
    if (_mgr != nullptr)
    {
        LobbyDaemon::_instance->_tick->Remove(_mgr);
        _mgr->removeReferenceCount(kFile, 26);
        _mgr = nullptr;
    }
}

// 0x7b170
bool TransactionChannel::InitializeTransactionChannel(long transactionLifetime)
{
    if (_mgr != nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 34, L"[tran-channel], initialize fail; already initialized");
        return false;
    }
    // LIFT: line 38 is in the disassembly (the HR drops the line argument).
    _mgr = new (Memory::_Manager[2]->Alloc(sizeof(Manager), kFile, 38)) Manager();
    _tranLifetime = transactionLifetime;
    if (transactionLifetime <= 0 || LobbyDaemon::_instance->_tick->Add(_mgr))
        return true;
    Log::Write(Log::LT_ERROR, kFile, 44, L"[tran-channel], initialize fail; add manager to lobby tick fail");
    _mgr->removeReferenceCount(kFile, 45);
    _mgr = nullptr;
    return false;
}

// No own body. LTCG inlines it at the callers (for example GetGoodsCountJob::getGoodsCountOk, 0x51b80).
bool TransactionChannel::TRecv(Transaction* t)
{
    if (_mgr != nullptr)
        return _mgr->remove(t);
    Log::Write(Log::LT_ERROR, kFile, 155, L"== CRASH == [tran-channel], send fail; manager not initialized");
    AlertSender::Write(kFile, 155, L"== CRASH == [tran-channel], send fail; manager not initialized");
    return false;
}

// 0x7b440
bool TransactionChannel::Manager::add(Transaction* t)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 179, L"[tran-channel], add to manager fail; invalid parameter");
        return false;
    }
    EnterCriticalSection(&_lock.CS);
    bool const result = _tranlist.Pushback(t);
    LeaveCriticalSection(&_lock.CS);
    return result;
}

// 0x7b4c0
bool TransactionChannel::Manager::remove(Transaction* t)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 192, L"[tran-channel], remove from manager fail; invalid parameter");
        return false;
    }
    EnterCriticalSection(&_lock.CS);
    bool const result = _tranlist.Remove(t);
    LeaveCriticalSection(&_lock.CS);
    return result;
}

// 0x7b540
bool TransactionChannel::Manager::Tick(long long elapsed)
{
    RefCntList expiredlist;
    EnterCriticalSection(&_lock.CS);
    // The list is in expire order. Move each expired transaction to the local list.
    for (Transaction* t = static_cast<Transaction*>(_tranlist.Begin()); t != nullptr;
         t = static_cast<Transaction*>(_tranlist.Begin()))
    {
        if (elapsed - t->_expire < 0)
            break;
        _tranlist.Popfront();
        expiredlist.Pushback(t);
        t->removeReferenceCount(kFile, 239);
    }
    LeaveCriticalSection(&_lock.CS);
    // Expire the transactions out of the lock.
    while (Transaction* t = static_cast<Transaction*>(expiredlist.Popfront()))
    {
        Log::Write(Log::LT_ERROR, kFile, 246, L"[tran-channel], transaction expired, tid:0x%I64X", t->GetTid());
        t->Expire();
        t->removeReferenceCount(kFile, 248);
    }
    return true;
}

// 0x7b7a0
void LobbyJobTransaction::Expire()
{
    LobbyDaemon::_instance->_jobMgr->ResumeW(_jobid, _state, _task, nullptr);
    _state = -1;
    _jobid = 0;
    _task = 0;
}

// 0x7b7e0
TransactionChannel::Transaction* LobbyJobTransaction::Set(LobbyJob* job, int task)
{
    if (job == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 281, L"== CRASH == [lobby-job-tran], set context fail; invalid parameter");
        AlertSender::Write(kFile, 281, L"== CRASH == [lobby-job-tran], set context fail; invalid parameter");
        return nullptr;
    }
    _jobid = job->_id;
    _state = job->_state;
    _task = task;
    return this;
}
