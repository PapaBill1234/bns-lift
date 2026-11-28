// gamedaemon_cpp.cpp: gamedaemon.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamedaemon.h"
#include "gamedconfig.h"
#include "pc.h"
#include "Network.h"
#include "StlMemory.h"
#include <vector>
#include <algorithm>
#include "LiftStub.h"
#include "Session.h"
#include "AlertSender.h"
#include "Log.h"
#include <intrin.h>

// LIFT: per-exe path literal (lessons A6).
#define GAMEDAEMON_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\GameDaemon.cpp"

#pragma comment(linker, "/INCLUDE:?EventId@GamedReloadInvalidRestoreTimer@@UEBAIXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetRandomStoreServiceState@GameDaemon@@SAHD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetServerIdForDaemon@GameDaemon@@SAFXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetServerIdForNPChat@GameDaemon@@SAFD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?EventId@GamedCooldownTimer@@UEBAIXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ServiceName@GameDaemon@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?NotCheckToPlayInWeek@GameDaemon@@QEAA_ND@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetAddressStringWForLogs@GameDaemon@@SAPEB_WK@Z")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: view of the GameDaemon members after the declared part of the layout (PDB offsets).
struct GameDaemonView
{
    char lift_pad_0[0x1628];
    ::SeasonContentsTypes * seasonContentsTypes;  // +5672 (0x1628)
    char lift_pad_1[0x152D2 - 0x1630];
    short _worldClusterId;                        // +86738 (0x152D2)
    char lift_pad_2[0x1533C - 0x152D4];
    unsigned int _worldId;                        // +86844 (0x1533C)
    char lift_pad_3[0x15350 - 0x15340];
    int * _randomStoreServiceStates;              // +86864 (0x15350)
};

// LIFT: view of GamedConfig after the declared part of the layout (PDB offset).
struct GamedConfigView
{
    char lift_pad_0[0x65C];
    bool _allowClientIPAddressInLogs;  // +1628 (0x65C)
};

// LIFT: view of SeasonContentsTypes (PDB: _typeList at +0, size 0x20). The skeleton class has no members yet.
struct SeasonContentsTypesView
{
    std::vector<char, StlAllocator<char, 2> > _typeList;  // +0
};

inline GameDaemonView * AsView(::GameDaemon * daemon)
{
    return reinterpret_cast<GameDaemonView *>(daemon);
}
}

// 0x339ee0
#pragma comment(linker, "/INCLUDE:?GenerateTid@@YA_KXZ")  // LIFT: dead-strip keep (no live caller yet)
unsigned __int64 __cdecl GenerateTid(void)
{
    // LIFT: the PDB has no symbol for the counter (pseudocode name _seed__, data 0x101e138). Static counter as in LobbyDaemon.
    static unsigned __int64 __seed__ = 0;
    long long const result = _InterlockedIncrement64(reinterpret_cast<volatile __int64 *>(&__seed__));
    if (result == 0)
    {
        // The counter wrapped to 0. Take the next value and log it.
        long long const v = _InterlockedExchangeAdd64(reinterpret_cast<volatile __int64 *>(&__seed__), 1);
        Log::Write(Log::LT_ERROR, GAMEDAEMON_FILE, 122, L"[game-tran], tid overflow");
        return static_cast<unsigned __int64>(v + 1);
    }
    return static_cast<unsigned __int64>(result);
}

// 0x339f30
bool __cdecl SeasonContentsTypes::Add(wchar_t const *)
{
    LIFT_STUB(0x339f30);
}

// 0x33a190
int wmain(int, wchar_t**)
{
    LIFT_STUB(0x33a190);
}

// 0x33a210
#pragma comment(linker, "/INCLUDE:?OnAccept@ManageSessionHandler@@UEBA_NPEBVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl ManageSessionHandler::OnAccept(::Session const * session) const
{
    Log::Write(Log::LT_DEBUG, GAMEDAEMON_FILE, 255, L"Manage Session(%I64X), Accepted", session->_id);
    return true;
}

// 0x33a250
#pragma comment(linker, "/INCLUDE:?OnConnect@ManageSessionHandler@@UEBA_NPEBVSession@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl ManageSessionHandler::OnConnect(::Session const *, bool) const
{
    Log::Write(Log::LT_ERROR, GAMEDAEMON_FILE, 261, L"== CRASH == [manage session handler], OnConnect; called ... wrong");
    AlertSender::Write(GAMEDAEMON_FILE, 261, L"== CRASH == [manage session handler], OnConnect; called ... wrong");
    return false;
}

// 0x33a290
void __cdecl ManageSessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0x33a290);
}

// 0x33a2d0
bool __cdecl ManageSessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x33a2d0);
}

// 0x33a6c0
bool __cdecl ManageSessionHandler::QaCommandPacketHandler(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x33a6c0);
}

