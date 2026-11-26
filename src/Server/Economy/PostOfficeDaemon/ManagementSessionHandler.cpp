// ManagementSessionHandler.obj (PostOfficeDaemon PDB). Source: .scratch/hr/ManagementSessionHandler.c
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <stdio.h>
#include "ManagementSessionHandler.h"
#include "Log.h"
#include "Packet.h"
#include "PacketBuffer.h"
#include "Session.h"

namespace
{
wchar_t const* const MANAGEMENT_SESSION_FILE = L"ManagementSessionHandler.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
static wchar_t const* const MODULE_NAME = L"management session handler";  // PDB MODULE_NAME
}

// LIFT: no out-of-line copy found
ManagementSessionHandler::~ManagementSessionHandler()
{
}

// 0x10be0
bool ManagementSessionHandler::OnAccept(Session const* session) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_NOTICE, MANAGEMENT_SESSION_FILE, 25,
               L"[%s], %s; accepted management session, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
               MODULE_NAME, L"ManagementSessionHandler::OnAccept", sessionId,
               static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
    return true;
}

// 0x10c40
bool ManagementSessionHandler::OnConnect(Session const* session, bool firstConnected) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_ERROR, MANAGEMENT_SESSION_FILE, 31,
               L"[%s], %s; cannot use ManagementSessionHandler::OnConnect handler, sessionId:0x%I64X, portId:%u, "
               L"sessionIndex:%u",
               MODULE_NAME, L"ManagementSessionHandler::OnConnect", sessionId,
               static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
    return false;
}

// 0x10ca0
void ManagementSessionHandler::OnClose(Session const* session, bool tryReconnect) const
{
    unsigned long long const sessionId = session->_id;
    Log::Write(Log::LT_NOTICE, MANAGEMENT_SESSION_FILE, 37,
               L"[%s], %s; closed management session, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
               MODULE_NAME, L"ManagementSessionHandler::OnClose", sessionId,
               static_cast<unsigned int>(sessionId >> 32), static_cast<unsigned int>(sessionId));
}

// 0x10d00
bool ManagementSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    wchar_t command[65] = {0};
    wchar_t failReason[257] = {0};

    if (packet->DecomposeText("s", command, 65) == 0)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_SESSION_FILE, 46,
                   L"[%s], %s; failed to decompose command, session:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"ManagementSessionHandler::PacketHandler", session->_id,
                   static_cast<unsigned int>(session->_id >> 32), static_cast<unsigned int>(session->_id));
        _snwprintf_s(failReason, 0x101, _TRUNCATE, L"failed to decompose command");
        goto $_ERROR;
    }

    {
        int index = 1;
        for (; index < 16; ++index)
        {
            if (_wcsicmp(command, PostOfficeManagementCommandList[index]) == 0)
                break;
        }

        // LIFT: 0x10d00 the PDB lines 61-69 and the label $_ERROR give a goto form. The handler tail call is the last block.
        if (index == 16)
        {
            Log::Write(Log::LT_ERROR, MANAGEMENT_SESSION_FILE, 61,
                       L"[%s], %s; invalid packet command of management session, command:%s, session:0x%I64X, portId:%u, "
                       L"sessionIndex:%u",
                       MODULE_NAME, L"ManagementSessionHandler::PacketHandler", command, session->_id,
                       static_cast<unsigned int>(session->_id >> 32), static_cast<unsigned int>(session->_id));
            _snwprintf_s(failReason, 0x101, _TRUNCATE, L"invalid packet command");
            goto $_ERROR;
        }

        Daemon::PacketHandler const handler = PostOfficeManagementPacketServerSideHandlerList[index];
        if (handler == nullptr)
        {
            Log::Write(Log::LT_ERROR, MANAGEMENT_SESSION_FILE, 68,
                       L"[%s], %s; invalid packet command of management session, command:%s, session:0x%I64X, portId:%u, "
                       L"sessionIndex:%u",
                       MODULE_NAME, L"ManagementSessionHandler::PacketHandler", command, session->_id,
                       static_cast<unsigned int>(session->_id >> 32), static_cast<unsigned int>(session->_id));
            _snwprintf_s(failReason, 0x101, _TRUNCATE, L"invalid packet command");
            goto $_ERROR;
        }
        return handler(session, packet);
    }

$_ERROR:
    // LIFT: Packet constructor, inlined (0x10d00): the fields are set one by one.
    Packet reply;
    reply.CurHeader = nullptr;
    reply.Splitter = nullptr;
    reply.ListHead = nullptr;
    reply.ListTail = nullptr;
    reply.IsFragmentPacket = false;
    reply.FragmentPacketCmd = 0;
    reply.Allocate();
    SendTextReply(session, &reply, command, failReason);
    return false;
}

// LIFT: inlined in each caller
void ManagementSessionHandler::SendTextReply(Session const* session, Packet* reply, wchar_t const* text1,
                                             wchar_t const* text2)
{
    reply->ComposeText("ss", text1, text2);
    PacketBuffer const* buffer = reply->ListHead;
    reply->ListHead->encrypt(session->_currentCrypt, session->_security3rd);
    Session* lockedSession = const_cast<Session*>(session);  // the original locks through a const session
    lockedSession->_lock.Enter();
    session->send(&buffer, 1);  // LIFT: inlined send
    lockedSession->_lock.Leave();
}
