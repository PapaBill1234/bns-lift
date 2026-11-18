// ContentsRuleConfigDefinition.obj (LobbyGate PDB).
#include "ContentsRuleConfigDefinition.h"
#include "FragmentPacket.h"
#include "Daemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include <windows.h>
#include <shlwapi.h>
#include <new>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

namespace
{
wchar_t const* const FILE_NAME = L"ContentsRuleConfigDefinition.cpp";        // LIFT: No PDB symbol. The binary uses the literal.
wchar_t const* const CONTENTS_RULE_CONFIG_FILENAME = L"ContentsRule.lobbygate.config.xml";  // rva 0x91328
wchar_t const* const CONTENTS_RULE_CONFIG_MODULENAME = L"lobbygate-contents-rule-config";  // rva 0x91330
int const ROW_COUNT = 13;           // LIFT: No PDB symbol. The binary uses the literal.
}

// Defaults, minimums and maximums. The PDB names are from the globals at the addresses.
static int const DEFAULT_DUMMY_DATA = 123;                                           // 0x14006e354
static bool const DEFAULT_USE_TIME_BASED_PLAY_SCHEDULE = false;                      // 0x14006324b
static bool const DEFAULT_ENABLE_PLAY_WARRIOR = true;                                // 0x14006b8aa
static bool const DEFAULT_ENABLE_FISH_SYSTEM = false;                                // 0x14006b8ab
static bool const DEFAULT_ENABLE_ACCOUNT_CONTENTS = false;                           // 0x14006cbaa
static int const DEFAULT_ACCOUNT_CONTENTS_REQUIRED_PC_LEVEL = 0;                     // 0x14006e358
static int const DEFAULT_ACCOUNT_CONTENTS_REQUIRED_PC_MASTERY_LEVEL = 0;             // 0x14006e3cc
static int const DEFAULT_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_LEVEL = 0;         // 0x14006e9a8
static int const DEFAULT_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_MASTERY_LEVEL = 0; // 0x14006f3ec
static int const DEFAULT_ACCOUNT_EXP_QUOTA_PER_DAY = 0;                              // 0x14006f400
static int const DEFAULT_ACCOUNT_EXP_QUOTA_RESET_TIME = 6;                           // 0x14006f404
static int const DEFAULT_ACCOUNT_LEVEL_MAX = 50;                                     // 0x14006f408
static bool const DEFAULT_ENABLE_GUILD_JOIN_RENEWAL = false;                         // 0x14006cbab

static int const MIN_DUMMY_DATA = 0;                                                 // 0x14006f42c
static int const MAX_DUMMY_DATA = 1234;                                              // 0x14006f40c
static int const MIN_ACCOUNT_CONTENTS_REQUIRED_PC_LEVEL = 0;                         // 0x14006f430
static int const MAX_ACCOUNT_CONTENTS_REQUIRED_PC_LEVEL = 1000;                      // 0x14006f410
static int const MIN_ACCOUNT_CONTENTS_REQUIRED_PC_MASTERY_LEVEL = 0;                 // 0x14006f434
static int const MAX_ACCOUNT_CONTENTS_REQUIRED_PC_MASTERY_LEVEL = 1000;              // 0x14006f414
static int const MIN_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_LEVEL = 0;             // 0x14006f438
static int const MAX_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_LEVEL = 1000;          // 0x14006f418
static int const MIN_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_MASTERY_LEVEL = 0;     // 0x14006f43c
static int const MAX_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_MASTERY_LEVEL = 1000;  // 0x14006f41c
static int const MIN_ACCOUNT_EXP_QUOTA_PER_DAY = 0;                                  // 0x14006f440
static int const MAX_ACCOUNT_EXP_QUOTA_PER_DAY = 0x7fffffff;                         // 0x14006f420
static int const MIN_ACCOUNT_EXP_QUOTA_RESET_TIME = 0;                               // 0x14006f444
static int const MAX_ACCOUNT_EXP_QUOTA_RESET_TIME = 23;                              // 0x14006f424
static int const MIN_ACCOUNT_LEVEL_MAX = 0;                                          // 0x14006f448
static int const MAX_ACCOUNT_LEVEL_MAX = 1000;                                       // 0x14006f428

