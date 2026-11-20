// LobbyDaemon.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyDaemon.h"
#include "Channel.h"
#include "LiftStub.h"

// 0x99220
wchar_t const* LobbyDaemon::ShortName()
{
    LIFT_STUB(0x99220);
}

// 0x99230
wchar_t const* LobbyDaemon::Name()
{
    LIFT_STUB(0x99230);
}

// 0x99240
wchar_t const* LobbyDaemon::ServiceName()
{
    LIFT_STUB(0x99240);
}

// 0x99250
wchar_t const* LobbyDaemon::Descriptions()
{
    LIFT_STUB(0x99250);
}

// 0x99260
void* LobbyObjPoolMemAllocator::Alloc(unsigned long long, wchar_t const*, int)
{
    LIFT_STUB(0x99260);
}

// 0x99380
void* BannedWordFilterMemoryAllocator::Alloc(unsigned long long, wchar_t const*, int)
{
    LIFT_STUB(0x99380);
}

// 0x99390
void* BannedWordFilterMemoryAllocator::Realloc(void*, unsigned long long, wchar_t const*, int)
{
    LIFT_STUB(0x99390);
}

// 0x993b0
void BannedWordFilterMemoryAllocator::Free(void*, wchar_t const*, int)
{
    LIFT_STUB(0x993b0);
}

// 0x993c0
unsigned long long GenerateClikey()
{
    LIFT_STUB(0x993c0);
}

// 0x99410
unsigned long long GenerateJobid()
{
    LIFT_STUB(0x99410);
}

// 0x99460
unsigned long long GenerateLobbyTokenkey()
{
    LIFT_STUB(0x99460);
}

// 0x994b0
void GameWorldReporterListener(GameWorldReporter*)
{
    LIFT_STUB(0x994b0);
}

// 0x995c0
bool CoolDown::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0x995c0);
}

// 0x99880
bool CoolDown::Start(long, long)
{
    LIFT_STUB(0x99880);
}

// 0x99990
unsigned int LobbydReloadInvalidRestoreTimer::EventId() const
{
    LIFT_STUB(0x99990);
}

// 0x999a0
bool LobbydReloadInvalidRestoreTimer::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0x999a0);
}

// 0x999b0
void LobbydReloadInvalidRestoreTimer::restoreInvalid()
{
    LIFT_STUB(0x999b0);
}

// 0x99df0
TimeBasedPlaySeasonSchedule::TimeBasedPlaySeasonSchedule()
{
    LIFT_STUB(0x99df0);
}

// 0x99ef0
bool TimeBasedPlaySeasonSchedule::Compose(RepeatPacketComposer&, Packet&) const
{
    LIFT_STUB(0x99ef0);
}

// 0x9a230
LobbyDaemon::LobbyDaemon()
{
    LIFT_STUB(0x9a230);
}

// 0x9a3c0
LobbyDaemon::~LobbyDaemon()
{
    LIFT_STUB(0x9a3c0);
}

// 0x9ae30
void LobbyDaemon::PrintDependency()
{
    LIFT_STUB(0x9ae30);
}

// 0x9af60
long LobbyDaemon::GetTimerInterval()
{
    LIFT_STUB(0x9af60);
}

// 0x9af70
long LobbyDaemon::GetTimerMaxTime()
{
    LIFT_STUB(0x9af70);
}

// 0x9af80
bool LobbyDaemon::SetTimeZoneBias()
{
    LIFT_STUB(0x9af80);
}

// 0x9b0c0
void LobbyDaemon::FailedEventObjectHandler(EventObject*)
{
    LIFT_STUB(0x9b0c0);
}

// 0x9b1b0
bool LobbyDaemon::initLog()
{
    LIFT_STUB(0x9b1b0);
}

// 0x9b300
bool LobbyDaemon::initialize()
{
    LIFT_STUB(0x9b300);
}

// 0x9d520
bool LobbyDaemon::initNetwork()
{
    LIFT_STUB(0x9d520);
}

// 0x9dca0
bool LobbyDaemon::onStart()
{
    LIFT_STUB(0x9dca0);
}

// 0x9e2f0
void LobbyDaemon::shutdown()
{
    LIFT_STUB(0x9e2f0);
}

// 0x9e5b0
bool LobbyDaemon::reload(wchar_t**, int)
{
    LIFT_STUB(0x9e5b0);
}

// 0x9ef40
bool LobbyDaemon::cooldown()
{
    LIFT_STUB(0x9ef40);
}

// 0x9f010
bool LobbyDaemon::startNPChannel()
{
    LIFT_STUB(0x9f010);
}

// 0x9f130
bool LobbyDaemon::setupNpScheduleInfo()
{
    LIFT_STUB(0x9f130);
}

// 0x9f3c0
wchar_t const* LobbyDaemon::GetAddressStringWForLogs(unsigned long)
{
    LIFT_STUB(0x9f3c0);
}

// 0x9f3f0
bool ConcatenatePacket(Session const*, Packet const*, bool&)
{
    LIFT_STUB(0x9f3f0);
}

// 0x9a1b0. C linkage, the signature is not in the public. wmain_bridge.c calls it.
extern "C" int __cdecl wmain(int, wchar_t**)
{
    LIFT_STUB(0x9a1b0);
}

// LIFT: LobbyDaemon.exe (2019 + PDB) has no ClientSideDaemonChannel symbol, so this function has no LD RVA.
// BloodLib Channel.cpp in lift_common emits the ClientSideDaemonChannel vftable, so the link needs a body.
// LobbyDaemon.cpp is the LD-only owner. The argument 0 means "no LD RVA". The stub does not return success.
bool ClientSideDaemonChannel::onAccept(Session const*)
{
    LIFT_STUB(0);
}
