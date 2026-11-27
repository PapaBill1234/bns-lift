// petitiondaemonchannel.h: petitiondaemonchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class PetitionChannelManager
{
public:
    bool __cdecl Initialize(short, short *const);  // 0x18d070
    void __cdecl Close(void);  // 0x18d320
    bool __cdecl IsConnected(short);  // 0x18d4b0
    bool __cdecl Send(short, char const *, ...);  // 0x18d570
    bool __cdecl Send(short, ::Packet const *);  // 0x18d6f0
private:
    ::PetitiondChannel * __cdecl acquire(unsigned int);  // 0x18d7e0
};

class PetitionSessionHandler
{
public:
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0x18c8a0
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0x18c8e0
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0x18cae0
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x18ccc0
};

class PetitiondChannel
{
public:
    void __cdecl Initialize(short);  // 0x18cf30
};

bool __cdecl HandlePetition_ServerVersionNotify(::Session const *, ::Packet const *);  // 0x18d8a0
bool __cdecl HandlePetition_ConnectWorldAck(::Session const *, ::Packet const *);  // 0x18dad0
bool __cdecl HandlePetition_SubmitPetitionOk(::Session const *, ::Packet const *);  // 0x18db60
bool __cdecl HandlePetition_SubmitPetitionFail(::Session const *, ::Packet const *);  // 0x18e0e0
bool __cdecl HandlePetition_CancelPetitionOk(::Session const *, ::Packet const *);  // 0x18e380
bool __cdecl HandlePetition_CancelPetitionFail(::Session const *, ::Packet const *);  // 0x18e590
bool __cdecl HandlePetition_FeedbackAck(::Session const *, ::Packet const *);  // 0x18e7c0
bool __cdecl HandlePetition_Checkout_Notify(::Session const *, ::Packet const *);  // 0x18ead0
bool __cdecl HandlePetition_Finish_Notify(::Session const *, ::Packet const *);  // 0x18ec90
bool __cdecl HandlePetition_Finish2_Notify(::Session const *, ::Packet const *);  // 0x18ed30
bool __cdecl HandlePetition_LeaveMessageReq(::Session const *, ::Packet const *);  // 0x18edd0
bool __cdecl HandlePetition_CharacterInfoReq(::Session const *, ::Packet const *);  // 0x18f340
bool __cdecl HandlePetition_ConnectedCharInfoReq(::Session const *, ::Packet const *);  // 0x18f440
bool __cdecl HandlePetition_CurrentPetitionAck(::Session const *, ::Packet const *);  // 0x18f570
bool __cdecl HandlePetition_ConnectedUnReadCharsInfoReq(::Session const *, ::Packet const *);  // 0x18f7a0
