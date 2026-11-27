// petitiondaemonchannel.cpp: petitiondaemonchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "petitiondaemonchannel.h"
#include "LiftStub.h"

// 0x18c8a0
bool __cdecl PetitionSessionHandler::OnAccept(::Session const *) const
{
    LIFT_STUB(0x18c8a0);
}

// 0x18c8e0
bool __cdecl PetitionSessionHandler::OnConnect(::Session const *, bool) const
{
    LIFT_STUB(0x18c8e0);
}

// 0x18cae0
void __cdecl PetitionSessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0x18cae0);
}

// 0x18ccc0
bool __cdecl PetitionSessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x18ccc0);
}

// 0x18cf30
void __cdecl PetitiondChannel::Initialize(short)
{
    LIFT_STUB(0x18cf30);
}

// 0x18d070
bool __cdecl PetitionChannelManager::Initialize(short, short *const)
{
    LIFT_STUB(0x18d070);
}

// 0x18d320
void __cdecl PetitionChannelManager::Close(void)
{
    LIFT_STUB(0x18d320);
}

// 0x18d4b0
bool __cdecl PetitionChannelManager::IsConnected(short)
{
    LIFT_STUB(0x18d4b0);
}

// 0x18d570
bool __cdecl PetitionChannelManager::Send(short, char const *, ...)
{
    LIFT_STUB(0x18d570);
}

// 0x18d6f0
bool __cdecl PetitionChannelManager::Send(short, ::Packet const *)
{
    LIFT_STUB(0x18d6f0);
}

// 0x18d7e0
::PetitiondChannel * __cdecl PetitionChannelManager::acquire(unsigned int)
{
    LIFT_STUB(0x18d7e0);
}

// 0x18d8a0
bool __cdecl HandlePetition_ServerVersionNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18d8a0);
}

// 0x18dad0
bool __cdecl HandlePetition_ConnectWorldAck(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18dad0);
}

// 0x18db60
bool __cdecl HandlePetition_SubmitPetitionOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18db60);
}

// 0x18e0e0
bool __cdecl HandlePetition_SubmitPetitionFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18e0e0);
}

// 0x18e380
bool __cdecl HandlePetition_CancelPetitionOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18e380);
}

// 0x18e590
bool __cdecl HandlePetition_CancelPetitionFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18e590);
}

// 0x18e7c0
bool __cdecl HandlePetition_FeedbackAck(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18e7c0);
}

// 0x18ead0
bool __cdecl HandlePetition_Checkout_Notify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18ead0);
}

// 0x18ec90
bool __cdecl HandlePetition_Finish_Notify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18ec90);
}

// 0x18ed30
bool __cdecl HandlePetition_Finish2_Notify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18ed30);
}

// 0x18edd0
bool __cdecl HandlePetition_LeaveMessageReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18edd0);
}

// 0x18f340
bool __cdecl HandlePetition_CharacterInfoReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18f340);
}

// 0x18f440
bool __cdecl HandlePetition_ConnectedCharInfoReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18f440);
}

// 0x18f570
bool __cdecl HandlePetition_CurrentPetitionAck(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18f570);
}

// 0x18f7a0
bool __cdecl HandlePetition_ConnectedUnReadCharsInfoReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x18f7a0);
}
