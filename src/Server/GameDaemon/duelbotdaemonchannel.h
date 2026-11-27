// duelbotdaemonchannel.h: duelbotdaemonchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DuelBotDaemonChannel
{
public:
    virtual __cdecl ~DuelBotDaemonChannel(void);  // 0xa76a0
    void __cdecl Initialize(void);  // 0xa76b0
    bool __cdecl InitSession(void);  // 0xa7730
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0xa7900
protected:
    virtual bool __cdecl onConnect(::Session const *, bool);  // 0xa7990
    virtual void __cdecl onClose(::Session const *, bool, bool);  // 0xa7a40
public:
    bool __cdecl SendPing(void);  // 0xa7b50
    void __cdecl CheckPing(void);  // 0xa7c10
    bool __cdecl IsConnected(void);  // 0xa7cd0
    bool __cdecl SendCreateDuelBotBrain(__int64, int);  // 0xa7d50
    bool __cdecl SendUseSkillFail(::DuelBotCreature *, short, __int64, unsigned int, char);  // 0xa7e00
};

bool __cdecl HandleDuelBotGameGameHelloOk(::Session const *, ::Packet const *);  // 0xa7ee0
bool __cdecl HandleDuelBotGameGameHelloFail(::Session const *, ::Packet const *);  // 0xa7f70
bool __cdecl HandleDuelBotGameGamePingOk(::Session const *, ::Packet const *);  // 0xa7fe0
bool __cdecl HandleDuelBotGameGameCreateDuelBotBrainOk(::Session const *, ::Packet const *);  // 0xa8090
bool __cdecl HandleDuelBotGameGameCreateDuelBotBrainFail(::Session const *, ::Packet const *);  // 0xa8340
bool __cdecl HandleDuelBotGameGameUseSkillReq(::Session const *, ::Packet const *);  // 0xa8630
bool __cdecl HandleDuelBotGameGameUseSkillToGroundReq(::Session const *, ::Packet const *);  // 0xa9020
bool __cdecl HandleDuelBotGameGameMoveReq(::Session const *, ::Packet const *);  // 0xa9a20
bool __cdecl HandleDuelBotGameGameCancelSkillActionReq(::Session const *, ::Packet const *);  // 0xa9e70
bool __cdecl HandleDuelBotGameGameCreatureInfoForMonitoringNotify(::Session const *, ::Packet const *);  // 0xaa1d0
