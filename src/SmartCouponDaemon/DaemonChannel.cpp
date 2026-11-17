// DaemonChannel.obj (SmartCouponDaemon PDB). Source: .scratch/hr/DaemonChannel.c
#include <winsock2.h>
#include <windows.h>
#include <shlobj.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <new>
#include <vector>
#include "DaemonChannel.h"
#include "AlertSender.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "Packet.h"
#include "Session.h"
#include "XmlReader.h"

namespace
{
wchar_t const* const DCHANNEL_FILE = L"DaemonChannel.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
wchar_t const* const SESSION_SOURCE_FILE = L"source\\Session.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
wchar_t const* const CHANNEL_HEADER_FILE =                          // LIFT: No PDB symbol. The binary uses the literal.
    L"E:\\DailyBuild02\\SmartCouponDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";
}

// 0x835F8 ❓ module. The data is next to the DaemonChannel.obj strings.
wchar_t const* SmartCouponDaemonTypeDesc[2] = {L"none", L"gamed"};

// 0xc8c0
DChannelMgr::DChannelMgr()
{
}

// 0xc970
DChannelMgr::~DChannelMgr()
{
    _list.clear();
}

// 0xca00
void DChannelMgr::Finalize()
{
    for (std::map<GameEventDaemonId, DChannel*, std::less<GameEventDaemonId>,
                  StlAllocator<std::pair<GameEventDaemonId const, DChannel*>, 2> >::iterator it = _list.begin();
         it != _list.end(); ++it)
    {
        if (it->second != nullptr)
            it->second->removeReferenceCount(DCHANNEL_FILE, 47);
    }
    // BUG: 0xCA00 the map is not cleared. The pointers stay in _list after the release.
    Log::Write(Log::LT_DEBUG, DCHANNEL_FILE, 50, L"[ch-mgr], daemon session manager finalized");
}

