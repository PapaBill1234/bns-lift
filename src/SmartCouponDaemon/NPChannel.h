// NPChannel.obj (..\Shared\NPChannel2.cpp), NPServiceChannel.obj and NPMessageHandler.obj (SmartCouponDaemon PDB).
// Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>

struct HINSTANCE__;
#include <map>
#include <vector>
#include "SharedChannel.h"
#include "Channel.h"
#include "Lock.h"
#include "StlMemory.h"
#include "TimerQueue.h"

class NPChannel;
class NPPing;
class NPTransactionRegistry;
class NPTransaction;
class SessionHandler;
class Session;
class Packet;

class CouponJob;
union id128;

namespace StsMsgLib
{
typedef int ECommand;      // ❓ PDB enum StsMsgLib::ECommand
typedef int EMessageType;  // ❓ PDB enum StsMsgLib::EMessageType (1 = MESSAGE_TYPE_REQUEST, 2 = response)
typedef int EStsMsgError;  // ❓ PDB enum StsMsgLib::EStsMsgError (0 = STS_MSG_ERROR_NONE, 1 = STS_MSG_ERROR_SUCCESS)

struct _StsMsg
{
    virtual ECommand GetCommand() = 0;            // slot 0
    virtual unsigned int GetTransactionId() = 0;  // slot 1
    virtual EMessageType GetMessageType() = 0;    // slot 2
};
static_assert(sizeof(_StsMsg) == 0x8, "sizeof StsMsgLib::_StsMsg");

struct _StsMsgBuffer
{
    unsigned char* pData;
    unsigned int nLen;
};

// The interface that StsMsgSrv64.dll gives (CreateStsMsg).
class IStsMsg
{
public:
    virtual int Initialize(int programId, char const* gameCode) = 0;            // slot 0
    virtual EStsMsgError Build(_StsMsg* msg, _StsMsgBuffer* buffer) = 0;        // slot 1
    virtual void WriteReceiveData(unsigned char* data, unsigned int len) = 0;   // slot 2
    virtual EStsMsgError Parse(_StsMsg** msg, void* cmdDispatcher) = 0;         // slot 3
    virtual void ReleaseStsMsg(_StsMsg* msg) = 0;                               // slot 4
    virtual int SetCryptFilterWhenUsingExternalAuth() = 0;                      // slot 5 ❓ signature
};

struct _StsMsgInfo
{
    ECommand eCmd;
    EMessageType msgType;
};
static_assert(sizeof(_StsMsgInfo) == 0x8, "sizeof StsMsgLib::_StsMsgInfo");

struct _StsMsgInfoRequest : public _StsMsgInfo
{
    unsigned int nTxnId;
};

struct _StsMsgRequest : public _StsMsg
{
    virtual ECommand GetCommand();            // 0x4440
    virtual unsigned int GetTransactionId();  // 0x4450
    virtual EMessageType GetMessageType();    // 0x4460

    _StsMsgInfoRequest msgInfo;
};
static_assert(sizeof(_StsMsgRequest) == 0x18, "sizeof StsMsgLib::_StsMsgRequest");
static_assert(offsetof(_StsMsgRequest, msgInfo.nTxnId) == 0x10, "_StsMsgRequest nTxnId");

struct _StsMsgRequestPing : public _StsMsgRequest
{
};

struct _StsMsgRequestInitialConnect : public _StsMsgRequest
{
    char* pszIpAddress;
};

struct _StsMsgRequestRewardBrokerEventNoti : public _StsMsgRequest
{
    void* pUserId;
    int nNotiType;
    int nEventId;
    long long nRequestKey;
    wchar_t* pwszRequestDesc;
};
static_assert(offsetof(_StsMsgRequestRewardBrokerEventNoti, nRequestKey) == 0x28, "nRequestKey");

struct _StsMsgRequestRewardRequestRewardForEvent : public _StsMsgRequest
{
    void* pUserId;
    char* pszEventId;
    short nRequestFromCode;
    char* pszRequestKey;
};

struct _StsMsgErrInfo
{
    char const* pszErr;
    unsigned int nStatusCode;
    wchar_t const* pwszReason;
    int nErrorCode;
    unsigned char banInfo[0x28];  // ❓ PDB type of banInfo
};
static_assert(sizeof(_StsMsgErrInfo) == 0x48, "sizeof StsMsgLib::_StsMsgErrInfo");

struct _StsMsgInfoResponse : public _StsMsgInfo
{
    unsigned int nTxnId;
    bool bComplete;
    _StsMsgErrInfo errInfo;
};
static_assert(sizeof(_StsMsgInfoResponse) == 0x58, "sizeof StsMsgLib::_StsMsgInfoResponse");

struct _StsMsgResponse : public _StsMsg
{
    _StsMsgInfoResponse msgInfo;
};
static_assert(sizeof(_StsMsgResponse) == 0x60, "sizeof StsMsgLib::_StsMsgResponse");
static_assert(offsetof(_StsMsgResponse, msgInfo.bComplete) == 0x14, "bComplete");
static_assert(offsetof(_StsMsgResponse, msgInfo.errInfo.nStatusCode) == 0x20, "nStatusCode");
static_assert(offsetof(_StsMsgResponse, msgInfo.errInfo.pwszReason) == 0x28, "pwszReason");
static_assert(offsetof(_StsMsgResponse, msgInfo.errInfo.nErrorCode) == 0x30, "nErrorCode");

struct _StsMsgResponseRewardBrokerEventNoti : public _StsMsgResponse
{
    wchar_t* pwszAcceptTid;
};
static_assert(sizeof(_StsMsgResponseRewardBrokerEventNoti) == 0x68, "sizeof _StsMsgResponseRewardBrokerEventNoti");
}  // namespace StsMsgLib

