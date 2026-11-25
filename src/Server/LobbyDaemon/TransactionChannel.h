// TransactionChannel.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
#pragma once
#include <stddef.h>
#include "RefCntList.h"
#include "SharedChannel.h"
#include "LobbyTick.h"
#include "Lock.h"

class LobbyJob;
class Packet;

class TransactionChannel : public SharedChannel
{
public:
    class Transaction : public RefCntListNode
    {
    public:
        virtual unsigned long long GetTid() const = 0;  // slot 4
        virtual void Expire() = 0;  // slot 5
        // LIFT: the PDB has no out-of-line body. It is inline (LobbyJobTransaction scalar deleting destructor 0x61030).
        virtual ~Transaction() {}

        long long _expire;
    };

    virtual ~TransactionChannel();  // 0x7b100
    bool InitializeTransactionChannel(long);  // 0x7b170
    bool TSend(Transaction* t, Packet const* packet);  // 0x7b2b0 (Not done: card ld-18 batch 1 only calls it)
    // PDB type 0x485A. LTCG inlines it at all callers. The binary has no own body (gap-06: the goods jobs).
    bool TRecv(Transaction* t);

    class Manager;  // PDB type 0x485B; layout below
    Manager* _mgr;
    long _tranLifetime;
};
static_assert(sizeof(TransactionChannel) == 0x30, "sizeof TransactionChannel");
static_assert(offsetof(TransactionChannel, _mgr) == 0x20, "TransactionChannel::_mgr");
static_assert(offsetof(TransactionChannel, _tranLifetime) == 0x28, "TransactionChannel::_tranLifetime");
static_assert(sizeof(TransactionChannel::Transaction) == 0x38, "sizeof TransactionChannel::Transaction");
static_assert(offsetof(TransactionChannel::Transaction, _expire) == 0x30, "TransactionChannel::Transaction::_expire");

// PDB TransactionChannel::Manager (sizeof 0x78, LobbyTick::Listener base).
class TransactionChannel::Manager : public LobbyTick::Listener
{
public:
    // LIFT: the constructor is inlined in TransactionChannel::InitializeTransactionChannel (0x7b170).
    Manager() {}
    // LIFT: no out-of-line body. The dtor is inlined in the scalar deleting destructor (0x7b3f0).
    virtual ~Manager() {}
    bool add(Transaction* t);  // 0x7b440
    bool remove(Transaction* t);  // 0x7b4c0
    virtual bool Tick(long long elapsed);  // 0x7b540
    // LIFT: the PDB also has expireAll(). The binary has no body for it. It is not declared here.

private:
    CriticalSection _lock;
    RefCntList _tranlist;
};
static_assert(sizeof(TransactionChannel::Manager) == 0x78, "sizeof TransactionChannel::Manager");

// PDB LobbyJobTransaction (sizeof 0x48, TransactionChannel::Transaction base).
class LobbyJobTransaction : public TransactionChannel::Transaction
{
public:
    // LIFT: the constructor is not in the PDB. Same initial state as NPLobbyJobTransaction (Expire resets to it).
    LobbyJobTransaction() : _jobid(0), _state(-1), _task(0) {}
    virtual ~LobbyJobTransaction() {}  // scalar deleting destructor 0x61030
    virtual unsigned long long GetTid() const;  // 0x7b0d0
    virtual void Expire();  // 0x7b7a0
    TransactionChannel::Transaction* Set(LobbyJob* job, int task);  // 0x7b7e0

    unsigned long long _jobid;
    int _state;
    int _task;
};
static_assert(sizeof(LobbyJobTransaction) == 0x48, "sizeof LobbyJobTransaction");
static_assert(offsetof(LobbyJobTransaction, _jobid) == 0x38, "LobbyJobTransaction::_jobid");
static_assert(offsetof(LobbyJobTransaction, _task) == 0x44, "LobbyJobTransaction::_task");
