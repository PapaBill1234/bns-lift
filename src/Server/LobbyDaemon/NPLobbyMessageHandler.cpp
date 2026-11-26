// NPLobbyMessageHandler.obj (LobbyDaemon PDB, 2019 + PDB). Logic from the 2019 + PDB pseudocode.
// Source file "NPLobbyMessageHandler.cpp" (log strings).
#include <windows.h>
#include <stddef.h>
#include <string.h>
#include <wchar.h>
#include "NPLobbyMessageHandler.h"
#include "NPServiceChannel.h"
#include "CliSession.h"
#include "CliSessionManager.h"
#include "CliSessionTable.h"
#include "LiftStub.h"
#include "LobbyConfig.h"
#include "LobbyDaemon.h"
#include "LobbyJob.h"
#include "Log.h"
#include "StringUtil.h"

// PDB public LobbyErrorDesc (28 entries). LobbyGamePacketHandler.cpp has the definition.
extern wchar_t const* LobbyErrorDesc[28];

namespace StsMsgLib
{
// LIFT: StsMsgGrade.h and AuctionEscrow.h define their own _StsMsg. They conflict with NPChannelBase.h.
// So this file has local copies of the message layouts that it reads. Layouts from tools/pdbcls.py LobbyDaemon.
struct _StsMsgInfoNotify : public _StsMsgInfo
{
};

struct _StsMsgNotify : public _StsMsg
{
    _StsMsgInfoNotify msgInfo;
};
static_assert(sizeof(_StsMsgNotify) == 0x10, "sizeof StsMsgLib::_StsMsgNotify");

// PDB 0x3975 (size 0x48).
struct _StsMsgNotifyPresenceUserInfo : public _StsMsgNotify
{
    _GUID guidPortalAccountId;
    unsigned int nDataCenter;
    wchar_t* pwszUserName;
    int userStatus;  // LIFT: PDB type StsMsgLib::EUserStatus (4 bytes). Only the log reads it.
    wchar_t* pwszAlias;
    void* externalAccount;  // LIFT: PDB type StsMsgLib::_ExternalAccount*. Not read here.
};
static_assert(sizeof(_StsMsgNotifyPresenceUserInfo) == 0x48, "sizeof _StsMsgNotifyPresenceUserInfo");
static_assert(offsetof(_StsMsgNotifyPresenceUserInfo, pwszUserName) == 0x28, "pwszUserName");
static_assert(offsetof(_StsMsgNotifyPresenceUserInfo, pwszAlias) == 0x38, "pwszAlias");

// PDB 0x34C6 (size 0xB8).
struct _StsMsgNotifyChargeNotifyApplyNewItem : public _StsMsgNotify
{
    _GUID UserId;
    unsigned int nRemainPlayTime;
    unsigned int nReservations;
    unsigned int nItemId;
    unsigned int nComputationBasis;
    wchar_t ChargeKey[68];
};
static_assert(sizeof(_StsMsgNotifyChargeNotifyApplyNewItem) == 0xB8, "sizeof _StsMsgNotifyChargeNotifyApplyNewItem");
static_assert(offsetof(_StsMsgNotifyChargeNotifyApplyNewItem, ChargeKey) == 0x30, "ChargeKey");

// PDB 0x3C95 (size 0x30).
struct _StsMsgNotifyChargeNotifyRemainTime : public _StsMsgNotify
{
    _GUID UserId;
    unsigned int nRemainPlayTime;
    unsigned int nReservations;
    unsigned int nItemId;
    unsigned int nComputationBasis;
};
static_assert(sizeof(_StsMsgNotifyChargeNotifyRemainTime) == 0x30, "sizeof _StsMsgNotifyChargeNotifyRemainTime");

// Copy of StsMsgGrade.h (size 0xC8).
struct _StsMsgNotifyGradeNotifyGradeChanged : public _StsMsgNotify
{
    _GUID UserId;
    int nGradeId;
    wchar_t AppGroupCode[9];
    wchar_t GameGradeKey[51];
    bool bActivation;
    int nGradeCount;
    long long tTotalEffectiveFrom;
    long long tTotalEffectiveTo;
    int nRemainingGradeTimePerSecond;
    wchar_t* pwszReason;
};
static_assert(sizeof(_StsMsgNotifyGradeNotifyGradeChanged) == 0xC8, "sizeof _StsMsgNotifyGradeNotifyGradeChanged");
static_assert(offsetof(_StsMsgNotifyGradeNotifyGradeChanged, bActivation) == 0x9C, "bActivation");
static_assert(offsetof(_StsMsgNotifyGradeNotifyGradeChanged, pwszReason) == 0xC0, "pwszReason");

// Copy of StsMsgGrade.h (size 0x48).
struct _StsMsgNotifyGradeNotifyScoreChanged : public _StsMsgNotify
{
    struct _Grade
    {
        int nGradeId;
        wchar_t AppGroupCode[9];
        wchar_t GameGradeKey[51];
    };
    _GUID UserId;
    int nRelatedGradesCount;
    _Grade* pRelatedGrades;
    bool bLevelChanged;
    int nLevelId;
    int nAccumulateGradeScore;
    int nMinimumLevelScore;
    int nMaximumLevelScore;
    int nMaximumGradeScore;
};
static_assert(sizeof(_StsMsgNotifyGradeNotifyScoreChanged) == 0x48, "sizeof _StsMsgNotifyGradeNotifyScoreChanged");
static_assert(offsetof(_StsMsgNotifyGradeNotifyScoreChanged, nLevelId) == 0x34, "nLevelId");
}  // namespace StsMsgLib

