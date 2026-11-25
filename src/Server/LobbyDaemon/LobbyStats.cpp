// LobbyStats.obj (LobbyDaemon 2019 + PDB).
#include "LobbyStats.h"
#include "Daemon.h"
#include "LiftStub.h"
#include "Log.h"
#include <shlobj.h>

#pragma comment(linker, "/INCLUDE:?Initialize@LobbyStats@@QEAA_NPEB_W00J@Z")  // LIFT: keep until the caller is lifted (0x5a0b0).
#pragma comment(linker, "/INCLUDE:?HandleEvent@LobbyStats@@UEAA_NPEAUEventContext@@K@Z")  // LIFT: keep until the caller is lifted (0x5a1d0).

// 0x5a0b0. LTCG folds fname and fext to L"lobby" and L"stats" at the original call site.
bool LobbyStats::Initialize(wchar_t const* dir, wchar_t const* fname, wchar_t const* fext, long period)
{
    if (dir == nullptr || period == 0 || wcslen(dir) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyStats.cpp", 35, L"[stats], init fail; invalid parameter");
        return false;
    }

    // BUG: 0x5a111. The original tests GetLastError, not the return code from SHCreateDirectoryExW.
    if (SHCreateDirectoryExW(nullptr, dir, nullptr) != ERROR_SUCCESS)
    {
        long error = GetLastError();
        if (error != ERROR_ALREADY_EXISTS)
        {
            Log::Write(L"LobbyStats.cpp", 42, error, L"[stats], init fail; create directory fail");
            return false;
        }
    }
    wcscpy_s(_dir, 260, dir);
    wcscpy_s(_fname, 260, fname);
    wcscpy_s(_fext, 260, fext);
    _period = period;
    return true;
}

// LIFT: no LD RVA. LTCG inlines it in LobbyDaemon::onStart (0x9dca0). Log line 58 is from the inlined copy.
bool LobbyStats::Start()
{
    if (_run)
    {
        Log::Write(Log::LT_ERROR, L"LobbyStats.cpp", 58, L"[stats], start fail; already run");
        return false;
    }
    _run = true;
    Daemon::Instance->AddTimer(_period, this);
    return true;
}

// 0x5a1d0
bool LobbyStats::HandleEvent(EventContext*, unsigned long)
{
    if (_run)
    {
        update();
        Daemon::Instance->AddTimer(_period, this);
    }
    return true;
}

// 0x5a210
// LIFT: Not done. It needs the LobbyDaemon, GameWorldRegistry, GameWorldCluster and GameWorld (lift-lobbydaemon-9) layouts (0x5a210).
bool LobbyStats::update()
{
    LIFT_STUB(0x5a210);
}
