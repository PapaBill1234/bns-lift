// DaemonChannel.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include <vector>
#include "Channel.h"
#include "Lock.h"
#include "StlMemory.h"

class Session;
class Packet;

struct GameEventDaemonId
{
    unsigned char _type;
    unsigned short _wid;
    unsigned char _reserved;

    // LIFT: inlined. The map compare uses the same key as DChannel::GetId (0x7D30), _reserved included.
    unsigned int Key() const { return ((static_cast<unsigned int>(_type) << 16) + _wid << 8) + _reserved; }  // LIFT: same math as DChannel::GetId 0x7d30
    bool operator<(GameEventDaemonId const& other) const { return Key() < other.Key(); }
};
static_assert(sizeof(GameEventDaemonId) == 0x6, "sizeof GameEventDaemonId");

class DChannel : public Channel
{
public:
    // LIFT: inlined in DChannelMgr::SetupDaemonList (0xD270).
    DChannel(GameEventDaemonId const& daemonId, unsigned long addr, unsigned short port)
        : _daemonId(daemonId), _addr(addr), _port(port) {}
    virtual ~DChannel();             // 0x7D50
    virtual unsigned long long GetId();  // 0x7D30

    GameEventDaemonId _daemonId;
    unsigned long _addr;
    unsigned short _port;
};
static_assert(sizeof(DChannel) == 0x38, "sizeof DChannel");

class DChannelMgr : public SessionHandler
{
public:
    struct DaemonInfo
    {
        GameEventDaemonId daemonId;
        unsigned long ipaddr;
        unsigned short port;
    };

    DChannelMgr();
    virtual ~DChannelMgr();
    virtual bool OnAccept(Session const*) const;
    virtual bool OnConnect(Session const*, bool) const;
    virtual void OnClose(Session const*, bool) const;
    virtual bool PacketHandler(Session const*, Packet const*) const;

    void Finalize();
    bool SetupDaemonListFromXml(wchar_t const* xml);
    bool SetupDaemonList(DaemonInfo** list, int count);
    static bool CreateDaemonListXml(wchar_t const* xml);
    // PDB DChannelMgr::ErrCode (SmartCouponDaemon type 0x47D3).
    enum ErrCode
    {
        ERR_SUCCESS = 0,
        ERR_INVALID_PARAM = 1,
        ERR_ADDWORLD_NOT_CAPABLE = 2,
        ERR_ADDWORLD_ALREADY_REGISTERED = 3,
    };

    ErrCode AddDaemon(DChannel* channel);  // 0xdab0
    DChannel* FindDaemon(GameEventDaemonId const* daemonId);
    bool ReplaceDaemon(DChannel* newDaemon);

private:
    static void writeFileUtf8(void* handle, wchar_t const* format, ...);

public:
    CriticalSection _lock;
    std::map<GameEventDaemonId, DChannel*, std::less<GameEventDaemonId>,
             StlAllocator<std::pair<GameEventDaemonId, DChannel*>, 2> > _list;
};
static_assert(sizeof(DChannelMgr::DaemonInfo) == 0x10, "sizeof DChannelMgr::DaemonInfo");
static_assert(sizeof(DChannelMgr) == 0x50, "sizeof DChannelMgr");
static_assert(offsetof(DChannelMgr, _list) == 0x30, "DChannelMgr::_list");

// 0x835F8
// PDB: LF_ENUM 0x2731
enum SmartCouponDaemonType
{
    SMARTCOUPON_DAEMONTYPE_NONE = 0,
    SMARTCOUPON_DAEMONTYPE_GAME = 1,
};

extern wchar_t const* SmartCouponDaemonTypeDesc[2];

bool HandleSmartCoupon_HelloReq(Session const* session, Packet const* packet);                 // 0x7DC0
bool HandleSmartCoupon_GameEventByCharacterReq(Session const* session, Packet const* packet);  // 0x8360
bool HandleSmartCoupon_GameEventByAccountReq(Session const* session, Packet const* packet);    // 0x8E80
// 0x83660
extern bool (*SmartCouponPacketSmartCouponSideHandlerList[10])(Session const* session, Packet const* packet);
