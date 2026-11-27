// logarchivecontext.cpp: logarchivecontext.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "logarchivecontext.h"
#include "LiftStub.h"

// 0x6d8430
__cdecl LogArchiveReadBuffer::LogArchiveReadBuffer(void)
{
    LIFT_STUB(0x6d8430);
}

// 0x6d84c0
__cdecl LogArchiveReadBuffer::~LogArchiveReadBuffer(void)
{
    LIFT_STUB(0x6d84c0);
}

// 0x6d84f0
bool __cdecl LogArchiveReadBuffer::ClearBuffer(void)
{
    LIFT_STUB(0x6d84f0);
}

// 0x6d8560
__cdecl LogArchiveWriteBuffer::LogArchiveWriteBuffer(int)
{
    LIFT_STUB(0x6d8560);
}

// 0x6d8650
bool __cdecl LogArchiveWriteBuffer::PushNetworkData(char const *const, unsigned int)
{
    LIFT_STUB(0x6d8650);
}

// 0x6d8860
bool __cdecl LogArchiveWriteBuffer::PushFileData(char const *const, unsigned int)
{
    LIFT_STUB(0x6d8860);
}

// 0x6d89e0
bool __cdecl LogArchiveWriteBuffer::ClearNetworkBuffer(void)
{
    LIFT_STUB(0x6d89e0);
}

// 0x6d8aa0
bool __cdecl LogArchiveWriteBuffer::ClearFileBuffer(void)
{
    LIFT_STUB(0x6d8aa0);
}

// 0x6d8b30
bool __cdecl LogArchiveWriteBuffer::growBufferChunkSize(unsigned int)
{
    LIFT_STUB(0x6d8b30);
}

// 0x6d8ca0
bool __cdecl LogArchiveWriteBuffer::growBufferCount(unsigned int)
{
    LIFT_STUB(0x6d8ca0);
}

// 0x6d8de0
__cdecl LogArchiveWriteContext::LogArchiveWriteContext(int)
{
    LIFT_STUB(0x6d8de0);
}

// 0x6d8e80
__cdecl LogArchiveWriteContext::~LogArchiveWriteContext(void)
{
    LIFT_STUB(0x6d8e80);
}

// 0x6d8f20
bool __cdecl LogArchiveWriteContext::SwitchStatus(void)
{
    LIFT_STUB(0x6d8f20);
}

// 0x6d8fa0
::LogArchiveWriteBuffer *const __cdecl LogArchiveWriteContext::GetWritingBuffer(void) const
{
    LIFT_STUB(0x6d8fa0);
}