FragmentPacket* ContentsRuleConfig::ListPacket = nullptr;              // 0x93f68
FragmentPacketWrap* ContentsRuleConfig::ListPacketOlds = nullptr;      // 0x93f70
ContentsRuleConfig* ContentsRuleConfig::Config = nullptr;              // 0x93f78
ContentsRuleConfigLoad* ContentsRuleConfig::ConfigNoReload = nullptr;  // 0x93f80
ContentsRuleConfig* ContentsRuleConfig::ConfigOlds = nullptr;          // 0x93f88
int ContentsRuleConfig::ConfigReloadCount = 0;                         // 0x93f90
long long ContentsRuleConfig::ConfigLastReloadTime = 0;                // 0x93f98

// The descriptions are the binary text (rva 0x71780 .. 0x71fd8).
// 0x140092850
XmlCfgDef const ContentsRuleConfigLoad::_Def[13] = {
    {offsetof(ContentsRuleConfigLoad, _dummyData), L"dummy-data", XmlCfgDef::CFG_INT, 1, &DEFAULT_DUMMY_DATA,
     L"dummy data (0 ~ 1234)"},
    {offsetof(ContentsRuleConfigLoad, _useTimeBasedPlaySchedule), L"use-time-based-play-schedule", XmlCfgDef::CFG_BOOL, 1,
     &DEFAULT_USE_TIME_BASED_PLAY_SCHEDULE, L"[TimeBased] TimeBased Play Schedule 사용 여부"},
    {offsetof(ContentsRuleConfigLoad, _enablePlayWarrior), L"enable-play-warrior", XmlCfgDef::CFG_BOOL, 1,
     &DEFAULT_ENABLE_PLAY_WARRIOR, L"[Character] 투사 캐릭터 플레이 가능 여부"},
    {offsetof(ContentsRuleConfigLoad, _enableFishSystem), L"enable-fish-system", XmlCfgDef::CFG_BOOL, 1,
     &DEFAULT_ENABLE_FISH_SYSTEM, L"[REQ] [낚시] 낚시 사용 여부 (default = n)"},
    {offsetof(ContentsRuleConfigLoad, _enableAccountContents), L"enable-account-contents", XmlCfgDef::CFG_BOOL, 1,
     &DEFAULT_ENABLE_ACCOUNT_CONTENTS, L"[REQ] [계정컨텐츠] 계정 컨텐츠 사용 여부 (default = n)"},
    {offsetof(ContentsRuleConfigLoad, _accountContentsRequiredPcLevel), L"account-contents-required-pc-level",
     XmlCfgDef::CFG_INT, 1, &DEFAULT_ACCOUNT_CONTENTS_REQUIRED_PC_LEVEL,
     L"[REQ] [계정컨텐츠] 계정 컨텐츠를 이용 가능한 최소 캐릭터 레벨. 계정 경험치 누적, 계정 등급 혜텍 적용 조건. account-contents-required-pc-mastery-level > 0이면, rule config의 pc-level-max 값과 동일해야한다.(default : 0) (0 ~ 1000)"},
    {offsetof(ContentsRuleConfigLoad, _accountContentsRequiredPcMasteryLevel),
     L"account-contents-required-pc-mastery-level", XmlCfgDef::CFG_INT, 1,
     &DEFAULT_ACCOUNT_CONTENTS_REQUIRED_PC_MASTERY_LEVEL, L"[REQ] [계정컨텐츠] 계정 컨텐츠를 이용 가능한 최소 캐릭터 Mastery 레벨. 계정 경험치 누적, 계정 등급 혜텍 적용 조건. 값이 0이면 체크하지 않는다. (default : 0) (0 ~ 1000)"},
    {offsetof(ContentsRuleConfigLoad, _accountContentsRequiredAccountTopPcLevel),
     L"account-contents-required-account-top-pc-level", XmlCfgDef::CFG_INT, 1,
     &DEFAULT_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_LEVEL,
     L"[REQ] [계정컨텐츠] 계정 컨텐츠를 이용하기 위해 보유해야하는 계정 내 캐릭터의 레벨 값. 계정 경험치 누적, 계정 등급 혜텍 적용 조건. account-contents-required-account-top-pc-mastery-level > 0이면, rule config의 pc-level-max 값과 동일해야한다.(default : 0) (0 ~ 1000)"},
    {offsetof(ContentsRuleConfigLoad, _accountContentsRequiredAccountTopPcMasteryLevel),
     L"account-contents-required-account-top-pc-mastery-level", XmlCfgDef::CFG_INT, 1,
     &DEFAULT_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_MASTERY_LEVEL,
     L"[REQ] [계정컨텐츠] 계정 컨텐츠를 이용하기 위해 보유해야하는 계정 내 캐릭터의 Mastery 레벨 값. 계정 경험치 누적, 계정 등급 혜텍 적용 조건. 값이 0이면 체크하지 않는다. (default : 0) (0 ~ 1000)"},
    {offsetof(ContentsRuleConfigLoad, _accountExpQuotaPerDay), L"account-exp-quota-per-day", XmlCfgDef::CFG_INT, 1,
     &DEFAULT_ACCOUNT_EXP_QUOTA_PER_DAY, L"[REQ] [계정컨텐츠] 계정(명예) 경험치 일일 최대 획득량. (default : 0) (0 ~ 2147483647)"},
    {offsetof(ContentsRuleConfigLoad, _accountExpQuotaResetTime), L"account-exp-quota-reset-time", XmlCfgDef::CFG_INT, 1,
     &DEFAULT_ACCOUNT_EXP_QUOTA_RESET_TIME, L"[REQ] [계정컨텐츠] 계정(명예) 경험치 일일 최대 획득량 초기화 시각. hour. 0~23시. (default : 6) (0 ~ 23)"},
    {offsetof(ContentsRuleConfigLoad, _accountLevelMax), L"account-level-max", XmlCfgDef::CFG_INT, 1,
     &DEFAULT_ACCOUNT_LEVEL_MAX, L"[REQ] [계정컨텐츠] 계정(명예) 레벨 max. (default : 50) (0 ~ 1000)"},
    {offsetof(ContentsRuleConfigLoad, _enableGuildJoinRenewal), L"enable-guild-join-renewal", XmlCfgDef::CFG_BOOL, 1,
     &DEFAULT_ENABLE_GUILD_JOIN_RENEWAL, L"[REQ] [문파 진입 개선] 문파 진입 개선 기능 사용 여부 (default=n)"},
};

