// LobbyToken.obj (LobbyDaemon PDB, 2019 + PDB).
#include <winsock2.h>
#include <windows.h>
#include <utility>
#include "LobbyToken.h"
#include "CliSession.h"
#include "Daemon.h"
#include "LiftStub.h"
#include "Log.h"

// LIFT: keep until the caller is lifted (0x96750).
#pragma comment(linker, "/INCLUDE:??0LobbyToken@@QEAA@PEAVCliSession@@@Z")

// 0x96750
LobbyToken::LobbyToken(CliSession* clisession) : _tokenkey(0), _clisession(clisession), _expire(0)
{
    if (clisession != nullptr)
        clisession->addReferenceCount(false, L"LobbyToken.cpp", 27);
}

// LIFT: the original emits this body as part of the deleting destructor (0x967d0).
LobbyToken::~LobbyToken()
{
    CliSession* clisession = _clisession;
    if (clisession != nullptr)
        clisession->removeReferenceCount(L"LobbyToken.cpp", 33);
}

// 0x96830
bool LobbyToken::Verify(int, unsigned long long, unsigned long long, unsigned long) const
{
    LIFT_STUB(0x96830);
}

// 0x96b00
void LobbyToken::Expire()
{
    LIFT_STUB(0x96b00);
}

// 0x96c30
LobbyTokenDesk::LobbyTokenDesk(long tokenLifeTime, unsigned long long (__cdecl* keygen)(void))
    : _tokenLifeTime(tokenLifeTime), _keygen(keygen)
{
}

// 0x96d70
LobbyTokenDesk::~LobbyTokenDesk()
{
    LIFT_STUB(0x96d70);
}

// 0x96e20
bool LobbyTokenDesk::Issue(LobbyToken* token)
{
    if (token == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyToken.cpp", 120, L"[token-desk], issue fail; invalid parameter");
        return false;
    }

    token->_tokenkey = _keygen();
    token->_expire = GetTickCount64() - Daemon::Instance->StartSystemTick64 + _tokenLifeTime;

    EnterCriticalSection(&_lock.CS);
    bool ok = _tokenlist.Pushback(token);
    if (ok)
    {
        if (!_tokenmap.insert(std::make_pair(token->_tokenkey, token)).second)
        {
            _tokenlist.Remove(token);
            ok = false;
        }
    }
    LeaveCriticalSection(&_lock.CS);

    if (ok)
        Log::Write(Log::LT_DEBUG, L"LobbyToken.cpp", 146, L"[token-desk], issue token ok, kind:%d, token-key:0x%I64X, cli-key:0x%I64X",
                   token->GetKind(), token->_tokenkey, token->_clisession != nullptr ? token->_clisession->_clikey : 0);
    else
        Log::Write(Log::LT_ERROR, L"LobbyToken.cpp", 148, L"[token-desk], issue token fail, kind:%d, token-key:0x%I64X, cli-key:0x%I64X",
                   token->GetKind(), token->_tokenkey, token->_clisession != nullptr ? token->_clisession->_clikey : 0);
    return ok;
}

// 0x96fb0
LobbyToken* LobbyTokenDesk::Verify(int, unsigned long long, unsigned long long, unsigned long, bool&)
{
    LIFT_STUB(0x96fb0);
}

// 0x97240
bool LobbyTokenDesk::Tick(long long)
{
    LIFT_STUB(0x97240);
}

// 0x967d0 (scalar deleting destructor; the LobbyToken body only)
EnterGameWorldToken::~EnterGameWorldToken()
{
}

// 0xe3ec0
LobbyToken::Kind EnterGameWorldToken::GetKind() const
{
    return TOKEN_ENTER_GAME_WORLD;
}

// 0x967d0 (scalar deleting destructor; the LobbyToken body only)
LeaveGameWorldToken::~LeaveGameWorldToken()
{
}

// 0x99980 (folded with LobbyGatePresence::GetKind)
LobbyToken::Kind LeaveGameWorldToken::GetKind() const
{
    return TOKEN_LEAVE_GAME_WORLD;
}
