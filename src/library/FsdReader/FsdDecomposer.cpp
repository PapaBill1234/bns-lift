// FsdDecomposer.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "FsdDecomposer.h"
#include "LiftStub.h"

// 0x119c10
bool FsdDecomposer::Decompose()
{
    LIFT_STUB(0x119c10);
}

// 0x119d00
bool FsdDecomposer::GetByte(char*)
{
    LIFT_STUB(0x119d00);
}

// 0x119dd0
bool FsdDecomposer::GetWord(short*)
{
    LIFT_STUB(0x119dd0);
}

// 0x119ea0
bool FsdDecomposer::GetDword(int*)
{
    LIFT_STUB(0x119ea0);
}

// 0x119f70
bool FsdDecomposer::GetQword(long long*)
{
    LIFT_STUB(0x119f70);
}

// 0x11a040
int FsdDecomposer::GetString(wchar_t*, int)
{
    LIFT_STUB(0x11a040);
}
