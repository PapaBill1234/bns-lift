// LobbyToken.obj (LobbyDaemon PDB, 2019 + PDB).
#pragma once
#include <map>
#include "Lock.h"
#include "LobbyTick.h"
#include "RefCntList.h"
#include "StlMemory.h"

class CliSession;
class Packet;
class SharedChannel;

class LobbyToken : public RefCntListNode
{
public:
    enum Kind
    {
        TOKEN_INVALID = 0,
        TOKEN_ENTER_GAME_WORLD = 1,
        TOKEN_LEAVE_GAME_WORLD = 2,
        TOKEN_KIND_MAX = 3,
    };

    LobbyToken(CliSession* clisession);  // 0x96750
    virtual ~LobbyToken();  // Inlined in 0x967d0.
    bool Verify(int, unsigned long long, unsigned long long, unsigned long) const;  // 0x96830
    virtual Kind GetKind() const = 0;
    virtual void Expire();  // 0x96b00

private:
    friend struct LobbyTokenLayoutCheck;  // LIFT: check private PDB field offsets (0x96750).
    // LIFT: access helper. HandleLobbyGame_EnterWorldReq (0x89270) reads _clisession (the PDB has no friend records).
    friend bool HandleLobbyGame_EnterWorldReq(SharedChannel*, Packet const*);
    // LIFT: access helpers (the PDB has no friend records). LobbyTokenDesk::Issue (0x96e20) sets _tokenkey and _expire.
    // EndWaitGameWorldJob::endWait (0x4b460) and LeaveGameWorldJob::leaveGameWorld (0x87e90) read _tokenkey.
    friend class LobbyTokenDesk;
    friend class EndWaitGameWorldJob;
    friend class LeaveGameWorldJob;

    unsigned long long _tokenkey;
    CliSession* _clisession;
    long long _expire;
};
static_assert(sizeof(LobbyToken) == 0x48, "sizeof LobbyToken");

// LIFT: check private PDB field offsets at compile time (0x96750).
struct LobbyTokenLayoutCheck
{
    static_assert(offsetof(LobbyToken, _tokenkey) == 0x30, "LobbyToken::_tokenkey");
    static_assert(offsetof(LobbyToken, _clisession) == 0x38, "LobbyToken::_clisession");
    static_assert(offsetof(LobbyToken, _expire) == 0x40, "LobbyToken::_expire");
};

// LIFT: PDB layout (sizeof 0x58). The PDB members are private; the lift keeps them public.
class EnterGameWorldToken : public LobbyToken
{
public:
    // The constructor is inline (EndWaitGameWorldJob::endWait, 0x4b460).
    EnterGameWorldToken(CliSession* clisession, short targetGameWorld, unsigned long long targetPcid)
        : LobbyToken(clisession), _targetGameWorld(targetGameWorld), _targetPcid(targetPcid)
    {
    }
    virtual ~EnterGameWorldToken();  // 0x967d0 (scalar deleting destructor, shared)
    virtual Kind GetKind() const;  // 0xe3ec0
    short _targetGameWorld;
    unsigned long long _targetPcid;
};
static_assert(sizeof(EnterGameWorldToken) == 0x58, "sizeof EnterGameWorldToken");
static_assert(offsetof(EnterGameWorldToken, _targetGameWorld) == 0x48, "EnterGameWorldToken::_targetGameWorld");
static_assert(offsetof(EnterGameWorldToken, _targetPcid) == 0x50, "EnterGameWorldToken::_targetPcid");

// PDB layout (sizeof 0x48, LobbyToken base).
class LeaveGameWorldToken : public LobbyToken
{
public:
    // The constructor is inline (LeaveGameWorldJob::leaveGameWorld, 0x87e90).
    LeaveGameWorldToken(CliSession* clisession) : LobbyToken(clisession) {}
    virtual ~LeaveGameWorldToken();  // 0x967d0 (scalar deleting destructor, shared)
    virtual Kind GetKind() const;  // 0x99980 (folded)
};
static_assert(sizeof(LeaveGameWorldToken) == 0x48, "sizeof LeaveGameWorldToken");

// LIFT: PDB layout (sizeof 0xa8, LobbyTick::Listener base). Layout from tools/pdbcls.py LobbyDaemon LobbyTokenDesk (fix7).
// The function bodies except Issue are still LIFT_STUB.
class LobbyTokenDesk : public LobbyTick::Listener
{
public:
    typedef unsigned long long (*LobbyTokenkeyGenerater)();
    typedef std::map<unsigned long long, LobbyToken*, std::less<unsigned long long>,
                     StlAllocator<std::pair<unsigned long long, LobbyToken*>, 2> > TokenMap;

    LobbyTokenDesk(long, unsigned long long (__cdecl*)(void));  // 0x96c30
    virtual ~LobbyTokenDesk();  // 0x96d70
    bool Issue(LobbyToken*);  // 0x96e20
    LobbyToken* Verify(int, unsigned long long, unsigned long long, unsigned long, bool&);  // 0x96fb0
    virtual bool Tick(long long);  // 0x97240

private:
    friend struct LobbyTokenDeskLayoutCheck;  // LIFT: checks the private PDB offsets.

    long _tokenLifeTime;  // +0x38
    LobbyTokenkeyGenerater _keygen;  // +0x40
    TokenMap _tokenmap;  // +0x48
    RefCntList _tokenlist;  // +0x68
    CriticalSection _lock;  // +0x80
};
static_assert(sizeof(LobbyTokenDesk) == 0xa8, "sizeof LobbyTokenDesk");
struct LobbyTokenDeskLayoutCheck
{
    static_assert(offsetof(LobbyTokenDesk, _tokenLifeTime) == 0x38, "LobbyTokenDesk::_tokenLifeTime");
    static_assert(offsetof(LobbyTokenDesk, _keygen) == 0x40, "LobbyTokenDesk::_keygen");
    static_assert(offsetof(LobbyTokenDesk, _tokenmap) == 0x48, "LobbyTokenDesk::_tokenmap");
    static_assert(offsetof(LobbyTokenDesk, _tokenlist) == 0x68, "LobbyTokenDesk::_tokenlist");
    static_assert(offsetof(LobbyTokenDesk, _lock) == 0x80, "LobbyTokenDesk::_lock");
};
