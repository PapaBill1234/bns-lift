// challengepartytran.h: challengepartytran.cpp, challengepartytran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ConfirmInvitationChallengePartyTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x65db0
    __cdecl ConfirmInvitationChallengePartyTran(::User *);  // 0x6fd20
private:
    virtual bool __cdecl work(int, void *);  // 0x6fdf0
    bool __cdecl init(int, void *);  // 0x6fe70
    bool __cdecl abort(short);  // 0x6ff10
    bool __cdecl confirmInvitationChallengeParty(void);  // 0x6ffe0
    bool __cdecl addMember(::ConfirmInvitationChallengePartyOkFromCacheParam *);  // 0x701c0
    bool __cdecl confirmInvitationChallengePartyOkFromCache(void *);  // 0x70400
    bool __cdecl confirmInvitationChallengePartyFailFromCache(void *);  // 0x70590
};

class CreateChallengePartyTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x65da0
private:
    virtual bool __cdecl work(int, void *);  // 0x6f470
    bool __cdecl init(int, void *);  // 0x6f4f0
    bool __cdecl abort(short);  // 0x6f5e0
    bool __cdecl createChallengeParty(void);  // 0x6f6b0
    bool __cdecl createChallengePartyOkFromCache(void *);  // 0x6f7a0
    bool __cdecl createChallengePartyFailFromCache(void *);  // 0x6fb60
};

class LeaveChallengePartyTran
{
public:
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const;  // 0x65dc0
    __cdecl LeaveChallengePartyTran(::User *);  // 0x706d0
    virtual __cdecl ~LeaveChallengePartyTran(void);  // 0x707a0
private:
    virtual bool __cdecl work(int, void *);  // 0x70860
    bool __cdecl init(int &, void *);  // 0x709f0
    bool __cdecl abort(short);  // 0x70b00
    bool __cdecl changeChallengePartyLeaderReq(void);  // 0x70bd0
    bool __cdecl changeLeader(::ChangeChallengePartyLeaderOkFromCacheParam *);  // 0x70cb0
    bool __cdecl changeChallengePartyLeaderOkFromCache(void *);  // 0x70e10
    bool __cdecl leaveChallengePartyReq(void);  // 0x70ee0
    bool __cdecl leaveMember(::LeaveChallengePartyOkFromCacheParam *);  // 0x710a0
    bool __cdecl leaveChallengePartyOkFromCache(void *);  // 0x71280
};

