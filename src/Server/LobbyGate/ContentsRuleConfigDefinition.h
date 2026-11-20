// ContentsRuleConfigDefinition.obj (LobbyGate PDB). Layouts from include/pdb/LobbyGate/types.h lines 1862-1925.
#pragma once
#include <stddef.h>
#include "DaemonConfig.h"

class FragmentPacket;
struct FragmentPacketWrap;

// PDB: ContentsRuleConfig::_Def (0x140092a60) has type 0x2E86, an array of const XmlCfgDefLocal (0x2697) of 728 bytes.
// 728 = 13 rows of 0x38. The XmlCfgDefLocal of the common code (0x26BA) has sizeof 64 (it has refOffset).
// LIFT: the name ContentsRuleXmlCfgDefLocal keeps the 0x38 row apart from the common XmlCfgDefLocal.
struct ContentsRuleXmlCfgDefLocal
{
    unsigned long long offset;
    wchar_t const* name;
    int type;
    int defType;
    void const* minValue;
    void const* maxValue;
    bool reload;
    void const* defaultValue;
};
static_assert(sizeof(ContentsRuleXmlCfgDefLocal) == 0x38, "sizeof ContentsRuleXmlCfgDefLocal");

class ContentsRuleConfigLoad
{
public:
    int _dummyData;
    bool _useTimeBasedPlaySchedule;
    bool _enablePlayWarrior;
    bool _enableFishSystem;
    bool _enableAccountContents;
    int _accountContentsRequiredPcLevel;
    int _accountContentsRequiredPcMasteryLevel;
    int _accountContentsRequiredAccountTopPcLevel;
    int _accountContentsRequiredAccountTopPcMasteryLevel;
    int _accountExpQuotaPerDay;
    int _accountExpQuotaResetTime;
    int _accountLevelMax;
    bool _enableGuildJoinRenewal;

    static ContentsRuleConfigLoad* Load();  // 0x8220

    static XmlCfgDef const _Def[13];  // 0x140092850
};
static_assert(sizeof(ContentsRuleConfigLoad) == 0x28, "sizeof ContentsRuleConfigLoad");
static_assert(offsetof(ContentsRuleConfigLoad, _enableGuildJoinRenewal) == 0x24, "ContentsRuleConfigLoad::_enableGuildJoinRenewal");

// LobbyDaemon only (2019 + PDB). LobbyGate does not use this class.
class ContentsRuleConfigReload
{
public:
    bool _useBotPriorityQueue;
    int _minBotScoreToApplyBotPriorityQueue;

    static ContentsRuleConfigReload* Load();  // 0x29730 (LobbyDaemon)
};
static_assert(sizeof(ContentsRuleConfigReload) == 0x8, "sizeof ContentsRuleConfigReload");
static_assert(offsetof(ContentsRuleConfigReload, _minBotScoreToApplyBotPriorityQueue) == 0x4,
              "ContentsRuleConfigReload::_minBotScoreToApplyBotPriorityQueue");

class ContentsRuleConfig
{
public:
    ContentsRuleConfig* _NEXT;
    int _dummyData;
    bool _useTimeBasedPlaySchedule;
    bool _enablePlayWarrior;
    bool _enableFishSystem;
    bool _enableAccountContents;
    int _accountContentsRequiredPcLevel;
    int _accountContentsRequiredPcMasteryLevel;
    int _accountContentsRequiredAccountTopPcLevel;
    int _accountContentsRequiredAccountTopPcMasteryLevel;
    int _accountExpQuotaPerDay;
    int _accountExpQuotaResetTime;
    int _accountLevelMax;
    bool _enableGuildJoinRenewal;

    // Inline constructor. The binary writes it in LoadContentsRuleConfig.
    ContentsRuleConfig()
        : _NEXT(nullptr), _dummyData(0), _useTimeBasedPlaySchedule(false), _enablePlayWarrior(false),
          _enableFishSystem(false), _enableAccountContents(false), _accountContentsRequiredPcLevel(0),
          _accountContentsRequiredPcMasteryLevel(0), _accountContentsRequiredAccountTopPcLevel(0),
          _accountContentsRequiredAccountTopPcMasteryLevel(0), _accountExpQuotaPerDay(0),
          _accountExpQuotaResetTime(0), _accountLevelMax(0), _enableGuildJoinRenewal(false)
    {
    }

    static bool LoadContentsRuleConfig();     // 0x82c0
    static void DestroyContentsRuleConfig();  // 0x84d0
    static void Dump();                       // 0x8600
    static bool ReloadContentsRuleConfig(bool& changed, bool& isNotify);  // 0x29980 (LobbyDaemon)

    static FragmentPacket* ListPacket;              // 0x93f68
    static FragmentPacketWrap* ListPacketOlds;      // 0x93f70
    static ContentsRuleConfig* Config;              // 0x93f78
    static ContentsRuleConfigLoad* ConfigNoReload;  // 0x93f80
    static ContentsRuleConfig* ConfigOlds;          // 0x93f88
    static int ConfigReloadCount;                   // 0x93f90
    static long long ConfigLastReloadTime;          // 0x93f98
    static ContentsRuleXmlCfgDefLocal const _Def[13];  // 0x140092a60

private:
    static FragmentPacket* MakeListPacket(ContentsRuleConfig* config);  // 0x8800
    static bool ConvPacketElement(char* utf8Name, char* utf8Value, wchar_t const* name,
                                  wchar_t const* value);  // 0x8ce0
    static bool CheckMinMaxBoundary(void const* const loaded, ContentsRuleXmlCfgDefLocal const* defList,
                                    XmlCfgDef const* loadDefList, int defCount);  // 0x8ef0
    bool UpdateAllVariable(ContentsRuleConfigLoad const* const loaded);         // 0x9060
    bool UpdateReloadedVariable(ContentsRuleConfigReload const* const reload, bool& isNotify);  // 0x2a090 (LobbyDaemon)
    bool CompareMatch(ContentsRuleConfigReload const* reload) const;  // 0x2a210 (LobbyDaemon)
};
static_assert(sizeof(ContentsRuleConfig) == 0x30, "sizeof ContentsRuleConfig");
static_assert(offsetof(ContentsRuleConfig, _dummyData) == 0x8, "ContentsRuleConfig::_dummyData");
static_assert(offsetof(ContentsRuleConfig, _enableGuildJoinRenewal) == 0x2C, "ContentsRuleConfig::_enableGuildJoinRenewal");
