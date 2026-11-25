// ContentsRuleConfigDefinition.obj (LobbyDaemon PDB, 2019 + PDB). Layout from the LobbyDaemon PDB (class 0x5345, size 0x18).
// LIFT: the LobbyGate class of the same name has a different layout (size 0x30). See src/Server/LobbyGate.
// This header has only the layout, the static data and the inline getters. The loaders are not lifted.
#pragma once
#include <stddef.h>

class ContentsRuleConfigLoad;

class ContentsRuleConfig
{
public:
    // PDB inline static method (no RVA). GameWorldCluster::enterUser (0x4dd90) reads Config directly.
    static ContentsRuleConfig* GetContentsRuleConfig() { return Config; }
    static bool LoadContentsRuleConfig();  // 0x297d0 (not lifted)
    static void Dump();                    // 0x29c30 (not lifted)

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
