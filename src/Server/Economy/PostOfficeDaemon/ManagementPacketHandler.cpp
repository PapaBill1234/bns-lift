// ManagementPacketHandler.obj (PostOfficeDaemon PDB). Source: .scratch/hr/ManagementPacketHandler.c
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <stdio.h>
#include "ManagementPacketHandler.h"
#include "ManagementSessionHandler.h"
#include "Log.h"
#include "Packet.h"
#include "PacketBuffer.h"
#include "PostContext.h"
#include "PostOfficeDB.h"
#include "PostOfficeDaemon.h"
#include "Session.h"

namespace
{
wchar_t const* const MANAGEMENT_PACKET_FILE = L"ManagementPacketHandler.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
static wchar_t const* const MODULE_NAME = L"management packet handler";  // PDB MODULE_NAME

// LIFT: Inlined in each handler: zero the packet and allocate the first buffer.
void initReply(Packet* reply)
{
    reply->CurHeader = nullptr;
    reply->Splitter = nullptr;
    reply->ListHead = nullptr;
    reply->ListTail = nullptr;
    reply->IsFragmentPacket = false;
    reply->FragmentPacketCmd = 0;
    reply->Allocate();
}

// LIFT: Inlined in each handler: compose "ss", encrypt and send under the session lock.
void sendTextReply(Session const* session, Packet* reply, wchar_t const* text1, wchar_t const* text2)
{
    ManagementSessionHandler::SendTextReply(session, reply, text1, text2);
}
}

// 0x97d0
bool HandlePostOfficeManagementHelloReq(Session const* session, Packet const* packet)
{
    Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 27, L"[%s], %s; <BEGIN PACKET HANDLER>", MODULE_NAME,
               L"HandlePostOfficeManagementHelloReq");
    Packet reply;
    initReply(&reply);
    sendTextReply(session, &reply, L"Hello,", L"How are you?");
    Log::Write(Log::LT_NOTICE, MANAGEMENT_PACKET_FILE, 33, L"[%s], %s; sent hello success ask", MODULE_NAME,
               L"HandlePostOfficeManagementHelloReq");
    Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 35, L"[%s], %s; <END PACKET HANDLER>", MODULE_NAME,
               L"HandlePostOfficeManagementHelloReq");
    return true;
}

