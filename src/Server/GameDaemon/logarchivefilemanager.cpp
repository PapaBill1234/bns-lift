// logarchivefilemanager.cpp: logarchivefilemanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "logarchivefilemanager.h"
#include "logarchivecontext.h"
#include "LiftStub.h"

// 0x6bb2a0
__cdecl LogArchiveFileContext::~LogArchiveFileContext(void)
{
    LIFT_STUB(0x6bb2a0);
}

// 0x6bb310
bool __cdecl LogArchiveFileContext::AllocWriteContext(void)
{
    LIFT_STUB(0x6bb310);
}

// 0x6bb410
bool __cdecl LogArchiveFileContext::DeallocWriteContext(void)
{
    LIFT_STUB(0x6bb410);
}

// 0x6bb4a0
__cdecl LogArchiveFileManager::LogArchiveFileManager(void)
{
    LIFT_STUB(0x6bb4a0);
}

// 0x6bb560
bool __cdecl LogArchiveFileManager::Initialize(wchar_t const *const, unsigned int, unsigned int)
{
    LIFT_STUB(0x6bb560);
}

// 0x6bb640
void __cdecl LogArchiveFileManager::CloseAllFiles(void)
{
    LIFT_STUB(0x6bb640);
}

// 0x6bb740
bool __cdecl LogArchiveFileManager::WriteToFile(::LogArchiveFileContext *const)
{
    LIFT_STUB(0x6bb740);
}

// 0x6bb950
bool __cdecl LogArchiveFileManager::ConvertNetDataToFileData(::LogArchiveWriteContext const *const)
{
    LIFT_STUB(0x6bb950);
}

// 0x6bbc70
bool __cdecl LogArchiveFileManager::PushWriteData(int, char const *const, unsigned int)
{
    LIFT_STUB(0x6bbc70);
}

// 0x6bbea0
bool __cdecl LogArchiveFileManager::IsWritting(int)
{
    LIFT_STUB(0x6bbea0);
}

// 0x6bbfb0
bool __cdecl LogArchiveFileManager::SetEvent(int, void *)
{
    LIFT_STUB(0x6bbfb0);
}

// 0x6bc0a0
void * __cdecl LogArchiveFileManager::GetEvent(int)
{
    LIFT_STUB(0x6bc0a0);
}

// 0x6bc160
bool __cdecl LogArchiveFileManager::Write(int)
{
    LIFT_STUB(0x6bc160);
}

// 0x6bc2c0
bool __cdecl LogArchiveFileManager::WriteComplete(int)
{
    LIFT_STUB(0x6bc2c0);
}

// 0x6bc4f0
void __cdecl LogArchiveFileManager::Flush(void)
{
    LIFT_STUB(0x6bc4f0);
}

// 0x6bc5b0
bool __cdecl LogArchiveFileManager::waitComplete(::LogArchiveFileContext const *const)
{
    LIFT_STUB(0x6bc5b0);
}

// 0x6bc7d0
bool __cdecl LogArchiveFileManager::createUnsentFile(::LogArchiveFileContext *const)
{
    LIFT_STUB(0x6bc7d0);
}

// 0x6bcb20
bool __cdecl LogArchiveFileManager::closeUnsentFile(::LogArchiveFileContext *const)
{
    LIFT_STUB(0x6bcb20);
}

// 0x6bcc40
bool __cdecl LogArchiveFileManager::checkFileSplit(::LogArchiveFileContext const *const)
{
    LIFT_STUB(0x6bcc40);
}

// 0x6bccc0
bool __cdecl LogArchiveFileManager::splitUnsentFile(::LogArchiveFileContext *const)
{
    LIFT_STUB(0x6bccc0);
}

// 0x6bcd40
bool __cdecl LogArchiveFileManager::checkFileSplitBySize(::LogArchiveFileContext const *const)
{
    LIFT_STUB(0x6bcd40);
}

// 0x6bcdd0
bool __cdecl LogArchiveFileManager::checkFileSplitByTime(::LogArchiveFileContext const *const)
{
    LIFT_STUB(0x6bcdd0);
}