// 0xcac0
bool DChannelMgr::SetupDaemonListFromXml(wchar_t const* xml)
{
    if (xml == nullptr || *xml == L'\0')
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 56, L"[ch-mgr], setup daemon list fail, invalid xmlfile");
        return false;
    }

    std::vector<DaemonInfo, StlAllocator<DaemonInfo, 2> > tempDaemonList;
    bool result = false;
    XmlReader const* reader = nullptr;
    XmlDoc* doc = nullptr;
    DaemonInfo** list = nullptr;
    int count = 0;
    XmlElement const* root = nullptr;
    XmlElement const* elem = nullptr;
    wchar_t const* version = nullptr;

    HMODULE library = LoadLibraryW(L"XmlReader_sv64.dll");
    if (library == nullptr)
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 75, L"[daemon-mgr], setup daemon list fail, %s missing",
                   L"XmlReader_sv64.dll");
        return false;
    }

    XriGetInterfaceVersion getInterfaceVersion =
        reinterpret_cast<XriGetInterfaceVersion>(GetProcAddress(library, "GetInterfaceVersion"));
    GetProcAddress(library, "SetMemAllocator");
    XriCreateFunc createXmlReader = reinterpret_cast<XriCreateFunc>(GetProcAddress(library, "CreateXmlReader"));
    XriDestoryFunc destroyXmlReader =
        reinterpret_cast<XriDestoryFunc>(GetProcAddress(library, "DestroyXmlReader"));

    reader = createXmlReader();
    if (reader == nullptr)
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 81, L"[daemon-mgr], setup daemon list fail, create xmlreader fail");
        FreeLibrary(library);
        return false;
    }

    version = getInterfaceVersion();
    if (_wcsicmp(version, L"15") != 0)
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 87,
                   L"[daemon-mgr], setup daemon list fail, xml version mismatch, current-version:%s, load-version:%s",
                   L"15", version);
        goto cleanup;
    }

    if (!reader->Initialize(nullptr, nullptr, false))
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 92, L"[daemon-mgr], setup daemon list fail, init xmlreader fail");
        goto cleanup;
    }

    doc = reader->Read(xml, static_cast<XmlPieceReader*>(nullptr));
    if (doc == nullptr)
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 98, L"[daemon-mgr], setup daemon list fail, read xml file fail");
        goto cleanup;
    }

    root = doc->Root();
    if (root != nullptr)
        elem = root->FirstChildElement();

    for (; elem != nullptr; elem = elem->NextElement())
    {
        if (!elem->ToXmlNode()->IsValid())
            break;

        wchar_t const* name = elem->Name();
        unsigned char type = 0;
        for (int i = 0; i < 2; ++i)
        {
            if (_wcsicmp(name, SmartCouponDaemonTypeDesc[i]) == 0)
            {
                type = static_cast<unsigned char>(i);
                break;
            }
        }

        if (_wcsicmp(name, L"gamed") != 0)
        {
            Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 145,
                       L"[daemon-mgr], setup daemon list exception, unknown element '%s', line:%d",
                       elem->Name(), elem->LineNumber());
            continue;
        }

        wchar_t const* wid = elem->Attribute(L"wid");
        wchar_t const* ipAddress = elem->Attribute(L"ip-address");
        wchar_t const* internalPort = elem->Attribute(L"internal-port");
        if (wid == nullptr || *wid == L'\0' || ipAddress == nullptr || *ipAddress == L'\0' ||
            internalPort == nullptr || *internalPort == L'\0')
        {
            Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 132,
                       L"[daemon-mgr], setup daemon list exception, invalid attribute value, line:%d",
                       elem->LineNumber());
            continue;
        }

        char ip[32] = {};
        WideCharToMultiByte(CP_ACP, 0, ipAddress, -1, ip, 31, nullptr, nullptr);

        DaemonInfo info;
        info.daemonId._type = type;
        info.daemonId._wid = static_cast<unsigned short>(_wtoi(wid));
        info.daemonId._reserved = 0;
        info.ipaddr = inet_addr(ip);
        info.port = static_cast<unsigned short>(_wtoi(internalPort));
        tempDaemonList.push_back(info);
    }

    count = static_cast<int>(tempDaemonList.size());
    if (count == 0)
    {
        Log::Write(Log::LT_NOTICE, DCHANNEL_FILE, 166, L"[daemon-mgr], setup daemon list with xml complete, xml:%s", xml);
        result = true;
        goto cleanup;
    }

    list = static_cast<DaemonInfo**>(Memory::_Manager[2]->Alloc(sizeof(DaemonInfo*) * count, DCHANNEL_FILE, 153));
    for (int i = 0; i < count; ++i)
    {
        list[i] = static_cast<DaemonInfo*>(Memory::_Manager[2]->Alloc(sizeof(DaemonInfo), DCHANNEL_FILE, 156));
        *list[i] = tempDaemonList[i];
    }

    if (SetupDaemonList(list, count))
    {
        Log::Write(Log::LT_NOTICE, DCHANNEL_FILE, 166, L"[daemon-mgr], setup daemon list with xml complete, xml:%s", xml);
        result = true;
    }

cleanup:
    if (list != nullptr)
    {
        for (int i = 0; i < count; ++i)
        {
            if (list[i] != nullptr)
                Memory::_Manager[2]->Free(list[i], DCHANNEL_FILE, 173);
        }
        Memory::_Manager[2]->Free(list, DCHANNEL_FILE, 175);
    }
    if (doc != nullptr)
        reader->Close(doc);
    destroyXmlReader(reader);
    FreeLibrary(library);
    return result;
}

