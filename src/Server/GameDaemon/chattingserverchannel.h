// chattingserverchannel.h: chattingserverchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ChattingServerChannel
{
public:
    virtual __cdecl ~ChattingServerChannel(void);  // 0x76ca0
    bool __cdecl InitSession(void);  // 0x76cb0
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x76df0
protected:
    virtual bool __cdecl onConnect(::Session const *, bool);  // 0x76e80
    virtual void __cdecl onClose(::Session const *, bool, bool);  // 0x76f10
public:
    void __cdecl SendServerId(::Session const *);  // 0x776e0
    void __cdecl SendAuthenticateUserResult(__int64, wchar_t const *, int, __int64, __int64, __int64, int, int);  // 0x77840
    void __cdecl SendChattingAvailable(::Pc *);  // 0x779f0
    void __cdecl SendAuthenticateGuildResult(wchar_t const *, __int64, __int64, int, int);  // 0x77a50
};

bool __cdecl HandleChattingGame_A2G_AUTHENTICATE_USERNotify(::Session const *, ::Packet const *);  // 0x77050
bool __cdecl HandleChattingGame_A2G_PROTOCOL_VERSIONNotify(::Session const *, ::Packet const *);  // 0x77250
bool __cdecl HandleChattingGame_A2G_AUTHENTICATE_GUILDNotify(::Session const *, ::Packet const *);  // 0x772a0
