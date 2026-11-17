// AgentPacketHandler.obj (PostOfficeDaemon PDB).
#pragma once

class Session;
class Packet;

bool HandlePostOfficeHelloReq(Session const* session, Packet const* packet);         // 0x1a6f0
bool HandlePostOfficeRegisterPostReq(Session const* session, Packet const* packet);  // 0x1aaa0
