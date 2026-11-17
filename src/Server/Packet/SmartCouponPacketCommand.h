// LIFT: file. The PDB has no source path for these enums. Names and values are from include/pdb/SmartCouponDaemon/types.h (SmartCouponDaemon PDB).
// Use these names in Send and Decompose calls. Do not write bare command or reason numbers.
#pragma once

enum SmartCouponMainPacketCommand : int {
    SMARTCOUPON_CMD_MIN = 0x1,
    SmartCoupon_HelloReqCmd = 0x1,
    SmartCoupon_HelloOkCmd = 0x2,
    SmartCoupon_HelloFailCmd = 0x3,
    SmartCoupon_GameEventByCharacterReqCmd = 0x4,
    SmartCoupon_GameEventByCharacterOkCmd = 0x5,
    SmartCoupon_GameEventByCharacterFailCmd = 0x6,
    SmartCoupon_GameEventByAccountReqCmd = 0x7,
    SmartCoupon_GameEventByAccountOkCmd = 0x8,
    SmartCoupon_GameEventByAccountFailCmd = 0x9,
    SMARTCOUPON_CMD_MAX = 0xA,
};

enum SmartCouponFailReason : int {
    SMARTCOUPON_NO_ERROR = 0x0,
    SMARTCOUPON_UNKNOWN_ERROR = 0x1,
    SMARTCOUPON_SYSTEM_ERROR = 0x2,
    SMARTCOUPON_TIMEOUT = 0x3,
    SMARTCOUPON_NP_ERROR = 0x4,
    SMARTCOUPON_NP_NOT_AVAILABLE = 0x5,
    SMARTCOUPON_DB_ERROR = 0x6,
    SMARTCOUPON_INVALID_PARAMETER = 0x7,
    SMARTCOUPON_SERVICE_NOT_AVAILABLE = 0x8,
    SMARTCOUPON_HELLOFAIL_INVALID_PACKET_VERSION = 0x9,
    SMARTCOUPON_HELLOFAIL_NOT_CONFIGURED = 0xA,
    SMARTCOUPON_HELLOFAIL_IP_ADDRESS_MISMATCH = 0xB,
    SMARTCOUPON_HELLOFAIL_PORT_MISMATCH = 0xC,
    SMARTCOUPON_HELLOFAIL_DUPLICATED_WORLD = 0xD,
    SMARTCOUPON_HELLOFAIL_DAEMON_TYPE_MISMATCH = 0xE,
    SMARTCOUPON_GAMEEVENTFAIL_FAIL = 0xF,
    SMARTCOUPON_GLOBAL_MAX = 0x10,
};