// 0x140092a60
ContentsRuleXmlCfgDefLocal const ContentsRuleConfig::_Def[13] = {
    {offsetof(ContentsRuleConfig, _dummyData), L"dummy-data", XmlCfgDef::CFG_INT, 0, &MIN_DUMMY_DATA, &MAX_DUMMY_DATA,
     false, &DEFAULT_DUMMY_DATA},
    {offsetof(ContentsRuleConfig, _useTimeBasedPlaySchedule), L"use-time-based-play-schedule", XmlCfgDef::CFG_BOOL, 0,
     nullptr, nullptr, false, &DEFAULT_USE_TIME_BASED_PLAY_SCHEDULE},
    {offsetof(ContentsRuleConfig, _enablePlayWarrior), L"enable-play-warrior", XmlCfgDef::CFG_BOOL, 0, nullptr, nullptr,
     false, &DEFAULT_ENABLE_PLAY_WARRIOR},
    {offsetof(ContentsRuleConfig, _enableFishSystem), L"enable-fish-system", XmlCfgDef::CFG_BOOL, 0, nullptr, nullptr,
     false, &DEFAULT_ENABLE_FISH_SYSTEM},
    {offsetof(ContentsRuleConfig, _enableAccountContents), L"enable-account-contents", XmlCfgDef::CFG_BOOL, 0, nullptr,
     nullptr, false, &DEFAULT_ENABLE_ACCOUNT_CONTENTS},
    {offsetof(ContentsRuleConfig, _accountContentsRequiredPcLevel), L"account-contents-required-pc-level",
     XmlCfgDef::CFG_INT, 0, &MIN_ACCOUNT_CONTENTS_REQUIRED_PC_LEVEL, &MAX_ACCOUNT_CONTENTS_REQUIRED_PC_LEVEL, false,
     &DEFAULT_ACCOUNT_CONTENTS_REQUIRED_PC_LEVEL},
    {offsetof(ContentsRuleConfig, _accountContentsRequiredPcMasteryLevel),
     L"account-contents-required-pc-mastery-level", XmlCfgDef::CFG_INT, 0,
     &MIN_ACCOUNT_CONTENTS_REQUIRED_PC_MASTERY_LEVEL, &MAX_ACCOUNT_CONTENTS_REQUIRED_PC_MASTERY_LEVEL, false,
     &DEFAULT_ACCOUNT_CONTENTS_REQUIRED_PC_MASTERY_LEVEL},
    {offsetof(ContentsRuleConfig, _accountContentsRequiredAccountTopPcLevel),
     L"account-contents-required-account-top-pc-level", XmlCfgDef::CFG_INT, 0,
     &MIN_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_LEVEL, &MAX_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_LEVEL, false,
     &DEFAULT_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_LEVEL},
    {offsetof(ContentsRuleConfig, _accountContentsRequiredAccountTopPcMasteryLevel),
     L"account-contents-required-account-top-pc-mastery-level", XmlCfgDef::CFG_INT, 0,
     &MIN_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_MASTERY_LEVEL,
     &MAX_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_MASTERY_LEVEL, false,
     &DEFAULT_ACCOUNT_CONTENTS_REQUIRED_ACCOUNT_TOP_PC_MASTERY_LEVEL},
    {offsetof(ContentsRuleConfig, _accountExpQuotaPerDay), L"account-exp-quota-per-day", XmlCfgDef::CFG_INT, 0,
     &MIN_ACCOUNT_EXP_QUOTA_PER_DAY, &MAX_ACCOUNT_EXP_QUOTA_PER_DAY, false, &DEFAULT_ACCOUNT_EXP_QUOTA_PER_DAY},
    {offsetof(ContentsRuleConfig, _accountExpQuotaResetTime), L"account-exp-quota-reset-time", XmlCfgDef::CFG_INT, 0,
     &MIN_ACCOUNT_EXP_QUOTA_RESET_TIME, &MAX_ACCOUNT_EXP_QUOTA_RESET_TIME, false,
     &DEFAULT_ACCOUNT_EXP_QUOTA_RESET_TIME},
    {offsetof(ContentsRuleConfig, _accountLevelMax), L"account-level-max", XmlCfgDef::CFG_INT, 0, &MIN_ACCOUNT_LEVEL_MAX,
     &MAX_ACCOUNT_LEVEL_MAX, false, &DEFAULT_ACCOUNT_LEVEL_MAX},
    {offsetof(ContentsRuleConfig, _enableGuildJoinRenewal), L"enable-guild-join-renewal", XmlCfgDef::CFG_BOOL, 0,
     nullptr, nullptr, false, &DEFAULT_ENABLE_GUILD_JOIN_RENEWAL},
};

