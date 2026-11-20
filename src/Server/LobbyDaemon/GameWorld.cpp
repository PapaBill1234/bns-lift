// GameWorld.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GameWorld.h"
#include "LiftStub.h"

// 0x4c810
short GameWorld::GetWid() const
{
    LIFT_STUB(0x4c810);
}

// 0x4c820
GameWorld::GameWorld()
{
    LIFT_STUB(0x4c820);
}

// 0x4cc40
bool GameWorld::FetchWorldInfo(FragmentPacket*) const
{
    LIFT_STUB(0x4cc40);
}

// 0x4ce60
bool GameWorld::FetchWorldInfoForInfoGate(FragmentPacket*) const
{
    LIFT_STUB(0x4ce60);
}

// 0x4cf40
bool GameWorld::EnterUser(CliSession*, bool&, WaitInfo&)
{
    LIFT_STUB(0x4cf40);
}

// 0x4d120
bool GameWorld::PermitCharacterManagement(CliSession*, bool)
{
    LIFT_STUB(0x4d120);
}

// 0x4d390
GameWorldCluster::GameWorldCluster()
{
    LIFT_STUB(0x4d390);
}

// 0x4d440
GameWorldCluster::~GameWorldCluster()
{
    LIFT_STUB(0x4d440);
}

// 0x4dc70
long long GameWorldCluster::UpdateCounters()
{
    LIFT_STUB(0x4dc70);
}

// 0x4dd90
bool GameWorldCluster::enterUser(GameWorld*, CliSession*, bool&, WaitInfo&)
{
    LIFT_STUB(0x4dd90);
}

// 0x4e080
bool GameWorldCluster::leaveUser(GameWorld*, CliSession*)
{
    LIFT_STUB(0x4e080);
}

// 0x4e4f0
bool GameWorldCluster::addGameWorld(GameWorld*)
{
    LIFT_STUB(0x4e4f0);
}

// 0x4e630
GameWorldRegistry::GameWorldRegistry()
{
    LIFT_STUB(0x4e630);
}

// 0x4e6c0
GameWorldRegistry::~GameWorldRegistry()
{
    LIFT_STUB(0x4e6c0);
}

// 0x4e8b0
GameWorld* GameWorldRegistry::Get(short)
{
    LIFT_STUB(0x4e8b0);
}

// 0x4e9b0
bool GameWorldRegistry::FetchWorldInfoList(FragmentPacket*)
{
    LIFT_STUB(0x4e9b0);
}

// 0x4ead0
bool GameWorldRegistry::FetchWorldInfoListForInfoGate(FragmentPacket*)
{
    LIFT_STUB(0x4ead0);
}

// 0x4ebf0
GameWorldCluster* GameWorldRegistry::getGameWorldCluster(short)
{
    LIFT_STUB(0x4ebf0);
}

// 0x4ec90
bool GameWorldRegistry::addGameWorldCluster(GameWorldCluster*)
{
    LIFT_STUB(0x4ec90);
}

// 0x4ed00
bool GameWorldRegistry::Setup(short, short)
{
    LIFT_STUB(0x4ed00);
}

// 0x4f330
void GameWorldRegistry::Update()
{
    LIFT_STUB(0x4f330);
}

// 0x4f940
GameWorldReporter::~GameWorldReporter()
{
    LIFT_STUB(0x4f940);
}

// 0x4f9b0
bool GameWorldReporter::Initialize(void (__cdecl*)(GameWorldReporter*), GameWorldRegistry*, long)
{
    LIFT_STUB(0x4f9b0);
}

// 0x4fa30
bool GameWorldReporter::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0x4fa30);
}

// 0x4fa80
bool GameWorldReporter::WriteReport()
{
    LIFT_STUB(0x4fa80);
}

// 0x4fc00
GameWorldReport::~GameWorldReport()
{
    LIFT_STUB(0x4fc00);
}

// 0x4fc70
bool GameWorldReport::Write(GameWorldRegistry*)
{
    LIFT_STUB(0x4fc70);
}

// 0x4fdc0
Packet const* GameWorldReport::GetPacket() const
{
    LIFT_STUB(0x4fdc0);
}
