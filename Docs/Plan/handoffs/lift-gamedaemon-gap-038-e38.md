# Handoff: lift-gamedaemon-gap-038-e38 (card lift-gamedaemon-e38)

## Lifted

- `GameArenaLobbyManager::GameArenaLobbyManager` (0xd3000). The body uses a local view of the PDB layout (size 0xD0). Formtest: SAME. The body has a dead-strip keep pragma.
- `GetNPCustomProtocolStr` (0x16f4e0). Local constants give the PDB enumerators. Formtest: SAME. The body has a dead-strip keep pragma.

## Not done

- `MarketReaderAgentSessionHandler::OnAccept` (0x1618f0): log path (E16). The body calls `Log::Write` and `AlertSender::Write`.
- `MarketReaderAgentSessionHandler::PacketHandler` (0x161d40): log path (E16). The body calls `Log::Write`.
- `GameSideArenaLobbySessionHandler::OnAccept` (0xd26d0): log path (E16). The body calls `Log::Write` and `AlertSender::Write`.
- `GameArenaLobbyManager::ResetIsInitializeGuildInfo` (0xd3720): log path (E16). The inlined lock check calls `Log::Write` and `AlertSender::Write`.
- `NPRegisterServiceTran::NPRegisterServiceTran` (0x16f530): the constructor sets the `GameTran` and the class vtables. The skeleton `GameTran` has no virtual layout and no lifted constructor. A view cannot give the vtable stores.
- `NPGetChannelPropertyTran::NPGetChannelPropertyTran` (0x170690): same cause as 0x16f530.
- `ReturnToLobbyTran::failProcess` (0x13bdc0): the body needs the `ReturnToLobbyTran::_user` layout, the GameDaemon `User`/`Channel::GetSession` call, `Session::Send` and `RefCntObject::removeReferenceCount` with the GameDaemon `Channel.h` path. No GameDaemon lift has these yet.
- `RankingChannel::onConnect` (0x1af180): log path (E16). The body calls `Log::Write`.
- `HandleRankingGame_HelloFail` (0x1af940): log path (E16). The body calls `Log::Write`.
- `AchievementDaemonChannel::onConnect` (0x32f90): log path (E16). The body calls `Log::Write`.
- `HandleAchievementGameGameHelloFail` (0x33520): log path (E16). The body calls `Log::Write`.
- `AchievementDaemonChannel::Destroy` (0xa7870): the body calls the virtual `getSession` and `releaseSession` of the channel, `Session::StopReconnect`, `Session::close` under the session lock and `Port::RemoveSession`. The GameDaemon skeleton has no channel vtable layout and no `Session` view yet. Note: ICF folds this body with `RankingChannel::Destroy`.
- `DeleteCharacterTran::DeleteCharacterTran` (0x760b0): same cause as 0x16f530. The constructor sets the `GameTran` and the class vtables.

All these bodies stay `LIFT_STUB`.

## Changed files

- `src/Server/GameDaemon/gamearenachannel_cpp_2.cpp`
- `src/Server/GameDaemon/npservicetran_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-038-e38.md`

## Gate and MATCH

The driver builds and runs the parity check after this session. This session ran no build.
