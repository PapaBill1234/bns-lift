// ManagementSessionHandler.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include "Channel.h"

class Session;
class Packet;

class ManagementSessionHandler : public SessionHandler
{
public:
    virtual ~ManagementSessionHandler();
    virtual bool OnAccept(Session const* session) const;                             // 0x10be0
    virtual bool OnConnect(Session const* session, bool firstConnected) const;       // 0x10c40
    virtual void OnClose(Session const* session, bool tryReconnect) const;           // 0x10ca0
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x10d00

    // LIFT: not in PDB: the inlined text reply (ComposeText "ss", encrypt, send under the session lock).
    static void SendTextReply(Session const* session, Packet* reply, wchar_t const* text1, wchar_t const* text2);
};
static_assert(sizeof(ManagementSessionHandler) == 0x8, "sizeof ManagementSessionHandler");

// PostOfficeManagementPacketHandlerList (data only).
typedef bool (*ManagementPacketHandlerFunc)(Session const* session, Packet const* packet);  // ❓ typedef name
extern wchar_t const* PostOfficeManagementCommandList[16];
extern ManagementPacketHandlerFunc PostOfficeManagementPacketServerSideHandlerList[16];
