// PostOfficeManagementPacketHandlerList (PostOfficeDaemon .data). Data tables only.
#include "ManagementPacketHandler.h"
#include "ManagementSessionHandler.h"

// 0x97420
wchar_t const* PostOfficeManagementCommandList[16] = {
    nullptr,
    L"Hello",
    L"HelloOk",
    L"HelloFail",
    L"ResetPostStatus",
    L"ResetPostStatusOk",
    L"ResetPostStatusFail",
    L"LoadRetryReadySinglePost",
    L"LoadRetryReadySinglePostOk",
    L"LoadRetryReadySinglePostFail",
    L"ResetAllPostStatus",
    L"ResetAllPostStatusOk",
    L"ResetAllPostStatusFail",
    L"LoadRetryReadyPostList",
    L"LoadRetryReadyPostListOk",
    L"LoadRetryReadyPostListFail",
};

// 0x974a0
ManagementPacketHandlerFunc PostOfficeManagementPacketServerSideHandlerList[16] = {
    nullptr,
    HandlePostOfficeManagementHelloReq,
    nullptr,
    nullptr,
    HandlePostOfficeManagementResetPostStatusReq,
    nullptr,
    nullptr,
    HandlePostOfficeManagementLoadRetryReadySinglePostReq,
    nullptr,
    nullptr,
    HandlePostOfficeManagementResetAllPostStatusReq,
    nullptr,
    nullptr,
    HandlePostOfficeManagementLoadRetryReadyPostListReq,
    nullptr,
    nullptr,
};
