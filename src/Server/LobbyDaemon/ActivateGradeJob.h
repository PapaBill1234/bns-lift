// ActivateGradeJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
struct Game_ActivateGradeReqParam;
struct LobbyGate_ActivateGradeReqParam;
struct LobbyJobDef;

class ActivateGradeJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0xbac0
    static void* _vtbl();  // 0xbb20
    ActivateGradeJob(CliSession*);  // 0xbba0
    virtual ~ActivateGradeJob();  // 0xbc00
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0xbad0
    virtual bool work(int, void*);  // 0xbc70
    bool initFromLobbyGate(LobbyGate_ActivateGradeReqParam*);  // 0xbd00
    bool initFromGame(Game_ActivateGradeReqParam*);  // 0xc1a0
    bool activateGradeReq();  // 0xc670
    bool activateGradeResponse(void*);  // 0xca10
    bool activateGradeExpire();  // 0xcf50
    void sendFail(int);  // 0xd0a0
};
