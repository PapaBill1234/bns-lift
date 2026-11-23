// PostOfficePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB).
#include <winsock2.h>
#include <windows.h>
#include "PostOfficePacketHandler.h"
#include "LobbyDaemon.h"
#include "LobbyJob.h"
#include "Log.h"
#include "Packet.h"
#include "PacketUtil.h"

namespace
{
wchar_t const* const POST_OFFICE_PH_FILE = L"PostOfficePacketHandler.cpp";  // LIFT: No PDB symbol. The binary uses the literal as the file string of the log calls (0x64740, 0x647f0, 0x64a20).

// PDB struct PostOfficeRegisterPostFailParam (LobbyDaemon type, sizeof 0x10).
struct PostOfficeRegisterPostFailParam
{
    unsigned long long receiptId;
    short reason;
};
static_assert(sizeof(PostOfficeRegisterPostFailParam) == 0x10, "sizeof PostOfficeRegisterPostFailParam");

// LIFT: The binary sets the decomposer fields by hand in each handler (0x64740, 0x647f0, 0x64a20): len = strlen(format), index = 1, offset = 2.
void setupDecomposer(PacketDecomposer& pdr, char const* format, int len)
{
    pdr.format = format;
    pdr.len = len;
    pdr.index = 1;
    pdr.offset = 2;
}

// LIFT: The PDB has no LobbyJob members yet. The binary inlines LobbyJobManager::find + execute here.
// LobbyJobManager::ExecuteW has the same behaviour, including the "no such job" log.
}

// 0x646f0
bool HandlePostOfficeHelloOk(Session const*, Packet const*)
{
    void* const event = LobbyDaemon::_instance->_postOfficeInitialConnectEvent.Event;
    if (event != nullptr)
        SetEvent(event);
    Log::Write(Log::LT_DEBUG, POST_OFFICE_PH_FILE, 19, L"[post-office], handle hello ok ok");
    return true;
}

// 0x64740
bool HandlePostOfficeHelloFail(Session const*, Packet const* packet)
{
    PacketDecomposer pdr;
    setupDecomposer(pdr, "hh", 2);
    short reason = 0;
    if (0 == packet->Decompose(&pdr, 1, &reason))
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_PH_FILE, 35,
                   L"[post-office], handle hello fail fail; decompose fail, reason:%d", static_cast<int>(reason));
        return false;
    }
    Log::Write(Log::LT_DEBUG, POST_OFFICE_PH_FILE, 39, L"[post-office], handle hello fail ok, reason:%d",
               static_cast<int>(reason));
    return true;
}

// 0x647f0
bool HandlePostOfficeRegisterPostOk(Session const*, Packet const* packet)
{
    PacketDecomposer pdr;
    setupDecomposer(pdr, "hqq", 3);
    unsigned long long tid = 0;
    unsigned long long receiptId = 0;
    if (0 == packet->Decompose(&pdr, 2, &tid, &receiptId))
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_PH_FILE, 58,
                   L"[post-office], handle register post ok fail; decompose fail, tid:0x%I64X, receipt-id:0x%I64X", tid,
                   receiptId);
        return false;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 171, &receiptId))
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_PH_FILE, 65,
                   L"[post-office], handle register post ok fail; execute job fail, tid:0x%I64X, receipt-id:0x%I64X",
                   tid, receiptId);
        return false;
    }
    Log::Write(Log::LT_DEBUG, POST_OFFICE_PH_FILE, 70,
               L"[post-office], handle register post ok ok, tid:0x%I64X, receipt-id:0x%I64X", tid, receiptId);
    return true;
}

// 0x64a20
bool HandlePostOfficeRegisterPostFail(Session const*, Packet const* packet)
{
    PacketDecomposer pdr;
    setupDecomposer(pdr, "hqqE", 4);
    unsigned long long tid = 0;
    // LIFT: zero-init on purpose. The original (0x64a20) leaves param uninitialised and the
    // decompose-fail log then prints stack garbage for receipt-id and reason. We fix this bug.
    PostOfficeRegisterPostFailParam param = {};
    if (0 == packet->Decompose(&pdr, 3, &tid, &param, &param.reason))
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_PH_FILE, 92,
                   L"[post-office], handle register post fail fail; decompose fail, tid:0x%I64X, receipt-id:0x%I64X, reason:%d",
                   tid, param.receiptId, static_cast<int>(param.reason));
        return false;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 172, &param))
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_PH_FILE, 99,
                   L"[post-office], handle register post fail fail; execute job fail, tid:0x%I64X, receipt-id:0x%I64X, reason:%d",
                   tid, param.receiptId, static_cast<int>(param.reason));
        return false;
    }
    Log::Write(Log::LT_DEBUG, POST_OFFICE_PH_FILE, 104,
               L"[post-office], handle register post fail ok, tid:0x%I64X, receipt-id:0x%I64X, reason:%d", tid,
               param.receiptId, static_cast<int>(param.reason));
    return true;
}