using namespace StsMsgLib;

namespace
{
wchar_t const NPLOBBYMESSAGEHANDLER_FILE[] = L"NPLobbyMessageHandler.cpp";

// LIFT: the messages hold _GUID (PDB). The session table takes id128.
inline id128 npUserId(_GUID const& guid)
{
    return *reinterpret_cast<id128 const*>(&guid);
}

inline wchar_t const* npReason(_StsMsgResponse const* res)
{
    return res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null";
}

// The request reason, or L"unknown" when it is null or empty.
inline wchar_t const* npReqReason(wchar_t const* reason)
{
    if (reason == nullptr || wcslen(reason) == 0)
        return L"unknown";
    return reason;
}

inline wchar_t const* npLobbyErrorDesc()
{
    unsigned int error = static_cast<unsigned int>(TLobbyError);
    return error >= 28 ? L"LOBERR_UNDEFINED" : LobbyErrorDesc[error];
}

// status 200, or status 400 with reason "Success".
inline bool npIsSuccess(_StsMsgResponse const* res)
{
    if (res->msgInfo.errInfo.nStatusCode == 200)
        return true;
    return res->msgInfo.errInfo.nStatusCode == 400 && _wcsicmp(L"Success", npReason(res)) == 0;
}
}  // namespace

#define NPLMH_GUID_ARGS(a)                                                                                      \
    (a).guid.id1, (a).guid.id2, (a).guid.id3, (a).guid.id4[0], (a).guid.id4[1], (a).guid.id4[2], (a).guid.id4[3], \
        (a).guid.id4[4], (a).guid.id4[5], (a).guid.id4[6], (a).guid.id4[7]

extern wchar_t const* LobbyErrorDesc[28];  // LIFT: PDB public LobbyErrorDesc; placeholder definition in LobbyGamePacketHandler.cpp.

namespace StsMsgLib
{
// PDB StsMsgLib::_StsMsgRequestChargeRequestStop (size 0x30).
struct _StsMsgRequestChargeRequestStop : public _StsMsgRequest
{
    _GUID UserId;
    wchar_t* pwszReason;
};
static_assert(sizeof(_StsMsgRequestChargeRequestStop) == 0x30, "sizeof _StsMsgRequestChargeRequestStop");
static_assert(offsetof(_StsMsgRequestChargeRequestStop, UserId) == 0x18, "_StsMsgRequestChargeRequestStop::UserId");
static_assert(offsetof(_StsMsgRequestChargeRequestStop, pwszReason) == 0x28, "_StsMsgRequestChargeRequestStop::pwszReason");
}  // namespace StsMsgLib

namespace
{
// LIFT: inlined in 0xcd5e0. A null or empty reason logs as "unknown".
inline wchar_t const* npReasonText(wchar_t const* reason)
{
    return (reason == nullptr || wcslen(reason) == 0) ? L"unknown" : reason;
}
}  // namespace

