// WorldConfigManager.obj (PostOfficeDaemon PDB). Source: .scratch/hr/WorldConfigManager.c
// The std::map functions of WorldConfigList (0xd8c0, 0xf210, 0xf2a0, 0xf310, 0xf3f0, 0xf760, 0xf890,
// 0x12a20, 0x1f520, 0x1f580, 0x1f5a0) come from include/vs2010.
#include <winsock2.h>
#include <windows.h>
#include <io.h>
#include <stdlib.h>
#include <wchar.h>
#include "WorldConfig.h"
#include "AlertSender.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "PostOfficeDaemon.h"
#include "XmlReader.h"

namespace
{
wchar_t const* const WORLD_CONFIG_FILE = L"WorldConfigManager.cpp";  // ❓ name
wchar_t const* const WORLD_CONFIG_TAG = L"world config manager";    // ❓ name
wchar_t const* const XML_READER_DLL = L"XmlReader_sv64.dll";        // ❓ name
wchar_t const* const XML_READER_VERSION = L"15";                    // ❓ name
int const BUCKET_COUNT = 33;                                        // ❓ name
int const WORLD_COUNT_PER_BUCKET = 1000;                            // ❓ name
}

// The original writes each "== CRASH ==" text to Log (LT_ERROR) and to AlertSender.
#define WORLD_CONFIG_CRASH(line, fmt, ...)                                     \
    do                                                                         \
    {                                                                          \
        Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, line, fmt, __VA_ARGS__);  \
        AlertSender::Write(WORLD_CONFIG_FILE, line, fmt, __VA_ARGS__);         \
    } while (0)

// 0xd910
WorldConfigList::~WorldConfigList()
{
    for (Container::iterator it = _configList.begin(); it != _configList.end(); ++it)
        Memory::_Manager[2]->Free(it->second, WORLD_CONFIG_FILE, 33);
    _configList.clear();
}

// 0xda70
bool WorldConfigManager::initConfigManager()
{
    if (!setWorldConfigFilePath())
    {
        Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 76, L"[%s], %s; failed to set world config file path",
                   WORLD_CONFIG_TAG, L"initConfigManager");
        return false;
    }
    if (_waccess(_filePath, 0) != 0)
    {
        if (!createWorldConfigFile(_filePath))
            Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 82,
                       L"[%s], %s; failed to create world config xml file, filePath:%s", WORLD_CONFIG_TAG,
                       L"initConfigManager", _filePath);
        // The original returns false also when it created the sample file.
        return false;
    }
    return true;
}

// 0xdb30
bool WorldConfigManager::updateWorldList(WorldConfigList const* worldConfigList)
{
    AutoCS lock(&_reloadLock);
    for (WorldConfigList::Container::const_iterator it = worldConfigList->_configList.begin();
         it != worldConfigList->_configList.end(); ++it)
    {
        unsigned short wid = it->first;
        WorldConfig const* worldConfig = it->second;
        int bucketIndex = wid / WORLD_COUNT_PER_BUCKET;
        if (bucketIndex >= BUCKET_COUNT)
        {
            Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 107,
                       L"[%s], %s; wid out of range, wid:%u, bucketIndex:%d, bucketCount:%d", WORLD_CONFIG_TAG,
                       L"updateWorldList", wid, bucketIndex, BUCKET_COUNT);
            lock.Leave();
            return false;
        }
        int worldIndex = wid - WORLD_COUNT_PER_BUCKET * bucketIndex;
        if (_containerList[bucketIndex] == nullptr)
            _containerList[bucketIndex] =
                static_cast<WorldConfig**>(Memory::_Manager[2]->AllocZero(8000, WORLD_CONFIG_FILE, 112));
        if (_containerList[bucketIndex][worldIndex] != nullptr)
        {
            if (!updateWorldConfig(wid, bucketIndex, worldIndex, worldConfig))
            {
                WORLD_CONFIG_CRASH(123,
                                   L"== CRASH == [%s], %s; failed to update world config, wid:%u, bucketIndex:%d, "
                                   L"worldIndex:%d, ipAddr:%s, port:%u",
                                   WORLD_CONFIG_TAG, L"updateWorldList", wid, bucketIndex, worldIndex,
                                   Network::GetAddressStringW(worldConfig->_ipAddress), worldConfig->_port);
                lock.Leave();
                return false;
            }
        }
        else if (!addWorldConfig(wid, bucketIndex, worldIndex, worldConfig))
        {
            WORLD_CONFIG_CRASH(117,
                               L"== CRASH == [%s], %s; failed to add world config, wid:%u, bucketIndex:%d, "
                               L"worldIndex:%d, ipAddr:%s, port:%u",
                               WORLD_CONFIG_TAG, L"updateWorldList", wid, bucketIndex, worldIndex,
                               Network::GetAddressStringW(worldConfig->_ipAddress), worldConfig->_port);
            lock.Leave();
            return false;
        }
    }
    lock.Leave();
    return true;
}