// 0xd270
bool DChannelMgr::SetupDaemonList(DaemonInfo** list, int count)
{
    if (list == nullptr)
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 192, L"[daemon-mgr], setup daemon list fail, null list");
        return false;  // LIFT: xor al, al at 0xd2a6
    }

    for (int i = 0; i < count; ++i)
    {
        DaemonInfo* info = list[i];
        if (info == nullptr)
            continue;

        DChannel* second = FindDaemon(&info->daemonId);
        if (second == nullptr)
        {
            void* mem = Memory::_Manager[2]->Alloc(sizeof(DChannel), DCHANNEL_FILE, 213);
            second = mem != nullptr ? new (mem) DChannel(info->daemonId, info->ipaddr, info->port) : nullptr;
            AddDaemon(second);
            Log::Write(Log::LT_NOTICE, DCHANNEL_FILE, 215, L"[daemon-mgr], daemon #%d added, ip:%s, port:%d",
                       info->daemonId._wid, Network::GetAddressStringW(info->ipaddr), info->port);
        }
        else
        {
            Session const* session = second->GetSession();
            if (session == nullptr)
            {
                second->_addr = info->ipaddr;
                second->_port = info->port;
                Log::Write(Log::LT_NOTICE, DCHANNEL_FILE, 207,
                           L"[daemon-mgr], daemon #%d's ip/port changed, ip:%s, port:%d",
                           info->daemonId._wid, Network::GetAddressStringW(info->ipaddr), info->port);
            }
            else
            {
                Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 203,
                           L"[daemon-mgr], setup daemon list exception, change daemon #%d's ip/port fail, already bound "
                           L"with session, session:0x%016I64X",
                           info->daemonId._wid, session->_id);
                const_cast<Session*>(session)->removeReferenceCount(CHANNEL_HEADER_FILE, 52);
            }
        }
        if (second != nullptr)
            second->removeReferenceCount(DCHANNEL_FILE, 217);
    }

    Log::Write(Log::LT_NOTICE, DCHANNEL_FILE, 221, L"[daemon-mgr], setup daemon list complete, daemon-count:%d", count);
    return true;
}

// 0xd5c0
bool DChannelMgr::CreateDaemonListXml(wchar_t const* xml)
{
    if (xml == nullptr || *xml == L'\0')
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 228,
                   L"== CRASH == [daemon-mgr], create daemon list xml fail, invalid parameter");
        AlertSender::Write(DCHANNEL_FILE, 228, L"== CRASH == [daemon-mgr], create daemon list xml fail, invalid parameter");
        return false;
    }

    HANDLE file = CreateFileW(xml, GENERIC_WRITE, 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE)
    {
        DWORD lastError = GetLastError();
        if (lastError != ERROR_PATH_NOT_FOUND)
        {
            Log::Write(DCHANNEL_FILE, 237, lastError, L"[daemon-mgr], create daemon list xml fail, create file fail");
            return false;
        }

        wchar_t drive[3];
        wchar_t dir[256];
        wchar_t name[256];
        wchar_t ext[256];
        if (_wsplitpath_s(xml, drive, 3, dir, 256, name, 256, ext, 256) != 0)
        {
            Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 248, L"[daemon-mgr], create daemon list xml fail, analyze path fail");
            return false;
        }
        if (drive[0] == L'\0' || dir[0] == L'\0' || name[0] == L'\0' || ext[0] == L'\0')
        {
            Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 253,
                       L"[daemon-mgr], create daemon list xml fail, not fully qualified file name, xml:%s", xml);
            return false;
        }

        wchar_t path[260];
        if (_wmakepath_s(path, 260, drive, dir, nullptr, nullptr) != 0)
        {
            Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 258, L"[daemon-mgr], create daemon list xml fail, make path fail");
            return false;
        }

        int error = SHCreateDirectoryExW(nullptr, path, nullptr);
        if (error != 0)
        {
            Log::Write(DCHANNEL_FILE, 263, error, L"[daemon-mgr], create daemon list xml fail, make directory fail");
            return false;
        }

        file = CreateFileW(xml, GENERIC_WRITE, 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file == INVALID_HANDLE_VALUE)
        {
            Log::Write(DCHANNEL_FILE, 269, GetLastError(), L"[daemon-mgr], create daemon list xml fail, create file fail");
            return false;
        }
    }

    writeFileUtf8(file, L"<?xml version='1.0' encoding='UTF-8'?>\r\n");
    writeFileUtf8(file, L"<gamed-list>\r\n");
    writeFileUtf8(file,
                  L"    <!-- <gamed wid='[world-id]' ip-address='[internal-IP]' internal-port='[internal-port]'/> -->\r\n");
    writeFileUtf8(file, L"</gamed-list>\r\n");
    CloseHandle(file);
    return true;
}

