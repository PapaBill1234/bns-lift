// gamedaemon_cpp.cpp: gamedaemon.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamedaemon.h"
#include "pc.h"
#include "LiftStub.h"

// 0x339ee0
unsigned __int64 __cdecl GenerateTid(void)
{
    LIFT_STUB(0x339ee0);
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
bool __cdecl ManageSessionHandler::OnAccept(::Session const *) const
{
    LIFT_STUB(0x33a210);
}

// 0x33a250
bool __cdecl ManageSessionHandler::OnConnect(::Session const *, bool) const
{
    LIFT_STUB(0x33a250);
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
bool __cdecl BuilderSessionHandler::OnAccept(::Session const *) const
{
    LIFT_STUB(0x33aaf0);
}

// 0x33ab30
bool __cdecl BuilderSessionHandler::OnConnect(::Session const *, bool) const
{
    LIFT_STUB(0x33ab30);
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
    LIFT_STUB(0x33afc0);
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
int __cdecl GameDaemon::GetRandomStoreServiceState(char)
{
    LIFT_STUB(0x340e70);
}

// 0x340ea0
short __cdecl GameDaemon::GetServerIdForDaemon(void)
{
    LIFT_STUB(0x340ea0);
}

// 0x340ee0
short __cdecl GameDaemon::GetServerIdForNPChat(char)
{
    LIFT_STUB(0x340ee0);
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
    LIFT_STUB(0x342ae0);
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
    LIFT_STUB(0x343030);
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
bool __cdecl GameDaemon::NotCheckToPlayInWeek(char)
{
    LIFT_STUB(0x343650);
}

// 0x3436c0
static int GenerateDump(_EXCEPTION_POINTERS*, bool)
{
    LIFT_STUB(0x3436c0);
}

// 0x3438f0
void __cdecl GameDaemon::WriteDump(bool)
{
    LIFT_STUB(0x3438f0);
}

// 0x343910
wchar_t const * __cdecl GameDaemon::GetAddressStringWForLogs(unsigned long)
{
    LIFT_STUB(0x343910);
}