// 0xdfd0
bool WorldConfigManager::addWorldConfig(unsigned short wid, int bucketIndex, int worldIndex,
                                        WorldConfig const* const worldConfig)
{
    if (wid == 0 || bucketIndex >= BUCKET_COUNT || worldIndex >= WORLD_COUNT_PER_BUCKET || worldConfig == nullptr)
    {
        WORLD_CONFIG_CRASH(136,
                           L"== CRASH == [%s], %s; invalid parameter, wid:%u, bucketIndex:%d, worldIndex:%d, "
                           L"worldConfig:0x%p",
                           WORLD_CONFIG_TAG, L"addWorldConfig", wid, bucketIndex, worldIndex, worldConfig);
        return false;
    }
    WorldConfig* newConfig =
        static_cast<WorldConfig*>(Memory::_Manager[2]->Alloc(sizeof(WorldConfig), WORLD_CONFIG_FILE, 143));  // ❓ line
    newConfig->_wid = worldConfig->_wid;
    newConfig->_ipAddress = worldConfig->_ipAddress;
    newConfig->_port = worldConfig->_port;
    _containerList[bucketIndex][worldIndex] = newConfig;
    if (_arrayBoundary[bucketIndex][0] == -1 || _arrayBoundary[bucketIndex][0] > worldIndex)
        _arrayBoundary[bucketIndex][0] = worldIndex;
    if (_arrayBoundary[bucketIndex][1] < worldIndex)
        _arrayBoundary[bucketIndex][1] = worldIndex;
    Log::Write(Log::LT_DEBUG, WORLD_CONFIG_FILE, 150,
               L"[%s], %s; succeeded to add world config, wid:%u, bucketIndex:%d, worldIndex:%d, ipAddr:%s, port:%u",
               WORLD_CONFIG_TAG, L"addWorldConfig", wid, bucketIndex, worldIndex,
               Network::GetAddressStringW(newConfig->_ipAddress), newConfig->_port);
    return true;
}

// 0xe190
bool WorldConfigManager::updateWorldConfig(unsigned short wid, int bucketIndex, int worldIndex,
                                           WorldConfig const* const worldConfig)
{
    if (wid == 0 || bucketIndex >= BUCKET_COUNT || worldIndex >= WORLD_COUNT_PER_BUCKET || worldConfig == nullptr)
    {
        WORLD_CONFIG_CRASH(158,
                           L"== CRASH == [%s], %s; invalid parameter, wid:%u, bucketIndex:%d, worldIndex:%d, "
                           L"worldConfig:0x%p",
                           WORLD_CONFIG_TAG, L"updateWorldConfig", wid, bucketIndex, worldIndex, worldConfig);
        return false;
    }
    WorldConfig* current = _containerList[bucketIndex][worldIndex];
    if (current->_wid != worldConfig->_wid || current->_ipAddress != worldConfig->_ipAddress ||
        current->_port != worldConfig->_port)
    {
        current->_ipAddress = worldConfig->_ipAddress;
        current->_port = worldConfig->_port;
        Log::Write(Log::LT_DEBUG, WORLD_CONFIG_FILE, 167,
                   L"[%s], %s; succeeded to update world config, wid:%u, bucketIndex:%d, worldIndex:%d, ipAddr:%s, "
                   L"port:%u",
                   WORLD_CONFIG_TAG, L"updateWorldConfig", wid, bucketIndex, worldIndex,
                   Network::GetAddressStringW(current->_ipAddress), current->_port);
    }
    return true;
}

