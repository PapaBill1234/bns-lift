// LobbyToken.obj (LobbyDaemon PDB, 2019 + PDB).
#pragma once
#include "RefCntList.h"

class CliSession;

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

// ❓ The PDB gives the desk layout (0x96c30). Wait for the LobbyTick::Listener base from lift-lobbydaemon-12.
class LobbyTokenDesk
{
public:
    LobbyTokenDesk(long, unsigned long long (__cdecl*)(void));  // 0x96c30
    virtual ~LobbyTokenDesk();  // 0x96d70
    bool Issue(LobbyToken*);  // 0x96e20
    LobbyToken* Verify(int, unsigned long long, unsigned long long, unsigned long, bool&);  // 0x96fb0
    virtual bool Tick(long long);  // 0x97240
};
