// BnsCommonConfigDefinition.obj (CacheGate PDB).  // ❓ file name
// Layout from include/pdb/CacheGate/types.h lines 877-927.
#pragma once
#include "DaemonConfig.h"
#include "StringUtil.h"

class BnsCommonConfigLoad
{
public:
    wchar_t const* _pType;
    int _npProgramId;
    wchar_t const* _npGameCode;
    wchar_t const* _npAppIdStr;
    wchar_t const* _npClientAppIdStr;

    static BnsCommonConfigLoad* Load();  // 0x12a0

    static XmlCfgDef const _Def[5];  // 0x595f0
};
static_assert(sizeof(BnsCommonConfigLoad) == 0x28, "sizeof BnsCommonConfigLoad");

class BnsCommonConfigReload
{
public:
    wchar_t const* _npAppIdStr;
    wchar_t const* _npClientAppIdStr;

    static BnsCommonConfigReload* Load();  // 0x1340

    static XmlCfgDef const _Def[2];  // 0x59460
};
static_assert(sizeof(BnsCommonConfigReload) == 0x10, "sizeof BnsCommonConfigReload");

class BnsCommonConfig
{
public:
    BnsCommonConfig* _NEXT;
    wchar_t _pType[260];
    int _npProgramId;
    wchar_t _npGameCode[260];
    id128 _npAppId;
    wchar_t _npAppIdStr[260];
    id128 _npClientAppId;
    wchar_t _npClientAppIdStr[260];

    // Inline constructor. The binary writes it in LoadBnsCommonConfig and ReloadBnsCommonConfig.
    BnsCommonConfig()
        : _NEXT(nullptr), _npProgramId(0)
    {
        _pType[0] = 0;
        _npGameCode[0] = 0;
        _npAppId.id[0] = 0;
        _npAppId.id[1] = 0;
        _npAppIdStr[0] = 0;
        _npClientAppId.id[0] = 0;
        _npClientAppId.id[1] = 0;
        _npClientAppIdStr[0] = 0;
    }

    static bool LoadBnsCommonConfig();               // 0x13e0
    static bool ReloadBnsCommonConfig(bool& changed);  // 0x1600
    static void Dump();                               // 0x1880

    static BnsCommonConfig* Config;               // 0x5a3c8
    static BnsCommonConfigLoad* ConfigNoReload;   // 0x5a3d0
    static BnsCommonConfig* ConfigOlds;           // 0x5a3d8
    static XmlCfgDefLocal const _Def[5];          // 0x594b0
    static XmlCfgDefLocal const _DefReload[2];    // 0x593e0

private:
    static bool CheckMinMaxBoundary(void const* const loaded, XmlCfgDefLocal const* defList,
                                    XmlCfgDef const* loadDefList, int defCount);  // 0x1a40
    bool UpdateAllVariable(BnsCommonConfigLoad const* const load);                 // 0x1c10
    bool Copy(BnsCommonConfig const* const source);                                // 0x1d50
    bool UpdateReloadedVariable(BnsCommonConfigReload const* const reload);        // 0x1e30
    bool CompareMatch(BnsCommonConfigReload const* reload) const;                  // 0x1fc0
};
static_assert(sizeof(BnsCommonConfig) == 0x850, "sizeof BnsCommonConfig");
static_assert(offsetof(BnsCommonConfig, _npAppId) == 0x420, "BnsCommonConfig::_npAppId");
static_assert(offsetof(BnsCommonConfig, _npClientAppIdStr) == 0x648, "BnsCommonConfig::_npClientAppIdStr");
