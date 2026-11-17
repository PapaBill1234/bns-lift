// CacheD.obj (CacheGate PDB).
#include "CacheD.h"

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "AlertSender.h"
#include "CacheGate.h"
#include "Connection.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "PipeConsole.h"
#include "Session.h"
#include "XmlReader.h"

static wchar_t const CACHED_FILE[] = L"CacheD.cpp";
// The inlined Channel::Close and Session release use the Channel.h path.
static wchar_t const CHANNEL_HEADER_FILE[] =
    L"E:\\DailyBuild02\\CacheGate-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";

// 0x23a0
unsigned long long CacheD::GetId()
{
    return _id;
}

// 0x23b0
CacheD::~CacheD()
{
}

// 0x23e0
bool CacheD::TryConnect()
{
    _lock.Enter();
    // LIFT: LTCG folded the portId (2), timeout and reconnect arguments.
    bool result = MakeSession(2, _addr, _port, 0, true);
    _lock.Leave();
    return result;
}

// 0x2430
void CacheD::Initialize(unsigned short id, unsigned long addr, unsigned short port, char status)
{
    _lock.Enter();
    _id = id;
    _addr = addr;
    _port = port;
    _status = 0;  // The status argument is not used.
    _lock.Leave();

    swprintf_s(_daemonInvalidInfoKey, 129, L"cached disconnected wid:%d", id);

    // Inlined PipeConsole::SetInvalidInfo(_daemonInvalidInfoKey, true).
    if (CacheGate::_instance != nullptr && CacheGate::_instance->pipeConsole != nullptr)
    {
        PipeConsole* console = CacheGate::_instance->pipeConsole;
        console->_lock.Enter();
        PipeConsole::ItemNode* node = console->_invalid._head._next;
        while (node != &console->_invalid._tail)
        {
            if (wcscmp(node->_key, _daemonInvalidInfoKey) == 0)
                break;
            node = node->_next;
        }
        if (node == &console->_invalid._tail)
            PipeConsole::addNode(console->_invalid, _daemonInvalidInfoKey, L"");  // LIFT: LTCG folded valueString. addNode (0x15ED0) does not read r8 and copies L"" (0x3B700).
        console->_lock.Leave();
    }
}

// 0x2530
int CacheD::Verify(Session const* session)
{
    _lock.Enter();
    if (_addr == session->_connection->_ip && _port == session->_connection->_portNumber)
    {
        if (_session == nullptr)
            SetSession(session);
        _lock.Leave();
        return 0;
    }
    _lock.Leave();
    return 2;
}

// 0x25c0
CacheDList::~CacheDList()
{
    if (_cachedMap != nullptr)
    {
        clear();
        _cachedMap->~CacheDMap();
        Memory::_Manager[2]->Free(_cachedMap, CACHED_FILE, 124);
    }
}

// 0x2660
bool CacheDList::Initialize()
{
    void* buffer = Memory::_Manager[2]->Alloc(sizeof(CacheDMap), CACHED_FILE, 130);
    _cachedMap = buffer != nullptr ? new (buffer) CacheDMap() : nullptr;
    return _cachedMap != nullptr;
}

// 0x2710
CacheD* CacheDList::Find(unsigned short id)
{
    CacheD* result = nullptr;
    _lock.Enter();
    CacheDMap::iterator it = _cachedMap->find(id);
    if (it != _cachedMap->end() && it->second != nullptr)
    {
        result = it->second;
        result->addReferenceCount(CACHED_FILE, 151);
    }
    _lock.Leave();
    return result;
}

