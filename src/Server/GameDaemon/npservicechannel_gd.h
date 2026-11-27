// npservicechannel_gd.h: npservicechannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class NPGameServiceChannel
{
public:
    bool __cdecl SendResponseGameGroupValidateGroupFail(unsigned int, wchar_t const *, int);  // 0x16f1b0
    bool __cdecl SendResponseGameGroupGetChannelPropertyOk(unsigned int, wchar_t *, ::NPChatChannelType, int, int, int, int, int, int, int, int, ::StsMsgLib::_StsMsgResponseGameGroupGetChannelProperty::ETransportType, int);  // 0x16f240
    bool __cdecl SendResponseGameGroupGetChannelPropertyFail(unsigned int, wchar_t const *, int);  // 0x16f340
    bool __cdecl SendResponseGameGroupGroupInfoFail(unsigned int, wchar_t const *, int);  // 0x16f3e0
};

class NPGameTransaction
{
public:
    virtual void __cdecl Expire(void);  // 0x16f470
};

class NPServiceChannelManager
{
public:
    bool __cdecl Initialize(unsigned int, unsigned long, unsigned short, long, long);  // 0x16e920
    void __cdecl CheckPing(void);  // 0x16eb40
    virtual bool __cdecl OnConnect(::NPChannel *, bool) const;  // 0x16ebc0
    virtual bool __cdecl OnClose(::NPChannel *, bool) const;  // 0x16ee90
    virtual bool __cdecl HandleMessage(::NPChannel *, ::StsMsgLib::_StsMsg *, void *) const;  // 0x16f020
};

void __cdecl NPGameServiceChannelCmdDispatcher(unsigned int, ::StsMsgLib::ECommand &);  // 0x16e840