// 0xcb710
bool (*DispatchNPLobbyMessageHandler(int cmd))(NPChannel*, _StsMsg*, NPTransaction*)
{
    switch (cmd)
    {
    case 1201: return Handle_CommonPres_UserInfo;
    case 1501: return Handle_CommonSlot_ListSlots;
    case 1502: return Handle_CommonSlot_GetSlot;
    case 1651: return Handle_SrvPromotionStamp_ListCurrentPromotions;
    case 1652: return Handle_SrvPromotionStamp_GetPromotionPolicy;
    case 1653: return Handle_SrvPromotionStamp_GetUserPromotionStatus;
    case 1655: return Handle_SrvPromotionStamp_AttendPromotionSecured;
    case 1711: return Handle_CommonSecondPassword_GetStatus;
    case 1721: return Handle_CommonGrade_ListGrades;
    case 1722: return Handle_CommonGrade_GetLevel;
    case 1725: return Handle_CommonGrade_ListAllGrades;
    case 2101: return Handle_SrvAuth_ConsumeGameToken;
    case 2106: return Handle_SrvAuth_IsUserNameChangeableIncomplete;
    case 2107: return Handle_SrvAuth_GetUserNameChangeableIncomplete;
    case 2108: return Handle_SrvAuth_ChangeMyUserNameIncomplete;
    case 2201: return Handle_SrvPres_Login;
    case 2202: return Handle_SrvPres_Logout;
    case 2205: return Handle_SrvPres_GetUserInfo;
    case 2207: return Handle_SrvPres_LogoutUser;
    case 2208: return Handle_SrvPres_SetAppData;
    case 2209: return Handle_SrvPres_Message;
    case 2210: return Handle_SrvPres_Kick;
    case 2251: return Handle_SrvGameAccount_ListUserLastPresences;
    case 2261: return Handle_SrvProfile_GetUserProfile;
    case 2271: return Handle_SrvGameTime_GetGameTime;
    case 2501: return Handle_SrvSlot_CreateSlots;
    case 2503: return Handle_SrvSlot_SetData;
    case 2591: return Handle_SrvRMS_Inquiry;
    case 2602: return Handle_SrvGate_RegisterService;
    case 2711: return Handle_SrvSecondPassword_IsVerified;
    case 2721: return Handle_SrvGrade_ActivateGrade;
    case 2723: return Handle_SrvGrade_NotifyGradeChanged;
    case 2724: return Handle_SrvGrade_NotifyScoreChanged;
    case 2751: return Handle_SrvFriend_SendMessage;
    case 2781: return Handle_SrvContentBan_ListUserBans;
    case 2901: return Handle_SrvCharge_GetInfo;
    case 2902: return Handle_SrvCharge_Start;
    case 2903: return Handle_SrvCharge_Stop;
    case 2904: return Handle_SrvCharge_RequestStop;
    case 2905: return Handle_SrvCharge_Abandon;
    case 2906: return Handle_SrvCharge_NotifyRemainTime;
    case 2907: return Handle_SrvCharge_NotifyApplyNewChargeItem;
    case 2961: return Handle_SrvAuction_Escrow;
    case 2962: return Handle_SrvAuction_RollbackEscrow;
    case 2963: return Handle_SrvAuction_Deliver;
    case 2964: return Handle_SrvAuction_Bid;
    case 2981: return Handle_SrvVirtualCurrency_Deposit;
    default: return nullptr;
    }
}

// 0xcbcb0
bool Handle_SrvGate_RegisterService(NPChannel*, _StsMsg* msg, NPTransaction*)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        _StsMsgResponse* res = static_cast<_StsMsgResponse*>(msg);
        if (npIsSuccess(res))
        {
            Log::Write(Log::LT_NOTICE, NPLOBBYMESSAGEHANDLER_FILE, 295, L"[np], Srv2GameAuction service registered");
            return true;
        }
        Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 291,
                   L"[np], register service fail; np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d, cmd:%d",
                   msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                   npReason(res), res->msgInfo.errInfo.nErrorCode, msg->GetCommand());
        return false;
    }
    return false;
}

