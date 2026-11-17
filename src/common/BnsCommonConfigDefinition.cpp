// BnsCommonConfigDefinition.obj (CacheGate PDB).
// Source file in the binary: ..\..\Shared\BnsCommonConfigDefinition.cpp
#include "BnsCommonConfigDefinition.h"
#include "AlertSender.h"
#include "Daemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include <windows.h>
#include <shlwapi.h>
#include <new>
#include <string.h>
#include <wchar.h>

namespace
{
wchar_t const* const FILE_NAME = L"..\\..\\Shared\\BnsCommonConfigDefinition.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
wchar_t const* const CONFIG_FILENAME = L"bns.common.config.xml";    // 0x59278
wchar_t const* const CONFIG_MODULENAME = L"bns-common-config";  // 0x59370
}

static int const MIN_NP_PROGRAM_ID = 0;        // 0x467b4
static int const MAX_NP_PROGRAM_ID = 10000;    // 0x465bc
static int const DEFAULT_NP_PROGRAM_ID = 303;  // 0x4638c

BnsCommonConfig* BnsCommonConfig::Config = nullptr;              // 0x5a3c8
BnsCommonConfigLoad* BnsCommonConfig::ConfigNoReload = nullptr;  // 0x5a3d0
BnsCommonConfig* BnsCommonConfig::ConfigOlds = nullptr;          // 0x5a3d8

#define NP_APP_ID_DESC \
    L"NP bns-server app-id(GUID). bnsserver:D5099619-B2F2-26EB-8DDA-DD084E83DB1B, " \
    L"bnstestserver:2F12DCE2-A63E-DF2C-1944-F2BF61049C05, bnsintr_svr:498FA190-012B-450D-B5A4-BF43302BA4F4, " \
    L"bnsprog_svr:AFACDF37-7714-474A-BEAD-B289447B5A2B"
#define NP_CLIENT_APP_ID_DESC \
    L"NP bns-client app-id(GUID). bnsclient:B0D42105-0CB6-BC9F-3CB2-BE28A0662340, " \
    L"bnstestclient:18A2B067-7A7E-DA99-CDF1-3BBE3BE93F68, bnsintr_cli:D59261E6-3B53-4E42-9A1F-5CF292B3738A, " \
    L"bnsprog_cli:6E599F8E-415E-4A4C-9999-07E9BBFFD17A"
#define NP_APP_ID_DEFAULT L"AFACDF37-7714-474A-BEAD-B289447B5A2B"
#define NP_CLIENT_APP_ID_DEFAULT L"6E599F8E-415E-4A4C-9999-07E9BBFFD17A"

// 0x594b0
XmlCfgDefLocal const BnsCommonConfig::_Def[5] = {
    {offsetof(BnsCommonConfig, _pType), L"p-type", XmlCfgDef::CFG_STR, XmlCfgDefLocal::CFG_DEF_TYPE_STRING, nullptr, nullptr, false, L"live",
     offsetof(BnsCommonConfig, _pType)},
    {offsetof(BnsCommonConfig, _npProgramId), L"np-program-id", XmlCfgDef::CFG_INT, XmlCfgDefLocal::CFG_DEF_TYPE_INT, &MIN_NP_PROGRAM_ID,
     &MAX_NP_PROGRAM_ID, false, &DEFAULT_NP_PROGRAM_ID, offsetof(BnsCommonConfig, _npProgramId)},
    {offsetof(BnsCommonConfig, _npGameCode), L"np-game-code", XmlCfgDef::CFG_STR, XmlCfgDefLocal::CFG_DEF_TYPE_STRING, nullptr, nullptr, false,
     L"bnsprog", offsetof(BnsCommonConfig, _npGameCode)},
    {offsetof(BnsCommonConfig, _npAppIdStr), L"np-app-id", XmlCfgDef::CFG_STR, XmlCfgDefLocal::CFG_DEF_TYPE_GUID, nullptr,
     nullptr, true, NP_APP_ID_DEFAULT, offsetof(BnsCommonConfig, _npAppId)},
    {offsetof(BnsCommonConfig, _npClientAppIdStr), L"np-client-app-id", XmlCfgDef::CFG_STR, XmlCfgDefLocal::CFG_DEF_TYPE_GUID,
     nullptr, nullptr, true, NP_CLIENT_APP_ID_DEFAULT, offsetof(BnsCommonConfig, _npClientAppId)},
};

