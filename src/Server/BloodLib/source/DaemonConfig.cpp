// DaemonConfig.obj (CacheGate PDB).
#include "DaemonConfig.h"
#include "Console.h"
#include "Daemon.h"
#include "Log.h"
#include "Memory.h"
#include "Network.h"
#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>
#include <string.h>
#if defined(__clang__)
#include <crt_cpp_overload.h>  // The Wine headers do not have swprintf_s<N>. VS2010 has it.
#endif

namespace
{
// Function types of the XmlReader_sv64.dll exports (PDB typedefs).
// XriGetInterfaceVersion, XriCreateFunc and XriDestoryFunc are in XmlReader.h.
typedef XmlConfigReader const* (*XciCreateFunc)(XmlReader const*);
typedef void (*XciDestoryFunc)(XmlConfigReader const*);

wchar_t const* const XML_READER_DLL = L"XmlReader_sv64.dll";  // LIFT: No PDB symbol. The binary uses the literal.
wchar_t const* const XML_READER_VERSION = L"15";              // LIFT: No PDB symbol. The binary uses the literal.
}

// 0xc600
void* DaemonConfig::Load(XmlCfgDef const* def, int count, unsigned long long size, wchar_t const* fileName,
                         wchar_t const* configName, bool readOnly)
{
    wchar_t fullPath[780];
    Daemon* daemon = Daemon::Instance;
    // 0xcca0 is swprintf_s<780>.
    if (PathIsFileSpecW(fileName) && daemon->confDir[0] != 0)
        swprintf_s(fullPath, L"%s\\%s", daemon->confDir, fileName);
    else
        swprintf_s(fullPath, fileName);  // BUG: 0xc600 the file name is used as a format string.

    Console* console = Daemon::Instance->console;
    HMODULE module = LoadLibraryW(XML_READER_DLL);
    if (module != nullptr)
    {  // LIFT: 0xc600 the binary puts the failure block of LoadLibraryW last; the body is not indented.
    XriGetInterfaceVersion getInterfaceVersion =
        reinterpret_cast<XriGetInterfaceVersion>(GetProcAddress(module, "GetInterfaceVersion"));
    GetProcAddress(module, "SetMemAllocator");
    XriCreateFunc createXmlReader = reinterpret_cast<XriCreateFunc>(GetProcAddress(module, "CreateXmlReader"));
    XriDestoryFunc destroyXmlReader =
        reinterpret_cast<XriDestoryFunc>(GetProcAddress(module, "DestroyXmlReader"));

    if (_wcsicmp(XML_READER_VERSION, getInterfaceVersion()) != 0)
    {
        if (console != nullptr)
        {
            // BUG: 0xc600 "%d" gets a string (the platform binary version).
            console->WriteStartLog(
                0, L"[config], xml reader check version failed, file: %s, required: %s, loaded: %s, platform binary:%d",
                XML_READER_DLL, XML_READER_VERSION, getInterfaceVersion(), L"0.0.346.440");
            Sleep(5000);
        }
        FreeLibrary(module);
        return nullptr;
    }

    XmlReader const* reader = createXmlReader();
    if (reader == nullptr)
    {
        if (console != nullptr)
        {
            console->WriteStartLog(0, L"[config], cannot load xml reader library, file: %s", XML_READER_DLL);
            Sleep(5000);
        }
        FreeLibrary(module);
        return nullptr;
    }

    if (!reader->Initialize(nullptr, nullptr, false))
    {
        if (console != nullptr)
        {
            console->WriteStartLog(0, L"[config], xml reader library initialize failed.");
            Sleep(5000);
        }
        destroyXmlReader(reader);
        FreeLibrary(module);
        return nullptr;
    }

    XciCreateFunc createXmlConfigReader =
        reinterpret_cast<XciCreateFunc>(GetProcAddress(module, "CreateXmlConfigReader"));
    XciDestoryFunc destroyXmlConfigReader =
        reinterpret_cast<XciDestoryFunc>(GetProcAddress(module, "DestroyXmlConfigReader"));
    XmlConfigReader const* config = createXmlConfigReader(reader);
    GetProcAddress(module, "EncodeToConfigPacket");
    GetProcAddress(module, "DecodeFromConfigPacket");

    if (config == nullptr)
    {
        if (console != nullptr)
        {
            console->WriteStartLog(0, L"[config], cannot create xml config, file: %s", XML_READER_DLL);
            Sleep(5000);
        }
        destroyXmlConfigReader(nullptr);
        destroyXmlReader(reader);
        FreeLibrary(module);
        return nullptr;
    }

    if (!config->Initialize(def, count, &DaemonConfig::AllocConfig, size))
    {
        if (console != nullptr)
        {
            console->WriteStartLog(0, L"[config], xml config library initialize failed, file: %s, error: %s", fullPath,
                                   config->GetLastErrorString());
            Sleep(5000);
        }
        destroyXmlConfigReader(config);
        destroyXmlReader(reader);
        FreeLibrary(module);
        return nullptr;
    }

    void* result = config->Read(fullPath, configName, readOnly);
    if (result == nullptr && console != nullptr)
    {
        console->WriteStartLog(0, L"[config], cannot load config, file: %s, error: %s", fullPath,
                               config->GetLastErrorString());
        Sleep(5000);
    }
    destroyXmlConfigReader(config);
    destroyXmlReader(reader);
    FreeLibrary(module);
    return result;
    }
    else
    {
        if (console != nullptr)
        {
            console->WriteStartLog(0, L"[config], cannot load xml reader library, file: %s", XML_READER_DLL);
            Sleep(5000);
        }
        return nullptr;
    }
}

