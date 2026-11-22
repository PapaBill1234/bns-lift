// BLDaemonInfo.obj (LobbyDaemon PDB, 2019 + PDB). Source file name from log strings: "BLDaemonInfo.cpp".
// LIFT: this object has the upper case build path of StlMemory.h (from the HR strings, 0x403c0).
#define LIFT_STLMEMORY_FILE \
    L"E:\\DailyBuild02\\LobbyDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\StlMemory.h"
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "BLDaemonInfo.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "XmlReader.h"

namespace
{
wchar_t const* const BLDAEMONINFO_FILE = L"BLDaemonInfo.cpp";  // LIFT: No PDB symbol. The binary uses the literal.

// LIFT: inlined five times in BLDaemonInfoTable::load 0x40510 (one copy for each element kind).
// The copies differ only in the kind and the source lines. The original writes ind.<kind>.internal_port.
// All union members have offset 0, so this helper writes ind.gamed.internal_port.
// It returns nullptr when an attribute is missing or empty. It frees the entry in that case.
inline BLDaemonInfo* ReadDaemonElement(XmlElement const* elem, int kind, int allocLine, int logLine, int freeLine)
{
    BLDaemonInfo* info =
        static_cast<BLDaemonInfo*>(Memory::_Manager[2]->AllocZero(sizeof(BLDaemonInfo), BLDAEMONINFO_FILE, allocLine));
    // BUG: 0x40510 does not check the AllocZero result before it writes id.kind.
    info->id.kind = kind;
    wchar_t const* wid = elem->Attribute(L"wid");
    wchar_t const* ipAddress = elem->Attribute(L"ip-address");
    wchar_t const* internalPort = elem->Attribute(L"internal-port");
    if (wid == nullptr || wcslen(wid) == 0 || ipAddress == nullptr || wcslen(ipAddress) == 0 ||
        internalPort == nullptr || wcslen(internalPort) == 0)
    {
        Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, logLine,
                   L"[daemon-list], load exception;invalid attribute value, line:%d", elem->LineNumber());
        Memory::_Manager[2]->Free(info, BLDAEMONINFO_FILE, freeLine);
        return nullptr;
    }
    info->internal_ipv4 = Network::GetAddress(ipAddress);
    info->id.wid = static_cast<short>(_wtoi(wid));
    info->ind.gamed.internal_port = static_cast<unsigned short>(_wtoi(internalPort));
    return info;
}
}  // namespace

// 0x403c0
#pragma comment(linker, "/INCLUDE:??0BLDaemonInfoTable@@QEAA@XZ")  // LIFT: keep until the caller is lifted (0x403c0)
BLDaemonInfoTable::BLDaemonInfoTable()
{
}

// 0x40490
#pragma comment(linker, "/INCLUDE:??1BLDaemonInfoTable@@QEAA@XZ")  // LIFT: keep until the caller is lifted (0x40490)
BLDaemonInfoTable::~BLDaemonInfoTable()
{
    Clear();
}