// 0x593e0
XmlCfgDefLocal const BnsCommonConfig::_DefReload[2] = {
    {offsetof(BnsCommonConfig, _npAppIdStr), L"np-app-id", XmlCfgDef::CFG_STR, XmlCfgDefLocal::CFG_DEF_TYPE_GUID, nullptr,
     nullptr, true, NP_APP_ID_DEFAULT, offsetof(BnsCommonConfig, _npAppId)},
    {offsetof(BnsCommonConfig, _npClientAppIdStr), L"np-client-app-id", XmlCfgDef::CFG_STR, XmlCfgDefLocal::CFG_DEF_TYPE_GUID,
     nullptr, nullptr, true, NP_CLIENT_APP_ID_DEFAULT, offsetof(BnsCommonConfig, _npClientAppId)},
};

// 0x595f0
XmlCfgDef const BnsCommonConfigLoad::_Def[5] = {
    {offsetof(BnsCommonConfigLoad, _pType), L"p-type", XmlCfgDef::CFG_STR, 1, L"live",
     L"product-type. live / remaster !!IF YOU HAVE ANY QUESTION ABOUT THIS CONFIG, PLEASE ASK TO STEAKY!!"},
    {offsetof(BnsCommonConfigLoad, _npProgramId), L"np-program-id", XmlCfgDef::CFG_INT, 0, &DEFAULT_NP_PROGRAM_ID,
     L"NP program-id. 302:live(QA), 303:program, 304:internal, 305:branch (0 ~ 10000)"},
    {offsetof(BnsCommonConfigLoad, _npGameCode), L"np-game-code", XmlCfgDef::CFG_STR, 0, L"bnsprog",
     L"NP game-code. bns:live(QA), bnsprog:program, bnsintr:internal, bnsbr:branch"},
    {offsetof(BnsCommonConfigLoad, _npAppIdStr), L"np-app-id", XmlCfgDef::CFG_STR, 0, NP_APP_ID_DEFAULT,
     NP_APP_ID_DESC},
    {offsetof(BnsCommonConfigLoad, _npClientAppIdStr), L"np-client-app-id", XmlCfgDef::CFG_STR, 0,
     NP_CLIENT_APP_ID_DEFAULT, NP_CLIENT_APP_ID_DESC},
};

// 0x59460
XmlCfgDef const BnsCommonConfigReload::_Def[2] = {
    {offsetof(BnsCommonConfigReload, _npAppIdStr), L"np-app-id", XmlCfgDef::CFG_STR, 0, NP_APP_ID_DEFAULT,
     NP_APP_ID_DESC},
    {offsetof(BnsCommonConfigReload, _npClientAppIdStr), L"np-client-app-id", XmlCfgDef::CFG_STR, 0,
     NP_CLIENT_APP_ID_DEFAULT, NP_CLIENT_APP_ID_DESC},
};

// 0x12a0
BnsCommonConfigLoad* BnsCommonConfigLoad::Load()
{
    wchar_t configPath[MAX_PATH] = {0};
    PathCombineW(configPath, Daemon::Instance->confDir, CONFIG_FILENAME);
    return static_cast<BnsCommonConfigLoad*>(
        DaemonConfig::Load(BnsCommonConfigLoad::_Def, 5, sizeof(BnsCommonConfigLoad), configPath, CONFIG_MODULENAME, false));
}

// 0x1340
BnsCommonConfigReload* BnsCommonConfigReload::Load()
{
    wchar_t configPath[MAX_PATH] = {0};
    PathCombineW(configPath, Daemon::Instance->confDir, CONFIG_FILENAME);
    return static_cast<BnsCommonConfigReload*>(DaemonConfig::Load(
        BnsCommonConfigReload::_Def, 2, sizeof(BnsCommonConfigReload), configPath, CONFIG_MODULENAME, true));
}