// 0x8220
ContentsRuleConfigLoad* ContentsRuleConfigLoad::Load()
{
    wchar_t configPath[MAX_PATH] = {0};
    PathCombineW(configPath, Daemon::Instance->confDir, CONTENTS_RULE_CONFIG_FILENAME);
    return static_cast<ContentsRuleConfigLoad*>(
        DaemonConfig::Load(_Def, 13, sizeof(ContentsRuleConfigLoad), configPath, CONTENTS_RULE_CONFIG_MODULENAME, false));
}

// 0x82c0
bool ContentsRuleConfig::LoadContentsRuleConfig()
{
    if (Config != nullptr)
        return false;

    void* memory = Memory::_Manager[2]->Alloc(sizeof(ContentsRuleConfig), FILE_NAME, 232);
    Config = memory != nullptr ? new (memory) ContentsRuleConfig() : nullptr;
    if (Config == nullptr)
        return false;

    ConfigNoReload = ContentsRuleConfigLoad::Load();
    if (ConfigNoReload == nullptr)
    {
        Memory::_Manager[2]->Free(Config, FILE_NAME, 239);
        Config = nullptr;
        Log::Write(Log::LT_ERROR, FILE_NAME, 241, L"[ContentsRuleConfig::LoadContentsRuleConfig], config file load failed");
        return false;
    }

    if (!CheckMinMaxBoundary(ConfigNoReload, _Def, ContentsRuleConfigLoad::_Def, ROW_COUNT))
    {
        DaemonConfig::FreeConfig(ConfigNoReload);
        ConfigNoReload = nullptr;
        Memory::_Manager[2]->Free(Config, FILE_NAME, 249);
        Config = nullptr;
        Log::Write(Log::LT_ERROR, FILE_NAME, 251, L"[ContentsRuleConfig::LoadContentsRuleConfig], boundary check failed");
        return false;
    }

    if (!Config->UpdateAllVariable(ConfigNoReload))
    {
        DaemonConfig::FreeConfig(ConfigNoReload);
        ConfigNoReload = nullptr;
        Memory::_Manager[2]->Free(Config, FILE_NAME, 259);
        Config = nullptr;
        Log::Write(Log::LT_ERROR, FILE_NAME, 261, L"[ContentsRuleConfig::LoadContentsRuleConfig], variable update failed");
        return false;
    }

    FragmentPacket* listPacket = MakeListPacket(Config);
    if (listPacket == nullptr)
    {
        DaemonConfig::FreeConfig(ConfigNoReload);
        ConfigNoReload = nullptr;
        Memory::_Manager[2]->Free(Config, FILE_NAME, 269);
        Config = nullptr;
        Log::Write(Log::LT_ERROR, FILE_NAME, 271, L"[ContentsRuleConfig::LoadContentsRuleConfig], packet make failed");
        return false;
    }

    InterlockedExchangePointer(reinterpret_cast<void* volatile*>(&ListPacket), listPacket);
    return true;
}