// 0xe310
WorldConfig* WorldConfigManager::getWorldConfig(unsigned short const wid)
{
    if (wid == 0)
    {
        Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 176, L"[%s], %s; invalid parameter, wid:%u", WORLD_CONFIG_TAG,
                   L"getWorldConfig", wid);
        return nullptr;
    }
    int bucketIndex = wid / WORLD_COUNT_PER_BUCKET;
    if (bucketIndex >= BUCKET_COUNT)
    {
        Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 186,
                   L"[%s], %s; wid out of range, wid:%u, bucketIndex:%d, bucketCount:%d", WORLD_CONFIG_TAG,
                   L"getWorldConfig", wid, bucketIndex, BUCKET_COUNT);
        return nullptr;
    }
    if (_containerList[bucketIndex] == nullptr)
    {
        Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 191, L"[%s], %s; no such container list, wid:%u, bucketIndex:%d",
                   WORLD_CONFIG_TAG, L"getWorldConfig", wid, bucketIndex);
        return nullptr;
    }
    return _containerList[bucketIndex][wid - WORLD_COUNT_PER_BUCKET * bucketIndex];
}

// 0xe430
bool WorldConfigManager::CheckWorldConfig(unsigned short wid, unsigned long ipAddr, unsigned short const port)
{
    if (wid == 0 || ipAddr == 0 || port == 0)
    {
        Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 201, L"[%s], %s; invalid parameter, wid:%u, ipAddr:%s, port:%u",
                   WORLD_CONFIG_TAG, L"CheckWorldConfig", wid, Network::GetAddressStringW(ipAddr), port);
        return false;
    }
    WorldConfig* worldConfig = getWorldConfig(wid);
    if (worldConfig == nullptr)
    {
        Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 207, L"[%s], %s; no such world config, wid:%u, worldConfig:0x%p",
                   WORLD_CONFIG_TAG, L"CheckWorldConfig", wid, worldConfig);
        return false;
    }
    return worldConfig->_wid == wid && worldConfig->_ipAddress == ipAddr && worldConfig->_port == port;
}

// 0xe560
bool WorldConfigManager::setWorldConfigFilePath()
{
    if (_wmakepath_s(_filePath, 260, nullptr, PostOfficeDaemon::_instance->_config->_configPath,
                     L"gamed-list.config.xml", nullptr) != 0)
    {
        Log::Write(WORLD_CONFIG_FILE, 234, GetLastError(), L"[%s], %s; failed to make config file path",
                   WORLD_CONFIG_TAG, L"setWorldConfigFilePath");
        return false;
    }
    return true;
}

// 0xe5f0
bool WorldConfigManager::loadWorldConfigFile(WorldConfigList* worldConfigList)
{
    bool result = false;
    HMODULE library = LoadLibraryW(XML_READER_DLL);
    if (library == nullptr)
    {
        Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 251,
                   L"[%s], %s; failed to initialize xml reader interface, dll name:%s", WORLD_CONFIG_TAG,
                   L"loadWorldConfigFile", XML_READER_DLL);
        return false;
    }
    XriGetInterfaceVersion getInterfaceVersion =
        reinterpret_cast<XriGetInterfaceVersion>(GetProcAddress(library, "GetInterfaceVersion"));
    GetProcAddress(library, "SetMemAllocator");
    XriCreateFunc createXmlReader = reinterpret_cast<XriCreateFunc>(GetProcAddress(library, "CreateXmlReader"));
    XriDestoryFunc destroyXmlReader =
        reinterpret_cast<XriDestoryFunc>(GetProcAddress(library, "DestroyXmlReader"));
    XmlReader const* reader = createXmlReader();
    XmlDoc* doc = nullptr;
    if (reader == nullptr)
    {
        Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 257, L"[%s], %s; failed to create xml reader", WORLD_CONFIG_TAG,
                   L"loadWorldConfigFile");
    }
    else if (wcscmp(getInterfaceVersion(), XML_READER_VERSION) != 0)
    {
        Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 263,
                   L"[%s], %s; xml interface version mismatch, current-version:%s, load-version:%s", WORLD_CONFIG_TAG,
                   L"loadWorldConfigFile", XML_READER_VERSION, getInterfaceVersion());  // ❓ argument order
    }
    else if (!reader->Initialize(nullptr, nullptr, false))
    {
        Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 268, L"[%s], %s; failed to initialize xml reader",
                   WORLD_CONFIG_TAG, L"loadWorldConfigFile");
    }
    else
    {
        doc = reader->Read(_filePath, static_cast<XmlPieceReader*>(nullptr));
        if (doc == nullptr)
        {
            Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 274,
                       L"[%s], %s; failed to read world config xml file, filePath:%s", WORLD_CONFIG_TAG,
                       L"loadWorldConfigFile", _filePath);
        }
        else if (setupWorldConfigList(doc, worldConfigList))
        {
            Log::Write(Log::LT_NOTICE, WORLD_CONFIG_FILE, 283,
                       L"[%s], %s; completed to load world config from xml file, filePath:%s", WORLD_CONFIG_TAG,
                       L"loadWorldConfigFile", _filePath);
            result = true;
        }
        else
        {
            Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 279, L"[%s], %s; failed to setup world config list",
                       WORLD_CONFIG_TAG, L"loadWorldConfigFile");
        }
    }
    if (reader != nullptr)
    {
        if (doc != nullptr)
            reader->Close(doc);
        destroyXmlReader(reader);
    }
    FreeLibrary(library);
    return result;
}