// 0x13e0
bool BnsCommonConfig::LoadBnsCommonConfig()
{
    if (Config != nullptr)
    {
        AlertSender::Write(FILE_NAME, 186, L"[BnsCommonConfig::LoadBnsCommonConfig], config file already loaded");
        Log::Write(Log::LT_ERROR, FILE_NAME, 186,
                   L"[BnsCommonConfig::LoadBnsCommonConfig], config file already loaded");
        Dump();
        // BUG: 0x13e0 the old Config is not freed. The next line overwrites it and the memory leaks.
    }

    void* memory = Memory::_Manager[2]->Alloc(sizeof(BnsCommonConfig), FILE_NAME, 190);
    Config = memory != nullptr ? new (memory) BnsCommonConfig() : nullptr;
    if (Config == nullptr)
        return false;

    ConfigNoReload = BnsCommonConfigLoad::Load();
    if (ConfigNoReload == nullptr)
    {
        Memory::_Manager[2]->Free(Config, FILE_NAME, 197);
        Config = nullptr;
        Log::Write(Log::LT_ERROR, FILE_NAME, 199, L"[BnsCommonConfig::LoadBnsCommonConfig], config file load failed");
        return false;
    }

    if (!CheckMinMaxBoundary(ConfigNoReload, _Def, BnsCommonConfigLoad::_Def, 5))
    {
        DaemonConfig::FreeConfig(ConfigNoReload);
        ConfigNoReload = nullptr;
        Memory::_Manager[2]->Free(Config, FILE_NAME, 207);
        Config = nullptr;
        Log::Write(Log::LT_ERROR, FILE_NAME, 209, L"[BnsCommonConfig::LoadBnsCommonConfig], boundary check failed");
        return false;
    }

    if (!Config->UpdateAllVariable(ConfigNoReload))
    {
        DaemonConfig::FreeConfig(ConfigNoReload);
        ConfigNoReload = nullptr;
        Memory::_Manager[2]->Free(Config, FILE_NAME, 217);
        Config = nullptr;
        Log::Write(Log::LT_ERROR, FILE_NAME, 219, L"[BnsCommonConfig::LoadBnsCommonConfig], variable update failed");
        return false;
    }

    return true;
}

// 0x1600
bool BnsCommonConfig::ReloadBnsCommonConfig(bool& changed)
{
    changed = false;
    if (Config == nullptr || ConfigNoReload == nullptr)
    {
        bool result = LoadBnsCommonConfig();
        changed = result;
        return result;
    }

    BnsCommonConfigReload* reload = BnsCommonConfigReload::Load();
    if (reload == nullptr)
    {
        Log::Write(Log::LT_ERROR, FILE_NAME, 235, L"[BnsCommonConfig::ReloadBnsCommonConfig], config file load failed");
        return false;
    }

    if (Config->CompareMatch(reload))
        return true;  // BUG: 0x1600 reload is not freed on this path and the memory leaks.

    if (!CheckMinMaxBoundary(reload, _DefReload, BnsCommonConfigReload::_Def, 2))
    {
        DaemonConfig::FreeConfig(reload);
        Log::Write(Log::LT_ERROR, FILE_NAME, 247, L"[BnsCommonConfig::ReloadBnsCommonConfig], boundary check failed");
        return false;
    }

    void* memory = Memory::_Manager[2]->Alloc(sizeof(BnsCommonConfig), FILE_NAME, 252);
    if (memory == nullptr)
    {
        DaemonConfig::FreeConfig(reload);
        Log::Write(Log::LT_ERROR, FILE_NAME, 256,
                   L"[BnsCommonConfig::ReloadBnsCommonConfig], new config make failed");
        return false;
    }
    BnsCommonConfig* newConfig = new (memory) BnsCommonConfig();

    if (!newConfig->Copy(Config))
    {
        Memory::_Manager[2]->Free(newConfig, FILE_NAME, 262);
        DaemonConfig::FreeConfig(reload);
        Log::Write(Log::LT_ERROR, FILE_NAME, 264,
                   L"[BnsCommonConfig::ReloadBnsCommonConfig], existing variable update failed");
        return false;
    }

    if (!newConfig->UpdateReloadedVariable(reload))
    {
        Memory::_Manager[2]->Free(newConfig, FILE_NAME, 271);
        DaemonConfig::FreeConfig(reload);
        Log::Write(Log::LT_ERROR, FILE_NAME, 273,
                   L"[BnsCommonConfig::ReloadBnsCommonConfig], reloaded variable update failed");
        return false;
    }

    // BUG: 0x1600 reload is not freed on the success path and the memory leaks.
    BnsCommonConfig* old =
        static_cast<BnsCommonConfig*>(InterlockedExchangePointer(reinterpret_cast<void* volatile*>(&Config), newConfig));
    if (old != nullptr)
    {
        old->_NEXT = ConfigOlds;
        ConfigOlds = old;
    }
    changed = true;
    return true;
}