// 0x40510
// LIFT: the original does not use this. The 2019 build passes xml in rcx (LTCG drops this).
bool BLDaemonInfoTable::load(wchar_t const* xml, BLDaemonInfo**& out, int& outCount)
{
    if (xml == nullptr || wcslen(xml) == 0)
    {
        Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 29, L"[daemon-list], load fail;invalid parameter, xml:%p", xml);
        return false;
    }

    int count = 0;
    out = nullptr;
    outCount = 0;
    bool result = false;
    XmlDoc* doc = nullptr;

    HMODULE library = LoadLibraryW(L"XmlReader_sv64.dll");
    if (library == nullptr)
    {
        Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 47, L"[daemon-list], load fail;module missing, xml:%s",
                   L"XmlReader_sv64.dll");
        return false;
    }

    XriGetInterfaceVersion getInterfaceVersion =
        reinterpret_cast<XriGetInterfaceVersion>(GetProcAddress(library, "GetInterfaceVersion"));
    GetProcAddress(library, "SetMemAllocator");
    XriCreateFunc createXmlReader = reinterpret_cast<XriCreateFunc>(GetProcAddress(library, "CreateXmlReader"));
    XriDestoryFunc destroyXmlReader = reinterpret_cast<XriDestoryFunc>(GetProcAddress(library, "DestroyXmlReader"));

    XmlReader const* reader = createXmlReader();
    if (reader == nullptr)
    {
        Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 54, L"[daemon-list], load fail;create xmlreader fail");
        goto cleanup;
    }

    {
        wchar_t const* version = getInterfaceVersion();
        if (_wcsicmp(version, L"15") != 0)
        {
            Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 61,
                       L"[daemon-list], load fail;xmlreader version mismatch, current-version:%s, load-version:%s",
                       L"15", version);
            goto cleanup;
        }
    }

    if (!reader->Initialize(nullptr, nullptr, false))
    {
        Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 67, L"[daemon-list], load fail;init xmlreader fail");
        goto cleanup;
    }

    doc = reader->Read(xml, static_cast<XmlPieceReader*>(nullptr));
    if (doc == nullptr)
    {
        Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 74, L"[daemon-list], load fail;read xml fail, xml:'%s'", xml);
        goto cleanup;
    }

    {
        XmlElement const* root = doc->Root();
        if (root != nullptr && root->ChildElementCount() > 0)
        {
            outCount = root->ChildElementCount();
            out = static_cast<BLDaemonInfo**>(Memory::_Manager[2]->AllocZero(
                sizeof(BLDaemonInfo*) * root->ChildElementCount(), BLDAEMONINFO_FILE, 82));
            // BUG: 0x40510 does not check this AllocZero result before it writes out[count].

            for (XmlElement const* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextElement())
            {
                if (!elem->ToXmlNode()->IsValid())
                    break;

                wchar_t const* name = elem->Name();
                BLDaemonInfo* info = nullptr;
                if (_wcsicmp(name, L"cached") == 0)
                    info = ReadDaemonElement(elem, BLDAEMONKIND_CACHED, 94, 103, 104);
                else if (_wcsicmp(name, L"gamed") == 0)
                    info = ReadDaemonElement(elem, BLDAEMONKIND_GAMED, 115, 124, 125);
                else if (_wcsicmp(name, L"lobby-gate") == 0)
                    info = ReadDaemonElement(elem, BLDAEMONKIND_LOBBY_GATE, 136, 145, 146);
                else if (_wcsicmp(name, L"infogate") == 0)
                    info = ReadDaemonElement(elem, BLDAEMONKIND_INFO_GATE, 157, 166, 167);
                else if (_wcsicmp(name, L"mobile-gate") == 0)
                    info = ReadDaemonElement(elem, BLDAEMONKIND_MOBILE_GATE, 179, 188, 189);
                else
                {
                    Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 201,
                               L"[daemon-list], load exception;unknown element '%s', line:%d", elem->Name(),
                               elem->LineNumber());
                }

                if (info != nullptr)
                    out[count++] = info;
            }

            if (count < outCount)
            {
                Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 209, L"[daemon-list], shrink output...");
                BLDaemonInfo** shrunk = static_cast<BLDaemonInfo**>(
                    Memory::_Manager[2]->Realloc(out, sizeof(BLDaemonInfo*) * count, BLDAEMONINFO_FILE, 210));
                // BUG: 0x40510 does not check the Realloc result. A failed Realloc loses the old block.
                outCount = count;
                out = shrunk;
            }
        }
    }

    Log::Write(Log::LT_NOTICE, BLDAEMONINFO_FILE, 215, L"[daemon-list], load xml ok, count:%d, xml:%s", outCount, xml);
    result = true;

cleanup:
    if (reader != nullptr)
    {
        if (doc != nullptr)
            reader->Close(doc);
        destroyXmlReader(reader);
    }
    FreeLibrary(library);
    return result;
}

// 0x40e30
bool BLDaemonInfoTable::add(BLDaemonInfo* daemon)
{
    if (daemon == nullptr)
    {
        Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 236, L"[daemon-list], add fail; invalid parameter");
        return false;
    }

    _lock.Enter();
    // LIFT: insert a std::pair<BLDaemonID, BLDaemonInfo*>, not value_type: the PDB has _Buynode<std::pair<BLDaemonID,BLDaemonInfo *> > (A15).
    bool inserted = _daemons.insert(std::pair<BLDaemonID, BLDaemonInfo*>(daemon->id, daemon)).second;
    _lock.Leave();

    if (inserted)
        Log::Write(Log::LT_DEBUG, BLDAEMONINFO_FILE, 249, L"[daemon-list], add ok, kind:%d, wid:%d", daemon->id.kind,
                   static_cast<int>(daemon->id.wid));
    else
        Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 251, L"[daemon-list], add fail, kind:%d, wid:%d", daemon->id.kind,
                   static_cast<int>(daemon->id.wid));
    return inserted;
}