// 0xcbe00
bool Handle_SrvProfile_GetUserProfile(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 93, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 309,
                           L"[np], handle srv-profile get user profile fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcbea0
bool Handle_SrvGameTime_GetGameTime(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 95, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 326,
                           L"[np], handle srv-gametime get game time fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcbf40
bool Handle_SrvAuth_ConsumeGameToken(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 34, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 343,
                           L"[np], handle consume game-token fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcbfe0
bool Handle_SrvAuth_IsUserNameChangeableIncomplete(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE && transaction != nullptr)
    {
        if (transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 66, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 360,
                           L"[np], handle is-user-name-changeable-incomplete response fail; execute job fail, tid:0x%I64X",
                           tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
        else
        {
            _StsMsgResponse* res = static_cast<_StsMsgResponse*>(msg);
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 367,
                       L"[np], handle is-user-name-changeable-incomplete response ok, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                       msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                       npReason(res), res->msgInfo.errInfo.nErrorCode);
            return true;
        }
    }
    return false;
}

// 0xcc110
bool Handle_SrvAuth_GetUserNameChangeableIncomplete(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE && transaction != nullptr)
    {
        if (transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 68, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 382,
                           L"[np], handle get-user-name-changeable-incomplete response fail; execute job fail, tid:0x%I64X",
                           tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
        else
        {
            _StsMsgResponse* res = static_cast<_StsMsgResponse*>(msg);
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 389,
                       L"[np], handle get-user-name-changeable-incomplete response ok, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                       msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                       npReason(res), res->msgInfo.errInfo.nErrorCode);
            return true;
        }
    }
    return false;
}

// 0xcc240
bool Handle_SrvAuth_ChangeMyUserNameIncomplete(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE && transaction != nullptr)
    {
        if (transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 70, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 404,
                           L"[np], handle change-my-user-name-incomplete response fail; execute job fail, tid:0x%I64X",
                           tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
        else
        {
            _StsMsgResponse* res = static_cast<_StsMsgResponse*>(msg);
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 411,
                       L"[np], handle change-my-user-name-incomplete response ok, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                       msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                       npReason(res), res->msgInfo.errInfo.nErrorCode);
            return true;
        }
    }
    return false;
}

// 0xcc370
// LIFT: not done. The body starts a KickJob through KickJob::_pool and ObjPool::Checkout (0x628c0).
// KickJob.h has no layout yet, and the LobbyDaemon ObjPool::Checkout is not lifted.
bool Handle_SrvPres_LogoutUser(NPChannel*, _StsMsg*, NPTransaction*)
{
    LIFT_STUB(0xcc370);
}

// 0xcc900
bool Handle_SrvPres_SetAppData(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 50, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 500,
                           L"[np], handle srv-presence set-app-data fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
        else
        {
            _StsMsgResponse* res = static_cast<_StsMsgResponse*>(msg);
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 508,
                       L"[np], handle srv-presence set-app-data ok, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                       msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                       npReason(res), res->msgInfo.errInfo.nErrorCode);
            return true;
        }
    }
    return false;
}

// 0xcca30
bool Handle_CommonSlot_GetSlot(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 37, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 523,
                           L"[np], handle common-slot get slot fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xccad0
bool Handle_CommonSlot_ListSlots(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 39, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 541,
                           L"[np], handle common-slot list slots fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xccb70
bool Handle_SrvSlot_CreateSlots(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 41, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 559,
                           L"[np], handle srv-slot create slots fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xccc10
bool Handle_SrvSlot_SetData(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 43, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 577,
                           L"[np], handle srv-slot set data fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcccb0
bool Handle_SrvPres_Login(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 45, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 595,
                           L"[np], handle srv-presence login fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xccd50
bool Handle_SrvPres_Logout(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 47, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 612,
                           L"[np], handle srv-presence logout fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
        else
        {
            _StsMsgResponse* res = static_cast<_StsMsgResponse*>(msg);
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 620,
                       L"[np], handle srv-presence logout ok, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                       msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                       npReason(res), res->msgInfo.errInfo.nErrorCode);
        }
    }
    return false;
}

// 0xcce80
bool Handle_SrvPres_GetUserInfo(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    // The original does not check the message type here.
    if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
    {
        NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
        LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
        if (!jobMgr->ExecuteW(tran->GetJobId(), 48, msg))
        {
            // The original log text says "login".
            Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 632,
                       L"[np], handle srv-presence login fail; execute job fail, tid:0x%I64X", tran->GetJobId());
        }
        else
        {
            return true;
        }
    }
    return false;
}

// 0xccf10
bool Handle_CommonPres_UserInfo(NPChannel*, _StsMsg* msg, NPTransaction*)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_NOTIFY)
    {
        _StsMsgNotifyPresenceUserInfo* noti = static_cast<_StsMsgNotifyPresenceUserInfo*>(msg);
        wchar_t const* alias = noti->pwszAlias != nullptr ? noti->pwszAlias : L"";
        wchar_t const* userName = noti->pwszUserName != nullptr ? noti->pwszUserName : L"";
        _GUID const& guid = noti->guidPortalAccountId;
        Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 647,
                   L"[np], handle common-presence user info notify ok, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, data-center:%d, user-name:%s, user-status:%d, alias:%s",
                   guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
                   guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7], noti->nDataCenter, userName,
                   noti->userStatus, alias);
        return true;
    }
    return false;
}

// 0xcd070
bool Handle_SrvPres_Message(NPChannel*, _StsMsg* msg, NPTransaction*)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        _StsMsgResponse* res = static_cast<_StsMsgResponse*>(msg);
        if (npIsSuccess(res))
        {
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 658,
                       L"[np], presence message success responsed, np-tid:%u, cmd:%d, type:%d", msg->GetTransactionId(),
                       msg->GetCommand(), msg->GetMessageType());
        }
        else
        {
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 661,
                       L"[np], presence message fail responsed, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                       msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(),
                       res->msgInfo.errInfo.nStatusCode, npReason(res), res->msgInfo.errInfo.nErrorCode);
        }
    }
    return false;
}

// 0xcd1a0
bool Handle_SrvPres_Kick(NPChannel*, _StsMsg* msg, NPTransaction*)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        _StsMsgResponse* res = static_cast<_StsMsgResponse*>(msg);
        if (npIsSuccess(res))
        {
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 672,
                       L"[np], presence kick success responsed, np-tid:%u, cmd:%d, type:%d", msg->GetTransactionId(),
                       msg->GetCommand(), msg->GetMessageType());
        }
        else
        {
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 675,
                       L"[np], presence kick fail responsed, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                       msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(),
                       res->msgInfo.errInfo.nStatusCode, npReason(res), res->msgInfo.errInfo.nErrorCode);
        }
    }
    return false;
}

