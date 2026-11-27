// channel.cpp: channel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "channel_gd.h"
#include "../BloodLib/include/Channel.h"
#include "LiftStub.h"

// 0x69a3e0 DaemonChannel::Send: LIFT: no body in wave 0 (shared class DaemonChannel has another form or the change needs codegen (W1, pattern 35)).

// 0x69a440 DaemonChannel::Send: LIFT: no body in wave 0 (shared class DaemonChannel has another form or the change needs codegen (W1, pattern 35)).

// 0x69a4c0 DaemonChannel::Send: LIFT: no body in wave 0 (shared class DaemonChannel has another form or the change needs codegen (W1, pattern 35)).

// 0x69a740
void __cdecl ClientSideDaemonChannel::initialize(unsigned int, unsigned long, unsigned short)
{
    LIFT_STUB(0x69a740);
}

// 0x69a7e0
bool __cdecl ClientSideDaemonChannel::initSession(bool *, bool, bool)
{
    LIFT_STUB(0x69a7e0);
}

// 0x69aa70
__cdecl ClientSideHashedDaemonChannel::~ClientSideHashedDaemonChannel(void)
{
    LIFT_STUB(0x69aa70);
}

// 0x69abf0
bool __cdecl ClientSideHashedDaemonChannel::Send(unsigned __int64, char const *, ...)
{
    LIFT_STUB(0x69abf0);
}

// 0x69ac40
bool __cdecl ClientSideHashedDaemonChannel::Send(unsigned __int64, ::Packet const *)
{
    LIFT_STUB(0x69ac40);
}

// 0x69acc0
void __cdecl ClientSideHashedDaemonChannel::initialize(unsigned int, unsigned long, unsigned short)
{
    LIFT_STUB(0x69acc0);
}

// 0x69ad60
bool __cdecl ClientSideHashedDaemonChannel::initSession(bool *, bool, bool)
{
    LIFT_STUB(0x69ad60);
}

// 0x69af30
::Session * __cdecl ClientSideHashedDaemonChannel::getSession(unsigned __int64)
{
    LIFT_STUB(0x69af30);
}

// 0x69afb0
void __cdecl ClientSideHashedDaemonChannel::releaseSession(::Session *)
{
    LIFT_STUB(0x69afb0);
}

// 0x69b000
__cdecl ServerSideDaemonChannel::~ServerSideDaemonChannel(void)
{
    LIFT_STUB(0x69b000);
}

// 0x69b0a0
bool __cdecl ServerSideDaemonChannel::Initialize(int)
{
    LIFT_STUB(0x69b0a0);
}

// 0x69b170
void __cdecl ServerSideDaemonChannel::CloseAll(void)
{
    LIFT_STUB(0x69b170);
}

// 0x69b260
bool __cdecl ServerSideDaemonChannel::onAccept(::Session const *)
{
    LIFT_STUB(0x69b260);
}

// 0x69b340
void __cdecl ServerSideDaemonChannel::onClose(::Session const *, bool, bool)
{
    LIFT_STUB(0x69b340);
}

// 0x69b4c0
::Session * __cdecl ServerSideDaemonChannel::getSession(void)
{
    LIFT_STUB(0x69b4c0);
}

// 0x69b670
void __cdecl ServerSideDaemonChannel::releaseSession(::Session *)
{
    LIFT_STUB(0x69b670);
}
