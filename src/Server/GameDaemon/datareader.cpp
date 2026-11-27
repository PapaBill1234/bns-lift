// datareader.cpp: datareader.cpp (GameDaemon PDB, 2019 + PDB).
#include "datareader.h"
#include "datareaderimpl.h"
#include "LiftStub.h"

// LIFT: keep the lifted functions until the callers are lifted (the callers are stubs; /OPT:REF drops them). Card lift-gamedaemon-gap-005-e5.
#pragma comment(linker, "/INCLUDE:?GetDataReaderInterfaceVersion@@YAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Logger@@YAPEAVDrLog@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x6eb2a0
wchar_t const * __cdecl GetDataReaderInterfaceVersion(void)
{
    return L"34";
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
    return DrDataReaderImpl::_logger;
}

// 0x6eb330
void __cdecl ReleaseDataReader(::DrDataReader *&)
{
    LIFT_STUB(0x6eb330);
}

// LIFT: definition of the PDB static data member DrDataReaderImpl::_logger (set by DrDataReaderImpl::Setup, a later card).
::DrLog * DrDataReaderImpl::_logger;