// 0xe8c0
bool WorldConfigManager::setupWorldConfigList(XmlDoc* xmlDoc, WorldConfigList* worldConfigList)
{
    if (xmlDoc == nullptr)
    {
        WORLD_CONFIG_CRASH(302, L"== CRASH == [%s], %s; invalid parameter, xml doc:0x%p", WORLD_CONFIG_TAG,
                           L"setupWorldConfigList", xmlDoc);
        return false;
    }
    XmlElement* root = xmlDoc->Root();
    if (root == nullptr)
    {
        Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 308, L"[%s], %s; root element is nothing", WORLD_CONFIG_TAG,
                   L"setupWorldConfigList");
        return false;
    }
    for (XmlElement const* element = root->FirstChildElement(); element != nullptr; element = element->NextElement())
    {
        if (!element->ToXmlNode()->IsValid())
        {
            Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 315, L"[%s], %s; invalid xml node, line:%d",
                       WORLD_CONFIG_TAG, L"setupWorldConfigList", element->LineNumber());
            return false;
        }
        if (_wcsicmp(element->Name(), L"gamed") != 0)
        {
            Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 321, L"[%s], %s; unknown element, elementName:%s, line:%d",
                       WORLD_CONFIG_TAG, L"setupWorldConfigList", element->Name(), element->LineNumber());
            return false;
        }
        wchar_t const* widStr = element->Attribute(L"wid");
        wchar_t const* ipAddrStr = element->Attribute(L"ip-address");
        wchar_t const* portStr = element->Attribute(L"internal-port");
        if (widStr == nullptr || ipAddrStr == nullptr || portStr == nullptr)
        {
            Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 330,
                       L"[%s], %s; invalid attribute; attribute string is null, widStr:0x%p, ipAddrStr:0x%p, "
                       L"portStr:0x%p, line:%d",
                       WORLD_CONFIG_TAG, L"setupWorldConfigList", widStr, ipAddrStr, portStr, element->LineNumber());
            return false;
        }
        if (wcslen(widStr) == 0 || wcslen(ipAddrStr) == 0 || wcslen(portStr) == 0)
        {
            Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 334,
                       L"[%s], %s; invalid attribute; string length is zero, widStr:%s, ipAddressStr:%s, portStr:%s, "
                       L"line:%d",
                       WORLD_CONFIG_TAG, L"setupWorldConfigList", widStr, ipAddrStr, portStr, element->LineNumber());
            return false;
        }
        // BUG: 0xe8c0 the result of Alloc is not checked for null.
        WorldConfig* worldConfig =
            static_cast<WorldConfig*>(Memory::_Manager[2]->Alloc(sizeof(WorldConfig), WORLD_CONFIG_FILE, 338));
        char ipAddrBuffer[32];
        ipAddrBuffer[30] = 0;
        WideCharToMultiByte(CP_ACP, 0, ipAddrStr, -1, ipAddrBuffer, 31, nullptr, nullptr);
        worldConfig->_ipAddress = inet_addr(ipAddrBuffer);
        worldConfig->_port = static_cast<unsigned short>(_wtoi(portStr));
        worldConfig->_wid = static_cast<unsigned short>(_wtoi(widStr));
        if (worldConfig->_wid == 0 || worldConfig->_ipAddress == 0 || worldConfig->_port == 0)
        {
            Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 340,
                       L"[%s], %s; invalid world config, wid:%u, ipAddress:%d, port:%u", WORLD_CONFIG_TAG,
                       L"setupWorldConfigList", worldConfig->_wid, worldConfig->_ipAddress, worldConfig->_port);
            Memory::_Manager[2]->Free(worldConfig, WORLD_CONFIG_FILE, 341);
            return false;
        }
        if (!worldConfigList->_configList.insert(std::make_pair(worldConfig->_wid, worldConfig)).second)
        {
            Log::Write(Log::LT_ERROR, WORLD_CONFIG_FILE, 348, L"[%s], %s; failed to add world config, wid:%u",
                       WORLD_CONFIG_TAG, L"setupWorldConfigList", worldConfig->_wid);
            Memory::_Manager[2]->Free(worldConfig, WORLD_CONFIG_FILE, 349);
            return false;
        }
        Log::Write(Log::LT_DEBUG, WORLD_CONFIG_FILE, 352, L"[%s], %s; loaded world config, wid:%u, ipAddress:%s, port:%u",
                   WORLD_CONFIG_TAG, L"setupWorldConfigList", worldConfig->_wid,
                   Network::GetAddressStringW(worldConfig->_ipAddress), worldConfig->_port);
    }
    return true;
}

