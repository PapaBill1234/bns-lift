// ContentsRuleConfigDefinition.obj (LobbyDaemon PDB, 2019 + PDB).
// LIFT: the LobbyGate file of the same name (src/Server/LobbyGate) has a different class (13 rows, list packet).
// This file copies its patterns. It does not share code with it.
// LIFT: ContentsRuleConfigReload, ReloadContentsRuleConfig (0x29980), UpdateReloadedVariable (0x2a090),
// CompareMatch (0x2a210) and the tables ContentsRuleConfigReload::_Def (0x205a60) and _DefReload (0x205bd0)
// are not lifted. LobbyDaemon::initialize does not call them.
#include "ContentsRuleConfigDefinition.h"
#include "Daemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include <windows.h>
#include <shlwapi.h>
#include <new>
#include <wchar.h>

namespace
{
wchar_t const* const FILE_NAME = L"ContentsRuleConfigDefinition.cpp";                // LIFT: No PDB symbol. The binary uses the literal.
wchar_t const* const CONTENTS_RULE_CONFIG_FILENAME = L"ContentsRule.lobbyd.config.xml";  // ContentsRuleConfigLoad::Load (0x29690)
wchar_t const* const CONTENTS_RULE_CONFIG_MODULENAME = L"lobbyd-contents-rule-config";   // ContentsRuleConfigLoad::Load (0x29690)
int const ROW_COUNT = 7;  // LIFT: No PDB symbol. The binary uses the literal 7.
}

// Defaults, minimums and maximums. The PDB names and the values are from the globals at the RVAs.
static int const DEFAULT_DUMMY_DATA = 123;                                       // rva 0x12e1c0
static bool const DEFAULT_USE_BOT_PRIORITY_QUEUE = false;                        // rva 0x1216cb
static int const DEFAULT_MIN_BOT_SCORE_TO_APPLY_BOT_PRIORITY_QUEUE = 0x7fffffff; // rva 0x12e1c4
static bool const DEFAULT_USE_TIME_BASED_PLAY_SCHEDULE = false;                  // rva 0x129d2a
static bool const DEFAULT_ENABLE_PLAY_WARRIOR = true;                            // rva 0x129d2b
static bool const DEFAULT_ENABLE_ACCOUNT_CONTENTS = false;                       // rva 0x12b02a
static bool const DEFAULT_ENABLE_GUILD_JOIN_RENEWAL = false;                     // rva 0x12b02b

static int const MIN_DUMMY_DATA = 0;                                             // rva 0x12e1d0
static int const MAX_DUMMY_DATA = 1234;                                          // rva 0x12e1c8
static int const MIN_MIN_BOT_SCORE_TO_APPLY_BOT_PRIORITY_QUEUE = 1;              // rva 0x12e1d4
static int const MAX_MIN_BOT_SCORE_TO_APPLY_BOT_PRIORITY_QUEUE = 0x7fffffff;     // rva 0x12e1cc

ContentsRuleConfig* ContentsRuleConfig::Config = nullptr;              // rva 0x209590
ContentsRuleConfigLoad* ContentsRuleConfig::ConfigNoReload = nullptr;  // rva 0x209598
ContentsRuleConfig* ContentsRuleConfig::ConfigOlds = nullptr;          // rva 0x2095a0
int ContentsRuleConfig::ConfigReloadCount = 0;                         // rva 0x2095a8
long long ContentsRuleConfig::ConfigLastReloadTime = 0;                // rva 0x2095b0