// 0xd8e0
void DChannelMgr::writeFileUtf8(void* handle, wchar_t const* format, ...)
{
    va_list args;
    va_start(args, format);
    int length = _vscwprintf(format, args) + 1;
    // The original uses _malloca for both buffers.
    std::vector<wchar_t> wide(length);
    vswprintf_s(&wide[0], length, format, args);
    va_end(args);

    // LIFT: 0xd99e passes cchWideChar = length - 1, so the terminating zero is not converted or written.
    int size = WideCharToMultiByte(CP_UTF8, 0, &wide[0], length - 1, nullptr, 0, nullptr, nullptr);
    std::vector<char> utf8(size + 1);
    int converted = WideCharToMultiByte(CP_UTF8, 0, &wide[0], length - 1, &utf8[0], size, nullptr, nullptr);

    DWORD written = 0;
    WriteFile(handle, &utf8[0], converted, &written, nullptr);  // LIFT: 0xda4c size = WideCharToMultiByte result
}

// 0xdab0
DChannelMgr::ErrCode DChannelMgr::AddDaemon(DChannel* channel)
{
    if (channel == nullptr)
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 316, L"[daemon-mgr], register daemon fail; null daemon parameter");
        return ERR_INVALID_PARAM;
    }

    _lock.Enter();
    bool inserted = _list.insert(std::pair<GameEventDaemonId const, DChannel*>(channel->_daemonId, channel)).second;
    if (inserted)
        channel->addReferenceCount(DCHANNEL_FILE, 327);
    _lock.Leave();

    if (inserted)
    {
        Log::Write(Log::LT_DEBUG, DCHANNEL_FILE, 332,
                   L"[daemon-mgr], daemon registered, id:%d, wid:%d, type:%d, ip:%s, port:%d",
                   static_cast<unsigned int>(channel->GetId()), channel->_daemonId._wid, channel->_daemonId._type,
                   Network::GetAddressStringW(channel->_addr), channel->_port);
        return ERR_SUCCESS;
    }

    Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 336,
               L"[daemon-mgr], register daemon fail; already exists, req-id:%d, req-wid:%d, req-type:%d, req-ip:%s, "
               L"req-port:%d",
               static_cast<unsigned int>(channel->GetId()), channel->_daemonId._wid, channel->_daemonId._type,
               Network::GetAddressStringW(channel->_addr), channel->_port);
    return ERR_ADDWORLD_ALREADY_REGISTERED;
}

// 0xdc50
DChannel* DChannelMgr::FindDaemon(GameEventDaemonId const* daemonId)
{
    DChannel* second = nullptr;
    _lock.Enter();
    std::map<GameEventDaemonId, DChannel*, std::less<GameEventDaemonId>,
             StlAllocator<std::pair<GameEventDaemonId const, DChannel*>, 2> >::iterator it = _list.find(*daemonId);
    if (it != _list.end())
    {
        second = it->second;
        second->addReferenceCount(DCHANNEL_FILE, 376);
    }
    _lock.Leave();
    return second;
}

// 0xdcd0
bool DChannelMgr::ReplaceDaemon(DChannel* newDaemon)
{
    if (newDaemon == nullptr)
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 388, L"[daemon-mgr], replace daemon fail; null parameter");
        return false;
    }

    DChannel* second = nullptr;
    _lock.Enter();
    std::map<GameEventDaemonId, DChannel*, std::less<GameEventDaemonId>,
             StlAllocator<std::pair<GameEventDaemonId const, DChannel*>, 2> >::iterator it =
        _list.find(newDaemon->_daemonId);
    if (it != _list.end())
    {
        second = it->second;
        _list.erase(it);
    }
    bool inserted =
        _list.insert(std::pair<GameEventDaemonId const, DChannel*>(newDaemon->_daemonId, newDaemon)).second;
    if (inserted)
        newDaemon->addReferenceCount(DCHANNEL_FILE, 409);
    _lock.Leave();

    if (second != nullptr)
        second->removeReferenceCount(DCHANNEL_FILE, 415);
    return inserted;
}

// 0xde10
bool DChannelMgr::OnAccept(Session const* session) const
{
    Log::Write(Log::LT_NOTICE, DCHANNEL_FILE, 422, L"[daemon-ch], 0x%.16I64X, %I64d, accept",
               session != nullptr ? session->_id : 0ULL, 0LL);
    return true;
}

