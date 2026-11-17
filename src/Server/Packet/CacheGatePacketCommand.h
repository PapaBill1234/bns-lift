// LIFT: file. The PDB has no source path for these enums. Names and values are from include/pdb/CacheGate/types.h (CacheGate PDB).
// Use these names in Send and Decompose calls. Do not write bare command or reason numbers.
#pragma once

enum CacheGatePacketCommand : int {
    CacheGate_HelloCmd = 0x1,
    CacheGate_HelloOkCmd = 0x2,
    CacheGate_HelloFailCmd = 0x3,
    CacheGate_RelayCmd = 0x4,
    CacheGate_RelayFailCmd = 0x5,
    CacheGate_RelayInvalidCmd = 0x6,
    CacheGate_TheOtherSideListReqCmd = 0x7,
    CacheGate_TheOtherSideListAckCmd = 0x8,
    CacheGate_FragmentRelayCmd = 0x9,
    CACHEGATE_CMD_MAX = 0xA,
};

enum CacheGateFailReason : int {
    CACHEGATE_NO_ERROR = 0x0,
    CACHEGATE_UNKNOWN_ERROR = 0x1,
    CACHEGATE_SYSTEM_ERROR = 0x2,
    CACHEGATE_SERVICE_NOT_AVAILABLE = 0x3,
    CACHEGATE_HELLOFAIL_INVALID_PARAMETER = 0x4,
    CACHEGATE_HELLOFAIL_INVALID_PACKET_VERSION = 0x5,
    CACHEGATE_HELLOFAIL_INVALID_WORLD_ID = 0x6,
    CACHEGATE_HELLOFAIL_DUPLICATE_SERVER_ID = 0x7,
    CACHEGATE_RELAYFAIL_CAN_NOT_FIND_DESTINATION = 0x8,
    CACHEGATE_RELAYFAIL_INVALID_CONNECTION = 0x9,
    CACHEGATE_RELAYINVALID_INCORRECT_TO_WID = 0xA,
    CACHEGATE_RELAYINVALID_INCORRECT_DATA_COMMAND = 0xB,
    CACHEGATE_GLOBAL_MAX = 0xC,
};