// rva 0x205ab0. The descriptions are the binary text.
XmlCfgDef const ContentsRuleConfigLoad::_Def[7] = {
    {offsetof(ContentsRuleConfigLoad, _dummyData), L"dummy-data", XmlCfgDef::CFG_INT, XmlCfgDef::CFG_REQUIRED,
     &DEFAULT_DUMMY_DATA, L"dummy data (0 ~ 1234)"},
    {offsetof(ContentsRuleConfigLoad, _useBotPriorityQueue), L"use-bot-priority-queue", XmlCfgDef::CFG_BOOL,
     XmlCfgDef::CFG_REQUIRED, &DEFAULT_USE_BOT_PRIORITY_QUEUE, L"[LobbyDaemon] enable bot priority queue"},
    {offsetof(ContentsRuleConfigLoad, _minBotScoreToApplyBotPriorityQueue), L"min-bot-score-to-apply-bot-priority-queue",
     XmlCfgDef::CFG_INT, XmlCfgDef::CFG_REQUIRED, &DEFAULT_MIN_BOT_SCORE_TO_APPLY_BOT_PRIORITY_QUEUE,
     L"[LobbyDaemon] apply bot priority queue if botscore is greather than or equal to this value (ignored if "
     L"use-bot-priority-queue is set no) (1 ~ 2147483647)"},
    {offsetof(ContentsRuleConfigLoad, _useTimeBasedPlaySchedule), L"use-time-based-play-schedule", XmlCfgDef::CFG_BOOL,
     XmlCfgDef::CFG_REQUIRED, &DEFAULT_USE_TIME_BASED_PLAY_SCHEDULE, L"[TimeBased] TimeBased Play Schedule 사용 여부"},
    {offsetof(ContentsRuleConfigLoad, _enablePlayWarrior), L"enable-play-warrior", XmlCfgDef::CFG_BOOL,
     XmlCfgDef::CFG_REQUIRED, &DEFAULT_ENABLE_PLAY_WARRIOR, L"[Character] 투사 캐릭터 플레이 가능 여부"},
    {offsetof(ContentsRuleConfigLoad, _enableAccountContents), L"enable-account-contents", XmlCfgDef::CFG_BOOL,
     XmlCfgDef::CFG_REQUIRED, &DEFAULT_ENABLE_ACCOUNT_CONTENTS, L"[REQ] [계정컨텐츠] 계정 컨텐츠 사용 여부 (default = n)"},
    {offsetof(ContentsRuleConfigLoad, _enableGuildJoinRenewal), L"enable-guild-join-renewal", XmlCfgDef::CFG_BOOL,
     XmlCfgDef::CFG_REQUIRED, &DEFAULT_ENABLE_GUILD_JOIN_RENEWAL,
     L"[REQ] [문파 진입 개선] 문파 진입 개선 기능 사용 여부 (default=n)"},
};

// rva 0x205c40. Column reload is 1 for the two rows that _DefReload (0x205bd0) also has.
ContentsRuleXmlCfgDefLocal const ContentsRuleConfig::_Def[7] = {
    {offsetof(ContentsRuleConfig, _dummyData), L"dummy-data", XmlCfgDef::CFG_INT, 0, &MIN_DUMMY_DATA, &MAX_DUMMY_DATA,
     false, &DEFAULT_DUMMY_DATA},
    {offsetof(ContentsRuleConfig, _useBotPriorityQueue), L"use-bot-priority-queue", XmlCfgDef::CFG_BOOL, 0, nullptr,
     nullptr, true, &DEFAULT_USE_BOT_PRIORITY_QUEUE},
    {offsetof(ContentsRuleConfig, _minBotScoreToApplyBotPriorityQueue), L"min-bot-score-to-apply-bot-priority-queue",
     XmlCfgDef::CFG_INT, 0, &MIN_MIN_BOT_SCORE_TO_APPLY_BOT_PRIORITY_QUEUE, &MAX_MIN_BOT_SCORE_TO_APPLY_BOT_PRIORITY_QUEUE,
     true, &DEFAULT_MIN_BOT_SCORE_TO_APPLY_BOT_PRIORITY_QUEUE},
    {offsetof(ContentsRuleConfig, _useTimeBasedPlaySchedule), L"use-time-based-play-schedule", XmlCfgDef::CFG_BOOL, 0,
     nullptr, nullptr, false, &DEFAULT_USE_TIME_BASED_PLAY_SCHEDULE},
    {offsetof(ContentsRuleConfig, _enablePlayWarrior), L"enable-play-warrior", XmlCfgDef::CFG_BOOL, 0, nullptr, nullptr,
     false, &DEFAULT_ENABLE_PLAY_WARRIOR},
    {offsetof(ContentsRuleConfig, _enableAccountContents), L"enable-account-contents", XmlCfgDef::CFG_BOOL, 0, nullptr,
     nullptr, false, &DEFAULT_ENABLE_ACCOUNT_CONTENTS},
    {offsetof(ContentsRuleConfig, _enableGuildJoinRenewal), L"enable-guild-join-renewal", XmlCfgDef::CFG_BOOL, 0,
     nullptr, nullptr, false, &DEFAULT_ENABLE_GUILD_JOIN_RENEWAL},
};

