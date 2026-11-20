// CancelWaitCharacterDeletionJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct CancelWaitCharacterDeletionReqParam;
class CliSession;
struct LobbyJobDef;

class CancelWaitCharacterDeletionJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x18890
    static void* _vtbl();  // 0x188f0
    CancelWaitCharacterDeletionJob(CliSession*);  // 0x18970
    virtual ~CancelWaitCharacterDeletionJob();  // 0x189e0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x188a0
    virtual bool work(int, void*);  // 0x18a80
    bool init(CancelWaitCharacterDeletionReqParam*);  // 0x18b40
    bool restore();  // 0x196f0
    bool restoreCharacterReq();  // 0x19ad0
    bool restoreCharacterOk();  // 0x19f30
    bool restoreCharacterFail(short*);  // 0x1a3b0
    bool restoreCharacterExpire();  // 0x1a860
};
