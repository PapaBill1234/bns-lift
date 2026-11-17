// LIFT: file. The PDB has no source path for these enums. Names and values are from include/pdb/PostOfficeDaemon/types.h (PostOfficeDaemon PDB).
// Use these names in Send and Decompose calls. Do not write bare command or reason numbers.
#pragma once

enum PostOfficePacketCommand : int {
    PostOffice_HelloReqCmd = 0x1,
    PostOffice_HelloOkCmd = 0x2,
    PostOffice_HelloFailCmd = 0x3,
    PostOffice_RegisterPostReqCmd = 0x4,
    PostOffice_RegisterPostOkCmd = 0x5,
    PostOffice_RegisterPostFailCmd = 0x6,
    POSTOFFICE_CMD_MAX = 0x7,
};

enum PostOfficeFailReason : int {
    POSTOFFICE_NO_ERROR = 0x0,
    POSTOFFICE_UNKNOWN_ERROR = 0x1,
    POSTOFFICE_SYSTEM_ERROR = 0x2,
    POSTOFFICE_DB_ERROR = 0x3,
    POSTOFFICE_HELLOFAIL_INVALID_CONNECTION_TYPE = 0x4,
    POSTOFFICE_HELLOFAIL_INVALID_PACKET_VERSION = 0x5,
    POSTOFFICE_REGISTERPOSTFAIL_INVALID_POST_DATA = 0x6,
    POSTOFFICE_REGISTERPOSTFAIL_INVALID_ITEM_DATA = 0x7,
    POSTOFFICE_REGISTERPOSTFAIL_INVALID_MONEY_ITEM_DATA = 0x8,
    POSTOFFICE_REGISTERPOSTFAIL_INVALID_DEFAULT_ITEM_DATA = 0x9,
    POSTOFFICE_REGISTERPOSTFAIL_INVALID_CUSTOM_ITEM_DATA = 0xA,
    POSTOFFICE_REGISTERPOSTFAIL_NO_SUCH_ITEM_TYPE = 0xB,
    POSTOFFICE_REGISTERPOSTFAIL_DUPLICATED_INVOICE_ID = 0xC,
    POSTOFFICE_GLOBAL_MAX = 0xD,
};