// 0xc9f0
void* DaemonConfig::AllocConfig(unsigned long long size)
{
    return Memory::_Manager[1]->Alloc(size, L"source\\DaemonConfig.cpp", 110);
}

// LIFT: inline only (seen in 0x13e0 and 0x1600)
void DaemonConfig::FreeConfig(void* config)
{
    Memory::_Manager[1]->Free(config, L"source\\DaemonConfig.cpp", 115);
}

// 0xca10
// LIFT: LTCG made this function specific to CacheGate. 0xCA3E loads CacheGateConfig::_Def + 8 (PDB 0003:1728)
// and 0xCA45 loads L"cachegate config". The only call (0x4535) passes only rcx = config. The lift uses the parameters.
// LIFT: noinline. The orig calls it out of line (POD 0x282d0).
__declspec(noinline) void DaemonConfig::Dump(wchar_t const* name, void const* config, XmlCfgDef const* defs, int count)
{
    wchar_t const* const file = L"source\\DaemonConfig.cpp";
    char const* base = static_cast<char const*>(config);
    wchar_t temp[1024];
    for (int i = 0; i < count; ++i)
    {
        XmlCfgDef const& def = defs[i];
        if (def.name == nullptr)
        {
            if (def.desc != nullptr)
                Log::Write(Log::LT_DEBUG, file, 132, L"[%s], ==== %s ====", name, def.desc);
            continue;
        }
        void const* field = base + def.offset;
        switch (def.type)
        {
        case XmlCfgDef::CFG_INT:
            Log::Write(Log::LT_DEBUG, file, 141, L"[%s], %s : %d", name, def.name, *static_cast<int const*>(field));
            break;
        case XmlCfgDef::CFG_INT64:
            Log::Write(Log::LT_DEBUG, file, 142, L"[%s], %s : %I64d", name, def.name,
                       *static_cast<long long const*>(field));
            break;
        case XmlCfgDef::CFG_FLOAT:
            Log::Write(Log::LT_DEBUG, file, 143, L"[%s], %s : %f", name, def.name,
                       static_cast<double>(*static_cast<float const*>(field)));
            break;
        case XmlCfgDef::CFG_BOOL:
            Log::Write(Log::LT_DEBUG, file, 144, L"[%s], %s : %s", name, def.name,
                       *static_cast<bool const*>(field) ? L"yes" : L"no");
            break;
        case XmlCfgDef::CFG_IP:
        {
            unsigned long long address = *static_cast<unsigned long long const*>(field);
            wchar_t const* text = address != 0 ? Network::GetAddressStringW(static_cast<unsigned long>(address)) : L"N/A";
            Log::Write(Log::LT_DEBUG, file, 148, L"[%s], %s : %s", name, def.name, text);
            break;
        }
        case XmlCfgDef::CFG_STR:
        case XmlCfgDef::CFG_DIR:
        {
            wchar_t const* text = *static_cast<wchar_t const* const*>(field);
            if (text == nullptr || *text == 0)
                text = L"N/A";
            Log::Write(Log::LT_DEBUG, file, 156, L"[%s], %s : %s", name, def.name, text);
            break;
        }
        case XmlCfgDef::CFG_ANSI:
        {
            temp[0] = 0;
            char const* text = *static_cast<char const* const*>(field);
            if (text == nullptr || *text == 0)
                text = "N/A";
            temp[1023] = 0;
            MultiByteToWideChar(CP_ACP, 0, text, -1, temp, 1023);
            temp[1023] = 0;
            Log::Write(Log::LT_DEBUG, file, 164, L"[%s], %s : %s", name, def.name, temp);
            break;
        }
        default:
            break;
        }
    }
}
