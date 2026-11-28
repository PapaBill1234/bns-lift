// logarchivesession.cpp: logarchivesession.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "logarchivesession.h"
#include "../BloodLib/include/Network.h"
#include "../BloodLib/include/Log.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1LogArchiveSession@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Close@LogArchiveSession@@UEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)

static wchar_t const LOG_ARCHIVE_SESSION_FILE[] = L"source\\LogArchiveSession.cpp";

// 0x6b9d00
// LIFT: the destructor calls Close. The compiler inlines it (same line 249 in HR).
__cdecl LogArchiveSession::~LogArchiveSession(void)
{
    Close();
}

// 0x6b9d60
bool __cdecl LogArchiveSession::Connect(unsigned long, unsigned short)
{
    LIFT_STUB(0x6b9d60);
}

// 0x6b9fd0
bool __cdecl LogArchiveSession::Send(::Packet const *)
{
    LIFT_STUB(0x6b9fd0);
}

// 0x6ba1f0
bool __cdecl LogArchiveSession::Recv(::Packet *)
{
    LIFT_STUB(0x6ba1f0);
}

// 0x6ba300
int __cdecl LogArchiveSession::recv(char *, int, int)
{
    LIFT_STUB(0x6ba300);
}

// 0x6ba510
void __cdecl LogArchiveSession::Close(void)
{
    if (_sock != INVALID_SOCKET)
    {
        if (closesocket(_sock) == SOCKET_ERROR)
        {
            // ❓ The text of the format string is not in the HR cache (0x6ba510). The text below is a guess.
            Log::Write(LOG_ARCHIVE_SESSION_FILE, 249, WSAGetLastError(), L"closesocket failed");
        }
        _sock = INVALID_SOCKET;
    }
}