// 0x27d0
bool CacheDList::MakeSessionAll()
{
    _lock.Enter();
    for (CacheDMap::iterator it = _cachedMap->begin(); it != _cachedMap->end(); ++it)
    {
        CacheD* cached = it->second;
        if (cached != nullptr)
        {
            // Inlined CacheD::TryConnect.
            cached->_lock.Enter();
            bool connected = cached->MakeSession(2, cached->_addr, cached->_port, 0, true);  // LIFT: folded args
            cached->_lock.Leave();
            if (connected)
                Log::Write(Log::LT_DEBUG, CACHED_FILE, 169, L"[cached list], connect, wid:%d, ipAddress:%s",
                           cached->_id, Network::GetAddressStringW(cached->_addr));
            else
                Log::Write(Log::LT_DEBUG, CACHED_FILE, 171, L"[cached list], try connect fail, wid:%d, ipAddress:%s",
                           cached->_id, Network::GetAddressStringW(cached->_addr));
        }
        else
        {
            Log::Write(Log::LT_DEBUG, CACHED_FILE, 175, L"[cached list], MakeSessionAll connect fail");
        }
    }
    _lock.Leave();
    return true;
}

// 0x2940
void CacheDList::RemoveSessionAll()
{
    _lock.Enter();
    for (CacheDMap::iterator it = _cachedMap->begin(); it != _cachedMap->end(); ++it)
    {
        CacheD* cached = it->second;
        if (cached == nullptr)
            continue;
        Session* session = const_cast<Session*>(cached->GetSession());
        if (session != nullptr)
        {
            session->StopReconnect();
            session->removeReferenceCount(CHANNEL_HEADER_FILE, 52);
        }
        cached->Close();
        cached->removeReferenceCount(CACHED_FILE, 204);
    }
    _cachedMap->clear();
    _lock.Leave();
    Log::Write(Log::LT_DEBUG, CACHED_FILE, 214, L"[cached list], RemoveSessionAll success,");
}

