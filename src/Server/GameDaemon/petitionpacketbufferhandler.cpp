// petitionpacketbufferhandler.cpp: petitionpacketbufferhandler.cpp (GameDaemon PDB, 2019 + PDB).
#include <stdarg.h>
#include "petitionpacketbufferhandler.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "LiftStub.h"
#include "AlertSender.h"
#include "Log.h"

// LIFT: per-exe path literal (lessons A6).
#define PETITIONPACKETBUFFERHANDLER_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\PetitionPacketBufferHandler.cpp"

// 0x190990
::PacketBufferHandler * __cdecl PetitionPacketBufferHandler::Clone(void *) const
{
    LIFT_STUB(0x190990);
}

// 0x1909e0
#pragma comment(linker, "/INCLUDE:?Destroy@PetitionPacketBufferHandler@@UEAAXPEAX@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl PetitionPacketBufferHandler::Destroy(void *buffer)
{
    // LIFT: a handler made in a caller buffer (placement form of Clone) is not freed.
    if (buffer == NULL)
        Memory::_Manager[2]->Free(this, PETITIONPACKETBUFFERHANDLER_FILE, 40);
}

// 0x190a10
int __cdecl PetitionPacketBufferHandler::ToPacket(::Session const *, char const *, int, int, char const **)
{
    LIFT_STUB(0x190a10);
}

// 0x190a90
#pragma comment(linker, "/INCLUDE:?ToBuffer@PetitionPacketBufferHandler@@UEAAHPEBVSession@@PEADHPEBDPEAPEBD@Z")  // LIFT: dead-strip keep (no live caller yet)
int __cdecl PetitionPacketBufferHandler::ToBuffer(::Session const *, char *, int, char const *packet, char const **sendBuffer)
{
    if (sendBuffer != NULL)
        *sendBuffer = packet;
    // LIFT: the packet header size (Packet::Header::size) is changed in place. The caller owns the packet buffer.
    ::Packet::Header *const header = reinterpret_cast< ::Packet::Header *>(const_cast<char *>(packet));
    int const size = header->size;
    header->size -= 3;
    return size;
}

// 0x190ab0
unsigned short __cdecl PetitionPacketBufferHandler::Compose(::Packet *, char const *, ...)
{
    LIFT_STUB(0x190ab0);
}

// 0x190b70
unsigned short __cdecl PetitionPacketBufferHandler::Decompose(::Packet const *, unsigned int, int, char const *, ...)
{
    LIFT_STUB(0x190b70);
}

// 0x190c10
#pragma comment(linker, "/INCLUDE:?Decompose@PetitionPacketBufferHandler@@SAGPEBVPacket@@PEBDZZ")  // LIFT: dead-strip keep (no live caller yet)
unsigned short __cdecl PetitionPacketBufferHandler::Decompose(::Packet const *p, char const *format, ...)
{
    va_list args;
    va_start(args, format);
    ::Packet::Header const *const header = p->CurHeader;
    if (header->size != 0 && format != NULL)
        return Decompose(reinterpret_cast<char const *>(header + 1), static_cast<unsigned short>(header->size) + 1, format, static_cast<unsigned __int64>(-1), args);
    AlertSender::Write(PETITIONPACKETBUFFERHANDLER_FILE, 146, L"[petition packet], Decompose2 Fail. invalid argument.");
    Log::Write(Log::LT_ERROR, PETITIONPACKETBUFFERHANDLER_FILE, 146, L"[petition packet], Decompose2 Fail. invalid argument.");
    return 0;
}

// 0x190ca0
unsigned short __cdecl PetitionPacketBufferHandler::Compose(char *, unsigned int, char const *, unsigned __int64, char *)
{
    LIFT_STUB(0x190ca0);
}

// 0x191230
unsigned short __cdecl PetitionPacketBufferHandler::Decompose(char const *, unsigned int, char const *, unsigned __int64, char *)
{
    LIFT_STUB(0x191230);
}

// 0x1917f0
short __cdecl PetitionPacketBufferHandler::getBinaryFormatSize(char const *, short &)
{
    LIFT_STUB(0x1917f0);
}
