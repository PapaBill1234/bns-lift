// Handler tables for the agent sessions (PostOfficeDaemon .data). ❓ file name: the PDB has no module for the tables.
#include "AgentPacketHandler.h"
#include "ThreadFreePacketPump.h"

// 0x97268
TFPP_PacketHandler PostOfficePacketServerSideHandlerList[7] = {
    nullptr, HandlePostOfficeHelloReq, nullptr, nullptr, HandlePostOfficeRegisterPostReq, nullptr, nullptr};

// 0x97308
TFPP_PacketHandler PostOfficePacketServerSideFragmentHandlerList[7] = {
    nullptr, nullptr, nullptr, nullptr, HandlePostOfficeRegisterPostReq, nullptr, nullptr};