// 0x84d0
void ContentsRuleConfig::DestroyContentsRuleConfig()
{
    if (ConfigNoReload != nullptr)
        DaemonConfig::FreeConfig(ConfigNoReload);
    // BUG: 0x84d0 ConfigNoReload is freed but not set to nullptr.

    if (Config != nullptr)
    {
        Memory::_Manager[2]->Free(Config, FILE_NAME, 289);
        Config = nullptr;
    }

    while (ConfigOlds != nullptr)
    {
        ContentsRuleConfig* next = ConfigOlds->_NEXT;
        Memory::_Manager[2]->Free(ConfigOlds, FILE_NAME, 295);
        ConfigOlds = next;
    }

    while (ListPacketOlds != nullptr)
    {
        FragmentPacketWrap* next = ListPacketOlds->_NEXT;
        if (ListPacketOlds->_child != nullptr)
            ListPacketOlds->_child->packet.Clear();
        // BUG: 0x84d0 the FragmentPacket destructor is not called; only packet.Clear() runs.
        Memory::_Manager[2]->Free(ListPacketOlds->_child, FILE_NAME, 301);
        Memory::_Manager[2]->Free(ListPacketOlds, FILE_NAME, 302);
        ListPacketOlds = next;
    }
}

// 0x8600
// LIFT: noinline. The orig calls it out of line at all call sites (LG 0x8600: not inlined).
__declspec(noinline) void ContentsRuleConfig::Dump()
{
    ContentsRuleConfig* config = Config;
    if (config == nullptr)
        return;

    Log::Write(Log::LT_NOTICE, FILE_NAME, 345, L"[%s], %s : %u-%u, %s : %u-%u", CONTENTS_RULE_CONFIG_MODULENAME, L"client-version", 65, 0,
               L"server-version", 72, 0);
    Log::Write(Log::LT_NOTICE, FILE_NAME, 346, L"[%s], %s : %d", CONTENTS_RULE_CONFIG_MODULENAME, L"reload-count", ConfigReloadCount);

    char const* base = reinterpret_cast<char const*>(config);
    for (int i = 0; i < ROW_COUNT; ++i)
    {
        ContentsRuleXmlCfgDefLocal const& def = _Def[i];
        char const* field = base + def.offset;
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 356, L"[%s], %s : %d", CONTENTS_RULE_CONFIG_MODULENAME, def.name,
                       *reinterpret_cast<int const*>(field));
            break;
        case XmlCfgDef::CFG_INT64:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 357, L"[%s], %s : %I64d", CONTENTS_RULE_CONFIG_MODULENAME, def.name,
                       *reinterpret_cast<long long const*>(field));
            break;
        case XmlCfgDef::CFG_FLOAT:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 358, L"[%s], %s : %f", CONTENTS_RULE_CONFIG_MODULENAME, def.name,
                       static_cast<double>(*reinterpret_cast<float const*>(field)));
            break;
        case XmlCfgDef::CFG_BOOL:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 359, L"[%s], %s : %s", CONTENTS_RULE_CONFIG_MODULENAME, def.name,
                       *field != 0 ? L"yes" : L"no");
            break;
        case XmlCfgDef::CFG_STR:
        {
            wchar_t const* value = reinterpret_cast<wchar_t const*>(field);
            if (value == nullptr || *value == 0)
                value = L"N/A";
            Log::Write(Log::LT_NOTICE, FILE_NAME, 363, L"[%s], %s : %s", CONTENTS_RULE_CONFIG_MODULENAME, def.name, value);
            break;
        }
        default:
            break;
        }
    }
}

