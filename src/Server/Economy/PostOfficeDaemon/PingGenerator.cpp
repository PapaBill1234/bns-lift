// PingGenerator.obj (PostOfficeDaemon PDB).
#include "PingGenerator.h"
#include <new>
#include <windows.h>
#include "Log.h"
#include "Memory.h"
#include "PostOfficeDaemon.h"
#include "PingRelay.h"

#define PING_GENERATOR_FILE L"PingGenerator.cpp"
static wchar_t const* const MODULE_NAME = L"ping generator";  // PDB MODULE_NAME

static bool isStopState(int state)  // LIFT: inlined switch
{
    return state == Daemon::STATE_STOPPED || state == Daemon::STATE_STOPPING ||
           state == Daemon::STATE_COOLDOWNING || state == Daemon::STATE_COOLDOWNED;
}

// 0x4cf0
void PingRelayContext::initResponse(RelayResponse* const response)
{
    PingRelayResponse* const pingResponse = static_cast<PingRelayResponse*>(response);
    static_cast<RelayResponse&>(_response) = *pingResponse;
    _response._pingSeq = pingResponse->_pingSeq;
}

// 0xfb40
unsigned short const PingRelayContext::GetRequestWid() const
{
    return _economyHeader._fromWid;
}

// LIFT: folded (ICF) with 0x34c40
bool PingRelayContext::ComposeRequestPacket(FragmentPacket&) const
{
    return true;  // 0x34c40 (ICF): mov al,1; ret.
}

// LIFT: folded (ICF) with 0x34c40
bool PingRelayContext::ComposeResponsePacket(FragmentPacket&) const
{
    return true;
}

// 0x34c40
bool PingRelayContext::ComposeResponsePacket(Packet&) const
{
    return true;
}

// 0x4d70
bool PingGenerator::HandleEvent(EventContext* context, unsigned long bytes)
{
    if (isStopState(Daemon::Instance->State))
        return true;

    Log::Write(Log::LT_DEBUG, PING_GENERATOR_FILE, 25, L"[%s], %s; <BEGIN TIMER HANDLER>", MODULE_NAME,
               L"PingGenerator::HandleEvent");
    bool const result = sendPing();
    Log::Write(Log::LT_DEBUG, PING_GENERATOR_FILE, 29, L"[%s], %s; <END TIMER HANDLER>", MODULE_NAME,
               L"PingGenerator::HandleEvent");
    if (result)
        return true;

    if (isStopState(Daemon::Instance->State) ||
        PostOfficeDaemon::_instance->AddTimer(1000 * PostOfficeDaemon::_instance->_config->_pingInterval, this))
        return true;

    Log::Write(Log::LT_ERROR, PING_GENERATOR_FILE, 34, L"[%s], %s; failed to add ping generator timer, wid:%u",
               MODULE_NAME, L"PingGenerator::HandleEvent", _wid);
    return false;
}

// 0x4ed0
bool PingGenerator::sendPing()
{
    CacheGateChannel* const channel = PostOfficeDaemon::_instance->checkCacheGateServiceState();
    if (channel == nullptr)
    {
        Log::Write(Log::LT_ERROR, PING_GENERATOR_FILE, 49, L"[%s], %s; cannot send ping relay request, wid:%u",
                   MODULE_NAME, L"PingGenerator::sendPing", _wid);
        return false;
    }

    // LIFT: inline of the RelayContextManager id generator
    long long volatile* const idSeed = reinterpret_cast<long long volatile*>(&RelayContextManager::_idSeed);
    unsigned long long relayTid = static_cast<unsigned long long>(InterlockedIncrement64(idSeed));
    if (relayTid == 0)
        relayTid = static_cast<unsigned long long>(InterlockedIncrement64(idSeed));

    EconomyHeader economyHeader;
    economyHeader._fromWid = PostOfficeDaemon::_instance->_serviceWid;
    economyHeader._toWid = _wid;
    economyHeader._relayTid = relayTid;

    unsigned long long const pingSeq =
        static_cast<unsigned long long>(InterlockedIncrement64(reinterpret_cast<long long volatile*>(&_pingSeq)));

    // LIFT: named request local. The original 0x4fab builds it on the stack before Alloc (unwind dtor$0 0x60220).
    PingRelayRequest const request(pingSeq);
    void* const memory = Memory::_Manager[2]->Alloc(sizeof(PingRelayContext), PING_GENERATOR_FILE, 60);
    PingRelayContext* const relayContext =
        memory != nullptr ? ::new (memory) PingRelayContext(economyHeader, request) : nullptr;

    // BUG: 0x4ed0 relayContext can be null here (Alloc failed); the call does not check it.
    if (!relayContext->ProcessRelayRequest(channel))
    {
        Log::Write(Log::LT_ERROR, PING_GENERATOR_FILE, 64,
                   L"[%s], %s; failed to send ping relay request, relayTid:0x%I64X, wid:%u, pingSeq:%I64u",
                   MODULE_NAME, L"PingGenerator::sendPing", relayTid, _wid, pingSeq);
        relayContext->removeReferenceCount(PING_GENERATOR_FILE, 65);
        channel->removeReferenceCount(PING_GENERATOR_FILE, 66);
        return false;
    }

    relayContext->removeReferenceCount(PING_GENERATOR_FILE, 70);
    channel->removeReferenceCount(PING_GENERATOR_FILE, 73);
    return true;
}