// 0x33a9c0
::Pointer2< ::Pc> __cdecl BuilderSessionHandler::GetPcPtr(::Session const *)
{
    LIFT_STUB(0x33a9c0);
}

// 0x33aaf0
#pragma comment(linker, "/INCLUDE:?OnAccept@BuilderSessionHandler@@UEBA_NPEBVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl BuilderSessionHandler::OnAccept(::Session const * session) const
{
    Log::Write(Log::LT_DEBUG, GAMEDAEMON_FILE, 486, L"Builder Session(%I64X), Accepted", session->_id);
    return true;
}

// 0x33ab30
#pragma comment(linker, "/INCLUDE:?OnConnect@BuilderSessionHandler@@UEBA_NPEBVSession@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl BuilderSessionHandler::OnConnect(::Session const *, bool) const
{
    Log::Write(Log::LT_ERROR, GAMEDAEMON_FILE, 492, L"== CRASH == [builder session handler], OnConnect; called ... wrong");
    AlertSender::Write(GAMEDAEMON_FILE, 492, L"== CRASH == [builder session handler], OnConnect; called ... wrong");
    return false;
}

// 0x33ab70
void __cdecl BuilderSessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0x33ab70);
}

// 0x33ac20
bool __cdecl BuilderSessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x33ac20);
}

// 0x33aed0
__cdecl NPMessageHandleEvent::~NPMessageHandleEvent(void)
{
    LIFT_STUB(0x33aed0);
}

// 0x33af60
bool __cdecl NPMessageHandleEvent::HandleEvent(::EventContext *, unsigned long)
{
    LIFT_STUB(0x33af60);
}

// 0x33afc0
unsigned int __cdecl GamedReloadInvalidRestoreTimer::EventId(void) const
{
    return 130;
}

// 0x33afd0
bool __cdecl GamedReloadInvalidRestoreTimer::HandleEvent(::EventContext *, unsigned long)
{
    LIFT_STUB(0x33afd0);
}

// 0x33afe0
void __cdecl GamedReloadInvalidRestoreTimer::restoreInvalid(void)
{
    LIFT_STUB(0x33afe0);
}

// 0x33b040
bool __cdecl TimeBasedPlaySeasonSchedule::Decompose(::RepeatPacketDecomposer &, ::Packet const *)
{
    LIFT_STUB(0x33b040);
}

// 0x33b2d0
__cdecl GameDaemon::GameDaemon(void)
{
    LIFT_STUB(0x33b2d0);
}

// 0x33b9a0
__cdecl GameDaemon::~GameDaemon(void)
{
    LIFT_STUB(0x33b9a0);
}

// 0x33c520
bool __cdecl GameDaemon::initLog(void)
{
    LIFT_STUB(0x33c520);
}

// 0x33cc40
void __cdecl GameDaemon::FlushExtraLog(void)
{
    LIFT_STUB(0x33cc40);
}

// 0x33cc60
bool __cdecl GameDaemon::initialize(void)
{
    LIFT_STUB(0x33cc60);
}

// 0x33e960
bool __cdecl GameDaemon::loadBannedWorldFilter(::XmlReaderIO *)
{
    LIFT_STUB(0x33e960);
}

// 0x33eee0
bool __cdecl GameDaemon::initNetwork(void)
{
    LIFT_STUB(0x33eee0);
}

// 0x340970
int __cdecl GameDaemon::GetDuelRatingBeginnerConst(int)
{
    LIFT_STUB(0x340970);
}

// 0x340a00
void __cdecl GameDaemon::SetDuelRatingBeginnerConst(void)
{
    LIFT_STUB(0x340a00);
}

// 0x340af0
void __cdecl GameDaemon::SetWorldIds(short, short *const)
{
    LIFT_STUB(0x340af0);
}

// 0x340c70
bool __cdecl GameDaemon::ValidWorldId(short)
{
    LIFT_STUB(0x340c70);
}

// 0x340cc0
bool __cdecl GameDaemon::SetPublisher(wchar_t const *)
{
    LIFT_STUB(0x340cc0);
}

// 0x340d50
bool __cdecl GameDaemon::SetTimeZoneBias(void)
{
    LIFT_STUB(0x340d50);
}

// 0x340e70
int __cdecl GameDaemon::GetRandomStoreServiceState(char randomStoreNumber)
{
    int * randomStoreServiceStates = AsView(GamedInstance)->_randomStoreServiceStates;
    if (randomStoreServiceStates == nullptr || randomStoreNumber < 1 || randomStoreNumber > 2)
        return 0;
    return randomStoreServiceStates[randomStoreNumber - 1];
}

// 0x340ea0
short __cdecl GameDaemon::GetServerIdForDaemon(void)
{
    if (GamedInstance->config->_arenaEnabled && GamedInstance->config->_arenaId != 0)
        return static_cast<short>(GamedInstance->config->_arenaId + 10000);
    return AsView(GamedInstance)->_worldClusterId;
}

