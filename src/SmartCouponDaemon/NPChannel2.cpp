// NPChannel.obj (..\Shared\NPChannel2.cpp) of the SmartCouponDaemon PDB.
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <new>
#include "NPChannel.h"
#include "AlertSender.h"
#include "Connection.h"
#include "CrashHandler.h"
#include "Daemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "Packet.h"
#include "PacketBuffer.h"
#include "Session.h"

using namespace StsMsgLib;

static wchar_t const NPCHANNEL_FILE[] = L"..\\Shared\\NPChannel2.cpp";
static wchar_t const SESSION_FILE[] = L"source\\Session.cpp";
static wchar_t const CHANNEL_H_FILE[] =
    L"E:\\DailyBuild02\\SmartCouponDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";

NPSessionHandler* NPChannel::_sessionHandler = nullptr;
HINSTANCE__* NPChannel::_module = nullptr;
int NPChannel::_programId = -1;  // .data rva 0x83250
wchar_t NPChannel::_gameCode[9] = {0};
IStsMsg* (*NPChannel::_stsCreate)() = nullptr;
void (*NPChannel::_stsCleanUp)(IStsMsg*) = nullptr;
bool NPChannel::_recvCompletionLog = false;  // .bss rva 0x84AF0

unsigned int NPPing::_class = 0;
unsigned long long NPPing::_id = 0;
long NPPing::_interval = 0;

// ❓ Thread-local buffers of the original (TLS area).
static __declspec(thread) unsigned char t_buildBuffer[64000];
static __declspec(thread) char t_addressBuffer[32];

// LIFT: Packet has no constructor. The original sets these fields inline.
static void zeroPacket(Packet* packet)
{
    packet->Splitter = nullptr;
    packet->IsFragmentPacket = false;
    packet->FragmentPacketCmd = 0;
    packet->CurHeader = nullptr;
    packet->ListHead = nullptr;
    packet->ListTail = nullptr;
}

// LIFT: Inlined Session::GetChannel with the add-ref (Session.cpp line 1051).
static Channel* acquireChannel(Session const* session)
{
    Channel* channel = session->_channel;
    if (channel != nullptr && !session->_waitForRelease)
    {
        channel->addReferenceCount(SESSION_FILE, 1051);
        return channel;
    }
    return nullptr;
}

static NPChannel* ownerOf(Channel* channel)  // LIFT: lift helper name, not in any PDB
{
    return static_cast<NPChannel*>(static_cast<SharedChannel::RawChannel*>(channel)->_owner);
}

// 0x4350
bool STSMSGLIB_CHECK_DLL_VERSION(HINSTANCE__* module)
{
    wchar_t path[260];
    if (GetModuleFileNameW(module, path, 260) == 260)
        return false;
    DWORD handle = 0;
    DWORD size = GetFileVersionInfoSizeW(path, &handle);
    if (size == 0 || size > 0x1000)
        return false;
    unsigned char data[4096];
    if (!GetFileVersionInfoW(path, 0, size, data))
        return false;
    VS_FIXEDFILEINFO* info = nullptr;
    UINT len = 0;
    if (!VerQueryValueW(data, L"\\", reinterpret_cast<void**>(&info), &len))
        return false;
    return HIWORD(info->dwFileVersionMS) == 0 && LOWORD(info->dwFileVersionMS) >= 0x77;
}

// 0x4440
ECommand _StsMsgRequest::GetCommand() { return msgInfo.eCmd; }

// 0x4450
unsigned int _StsMsgRequest::GetTransactionId() { return msgInfo.nTxnId; }

// 0x4460
EMessageType _StsMsgRequest::GetMessageType() { return msgInfo.msgType; }

// 0x4470
unsigned int NPPing::TimerClass() const { return _class; }

// 0x4480
unsigned long long NPPing::TimerId() const { return _id; }

