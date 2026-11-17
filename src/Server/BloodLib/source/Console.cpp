// Console.obj (CacheGate PDB).
#include "Console.h"
#include "Daemon.h"
#include <stdio.h>

// 0x13f50
Console::Console()
{
}

// 0xcd70 (folded with NetworkEndEvent::EventId)
int Console::GetType() const
{
    return 1;
}

// 0x16f50 (folded: empty function)
void Console::Flush()
{
}

// 0x16f50 (folded: empty function; Console vftable slot 13)
void Console::setTitle(wchar_t const* title)
{
}

// 0x139b0
void Console::SetTitle(wchar_t const* def_title)
{
    wchar_t title[1024];
    swprintf(title, 1024, L"%s %s", Daemon::Instance->Descriptions(), Daemon::Instance->VerStr);
    setTitle(title);
}