// 0xcd2d0
bool Handle_SrvCharge_GetInfo(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 52, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 689,
                           L"[np], handle srv-charge get info fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcd370
bool Handle_SrvCharge_Start(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 54, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 706,
                           L"[np], handle srv-charge start fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcd410
bool Handle_SrvCharge_Stop(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr)
        {
            if (transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
            {
                NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
                LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
                if (!jobMgr->ExecuteW(tran->GetJobId(), 56, msg))
                {
                    Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 725,
                               L"[np], handle srv-charge stop fail; execute job fail, tid:0x%I64X", tran->GetJobId());
                }
                else
                {
                    return true;
                }
            }
        }
        else
        {
            _StsMsgResponse* res = static_cast<_StsMsgResponse*>(msg);
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 734,
                       L"[np], handle srv-charge stop ok, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                       msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                       npReason(res), res->msgInfo.errInfo.nErrorCode);
            return true;
        }
    }
    return false;
}

// 0xcd540
bool Handle_SrvCharge_Abandon(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 58, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 749,
                           L"[np], handle srv-charge abandon fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcdaa0
bool Handle_SrvCharge_NotifyApplyNewChargeItem(NPChannel*, _StsMsg* msg, NPTransaction*)
{
    if (msg->GetMessageType() != MESSAGE_TYPE_NOTIFY)
        return false;
    _StsMsgNotifyChargeNotifyApplyNewItem* noti = static_cast<_StsMsgNotifyChargeNotifyApplyNewItem*>(msg);
    id128 userId = npUserId(noti->UserId);
    CliSession* session = LobbyDaemon::_instance->_clisessionMgr->Select_index_account(userId);
    if (session == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 834,
                   L"[np], handle srv-charge notify apply new charge item fail; no such cli-session, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, charge-key:%s",
                   NPLMH_GUID_ARGS(userId), noti->ChargeKey);
        return true;
    }
    if (!session->ApplyNewChargeItem(noti->ChargeKey, static_cast<long>(noti->nRemainPlayTime), noti->nItemId,
                                     static_cast<short>(noti->nReservations)))
    {
        Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 842,
                   L"[np], handle srv-charge notify apply new charge item fail; apply fail, error:%s, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, charge-key:%s",
                   npLobbyErrorDesc(), NPLMH_GUID_ARGS(userId), noti->ChargeKey);
        session->removeReferenceCount(NPLOBBYMESSAGEHANDLER_FILE, 843);
        return true;
    }
    Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 847,
               L"[np], handle srv-charge notify apply new charge item ok, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, charge-key:%s",
               NPLMH_GUID_ARGS(userId), noti->ChargeKey);
    session->removeReferenceCount(NPLOBBYMESSAGEHANDLER_FILE, 849);
    return true;
}

// 0xcdda0
bool Handle_SrvCharge_NotifyRemainTime(NPChannel*, _StsMsg* msg, NPTransaction*)
{
    if (msg->GetMessageType() != MESSAGE_TYPE_NOTIFY)
        return false;
    _StsMsgNotifyChargeNotifyRemainTime* noti = static_cast<_StsMsgNotifyChargeNotifyRemainTime*>(msg);
    id128 userId = npUserId(noti->UserId);
    CliSession* session = LobbyDaemon::_instance->_clisessionMgr->Select_index_account(userId);
    if (session == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 867,
                   L"[np], handle srv-charge notify remain time fail; no such cli-session, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, remain-play-time:%d, reservations:%d, item-id:%u, computation-basis:%d",
                   NPLMH_GUID_ARGS(userId), noti->nRemainPlayTime, noti->nReservations, noti->nItemId,
                   noti->nComputationBasis);
        return true;
    }
    if (!session->NotifyChargeRemainTime(static_cast<long>(noti->nRemainPlayTime),
                                         static_cast<short>(noti->nReservations), noti->nItemId))
    {
        Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 875,
                   L"[np], handle srv-charge notify remain time fail; notify fail, error:%s, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, remain-play-time:%d, reservations:%d, item-id:%u, computation-basis:%d",
                   npLobbyErrorDesc(), NPLMH_GUID_ARGS(userId), noti->nRemainPlayTime, noti->nReservations,
                   noti->nItemId, noti->nComputationBasis);
    }
    // The original writes the "ok" line also after the "notify fail" line.
    Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 880,
               L"[np], handle srv-charge notify remain time ok, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, remain-play-time:%d, reservations:%d, item-id:%u, computation-basis:%d",
               NPLMH_GUID_ARGS(userId), noti->nRemainPlayTime, noti->nReservations, noti->nItemId,
               noti->nComputationBasis);
    session->removeReferenceCount(NPLOBBYMESSAGEHANDLER_FILE, 881);
    return true;
}

// 0xce140
bool Handle_SrvFriend_SendMessage(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 60, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 895,
                           L"[np], handle srv-friend send-message fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 898, L"[np], handle srv-friend send-message ok, tid:0x%I64X",
                           tran->GetJobId());
                return true;
            }
        }
        else
        {
            _StsMsgResponse* res = static_cast<_StsMsgResponse*>(msg);
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 904,
                       L"[np], handle srv-friend send-message ok, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                       msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                       npReason(res), res->msgInfo.errInfo.nErrorCode);
            return true;
        }
    }
    return false;
}