// 0x9950
bool HandlePostOfficeManagementResetPostStatusReq(Session const* session, Packet const* packet)
{
    wchar_t const* const FUNC = L"HandlePostOfficeManagementResetPostStatusReq";
    Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 42, L"[%s], %s; <BEGIN PACKET HANDLER>", MODULE_NAME,
               FUNC);
    Packet reply;
    initReply(&reply);
    wchar_t command[65] = {0};
    wchar_t failReason[257] = {0};
    long long postId = 0;
    long long invoiceId = 0;
    long long recipientPcId = 0;
    PostContext* postContext = nullptr;

    if (packet->DecomposeText("sqqq", command, 65, &postId, &invoiceId, &recipientPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_PACKET_FILE, 59, L"[%s], %s; failed to decompose packet",
                   MODULE_NAME, FUNC);
        _snwprintf_s(failReason, 0x101, _TRUNCATE, L"failed to decompose packet");
    }
    else
    {
        Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 63,
                   L"[%s], %s; decomposed packet, postId:0x%I64X, invoiceId:0x%I64X, recipientPcId:0x%I64X",
                   MODULE_NAME, FUNC, postId, invoiceId, recipientPcId);
        if (postId <= 0 || recipientPcId <= 0)
        {
            Log::Write(Log::LT_ERROR, MANAGEMENT_PACKET_FILE, 67,
                       L"[%s], %s; invalid parameter, postId:0x%I64X, invoiceId:0x%I64X, recipientPcId:0x%I64X",
                       MODULE_NAME, FUNC, postId, invoiceId, recipientPcId);
            _snwprintf_s(failReason, 0x101, _TRUNCATE,
                         L"invalid parameter, postId:0x%I64X, invoiceId:0x%I64X, recipientPcId:0x%I64X", postId,
                         invoiceId, recipientPcId);
        }
        else
        {
            postContext = PostOfficeDaemon::_instance->_postContextManager->GetContext(postId);
            if (postContext != nullptr)
            {
                Log::Write(Log::LT_ERROR, MANAGEMENT_PACKET_FILE, 74,
                           L"[%s], %s; post context is exists on memory, postId:0x%I64X", MODULE_NAME, FUNC,
                           postId);
                _snwprintf_s(failReason, 0x101, _TRUNCATE, L"post context is exists on memory, postId:0x%I64X",
                             postId);
            }
            else
            {
                int dbRetValue = 0;
                if (!PostOfficeDB::UpdateStatusToRetryReady(&dbRetValue, postId, invoiceId, recipientPcId))
                {
                Log::Write(Log::LT_ERROR, MANAGEMENT_PACKET_FILE, 81,
                           L"[%s], %s; failed to update post status [retry ready status], dbRetValue:%d, "
                           L"postId:0x%I64X, invoiceId:0x%I64X, recipientPcId:0x%I64X",
                           MODULE_NAME, FUNC, dbRetValue, postId, invoiceId, recipientPcId);
                _snwprintf_s(failReason, 0x101, _TRUNCATE,
                             L"failed to update post status [retry ready status], dbRetValue:%d, postId:0x%I64X, "
                             L"invoiceId:0x%I64X, recipientPcId:0x%I64X",
                             dbRetValue, postId, invoiceId, recipientPcId);
                }
                else
                {
                    _snwprintf_s(failReason, 0x101, _TRUNCATE,
                                 L"succeeded to update post status [retry ready status], postId:0x%I64X", postId);
                    sendTextReply(session, &reply, command, failReason);
                    Log::Write(Log::LT_NOTICE, MANAGEMENT_PACKET_FILE, 91,
                               L"[%s], %s; sent post status update success ack [retry ready status]",
                               MODULE_NAME, FUNC);
                    Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 93, L"[%s], %s; <END PACKET HANDLER>",
                               MODULE_NAME, FUNC);
                    return true;
                }
            }
        }
    }

    sendTextReply(session, &reply, command, failReason);
    Log::Write(Log::LT_NOTICE, MANAGEMENT_PACKET_FILE, 99,
               L"[%s], %s; sent post status update failure ack [retry ready status]", MODULE_NAME, FUNC);
    if (postContext != nullptr)
        postContext->removeReferenceCount(MANAGEMENT_PACKET_FILE, 102);
    Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 104, L"[%s], %s; <END PACKET HANDLER>", MODULE_NAME,
               FUNC);
    return true;
}