// 0x29690
// LIFT: noinline. The orig calls it out of line from LoadContentsRuleConfig (0x297d0).
__declspec(noinline) ContentsRuleConfigLoad* ContentsRuleConfigLoad::Load()
{
    wchar_t configPath[MAX_PATH] = {0};
    PathCombineW(configPath, Daemon::Instance->confDir, CONTENTS_RULE_CONFIG_FILENAME);
    return static_cast<ContentsRuleConfigLoad*>(
        DaemonConfig::Load(_Def, ROW_COUNT, sizeof(ContentsRuleConfigLoad), configPath, CONTENTS_RULE_CONFIG_MODULENAME, false));
}

// 0x297d0
bool ContentsRuleConfig::LoadContentsRuleConfig()
{
    if (Config != nullptr)
        return false;

    void* memory = Memory::_Manager[2]->Alloc(sizeof(ContentsRuleConfig), FILE_NAME, 187);
    Config = memory != nullptr ? new (memory) ContentsRuleConfig() : nullptr;
    if (Config == nullptr)
        return false;

    ConfigNoReload = ContentsRuleConfigLoad::Load();
    if (ConfigNoReload == nullptr)
    {
        Memory::_Manager[2]->Free(Config, FILE_NAME, 194);
        Config = nullptr;
        Log::Write(Log::LT_ERROR, FILE_NAME, 196, L"[ContentsRuleConfig::LoadContentsRuleConfig], config file load failed");
        return false;
    }

    if (!CheckMinMaxBoundary(ConfigNoReload, _Def, ContentsRuleConfigLoad::_Def, ROW_COUNT))
    {
        DaemonConfig::FreeConfig(ConfigNoReload);
        ConfigNoReload = nullptr;
        Memory::_Manager[2]->Free(Config, FILE_NAME, 204);
        Config = nullptr;
        Log::Write(Log::LT_ERROR, FILE_NAME, 206, L"[ContentsRuleConfig::LoadContentsRuleConfig], boundary check failed");
        return false;
    }

    if (!Config->UpdateAllVariable(ConfigNoReload))
    {
        DaemonConfig::FreeConfig(ConfigNoReload);
        ConfigNoReload = nullptr;
        Memory::_Manager[2]->Free(Config, FILE_NAME, 214);
        Config = nullptr;
        Log::Write(Log::LT_ERROR, FILE_NAME, 216, L"[ContentsRuleConfig::LoadContentsRuleConfig], variable update failed");
        return false;
    }

    return true;
}

// 0x29c30
// LIFT: noinline. The orig calls it out of line from LobbyDaemon::initialize (0x9b300).
__declspec(noinline) void ContentsRuleConfig::Dump()
{
    ContentsRuleConfig* config = Config;
    if (config == nullptr)
        return;

    Log::Write(Log::LT_NOTICE, FILE_NAME, 334, L"[%s], %s : %u-%u, %s : %u-%u", CONTENTS_RULE_CONFIG_MODULENAME,
               L"client-version", 65, 0, L"server-version", 72, 0);
    Log::Write(Log::LT_NOTICE, FILE_NAME, 335, L"[%s], %s : %d", CONTENTS_RULE_CONFIG_MODULENAME, L"reload-count",
               ConfigReloadCount);

    char const* base = reinterpret_cast<char const*>(config);
    for (int i = 0; i < ROW_COUNT; ++i)
    {
        ContentsRuleXmlCfgDefLocal const& def = _Def[i];
        char const* field = base + def.offset;
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 345, L"[%s], %s : %d", CONTENTS_RULE_CONFIG_MODULENAME, def.name,
                       *reinterpret_cast<int const*>(field));
            break;
        case XmlCfgDef::CFG_INT64:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 346, L"[%s], %s : %I64d", CONTENTS_RULE_CONFIG_MODULENAME, def.name,
                       *reinterpret_cast<long long const*>(field));
            break;
        case XmlCfgDef::CFG_FLOAT:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 347, L"[%s], %s : %f", CONTENTS_RULE_CONFIG_MODULENAME, def.name,
                       static_cast<double>(*reinterpret_cast<float const*>(field)));
            break;
        case XmlCfgDef::CFG_BOOL:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 348, L"[%s], %s : %s", CONTENTS_RULE_CONFIG_MODULENAME, def.name,
                       *field != 0 ? L"yes" : L"no");
            break;
        case XmlCfgDef::CFG_STR:
        {
            wchar_t const* value = reinterpret_cast<wchar_t const*>(field);
            if (value == nullptr || *value == 0)
                value = L"N/A";
            Log::Write(Log::LT_NOTICE, FILE_NAME, 352, L"[%s], %s : %s", CONTENTS_RULE_CONFIG_MODULENAME, def.name, value);
            break;
        }
        default:
            break;
        }
    }
}

