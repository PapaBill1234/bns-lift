// datareader.cpp: datareader.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "datareader.h"
#include "LiftStub.h"

// 0x6eb2a0
wchar_t const * __cdecl GetDataReaderInterfaceVersion(void)
{
    LIFT_STUB(0x6eb2a0);
}

// 0x6eb2b0
bool __cdecl SetupDataReader(long, ::DrLog *, ::DrMemory *, ::DrMemory *)
{
    LIFT_STUB(0x6eb2b0);
}

// 0x6eb2c0
void __cdecl CloseDataReader(void)
{
    LIFT_STUB(0x6eb2c0);
}

// 0x6eb2d0
::DrDataReader * __cdecl CreateDataReader(void)
{
    LIFT_STUB(0x6eb2d0);
}

// 0x6eb320
::DrLog * __cdecl Logger(void)
{
    LIFT_STUB(0x6eb320);
}

// 0x6eb330
void __cdecl ReleaseDataReader(::DrDataReader *&)
{
    LIFT_STUB(0x6eb330);
}
