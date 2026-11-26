// ContentsRuleConfigDefinition.obj (LobbyDaemon PDB, 2019 + PDB). Layout from the LobbyDaemon PDB (class 0x5345, size 0x18).
// LIFT: the LobbyGate class of the same name has a different layout (size 0x30). See src/Server/LobbyGate.
// The loaders on the LobbyDaemon::initialize path are lifted. Reload, UpdateReloadedVariable and CompareMatch are not.
#pragma once
#include <stddef.h>
#include "DaemonConfig.h"

// PDB: ContentsRuleConfig::_Def (rva 0x205c40) and _DefReload (rva 0x205bd0) have rows of 0x38 bytes.
// 0x205c40 - 0x205bd0 = 0x70 = 2 rows. Dump (0x29c30) steps 7 qwords per row.
// The XmlCfgDefLocal of the common code (PDB 0x24D7) has sizeof 0x40 (it has refOffset).
// LIFT: the name ContentsRuleXmlCfgDefLocal keeps the 0x38 row apart from the common XmlCfgDefLocal (as in LobbyGate).
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

// PDB class 0x5326, size 0x10.
class ContentsRuleConfigLoad
{
public:
    static ContentsRuleConfigLoad* Load();  // 0x29690

    static XmlCfgDef const _Def[7];  // rva 0x205ab0

    int _dummyData;                           // +0
    bool _useBotPriorityQueue;                // +4
    int _minBotScoreToApplyBotPriorityQueue;  // +8
    bool _useTimeBasedPlaySchedule;           // +12
    bool _enablePlayWarrior;                  // +13
    bool _enableAccountContents;              // +14
    bool _enableGuildJoinRenewal;             // +15
};
static_assert(sizeof(ContentsRuleConfigLoad) == 0x10, "sizeof ContentsRuleConfigLoad");
static_assert(offsetof(ContentsRuleConfigLoad, _minBotScoreToApplyBotPriorityQueue) == 0x8,
              "ContentsRuleConfigLoad::_minBotScoreToApplyBotPriorityQueue");
static_assert(offsetof(ContentsRuleConfigLoad, _enableGuildJoinRenewal) == 0xF, "ContentsRuleConfigLoad::_enableGuildJoinRenewal");

// LobbyDaemon PDB: sizeof 8. The LobbyGate class of the same name is empty (sizeof 1). See src/Server/LobbyGate.
class ContentsRuleConfigReload
{
public:
    static ContentsRuleConfigReload* Load();  // 0x29730 (not lifted)

    bool _useBotPriorityQueue;
    int _minBotScoreToApplyBotPriorityQueue;
};
static_assert(sizeof(ContentsRuleConfigReload) == 0x8, "sizeof ContentsRuleConfigReload");
static_assert(offsetof(ContentsRuleConfigReload, _minBotScoreToApplyBotPriorityQueue) == 0x4,
              "ContentsRuleConfigReload::_minBotScoreToApplyBotPriorityQueue");

class ContentsRuleConfig
{
public:
    // PDB inline static method (no RVA). GameWorldCluster::enterUser (0x4dd90) reads Config directly.
    static ContentsRuleConfig* GetContentsRuleConfig() { return Config; }
    static bool LoadContentsRuleConfig();  // 0x297d0
    static void Dump();                    // 0x29c30

    // PDB inline constructor (no RVA). LoadContentsRuleConfig (0x297d0) writes the zeros after Alloc.
    ContentsRuleConfig()
        : _NEXT(nullptr),
          _dummyData(0),
          _useBotPriorityQueue(false),
          _minBotScoreToApplyBotPriorityQueue(0),
          _useTimeBasedPlaySchedule(false),
          _enablePlayWarrior(false),
          _enableAccountContents(false),
          _enableGuildJoinRenewal(false)
    {
    }

    ContentsRuleConfig* _NEXT;  // +0

    // PDB inline methods (no RVA).
    int GetDummyData() const { return _dummyData; }
    bool GetUseBotPriorityQueue() const { return _useBotPriorityQueue; }
    int GetMinBotScoreToApplyBotPriorityQueue() const { return _minBotScoreToApplyBotPriorityQueue; }
    bool GetUseTimeBasedPlaySchedule() const { return _useTimeBasedPlaySchedule; }
    bool GetEnablePlayWarrior() const { return _enablePlayWarrior; }
    bool GetEnableAccountContents() const { return _enableAccountContents; }
    bool GetEnableGuildJoinRenewal() const { return _enableGuildJoinRenewal; }

private:
    static ContentsRuleConfig* Config;              // rva 0x209590
    static ContentsRuleConfigLoad* ConfigNoReload;  // rva 0x209598
    static ContentsRuleConfig* ConfigOlds;          // rva 0x2095a0
    static int ConfigReloadCount;                   // rva 0x2095a8
    static long long ConfigLastReloadTime;          // rva 0x2095b0
    static ContentsRuleXmlCfgDefLocal const _Def[7];  // rva 0x205c40

    static bool CheckMinMaxBoundary(void const* const loaded, ContentsRuleXmlCfgDefLocal const* defList,
                                    XmlCfgDef const* loadDefList, int defCount);  // 0x29e30
    bool UpdateAllVariable(ContentsRuleConfigLoad const* const loaded);          // 0x29fa0

    int _dummyData;                           // +8
    bool _useBotPriorityQueue;                // +12
    int _minBotScoreToApplyBotPriorityQueue;  // +16
    bool _useTimeBasedPlaySchedule;           // +20
    bool _enablePlayWarrior;                  // +21
    bool _enableAccountContents;              // +22
    bool _enableGuildJoinRenewal;             // +23

    friend struct ContentsRuleConfigLayoutCheck;
};

// LIFT: access helper for the layout checks of the private members. Not in the PDB.
struct ContentsRuleConfigLayoutCheck
{
    static_assert(sizeof(ContentsRuleConfig) == 0x18, "sizeof ContentsRuleConfig");
    static_assert(offsetof(ContentsRuleConfig, _dummyData) == 0x8, "ContentsRuleConfig::_dummyData");
    static_assert(offsetof(ContentsRuleConfig, _useBotPriorityQueue) == 0xC, "ContentsRuleConfig::_useBotPriorityQueue");
    static_assert(offsetof(ContentsRuleConfig, _minBotScoreToApplyBotPriorityQueue) == 0x10,
                  "ContentsRuleConfig::_minBotScoreToApplyBotPriorityQueue");
    static_assert(offsetof(ContentsRuleConfig, _useTimeBasedPlaySchedule) == 0x14, "ContentsRuleConfig::_useTimeBasedPlaySchedule");
    static_assert(offsetof(ContentsRuleConfig, _enableGuildJoinRenewal) == 0x17, "ContentsRuleConfig::_enableGuildJoinRenewal");
};