// 0xede0
bool WorldConfigManager::createWorldConfigFile(wchar_t const* const worldConfigFilePath)
{
    if (worldConfigFilePath == nullptr)
    {
        WORLD_CONFIG_CRASH(363, L"== CRASH == [%s], %s; invalid parameter, worldConfigFilePath:0x%p",
                           WORLD_CONFIG_TAG, L"createWorldConfigFile", worldConfigFilePath);
        return false;
    }
    HANDLE fileHandle =
        CreateFileW(worldConfigFilePath, GENERIC_WRITE, 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        Log::Write(WORLD_CONFIG_FILE, 369, GetLastError(),
                   L"[%s], %s; failed to create world config xml file, worldConfigFilePath:%s", WORLD_CONFIG_TAG,
                   L"createWorldConfigFile", worldConfigFilePath);
        return false;
    }
    writeSampleConfigFormat(fileHandle);
    if (!CloseHandle(fileHandle))
    {
        Log::Write(WORLD_CONFIG_FILE, 376, GetLastError(), L"[%s], %s; failed to close file handle", WORLD_CONFIG_TAG,
                   L"createWorldConfigFile");
        return false;
    }
    return true;
}

// 0xef40
void WorldConfigManager::writeSampleConfigFormat(void* fileHandle)
{
    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        WORLD_CONFIG_CRASH(386, L"== CRASH == [%s], %s; invalid file handle", WORLD_CONFIG_TAG,
                           L"writeSampleConfigFormat");
        return;
    }
    writeConfigString(fileHandle, L"<?xml version='1.0' encoding='UTF-8'?>\r\n");
    writeConfigString(fileHandle, L"<gamed-list>\r\n");
    writeConfigString(fileHandle,
                      L"    <!-- <gamed wid='[world-id]' ip-address='[internal-IP]' internal-port='[internal-port]'/> -->\r\n");
    writeConfigString(fileHandle, L"</gamed-list>\r\n");
}

// 0xeff0
bool WorldConfigManager::writeConfigString(void* fileHandle, wchar_t const* const configString)
{
    if (fileHandle == INVALID_HANDLE_VALUE || configString == nullptr)
    {
        WORLD_CONFIG_CRASH(399, L"== CRASH == [%s], %s; invalid parameter, configString:0x%p", WORLD_CONFIG_TAG,
                           L"writeConfigString", configString);
        return false;
    }
    int length = WideCharToMultiByte(CP_UTF8, 0, configString, -1, nullptr, 0, nullptr, nullptr);
    char* buffer = static_cast<char*>(Memory::_Manager[2]->AllocZero(length, WORLD_CONFIG_FILE, 404));
    if (WideCharToMultiByte(CP_UTF8, 0, configString, -1, buffer, length, nullptr, nullptr) == 0)
    {
        Log::Write(WORLD_CONFIG_FILE, 406, GetLastError(), L"[%s], %s; failed to convert string, configString:%s",
                   WORLD_CONFIG_TAG, L"writeConfigString", configString);
        Memory::_Manager[2]->Free(buffer, WORLD_CONFIG_FILE, 407);
        return false;
    }
    DWORD written = 0;
    if (!WriteFile(fileHandle, buffer, length - 1, &written, nullptr))
    {
        Log::Write(WORLD_CONFIG_FILE, 413, GetLastError(), L"[%s], %s; failed to write config string, configString:%s",
                   WORLD_CONFIG_TAG, L"writeConfigString", configString);
        Memory::_Manager[2]->Free(buffer, WORLD_CONFIG_FILE, 414);
        return false;
    }
    Memory::_Manager[2]->Free(buffer, WORLD_CONFIG_FILE, 418);
    return true;
}