// 0x4490
bool NPPing::HandleEvent(EventContext*, unsigned long)
{
    if (_run)
    {
        _StsMsgRequestPing msg;
        msg.msgInfo.eCmd = COMMAND_PING;
        msg.msgInfo.msgType = MESSAGE_TYPE_REQUEST;
        msg.msgInfo.nTxnId = 0;
        _owner->SendMsg(&msg, false, nullptr);
        Daemon::Instance->AddTimer(_interval, this);
    }
    return true;
}

// 0x4500
NPTransactionRegistry::NPTransactionRegistry(CmdDispatcher cmdDispatcher) : _cmdDispatcher(cmdDispatcher), _seed(0)
{
    // ❓ The binary stores the constant NPServiceChannelCmdDispatcher, not the argument.
}

// 0x4580
bool NPTransactionRegistry::Find(unsigned int id, Item* item)
{
    bool result = false;
    _lock.Enter();
    auto it = _dict.find(id);
    if (it != _dict.end() && item != nullptr)
    {
        if (it->second == nullptr)
        {
            Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 112, L"== CRASH == ASSERT CRASH");
            AlertSender::Write(NPCHANNEL_FILE, 112, L"== CRASH == ASSERT CRASH");
            CrashHandler::MakeCrash("..\\Shared\\NPChannel2.cpp", 112, L"");
        }
        *item = *it->second;
        result = true;
    }
    _lock.Leave();
    return result;
}

// 0x4690
bool NPTransactionRegistry::Register(ECommand cmd, void* context, unsigned int* id)
{
    unsigned int txnId;
    while ((txnId = static_cast<unsigned int>(InterlockedIncrement(reinterpret_cast<LONG volatile*>(&_seed)))) == 0)
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 211, L"[np], txn-id overflow");

    Item* item = static_cast<Item*>(Memory::_Manager[2]->Alloc(sizeof(Item), NPCHANNEL_FILE, 134));
    item->cmd = cmd;
    item->context = context;

    _lock.Enter();
    bool inserted = _dict.insert(std::make_pair(txnId, item)).second;
    _lock.Leave();

    if (inserted)
    {
        *id = txnId;
        return true;
    }
    Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 147, L"[np], register txn-id fail; duplicated, txn-id:%u", txnId);
    Memory::_Manager[2]->Free(item, NPCHANNEL_FILE, 148);
    return false;
}

// 0x47D0
void* NPTransactionRegistry::Release(unsigned int id)
{
    Item* item = nullptr;
    _lock.Enter();
    auto it = _dict.find(id);
    if (it != _dict.end())
    {
        item = it->second;
        _dict.erase(it);
    }
    _lock.Leave();
    if (item == nullptr)
        return nullptr;
    void* context = item->context;
    Memory::_Manager[2]->Free(item, NPCHANNEL_FILE, 175);
    return context;
}

// 0x48B0
void NPTransactionRegistry::ReleaseAll(std::vector<void*, StlAllocator<void*, 2> >* e)
{
    _lock.Enter();
    for (auto it = _dict.begin(); it != _dict.end(); ++it)
    {
        if (it->second != nullptr)
        {
            e->push_back(it->second->context);
            Memory::_Manager[2]->Free(it->second, NPCHANNEL_FILE, 191);
        }
    }
    _dict.clear();
    _lock.Leave();
}

// 0x4A60
bool NPSessionHandler::OnAccept(Session const* session) const
{
    Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 235,
               L"== CRASH == [np-session-handler], accept not allowed, session-id:0x%016I64X", session->_id);
    AlertSender::Write(NPCHANNEL_FILE, 235,
                       L"== CRASH == [np-session-handler], accept not allowed, session-id:0x%016I64X", session->_id);
    return false;
}

// 0x4AD0
bool NPSessionHandler::OnConnect(Session const* session, bool firstConnected) const
{
    bool result = false;
    _connlock.Enter();
    Channel* channel = acquireChannel(session);
    _connlock.Leave();
    if (channel != nullptr)
    {
        NPChannel* owner = ownerOf(channel);
        if (owner != nullptr)
            result = owner->onConnect(session, firstConnected);
    }
    Log::Write(Log::LT_DEBUG, NPCHANNEL_FILE, 252, L"[np-session-handler], connected, session-id:0x%016I64X",
               session->_id);
    if (channel != nullptr)
        channel->removeReferenceCount(SESSION_FILE, 1059);
    return result;
}