// Adds one UTF-8 string element to the packet. This is the inlined code that repeats in MakeListPacket.
static void addElement(FragmentPacket* fp, char* elementStr, wchar_t const* elementWStr, int length)  // LIFT: inlined in MakeListPacket 0x8965, 0x8af5, 0x8bdd. No PDB name.
{
    unsigned long long size = static_cast<unsigned long long>(
        WideCharToMultiByte(CP_UTF8, 0, elementWStr, length, elementStr, 260, nullptr, nullptr));
    elementStr[size] = 0;
    if (static_cast<unsigned long long>(static_cast<unsigned int>(fp->FreeSize())) < size + 2)
        fp->packet.Allocate(&fp->composer);
    fp->Compose(1, elementStr, static_cast<unsigned int>(size));
    RepeatPacketComposer& composer = fp->composer;
    int index = composer.start[composer.top] + 1;
    if (composer.subTop < 0)
        composer.index = index;
    else
        composer.sub[composer.subTop].index = index;
    ++*composer.counts[composer.top];
}

// 0x8800
FragmentPacket* ContentsRuleConfig::MakeListPacket(ContentsRuleConfig* config)
{
    // BUG: 0x8800 the parameter is not used. The function reads the global Config.
    (void)config;
    ContentsRuleConfig* current = Config;

    void* memory = Memory::_Manager[2]->Alloc(sizeof(FragmentPacket), FILE_NAME, 0);
    FragmentPacket* fp = memory != nullptr ? new (memory) FragmentPacket(107, "hihhiCb;") : nullptr;
    if (fp == nullptr)
        return nullptr;

    char elementStr[264] = {0};
    wchar_t elementWStr[264] = {0};

    fp->packet.Allocate(&fp->composer);
    fp->Compose(3, 65, 0, ConfigReloadCount);  // 0x88d9: edx = 3, r8d = 65, r9d = 0, [rsp+20h] = ConfigReloadCount
    if (fp->packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp->packet.CurHeader->size) < 2)
        fp->packet.Allocate(&fp->composer);
    fp->composer.PushRepeatCount(&fp->packet);

    int length = swprintf_s(elementWStr, 260,
                            L"<?xml version=\"1.0\" encoding=\"utf-8\"?><config major-version=\"%d\" minor-version=\"%d\" "
                            L"module=\"contents-rule-config\" release-module=\"LocalizationData\" release-side=\"client\">",
                            65, 0);
    addElement(fp, elementStr, elementWStr, length);

    char const* base = reinterpret_cast<char const*>(current);
    for (int i = 0; i < ROW_COUNT; ++i)
    {
        ContentsRuleXmlCfgDefLocal const& def = _Def[i];
        char const* field = base + def.offset;
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
            length = swprintf_s(elementWStr, 260, L"<option name='%s' value='%d'/>", def.name,
                                *reinterpret_cast<int const*>(field));
            break;
        case XmlCfgDef::CFG_INT64:
            length = swprintf_s(elementWStr, 260, L"<option name='%s' value='%I64d'/>", def.name,
                                *reinterpret_cast<long long const*>(field));
            break;
        case XmlCfgDef::CFG_FLOAT:
            length = swprintf_s(elementWStr, 260, L"<option name='%s' value='%f'/>", def.name,
                                static_cast<double>(*reinterpret_cast<float const*>(field)));
            break;
        case XmlCfgDef::CFG_BOOL:
            length = swprintf_s(elementWStr, 260, L"<option name='%s' value='%s'/>", def.name,
                                *field != 0 ? L"yes" : L"no");
            break;
        case XmlCfgDef::CFG_STR:
        {
            wchar_t const* value = reinterpret_cast<wchar_t const*>(field);
            if (value == nullptr)
                value = L"";  // PDB: ??_C@_11LOCGONAA@ (rva 0x627d8)
            length = swprintf_s(elementWStr, 260, L"<option name='%s' value='%s'/>", def.name, value);
            break;
        }
        default:
            continue;
        }
        addElement(fp, elementStr, elementWStr, length);
    }

    length = swprintf_s(elementWStr, 260, L"</config>");
    addElement(fp, elementStr, elementWStr, length);

    fp->composer.PopRepeatCount();
    if (fp->packet.Splitter != nullptr)
        fp->packet.Splitter->Finalize(fp->packet.CurHeader);
    return fp;
}