// 0xce280
bool Handle_CommonSecondPassword_GetStatus(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 62, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 920,
                           L"[np], handle common-second-password get-status fail; execute job fail, tid:0x%I64X",
                           tran->GetJobId());
            }
            else
            {
                Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 923,
                           L"[np], handle common-second-password get-status ok, tid:0x%I64X", tran->GetJobId());
                return true;
            }
        }
        else
        {
            _StsMsgResponse* res = static_cast<_StsMsgResponse*>(msg);
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 929,
                       L"[np], handle common-second-password get-status ok, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                       msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                       npReason(res), res->msgInfo.errInfo.nErrorCode);
            return true;
        }
    }
    return false;
}

// 0xce3c0
bool Handle_SrvSecondPassword_IsVerified(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 64, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 945,
                           L"[np], handle common-second-password is-verified fail; execute job fail, tid:0x%I64X",
                           tran->GetJobId());
            }
            else
            {
                Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 948,
                           L"[np], handle common-second-password is-verified ok, tid:0x%I64X", tran->GetJobId());
                return true;
            }
        }
        else
        {
            _StsMsgResponse* res = static_cast<_StsMsgResponse*>(msg);
            Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 954,
                       L"[np], handle common-second-password is-verified ok, np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                       msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                       npReason(res), res->msgInfo.errInfo.nErrorCode);
            return true;
        }
    }
    return false;
}

// 0xce500
bool Handle_SrvGameAccount_ListUserLastPresences(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 72, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 969,
                           L"[np], handle srv-game account listuser last presences fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xce5a0
bool Handle_CommonGrade_ListGrades(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 74, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 987,
                           L"[np], handle common-grade list-grades fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xce640
bool Handle_CommonGrade_ListAllGrades(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 76, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1005,
                           L"[np], handle common-grade list-all-grades fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xce6e0
bool Handle_CommonGrade_GetLevel(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 78, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1023,
                           L"[np], handle common-grade get-level fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xce780
bool Handle_SrvGrade_ActivateGrade(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 80, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1041,
                           L"[np], handle srv-grade activate-grade fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xce820
bool Handle_SrvGrade_NotifyGradeChanged(NPChannel*, _StsMsg* msg, NPTransaction*)
{
    if (msg->GetMessageType() != MESSAGE_TYPE_NOTIFY)
        return false;
    _StsMsgNotifyGradeNotifyGradeChanged* noti = static_cast<_StsMsgNotifyGradeNotifyGradeChanged*>(msg);
    id128 userId = npUserId(noti->UserId);
    CliSession* session = LobbyDaemon::_instance->_clisessionMgr->Select_index_account(userId);
    if (session == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1064,
                   L"[np], handle srv-grade notify grade changed fail; no such cli-session, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, grade-id:%d, game-grade-key:%s, activation:%s, grade-count:%d, from:%I64u, to:%I64u, remain-sec:%d, reason:%s",
                   NPLMH_GUID_ARGS(userId), noti->nGradeId, noti->GameGradeKey, noti->bActivation ? L"yes" : L"no",
                   noti->nGradeCount, noti->tTotalEffectiveFrom, noti->tTotalEffectiveTo,
                   noti->nRemainingGradeTimePerSecond, noti->pwszReason != nullptr ? noti->pwszReason : L"none");
        return true;
    }
    if (LobbyDaemon::_instance->_config->_useGrade && !session->NotifyChangedGrade(*noti))
    {
        Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1072,
                   L"[np], handle srv-grade notify grade changed fail; handle fail, cli-key:0x%I64X, error:%s, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, grade-id:%d, game-grade-key:%s, activation:%s, grade-count:%d, from:%I64u, to:%I64u, remain-sec:%d, reason:%s",
                   session->_clikey, npLobbyErrorDesc(), NPLMH_GUID_ARGS(userId), noti->nGradeId, noti->GameGradeKey,
                   noti->bActivation ? L"yes" : L"no", noti->nGradeCount, noti->tTotalEffectiveFrom,
                   noti->tTotalEffectiveTo, noti->nRemainingGradeTimePerSecond,
                   noti->pwszReason != nullptr ? noti->pwszReason : L"none");
        session->removeReferenceCount(NPLOBBYMESSAGEHANDLER_FILE, 1073);
        return true;
    }
    Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 1078,
               L"[np], handle srv-grade notify grade changed ok, cli-key:0x%I64X, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, grade-id:%d, game-grade-key:%s, activation:%s, grade-count:%d, from:%I64u, to:%I64u, remain-sec:%d, reason:%s",
               session->_clikey, NPLMH_GUID_ARGS(userId), noti->nGradeId, noti->GameGradeKey,
               noti->bActivation ? L"yes" : L"no", noti->nGradeCount, noti->tTotalEffectiveFrom,
               noti->tTotalEffectiveTo, noti->nRemainingGradeTimePerSecond,
               noti->pwszReason != nullptr ? noti->pwszReason : L"none");
    session->removeReferenceCount(NPLOBBYMESSAGEHANDLER_FILE, 1079);
    return true;
}

// 0xced00
bool Handle_SrvGrade_NotifyScoreChanged(NPChannel*, _StsMsg* msg, NPTransaction*)
{
    if (msg->GetMessageType() != MESSAGE_TYPE_NOTIFY)
        return false;
    _StsMsgNotifyGradeNotifyScoreChanged* noti = static_cast<_StsMsgNotifyGradeNotifyScoreChanged*>(msg);
    id128 userId = npUserId(noti->UserId);
    CliSession* session = LobbyDaemon::_instance->_clisessionMgr->Select_index_account(userId);
    if (session == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1101,
                   L"[np], handle srv-grade notify grade score changed fail; no such cli-session, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, level-id:%d, accumulate-grade-score:%d, minimum-level-score:%d, maximum-level-score:%d, maximum-grade-score:%d",
                   NPLMH_GUID_ARGS(userId), noti->nLevelId, noti->nAccumulateGradeScore, noti->nMinimumLevelScore,
                   noti->nMaximumLevelScore, noti->nMaximumGradeScore);
        return true;
    }
    if (LobbyDaemon::_instance->_config->_useGradeLevel && !session->NotifyChangedGradeLevel(*noti))
    {
        Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1109,
                   L"[np], handle srv-grade notify grade score changed fail; handle fail, cli-key:0x%I64X, error:%s, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, level-id:%d, accumulate-grade-score:%d, minimum-level-score:%d, maximum-level-score:%d, maximum-grade-score:%d",
                   session->_clikey, npLobbyErrorDesc(), NPLMH_GUID_ARGS(userId), noti->nLevelId,
                   noti->nAccumulateGradeScore, noti->nMinimumLevelScore, noti->nMaximumLevelScore,
                   noti->nMaximumGradeScore);
        session->removeReferenceCount(NPLOBBYMESSAGEHANDLER_FILE, 1110);
        return true;
    }
    Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 1115,
               L"[np], handle srv-grade notify grade score changed ok, cli-key:0x%I64X, user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, level-id:%d, accumulate-grade-score:%d, minimum-level-score:%d, maximum-level-score:%d, maximum-grade-score:%d",
               session->_clikey, NPLMH_GUID_ARGS(userId), noti->nLevelId, noti->nAccumulateGradeScore,
               noti->nMinimumLevelScore, noti->nMaximumLevelScore, noti->nMaximumGradeScore);
    session->removeReferenceCount(NPLOBBYMESSAGEHANDLER_FILE, 1116);
    return true;
}

