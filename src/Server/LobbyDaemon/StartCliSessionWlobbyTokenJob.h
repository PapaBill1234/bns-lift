// StartCliSessionWlobbyTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class LobbyGateChannel;
struct LobbyJobDef;

class StartCliSessionWlobbyTokenJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x76250
    static void* _vtbl();  // 0x762b0
    bool Initialize(LobbyGateChannel*);  // 0x76380
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x76260
    virtual bool work(int, void*);  // 0x76490
    bool init();  // 0x76550
    bool getGradeLevelReq();  // 0x76720
    bool getGradeLevelResponse(void*);  // 0x76a50
    bool getGradeLevelExpire();  // 0x76f30
    bool listAllGradesReq();  // 0x77050
    bool listAllGradesResponse(void*);  // 0x77340
    bool listAllGradesExpire();  // 0x777f0
    bool start();  // 0x77910
};
