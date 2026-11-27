# Handoff: lift-gamedaemon-gap-025-e25 (card lift-gamedaemon-e25)

Exe: GameDaemon (2019 + PDB). Round 1. Two sessions did the work (planned context split).

## Lifted

- `source_logfile`: `LogFile::Write` (0x6a0250).
- `logarchivesession`: `LogArchiveSession::~LogArchiveSession` (0x6b9d00), `LogArchiveSession::Close` (0x6ba510).
- `daemon`: `Daemon::AddDelayedRelease` (0x68cf50), `Daemon::SetPublicAddressWithSetting` (0x68d9e0), `parseCIDRAddress` (0x68dba0).
- `lock`: `AutoCS::Enter` (0x1cbd0), `AutoCS::Leave` (0x1cc50), `AccountInventoryChannelManager::~AccountInventoryChannelManager` (0x18d060), `AutoSRW::~AutoSRW` (0x1dc200).
- `source_delayedrelease`: `DelayedRelease::DelayedRelease` (0x6a11d0), `DelayedDelete::Cleanup` (0x6a1960), `DelayedDelete::deleteNode` (0x6a19d0), `DeleteEvent::HandleEvent` (0x6a1a50).
- `channel`: `DaemonChannel::Send` x3 (0x69a3e0, 0x69a440, 0x69a4c0), `ClientSideDaemonChannel::initialize` (0x69a740), `ClientSideHashedDaemonChannel::Send` x2 (0x69abf0, 0x69ac40), `ClientSideHashedDaemonChannel::initialize` (0x69acc0), `ClientSideHashedDaemonChannel::releaseSession` (0x69afb0), `ServerSideDaemonChannel::Initialize` (0x69b0a0).
- `source_jsoncpp`: `Json::Reader::Reader` (0x6a4eb0), `Json::Value::CommentInfo::~CommentInfo` (0x6a8600), `Json::Value::CZString::~CZString` (0x6a87a0), `Json::Value::CZString::operator<` (0x6a87d0), `Json::Value::isInt` (0x6aa080), `Json::Value::isUInt64` (0x6aa1b0), `Json::valueToString(unsigned __int64)` (0x6aa430), `Json::valueToString(double)` (0x6aa650), `Json::valueToString(bool)` (0x6aa680), `GameObjectIdManager::~GameObjectIdManager` (0x6aad60).

## Decisions

- `LogArchiveSession`: the destructor calls `Close`. The compiler inlines `Close` (both bodies use line 249). The HR cache does not show the text of the log format string. The text in the source is a guess and has a `❓` mark.
- `jsoncpp.h`: added the PDB layouts of `Json::Value` (0x28), `Json::Value::CZString` (0x10), `Json::Value::CommentInfo`, `Json::Reader` (0xE0), `Json::Reader::Token`, `Json::Reader::ErrorInfo`, `Json::Features` and the enum `Json::ValueType`. `ValueHolder::map_` is `void*` for now (PDB type `ObjectValues*`).
- `IsIntegral`, `uintToString` and `maxUInt64AsDouble` are file statics of jsoncpp.cpp. The compiler inlines the two helpers.
- `GameObjectIdManager::~GameObjectIdManager` is an empty body. ICF folds it with other empty virtual destructors.
- The three `Json::valueToString` bodies have no `/INCLUDE` pragma. The public names have a long `StlAllocator` return type, and a wrong name stops the link. If funcdiff cannot pair them, add the pragma with the name from the publics dump.

## Not done

- 0x6a83c0 `Json::Exception::~Exception`: `Json::Exception` has no `std::exception` base and no `msg_` member yet (earlier decision, see the comment in `jsoncpp.h` and 0x6a84d0). The body needs that layout.
- 0x6a8420 `Json::Exception::what`: same cause (needs `msg_`).
- 0x6a8440 `Json::throwRuntimeError`: same cause. `Json::RuntimeError` also has no layout.
- 0x6a8540 `Json::throwLogicError`: same cause. `Json::LogicError` in `GameDaemonFwd.h` has no base.

## Gate and MATCH

The driver builds and runs the gate and funcdiff after this session. This session did not record a result.

Round 2: the round 1 gate build failed. The build log showed only a wine `XDG_RUNTIME_DIR` line. The missing object was `include_jsoncpp.cpp.obj`. Its cause: `jsoncpp.h` includes `<stack>` for `Json::Reader::nodes_`, and the VS2010 STL subset in `include/vs2010` had no `stack` header (the build uses `/X`). Round 2 adds `include/vs2010/stack` (`std::stack` over `deque`, size 0x30, the same form as `include/vs2010/queue`). This round did not change other code.

## Files changed

- `src/Server/BloodLib/include/Channel.h`
- `src/Server/BloodLib/include/Daemon.h`
- `src/Server/BloodLib/include/DelayedRelease.h`
- `src/Server/BloodLib/include/Lock.h`
- `src/Server/BloodLib/include/Session.h`
- `src/Server/GameDaemon/GameDaemonFwd.h`
- `src/Server/GameDaemon/accountinventorychannel_gd.h`
- `src/Server/GameDaemon/channel.cpp`
- `src/Server/GameDaemon/channel_gd.h`
- `src/Server/GameDaemon/daemon.cpp`
- `src/Server/GameDaemon/delayedrelease_gd.h`
- `src/Server/GameDaemon/leadtheballmanager.h`
- `src/Server/GameDaemon/lock.cpp`
- `src/Server/GameDaemon/lock_gd.h`
- `src/Server/GameDaemon/source_delayedrelease.cpp`
- `src/Server/GameDaemon/source_logfile.cpp`
- `src/Server/GameDaemon/logarchivesession.cpp`
- `src/Server/GameDaemon/logarchivesession.h`
- `src/Server/GameDaemon/jsoncpp.h`
- `src/Server/GameDaemon/source_jsoncpp.cpp`
- `include/vs2010/stack` (round 2)
- `Docs/Plan/handoffs/lift-gamedaemon-gap-025-e25.md`