// 0x4BC0
void NPSessionHandler::OnClose(Session const* session, bool tryReconnect) const
{
    Channel* channel = acquireChannel(session);
    if (channel != nullptr)
    {
        NPChannel* owner = ownerOf(channel);
        if (owner != nullptr)
        {
            Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 623, L"[np], session-closed, disconnected to np game gateway");
            if (!tryReconnect && owner->_ping != nullptr)
                owner->_ping->_run = false;
            if (owner->_handler != nullptr)
                owner->_handler->OnClose(owner, tryReconnect);
        }
        channel->removeReferenceCount(SESSION_FILE, 1059);
    }
    Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 266, L"[np-session-handler], closed, session-id:0x%016I64X",
               session->_id);
}

// 0x4CC0
bool NPSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    Channel* channel = acquireChannel(session);
    if (channel != nullptr)
    {
        NPChannel* owner = ownerOf(channel);
        if (owner != nullptr)
            owner->handlePacket(packet);
        channel->removeReferenceCount(SESSION_FILE, 1059);
    }
    return true;
}

// 0x4D40
bool NPChannel::Setup(int programId, wchar_t const* gameCode)
{
    if (programId == 0)
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 305,
                   L"[np], setup np channel fail; invalid program id, program-id:%d", programId);
        return false;
    }
    _module = LoadLibraryW(L"StsMsgSrv64.dll");
    if (_module == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 311, L"[np], setup np channel failed; load dll failed");
        return false;
    }
    if (!STSMSGLIB_CHECK_DLL_VERSION(_module))
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 316,
                   L"[np], setup np channel failed; check dll version failed, required:%d.%d.%d.0", 0, 119, 0);
        return false;
    }
    _programId = programId;
    wcscpy_s(_gameCode, 9, gameCode);
    _stsCreate = reinterpret_cast<IStsMsg* (*)()>(GetProcAddress(_module, "CreateStsMsg"));
    _stsCleanUp =
        reinterpret_cast<void (*)(IStsMsg*)>(GetProcAddress(_module, "CleanUpStsMsg"));
    if (_stsCreate == nullptr || _stsCleanUp == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 326,
                   L"[np], setup np channel failed; initialize sts message function failed");
        return false;
    }
    void* mem = Memory::_Manager[2]->Alloc(sizeof(NPSessionHandler), NPCHANNEL_FILE, 330);
    _sessionHandler = mem ? new (mem) NPSessionHandler() : nullptr;
    NPPing::_class = 1;
    NPPing::_id = 1;
    NPPing::_interval = 30000;
    Log::Write(Log::LT_NOTICE, NPCHANNEL_FILE, 336, L"[np], setup np channel success");
    return true;
}

// 0x4F50
void NPChannel::Cleanup()
{
    if (_sessionHandler != nullptr)
    {
        _sessionHandler->~NPSessionHandler();
        Memory::_Manager[2]->Free(_sessionHandler, NPCHANNEL_FILE, 344);
        _sessionHandler = nullptr;
    }
    if (_module != nullptr)
    {
        FreeLibrary(_module);
        _programId = -1;
        _gameCode[0] = 0;
        _module = nullptr;
        _stsCreate = nullptr;
        _stsCleanUp = nullptr;
    }
}

// 0x5000
NPChannel::~NPChannel()
{
    if (_ping != nullptr)
    {
        _ping->removeReferenceCount(NPCHANNEL_FILE, 369);
        _ping = nullptr;
    }
    if (_tranRegistry != nullptr)
    {
        _tranRegistry->~NPTransactionRegistry();
        Memory::_Manager[2]->Free(_tranRegistry, NPCHANNEL_FILE, 374);
        _tranRegistry = nullptr;
    }
    if (_sts != nullptr)
    {
        _stsCleanUp(_sts);
        _sts = nullptr;
    }
}