// 0x340ee0
short __cdecl GameDaemon::GetServerIdForNPChat(char gameServerType)
{
    (void)gameServerType;
    if (GamedInstance->config->_arenaEnabled && GamedInstance->config->_arenaId != 0)
        return static_cast<short>(GamedInstance->config->_arenaId + 10000);
    return static_cast<short>(AsView(GamedInstance)->_worldId);
}

// 0x340f20
short __cdecl GameDaemon::GetServerIdForChat(char)
{
    LIFT_STUB(0x340f20);
}

// 0x340fc0
bool __cdecl GameDaemon::onStart(void)
{
    LIFT_STUB(0x340fc0);
}

// 0x341230
void __cdecl GameDaemon::shutdown(void)
{
    LIFT_STUB(0x341230);
}

// 0x341890
bool __cdecl GameDaemon::startGameDaemon(void)
{
    LIFT_STUB(0x341890);
}

// 0x3419f0
bool __cdecl GameDaemon::startNPChannel(void)
{
    LIFT_STUB(0x3419f0);
}

// 0x341cf0
bool __cdecl GameDaemon::initializePublisherLibs(void)
{
    LIFT_STUB(0x341cf0);
}

// 0x342110
bool __cdecl GameDaemon::reload(wchar_t **, int)
{
    LIFT_STUB(0x342110);
}

// 0x342ae0
unsigned int __cdecl GamedCooldownTimer::EventId(void) const
{
    return 129;
}

// 0x342af0
bool __cdecl GamedCooldownTimer::HandleEvent(::EventContext *, unsigned long)
{
    LIFT_STUB(0x342af0);
}

// 0x342c20
int __cdecl GamedCooldownTimer::disconnectAll(void)
{
    LIFT_STUB(0x342c20);
}

// 0x342d80
bool __cdecl GameDaemon::cooldown(void)
{
    LIFT_STUB(0x342d80);
}

// 0x342f80
void __cdecl GameDaemon::FailedEventObjectHandler(::EventObject *)
{
    LIFT_STUB(0x342f80);
}

// 0x343030
wchar_t const * __cdecl GameDaemon::ServiceName(void)
{
    return L"BnS gamed";
}

// 0x343040
wchar_t const * __cdecl GameDaemon::Descriptions(void)
{
    LIFT_STUB(0x343040);
}

// 0x343140
void __cdecl GameDaemon::PrintDependency(void)
{
    LIFT_STUB(0x343140);
}

// 0x343650
bool __cdecl GameDaemon::NotCheckToPlayInWeek(char seasonContentsType)
{
    SeasonContentsTypesView * seasonContentsTypes =
        reinterpret_cast<SeasonContentsTypesView *>(AsView(this)->seasonContentsTypes);
    if (seasonContentsTypes == nullptr || seasonContentsType <= 0 || seasonContentsType >= 16)
        return false;
    // LIFT: SeasonContentsTypes::IsExist (inlined, PDB name) is a binary search of the sorted type list.
    // include/vs2010/algorithm has no binary_search, so the VS2010 _Lower_bound loop is written here.
    typedef std::vector<char, StlAllocator<char, 2> > TypeList;
    TypeList const& typeList = seasonContentsTypes->_typeList;
    TypeList::const_iterator first = typeList.begin();
    TypeList::const_iterator const last = typeList.end();
    long long count = last - first;
    while (count > 0)
    {
        long long const half = count / 2;
        if (first[half] < seasonContentsType)
        {
            first += half + 1;
            count -= half + 1;
        }
        else
        {
            count = half;
        }
    }
    return first != last && !(seasonContentsType < *first);
}

// 0x3436c0
static int GenerateDump(_EXCEPTION_POINTERS*, bool)
{
    LIFT_STUB(0x3436c0);
}

// 0x3438f0
#pragma comment(linker, "/INCLUDE:?WriteDump@GameDaemon@@SAX_N@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl GameDaemon::WriteDump(bool /*fullMemory*/)
{
    // The original raises an access violation and writes the dump in the filter (filt$0, 0x702a30, line 4357).
    // LIFT: the original filter does not load fullMemory (GenerateDump does not use it). The body does not
    // read the argument, so the build does not spill it. RaiseException gets all 4 arguments (r8 = r9 = 0).
    // ❓ the source maybe passed fullMemory; the 2019 build gives no load of it.
    __try
    {
        RaiseException(0xC0000005, 1, 0, NULL);
    }
    __except (GenerateDump(GetExceptionInformation(), false))
    {
    }
}

// 0x343910
wchar_t const * __cdecl GameDaemon::GetAddressStringWForLogs(unsigned long addr)
{
    if (GamedInstance != nullptr && GamedInstance->config != nullptr &&
        !reinterpret_cast<GamedConfigView *>(GamedInstance->config)->_allowClientIPAddressInLogs)
        addr = 0;
    return Network::GetAddressStringW(addr);
}