// 0x9e90
bool HandlePostOfficeManagementLoadRetryReadySinglePostReq(Session const* session, Packet const* packet)
{
    wchar_t const* const FUNC = L"HandlePostOfficeManagementLoadRetryReadySinglePostReq";
    Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 110, L"[%s], %s; <BEGIN PACKET HANDLER>", MODULE_NAME,
               FUNC);
    Packet reply;
    initReply(&reply);
    wchar_t command[65] = {0};
    wchar_t failReason[257] = {0};
    long long postId = 0;
    long long invoiceId = 0;
    long long recipientPcId = 0;
    PostContext* postContext = nullptr;

    if (packet->DecomposeText("sqqq", command, 65, &postId, &invoiceId, &recipientPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_PACKET_FILE, 127, L"[%s], %s; failed to decompose packet",
                   MODULE_NAME, FUNC);
        _snwprintf_s(failReason, 0x101, _TRUNCATE, L"failed to decompose packet");
    }
    else
    {
        Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 131,
                   L"[%s], %s; decomposed packet, postId:0x%I64X, invoiceId:0x%I64X, recipientPcId:0x%I64X",
                   MODULE_NAME, FUNC, postId, invoiceId, recipientPcId);
        if (postId <= 0 || recipientPcId <= 0)
        {
            Log::Write(Log::LT_ERROR, MANAGEMENT_PACKET_FILE, 135,
                       L"[%s], %s; invalid parameter, postId:0x%I64X, invoiceId:0x%I64X, recipientPcId:0x%I64X",
                       MODULE_NAME, FUNC, postId, invoiceId, recipientPcId);
            _snwprintf_s(failReason, 0x101, _TRUNCATE,
                         L"invalid parameter, postId:0x%I64X, invoiceId:0x%I64X, recipientPcId:0x%I64X", postId,
                         invoiceId, recipientPcId);
        }
        else
        {
            postContext = PostOfficeDaemon::_instance->_postContextManager->GetContext(postId);
            if (postContext != nullptr)
            {
                Log::Write(Log::LT_ERROR, MANAGEMENT_PACKET_FILE, 142,
                           L"[%s], %s; post context is exists on memory, postId:0x%I64X", MODULE_NAME, FUNC,
                           postId);
                _snwprintf_s(failReason, 0x101, _TRUNCATE, L"post context is exists on memory, postId:0x%I64X",
                             postId);
            }
            else
            {
                int dbRetValue = 0;
                if (!PostOfficeDB::LoadRetryReadySinglePost(&dbRetValue, postId, invoiceId, recipientPcId))
                {
                Log::Write(Log::LT_ERROR, MANAGEMENT_PACKET_FILE, 149,
                           L"[%s], %s; failed to load retry ready single post, dbRetValue:%d, postId:0x%I64X, "
                           L"invoiceId:0x%I64X, recipientPcId:0x%I64X",
                           MODULE_NAME, FUNC, dbRetValue, postId, invoiceId, recipientPcId);
                _snwprintf_s(failReason, 0x101, _TRUNCATE,
                             L"failed to load retry ready single post, dbRetValue:%d, postId:0x%I64X, "
                             L"invoiceId:0x%I64X, recipientPcId:0x%I64X",
                             dbRetValue, postId, invoiceId, recipientPcId);
                }
                else
                {
                    _snwprintf_s(failReason, 0x101, _TRUNCATE,
                                 L"succeeded to load retry ready single post, postId:0x%I64X", postId);
                    sendTextReply(session, &reply, command, failReason);
                    Log::Write(Log::LT_NOTICE, MANAGEMENT_PACKET_FILE, 159,
                               L"[%s], %s; sent retry ready single post load success ack", MODULE_NAME,
                               FUNC);
                    Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 161, L"[%s], %s; <END PACKET HANDLER>",
                               MODULE_NAME, FUNC);
                    return true;
                }
            }
        }
    }

    sendTextReply(session, &reply, command, failReason);
    Log::Write(Log::LT_NOTICE, MANAGEMENT_PACKET_FILE, 167, L"[%s], %s; sent retry ready single post load failure ack",
               MODULE_NAME, FUNC);
    if (postContext != nullptr)
        postContext->removeReferenceCount(MANAGEMENT_PACKET_FILE, 170);
    Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 172, L"[%s], %s; <END PACKET HANDLER>", MODULE_NAME,
               FUNC);
    return true;
}