// 0x5120
bool NPChannel::Initialize(NPMessageHandler* handler, NPTransactionRegistry::CmdDispatcher cmdDispatcher)
{
    if (handler == nullptr || cmdDispatcher == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 385,
                   L"== CRASH == [np], intialize fail; invalid parameter, message-handler:%p, command-dispatcher:%p",
                   handler, cmdDispatcher);
        AlertSender::Write(NPCHANNEL_FILE, 385,
                           L"== CRASH == [np], intialize fail; invalid parameter, message-handler:%p, "
                           L"command-dispatcher:%p",
                           handler, cmdDispatcher);
        return false;
    }
    if (_sts != nullptr)
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 390, L"== CRASH == [np], initialize fail; already initialized");
        AlertSender::Write(NPCHANNEL_FILE, 390, L"== CRASH == [np], initialize fail; already initialized");
        return false;
    }
    _sts = _stsCreate();
    if (_sts == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 396, L"[np], connect fail; sts interface not ready");
        return false;
    }
    _handler = handler;
    void* mem = Memory::_Manager[2]->Alloc(sizeof(NPTransactionRegistry), NPCHANNEL_FILE, 401);
    _tranRegistry = mem ? new (mem) NPTransactionRegistry(cmdDispatcher) : nullptr;
    if (NPPing::_interval > 0)
    {
        mem = Memory::_Manager[2]->Alloc(sizeof(NPPing), NPCHANNEL_FILE, 404);
        _ping = mem ? new (mem) NPPing(this) : nullptr;
    }
    Log::Write(Log::LT_DEBUG, NPCHANNEL_FILE, 406, L"[np], initialize ok");
    return true;
}

// 0x5300
bool NPChannel::Connect(unsigned long long id, unsigned int portId, unsigned long ip, unsigned short portNo,
                        long timeout, bool reconnect)
{
    _sessionHandler->_connlock.Enter();
    bool result = SharedChannel::Connect(id, portId, ip, portNo, timeout, reconnect);
    _sessionHandler->_connlock.Leave();
    if (result)
        Log::Write(Log::LT_DEBUG, NPCHANNEL_FILE, 420, L"[np], try connect success");
    else
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 422, L"[np], try connect fail");
    return result;
}