// 0x1880
void BnsCommonConfig::Dump()
{
    BnsCommonConfig const* config = Config;
    if (config == nullptr)
        return;

    Log::Write(Log::LT_NOTICE, FILE_NAME, 317, L"[%s], %s : %u", CONFIG_MODULENAME, L"version", 2u);
    char const* base = reinterpret_cast<char const*>(config);
    for (int i = 0; i < 5; ++i)
    {
        XmlCfgDefLocal const& def = _Def[i];
        void const* field = base + def.offset;
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 327, L"[%s], %s : %d", CONFIG_MODULENAME, def.name,
                       *static_cast<int const*>(field));
            break;
        case XmlCfgDef::CFG_INT64:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 328, L"[%s], %s : %I64d", CONFIG_MODULENAME, def.name,
                       *static_cast<long long const*>(field));
            break;
        case XmlCfgDef::CFG_FLOAT:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 329, L"[%s], %s : %f", CONFIG_MODULENAME, def.name,
                       static_cast<double>(*static_cast<float const*>(field)));
            break;
        case XmlCfgDef::CFG_BOOL:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 330, L"[%s], %s : %s", CONFIG_MODULENAME, def.name,
                       *static_cast<bool const*>(field) ? L"yes" : L"no");
            break;
        case XmlCfgDef::CFG_IP:
            Log::Write(Log::LT_NOTICE, FILE_NAME, 334, L"[%s], %s : %s", CONFIG_MODULENAME, def.name,
                       Network::GetAddressStringW(*static_cast<unsigned long const*>(field)));
            break;
        case XmlCfgDef::CFG_STR:
        {
            wchar_t const* text = static_cast<wchar_t const*>(field);
            Log::Write(Log::LT_NOTICE, FILE_NAME, 342, L"[%s], %s : %s", CONFIG_MODULENAME, def.name,
                       text != nullptr ? text : L"N/A");
            break;
        }
        default:
            break;
        }
    }
}

