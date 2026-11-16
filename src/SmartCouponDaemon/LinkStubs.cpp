// Stub bodies so that the SmartCouponDaemon exe links.
// Each stub is listed in Docs/Plan/handoffs/lift-smartcoupondaemon-4.md (Not done).
// Replace each stub with the lifted body in its PDB module .cpp, then remove it here.
#include "SmartCouponDaemon.h"
#include "CouponGameEventConfig.h"
#include "CouponJob.h"
#include "DaemonChannel.h"
#include "Db.h"
#include "EventNotiJob.h"
#include "GameEventWorker.h"
#include "NPChannel.h"
#include "ObjectPool.h"
#include "SendPublicationEvent.h"
#include "ManagerChannel.h"
#include "Channel.h"
#include "SmartCouponDB.h"

// CouponGameEventConfig.obj
GameEventConfig::GameEventConfig() {}                                  // TODO(lift-smartcoupondaemon-5)
GameEventConfig::~GameEventConfig() {}                                 // TODO(lift-smartcoupondaemon-5)
bool GameEventConfig::Load(wchar_t const*) { return false; }           // TODO(lift-smartcoupondaemon-5)
void GameEventConfig::Dump() {}                                        // TODO(lift-smartcoupondaemon-5)

// Channel.obj (lift_common). ❓ Not in the SmartCouponDaemon PDB. The ClientSideDaemonChannel vftable in
// Channel.cpp needs it. CacheGate has its body in src/CacheGate/CacheDChannel.cpp.
bool ClientSideDaemonChannel::onAccept(Session const*) { return false; }  // ❓ TODO(lift-smartcoupondaemon-5)

// GameEventWorker.obj
GameEventManager* GameEventManager::Instance = 0;                      // TODO(lift-smartcoupondaemon-5)
bool RetryCouponPublicationEvent::HandleEvent(EventContext*, unsigned long) { return false; }  // 0xC2F0 TODO(lift-smartcoupondaemon-5)

// SmartCouponDB.obj
bool SmartCouponDB::LoadRetryReadyGameEventLogList(int*, RetrieveEventLogContext*) { return false; }  // 0x145F0 TODO(lift-smartcoupondaemon-5)

// CouponJob.obj
RefCntPoolObj::~RefCntPoolObj() {}                                     // TODO(lift-smartcoupondaemon-5)
CouponJob::~CouponJob() {}                                           // TODO(lift-smartcoupondaemon-5)
bool CouponJob::dispatch_work(int, void*) { return false; }            // TODO(lift-smartcoupondaemon-5)
JobManager::~JobManager() {}                                           // TODO(lift-smartcoupondaemon-5)
bool JobManager::Initialize(int) { return false; }                     // TODO(lift-smartcoupondaemon-5)
void JobManager::Clear() {}                                            // TODO(lift-smartcoupondaemon-5)

// SendPublicationEvent (❓ module)
SendPublicationEvent::~SendPublicationEvent() {}                       // TODO(lift-smartcoupondaemon-5)
unsigned int SendPublicationEvent::EventId() const { return 0; }       // TODO(lift-smartcoupondaemon-5)
bool SendPublicationEvent::HandleEvent(EventContext*, unsigned long) { return false; }  // TODO(lift-smartcoupondaemon-5)

// DaemonChannel.obj
DChannelMgr::DChannelMgr() {}                                          // TODO(lift-smartcoupondaemon-5)
DChannelMgr::~DChannelMgr() {}                                         // TODO(lift-smartcoupondaemon-5)
bool DChannelMgr::OnAccept(Session const*) const { return false; }     // TODO(lift-smartcoupondaemon-5)
bool DChannelMgr::OnConnect(Session const*, bool) const { return false; }  // TODO(lift-smartcoupondaemon-5)
void DChannelMgr::OnClose(Session const*, bool) const {}               // TODO(lift-smartcoupondaemon-5)
bool DChannelMgr::PacketHandler(Session const*, Packet const*) const { return false; }  // TODO(lift-smartcoupondaemon-5)
void DChannelMgr::Finalize() {}                                        // TODO(lift-smartcoupondaemon-5)
bool DChannelMgr::SetupDaemonListFromXml(wchar_t const*) { return false; }  // TODO(lift-smartcoupondaemon-5)
bool DChannelMgr::CreateDaemonListXml(wchar_t const*) { return false; }     // TODO(lift-smartcoupondaemon-5)

// Db.obj
void* Db::EnvHandle = 0;                                               // TODO(lift-smartcoupondaemon-5)
Db* Db::Instance[41];                                                  // TODO(lift-smartcoupondaemon-5)
bool Db::Initialize(unsigned int, wchar_t const*) { return false; }    // TODO(lift-smartcoupondaemon-5)
void Db::Clear(unsigned int) {}                                        // TODO(lift-smartcoupondaemon-5)

// EventNotiJob.obj
ObjPool* EventNotiJob::_pool = 0;                                      // ❓ TODO(lift-smartcoupondaemon-5)
EventNotiJob::EventNotiJob() {}                                        // TODO(lift-smartcoupondaemon-5)
EventNotiJob::~EventNotiJob() {}                                       // TODO(lift-smartcoupondaemon-5)
JobDef const* EventNotiJob::GetDefinition() const { return 0; }        // TODO(lift-smartcoupondaemon-5)
void EventNotiJob::deallocate_me(void*, wchar_t const*, int) {}        // TODO(lift-smartcoupondaemon-5)
bool EventNotiJob::work(int, void*) { return false; }                  // TODO(lift-smartcoupondaemon-5)

// GameEventWorker.obj
bool GameEventManager::Initialize(void (*)(EventObject*), ThreadManager*, unsigned int) { return false; }  // TODO(lift-smartcoupondaemon-5)
bool GameEventManager::PostGameEventLogList(RetrieveEventLogContext*) { return false; }  // TODO(lift-smartcoupondaemon-5)
void GameEventManager::Clear() {}                                      // TODO(lift-smartcoupondaemon-5)

// NPChannel.obj
SessionHandler* NPChannel::_sessionHandler = 0;                        // ❓ TODO(lift-smartcoupondaemon-5)
bool NPChannel::Setup(int, wchar_t const*) { return false; }           // TODO(lift-smartcoupondaemon-5)
void NPChannel::Cleanup() {}                                           // TODO(lift-smartcoupondaemon-5)
bool NPServiceChannelManager::OnConnect(NPChannel*, bool) const { return false; }  // TODO(lift-smartcoupondaemon-5)
bool NPServiceChannelManager::OnClose(NPChannel*, bool) const { return false; }    // TODO(lift-smartcoupondaemon-5)
bool NPServiceChannelManager::HandleMessage(NPChannel*, StsMsgLib::_StsMsg*, void*) const { return false; }  // TODO(lift-smartcoupondaemon-5)
bool NPServiceChannelManager::Initialize(unsigned long, unsigned short) { return false; }  // TODO(lift-smartcoupondaemon-5)

// SmartCouponDB.obj
bool SmartCouponDB::LoadCouponPublicationList(int*, RetrievePublicationContext*) { return false; }  // TODO(lift-smartcoupondaemon-5)
bool SmartCouponDB::LoadGameEventLogList(int*, RetrieveEventLogContext*) { return false; }          // TODO(lift-smartcoupondaemon-5)