// 0x29e30
bool ContentsRuleConfig::CheckMinMaxBoundary(void const* const loaded, ContentsRuleXmlCfgDefLocal const* defList,
                                             XmlCfgDef const* loadDefList, int defCount)
{
    if (loaded == nullptr)
        return false;

    char const* base = static_cast<char const*>(loaded);
    bool result = true;
    for (int i = 0; i < defCount; ++i)
    {
        ContentsRuleXmlCfgDefLocal const& def = defList[i];
        char const* field = base + loadDefList[i].offset;
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
        {
            int value = *reinterpret_cast<int const*>(field);
            int minValue = *static_cast<int const*>(def.minValue);
            int maxValue = *static_cast<int const*>(def.maxValue);
            if (value < minValue || value > maxValue)
            {
                Log::Write(Log::LT_ERROR, FILE_NAME, 382,
                           L"[ContentsRuleConfig::CheckMinMaxBoundary], value outranged, name:%s, value:%d, min:%d, max:%d",
                           def.name, value, minValue, maxValue);
                result = false;
            }
            break;
        }
        case XmlCfgDef::CFG_INT64:
        {
            long long value = *reinterpret_cast<long long const*>(field);
            long long minValue = *static_cast<long long const*>(def.minValue);
            long long maxValue = *static_cast<long long const*>(def.maxValue);
            if (value < minValue || value > maxValue)
            {
                Log::Write(Log::LT_ERROR, FILE_NAME, 390,
                           L"[ContentsRuleConfig::CheckMinMaxBoundary], value outranged, name:%s, value:%I64d, min:%I64d, max:%I64d",
                           def.name, value, minValue, maxValue);
                result = false;
            }
            break;
        }
        case XmlCfgDef::CFG_FLOAT:
        {
            float value = *reinterpret_cast<float const*>(field);
            float minValue = *static_cast<float const*>(def.minValue);
            float maxValue = *static_cast<float const*>(def.maxValue);
            if (minValue > value || value > maxValue)
            {
                Log::Write(Log::LT_ERROR, FILE_NAME, 398,
                           L"[ContentsRuleConfig::CheckMinMaxBoundary], value outranged, name:%s, value:%f, min:%f, max:%f",
                           def.name, static_cast<double>(value), static_cast<double>(minValue),
                           static_cast<double>(maxValue));
                result = false;
            }
            break;
        }
        default:
            break;
        }
    }
    return result;
}

// 0x29fa0
bool ContentsRuleConfig::UpdateAllVariable(ContentsRuleConfigLoad const* const load)
{
    // LIFT: LTCG put the globals Config and ConfigNoReload in place of this and load (one caller, 0x297d0).
    if (load == nullptr)
        return false;

    char* dst = reinterpret_cast<char*>(this);
    char const* src = reinterpret_cast<char const*>(load);
    // LIFT: count down with pointer steps, as the original (0x29fa0, counter 7). Same as BnsCommonConfig.
    XmlCfgDef const* loadDefPtr = ContentsRuleConfigLoad::_Def;
    ContentsRuleXmlCfgDefLocal const* defPtr = _Def;
    for (int i = ROW_COUNT; i != 0; --i, ++defPtr, ++loadDefPtr)
    {
        ContentsRuleXmlCfgDefLocal const& def = *defPtr;
        XmlCfgDef const& loadDef = *loadDefPtr;
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
        case XmlCfgDef::CFG_FLOAT:
            *reinterpret_cast<int*>(dst + def.offset) = *reinterpret_cast<int const*>(src + loadDef.offset);
            break;
        case XmlCfgDef::CFG_INT64:
            *reinterpret_cast<long long*>(dst + def.offset) = *reinterpret_cast<long long const*>(src + loadDef.offset);
            break;
        case XmlCfgDef::CFG_BOOL:
            *reinterpret_cast<bool*>(dst + def.offset) = *reinterpret_cast<bool const*>(src + loadDef.offset);
            break;
        case XmlCfgDef::CFG_STR:
        {
            wchar_t const* value = *reinterpret_cast<wchar_t const* const*>(src + loadDef.offset);
            wcscpy_s(reinterpret_cast<wchar_t*>(dst + def.offset), 260, value != nullptr ? value : L"");  // HR: valueString
            break;
        }
        default:
            break;
        }
    }
    return true;
}
