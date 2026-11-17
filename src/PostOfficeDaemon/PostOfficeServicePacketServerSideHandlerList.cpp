// Handler tables for the world sessions (PostOfficeDaemon .data). ❓ file name: the PDB has no module for the tables.
#include "WorldPacketHandler.h"
#include "ThreadFreePacketPump.h"

// 0x97340
TFPP_PacketHandler PostOfficeServicePacketServerSideHandlerList[13] = {
    nullptr, HandlePostOfficeServiceHelloReq, nullptr, nullptr, HandlePostOfficeServiceRetrieveCharacterInfoReq,
    nullptr, nullptr, HandlePostOfficeServiceCheckPostCapacityReq, nullptr, nullptr,
    HandlePostOfficeServiceRegisterPostReq, nullptr, nullptr};

// 0x973b0
TFPP_PacketHandler PostOfficeServicePacketServerSideFragmentHandlerList[13] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    HandlePostOfficeServiceRegisterPostReq, nullptr, nullptr};
