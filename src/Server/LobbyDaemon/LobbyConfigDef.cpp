// LobbyConfig.obj (LobbyDaemon PDB, 2019 + PDB): the XML table LobbyConfig::_Def and its default values.
// LIFT: this file holds only the table. The original has it in LobbyConfig.obj. A separate file keeps the
// LobbyConfig.cpp bodies free of merge conflicts.
// The rows come from the exe .rdata at rva 0x205DD0 (167 rows of 40 bytes). DaemonConfig::Dump (0xe3c00) stops
// at row 167. The names of the default values come from the PDB (LobbyConfig.obj).
// ❓ The 3 empty-string defaults share one literal in the exe. The row to name mapping of these 3 is not verified.
#include <stddef.h>
#include "LobbyConfig.h"
#include "DaemonConfig.h"

// Default values of LobbyConfig::_Def.
static int const DEFAULT_DUMPTYPE = 1;  // rva 0x12B76C
static int const DEFAULT_TIMER_INTERVAL = 500;  // rva 0x12B8FC
static int const DEFAULT_TIMER_MAX_TIME = 20;  // rva 0x12BAF4
static int const DEFUALT_TYPE_FOR_FAILED_OBJECT_LOG = 40;  // rva 0x12BB6C
static int const DEFAULT_NP_PORT = 6601;  // rva 0x12BD0C
static int const DEFAULT_WORLD_PORT = 21800;  // rva 0x12BF04
static int const DEFAULT_LOBBY_GATE_PORT = 21801;  // rva 0x12BF7C
static int const DEFAULT_MANAGE_PORT = 31800;  // rva 0x12C1AC
static int const DEFAULT_POSTOFFICE_PORT = 20500;  // rva 0x12C3A4
static int const DEFAULT_LOBBY_WORLD_ID = 10050;  // rva 0x12C41C
static int const DEFAULT_LOBBY_JOB_TRANSACTION_LIFE_TIME = 30000;  // rva 0x12C5CC
static int const DEFAULT_LOBBY_TOKEN_LIFE_TIME = 600000;  // rva 0x12C7D4
static int const DEFAULT_UPDATE_PERIOD_OF_WORLD_INFO_LIST = 5000;  // rva 0x12C84C
static int const DEFAULT_STOP_PLAY_GAME_WORLD_TIMEOUT = 30000;  // rva 0x12D86C
static int const DEFAULT_SECOND_PASSWORD_TYPE = 3;  // rva 0x12D9A0
static int const DEFAULT_ACTIVITY_RESTING_STATUS_PERIOD = 2592000;  // rva 0x12D9A4
static int const DEFAULT_ACTIVITY_PRE_RESTING_STATUS_PERIOD = 1296000;  // rva 0x12D9A8
static int const DEFAULT_CONTENT_BAN_ID_FOR_JUMPING_CHARACTER = 5;  // rva 0x12D9AC
static int const DEFAULT_ALLOWED_CHARACTER_NAME_LENGTH_MIN = 1;  // rva 0x12D9B0
static int const DEFAULT_ALLOWED_CHARACTER_NAME_LENGTH_MAX = 12;  // rva 0x12D9B4
static int const DEFAULT_ALLOWED_CHARACTER_NAME_SPACE_AMOUNT = 2;  // rva 0x12D9B8
static int const DEFAULT_CHARACTER_NAME_REUSE_LIMIT_DURATION = 31536000;  // rva 0x12D9BC
static int const DEFAULT_SHORT_TERM_WAIT_CHARACTER_DELETION_TIME = 600;  // rva 0x12D9C0
static int const DEFAULT_LONG_TERM_WAIT_CHARACTER_DELETION_TIME = 86400;  // rva 0x12D9C4
static int const DEFAULT_LONG_TERM_WAIT_CHARACTER_DELETION_CRITERIA_LEVEL = 10;  // rva 0x12D9C8
static int const DEFAULT_CHARACTER_DELETION_SCHEDULER_PERIOD = 300;  // rva 0x12D9CC
static int const DEFAULT_CHARACTER_DELETION_SCHEDULER_CONCURRENT_PROCESSING_COUNT = 50;  // rva 0x12D9D0
static int const DEFAULT_MAX_SLOT_COUNT = 7;  // rva 0x12D9D4
static int const DEFAULT_ALLOWED_GUILD_NAME_LENGTH_MIN = 1;  // rva 0x12D9D8
static int const DEFAULT_ALLOWED_GUILD_NAME_LENGTH_MAX = 32;  // rva 0x12D9DC
static int const DEFAULT_ALLOWED_GUILD_NAME_SPACE_AMOUNT = 2;  // rva 0x12D9E0
static int const DEFAULT_GUILD_NAME_REUSE_LIMIT_DURATION = 604800;  // rva 0x12D9E4
static int const DEFAULT_ALLOWED_USER_NAME_LENGTH_MIN = 2;  // rva 0x12D9E8
static int const DEFAULT_ALLOWED_USER_NAME_LENGTH_MAX = 10;  // rva 0x12D9EC
static int const DEFAULT_ACCOUNT_INVENTORY_PORT = 21700;  // rva 0x12D9F0
static int const DEFAULT_INFO_GATE_PORT = 21802;  // rva 0x12D9F4
static int const DEFAULT_INFO_GATE_PUBLIC_PORT = 12100;  // rva 0x12D9F8
static int const DEFAULT_FREE_PLAY_TYPE = 0;  // rva 0x12D9FC
static int const DEFAULT_TRIAL_PLAY_LIMIT_LV = 0;  // rva 0x12DA00
static int const DEFAULT_MIN_LOBBY_SERVICE_ITEM_DATA_ID = 1;  // rva 0x12DA04
static int const DEFAULT_MAX_LOBBY_SERVICE_ITEM_DATA_ID = 999;  // rva 0x12DA08
static int const DEFAULT_AUCTION_ESCROW_MIN_MONEY = 10000;  // rva 0x12DA0C
static int const DEFAULT_AUCTION_ESCROW_UNIT_MONEY = 10000;  // rva 0x12DA10
static int const DEFAULT_MILEAGE_DEPOSIT_REQUEST_CODE = 9;  // rva 0x12DA14
static int const DEFAULT_MILEAGE_DEPOSIT_REASON = 5;  // rva 0x12DA18
static int const DEFAULT_MILEAGE_DEPOSIT_PERIOD = 30;  // rva 0x12DA1C
static int const DEFAULT_MILEAGE_SCHEDULE_WEEK_COUNT = 4;  // rva 0x12DA20
static int const DEFAULT_MILEAGE_BATCH_RETRY_CONCURRENT_COUNT = 50;  // rva 0x12DA24
static int const DEFAULT_EXPORT_LOBBY_STATS_FILE_PERIOD = 300;  // rva 0x12DA28
static int const DEFAULT_TENCENT_UIC_INTERVAL = 10;  // rva 0x12DA2C
static wchar_t const* const DEFAULT_FIREND_MESSAGE_RECIPIENT_APP_ID_LIST = L"";
static wchar_t const* const DEFAULT_SUPPORT_LANGUAGES = L"default";
static wchar_t const* const DEFAULT_INITIAL_USER_NAME_PREFIX_LIST = L"QQID_";
static wchar_t const* const DEFAULT_TENCENT_UIC_CONFIGFILE = L"./bin/tss_sdk_plugin_uic_config.xml";
static wchar_t const* const DEFAULT_AUCTION_ESCROW_MONEY_ITEM_KEY = L"66001";
static wchar_t const* const DEFAULT_EXTEND_JUMPING_CHARACTER_CREATION_QUOTA_ITEM_DATA_IDS = L"111";
static wchar_t const* const DEFAULT_CHANGE_USER_NAME_ITEM_DATA_IDS = L"110";
static wchar_t const* const DEFAULT_ADD_SLOT_ITEM_DATA_IDS = L"104;108";
static wchar_t const* const DEFAULT_RENAME_CHARACTER_BY_SYSTEM_ITEM_DATA_IDS = L"114";
static wchar_t const* const DEFAULT_RENAME_CHARACTER_ITEM_DATA_IDS = L"105;109";
static wchar_t const* const DEFAULT_CHANGE_CHARACTER_RACE_ITEM_DATA_IDS = L"113";
static wchar_t const* const DEFAULT_CHANGE_CHARACTER_SEX_ITEM_DATA_IDS = L"112";
static wchar_t const* const DEFAULT_CHANGE_CHARACTER_APPEARANCE_ITEM_DATA_IDS = L"102;106";
static wchar_t const* const LOCALHOST_IP = L"127.0.0.1";
static wchar_t const* const DEFAULT_FORBIDDEN_CHARACTERS_FOR_CHARACTER_NAME = L"";
static wchar_t const* const DEFAULT_FORBIDDEN_CHARACTERS_FOR_GUILD_NAME = L"";
// Rows with a small literal value (not a pointer) are bool defaults: the exe holds the value 1.
#define DEFAULT_TRUE reinterpret_cast<void const*>(1)

