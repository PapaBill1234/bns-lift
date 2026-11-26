// NPLobbyMessageHandler.obj (LobbyDaemon PDB, 2019 + PDB).
// The module has no classes. It has the dispatch function and one handler per NP command.
// PDB type 0x4E6C: every handler is bool (NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*).
#pragma once

class NPChannel;
class NPTransaction;
namespace StsMsgLib
{
struct _StsMsg;
}

// 0xcb710 PDB type 0x7837. NPServiceChannelManager::HandleMessage (0xd0100) calls it.
bool (*DispatchNPLobbyMessageHandler(int cmd))(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);

bool Handle_SrvGate_RegisterService(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                  // 0xcbcb0
bool Handle_SrvProfile_GetUserProfile(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                // 0xcbe00
bool Handle_SrvGameTime_GetGameTime(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                  // 0xcbea0
bool Handle_SrvAuth_ConsumeGameToken(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                 // 0xcbf40
bool Handle_SrvAuth_IsUserNameChangeableIncomplete(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);   // 0xcbfe0
bool Handle_SrvAuth_GetUserNameChangeableIncomplete(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);  // 0xcc110
bool Handle_SrvAuth_ChangeMyUserNameIncomplete(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);       // 0xcc240
bool Handle_SrvPres_LogoutUser(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                       // 0xcc370
bool Handle_SrvPres_SetAppData(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                       // 0xcc900
bool Handle_CommonSlot_GetSlot(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                       // 0xcca30
bool Handle_CommonSlot_ListSlots(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                     // 0xccad0
bool Handle_SrvSlot_CreateSlots(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                      // 0xccb70
bool Handle_SrvSlot_SetData(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                          // 0xccc10
bool Handle_SrvPres_Login(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                            // 0xcccb0
bool Handle_SrvPres_Logout(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                           // 0xccd50
bool Handle_SrvPres_GetUserInfo(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                      // 0xcce80
bool Handle_CommonPres_UserInfo(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                      // 0xccf10
bool Handle_SrvPres_Message(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                          // 0xcd070
bool Handle_SrvPres_Kick(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                             // 0xcd1a0
bool Handle_SrvCharge_GetInfo(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                        // 0xcd2d0
bool Handle_SrvCharge_Start(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                          // 0xcd370
bool Handle_SrvCharge_Stop(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                           // 0xcd410
bool Handle_SrvCharge_Abandon(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                        // 0xcd540
bool Handle_SrvCharge_RequestStop(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                    // 0xcd5e0
bool Handle_SrvCharge_NotifyApplyNewChargeItem(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);       // 0xcdaa0
bool Handle_SrvCharge_NotifyRemainTime(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);               // 0xcdda0
bool Handle_SrvFriend_SendMessage(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                    // 0xce140
bool Handle_CommonSecondPassword_GetStatus(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);           // 0xce280
bool Handle_SrvSecondPassword_IsVerified(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);             // 0xce3c0
bool Handle_SrvGameAccount_ListUserLastPresences(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);     // 0xce500
bool Handle_CommonGrade_ListGrades(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                   // 0xce5a0
bool Handle_CommonGrade_ListAllGrades(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                // 0xce640
bool Handle_CommonGrade_GetLevel(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                     // 0xce6e0
bool Handle_SrvGrade_ActivateGrade(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                   // 0xce780
bool Handle_SrvGrade_NotifyGradeChanged(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);              // 0xce820
bool Handle_SrvGrade_NotifyScoreChanged(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);              // 0xced00
bool Handle_SrvAuction_Escrow(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                        // 0xcf0b0
bool Handle_SrvAuction_RollbackEscrow(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                // 0xcf270
bool Handle_SrvAuction_Deliver(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                       // 0xcf440
bool Handle_SrvAuction_Bid(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                           // 0xcf570
bool Handle_SrvContentBan_ListUserBans(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);               // 0xcf620
bool Handle_SrvRMS_Inquiry(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);                           // 0xcf6c0
bool Handle_SrvVirtualCurrency_Deposit(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);               // 0xcf760
bool Handle_SrvPromotionStamp_ListCurrentPromotions(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);  // 0xcf800
bool Handle_SrvPromotionStamp_GetPromotionPolicy(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);     // 0xcf8a0
bool Handle_SrvPromotionStamp_GetUserPromotionStatus(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*); // 0xcf940
bool Handle_SrvPromotionStamp_AttendPromotionSecured(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*); // 0xcf9e0