// 0x2b20
bool CacheDList::LoadCachedListConfigFile(wchar_t const* fileName, bool reload)
{
    HMODULE module = LoadLibraryW(L"XmlReader_sv64.dll");
    if (module == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHED_FILE, 233, L"%s missing.", L"XmlReader_sv64.dll");
        return false;
    }

    XriGetInterfaceVersion getVersion = reinterpret_cast<XriGetInterfaceVersion>(GetProcAddress(module, "GetInterfaceVersion"));
    XriSetMemAllocator setAllocator = reinterpret_cast<XriSetMemAllocator>(GetProcAddress(module, "SetMemAllocator"));
    (void)setAllocator;  // The function does not call it.
    XriCreateFunc createReader = reinterpret_cast<XriCreateFunc>(GetProcAddress(module, "CreateXmlReader"));
    XriDestoryFunc destroyReader = reinterpret_cast<XriDestoryFunc>(GetProcAddress(module, "DestroyXmlReader"));

    wchar_t const* version = getVersion();
    if (version == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHED_FILE, 245, L"xml-reader version invalid");
        return false;  // BUG: 0x2b20 the library is not freed on this path.
    }
    if (_wcsicmp(L"15", version) != 0)
        Log::Write(Log::LT_ERROR, CACHED_FILE, 240,
                   L"xml-reader version invalid, current version : %s, loaded version : %s", L"15", version);

    bool result = false;
    _lock.Enter();
    XmlReader const* reader = createReader();
    if (reader == nullptr)
    {
        result = true;  // BUG: 0x2b20 a failed reader gives success.
    }
    else
    {
        reader->Initialize(nullptr, nullptr, false);
        XmlDoc* doc = reader->Read(fileName, static_cast<XmlPieceReader*>(nullptr));
        if (doc != nullptr && doc->Root() != nullptr)
        {
            XmlElement* root = doc->Root();
            XmlNode* rootNode = root->ToXmlNode();
            if (rootNode == nullptr)
            {
                reader->Close(doc);
            }
            else
            {
                XmlNode const* node = rootNode->FirstChild();
                result = true;
                while (node != nullptr && node->IsValid())
                {
                    if (node->Type() == 1)
                    {
                        XmlElement const* element = node->ToXmlElement();
                        if (element == nullptr)
                        {
                            result = false;
                            break;
                        }
                        if (wcsncmp(element->Name(), L"cached", 7) == 0)
                        {
                            unsigned short wid = static_cast<unsigned short>(_wtoi(element->Attribute(L"wid")));
                            char ipText[32];
                            WideCharToMultiByte(CP_ACP, 0, element->Attribute(L"ip-address"), -1, ipText, 31, nullptr, nullptr);
                            unsigned long ip = inet_addr(ipText);
                            unsigned short port = static_cast<unsigned short>(_wtoi(element->Attribute(L"economy-port")));

                            CacheD* existing = Find(wid);
                            if (existing == nullptr)
                            {
                                if (!addCacheD(wid, ip, port, reload))
                                    Log::Write(Log::LT_ERROR, CACHED_FILE, 285,
                                               L"[cached list], failed to add new cached, wid:%d, ip-address:%s, port:%d",
                                               wid, Network::GetAddressStringW(ip), port);
                            }
                            else if (existing->_addr == ip && existing->_port == port)
                            {
                                Log::Write(Log::LT_DEBUG, CACHED_FILE, 295,
                                           L"[cached list], load cached success, already exists, wid:%d, ip-address:%s, port:%d",
                                           wid, Network::GetAddressStringW(ip), port);
                                existing->removeReferenceCount(CACHED_FILE, 296);
                            }
                            else
                            {
                                Log::Write(Log::LT_DEBUG, CACHED_FILE, 302,
                                           L"[cached list], load cached success, update cached info OLD , wid:%d, ip-address:%s, port:%d"
                                           L"NEW , wid:%d, ip-address:%s, port:%d",
                                           existing->_id, Network::GetAddressStringW(existing->_addr), existing->_port,
                                           wid, Network::GetAddressStringW(ip), port);
                                if (!del(existing->_id))
                                {
                                    Log::Write(Log::LT_ERROR, CACHED_FILE, 307,
                                               L"[cached list], failed to delete old cahed info, wid:%d, ip-address:%s, port:%d",
                                               existing->_id, Network::GetAddressStringW(existing->_addr), existing->_port);
                                    existing->removeReferenceCount(CACHED_FILE, 308);
                                }
                                else if (!addCacheD(wid, ip, port, reload))
                                {
                                    Log::Write(Log::LT_ERROR, CACHED_FILE, 315,
                                               L"[cached list], failed to add new cached, wid:%d, ip-address:%s, port:%d",
                                               wid, Network::GetAddressStringW(ip), port);
                                    existing->removeReferenceCount(CACHED_FILE, 316);
                                }
                                else
                                {
                                    Session* session = const_cast<Session*>(existing->GetSession());
                                    if (session != nullptr)
                                    {
                                        session->StopReconnect();
                                        session->removeReferenceCount(CHANNEL_HEADER_FILE, 52);
                                    }
                                    existing->Close();
                                    existing->removeReferenceCount(CACHED_FILE, 329);
                                }
                            }
                        }
                    }
                    node = node->Next();
                }
                reader->Close(doc);
            }
        }
    }
    _lock.Leave();
    if (reader != nullptr)
        destroyReader(reader);
    FreeLibrary(module);
    return result;
}

// 0x3120
bool CacheDList::CreateCachedListConfigFile(wchar_t const* const fileName)
{
    if (fileName == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHED_FILE, 361, L"== CRASH == [cached list], invalid parameter, fileName:0x%p", fileName);
        AlertSender::Write(CACHED_FILE, 361, L"== CRASH == [cached list], invalid parameter, fileName:0x%p", fileName);
        return false;
    }
    HANDLE file = CreateFileW(fileName, GENERIC_WRITE, 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
    {
        Log::Write(CACHED_FILE, 367, GetLastError(), L"[cached list], failed to create config xml file, configFilePath:%s", fileName);
        return false;
    }
    writeSampleConfigFormat(file);
    if (!CloseHandle(file))
    {
        Log::Write(CACHED_FILE, 374, GetLastError(), L"[cached list], failed to close file handle");
        return false;
    }
    return true;
}

