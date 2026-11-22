// LobbyConfig.obj (LobbyDaemon PDB, 2019 + PDB).
// LIFT: the field layout is from include/pdb/LobbyDaemon/types.h (sizeof 0x298). The XML table _Def is not here yet.
#pragma once
#include <stddef.h>

union id128;

class LobbyConfig
{
public:
    enum DumpType : int
    {
        DUMP_NONE = 0,
        DUMP_MINIMAL = 1,
        DUMP_FULL = 2,
        DUMP_MAX = 3,
    };
    enum FreePlayType : int
    {
        FREEPLAYTYPE_NONE = 0,
        FREEPLAYTYPE_TRIAL = 1,
        FREEPLAYTYPE_F2P = 2,
    };
    struct InitialUserNamePrefix
    {
        wchar_t* prefix;
        int len;
    };

    bool Check() const;  // 0x98980
    void Reload();  // 0x990f0

    wchar_t* _rootPath;
    wchar_t* _logPath;
    wchar_t* _configPath;
    wchar_t* _dataPath;
    char* _certFile;
    int _workerThreadCount;
    int _dumpType;
    int _timerInterval;
    int _timerMaxTime;
    int _reuseWaitTime;
    int _reservedMinLobbyGateWidRange;
    int _reservedMaxLobbyGateWidRange;
    int _reservedMinGameWorldWidRange;
    int _reservedMaxGameWorldWidRange;
    int _reservedMinInfoGateWidRange;
    int _reservedMaxInfoGateWidRange;
    int _typeForFailedEventObjectLog;
    int _maxNPSessionCount;
    int _maxLobbyGateSessionCount;
    int _maxInfoGateSessionCount;
    int _maxGameWorldSessionCount;
    int _maxManageSessionCount;
    int _maxPostOfficeSessionCount;
    unsigned long _npAddr;
    int _npPort;
    int _worldPort;
    int _lobbyGatePort;
    int _infoGatePort;
    int _managePort;
    int _postOfficeAddr;
    int _postOfficePort;
    wchar_t* _supportLanguages;
    int _worldId;
    int _cliSessionHashCount;
    int _initCliSessionCount;
    int _lobbyJobHashCount;
    int _initLobbyJobCount;
    int _accountHashCount;
    int _lobbyJobTransactionLifeTime;
    int _lobbyTokenLifeTime;
    int _worldInfoListUpdatePeriod;
    int _stopPlayGameWorldTimeout;
    bool _checkIpMismatch;
    bool _storeUserIpAddress;
    bool _storeGameAccountName;
    int _allowedCharacterNameLenMin;
    int _allowedCharacterNameLenMax;
    int _allowedCharacterNameSpaceAmount;
    int _characterNameReuseLimitDuration;
    bool _waitCharacterDeletion;
    int _shortTermWaitCharacterDeletionTime;
    int _longTermWaitCharacterDeletionTime;
    int _longTermWaitCharacterDeletionCriteriaLevel;
    int _characterDeletionSchedulerPeriod;
    int _characterDeletionSchedulerConcurrentProcessingCount;
    bool _checkCharacterGoodsForCharacterDeletion;
    int _maxSlotCount;
    bool _enableNumericForCharacterName;
    bool _forceSentenceCaseForCharacterName;
    bool _enableMultilingualCharacterName;
    wchar_t* _forbiddenCharactersForCharacterName;
    bool _enableJumpingCharacterCreation;
    bool _useJumpingCharacterCreationQuota;
    bool _useJumpingCharacterCreationQuotaInWorld;
    int _allowedGuildNameLenMin;
    int _allowedGuildNameLenMax;
    int _allowedGuildNameSpaceAmount;
    int _guildNameReuseLimitDuration;
    bool _enableNumericForGuildName;
    bool _forceSentenceCaseForGuildName;
    bool _enableMultilingualGuildName;
    wchar_t* _forbiddenCharactersForGuildName;
    bool _enableInitialUserName;
    int _allowedUserNameLenMin;
    int _allowedUserNameLenMax;
    bool _forceSentenceCaseForUserName;
    bool _enableMultilingualUserName;
    bool _useAccountInventory;
    int _accountInventoryAddr;
    int _accountInventoryPort;
    int _accountInventoryMaxSessionCount;
    bool _useInfoGate;
    int _infoGatePubAddr;
    int _infoGatePubPort;
    bool _applyCharge;
    int _freePlayType;
    int _trialPlayLimitLv;
    bool _limitNoChargeInPcCafe;
    bool _useGrade;
    bool _useGradeLevel;
    int _gradeLevelGroupId;
    int _gameGradeKeyForGetLevel;
    bool _useGradePriorityQueue;
    int _gradePriorityQueueGameGradeKey;
    bool _enableReloadGradeWhileReturnToLobby;
    int _minLobbyServiceItemDataId;
    int _maxLobbyServiceItemDataId;
    wchar_t* _itemDataIdsForChangeCharacterAppearance;
    wchar_t* _itemDataIdsForChangeCharacterSex;
    wchar_t* _itemDataIdsForChangeCharacterRace;
    bool _permitEnterWorldInChangeCharacterAppearance;
    wchar_t* _itemDataIdsForRenameCharacter;
    wchar_t* _itemDataIdsForRenameCharacterBySystem;
    wchar_t* _itemDataIdsForAddSlot;
    bool _checkSlotCapacity;
    bool _enableChangeUserNameService;
    wchar_t* _itemDataIdsForChangeUserName;
    bool _enableAuctionEscrowService;
    int _auctionEscrowMinMoney;
    int _auctionEscrowUnitMoney;
    wchar_t* _auctionEscrowMoneyItemKey;
    wchar_t* _itemDataIdsForExtendJumpingCharacterCreationQuota;
    bool _enableMileage;
    int _mileageDepositRequestCode;
    int _mileageDepositReason;
    int _mileageDepositPeriod;
    int _mileageScheduleWeekCount;
    bool _enableMileageDepositNotification;
    bool _enableMileageBatchRetryOnStartup;
    int _mileageBatchRetryConcurrentCount;
    bool _enableGameMileage;
    int _gameMileageVirtualCurrencyId;
    int _gameMileageDepositRequestCode;
    int _gameMileageDepositReasonCode;
    int _gameMileageEffectiveDurationInDays;
    int _gameCashVirtualCurrencyId;
    int _exportLobbyStatsFilePeriod;
    wchar_t* _exportLobbyStatsFilePath;
    bool _usePerfMonitor;
    LobbyConfig::InitialUserNamePrefix* _initialUserNamePrefixList;
    int _initialUserNamePrefixCount;
    wchar_t* _initialUserNamePrefixString;
    bool _tencentUICEnable;
    wchar_t* _tencentUICConfigFile;
    int _tencentUICInterval;
    bool _enableFriendMessageNotification;
    wchar_t* _friendMessageRecipientAppIdListString;
    id128* _friendMessageRecipientAppIdList;
    int _friendMessageRecipientAppIdCount;
    bool _enableSecondPassword;
    int _secondPasswordType;
    bool _enableActivityStatus;
    int _activityRestingStatusPeriod;
    int _activityPreRestingStatusPeriod;
    bool _enableContentBan;
    bool _enableRMSInquiry;
    int _contentBanIdForJumpingCharacter;
    bool _enableGameTimeSchedule;
    int _teenAgeBoundary;
    bool _enableNpRecvCompletionLog;
    bool _allowClientIPAddressInLogs;
};
static_assert(sizeof(LobbyConfig) == 0x298, "sizeof LobbyConfig");
static_assert(offsetof(LobbyConfig, _rootPath) == 0x0, "LobbyConfig::_rootPath");
static_assert(offsetof(LobbyConfig, _logPath) == 0x8, "LobbyConfig::_logPath");
static_assert(offsetof(LobbyConfig, _configPath) == 0x10, "LobbyConfig::_configPath");
static_assert(offsetof(LobbyConfig, _dataPath) == 0x18, "LobbyConfig::_dataPath");
