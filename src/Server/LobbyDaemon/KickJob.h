// KickJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class KickJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x861a0
    static void* _vtbl();  // 0x86200
    virtual ~KickJob();  // 0x862f0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x861b0
    virtual bool work(int, void*);  // 0x86380
    bool init(int, void*);  // 0x86460
    bool kick();  // 0x865e0
    bool worldKickReq();  // 0x87010
    bool worldKickOk();  // 0x872e0
    bool worldKickFail(short);  // 0x87420
    bool worldKickExpire();  // 0x87580
};

class ManageDemander
{
public:
    virtual void Response(int);  // 0x87750
};

class NPDemander
{
public:
    virtual void Response(int);  // 0x876c0
};