// 0x3230
void CacheDList::writeSampleConfigFormat(void* fileHandle)
{
    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        Log::Write(Log::LT_ERROR, CACHED_FILE, 384, L"== CRASH == [cached list], invalid file handle");
        AlertSender::Write(CACHED_FILE, 384, L"== CRASH == [cached list], invalid file handle");
        return;
    }
    writeConfigString(fileHandle, L"<?xml version='1.0' encoding='UTF-8'?>\r\n");
    writeConfigString(fileHandle, L"<cached-list>\r\n");
    writeConfigString(fileHandle,
                      L"    <!-- <cached wid='[world-id]' ip-address='[internal-IP]' internal-port='[internal-port]' "
                      L"economy-port='[economy-port]'/> -->\r\n");
    writeConfigString(fileHandle, L"</cached-list>\r\n");
}

// 0x32c0
bool CacheDList::writeConfigString(void* fileHandle, wchar_t const* configString)
{
    if (fileHandle == INVALID_HANDLE_VALUE || configString == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHED_FILE, 397, L"== CRASH == [cached list], invalid parameter, configString:0x%p", configString);
        AlertSender::Write(CACHED_FILE, 397, L"== CRASH == [cached list], invalid parameter, configString:0x%p", configString);
        return false;
    }
    int size = WideCharToMultiByte(CP_UTF8, 0, configString, -1, nullptr, 0, nullptr, nullptr);
    char* buffer = static_cast<char*>(Memory::_Manager[2]->AllocZero(size, CACHED_FILE, 402));
    if (WideCharToMultiByte(CP_UTF8, 0, configString, -1, buffer, size, nullptr, nullptr) == 0)
    {
        Log::Write(CACHED_FILE, 404, GetLastError(), L"[cached list], failed to convert string, configString:%s", configString);
        Memory::_Manager[2]->Free(buffer, CACHED_FILE, 405);
        return false;
    }
    DWORD written = 0;
    if (!WriteFile(fileHandle, buffer, size - 1, &written, nullptr))
    {
        Log::Write(CACHED_FILE, 411, GetLastError(), L"[cached list], failed to write config string, configString:%s", configString);
        Memory::_Manager[2]->Free(buffer, CACHED_FILE, 412);
        return false;
    }
    Memory::_Manager[2]->Free(buffer, CACHED_FILE, 416);
    return true;
}

// 0x3490
bool CacheDList::add(CacheD* cached)
{
    if (cached == nullptr || cached->_id == 0)
    {
        Log::Write(Log::LT_ERROR, CACHED_FILE, 424, L"[cached list], add cached fail, add invalid cached.");
        return false;
    }
    _lock.Enter();
    bool result = _cachedMap->insert(CacheDMap::value_type(cached->_id, cached)).second;
    if (result)
        cached->addReferenceCount(CACHED_FILE, 434);
    _lock.Leave();
    return result;
}

// 0x3550
bool CacheDList::del(unsigned short id)
{
    if (id == 0)
    {
        Log::Write(Log::LT_ERROR, CACHED_FILE, 444, L"[cached list], del fail, invalid param, id : %d", id);
        return false;
    }
    _lock.Enter();
    CacheDMap::iterator it = _cachedMap->find(id);
    if (it != _cachedMap->end())
    {
        if (it->second != nullptr)
            it->second->removeReferenceCount(CACHED_FILE, 454);
        _cachedMap->erase(it);
    }
    _lock.Leave();
    return true;
}

// 0x3640
void CacheDList::clear()
{
    _lock.Enter();
    for (CacheDMap::iterator it = _cachedMap->begin(); it != _cachedMap->end(); ++it)
    {
        if (it->second != nullptr)
            it->second->removeReferenceCount(CACHED_FILE, 472);
    }
    _cachedMap->clear();
    _lock.Leave();
}

// 0x3700
bool CacheDList::addCacheD(unsigned short wid, unsigned long addr, unsigned short port, bool connect)
{
    void* buffer = Memory::_Manager[2]->Alloc(sizeof(CacheD), CACHED_FILE, 485);
    if (buffer == nullptr)
        return false;
    CacheD* cached = new (buffer) CacheD();
    cached->Initialize(wid, addr, port, 0);
    if (!add(cached))
    {
        cached->removeReferenceCount(CACHED_FILE, 494);
        return false;
    }
    if (connect)
        cached->TryConnect();
    cached->removeReferenceCount(CACHED_FILE, 502);
    return true;
}
