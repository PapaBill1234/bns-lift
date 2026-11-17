// Channel.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>
#include "RefCntObject.h"

class Session;
class Packet;

class Channel : public DynamicRefCntObj
{
public:
    Channel() : _session(nullptr), _useDelayedRemove(false), _waitForRelease(false) {}  // LIFT: inlined in the callers
    virtual ~Channel();                                                // 0x103C0
    virtual void SetSession(Session const* session);                   // 0x10560 (slot 4)
    virtual void RemoveSession(Session const* session, bool forceNow); // 0x10620 (slot 5)
    virtual Session const* GetSession() const;                         // 0x107D0 (slot 6)
    virtual unsigned long long GetId() = 0;                            // slot 7

    bool MakeSession(unsigned int portId, unsigned long ip, unsigned short portNo, long timeout, bool reconnect);  // 0x10450
    void Close();                                                      // 0x10810
    bool Send(Packet const* packet);                                   // 0x21720 (LobbyGate)
    bool Send(char const* format, ...);                                // 0x216C0 (LobbyGate)

protected:
    static void removeSession(RefCntObject* ref1, RefCntObject* ref2, RefCntObject* ref3);  // 0x10770

public:
    Session* _session;
    bool _useDelayedRemove;
    bool _waitForRelease;

    friend class DelayedRelease;  // LIFT: access for DelayedRelease::Add, LTCG folded the callback
};
static_assert(sizeof(Channel) == 0x28, "sizeof Channel");
static_assert(offsetof(Channel, _session) == 0x18, "Channel::_session");
static_assert(offsetof(Channel, _useDelayedRemove) == 0x20, "Channel::_useDelayedRemove");
static_assert(offsetof(Channel, _waitForRelease) == 0x21, "Channel::_waitForRelease");

// ❓ The PDB does not give a module for SessionHandler. The exe has only the
// vector deleting destructor (0x4040). The empty bodies are a guess.
class SessionHandler
{
public:
    virtual ~SessionHandler() {}
    virtual void OnCreated(Session const* session) const {}
    virtual void OnDestroyed(Session const* session) const {}
    virtual bool OnAccept(Session const* session) const = 0;
    virtual bool OnConnect(Session const* session, bool firstConnected) const = 0;
    virtual void OnClose(Session const* session, bool tryReconnect) const = 0;
    virtual bool PacketHandler(Session const* session, Packet const* packet) const = 0;
};
static_assert(sizeof(SessionHandler) == 0x8, "sizeof SessionHandler");

class DaemonChannel : public SessionHandler
{
public:
    DaemonChannel() : ConnectedSessionCount(0) {}  // LIFT: inlined in the callers
    virtual ~DaemonChannel();                                                    // 0x108A0
    virtual bool OnAccept(Session const* session) const;                         // 0x108B0
    virtual bool OnConnect(Session const* session, bool firstConnected) const;   // 0x108E0
    virtual void OnClose(Session const* session, bool tryReconnect) const;       // 0x10910

protected:
    virtual Session* getSession() = 0;                                           // slot 7
    virtual void releaseSession(Session* session) = 0;                           // slot 8
    virtual bool onAccept(Session const* session) = 0;                           // slot 9
    virtual bool onConnect(Session const* session, bool firstConnected) = 0;     // slot 10
    virtual void onClose(Session const* session, bool tryReconnect, bool closeAll) = 0;  // slot 11 (PDB CacheDChannel::onClose: closeAll)

public:
    // The const methods change the count. The PDB type is int.
    mutable long volatile ConnectedSessionCount;
};
static_assert(sizeof(DaemonChannel) == 0x10, "sizeof DaemonChannel");
static_assert(offsetof(DaemonChannel, ConnectedSessionCount) == 0x8, "DaemonChannel::ConnectedSessionCount");

class ClientSideDaemonChannel : public DaemonChannel
{
public:
    virtual ~ClientSideDaemonChannel();                  // 0x10950

protected:
    virtual Session* getSession();                       // 0x10AD0
    virtual void releaseSession(Session* session);       // 0x10B90
    virtual bool onAccept(Session const* session);       // 0x40B0 (app module, later card)

public:
    unsigned int PortId;
    unsigned long ServerIp;
    unsigned short ServerPort;
    int SessionSize;
    Session** session;
};
static_assert(sizeof(ClientSideDaemonChannel) == 0x28, "sizeof ClientSideDaemonChannel");
static_assert(offsetof(ClientSideDaemonChannel, SessionSize) == 0x1C, "ClientSideDaemonChannel::SessionSize");
static_assert(offsetof(ClientSideDaemonChannel, session) == 0x20, "ClientSideDaemonChannel::session");
