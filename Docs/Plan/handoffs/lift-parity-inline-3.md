# lift-parity-inline-3 handoff

## Done
- MATCH +3 CG (424), +9 LG (583), +3 SCD (543), +6 POD (626). No MATCH lost. Gate ok, parity ok.
- Fixed: `Log::Initialize`, `String::GetId128FromGuidString`, `CrashHandler::handleCrash` (4 exes), LG `LobbyD::Send*` x6, POD `RelayContext::ProcessRelayRequest/Response/Timeout`.
- Fix forms are in `Docs/Parity/lessons.md` (inline-3 stages 2 to 5).

## Not fixed (function, signal, cause, why stopped)
- `WinServiceConsole::UninstallService` (CG 0x17f00): orig 5 `CloseServiceHandle`, ours 4. Compiler tail merge. Two source forms tried.
- `PipeConsole::SetInvalidInfo` (CG 0x15d90): orig 2 `addNode` sites, ours 1. Compiler merges the calls. Three forms tried.
- `Network::OpenPort` 9-arg (CG 0xd2c0): ours has fewer assert tails. Per-exe purpose test and constant propagation drops `id == 0`. Perexe-3 scope.
- `Network::OpenPort` 1-arg (SCD 0x1ab20): not measured in detail. Same family as above.
- `PacketBuffer::Compose`: orig 3 `memcpy`, ours 2. VS2010 merges the identical tails of cases K, P, s. Fix splits the crash tails (score drops).
- `Session::HandleEvent` (CG 0xf1c0): one extra `Log::Write`, score 98.5. Not found in the time.
- `Session::~Session`: not measured.
- LG `LobbyDSessionHandler::OnConnect` (94.4), `OnClose`: ours has consts `0x2`, `0x278` extra and no `L""` ref. Cause not found.
- POD `TextStreamPacketBufferHandler::Destroy` (0x2c4a0), `RawPacketBufferHandler::Destroy`: one extra `<indirect>`. Cause not found.

## ❓
- `Network::OpenPort` purpose test form. `L""` ref and `0x278` const in LG OnClose/OnConnect/Hello.

## Blocked
- None.

## Gate result
- `tools/gate.sh` ok. `tools/parity.sh` ok (CG 424/491, LG 583/739, SCD 543/669, POD 626/759).

Turns: about 100 (5 stages)
