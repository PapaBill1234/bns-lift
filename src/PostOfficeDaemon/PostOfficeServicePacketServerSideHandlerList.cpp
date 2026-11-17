// Handler tables for the world sessions (PostOfficeDaemon .data). LIFT: file name. The PDB has no module for the tables.
#include "WorldPacketHandler.h"
#include "ThreadFreePacketPump.h"

// 0x97340
Daemon::PacketHandler PostOfficeServicePacketServerSideHandlerList[13] = {
    nullptr, HandlePostOfficeServiceHelloReq, nullptr, nullptr, HandlePostOfficeServiceRetrieveCharacterInfoReq,
    nullptr, nullptr, HandlePostOfficeServiceCheckPostCapacityReq, nullptr, nullptr,
    HandlePostOfficeServiceRegisterPostReq, nullptr, nullptr};

// 0x973b0
Daemon::PacketHandler PostOfficeServicePacketServerSideFragmentHandlerList[13] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    HandlePostOfficeServiceRegisterPostReq, nullptr, nullptr};
