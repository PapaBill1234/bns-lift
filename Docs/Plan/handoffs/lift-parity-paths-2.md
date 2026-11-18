# lift-parity-paths-2 handoff

Turns: 38

## Done
- Per-exe path literals: macros `LIFT_PACKETUTIL_H_PATH`, `LIFT_CHANNEL_H_FILE`, `LIFT_FRAGMENTPACKET_PATH`, `LIFT_STLMEMORY_FILE`.
- Wrappers `{Port,Timer,Channel}<Exe>.cpp`, `PacketUtil{LobbyGate,PostOfficeDaemon}.cpp`, `FragmentPacketLobbyGate.cpp`;
  CMake `LIFT_COMMON_PATH_SOURCES` and `lift_common_{lg,scd,pod}` choose the wrapper. CG keeps its object order.
- Parity: CG 406/491 (+1), LG 512/739 (+6), SCD 488/669 (+4), POD 535/759 (+6). No MATCH lost.
- `Docs/Parity/lessons.md` A5: patterns that worked and that did not work.

## Not done (function, signal, cause, why stopped)
- `TimerQueue::~TimerQueue` (LG, SCD, POD): refs; the inlined `StlAllocator::deallocate` COMDAT copy with the CG path wins at link.
  Fix needs `-DLIFT_EXE_<X>` per exe-library source in `tools/vs2010/build.sh` (outside my files). Expected +3.
- POD `RelayContext::ProcessRelayResponse`, `ProcessRelayTimeout`, `*::updateWorldList`, `UnsentPostContextManager::initContextManager`
  (+3 more): refs `Lock.h`; ours inlines `AutoCS` more; `noinline` on `AutoCS::~AutoCS`/`Leave` loses a MATCH. Undone.
- `LogMedia::Write`, `TimerQueue::clearShortTermQueueSlot` (4 exes): refs `RefCntObject.h`; the original calls `removeReferenceCount`,
  ours inlines it; `noinline` loses 5 MATCH. Undone.
- `BloodDaemonMain`, `Daemon::start` (4 exes): refs `source\Memory.cpp`; the original inlines the Memory init and calls `printUsage`
  before `makeConsole`. Inline choice, not path. Stopped.
- LG `FragmentPacket::StartRepeat` (const 0x8), `FragmentPacketConcatenater::Clone` (const 0xfffffffffffffffe), `::Add` (Log::Write order): not path causes.
- POD `PacketFormatIterator::SetFormat`, `Channel::Close`, `SessionPool` functions: not analysed again after the wrappers; the remaining DIFF is not a path literal.

## ❓
- Whether the wrappers move the data layout (no MATCH lost, so no effect seen).

## Gate result
`tools/gate.sh` ok. `tools/parity.sh` ok.