// 0xcf0b0
// LIFT: not done. The body takes an AuctionEscrowJob from AuctionEscrowJob::_pool through ObjPool::Checkout
// (0x628c0). The LobbyDaemon ObjPool::Checkout is not lifted.
bool Handle_SrvAuction_Escrow(NPChannel*, _StsMsg*, NPTransaction*)
{
    LIFT_STUB(0xcf0b0);
}

// 0xcf270
// LIFT: not done. Same reason as 0xcf0b0 (AuctionRollbackEscrowJob::_pool, ObjPool::Checkout 0x628c0).
bool Handle_SrvAuction_RollbackEscrow(NPChannel*, _StsMsg*, NPTransaction*)
{
    LIFT_STUB(0xcf270);
}

// 0xcf440
// LIFT: not done. Same reason as 0xcf0b0 (AuctionDeliverJob::_pool, ObjPool::Checkout 0x628c0).
bool Handle_SrvAuction_Deliver(NPChannel*, _StsMsg*, NPTransaction*)
{
    LIFT_STUB(0xcf440);
}

// 0xcf570
bool Handle_SrvAuction_Bid(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 85, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1219,
                           L"[np], handle srv-auction bid fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                Log::Write(Log::LT_DEBUG, NPLOBBYMESSAGEHANDLER_FILE, 1223, L"[np], handle srv-auction bid ok, tid:0x%I64X",
                           tran->GetJobId());
                return true;
            }
        }
    }
    return false;
}