// 0xde60
bool DChannelMgr::OnConnect(Session const* session, bool) const
{
    unsigned long long id = session != nullptr ? session->_id : 0ULL;
    Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 428, L"== CRASH == [daemon-ch], 0x%.16I64X, %I64d, connect, invalid call",
               id, 0LL);
    AlertSender::Write(DCHANNEL_FILE, 428, L"== CRASH == [daemon-ch], 0x%.16I64X, %I64d, connect, invalid call", id,
                       0LL);
    return false;
}

// 0xdee0
void DChannelMgr::OnClose(Session const* session, bool) const
{
    Channel* channel = session->GetChannel();
    if (channel != nullptr)
    {
        Log::Write(Log::LT_NOTICE, DCHANNEL_FILE, 438, L"[daemon-ch], 0x%.16I64X, %I64d, close", session->_id,
                   channel->GetId());
        channel->RemoveSession(session, false);
        channel->removeReferenceCount(SESSION_SOURCE_FILE, 1059);
    }
    else
    {
        Log::Write(Log::LT_NOTICE, DCHANNEL_FILE, 443, L"[daemon-ch], 0x%.16I64X, %I64d, close without channel",
                   session->_id, 0LL);
    }
}

// 0xdfe0
bool DChannelMgr::PacketHandler(Session const* session, Packet const* packet) const
{
    if (session == nullptr || packet == nullptr)
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 452, L"== CRASH == [gamedmgr], handle packet failed; invalid parameter");
        AlertSender::Write(DCHANNEL_FILE, 452, L"== CRASH == [gamedmgr], handle packet failed; invalid parameter");
        return false;
    }

    short const* command = reinterpret_cast<short const*>(packet->CurHeader + 1);
    if (command == nullptr)
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 459,
                   L"[gamedmgr], invalid packet; command is null, cmd:0x%p, sessionId:0x%I64X, portId:%u, "
                   L"sessionIndex:%u",
                   static_cast<void const*>(nullptr), session->_id, static_cast<unsigned int>(session->_id >> 32),
                   static_cast<unsigned int>(session->_id));
        return false;
    }

    bool result = false;
    Channel* channel = session->GetChannel();
    unsigned long long channelId = channel != nullptr ? channel->GetId() : 0ULL;
    short cmd = *command;

    // BUG: 0xDFE0 there is no check for cmd < 10. A large cmd reads past the handler list.
    if (cmd < 0 || SmartCouponPacketSmartCouponSideHandlerList[cmd] == nullptr)
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 468, L"[daemon-ch], 0x%.16I64X, %I64d, handle fail, no such cmd, cmd:%d",
                   session->_id, channelId, static_cast<int>(cmd));
    }
    else if (channel != nullptr)
    {
        Log::Write(Log::LT_DEBUG, DCHANNEL_FILE, 497, L"[daemon-ch], 0x%.16I64X, %I64d, handle start, cmd:%d",
                   session->_id, channelId, static_cast<int>(cmd));
        result = SmartCouponPacketSmartCouponSideHandlerList[cmd](session, packet);
        Log::Write(Log::LT_DEBUG, DCHANNEL_FILE, 499, L"[daemon-ch], 0x%.16I64X, %I64d, handle end, cmd:%d",
                   session->_id, channelId, static_cast<int>(cmd));
    }
    else if (cmd == 1)
    {
        Log::Write(Log::LT_DEBUG, DCHANNEL_FILE, 478, L"[daemon-ch], 0x%.16I64X, %I64d, handle start, cmd:%d",
                   session->_id, channelId, static_cast<int>(cmd));
        result = SmartCouponPacketSmartCouponSideHandlerList[cmd](session, packet);
        Log::Write(Log::LT_DEBUG, DCHANNEL_FILE, 480, L"[daemon-ch], 0x%.16I64X, %I64d, handle end, cmd:%d",
                   session->_id, channelId, static_cast<int>(cmd));
    }
    else
    {
        Log::Write(Log::LT_ERROR, DCHANNEL_FILE, 484,
                   L"[gamedmgr], invalid packet command of not authorized session, command:%d, sessionId:0x%I64X, "
                   L"portId:%u, sessionIndex:%u",
                   static_cast<int>(cmd), session->_id, static_cast<unsigned int>(session->_id >> 32),
                   static_cast<unsigned int>(session->_id));
    }

    if (channel != nullptr)
        channel->removeReferenceCount(SESSION_SOURCE_FILE, 1059);
    return result;
}