// 0x1a40
bool BnsCommonConfig::CheckMinMaxBoundary(void const* const loaded, XmlCfgDefLocal const* defList,
                                          XmlCfgDef const* loadDefList, int defCount)
{
    if (loaded == nullptr)
        return false;

    bool result = true;
    char const* base = static_cast<char const*>(loaded);
    for (int i = 0; i < defCount; ++i)
    {
        XmlCfgDefLocal const& def = defList[i];
        void const* field = base + loadDefList[i].offset;
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
        {
            int value = *static_cast<int const*>(field);
            int minValue = *static_cast<int const*>(def.minValue);
            int maxValue = *static_cast<int const*>(def.maxValue);
            if (value >= minValue && value <= maxValue)
                continue;
            Log::Write(Log::LT_ERROR, FILE_NAME, 374,
                       L"[BnsCommonConfig::CheckMinMaxBoundary], value outranged, name:%s, value:%d, min:%d, max:%d",
                       def.name, value, minValue, maxValue);
            break;
        }
        case XmlCfgDef::CFG_INT64:
        {
            long long value = *static_cast<long long const*>(field);
            long long minValue = *static_cast<long long const*>(def.minValue);
            long long maxValue = *static_cast<long long const*>(def.maxValue);
            if (value >= minValue && value <= maxValue)
                continue;
            Log::Write(
                Log::LT_ERROR, FILE_NAME, 382,
                L"[BnsCommonConfig::CheckMinMaxBoundary], value outranged, name:%s, value:%I64d, min:%I64d, max:%I64d",
                def.name, value, minValue, maxValue);
            break;
        }
        case XmlCfgDef::CFG_FLOAT:
        {
            float value = *static_cast<float const*>(field);
            float minValue = *static_cast<float const*>(def.minValue);
            float maxValue = *static_cast<float const*>(def.maxValue);
            if (minValue <= value && value <= maxValue)
                continue;
            Log::Write(Log::LT_ERROR, FILE_NAME, 390,
                       L"[BnsCommonConfig::CheckMinMaxBoundary], value outranged, name:%s, value:%f, min:%f, max:%f",
                       def.name, static_cast<double>(value), static_cast<double>(minValue),
                       static_cast<double>(maxValue));
            break;
        }
        case XmlCfgDef::CFG_STR:
        {
            if (def.defType != XmlCfgDefLocal::CFG_DEF_TYPE_GUID)
                continue;
            wchar_t const* value = *static_cast<wchar_t const* const*>(field);
            if (String::GetId128FromGuidString(value, nullptr))
                continue;
            Log::Write(Log::LT_ERROR, FILE_NAME, 400,
                       L"[BnsCommonConfig::CheckMinMaxBoundary], guid value invalid, name:%s, value:%s", def.name,
                       value);
            break;
        }
        default:
            continue;
        }
        result = false;
    }
    return result;
}

// 0x1c10
// ❓ LTCG put the globals in place of the arguments: the binary reads Config as this and ConfigNoReload as load.
// The only caller (LoadBnsCommonConfig) gives these values, so the result is the same.
bool BnsCommonConfig::UpdateAllVariable(BnsCommonConfigLoad const* const load)
{
    if (load == nullptr)
        return false;

    char* dst = reinterpret_cast<char*>(this);
    char const* src = reinterpret_cast<char const*>(load);
    for (int i = 0; i < 5; ++i)
    {
        XmlCfgDefLocal const& def = _Def[i];
        XmlCfgDef const& loadDef = BnsCommonConfigLoad::_Def[i];
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
        case XmlCfgDef::CFG_FLOAT:
        case XmlCfgDef::CFG_IP:
            *reinterpret_cast<unsigned long*>(dst + def.offset) =
                *reinterpret_cast<unsigned long const*>(src + loadDef.offset);
            break;
        case XmlCfgDef::CFG_INT64:
            *reinterpret_cast<long long*>(dst + def.offset) = *reinterpret_cast<long long const*>(src + loadDef.offset);
            break;
        case XmlCfgDef::CFG_BOOL:
            *reinterpret_cast<bool*>(dst + def.offset) = *reinterpret_cast<bool const*>(src + loadDef.offset);
            break;
        case XmlCfgDef::CFG_STR:
        {
            wchar_t* text = reinterpret_cast<wchar_t*>(dst + def.offset);
            wchar_t const* value = *reinterpret_cast<wchar_t const* const*>(src + loadDef.offset);
            wcscpy_s(text, 260, value != nullptr ? value : L"");
            if (def.defType == XmlCfgDefLocal::CFG_DEF_TYPE_GUID)
                String::GetId128FromGuidString(text, reinterpret_cast<id128*>(dst + def.refOffset));
            break;
        }
        default:
            break;
        }
    }
    return true;
}

// 0x1d50
// ❓ LTCG put the global Config in place of source. The only caller gives Config.
bool BnsCommonConfig::Copy(BnsCommonConfig const* const source)
{
    if (source == nullptr)
        return false;

    wcscpy_s(_pType, 260, source->_pType);
    _npProgramId = source->_npProgramId;
    wcscpy_s(_npGameCode, 260, source->_npGameCode);
    _npAppId = source->_npAppId;
    wcscpy_s(_npAppIdStr, 260, source->_npAppIdStr);
    _npClientAppId = source->_npClientAppId;
    wcscpy_s(_npClientAppIdStr, 260, source->_npClientAppIdStr);
    return true;
}

