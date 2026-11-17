// NPServiceChannel.obj of the SmartCouponDaemon PDB.
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <new>
#include "NPChannel.h"
#include "AlertSender.h"
#include "CouponJob.h"
#include "Daemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "PipeConsole.h"
#include "SmartCouponDaemon.h"
#include "StringUtil.h"

using namespace StsMsgLib;

static wchar_t const NPSERVICECHANNEL_FILE[] = L"NPServiceChannel.cpp";
static wchar_t const NPMESSAGEHANDLER_FILE[] = L"NPMessageHandler.cpp";

// 0xFD80
void NPServiceChannelCmdDispatcher(unsigned int id, ECommand* eCmd)
{
    NPServiceChannel* channel = SmartCouponDaemon::_instance->_npChannelMgr->_npServChannel;
    if (channel == nullptr)  // LIFT: 0xfda1 tests only the channel
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 22,
                   L"[np], [np-game-service-channel], dispatch command fail; no channel exists, txn-id:%u", id);
        return;
    }
    NPTransactionRegistry* registry = channel->_tranRegistry;
    if (registry == nullptr)  // LIFT: 0xfdd0
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 28,
                   L"== CRASH == [np], [np-gameservch-tran-reg], not ready to dispatch command");
        AlertSender::Write(NPSERVICECHANNEL_FILE, 28,
                           L"== CRASH == [np], [np-gameservch-tran-reg], not ready to dispatch command");
        return;
    }
    NPTransactionRegistry::Item item;
    if (registry->Find(id, &item))
        *eCmd = item.cmd;
    else
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 34,
                   L"[np], [np-gameservch-tran-reg], dispatch command fail; not found, txn-id:%u", id);
}

// 0xFE70
void NPJobTransaction::Expire()
{
    Log::Write(Log::LT_DEBUG, NPSERVICECHANNEL_FILE, 59,
               L"[np], np job transaction expired jobid:0x%I64X, state:%d, task:%d", _jobid, _state, _task);
    if (!SmartCouponDaemon::_instance->_jobMgr->ResumeW(_jobid, _state, _task))
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 62,
                   L"[np], expire np job transaction fail; execute job fail, jobid:0x%I64X, state:%d, task:%d", _jobid,
                   _state, _task);
}

// 0xFF10
bool NPServiceChannel::SendRequestEventNoti(CouponJob* job, id128 const* gameAccountId, int couponEventId,
                                            long long publicationId)
{
    auto const& acc = gameAccountId->guid;
    if (job == nullptr)
    {
        Log::Write(Log::LT_DEBUG, NPSERVICECHANNEL_FILE, 85,
                   L"[np], request event noti, job is null, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
                   L"eventid:%d",
                   acc.id1, acc.id2, acc.id3, acc.id4[0], acc.id4[1], acc.id4[2], acc.id4[3], acc.id4[4], acc.id4[5],
                   acc.id4[6], acc.id4[7], couponEventId);
        return false;
    }
    Log::Write(Log::LT_DEBUG, NPSERVICECHANNEL_FILE, 89,
               L"[np], request event noti, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, eventid:%d, "
               L"publicationid:%I64d",
               acc.id1, acc.id2, acc.id3, acc.id4[0], acc.id4[1], acc.id4[2], acc.id4[3], acc.id4[4], acc.id4[5],
               acc.id4[6], acc.id4[7], couponEventId, publicationId);

    void* mem;
    NPJobTransaction* tran;
    if (SmartCouponDaemon::_instance->_config->_npRewardChangeoverEnable)
    {
        char strEventId[51] = {0};
        sprintf_s(strEventId, sizeof(strEventId), "%d", couponEventId);
        char strPublicationId[50] = {0};
        sprintf_s(strPublicationId, sizeof(strPublicationId), "%I64d", publicationId);

        _StsMsgRequestRewardRequestRewardForEvent msg;
        msg.msgInfo.eCmd = COMMAND_SRV_REWARD_REQUEST_REWARD_FOR_EVENT;
        msg.msgInfo.msgType = MESSAGE_TYPE_REQUEST;
        msg.msgInfo.nTxnId = 0;
        msg.pUserId = const_cast<id128*>(gameAccountId);
        msg.pszEventId = strEventId;
        msg.nRequestFromCode = 9;
        msg.pszRequestKey = strPublicationId;

        mem = Memory::_Manager[2]->Alloc(sizeof(NPJobTransaction), NPSERVICECHANNEL_FILE, 121);
        // BUG: 0xFF10 the result of Alloc is not checked.
        tran = new (mem) NPJobTransaction();
        tran->_jobid = job->_id;
        tran->_state = job->_state;
        tran->_task = 2;
        return SendMsg(&msg, true, tran);
    }

    _StsMsgRequestRewardBrokerEventNoti msg;
    msg.msgInfo.eCmd = COMMAND_SRV_REWARDBROKER_EVENT_NOTI;
    msg.msgInfo.msgType = MESSAGE_TYPE_REQUEST;
    msg.msgInfo.nTxnId = 0;
    msg.pUserId = const_cast<id128*>(gameAccountId);
    msg.nNotiType = 1;
    msg.nEventId = couponEventId;
    msg.nRequestKey = publicationId;
    msg.pwszRequestDesc = nullptr;

    mem = Memory::_Manager[2]->Alloc(sizeof(NPJobTransaction), NPSERVICECHANNEL_FILE, 99);
    // BUG: 0xFF10 the result of Alloc is not checked.
    tran = new (mem) NPJobTransaction();
    tran->_jobid = job->_id;
    tran->_state = job->_state;
    tran->_task = 2;
    return SendMsg(&msg, true, tran);
}

