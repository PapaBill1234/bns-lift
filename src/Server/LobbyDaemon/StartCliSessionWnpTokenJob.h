// StartCliSessionWnpTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
struct LobbyJobDef;

class StartCliSessionWnpTokenJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0xd2340
    StartCliSessionWnpTokenJob(CliSession*);  // 0xd23a0
    virtual ~StartCliSessionWnpTokenJob();  // 0xd24a0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0xd2350
    virtual bool work(int, void*);  // 0xd2530
    bool init(int, void*);  // 0xd2840
    bool consumeToken(int, void*);  // 0xd31e0
    bool consumeTokenResponse(int, void*);  // 0xd3500
    bool consumeTokenExpire();  // 0xd3bc0
    bool listUserLastPresencesReq();  // 0xd3ce0
    bool listUserLastPresencesResponse(void*);  // 0xd4050
    bool listUserLastPresencesExpire();  // 0xd46c0
    bool listSlotsReq();  // 0xd47e0
    bool listSlotsResponse(void*);  // 0xd4b90
    bool listSlotsExpire();  // 0xd5190
    bool createSlotsReq();  // 0xd52b0
    bool createSlotsResponse(void*);  // 0xd5770
    bool createSlotsExpire();  // 0xd5db0
    bool setSlotDataReq();  // 0xd5ed0
    bool setSlotDataResponse(void*);  // 0xd62b0
    bool setSlotDataExpire();  // 0xd66b0
    bool presenceLoginReq();  // 0xd67d0
    bool presenceLoginResponse(void*);  // 0xd6ad0
    bool presenceLoginExpire();  // 0xd74a0
    bool getUserProfileReq();  // 0xd75c0
    bool getUserProfileResponse(void*);  // 0xd7930
    bool getUserProfileExpire();  // 0xd7ec0
    bool getGameTimeReq();  // 0xd7fe0
    bool getGameTimeResponse(void*);  // 0xd8360
    bool getGameTimeExpire();  // 0xd8b10
    bool getGradeLevelReq();  // 0xd8c30
    bool getGradeLevelResponse(void*);  // 0xd8f60
    bool getGradeLevelExpire();  // 0xd9420
    bool listAllGradesReq();  // 0xd9540
    bool listAllGradesResponse(void*);  // 0xd98b0
    bool listAllGradesExpire();  // 0xd9da0
    bool listUserBansReq();  // 0xd9ec0
    bool listUserBansResponse(void*);  // 0xda1a0
    bool listUserBansExpire();  // 0xda680
    bool getRMSInquiryReq();  // 0xda7a0
    bool getRMSInquiryResponse(void*);  // 0xdaa90
    bool getRMSInquiryExpire();  // 0xdaf60
    bool getUserPromotionStatusReq();  // 0xdb080
    bool getUserPromotionStatusResponse(void*);  // 0xdb400
    bool getUserPromotionStatusExpire();  // 0xdb830
    bool loginAccount();  // 0xdb950
    bool checkIntialUserName(wchar_t const*);  // 0xdc310
};
