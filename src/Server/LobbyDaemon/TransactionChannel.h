// TransactionChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class LobbyJobTransaction
{
public:
    virtual unsigned long long GetTid() const;  // 0x7b0d0
    virtual void Expire();  // 0x7b7a0
};

class TransactionChannel
{
public:
    virtual ~TransactionChannel();  // 0x7b100
    bool InitializeTransactionChannel(long);  // 0x7b170
};
