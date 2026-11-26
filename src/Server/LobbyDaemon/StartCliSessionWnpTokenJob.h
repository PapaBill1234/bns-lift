// StartCliSessionWnpTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon StartCliSessionWnpTokenJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"
#include "StringUtil.h"

class CliSession;
class IDEV612_TimeTable;
class LobbyGateChannel;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x1E0, CliSessionJob base).
class StartCliSessionWnpTokenJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        CONSUME_TOKEN = 1,
        CHECK_SECOND_PASSWD = 2,
        CHECK_ACTIVITY_LIST_USER_LAST_PRESENCES = 3,
        CHECK_ACTIVITY_LIST_SLOTS = 4,
        CHECK_ACTIVITY_CREATE_SLOTS = 5,
        CHECK_ACTIVITY_SET_SLOT_DATA = 6,
        PRESENCE_LOGIN = 7,
        GET_USER_PROFILE = 8,
        GET_GAME_TIME = 9,
        GET_GRADE_LEVEL = 10,
        LIST_ALL_GRADES = 11,
        GET_CONTENT_BAN = 12,
        GET_RMS_INQUIRY = 13,
        GET_GET_USER_PROMOTION_STATUS = 14,
        LOGIN_ACCOUNT = 15,
        FIN = 16
    };

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

    LobbyGateChannel* _lgate;  // +0x58
    unsigned long long _clikey;  // +0x60
    id128 _nptoken;  // +0x68
    id128 _portalAccountId;  // +0x78
    id128 _gameAccountId;  // +0x88
    id128 _userId;  // +0x98
    wchar_t _gameAccountName[65];  // +0xA8
    wchar_t _userName[65];  // +0x12A
    unsigned long long _activityStatus;  // +0x1B0
    id128 _activitySlotId;  // +0x1B8
    IDEV612_TimeTable* _gameTimeSchedule;  // +0x1C8
    char _lastGetUserPromotionStatusTargetType;  // +0x1D0
    int _lastGetUserPromotionStatusPromotionId;  // +0x1D4
    int _timeBasedPromotionIds[2];  // +0x1D8

public:
    static ObjPool _pool;  // .data 0x2056b0
    static void* _vtbl();  // LIFT: PDB declares it; no RVA (inlined in LobbyDaemon::initialize 0x9b300)
    static LobbyJobDef _def;

    friend struct StartCliSessionWnpTokenJobLayoutCheck;
};

struct StartCliSessionWnpTokenJobLayoutCheck
{
    static_assert(sizeof(StartCliSessionWnpTokenJob) == 0x1E0, "sizeof StartCliSessionWnpTokenJob");
    static_assert(offsetof(StartCliSessionWnpTokenJob, _lgate) == 0x58, "StartCliSessionWnpTokenJob::_lgate");
    static_assert(offsetof(StartCliSessionWnpTokenJob, _nptoken) == 0x68, "StartCliSessionWnpTokenJob::_nptoken");
    static_assert(offsetof(StartCliSessionWnpTokenJob, _userId) == 0x98, "StartCliSessionWnpTokenJob::_userId");
    static_assert(offsetof(StartCliSessionWnpTokenJob, _gameAccountName) == 0xA8, "StartCliSessionWnpTokenJob::_gameAccountName");
    static_assert(offsetof(StartCliSessionWnpTokenJob, _userName) == 0x12A, "StartCliSessionWnpTokenJob::_userName");
    static_assert(offsetof(StartCliSessionWnpTokenJob, _activityStatus) == 0x1B0, "StartCliSessionWnpTokenJob::_activityStatus");
    static_assert(offsetof(StartCliSessionWnpTokenJob, _activitySlotId) == 0x1B8, "StartCliSessionWnpTokenJob::_activitySlotId");
    static_assert(offsetof(StartCliSessionWnpTokenJob, _gameTimeSchedule) == 0x1C8, "StartCliSessionWnpTokenJob::_gameTimeSchedule");
    static_assert(offsetof(StartCliSessionWnpTokenJob, _lastGetUserPromotionStatusPromotionId) == 0x1D4, "StartCliSessionWnpTokenJob::_lastGetUserPromotionStatusPromotionId");
    static_assert(offsetof(StartCliSessionWnpTokenJob, _timeBasedPromotionIds) == 0x1D8, "StartCliSessionWnpTokenJob::_timeBasedPromotionIds");
};
