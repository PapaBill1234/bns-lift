// FragmentPacket.obj (CacheGate PDB): SendFragmentPacketConcatenater.
#include "PacketUtil.h"

#include <new>

#include "AlertSender.h"
#include "Log.h"
#include "Packet.h"

static wchar_t const FRAGMENT_PACKET_FILE[] = L"..\\..\\Packet\\FragmentPacket.cpp";

// 0x11c0
SendFragmentPacketConcatenater::~SendFragmentPacketConcatenater()
{
    _packet.Clear();
}

// 0x1200
void SendFragmentPacketConcatenater::Clear()
{
    _packet.Clear();
}

// 0x1210
unsigned long long SendFragmentPacketConcatenater::AllocSize() const
{
    return sizeof(SendFragmentPacketConcatenater);
}

// 0x1220
PacketConcatenater* SendFragmentPacketConcatenater::Clone(void* buffer) const
{
    if (buffer == nullptr)
    {
        Log::Write(Log::LT_ERROR, FRAGMENT_PACKET_FILE, 389,
                   L"== CRASH == [network], SendFragmentPacketConcatenater Clone() failed");
        AlertSender::Write(FRAGMENT_PACKET_FILE, 389,
                           L"== CRASH == [network], SendFragmentPacketConcatenater Clone() failed");
        return nullptr;
    }
    return new (buffer) SendFragmentPacketConcatenater();
}

// 0x1290
void SendFragmentPacketConcatenater::Destroy(void* buffer)
{
    // The original calls the virtual destructor of this object (flag 0). It does not use buffer.
    this->~SendFragmentPacketConcatenater();
}
