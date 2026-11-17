// LIFT: file. The PDB has no source path for these enums. Names and values are from include/pdb/SmartCouponDaemon/types.h (SmartCouponDaemon PDB).
// Use these names in Send and Decompose calls. Do not write bare command or reason numbers.
#pragma once

enum SmartCouponManagerPacketCommand : int {
    SMARTCOUPONMANAGER_CMD_MIN = 0x1,
    SmartCouponManager_HelloReqCmd = 0x1,
    SmartCouponManager_HelloOkCmd = 0x2,
    SmartCouponManager_HelloFailCmd = 0x3,
    SmartCouponManager_RetryCouponPublicationReqCmd = 0x4,
    SmartCouponManager_RetryCouponPublicationOkCmd = 0x5,
    SmartCouponManager_RetryCouponPublicationFailCmd = 0x6,
    SmartCouponManager_LoadRetryReadyGameEventLogListReqCmd = 0x7,
    SmartCouponManager_LoadRetryReadyGameEventLogListOkCmd = 0x8,
    SmartCouponManager_LoadRetryReadyGameEventLogListFailCmd = 0x9,
    SMARTCOUPONMANAGER_CMD_MAX = 0xA,
};

enum SmartCouponManagerFailReason : int {
    SMARTCOUPONMANAGER_NO_ERROR = 0x0,
    SMARTCOUPONMANAGER_UNKNOWN_ERROR = 0x1,
    SMARTCOUPONMANAGER_SYSTEM_ERROR = 0x2,
    SMARTCOUPONMANAGER_TIMEOUT = 0x3,
    SMARTCOUPONMANAGER_DB_ERROR = 0x4,
    SMARTCOUPONMANAGER_NP_NOT_AVAILABLE = 0x5,
    SMARTCOUPONMANAGER_NP_ERROR = 0x6,
    SMARTCOUPONMANAGER_INVALID_PARAMETER = 0x7,
    SMARTCOUPONMANAGER_HELLOFAIL_DUPLICATION_HELLO_REQ = 0x8,
    SMARTCOUPONMANAGER_HELLOFAIL_INVALID_PACKET_VERSION = 0x9,
    SMARTCOUPONMANAGER_RETRYCOUPONPUBLICATIONFAIL_NO_SUCH_PUBLICATIONID = 0xA,
    SMARTCOUPONMANAGER_GLOBAL_MAX = 0xB,
};
