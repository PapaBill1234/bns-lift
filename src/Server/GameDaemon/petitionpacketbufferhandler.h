// petitionpacketbufferhandler.h: petitionpacketbufferhandler.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class PetitionPacketBufferHandler
{
public:
    virtual ::PacketBufferHandler * __cdecl Clone(void *) const;  // 0x190990
    virtual void __cdecl Destroy(void *);  // 0x1909e0
    virtual int __cdecl ToPacket(::Session const *, char const *, int, int, char const **);  // 0x190a10
    virtual int __cdecl ToBuffer(::Session const *, char *, int, char const *, char const **);  // 0x190a90
    static unsigned short __cdecl Compose(::Packet *, char const *, ...);  // 0x190ab0
    static unsigned short __cdecl Decompose(::Packet const *, unsigned int, int, char const *, ...);  // 0x190b70
    static unsigned short __cdecl Decompose(::Packet const *, char const *, ...);  // 0x190c10
    static unsigned short __cdecl Compose(char *, unsigned int, char const *, unsigned __int64, char *);  // 0x190ca0
    static unsigned short __cdecl Decompose(char const *, unsigned int, char const *, unsigned __int64, char *);  // 0x191230
private:
    static short __cdecl getBinaryFormatSize(char const *, short &);  // 0x1917f0
};

