// RecoverPcJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class Character;
class CliSession;
class LobbyGateChannel;
struct LobbyJobDef;
union id128;

class RecoverPcJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x64e50
    static void* _vtbl();  // 0x64eb0
    RecoverPcJob(CliSession*);  // 0x64f30
    virtual ~RecoverPcJob();  // 0x64fa0
    bool Initialize(LobbyGateChannel*, id128 const&);  // 0x65040
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x64e60
    virtual bool work(int, void*);  // 0x65260
    bool init();  // 0x652f0
    bool restoreGameWorldPcReq();  // 0x65b40
    bool restoreGameWorldPcOk();  // 0x65d30
    bool restoreGameWorldPcFail(short*);  // 0x66070
    bool restoreGameWorldPcExpired();  // 0x664f0
    bool __restoreStuckPc(Character*, short&);  // 0x66600
};