bool STSMSGLIB_CHECK_DLL_VERSION(HINSTANCE__* module);  // 0x4350

class NPMessageHandler
{
public:
    virtual bool OnConnect(NPChannel*, bool) const = 0;                               // slot 0
    virtual bool OnClose(NPChannel*, bool) const = 0;                                 // slot 1
    virtual bool HandleMessage(NPChannel*, StsMsgLib::_StsMsg*, void*) const = 0;     // slot 2
};
static_assert(sizeof(NPMessageHandler) == 0x8, "sizeof NPMessageHandler");

class NPSessionHandler : public SessionHandler
{
public:
    virtual bool OnAccept(Session const* session) const;                          // 0x4A60
    virtual bool OnConnect(Session const* session, bool firstConnected) const;    // 0x4AD0
    virtual void OnClose(Session const* session, bool tryReconnect) const;        // 0x4BC0
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x4CC0

    mutable CriticalSection _connlock;
};
static_assert(sizeof(NPSessionHandler) == 48, "sizeof NPSessionHandler");

class NPPing : public Timer
{
public:
    // ❓ Inlined in NPChannel::Initialize (0x5120).
    explicit NPPing(NPChannel* owner) : _owner(owner), _run(false)
    {
        StartTick = 0;
        InLtq = false;
        prev = nullptr;
        next = nullptr;
        SlotIndex = -1;
    }
    virtual unsigned int TimerClass() const;                        // 0x4470
    virtual unsigned long long TimerId() const;                     // 0x4480
    virtual bool HandleEvent(EventContext* ctx, unsigned long);     // 0x4490

    static unsigned int _class;        // rva 0x84AC0
    static unsigned long long _id;     // rva 0x84AC8
    static long _interval;             // rva 0x84AC4

    NPChannel* _owner;
    bool _run;
};
static_assert(sizeof(NPPing) == 72, "sizeof NPPing");

class NPTransactionRegistry
{
public:
    struct Item
    {
        StsMsgLib::ECommand cmd;
        void* context;
    };
    typedef void (*CmdDispatcher)(unsigned int, StsMsgLib::ECommand*);  // ❓ typedef name

    explicit NPTransactionRegistry(CmdDispatcher cmdDispatcher);  // 0x4500
    bool Find(unsigned int id, Item* item);                         // 0x4580
    bool Register(StsMsgLib::ECommand cmd, void* context, unsigned int* id);  // 0x4690
    void* Release(unsigned int id);                                 // 0x47D0
    // ❓ The PDB type is std::vector<Timer*,StlAllocator<Timer*,2>>* (COMDAT folding). The code stores void*.
    void ReleaseAll(std::vector<void*, StlAllocator<void*, 2> >* e);  // 0x48B0

    CmdDispatcher _cmdDispatcher;
    unsigned int volatile _seed;
    std::map<unsigned int, Item*, std::less<unsigned int>, StlAllocator<std::pair<unsigned int const, Item*>, 2> > _dict;
    CriticalSection _lock;
};
static_assert(sizeof(NPTransactionRegistry) == 0x58, "sizeof NPTransactionRegistry");

class NPTransaction
{
public:
    virtual ~NPTransaction() {}
    virtual int GetKind() const = 0;
    virtual void Expire() = 0;
};

class NPJobTransaction : public NPTransaction
{
public:
    NPJobTransaction() : _jobid(0), _state(-1), _task(0) {}  // ❓ inlined in SendRequestEventNoti (0xFF10)
    virtual ~NPJobTransaction() {}
    virtual int GetKind() const { return 1; }  // 0x231F0
    virtual void Expire();                     // 0xFE70