// 0x10230
NPMsgHandleEvent::~NPMsgHandleEvent()
{
    if (_channel != nullptr)
        _channel->removeReferenceCount(NPSERVICECHANNEL_FILE, 147);
    if (_tran != nullptr)
    {
        _tran->~NPTransaction();
        Memory::_Manager[2]->Free(_tran, NPSERVICECHANNEL_FILE, 149);
        _tran = nullptr;
    }
}

// 0x102C0
bool NPMsgHandleEvent::HandleEvent(EventContext*, unsigned long)
{
    if (_channel != nullptr && _msg != nullptr)
    {
        if (_handler != nullptr)
            _handler(_channel, _msg, _tran);
        _channel->_sts->ReleaseStsMsg(_msg);
    }
    removeReferenceCount(NPSERVICECHANNEL_FILE, 165);
    return true;
}

// 0x10340
bool NPServiceChannelManager::Initialize(unsigned int portId, unsigned long ip, unsigned short portNo, long timeout)
{
    if (_init)
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 195, L"[npchmgr], initialize fail; already initailized");
        return false;
    }
    _init = true;
    void* mem = Memory::_Manager[2]->Alloc(sizeof(NPServiceChannel), NPSERVICECHANNEL_FILE, 201);
    _npServChannel = mem ? new (mem) NPServiceChannel() : nullptr;
    if (!_npServChannel->Initialize(this, NPServiceChannelCmdDispatcher))
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 204,
                   L"[npchmgr], initialize fail; init game-service channel fail");
        return false;
    }
    if (!_npServChannel->Connect(0, portId, ip, portNo, timeout, true))
    {
        Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 209,
                   L"[npchmgr], initialize fail; connect game service channel fail");
        return false;
    }
    Log::Write(Log::LT_DEBUG, NPSERVICECHANNEL_FILE, 213,
               L"[npchmgr], initialize ok, port-id:%d, ip:%s, port:%d, timeout:%d(sec)", portId,
               Network::GetAddressStringW(ip), portNo, timeout);
    return true;
}

// 0x104A0
bool NPServiceChannelManager::OnConnect(NPChannel* channel, bool firstConnected) const
{
    unsigned long long id =
        (channel != nullptr && channel->_rawChannel != nullptr) ? channel->_rawChannel->GetId() : 0;
    Log::Write(Log::LT_NOTICE, NPSERVICECHANNEL_FILE, 230, L"[np], np serivce channel connected, channel-id:%I64d", id);
    void* event = SmartCouponDaemon::_instance->_npInitialConnectEvent.Event;
    if (!firstConnected || (event != nullptr && SetEvent(event)))
    {
        if (Daemon::Instance->pipeConsole != nullptr)
            Daemon::Instance->pipeConsole->SetInvalidInfo(L"NP game-service disconnected", false);
        return true;
    }
    Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 234, L"[np], set np initial connect event fail");
    return false;
}

// 0x10560
bool NPServiceChannelManager::OnClose(NPChannel* channel, bool) const
{
    unsigned long long id =
        (channel != nullptr && channel->_rawChannel != nullptr) ? channel->_rawChannel->GetId() : 0;
    Log::Write(Log::LT_ERROR, NPSERVICECHANNEL_FILE, 249, L"[np], np service channel closed,  channel-id:%I64d", id);
    if (Daemon::Instance->pipeConsole != nullptr)
        Daemon::Instance->pipeConsole->SetInvalidInfo(L"NP game-service disconnected", true);
    if (channel->_tranRegistry != nullptr)
    {
        std::vector<void*, StlAllocator<void*, 2> > expired;
        channel->_tranRegistry->ReleaseAll(&expired);
        for (auto it = expired.begin(); it != expired.end(); ++it)
        {
            NPTransaction* tran = static_cast<NPTransaction*>(*it);
            if (tran != nullptr)
            {
                tran->Expire();
                tran->~NPTransaction();
                Memory::_Manager[2]->Free(tran, NPSERVICECHANNEL_FILE, 265);
            }
        }
    }
    return true;
}

// 0x10700
bool NPServiceChannelManager::HandleMessage(NPChannel* channel, _StsMsg* msg, void* context) const
{
    if (channel == nullptr || msg == nullptr)
        return false;
    ECommand cmd = msg->GetCommand();
    if (cmd < COMMAND_SRV_REWARDBROKER_EVENT_NOTI || cmd > COMMAND_SRV_REWARD_REQUEST_REWARD_FOR_EVENT)
    {
        Log::Write(Log::LT_ERROR, NPMESSAGEHANDLER_FILE, 36, L"[np], DispatchNPMessageHandler, invalid command, cmd:%d",
                   cmd);
        channel->_sts->ReleaseStsMsg(msg);
        return false;
    }
    void* mem = Memory::_Manager[2]->Alloc(sizeof(NPMsgHandleEvent), NPSERVICECHANNEL_FILE, 284);
    NPMsgHandleEvent* ev =
        mem ? new (mem) NPMsgHandleEvent(channel, msg, static_cast<NPTransaction*>(context), NPHandlerEventNoti)
            : nullptr;
    channel->addReferenceCount(NPSERVICECHANNEL_FILE, 141);
    PostQueuedCompletionStatus(Network::iocpHandle(), 0, reinterpret_cast<ULONG_PTR>(ev), nullptr);
    return true;
}