// 0x8ce0
bool ContentsRuleConfig::ConvPacketElement(char* utf8Name, char* utf8Value, wchar_t const* name, wchar_t const* value)
{
    if (value == nullptr)
        return false;

    long long valueLength = 0;
    long long nameLength = WideCharToMultiByte(CP_UTF8, 0, name, static_cast<int>(wcslen(name)), utf8Name, 260,
                                               nullptr, nullptr);
    if (nameLength != 0)
        valueLength = WideCharToMultiByte(CP_UTF8, 0, value, static_cast<int>(wcslen(value)), utf8Value, 260,
                                          nullptr, nullptr);

    if ((wcslen(name) == 0 || nameLength != 0) && (wcslen(value) == 0 || valueLength != 0))
    {
        if (static_cast<unsigned long long>(valueLength + nameLength + 31) <= 0x104)
        {
            utf8Name[nameLength] = 0;
            utf8Value[valueLength] = 0;
            return true;
        }
        Log::Write(Log::LT_ERROR, FILE_NAME, 475,
                   L"[ContentsRuleConfig::ConvPacketElement], overflow(%d chars), config:%s, value:%s",
                   static_cast<int>(valueLength + nameLength - 229), name, value);
        return false;
    }

    wchar_t* fmtStr = nullptr;
    DWORD lastError = GetLastError();
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY, nullptr,
                   lastError, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), reinterpret_cast<LPWSTR>(&fmtStr), 0,
                   nullptr);
    Log::Write(Log::LT_ERROR, FILE_NAME, 467,
               L"[ContentsRuleConfig::ConvPacketElement], overflow(%d/%s), config:%s, value:%s", lastError,
               fmtStr != nullptr ? fmtStr : L"", name, value);
    if (fmtStr != nullptr)
        LocalFree(fmtStr);
    return false;
}