// 0xa3d0
bool HandlePostOfficeManagementResetAllPostStatusReq(Session const* session, Packet const* packet)
{
    wchar_t const* const FUNC = L"HandlePostOfficeManagementResetAllPostStatusReq";
    Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 178, L"[%s], %s; <BEGIN PACKET HANDLER>", MODULE_NAME,
               FUNC);
    Packet reply;
    initReply(&reply);
    wchar_t command[65] = {0};
    wchar_t failReason[257] = {0};

    if (packet->DecomposeText("s", command, 65) == 0)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_PACKET_FILE, 187, L"[%s], %s; failed to decompose packet",
                   MODULE_NAME, FUNC);
        _snwprintf_s(failReason, 0x101, _TRUNCATE, L"failed to decompose packet");
    }
    else
    {
        Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 191, L"[%s], %s; decomposed packet", MODULE_NAME,
                   FUNC);
        int dbRetValue = 0;
        if (!PostOfficeDB::ResetAllDeliveryFailurePost(&dbRetValue))
        {
            Log::Write(Log::LT_ERROR, MANAGEMENT_PACKET_FILE, 195,
                       L"[%s], %s; failed to reset all delivery failure post [retry ready status], dbRetValue:%d",
                       MODULE_NAME, FUNC, dbRetValue);
            _snwprintf_s(failReason, 0x101, _TRUNCATE,
                         L"failed to reset all delivery failure post [retry ready status], dbRetValue:%d",
                         dbRetValue);
        }
        else
        {
            _snwprintf_s(failReason, 0x101, _TRUNCATE,
                         L"succeeded to reset all delivery failure post [retry ready status]");
            sendTextReply(session, &reply, command, failReason);
            Log::Write(Log::LT_NOTICE, MANAGEMENT_PACKET_FILE, 205,
                       L"[%s], %s; sent all delivery failure post reset success ack [retry ready status]",
                       MODULE_NAME, FUNC);
            Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 207, L"[%s], %s; <END PACKET HANDLER>",
                       MODULE_NAME, FUNC);
            return true;
        }
    }

    sendTextReply(session, &reply, command, failReason);
    Log::Write(Log::LT_NOTICE, MANAGEMENT_PACKET_FILE, 213,
               L"[%s], %s; sent all delivery failure post reset failure ack [retry ready status]",
               MODULE_NAME, FUNC);
    Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 215, L"[%s], %s; <END PACKET HANDLER>", MODULE_NAME,
               FUNC);
    return true;
}

// 0xa750
bool HandlePostOfficeManagementLoadRetryReadyPostListReq(Session const* session, Packet const* packet)
{
    wchar_t const* const FUNC = L"HandlePostOfficeManagementLoadRetryReadyPostListReq";
    Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 221, L"[%s], %s; <BEGIN PACKET HANDLER>", MODULE_NAME,
               FUNC);
    Packet reply;
    initReply(&reply);
    wchar_t command[65] = {0};
    wchar_t failReason[257] = {0};

    if (packet->DecomposeText("s", command, 65) == 0)
    {
        Log::Write(Log::LT_ERROR, MANAGEMENT_PACKET_FILE, 230, L"[%s], %s; failed to decompose packet",
                   MODULE_NAME, FUNC);
        _snwprintf_s(failReason, 0x101, _TRUNCATE, L"failed to decompose packet");
    }
    else
    {
        Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 234, L"[%s], %s; decomposed packet", MODULE_NAME,
                   FUNC);
        int dbRetValue = 0;
        if (!PostOfficeDB::LoadRetryReadyPostList(&dbRetValue))
        {
            Log::Write(Log::LT_ERROR, MANAGEMENT_PACKET_FILE, 238,
                       L"[%s], %s; failed to load retry ready post list, dbRetValue:%d", MODULE_NAME, FUNC,
                       dbRetValue);
            _snwprintf_s(failReason, 0x101, _TRUNCATE, L"failed to load retry ready post list, dbRetValue:%d",
                         dbRetValue);
        }
        else
        {
            _snwprintf_s(failReason, 0x101, _TRUNCATE, L"succeeded to load retry ready post list");
            sendTextReply(session, &reply, command, failReason);
            Log::Write(Log::LT_NOTICE, MANAGEMENT_PACKET_FILE, 248,
                       L"[%s], %s; sent retry ready post list load success ack", MODULE_NAME, FUNC);
            Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 250, L"[%s], %s; <END PACKET HANDLER>",
                       MODULE_NAME, FUNC);
            return true;
        }
    }

    sendTextReply(session, &reply, command, failReason);
    Log::Write(Log::LT_NOTICE, MANAGEMENT_PACKET_FILE, 256, L"[%s], %s; sent retry ready post list load failure ack",
               MODULE_NAME, FUNC);
    Log::Write(Log::LT_DEBUG, MANAGEMENT_PACKET_FILE, 258, L"[%s], %s; <END PACKET HANDLER>", MODULE_NAME,
               FUNC);
    return true;
}