// 0xcf620
bool Handle_SrvContentBan_ListUserBans(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 87, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1237,
                           L"[np], handle srv-content-ban list-user-bans fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcf6c0
bool Handle_SrvRMS_Inquiry(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 89, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1256,
                           L"[np], handle srv-rms inquiry fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcf760
bool Handle_SrvVirtualCurrency_Deposit(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 91, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1275,
                           L"[np], handle srv-virtual-currency deposit fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcf800
bool Handle_SrvPromotionStamp_ListCurrentPromotions(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 97, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1292,
                           L"[np], handle srv-promotion-stamp list-current-promotions fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcf8a0
bool Handle_SrvPromotionStamp_GetPromotionPolicy(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 99, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1309,
                           L"[np], handle srv-promotion-stamp list-current-promotions fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcf940
bool Handle_SrvPromotionStamp_GetUserPromotionStatus(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 101, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1326,
                           L"[np], handle srv-promotion-stamp get-promotion-status fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// 0xcf9e0
bool Handle_SrvPromotionStamp_AttendPromotionSecured(NPChannel*, _StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() == MESSAGE_TYPE_RESPONSE)
    {
        if (transaction != nullptr && transaction->GetKind() == NPTransaction::KIND_LOBBYJOB)
        {
            NPLobbyJobTransaction* tran = static_cast<NPLobbyJobTransaction*>(transaction);
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (!jobMgr->ExecuteW(tran->GetJobId(), 103, msg))
            {
                Log::Write(Log::LT_ERROR, NPLOBBYMESSAGEHANDLER_FILE, 1343,
                           L"[np], handle srv-promotion-stamp attend-promotion-secured fail; execute job fail, tid:0x%I64X", tran->GetJobId());
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

// 0xcd5e0 (command 2904 = COMMAND_SRV_CHARGE_REQUEST_STOP)
bool Handle_SrvCharge_RequestStop(NPChannel* channel, StsMsgLib::_StsMsg* msg, NPTransaction* transaction)
{
    if (msg->GetMessageType() != StsMsgLib::MESSAGE_TYPE_REQUEST)
        return false;
    StsMsgLib::_StsMsgRequestChargeRequestStop* req = static_cast<StsMsgLib::_StsMsgRequestChargeRequestStop*>(msg);
    unsigned int txnid = msg->GetTransactionId();
    id128 userId = *reinterpret_cast<id128 const*>(&req->UserId);
    CliSession* cs = LobbyDaemon::_instance->_clisessionMgr->Select_index_account(userId);
    if (cs == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"NPLobbyMessageHandler.cpp", 773,
                   L"[np], handle srv-charge request stop fail; no such cli-session, txn-id:%u, req-reason:%s, "
                   L"user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   txnid, npReasonText(req->pwszReason), userId.guid.id1, userId.guid.id2, userId.guid.id3,
                   userId.guid.id4[0], userId.guid.id4[1], userId.guid.id4[2], userId.guid.id4[3],
                   userId.guid.id4[4], userId.guid.id4[5], userId.guid.id4[6], userId.guid.id4[7]);
        StsMsgLib::_StsMsgResponseChargeRequestStop res;
        npInitResponse(res, StsMsgLib::COMMAND_SRV_CHARGE_REQUEST_STOP, txnid);
        res.msgInfo.errInfo.nStatusCode = 400;
        res.msgInfo.errInfo.pwszReason = L"ErrUserNotOnline";
        res.msgInfo.errInfo.nErrorCode = 3007;
        channel->SendMsg(&res, false, nullptr);
        return true;
    }
    short stopPlayReason = 0;
    wchar_t const* reason = req->pwszReason;
    if (reason != nullptr && wcslen(reason) != 0)
    {
        if (wcscmp(reason, L"Already Charge") == 0)
            stopPlayReason = 1;
        else if (wcscmp(reason, L"Terminate") == 0)
            stopPlayReason = 2;
        else if (wcscmp(reason, L"Suspend") == 0)
            stopPlayReason = 3;
        else if (wcscmp(reason, L"Abandon") == 0)
            stopPlayReason = 4;
        else if (wcscmp(reason, L"IPKick") == 0)
            stopPlayReason = 5;
    }
    if (!cs->OnChargeStopRequested(txnid))
    {
        LobbyError error = TLobbyError;
        Log::Write(Log::LT_ERROR, L"NPLobbyMessageHandler.cpp", 800,
                   L"[np], handle srv-charge request stop fail; denied by cli-session, error:%s, txn-id:%u, req-reason:%s, "
                   L"user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   static_cast<unsigned int>(error) >= 28 ? L"LOBERR_UNDEFINED" : LobbyErrorDesc[error], txnid,
                   npReasonText(req->pwszReason), userId.guid.id1, userId.guid.id2, userId.guid.id3,
                   userId.guid.id4[0], userId.guid.id4[1], userId.guid.id4[2], userId.guid.id4[3],
                   userId.guid.id4[4], userId.guid.id4[5], userId.guid.id4[6], userId.guid.id4[7]);
        static_cast<NPGameServiceChannel*>(channel)->SendResponseChargeRequestStopFail(txnid, L"ErrBadData", 4);
        cs->removeReferenceCount(L"NPLobbyMessageHandler.cpp", 802);
        return true;
    }
    cs->ReserveStopPlay(false, stopPlayReason, 9);
    Log::Write(Log::LT_DEBUG, L"NPLobbyMessageHandler.cpp", 813,
               L"[np], handle srv-charge request stop ok, txn-id:%u, req-reason:%s, "
               L"user-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
               txnid, npReasonText(req->pwszReason), userId.guid.id1, userId.guid.id2, userId.guid.id3,
               userId.guid.id4[0], userId.guid.id4[1], userId.guid.id4[2], userId.guid.id4[3],
               userId.guid.id4[4], userId.guid.id4[5], userId.guid.id4[6], userId.guid.id4[7]);
    cs->removeReferenceCount(L"NPLobbyMessageHandler.cpp", 815);
    return true;
}
