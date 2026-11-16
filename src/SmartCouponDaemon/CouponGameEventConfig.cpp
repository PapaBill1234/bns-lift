// CouponGameEventConfig.obj (SmartCouponDaemon PDB). Source: .scratch/hr/CouponGameEventConfig.c
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <wchar.h>
#include "CouponGameEventConfig.h"
#include "Console.h"
#include "Daemon.h"
#include "DaemonChannel.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "XmlReader.h"

namespace
{
wchar_t const* const GAME_EVENT_CONFIG_FILE = L"..\\Shared\\CouponGameEventConfig.cpp";  // ❓ name
}

// ❓ Inlined in each fail path: write the start log to the console, then wait 5 seconds.
void GameEventConfig::writeStartLog(Console* console, wchar_t const* message)
{
    if (console != nullptr)
    {
        console->WriteStartLog(0, message);
        Sleep(5000);
    }
}

// 0x2a40
GameEventConfig::GameEventConfig()
{
}

// 0x2b10
GameEventConfig::~GameEventConfig()
{
    for (auto it = _gameEventList.begin(); it != _gameEventList.end(); ++it)
    {
        if (it->second != nullptr)
            Memory::_Manager[2]->Free(it->second, GAME_EVENT_CONFIG_FILE, 36);
    }
    _gameEventList.clear();
}

// 0x2c80
bool GameEventConfig::SetupGameEventListFromXml(wchar_t const* xml)
{
    Console* console = Daemon::Instance->console;

    if (xml == nullptr || *xml == L'\0')
    {
        wchar_t const* message = L"[game-event-cfg], setup game event list fail, invalid xmlfile";
        Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 48, message);
        writeStartLog(console, message);
        return false;
    }

    HMODULE library = LoadLibraryW(L"XmlReader_sv64.dll");
    if (library == nullptr)
    {
        Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 64, L"[game-event-cfg], setup game event list fail, %s missing",
                   L"XmlReader_sv64.dll");
        if (console != nullptr)
        {
            console->WriteStartLog(0, L"[game-event-cfg], setup game event list fail, %s missing", L"XmlReader_sv64.dll");
            Sleep(5000);
        }
        return false;
    }

    // BUG: 0x2c80 DestroyXmlReader and FreeLibrary are never called. The reader, the doc and the dll leak.
    GetInterfaceVersionFunc getInterfaceVersion =
        reinterpret_cast<GetInterfaceVersionFunc>(GetProcAddress(library, "GetInterfaceVersion"));
    GetProcAddress(library, "SetMemAllocator");
    CreateXmlReaderFunc createXmlReader = reinterpret_cast<CreateXmlReaderFunc>(GetProcAddress(library, "CreateXmlReader"));
    GetProcAddress(library, "DestroyXmlReader");

    XmlReader* reader = createXmlReader();
    if (reader == nullptr)
    {
        wchar_t const* message = L"[game-event-cfg], setup game event list fail, create xmlreader fail";
        Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 71, message);
        writeStartLog(console, message);
        return false;
    }

    wchar_t const* version = getInterfaceVersion();
    if (_wcsicmp(version, L"15") != 0)
    {
        wchar_t const* format =
            L"[game-event-cfg], setup game event list fail, xml version mismatch, current-version:%s, load-version:%s";
        Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 78, format, L"15", version);
        if (console != nullptr)
        {
            console->WriteStartLog(0, format, L"15", version);
            Sleep(5000);
        }
        return false;
    }

    if (!reader->Initialize(nullptr, nullptr, false))
    {
        wchar_t const* message = L"[game-event-cfg], setup game event list fail, init xmlreader fail";
        Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 84, message);
        writeStartLog(console, message);
        return false;
    }

    XmlDoc* doc = reader->Read(xml, static_cast<XmlPieceReader*>(nullptr));
    if (doc == nullptr)
    {
        wchar_t const* message = L"[game-event-cfg], setup game event list fail, read xml file fail";
        Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 91, message);
        writeStartLog(console, message);
        return false;
    }

    XmlElement const* root = doc->Root();
    if (root == nullptr)
        return true;

    for (XmlElement const* i = root->FirstChildElement(); i != nullptr; i = i->NextElement())
    {
        if (!i->ToXmlNode()->IsValid())
            break;

        wchar_t const* daemonName = i->Name();
        int daemonType = 0;
        for (; daemonType < 2; ++daemonType)
        {
            if (_wcsicmp(daemonName, SmartCouponDaemonTypeDesc[daemonType]) == 0)
                break;
        }
        if (daemonType == 2 || daemonType == 0)
        {
            Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 186,
                       L"[game-event-cfg], setup game-event-list exception, unknown element '%s', line:%d", i->Name(),
                       i->LineNumber());
            continue;
        }

        for (XmlElement const* c = i->FirstChildElement(); c != nullptr; c = c->NextElement())
        {
            if (!c->ToXmlNode()->IsValid())
                break;

            if (_wcsicmp(c->Name(), L"event") != 0)
            {
                Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 178,
                           L"[game-event-cfg], setup game-event-list exception, unknown element '%s', line:%d", c->Name(),
                           c->LineNumber());
                continue;
            }

            wchar_t const* id = c->Attribute(L"id");
            wchar_t const* name = c->Attribute(L"name");
            wchar_t const* type = c->Attribute(L"type");
            wchar_t const* enable = c->Attribute(L"enable");
            if (id == nullptr || *id == L'\0' || name == nullptr || *name == L'\0' || type == nullptr || *type == L'\0' ||
                enable == nullptr || *enable == L'\0')
            {
                Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 137,
                           L"[game-event-cfg], setup game event list exception, invalid attribute value, line:%d",
                           c->LineNumber());
                continue;
            }

            int eventId = _wtoi(id);
            GameEventInfo* info = FindGameEventInfo(eventId);
            if (info != nullptr)
            {
                wcscpy_s(info->name, 260, name);
                info->eventType = static_cast<char>(_wtoi(type));
                info->daemonType = static_cast<unsigned char>(daemonType);
                info->enable = _wcsicmp(L"true", enable) == 0;
            }
            else
            {
                info = static_cast<GameEventInfo*>(
                    Memory::_Manager[2]->AllocZero(sizeof(GameEventInfo), GAME_EVENT_CONFIG_FILE, 160));
                info->id = eventId;
                wcscpy_s(info->name, 260, name);
                info->eventType = static_cast<char>(_wtoi(type));
                info->daemonType = static_cast<unsigned char>(daemonType);
                info->enable = _wcsicmp(L"true", enable) == 0;
                addGameEventInfo(info);
            }
        }
    }
    return true;
}