// 0x53D0
bool NPChannel::SendMsg(_StsMsg* msg, bool response, void* context)
{
    if (msg == nullptr)
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 430, L"== CRASH == [np], try to send null message");
        AlertSender::Write(NPCHANNEL_FILE, 430, L"== CRASH == [np], try to send null message");
        return false;
    }
    if (!IsConnected())
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 435, L"[np], send fail; not connected session");
        return false;
    }
    if (response && msg->GetMessageType() == MESSAGE_TYPE_REQUEST &&
        !_tranRegistry->Register(msg->GetCommand(), context, &static_cast<_StsMsgRequest*>(msg)->msgInfo.nTxnId))
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 442, L"== CRASH == [np], register transaction failed");
        AlertSender::Write(NPCHANNEL_FILE, 442, L"== CRASH == [np], register transaction failed");
        return false;
    }

    _StsMsgBuffer buffer;
    buffer.pData = t_buildBuffer;
    buffer.nLen = sizeof(t_buildBuffer);
    EStsMsgError err = _sts->Build(msg, &buffer);
    if (err == 1)
    {
        Packet p;
        zeroPacket(&p);
        unsigned char const* data = buffer.pData;
        unsigned int remain = buffer.nLen;
        do
        {
            PacketBuffer* prev = p.ListTail;
            PacketBuffer* pb = PacketBufferAllocator::_Local->allocate();
            if (p.ListHead == nullptr)
                p.ListHead = pb;
            else
                prev->Next = pb;
            p.ListTail = pb;
            p.CurHeader = reinterpret_cast<Packet::Header*>(&pb->Buffer[8]);
            p.CurHeader->size = 2;
            unsigned int n = remain < 3998 ? remain : 3998;
            if (static_cast<short>(n) > 0)
            {
                memcpy(reinterpret_cast<char*>(p.CurHeader) + p.CurHeader->size, data, n);
                p.CurHeader->size = static_cast<short>(p.CurHeader->size + n);
            }
            data += n;
            remain -= n;
        } while (remain != 0);

        if (_rawChannel != nullptr)
        {
            Session* s = const_cast<Session*>(_rawChannel->GetSession());
            if (s != nullptr)
            {
                s->_lock.Enter();
                bool connected = s->_state == Session::CONNECTED && s->_connection->_socket != INVALID_SOCKET;
                s->_lock.Leave();
                // BUG: 0x53D0 the session reference leaks when the session is not connected.
                if (connected)
                {
                    PacketBuffer const* head = p.ListHead;
                    p.ListHead->encrypt(s->_currentCrypt, s->_security3rd);
                    s->_lock.Enter();
                    s->send(&head, 1);  // LIFT: inlined send
                    s->_lock.Leave();
                    s->removeReferenceCount(CHANNEL_H_FILE, 52);
                }
            }
        }
        Log::Write(Log::LT_DEBUG, NPCHANNEL_FILE, 472, L"[np], sts msg sent, np-tid:%d, cmd:%d, type:%d",
                   msg->GetTransactionId(), msg->GetCommand(), msg->GetMessageType());
        p.Clear();
    }
    else
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 476, L"[np], build sts msg failed, error-code:%d", err);
        if (!checkLibError(err))
        {
            Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 480,
                       L"== CRASH == [np], critical sts msg lib error occurs, error-code:%d", err);
            AlertSender::Write(NPCHANNEL_FILE, 480,
                               L"== CRASH == [np], critical sts msg lib error occurs, error-code:%d", err);
        }
    }
    return true;
}

// 0x57D0
bool NPChannel::handlePacket(Packet const* packet)
{
    unsigned char const* body = reinterpret_cast<unsigned char const*>(&packet->CurHeader[1]);
    unsigned short bodySize = static_cast<unsigned short>(packet->CurHeader->size - 2);
    if (_recvCompletionLog)
    {
        static wchar_t const hex[] = L"0123456789ABCDEF";
        wchar_t temp[304];
        int k = 0;
        for (unsigned int i = 0; i < bodySize && k < 300; ++i, k += 3)
        {
            temp[k] = hex[body[i] >> 4];
            temp[k + 1] = hex[body[i] & 0xF];
            temp[k + 2] = L' ';
        }
        temp[k] = 0;
        Log::Write(Log::LT_DEBUG, NPCHANNEL_FILE, 516, L"[np], recvd, size:%d, body:%s", bodySize, temp);
    }
    _sts->WriteReceiveData(const_cast<unsigned char*>(body), bodySize);

    _StsMsg* msg = nullptr;
    EStsMsgError err;
    while ((err = _sts->Parse(&msg, reinterpret_cast<void*>(_tranRegistry->_cmdDispatcher))) != 0)
    {
        if (err != 1)
        {
            Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 542, L"[np], parse failed, error:%d", err);
            continue;
        }
        if (msg == nullptr)
            continue;
        ECommand cmd = msg->GetCommand();
        unsigned int txn = msg->GetTransactionId();
        EMessageType type = msg->GetMessageType();
        Log::Write(Log::LT_DEBUG, NPCHANNEL_FILE, 553, L"[np], sts msg received, np-tid:%u, cmd:%d, type:%d", txn,
                   cmd, type);
        void* context = nullptr;
        if (type == 2)
        {
            if (static_cast<_StsMsgResponse*>(msg)->msgInfo.bComplete)
            {
                context = _tranRegistry->Release(txn);
            }
            else
            {
                NPTransactionRegistry::Item item;
                if (!_tranRegistry->Find(txn, &item))
                {
                    Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 567,
                               L"== CRASH == [np], handle sts msg failed; not registered response msg; txn id not "
                               L"found, np-tid:%u, cmd:%d, type:%d",
                               txn, cmd, 2);
                    AlertSender::Write(NPCHANNEL_FILE, 567,
                                       L"== CRASH == [np], handle sts msg failed; not registered response msg; txn id "
                                       L"not found, np-tid:%u, cmd:%d, type:%d",
                                       txn, cmd, 2);
                    _sts->ReleaseStsMsg(msg);
                    continue;
                }
                context = item.context;
            }
        }
        if (!_handler->HandleMessage(this, msg, context))
            Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 578, L"[np], handle sts msg failed, np-tid:%u, cmd:%d, type:%d",
                       txn, cmd, type);
    }
    return true;
}