// 0x40f30
#pragma comment(linker, "/INCLUDE:?Load@BLDaemonInfoTable@@QEAA_NPEB_W@Z")  // LIFT: keep until the caller is lifted (0x40f30)
bool BLDaemonInfoTable::Load(wchar_t const* xml)
{
    BLDaemonInfo** loaded = nullptr;
    int loadedCount = 0;
    if (!load(xml, loaded, loadedCount))
    {
        Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 262, L"[daemon-list], load fail; load xml fail");
        return false;
    }

    for (BLDaemonInfo** it = loaded; it != loaded + loadedCount; ++it)
    {
        BLDaemonInfo* info = *it;
        if (info != nullptr && !add(info))
        {
            Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 270,
                       L"[daemon-list], load exception; add daemon-info fail; daemon info duplicated, kind:%d, wid:%d",
                       info->id.kind, static_cast<int>(info->id.wid));
            Memory::_Manager[2]->Free(info, BLDAEMONINFO_FILE, 271);
        }
    }

    if (loaded != nullptr)
        Memory::_Manager[2]->Free(loaded, BLDAEMONINFO_FILE, 277);

    Log::Write(Log::LT_NOTICE, BLDAEMONINFO_FILE, 279, L"[daemon-list], load ok, final-count:%d, xml:%s",
               _daemons.size(), xml);
    return true;
}

// 0x41090
#pragma comment(linker, "/INCLUDE:?Update@BLDaemonInfoTable@@QEAAXPEB_W@Z")  // LIFT: keep until the caller is lifted (0x41090)
void BLDaemonInfoTable::Update(wchar_t const* xml)
{
    BLDaemonInfo** loaded = nullptr;
    int loadedCount = 0;
    if (!load(xml, loaded, loadedCount))
    {
        Log::Write(Log::LT_ERROR, BLDAEMONINFO_FILE, 289, L"[daemon-list], update fail; load xml fail");
        return;
    }

    for (BLDaemonInfo** it = loaded; it != loaded + loadedCount; ++it)
    {
        BLDaemonInfo* info = *it;
        if (info == nullptr)
            continue;

        // LIFT: the original writes through the const pointer that Find returns.
        BLDaemonInfo* found = const_cast<BLDaemonInfo*>(Find(info->id));
        if (found != nullptr)
        {
            // BUG: 0x41090 info is not freed when the entry exists (changed or not). The original leaks it.
            if (memcmp(found, info, sizeof(BLDaemonInfo)) != 0)
            {
                *found = *info;
                Log::Write(Log::LT_NOTICE, BLDAEMONINFO_FILE, 301, L"[daemon-list], update, kind:%d, wid:%d",
                           found->id.kind, static_cast<int>(found->id.wid));
            }
        }
        else if (add(info))
        {
            Log::Write(Log::LT_NOTICE, BLDAEMONINFO_FILE, 307, L"[daemon-list], add, kind:%d, wid:%d", info->id.kind,
                       static_cast<int>(info->id.wid));
        }
        // BUG: 0x41090 info is not freed when add fails. The original leaks it.
    }

    Memory::_Manager[2]->Free(loaded, BLDAEMONINFO_FILE, 312);
}

// 0x41210
#pragma comment(linker, "/INCLUDE:?Find@BLDaemonInfoTable@@QEBAPEBUBLDaemonInfo@@AEBUBLDaemonID@@@Z")  // LIFT: keep until the caller is lifted (0x41210)
BLDaemonInfo const* BLDaemonInfoTable::Find(BLDaemonID const& id) const
{
    BLDaemonInfo const* found = nullptr;
    // LIFT: Find is const in the PDB. The original locks _lock.CS directly.
    CriticalSection& lock = const_cast<CriticalSection&>(_lock);
    lock.Enter();
    BLDaemonInfoMap::const_iterator it = _daemons.find(id);
    if (it != _daemons.end())
        found = it->second;
    lock.Leave();
    return found;
}

// 0x412d0
#pragma comment(linker, "/INCLUDE:?Clear@BLDaemonInfoTable@@QEAAXXZ")  // LIFT: keep until the caller is lifted (0x412d0)
void BLDaemonInfoTable::Clear()
{
    for (BLDaemonInfoMap::iterator it = _daemons.begin(); it != _daemons.end(); ++it)
    {
        if (it->second != nullptr)
            Memory::_Manager[2]->Free(it->second, BLDAEMONINFO_FILE, 362);
    }
    _daemons.clear();
}

// 0x416f0 std::_Tree<...BLDaemonID...>::_Linsert
// LIFT: template instance of the VS2010 <xtree>. BLDaemonInfoTable::add 0x40e30 makes it with _daemons.insert.