// rva 0x205DD0
XmlCfgDef const LobbyConfig::_Def[167] = {
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"path"},
    {offsetof(LobbyConfig, _rootPath), L"root-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full root path"},
    {offsetof(LobbyConfig, _logPath), L"log-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full log path"},
    {offsetof(LobbyConfig, _configPath), L"config-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full config path"},
    {offsetof(LobbyConfig, _dataPath), L"data-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full data path"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"certification"},
    {offsetof(LobbyConfig, _certFile), L"cert", XmlCfgDef::CFG_ANSI, 1, nullptr, L"certification file path"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"system configuration"},
    {offsetof(LobbyConfig, _workerThreadCount), L"worker-thread", XmlCfgDef::CFG_INT, 0, nullptr, L"0 is system recommend"},
    {offsetof(LobbyConfig, _dumpType), L"dump-type", XmlCfgDef::CFG_INT, 0, &DEFAULT_DUMPTYPE, L"0: no dump, 1: minimal dump(default), 2: full dump"},
    {offsetof(LobbyConfig, _timerInterval), L"timer-interval", XmlCfgDef::CFG_INT, 0, &DEFAULT_TIMER_INTERVAL, L"interval of timer(msec)"},
    {offsetof(LobbyConfig, _timerMaxTime), L"timer-max-time", XmlCfgDef::CFG_INT, 0, &DEFAULT_TIMER_MAX_TIME, L"max time of timer(sec)"},
    {offsetof(LobbyConfig, _reuseWaitTime), L"wait-time-for-reuse-pool-object", XmlCfgDef::CFG_INT, 0, nullptr, L"msec. for debugging. 0 means pool object be reused immediately. caution, in service mode, pool object do not wait for reuse"},
    {offsetof(LobbyConfig, _reservedMinLobbyGateWidRange), L"reserved-lobby-gate-wid-range-min", XmlCfgDef::CFG_INT, 1, nullptr, L"min. of reserved lobby-gate world id range"},
    {offsetof(LobbyConfig, _reservedMaxLobbyGateWidRange), L"reserved-lobby-gate-wid-range-max", XmlCfgDef::CFG_INT, 1, nullptr, L"max. of reserved lobby-gate world id range"},
    {offsetof(LobbyConfig, _reservedMinGameWorldWidRange), L"reserved-game-world-wid-range-min", XmlCfgDef::CFG_INT, 1, nullptr, L"min. of reserved game-world world id range"},
    {offsetof(LobbyConfig, _reservedMaxGameWorldWidRange), L"reserved-game-world-wid-range-max", XmlCfgDef::CFG_INT, 1, nullptr, L"max. of reserved game-world world id range"},
    {offsetof(LobbyConfig, _reservedMinInfoGateWidRange), L"reserved-info-gate-wid-range-min", XmlCfgDef::CFG_INT, 1, nullptr, L"min. of reserved info-gate world id range"},
    {offsetof(LobbyConfig, _reservedMaxInfoGateWidRange), L"reserved-info-gate-wid-range-max", XmlCfgDef::CFG_INT, 1, nullptr, L"max. of reserved info-gate world id range"},
    {offsetof(LobbyConfig, _typeForFailedEventObjectLog), L"type-for-failed-event-object-log", XmlCfgDef::CFG_INT, 0, &DEFUALT_TYPE_FOR_FAILED_OBJECT_LOG, L"event object bit flag for writing failed event object log, 3:session, 5:timer. default 40(101000 session and timer)"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"session configuration"},
    {offsetof(LobbyConfig, _maxNPSessionCount), L"max-np-session-count", XmlCfgDef::CFG_INT, 1, nullptr, L"0 means default internal session count"},
    {offsetof(LobbyConfig, _maxLobbyGateSessionCount), L"max-lobby-gate-session-count", XmlCfgDef::CFG_INT, 1, nullptr, L"0 means default internal session count"},
    {offsetof(LobbyConfig, _maxInfoGateSessionCount), L"max-info-gate-session-count", XmlCfgDef::CFG_INT, 1, nullptr, L"0 means default internal session count"},
    {offsetof(LobbyConfig, _maxGameWorldSessionCount), L"max-game-world-session-count", XmlCfgDef::CFG_INT, 1, nullptr, L"0 means default internal session count"},
    {offsetof(LobbyConfig, _maxManageSessionCount), L"max-management-session-count", XmlCfgDef::CFG_INT, 1, nullptr, L"0 means default manage session count"},
    {offsetof(LobbyConfig, _maxPostOfficeSessionCount), L"max-postoffice-session-count", XmlCfgDef::CFG_INT, 1, nullptr, L"0 means default internal session count"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"network configuration"},
    {offsetof(LobbyConfig, _npAddr), L"np-address", XmlCfgDef::CFG_IP, 1, LOCALHOST_IP, L"np ip address"},
    {offsetof(LobbyConfig, _npPort), L"np-port", XmlCfgDef::CFG_INT, 1, &DEFAULT_NP_PORT, L"np port"},
    {offsetof(LobbyConfig, _worldPort), L"world-port", XmlCfgDef::CFG_INT, 1, &DEFAULT_WORLD_PORT, L"world port"},
    {offsetof(LobbyConfig, _lobbyGatePort), L"lobby-gate-port", XmlCfgDef::CFG_INT, 1, &DEFAULT_LOBBY_GATE_PORT, L"lobby gate port"},
    {offsetof(LobbyConfig, _managePort), L"manage-port", XmlCfgDef::CFG_INT, 1, &DEFAULT_MANAGE_PORT, L"manage port"},
    {offsetof(LobbyConfig, _postOfficeAddr), L"post-office-address", XmlCfgDef::CFG_IP, 1, LOCALHOST_IP, L"post-office ip address"},
    {offsetof(LobbyConfig, _postOfficePort), L"post-office-port", XmlCfgDef::CFG_INT, 1, &DEFAULT_POSTOFFICE_PORT, L"post-office port"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"locale configuration"},
    {offsetof(LobbyConfig, _supportLanguages), L"support-languages", XmlCfgDef::CFG_STR, 1, DEFAULT_SUPPORT_LANGUAGES, L"support languages. sperated by ';'. supports:[default(alphabet&korean)|korean|english|japanese|chineses|chineset|russian|french|german|thai|vietnamese|bportuguese]"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"lobby configuration"},
    {offsetof(LobbyConfig, _worldId), L"lobby-world-id", XmlCfgDef::CFG_INT, 1, &DEFAULT_LOBBY_WORLD_ID, L"world-id of lobby daemon"},
    {offsetof(LobbyConfig, _cliSessionHashCount), L"cli-session-hash-count", XmlCfgDef::CFG_INT, 1, nullptr, L"cli-session hash count. 0 means system default."},
    {offsetof(LobbyConfig, _initCliSessionCount), L"init-client-session-count", XmlCfgDef::CFG_INT, 1, nullptr, L"cli-session initial object pool size. 0 means no preparance"},
    {offsetof(LobbyConfig, _lobbyJobHashCount), L"lobby-job-hash-count", XmlCfgDef::CFG_INT, 1, nullptr, L"lobby-job hash count. 0 means system default."},
    {offsetof(LobbyConfig, _initLobbyJobCount), L"init-lobby-job-count", XmlCfgDef::CFG_INT, 1, nullptr, L"lobby-job initial object pool size. 0 means no preparance"},
    {offsetof(LobbyConfig, _accountHashCount), L"account-hash-count", XmlCfgDef::CFG_INT, 1, nullptr, L"account hash count. 0 means system default."},
    {offsetof(LobbyConfig, _lobbyJobTransactionLifeTime), L"lobby-job-transaction-life-time", XmlCfgDef::CFG_INT, 1, &DEFAULT_LOBBY_JOB_TRANSACTION_LIFE_TIME, L"msec. life time of lobby job's transaction"},
    {offsetof(LobbyConfig, _lobbyTokenLifeTime), L"lobby-token-life-time", XmlCfgDef::CFG_INT, 1, &DEFAULT_LOBBY_TOKEN_LIFE_TIME, L"msec. life time of lobby token"},
    {offsetof(LobbyConfig, _worldInfoListUpdatePeriod), L"world-info-list-update-period", XmlCfgDef::CFG_INT, 1, &DEFAULT_UPDATE_PERIOD_OF_WORLD_INFO_LIST, L"msec. update period of world-info-list"},
    {offsetof(LobbyConfig, _stopPlayGameWorldTimeout), L"stop-play-game-world-timeout", XmlCfgDef::CFG_INT, 1, &DEFAULT_STOP_PLAY_GAME_WORLD_TIMEOUT, L"msec. timeout of waiting stop play game-world"},
    {offsetof(LobbyConfig, _checkIpMismatch), L"check-ip-mismatch", XmlCfgDef::CFG_BOOL, 1, nullptr, L"whether check ip mismatch or not"},
    {offsetof(LobbyConfig, _storeUserIpAddress), L"store-user-ip-address", XmlCfgDef::CFG_BOOL, 1, nullptr, L"사용자의 IP 주소를 D/B에 수집할지 여부. yes이면, 수집한다. 한국의 경우 '정보통신망법 시행령 개정에 따른 개인정보 유효기간 단축'으로 수집하지 않도록 설정(no)하여야 한다."},
    {offsetof(LobbyConfig, _storeGameAccountName), L"store-game-account-name", XmlCfgDef::CFG_BOOL, 1, nullptr, L"사용자의 계정명을 D/B에 수집할지 여부. yes이면, 수집한다. 한국의 경우 '정보통신망법 시행령 개정에 따른 개인정보 유효기간 단축'으로 수집하지 않도록 설정(no)하여야 한다."},
    {offsetof(LobbyConfig, _enableFriendMessageNotification), L"enable-friend-message-notification", XmlCfgDef::CFG_BOOL, 1, nullptr, L"whether enable friend message notification or not"},
    {offsetof(LobbyConfig, _friendMessageRecipientAppIdListString), L"friend-message-recipient-app-id-list", XmlCfgDef::CFG_STR, 0, DEFAULT_FIREND_MESSAGE_RECIPIENT_APP_ID_LIST, L"GUID. recipient app-id list for broadcasting message to friends. seperate by ';'. bnsclient:B0D42105-0CB6-BC9F-3CB2-BE28A0662340, bnstestclient:2F12DCE2-A63E-DF2C-1944-F2BF61049C05, plaync:206A130F-BF96-667A-4E4B-FE1A62583117, ncmessenger:452EB954-F453-3690-7C37-A810D2CC1BE5."},
    {offsetof(LobbyConfig, _enableSecondPassword), L"enable-second-password", XmlCfgDef::CFG_BOOL, 1, nullptr, L"whether enable second-password or not"},
    {offsetof(LobbyConfig, _secondPasswordType), L"second-password-type", XmlCfgDef::CFG_INT, 0, &DEFAULT_SECOND_PASSWORD_TYPE, L"type of second-password for lobby."},
    {offsetof(LobbyConfig, _enableActivityStatus), L"enable-activity-status", XmlCfgDef::CFG_BOOL, 1, nullptr, L"whether enable activity status or not"},
    {offsetof(LobbyConfig, _activityRestingStatusPeriod), L"activity-resting-status-period", XmlCfgDef::CFG_INT, 0, &DEFAULT_ACTIVITY_RESTING_STATUS_PERIOD, L"sec. period to decide resting activity status."},
    {offsetof(LobbyConfig, _activityPreRestingStatusPeriod), L"activity-pre-resting-status-period", XmlCfgDef::CFG_INT, 0, &DEFAULT_ACTIVITY_PRE_RESTING_STATUS_PERIOD, L"sec. period to decide pre-resting activity status."},
    {offsetof(LobbyConfig, _enableContentBan), L"enable-content-ban", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether enable content-ban or not."},
    {offsetof(LobbyConfig, _enableRMSInquiry), L"enable-rms-inquiry", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether enable rms-inquery or not."},
    {offsetof(LobbyConfig, _contentBanIdForJumpingCharacter), L"content-ban-id-for-jumping-character", XmlCfgDef::CFG_INT, 0, &DEFAULT_CONTENT_BAN_ID_FOR_JUMPING_CHARACTER, L"content ban id for restricting to create jumping character. 0 means no restriction"},
    {offsetof(LobbyConfig, _enableGameTimeSchedule), L"enable-game-time-schedule", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether enable game-time-schedule service or not"},
    {offsetof(LobbyConfig, _teenAgeBoundary), L"teen-age-boundary", XmlCfgDef::CFG_INT, 0, nullptr, L"age. users under this age are classified as teen. 0 means no classification needed."},
    {offsetof(LobbyConfig, _enableNpRecvCompletionLog), L"enable-np-recv-completion-log", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether enable np recv completion log or not."},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"character configuration"},
    {offsetof(LobbyConfig, _allowedCharacterNameLenMin), L"allowed-min-character-name-length", XmlCfgDef::CFG_INT, 1, &DEFAULT_ALLOWED_CHARACTER_NAME_LENGTH_MIN, L"allowed minimum length of character name"},
    {offsetof(LobbyConfig, _allowedCharacterNameLenMax), L"allowed-max-character-name-length", XmlCfgDef::CFG_INT, 1, &DEFAULT_ALLOWED_CHARACTER_NAME_LENGTH_MAX, L"allowed maximum length of character name"},
    {offsetof(LobbyConfig, _allowedCharacterNameSpaceAmount), L"allowed-character-name-space-amount", XmlCfgDef::CFG_INT, 1, &DEFAULT_ALLOWED_CHARACTER_NAME_SPACE_AMOUNT, L"allowed space amount of character name"},
    {offsetof(LobbyConfig, _characterNameReuseLimitDuration), L"character-name-reuse-limit-duration", XmlCfgDef::CFG_INT, 1, &DEFAULT_CHARACTER_NAME_REUSE_LIMIT_DURATION, L"sec. duration of forbiding recycle renamed character name"},
    {offsetof(LobbyConfig, _waitCharacterDeletion), L"wait-character-deletion", XmlCfgDef::CFG_BOOL, 1, nullptr, L"yes:wait deletion, no:direct deletion"},
    {offsetof(LobbyConfig, _shortTermWaitCharacterDeletionTime), L"short-term-character-deletion-time", XmlCfgDef::CFG_INT, 1, &DEFAULT_SHORT_TERM_WAIT_CHARACTER_DELETION_TIME, L"sec. short term wait character deletion time. below level criteria"},
    {offsetof(LobbyConfig, _longTermWaitCharacterDeletionTime), L"long-term-character-deletion-time", XmlCfgDef::CFG_INT, 1, &DEFAULT_LONG_TERM_WAIT_CHARACTER_DELETION_TIME, L"sec. long term wait character deletion time. equal to or above level criteria"},
    {offsetof(LobbyConfig, _longTermWaitCharacterDeletionCriteriaLevel), L"long-term-character-deletion-criteria-level", XmlCfgDef::CFG_INT, 1, &DEFAULT_LONG_TERM_WAIT_CHARACTER_DELETION_CRITERIA_LEVEL, L"criteria level for wait for short term or long term."},
    {offsetof(LobbyConfig, _characterDeletionSchedulerPeriod), L"character-deletion-scheduler-period", XmlCfgDef::CFG_INT, 1, &DEFAULT_CHARACTER_DELETION_SCHEDULER_PERIOD, L"sec. period of character deletion scheduler."},
    {offsetof(LobbyConfig, _characterDeletionSchedulerConcurrentProcessingCount), L"character-deletion-scheduler-concurrent-processing-count", XmlCfgDef::CFG_INT, 1, &DEFAULT_CHARACTER_DELETION_SCHEDULER_CONCURRENT_PROCESSING_COUNT, L"concurrent processing count of character deletion scheduler."},
    {offsetof(LobbyConfig, _checkCharacterGoodsForCharacterDeletion), L"check-character-goods-for-character-deletion", XmlCfgDef::CFG_BOOL, 0, nullptr, L"enable/disable check character goods for character deletion."},
    {offsetof(LobbyConfig, _maxSlotCount), L"max-slot-count", XmlCfgDef::CFG_INT, 1, &DEFAULT_MAX_SLOT_COUNT, L"max slot count."},
    {offsetof(LobbyConfig, _enableNumericForCharacterName), L"enable-numeric-for-character-name", XmlCfgDef::CFG_BOOL, 1, nullptr, L"enable/disable numeric characters for name of character."},
    {offsetof(LobbyConfig, _forceSentenceCaseForCharacterName), L"force-sentence-case-for-character-name", XmlCfgDef::CFG_BOOL, 1, nullptr, L"force sentence case for name of character."},
    {offsetof(LobbyConfig, _enableMultilingualCharacterName), L"enable-multilingual-for-character-name", XmlCfgDef::CFG_BOOL, 1, DEFAULT_TRUE, L"enable/disable multilingual for name of character."},
    {offsetof(LobbyConfig, _forbiddenCharactersForCharacterName), L"forbidden-characters-for-character-name", XmlCfgDef::CFG_STR, 0, DEFAULT_FORBIDDEN_CHARACTERS_FOR_CHARACTER_NAME, L"forbidden characters for name of character."},
    {offsetof(LobbyConfig, _enableJumpingCharacterCreation), L"enable-jumping-character-creation", XmlCfgDef::CFG_BOOL, 0, DEFAULT_TRUE, L"enable/disable jumping character creation"},
    {offsetof(LobbyConfig, _useJumpingCharacterCreationQuota), L"use-jumping-character-creation-quota", XmlCfgDef::CFG_BOOL, 0, nullptr, L"enable/disable use of jumping character creation quota. including quota checking, quota consumption"},
    {offsetof(LobbyConfig, _useJumpingCharacterCreationQuotaInWorld), L"use-jumping-character-creation-quota-in-world", XmlCfgDef::CFG_BOOL, 0, nullptr, L"enable/disable use of jumping character creation quota in world."},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"guild configuration"},
    {offsetof(LobbyConfig, _allowedGuildNameLenMin), L"allowed-min-guild-name-length", XmlCfgDef::CFG_INT, 1, &DEFAULT_ALLOWED_GUILD_NAME_LENGTH_MIN, L"allowed minimum length of guild name"},
    {offsetof(LobbyConfig, _allowedGuildNameLenMax), L"allowed-max-guild-name-length", XmlCfgDef::CFG_INT, 1, &DEFAULT_ALLOWED_GUILD_NAME_LENGTH_MAX, L"allowed maximum length of guild name"},
    {offsetof(LobbyConfig, _allowedGuildNameSpaceAmount), L"allowed-guild-name-space-amount", XmlCfgDef::CFG_INT, 1, &DEFAULT_ALLOWED_GUILD_NAME_SPACE_AMOUNT, L"allowed space amount of guild name"},
    {offsetof(LobbyConfig, _guildNameReuseLimitDuration), L"guild-name-reuse-limit-duration", XmlCfgDef::CFG_INT, 1, &DEFAULT_GUILD_NAME_REUSE_LIMIT_DURATION, L"sec. duration of forbiding recycle renamed guild name"},
    {offsetof(LobbyConfig, _enableNumericForGuildName), L"enable-numeric-for-guild-name", XmlCfgDef::CFG_BOOL, 1, nullptr, L"enable/disable numeric characters for name of guild name."},
    {offsetof(LobbyConfig, _forceSentenceCaseForGuildName), L"force-sentence-case-for-guild-name", XmlCfgDef::CFG_BOOL, 1, nullptr, L"force sentence case for name of guild name."},
    {offsetof(LobbyConfig, _enableMultilingualGuildName), L"enable-multilingual-for-guild-name", XmlCfgDef::CFG_BOOL, 1, DEFAULT_TRUE, L"enable/disable multilingual for name of guild name."},
    {offsetof(LobbyConfig, _forbiddenCharactersForGuildName), L"forbidden-characters-for-guild-name", XmlCfgDef::CFG_STR, 0, DEFAULT_FORBIDDEN_CHARACTERS_FOR_GUILD_NAME, L"forbidden characters for name of guild name."},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"user-name configuration"},
    {offsetof(LobbyConfig, _enableInitialUserName), L"initial-user-name-enable", XmlCfgDef::CFG_BOOL, 1, nullptr, L"enable/disable initial user name. Default no"},
    {offsetof(LobbyConfig, _initialUserNamePrefixString), L"initial-user-name-prefix-list", XmlCfgDef::CFG_STR, 0, DEFAULT_INITIAL_USER_NAME_PREFIX_LIST, L"initial user-name prefix list. seperated by ';'"},
    {offsetof(LobbyConfig, _allowedUserNameLenMin), L"allowed-min-user-name-length", XmlCfgDef::CFG_INT, 1, &DEFAULT_ALLOWED_USER_NAME_LENGTH_MIN, L"allowed minimum length of user name"},
    {offsetof(LobbyConfig, _allowedUserNameLenMax), L"allowed-max-user-name-length", XmlCfgDef::CFG_INT, 1, &DEFAULT_ALLOWED_USER_NAME_LENGTH_MAX, L"allowed maximum length of user name"},
    {offsetof(LobbyConfig, _forceSentenceCaseForUserName), L"force-sentence-case-for-user-name", XmlCfgDef::CFG_BOOL, 1, nullptr, L"force sentence case for name of user name."},
    {offsetof(LobbyConfig, _enableMultilingualUserName), L"enable-multilingual-for-user-name", XmlCfgDef::CFG_BOOL, 1, DEFAULT_TRUE, L"enable/disable multilingual for name of user name."},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"account inventory configuration"},
    {offsetof(LobbyConfig, _useAccountInventory), L"use-account-inventory", XmlCfgDef::CFG_BOOL, 1, nullptr, L"whether use account inventory or not"},
    {offsetof(LobbyConfig, _accountInventoryAddr), L"account-inventory-adress", XmlCfgDef::CFG_IP, 1, LOCALHOST_IP, L"account inventory ip address"},
    {offsetof(LobbyConfig, _accountInventoryPort), L"account-inventory-port", XmlCfgDef::CFG_INT, 1, &DEFAULT_ACCOUNT_INVENTORY_PORT, L"account inventory port"},
    {offsetof(LobbyConfig, _accountInventoryMaxSessionCount), L"account-inventory-max-session-count", XmlCfgDef::CFG_INT, 1, nullptr, L"0 means default account inventory session count"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"info-gate configuration"},
    {offsetof(LobbyConfig, _useInfoGate), L"use-info-gate", XmlCfgDef::CFG_BOOL, 1, nullptr, L"whether use info-gate or not"},
    {offsetof(LobbyConfig, _infoGatePort), L"info-gate-port", XmlCfgDef::CFG_INT, 0, &DEFAULT_INFO_GATE_PORT, L"info-gate listen port for lobby accept"},
    {offsetof(LobbyConfig, _infoGatePubAddr), L"info-gate-public-address", XmlCfgDef::CFG_IP, 0, LOCALHOST_IP, L"info-gate public ip address for client access"},
    {offsetof(LobbyConfig, _infoGatePubPort), L"info-gate-public-port", XmlCfgDef::CFG_INT, 0, &DEFAULT_INFO_GATE_PUBLIC_PORT, L"info-gate public port for client access"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"charge configuration"},
    {offsetof(LobbyConfig, _applyCharge), L"apply-charge", XmlCfgDef::CFG_BOOL, 1, nullptr, L"whether apply charge process or not"},
    {offsetof(LobbyConfig, _freePlayType), L"free-play-type", XmlCfgDef::CFG_INT, 1, &DEFAULT_FREE_PLAY_TYPE, L"free play type. 0:none, 1:trial, 2:F2P"},
    {offsetof(LobbyConfig, _trialPlayLimitLv), L"trial-play-limit-level", XmlCfgDef::CFG_INT, 1, &DEFAULT_TRIAL_PLAY_LIMIT_LV, L"level limitation of trial play"},
    {offsetof(LobbyConfig, _limitNoChargeInPcCafe), L"limit-not-charge-pc-cafe", XmlCfgDef::CFG_BOOL, 1, nullptr, L"whether enter world (no charge and in pc cafe and f2p) or not"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"grade configuration"},
    {offsetof(LobbyConfig, _useGrade), L"use-grade", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether use grade(yes or no)"},
    {offsetof(LobbyConfig, _useGradeLevel), L"use-grade-level", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether use grade level(yes or no)"},
    {offsetof(LobbyConfig, _gradeLevelGroupId), L"grade-level-group-id", XmlCfgDef::CFG_INT, 0, nullptr, L"grade level group id for getting grade level info. either 'grade-level-group-id' or 'game-grade-key-for-get-level' must be defined when 'use-grade-level' is 'yes'"},
    {offsetof(LobbyConfig, _gameGradeKeyForGetLevel), L"game-grade-key-for-get-level", XmlCfgDef::CFG_INT, 0, nullptr, L"game grade key for getting grade level info. either 'grade-level-group-id' or 'game-grade-key-for-get-level' must be defined when 'use-grade-level' is 'yes'"},
    {offsetof(LobbyConfig, _useGradePriorityQueue), L"use-grade-priority-queue", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether use grade priority queue(yes or no)"},
    {offsetof(LobbyConfig, _gradePriorityQueueGameGradeKey), L"grade-priority-queue-game-grade-key", XmlCfgDef::CFG_INT, 0, nullptr, L"game grade key for using grade priority queue"},
    {offsetof(LobbyConfig, _enableReloadGradeWhileReturnToLobby), L"enable-reload-grade-while-return-to-lobby", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether enable reload grade-list while return to lobby or not"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"service configuration"},
    {offsetof(LobbyConfig, _minLobbyServiceItemDataId), L"min-lobby-service-item-data-id", XmlCfgDef::CFG_INT, 1, &DEFAULT_MIN_LOBBY_SERVICE_ITEM_DATA_ID, L"min. of lobby-service-item data-id"},
    {offsetof(LobbyConfig, _maxLobbyServiceItemDataId), L"max-lobby-service-item-data-id", XmlCfgDef::CFG_INT, 1, &DEFAULT_MAX_LOBBY_SERVICE_ITEM_DATA_ID, L"max. of lobby-service-item data-id"},
    {offsetof(LobbyConfig, _itemDataIdsForChangeCharacterAppearance), L"change-character-appearance-item-data-ids", XmlCfgDef::CFG_STR, 1, DEFAULT_CHANGE_CHARACTER_APPEARANCE_ITEM_DATA_IDS, L"item data id candidates for change character appearance service. seperate by ';'"},
    {offsetof(LobbyConfig, _itemDataIdsForChangeCharacterSex), L"change-character-sex-item-data-ids", XmlCfgDef::CFG_STR, 1, DEFAULT_CHANGE_CHARACTER_SEX_ITEM_DATA_IDS, L"item data id candidates for change character sex service. seperate by ';'"},
    {offsetof(LobbyConfig, _itemDataIdsForChangeCharacterRace), L"change-character-race-item-data-ids", XmlCfgDef::CFG_STR, 1, DEFAULT_CHANGE_CHARACTER_RACE_ITEM_DATA_IDS, L"item data id candidates for change character race service. seperate by ';'"},
    {offsetof(LobbyConfig, _permitEnterWorldInChangeCharacterAppearance), L"permit-enter-world-in-change-character-appearance", XmlCfgDef::CFG_BOOL, 1, DEFAULT_TRUE, L"whether permit enter world or not for stuck character by change character appearance service"},
    {offsetof(LobbyConfig, _itemDataIdsForRenameCharacter), L"rename-character-item-data-ids", XmlCfgDef::CFG_STR, 1, DEFAULT_RENAME_CHARACTER_ITEM_DATA_IDS, L"item data id candidates for rename character service. seperate by ';'"},
    {offsetof(LobbyConfig, _itemDataIdsForRenameCharacterBySystem), L"rename-character-by-system-item-data-ids", XmlCfgDef::CFG_STR, 1, DEFAULT_RENAME_CHARACTER_BY_SYSTEM_ITEM_DATA_IDS, L"item data id candidates for rename character service by system . seperate by ';'"},
    {offsetof(LobbyConfig, _itemDataIdsForAddSlot), L"add-slot-item-data-ids", XmlCfgDef::CFG_STR, 1, DEFAULT_ADD_SLOT_ITEM_DATA_IDS, L"item data id candidates for add slot service. seperate by ';'"},
    {offsetof(LobbyConfig, _enableChangeUserNameService), L"enable-change-user-name-service", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether enable change user name service or not."},
    {offsetof(LobbyConfig, _itemDataIdsForChangeUserName), L"change-user-name-item-data-ids", XmlCfgDef::CFG_STR, 1, DEFAULT_CHANGE_USER_NAME_ITEM_DATA_IDS, L"item data id candidates for change user name. seperate by ';'"},
    {offsetof(LobbyConfig, _checkSlotCapacity), L"check-slot-capacity", XmlCfgDef::CFG_BOOL, 1, DEFAULT_TRUE, L"whether check max capacity of slot for add slot service or not."},
    {offsetof(LobbyConfig, _enableAuctionEscrowService), L"enable-auction-escrow-service", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether enable auction escrow service or not."},
    {offsetof(LobbyConfig, _auctionEscrowMinMoney), L"auction-escrow-min-money", XmlCfgDef::CFG_INT, 0, &DEFAULT_AUCTION_ESCROW_MIN_MONEY, L"minimum money for auction escrow"},
    {offsetof(LobbyConfig, _auctionEscrowUnitMoney), L"auction-escrow-unit-money", XmlCfgDef::CFG_INT, 0, &DEFAULT_AUCTION_ESCROW_UNIT_MONEY, L"unit money for auction escrow"},
    {offsetof(LobbyConfig, _auctionEscrowMoneyItemKey), L"auction-escrow-money-item-key", XmlCfgDef::CFG_STR, 0, DEFAULT_AUCTION_ESCROW_MONEY_ITEM_KEY, L"money item key for auction escrow"},
    {offsetof(LobbyConfig, _itemDataIdsForExtendJumpingCharacterCreationQuota), L"extend-jumping-character-creation-quota-item-data-ids", XmlCfgDef::CFG_STR, 1, DEFAULT_EXTEND_JUMPING_CHARACTER_CREATION_QUOTA_ITEM_DATA_IDS, L"item data id candidates for extend jumping character creation quota service. seperate by ';'"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"mileage configuration"},
    {offsetof(LobbyConfig, _enableMileage), L"enable-mileage", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether enable mileage service or not."},
    {offsetof(LobbyConfig, _mileageDepositRequestCode), L"mileage-deposit-request-code", XmlCfgDef::CFG_INT, 0, &DEFAULT_MILEAGE_DEPOSIT_REQUEST_CODE, L"mileage deposit request-code for virtual currency service. default '9'"},
    {offsetof(LobbyConfig, _mileageDepositReason), L"mileage-deposit-reason", XmlCfgDef::CFG_INT, 0, &DEFAULT_MILEAGE_DEPOSIT_REASON, L"mileage deposit-reason-code for virtual currency service. default '5'"},
    {offsetof(LobbyConfig, _mileageDepositPeriod), L"mileage-deposit-period", XmlCfgDef::CFG_INT, 0, &DEFAULT_MILEAGE_DEPOSIT_PERIOD, L"min. deposit period of mileage. 'pc-cafe' mileage only. default 30 minutes."},
    {offsetof(LobbyConfig, _mileageScheduleWeekCount), L"mileage-schedule-week-count", XmlCfgDef::CFG_INT, 0, &DEFAULT_MILEAGE_SCHEDULE_WEEK_COUNT, L"week. scheduling weeks for mileage. default 4 weeks."},
    {offsetof(LobbyConfig, _enableMileageDepositNotification), L"enable-mileage-deposit-notification", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether enable mileage deposit notification via np or not. 'pc-cafe' mileage only."},
    {offsetof(LobbyConfig, _enableMileageBatchRetryOnStartup), L"enable-mileage-batch-retry-on-startup", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether mileage deposit batch retry on startup or not."},
    {offsetof(LobbyConfig, _mileageBatchRetryConcurrentCount), L"mileage-batch-retry-concurrent-count", XmlCfgDef::CFG_INT, 0, &DEFAULT_MILEAGE_BATCH_RETRY_CONCURRENT_COUNT, L"count per tick(=timer-interval) for mileage deposit batch retry."},
    {offsetof(LobbyConfig, _enableGameMileage), L"enable-game-mileage", XmlCfgDef::CFG_BOOL, 0, nullptr, L"whether enable game-mileage or not."},
    {offsetof(LobbyConfig, _gameMileageVirtualCurrencyId), L"game-mileage-virtual-currency-id", XmlCfgDef::CFG_INT, 0, nullptr, L"virtual-currency-id for game mileage."},
    {offsetof(LobbyConfig, _gameMileageDepositRequestCode), L"game-mileage-deposit-request-code", XmlCfgDef::CFG_INT, 0, nullptr, L"deposit-request-code for game mileage."},
    {offsetof(LobbyConfig, _gameMileageDepositReasonCode), L"game-mileage-deposit-reason-code", XmlCfgDef::CFG_INT, 0, nullptr, L"deposit-reason-code for game mileage"},
    {offsetof(LobbyConfig, _gameMileageEffectiveDurationInDays), L"game-mileage-effective-duration-in-days", XmlCfgDef::CFG_INT, 0, nullptr, L"days. effectivate-duration for game-mileage. 0 means unlimited."},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"F2P configuration"},
    {offsetof(LobbyConfig, _gameCashVirtualCurrencyId), L"game-cash-virtual-currency-id", XmlCfgDef::CFG_INT, 0, nullptr, L"virtual-currency-id for game cash(bcoin free)."},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"misc. configuration"},
    {offsetof(LobbyConfig, _exportLobbyStatsFilePeriod), L"export-lobby-stats-file-period", XmlCfgDef::CFG_INT, 0, &DEFAULT_EXPORT_LOBBY_STATS_FILE_PERIOD, L"sec. export lobby stats file period. 0 means no export."},
    {offsetof(LobbyConfig, _exportLobbyStatsFilePath), L"export-lobby-stats-file-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"sec. full directory path of lobby stats file."},
    {offsetof(LobbyConfig, _usePerfMonitor), L"use-perf-monitor", XmlCfgDef::CFG_BOOL, 1, nullptr, L"where use performance monitor or not"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"tencent uic"},
    {offsetof(LobbyConfig, _tencentUICEnable), L"tencent-uic-enable", XmlCfgDef::CFG_BOOL, 0, nullptr, L"enable/disable tencent uic or not. Default no"},
    {offsetof(LobbyConfig, _tencentUICConfigFile), L"tencent-uic-config", XmlCfgDef::CFG_STR, 0, DEFAULT_TENCENT_UIC_CONFIGFILE, L"full config file name"},
    {offsetof(LobbyConfig, _tencentUICInterval), L"tencent-uic-inverval", XmlCfgDef::CFG_INT, 0, &DEFAULT_TENCENT_UIC_INTERVAL, L"tencent uic check interval : Default 10 ms"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"Configuration for logs"},
    {offsetof(LobbyConfig, _allowClientIPAddressInLogs), L"allow-client-ip-address-in-logs", XmlCfgDef::CFG_BOOL, 0, DEFAULT_TRUE, L"allow client ip address in logs"},
};