// 0x5AD0
bool NPChannel::onConnect(Session const* session, bool firstConnected)
{
    Log::Write(Log::LT_DEBUG, NPCHANNEL_FILE, 592, L"[np], connected to np game gateway");
    char gameCodeA[16];
    gameCodeA[7] = 0;
    gameCodeA[8] = 0;
    WideCharToMultiByte(0, 0, _gameCode, -1, gameCodeA, 8, nullptr, nullptr);
    if (_sts->Initialize(_programId, gameCodeA) == 0)
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 598, L"[np], onConnect failed; initialize sts interface failed");
        return false;
    }
    if (!sendInitialConnectMessage(session))
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 603, L"[np], send initial connect message fail");
        return false;
    }
    if (firstConnected && _ping != nullptr && !_ping->_run)
    {
        _ping->_run = true;
        Daemon::Instance->AddTimer(NPPing::_interval, _ping);
    }
    if (_handler != nullptr && !_handler->OnConnect(this, firstConnected))
    {
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 613, L"[np], handle on connect fail");
        return false;
    }
    Log::Write(Log::LT_DEBUG, NPCHANNEL_FILE, 617, L"[np], np channel connected");
    return true;
}

// 0x5C40
bool NPChannel::sendInitialConnectMessage(Session const* session)
{
    char localIP[17] = {0};
    t_addressBuffer[0] = 0;
    in_addr addr;
    addr.s_addr = session->_connection->GetLocalAddress();
    char const* text = inet_ntoa(addr);
    if (text != nullptr)
        strcpy_s(t_addressBuffer, sizeof(t_addressBuffer), text);
    strcpy_s(localIP, sizeof(localIP), t_addressBuffer);

    _StsMsgRequestInitialConnect msg;
    msg.msgInfo.eCmd = COMMAND_INITIAL_CONNECT;
    msg.msgInfo.msgType = MESSAGE_TYPE_REQUEST;
    msg.msgInfo.nTxnId = 0;
    msg.pszIpAddress = localIP;
    Log::Write(Log::LT_DEBUG, NPCHANNEL_FILE, 642, L"[np], send initial connect message, local-ip:%s",
               Network::GetAddressStringW(session->_connection->GetLocalAddress()));
    return SendMsg(&msg, false, nullptr);
}

// 0x5D50
bool NPChannel::checkLibError(EStsMsgError err)
{
    switch (err)
    {
    case 2:
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 663, L"[np], STS_MSG_ERROR_FAIL");
        break;
    case 3:
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 666, L"[np], STS_MSG_ERROR_WRONG_GAME_CODE");
        break;
    case 4:
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 669, L"[np], STS_MSG_ERROR_WRONG_PARAMETERS");
        break;
    case 5:
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 672, L"[np], STS_MSG_ERROR_BUFFER_SIZE_IS_NOT_ENOUGH");
        break;
    case 6:
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 675, L"[np], STS_MSG_ERROR_WRONG_MESSAGE_BODY");
        return false;
    case 7:
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 679, L"[np], STS_MSG_ERROR_ALLOC_FAILED");
        break;
    case 8:
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 682, L"[np], STS_MSG_ERROR_WRONG_KEY_DATA");
        return false;
    case 9:
        Log::Write(Log::LT_ERROR, NPCHANNEL_FILE, 686, L"[np], STS_MSG_ERROR_WRONG_COMMAND");
        break;
    default:
        break;
    }
    return true;
}