// 0x1e30
bool BnsCommonConfig::UpdateReloadedVariable(BnsCommonConfigReload const* const reload)
{
    if (reload == nullptr)
        return false;

    char* dst = reinterpret_cast<char*>(this);
    char const* src = reinterpret_cast<char const*>(reload);
    for (int i = 0; i < 2; ++i)
    {
        XmlCfgDefLocal const& def = _DefReload[i];
        XmlCfgDef const& reloadDef = BnsCommonConfigReload::_Def[i];
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
        case XmlCfgDef::CFG_IP:
        {
            unsigned long value = *reinterpret_cast<unsigned long const*>(src + reloadDef.offset);
            unsigned long* field = reinterpret_cast<unsigned long*>(dst + def.offset);
            if (*field != value)
                *field = value;
            break;
        }
        case XmlCfgDef::CFG_INT64:
        {
            long long value = *reinterpret_cast<long long const*>(src + reloadDef.offset);
            long long* field = reinterpret_cast<long long*>(dst + def.offset);
            if (*field != value)
                *field = value;
            break;
        }
        case XmlCfgDef::CFG_FLOAT:
        {
            float value = *reinterpret_cast<float const*>(src + reloadDef.offset);
            float* field = reinterpret_cast<float*>(dst + def.offset);
            if (*field != value)
                *field = value;
            break;
        }
        case XmlCfgDef::CFG_BOOL:
        {
            bool value = *reinterpret_cast<bool const*>(src + reloadDef.offset);
            bool* field = reinterpret_cast<bool*>(dst + def.offset);
            if (*field != value)
                *field = value;
            break;
        }
        case XmlCfgDef::CFG_STR:
        {
            wchar_t* text = reinterpret_cast<wchar_t*>(dst + def.offset);
            wchar_t const* value = *reinterpret_cast<wchar_t const* const*>(src + reloadDef.offset);
            if (value == nullptr)
                value = L"";
            if (wcscmp(text, value) != 0)
                wcscpy_s(text, 260, value);
            if (def.defType == XmlCfgDefLocal::CFG_DEF_TYPE_GUID)
                String::GetId128FromGuidString(text, reinterpret_cast<id128*>(dst + def.refOffset));
            break;
        }
        default:
            break;
        }
    }
    return true;
}

// 0x1fc0
// ❓ LTCG put the global Config in place of this. The only caller gives Config.
bool BnsCommonConfig::CompareMatch(BnsCommonConfigReload const* reload) const
{
    if (reload == nullptr)
        return true;

    char const* dst = reinterpret_cast<char const*>(this);
    char const* src = reinterpret_cast<char const*>(reload);
    for (unsigned int i = 0; i < 2; ++i)
    {
        XmlCfgDefLocal const& def = _DefReload[i];
        XmlCfgDef const& reloadDef = BnsCommonConfigReload::_Def[i];
        bool equal = true;
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
        case XmlCfgDef::CFG_IP:
            equal = *reinterpret_cast<unsigned long const*>(dst + def.offset) ==
                    *reinterpret_cast<unsigned long const*>(src + reloadDef.offset);
            break;
        case XmlCfgDef::CFG_INT64:
            equal = *reinterpret_cast<long long const*>(dst + def.offset) ==
                    *reinterpret_cast<long long const*>(src + reloadDef.offset);
            break;
        case XmlCfgDef::CFG_FLOAT:
            equal = *reinterpret_cast<float const*>(dst + def.offset) ==
                    *reinterpret_cast<float const*>(src + reloadDef.offset);
            break;
        case XmlCfgDef::CFG_BOOL:
            equal = *reinterpret_cast<bool const*>(dst + def.offset) ==
                    *reinterpret_cast<bool const*>(src + reloadDef.offset);
            break;
        case XmlCfgDef::CFG_STR:
        {
            wchar_t const* value = *reinterpret_cast<wchar_t const* const*>(src + reloadDef.offset);
            equal = wcscmp(reinterpret_cast<wchar_t const*>(dst + def.offset), value != nullptr ? value : L"") == 0;
            break;
        }
        default:
            break;
        }
        if (!equal)
            return false;
    }
    return true;
}
