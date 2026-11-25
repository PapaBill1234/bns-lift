// NPLobbyMessageHandler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class NPChannel;
class NPTransaction;
namespace StsMsgLib
{
struct _StsMsg;
}

// 0xcb710 PDB type 0x7837. NPServiceChannelManager::HandleMessage (0xd0100) calls it.
bool (*DispatchNPLobbyMessageHandler(int cmd))(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);

// 0xcd5e0 PDB type 0x4E6C. DispatchNPLobbyMessageHandler (0xcb710) returns it for command 2904.
bool Handle_SrvCharge_RequestStop(NPChannel* channel, StsMsgLib::_StsMsg* msg, NPTransaction* transaction);
