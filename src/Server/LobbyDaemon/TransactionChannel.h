// TransactionChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: TransactionChannel has its PDB layout (ld-18). LobbyJobTransaction has no layout yet.
#pragma once
#include <stddef.h>
#include "RefCntList.h"
#include "SharedChannel.h"

class Packet;

class LobbyJobTransaction
{
public:
    virtual unsigned long long GetTid() const;  // 0x7b0d0
    virtual void Expire();  // 0x7b7a0
};

class TransactionChannel : public SharedChannel
{
public:
    class Transaction : public RefCntListNode
    {
    public:
        virtual unsigned long long GetTid() const = 0;  // slot 4
        virtual void Expire() = 0;  // slot 5
        virtual ~Transaction();

        long long _expire;
    };

    virtual ~TransactionChannel();  // 0x7b100
    bool InitializeTransactionChannel(long);  // 0x7b170
    bool TSend(Transaction* t, Packet const* packet);  // 0x7b2b0 (Not done: card ld-18 batch 1 only calls it)

    class Manager;  // PDB type 0x485B; no layout yet
    Manager* _mgr;
    long _tranLifetime;
};
static_assert(sizeof(TransactionChannel) == 0x30, "sizeof TransactionChannel");
static_assert(offsetof(TransactionChannel, _mgr) == 0x20, "TransactionChannel::_mgr");
static_assert(offsetof(TransactionChannel, _tranLifetime) == 0x28, "TransactionChannel::_tranLifetime");
static_assert(sizeof(TransactionChannel::Transaction) == 0x38, "sizeof TransactionChannel::Transaction");
static_assert(offsetof(TransactionChannel::Transaction, _expire) == 0x30, "TransactionChannel::Transaction::_expire");