// 0x8ef0
bool ContentsRuleConfig::CheckMinMaxBoundary(void const* const loaded, ContentsRuleXmlCfgDefLocal const* defList,
                                             XmlCfgDef const* loadDefList, int defCount)
{
    // LIFT: LTCG folded the arguments. The only call (LoadContentsRuleConfig 0x8372) sets no argument register.
    // The body reads ConfigNoReload and the two _Def tables. It stops at the address of
    // LobbyGateConfig::_Def[0].defaultValue (the next table in .rdata). That is the same as 13 rows.
    (void)loaded;
    (void)defList;
    (void)loadDefList;
    (void)defCount;

    ContentsRuleConfigLoad const* load = ConfigNoReload;
    if (load == nullptr)
        return false;

    char const* base = reinterpret_cast<char const*>(load);
    bool result = true;
    for (int i = 0; i < ROW_COUNT; ++i)
    {
        ContentsRuleXmlCfgDefLocal const& def = _Def[i];
        char const* field = base + ContentsRuleConfigLoad::_Def[i].offset;
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
        {
            int value = *reinterpret_cast<int const*>(field);
            int minValue = *static_cast<int const*>(def.minValue);
            int maxValue = *static_cast<int const*>(def.maxValue);
            if (value < minValue || value > maxValue)
            {
                Log::Write(Log::LT_ERROR, FILE_NAME, 504,
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
                Log::Write(Log::LT_ERROR, FILE_NAME, 512,
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
                Log::Write(Log::LT_ERROR, FILE_NAME, 520,
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

// 0x9060
bool ContentsRuleConfig::UpdateAllVariable(ContentsRuleConfigLoad const* const loaded)
{
    // LIFT: LTCG folded this and loaded. The only call (LoadContentsRuleConfig 0x83d6) sets no argument register.
    // The body reads the globals Config and ConfigNoReload.
    (void)loaded;
    ContentsRuleConfigLoad const* load = ConfigNoReload;
    ContentsRuleConfig* config = Config;
    if (load == nullptr)
        return false;

    char utf8Name[264] = {0};
    char utf8Value[264] = {0};
    char* target = reinterpret_cast<char*>(config);
    char const* source = reinterpret_cast<char const*>(load);
    for (int i = 0; i < ROW_COUNT; ++i)
    {
        ContentsRuleXmlCfgDefLocal const& def = _Def[i];
        char const* from = source + ContentsRuleConfigLoad::_Def[i].offset;
        char* to = target + def.offset;
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
        case XmlCfgDef::CFG_FLOAT:
            *reinterpret_cast<int*>(to) = *reinterpret_cast<int const*>(from);
            break;
        case XmlCfgDef::CFG_INT64:
            *reinterpret_cast<long long*>(to) = *reinterpret_cast<long long const*>(from);
            break;
        case XmlCfgDef::CFG_BOOL:
            *to = *from;
            break;
        case XmlCfgDef::CFG_STR:
        {
            wchar_t const* value = *reinterpret_cast<wchar_t const* const*>(from);
            if (value == nullptr)
                value = L"";  // PDB: ??_C@_11LOCGONAA@ (rva 0x627d8)
            if (def.name == nullptr || !ConvPacketElement(utf8Name, utf8Value, def.name, value))
                return false;
            wcscpy_s(reinterpret_cast<wchar_t*>(to), 260, value);
            break;
        }
        default:
            break;
        }
    }
    return true;
}