    unsigned long long _jobid;
    int _state;
    int _task;
};
static_assert(sizeof(NPJobTransaction) == 24, "sizeof NPJobTransaction");

class NPChannel : public SharedChannel
{
public:
    NPChannel() : _sts(nullptr), _handler(nullptr), _tranRegistry(nullptr), _ping(nullptr) {}  // ❓ inlined
    virtual ~NPChannel();  // 0x5000
    virtual bool Connect(unsigned long long id, unsigned int portId, unsigned long ip, unsigned short portNo,
                         long timeout, bool reconnect);  // 0x5300

    static bool Setup(int programId, wchar_t const* gameCode);  // 0x4D40
    static void Cleanup();                                      // 0x4F50

    bool Initialize(NPMessageHandler* handler, NPTransactionRegistry::CmdDispatcher cmdDispatcher);  // 0x5120
    bool SendMsg(StsMsgLib::_StsMsg* msg, bool response, void* context);  // 0x53D0
    bool handlePacket(Packet const* packet);                                // 0x57D0
    bool onConnect(Session const* session, bool firstConnected);           // 0x5AD0
    bool sendInitialConnectMessage(Session const* session);                // 0x5C40
    static bool checkLibError(StsMsgLib::EStsMsgError err);                // 0x5D50

    static NPSessionHandler* _sessionHandler;
    static HINSTANCE__* _module;
    static int _programId;
    static wchar_t _gameCode[9];
    static StsMsgLib::IStsMsg* (*_stsCreate)();
    static void (*_stsCleanUp)(StsMsgLib::IStsMsg*);
    static bool _recvCompletionLog;

    StsMsgLib::IStsMsg* _sts;
    NPMessageHandler* _handler;
    NPTransactionRegistry* _tranRegistry;
    NPPing* _ping;
};
static_assert(sizeof(NPChannel) == 0x40, "sizeof NPChannel");

class NPServiceChannel : public NPChannel
{
public:
    NPServiceChannel() {}            // ❓ inlined in NPServiceChannelManager::Initialize (0x10340)
    virtual ~NPServiceChannel() {}   // 0xFD50 (scalar deleting destructor only)

    bool SendRequestEventNoti(CouponJob* job, id128 const* gameAccountId, int couponEventId,
                              long long publicationId);  // 0xFF10
};
static_assert(sizeof(NPServiceChannel) == 0x40, "sizeof NPServiceChannel");

class NPMsgHandleEvent : public DynamicEventObject
{
public:
    typedef bool (*Handler)(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);  // ❓ typedef name

    // ❓ Inlined in NPServiceChannelManager::HandleMessage (0x10700).
    NPMsgHandleEvent(NPChannel* channel, StsMsgLib::_StsMsg* msg, NPTransaction* tran, Handler handler)
        : _channel(channel), _msg(msg), _tran(tran), _handler(handler)
    {
    }
    virtual ~NPMsgHandleEvent();                                   // 0x10230
    virtual unsigned int EventId() const { return 0; }             // ❓ value
    virtual bool HandleEvent(EventContext* ctx, unsigned long);    // 0x102C0

    NPChannel* _channel;
    StsMsgLib::_StsMsg* _msg;
    NPTransaction* _tran;
    Handler _handler;
};
static_assert(sizeof(NPMsgHandleEvent) == 56, "sizeof NPMsgHandleEvent");

class NPServiceChannelManager : public NPMessageHandler
{
public:
    // ❓ Inlined in SmartCouponDaemon::initialize (0x150E0).
    NPServiceChannelManager() : _init(false), _npServChannel(nullptr) {}
    virtual bool OnConnect(NPChannel*, bool) const;                                  // 0x104A0
    virtual bool OnClose(NPChannel*, bool) const;                                    // 0x10560
    virtual bool HandleMessage(NPChannel*, StsMsgLib::_StsMsg*, void*) const;        // 0x10700

    bool Initialize(unsigned int portId, unsigned long ip, unsigned short portNo, long timeout);  // 0x10340

    bool _init;
    NPServiceChannel* _npServChannel;
};
static_assert(sizeof(NPServiceChannelManager) == 0x18, "sizeof NPServiceChannelManager");

void NPServiceChannelCmdDispatcher(unsigned int id, StsMsgLib::ECommand* eCmd);           // 0xFD80
bool NPHandlerEventNoti(NPChannel* channel, StsMsgLib::_StsMsg* msg, NPTransaction* tran);  // 0xFBC0
