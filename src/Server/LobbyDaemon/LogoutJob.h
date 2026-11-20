// LogoutJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class LobbyGateChannel;
struct LobbyJobDef;

class LogoutJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x97a10
    static void* _vtbl();  // 0x97a70
    LogoutJob(CliSession*, LobbyGateChannel*, bool);  // 0x97af0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x97a20
    virtual bool work(int, void*);  // 0x97bb0
    bool init(int, void*);  // 0x97bf0
    bool logout();  // 0x97d30
};
