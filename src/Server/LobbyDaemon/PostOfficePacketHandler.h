// PostOfficePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class Packet;
class Session;

bool HandlePostOfficeHelloOk(Session const*, Packet const*);  // 0x646f0
bool HandlePostOfficeHelloFail(Session const*, Packet const*);  // 0x64740
bool HandlePostOfficeRegisterPostOk(Session const*, Packet const*);  // 0x647f0
bool HandlePostOfficeRegisterPostFail(Session const*, Packet const*);  // 0x64a20
