// KickJob.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class GamedChannel;
class LobbyJobTransaction;
class NPGameServiceChannel;
class ObjPool;
class Session;
struct LobbyJobDef;

// LIFT: PDB layout (CliSessionJob base).
class KickJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        KICK = 1,
        WORLD_KICK = 2,
        FIN_CLISESSION = 3,
        KICK_ACK = 4,
        FIN = 5
    };

    enum KickResult
    {
        KR_INVALID = 0,
        KR_OK = 1,
        KR_SYSTEM_ERROR = 2,
        KR_ALREADY_FIN = 3
    };

    // PDB KickJob::Demander (sizeof 8).
    class Demander
    {
    public:
        // LIFT: the original global operator delete(void*) (0x32b50) is empty. KickJob::~KickJob calls the scalar
        // deleting destructor and then Memory::_Manager[2]->Free. This empty class operator delete keeps that shape.
        static void operator delete(void*) {}

        virtual ~Demander() {}  // slot 0
        virtual void Response(int) = 0;  // slot 1
    };

    KickJob(CliSession*, int, Demander*);  // 0x86280
    virtual ~KickJob();  // 0x862f0
    virtual LobbyJobDef const* GetDefinition() const;  // 0x861a0
    static void* _vtbl();  // 0x86200
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x861b0
    virtual bool work(int, void*);  // 0x86380
    bool init(int, void*);  // 0x86460
    bool kick();  // 0x865e0
    bool worldKickReq();  // 0x87010
    bool worldKickOk();  // 0x872e0
    bool worldKickFail(short);  // 0x87420
    bool worldKickExpire();  // 0x87580
    // LIFT: the PDB also has finClisession() and kickAck(). The binary has no body for them (inlined in work).

    int _last;
    int _result;
    int _kickReason;
    Demander* _demander;
    LobbyJobTransaction* _tran;
    GamedChannel* _gamed;

public:
    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(KickJob) == 0x80, "sizeof KickJob");
static_assert(sizeof(KickJob::Demander) == 0x8, "sizeof KickJob::Demander");

// PDB ManageDemander (sizeof 0x18, KickJob::Demander base).
class ManageDemander : public KickJob::Demander
{
public:
    // LIFT: the PDB constructor ManageDemander(Session const*, unsigned long long) has no body. It is inlined in
    // the manage packet handler (KickJob.cpp line 414). It is not declared here until that caller is lifted.
    virtual ~ManageDemander();  // 0x87700 (scalar deleting destructor)
    virtual void Response(int);  // 0x87750

private:
    Session const* _session;
    unsigned long long _tid;
};
static_assert(sizeof(ManageDemander) == 0x18, "sizeof ManageDemander");

// PDB NPDemander (sizeof 0x18, KickJob::Demander base).
class NPDemander : public KickJob::Demander
{
public:
    // LIFT: the PDB constructor NPDemander(NPGameServiceChannel*, unsigned int) has no body. It is inlined in
    // NPLobbyMessageHandler (KickJob.cpp line 374). It is not declared here until that caller is lifted.
    virtual ~NPDemander();  // 0x87670 (scalar deleting destructor)
    virtual void Response(int);  // 0x876c0

private:
    NPGameServiceChannel* _channel;
    unsigned int _txnid;
};
static_assert(sizeof(NPDemander) == 0x18, "sizeof NPDemander");
