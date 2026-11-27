// logarchivefilemanager.h: logarchivefilemanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class LogArchiveFileContext
{
protected:
    __cdecl ~LogArchiveFileContext(void);  // 0x6bb2a0
    bool __cdecl AllocWriteContext(void);  // 0x6bb310
    bool __cdecl DeallocWriteContext(void);  // 0x6bb410
};

class LogArchiveFileManager
{
public:
    __cdecl LogArchiveFileManager(void);  // 0x6bb4a0
    bool __cdecl Initialize(wchar_t const *const, unsigned int, unsigned int);  // 0x6bb560
    void __cdecl CloseAllFiles(void);  // 0x6bb640
    bool __cdecl WriteToFile(::LogArchiveFileContext *const);  // 0x6bb740
    bool __cdecl ConvertNetDataToFileData(::LogArchiveWriteContext const *const);  // 0x6bb950
    bool __cdecl PushWriteData(int, char const *const, unsigned int);  // 0x6bbc70
    bool __cdecl IsWritting(int);  // 0x6bbea0
    bool __cdecl SetEvent(int, void *);  // 0x6bbfb0
    void * __cdecl GetEvent(int);  // 0x6bc0a0
    bool __cdecl Write(int);  // 0x6bc160
    bool __cdecl WriteComplete(int);  // 0x6bc2c0
    void __cdecl Flush(void);  // 0x6bc4f0
protected:
    bool __cdecl waitComplete(::LogArchiveFileContext const *const);  // 0x6bc5b0
    bool __cdecl createUnsentFile(::LogArchiveFileContext *const);  // 0x6bc7d0
    bool __cdecl closeUnsentFile(::LogArchiveFileContext *const);  // 0x6bcb20
    bool __cdecl checkFileSplit(::LogArchiveFileContext const *const);  // 0x6bcc40
    bool __cdecl splitUnsentFile(::LogArchiveFileContext *const);  // 0x6bccc0
    bool __cdecl checkFileSplitBySize(::LogArchiveFileContext const *const);  // 0x6bcd40
    bool __cdecl checkFileSplitByTime(::LogArchiveFileContext const *const);  // 0x6bcdd0
};