// 0x3260
bool GameEventConfig::addGameEventInfo(GameEventInfo* gameEventInfo)
{
    Console* console = Daemon::Instance->console;

    if (gameEventInfo == nullptr)
    {
        wchar_t const* message = L"[game-event-cfg], register game-event-info fail; game-event-info is null";
        Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 268, message);
        writeStartLog(console, message);
        return false;
    }

    _lock.Enter();
    bool inserted = _gameEventList.insert(std::make_pair(gameEventInfo->id, gameEventInfo)).second;
    _lock.Leave();

    if (!inserted)
    {
        wchar_t const* format = L"[game-event-cfg], register game-event-info fail; already exists, event-id:%d, event-name:%s";
        Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 285, format, gameEventInfo->id, gameEventInfo->name);
        if (console != nullptr)
        {
            console->WriteStartLog(0, format, gameEventInfo->id, gameEventInfo->name);
            Sleep(5000);
        }
        return false;
    }
    return true;
}

// 0x3390
GameEventConfig::GameEventInfo* GameEventConfig::FindGameEventInfo(int id)
{
    GameEventInfo* result = nullptr;
    _lock.Enter();
    auto it = _gameEventList.find(id);
    if (it != _gameEventList.end())
        result = it->second;
    _lock.Leave();
    return result;
}

// 0x3430
bool GameEventConfig::Load(wchar_t const* configPath)
{
    Console* console = Daemon::Instance->console;
    wchar_t file[260] = {};

    if (_wmakepath_s(file, 260, nullptr, configPath, L"game-event.config.xml", nullptr) != 0)
    {
        wchar_t const* format = L"[scd], failed to make coupon game-event config file path, gameEventConfigFileName:.\\%s";
        Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 344, format, L"game-event.config.xml");
        if (console != nullptr)
        {
            console->WriteStartLog(0, format, L"game-event.config.xml");
            Sleep(5000);
        }
        return false;
    }

    if (SetupGameEventListFromXml(file))
        return true;

    wchar_t const* format = L"[scd], setup coupon game-event list fail, gameEventConfigFileName:%s";
    Log::Write(Log::LT_ERROR, GAME_EVENT_CONFIG_FILE, 350, format, file);
    if (console != nullptr)
    {
        console->WriteStartLog(0, format, file);
        Sleep(5000);
    }
    return false;
}

// 0x3580
void GameEventConfig::Dump()
{
    for (auto it = _gameEventList.begin(); it != _gameEventList.end(); ++it)
    {
        GameEventInfo* info = it->second;
        if (info == nullptr)
            continue;
        Log::Write(Log::LT_DEBUG, GAME_EVENT_CONFIG_FILE, 365,
                   L"[game-event-cfg], daemon:%s(%d), id:%d, name:%s, type:%d, enable:%s",
                   SmartCouponDaemonTypeDesc[info->daemonType], static_cast<int>(info->daemonType), info->id, info->name,
                   static_cast<int>(info->eventType), info->enable ? L"true" : L"false");
    }
}
