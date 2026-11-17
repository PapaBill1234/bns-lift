// LobbyDChannel.obj (LobbyGate PDB). Layouts from include/pdb/LobbyGate/types.h.
#pragma once
#include <stddef.h>
#include "Channel.h"
#include "Lock.h"
#include "StringUtil.h"
#include "ThreadFreePacketPump.h"

class LobbyDSessionHandler;

// PDB: globals of the bypass packet pump. Type 0x2EC3 is an array of 2 pointers (16 bytes) to bool(Session const*, Packet const*).
extern Daemon::PacketHandler bypassHandler[2];
extern Daemon::PacketHandler bypassHandlerFF[2];

class LobbyD : public Channel
{
public:
    virtual ~LobbyD();                  // not in index.tsv for this module
    virtual unsigned long long GetId(); // not in index.tsv for this module

    bool Hello(LobbyDSessionHandler* handler, bool waitAck, unsigned int portId, unsigned long ip, unsigned short port,
               long connectTimeout, bool reconnect);  // 0x9bd0
    bool hello();                                                                              // 0x9d80
    bool SendInitSessionWithNPTokenReq(unsigned long long gateKey, id128 const* npToken, id128 const* portalAccountId,
                                       unsigned int ipAddress);                                  // 0x9e70
    bool SendStartSessionWithNPTokenReq(unsigned long long cliKey, id128 const* npToken, id128 const* portalAccountId,
                                        unsigned int ipAddress);                                 // 0xa280
    bool SendInitSessionWithLobbyTokenReq(unsigned long long gateKey, unsigned long long cliKey,
                                          unsigned long long lobbyToken, unsigned int ipAddress); // 0xa690
    bool SendStartSessionWithLobbyTokenReq(unsigned long long cliKey);                          // 0xa920
    bool SendLostAnonymousConnectionNotify(unsigned long long gateKey);  // 0xab20 (PDB: unsigned __int64)
    bool SendLostConnectionNotify(unsigned long long cliKey);   // 0xad20

    int _state;
    short _wid;
    SystemEvent _helloEvent;
};
static_assert(sizeof(LobbyD) == 0x38, "sizeof LobbyD");

class LobbyDSessionHandler : public SessionHandler
{
public:
    virtual bool OnAccept(Session const* session) const;                        // 0x92a0
    virtual bool OnConnect(Session const* session, bool firstConnected) const;  // 0x9310
    virtual void OnClose(Session const* session, bool tryReconnect) const;      // 0x94c0
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x9660
    virtual ~LobbyDSessionHandler();                                            // not in index.tsv for this module

    static bool isBypassPacket(short cmd);                    // 0x9200
    static short SwitchCmdLobbyDaemonToLobbyGate(short cmd);  // 0x98a0

    void** _lobbydHandlerList;
    void** _lobbydFragmentHandlerList;
    int _lobbydPacketVer;
    CriticalSection _connlock;
};
static_assert(sizeof(LobbyDSessionHandler) == 0x48, "sizeof LobbyDSessionHandler");
