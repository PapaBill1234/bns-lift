// Mileage.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class FragmentPacket;
class LobbyMessage;
class Mileage;
class MileageConfig;
class MileageLimit;
class MileageSlot;
union id128;

class LobbyMessageAcceptor
{
public:
    virtual ~LobbyMessageAcceptor();  // 0x5d370
};

class Mileage
{
public:
    virtual ~Mileage();  // 0x5d8a0
    virtual bool Initialize(MileageConfig const&, long long);  // 0x5d940
    bool FetchFeverTimeList(FragmentPacket*) const;  // 0x5dbf0
protected:
    bool deposit(id128 const&, long long, long long, long long, MileageLimit*, bool);  // 0x5e1a0
};

class MileageBatchRetryDeposit
{
public:
    virtual bool Tick(long long);  // 0x61060
};

class MileageConfig
{
public:
    MileageConfig();  // 0x5d410
    ~MileageConfig();  // 0x5d460
    bool Check() const;  // 0x5d760
};

struct MileageInfo
{
public:
    bool check() const;  // 0x5d390
};

class MileageInterimDepositTimer
{
public:
    MileageInterimDepositTimer(long long);  // 0x60a80
    virtual ~MileageInterimDepositTimer();  // 0x60b20
    virtual bool Tick(long long);  // 0x60d00
};

class MileageManager
{
public:
    virtual ~MileageManager();  // 0x5f480
    bool Initialize(long long);  // 0x5f5a0
    MileageSlot* CreateSlot(id128 const&, unsigned long long);  // 0x5fc30
    virtual void Accept(LobbyMessage*);  // 0x60660
};

class MileageSession
{
public:
    MileageSession(Mileage*, long long);  // 0x606b0
    virtual ~MileageSession();  // 0x60770
    void ReserveInterimDeposit(unsigned long long);  // 0x60800
};

class MileageSlot
{
public:
    MileageSlot(int);  // 0x608d0
    ~MileageSlot();  // 0x60950
};
