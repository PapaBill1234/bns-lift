// ManagementPacketHandler.obj (PostOfficeDaemon PDB).
#pragma once

class Session;
class Packet;

bool HandlePostOfficeManagementHelloReq(Session const* session, Packet const* packet);                     // 0x97d0
bool HandlePostOfficeManagementResetPostStatusReq(Session const* session, Packet const* packet);           // 0x9950
bool HandlePostOfficeManagementLoadRetryReadySinglePostReq(Session const* session, Packet const* packet);  // 0x9e90
bool HandlePostOfficeManagementResetAllPostStatusReq(Session const* session, Packet const* packet);        // 0xa3d0
bool HandlePostOfficeManagementLoadRetryReadyPostListReq(Session const* session, Packet const* packet);    // 0xa750
