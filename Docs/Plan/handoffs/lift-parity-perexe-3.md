# lift-parity-perexe-3 handoff

Turns: 75 (estimate, 3 stages)

## Done
- Per-exe build: `tools/vs2010/build.sh` (objects in `build-vs2010/obj/<TAG>/`).
- `StlMemory.h`: per-exe default path. `TimerQueue::~TimerQueue` MATCH in CG, LG, SCD, POD.
- `Session.cpp`: `Send(Packet const*)` noinline for CG and LG. `deallocateCrypt` noinline for LG. Compare-chain type test. LG `~Session` 0x175a0 MATCH.
- POD `PostContext`, `RelayContext`, `RelayTimeContext`: mixed-case `LIFT_STLMEMORY_FILE`.
- `Port::Clear`, `Port::clearPool`, `Session::Send`, `Session::~Session`: MATCH in all 4 exes.
- `Docs/Parity/lessons.md` section E: worked, did not work, facts.

## Not done (one line per DIFF)
- `Session::SendV` CG 0xfaa0: consts 91. The original has const 0xf9e twice, ours once. Cause not checked (IDA did not open). Stopped: IDA-only item.
- `operator delete(void*,void*)` (Memory.h:173): score 0 in CG, SCD, POD. Not a per-exe cause. Card arraynew-3.
- `Network::Network`, `PacketBufferAllocator::initAllocator`, `Session::Session`, `StaticPageMemoryManager::Initialize`, `DaemonConfig::Dump`: refs-only DIFF (global data-ref count, not a path). Not per-exe.
- Extra inline of `RefCntObject` remove-reference (`Daemon::Now` + CRASH log) in ours, in CG, LG, SCD, POD. The function is not named. Find it with `funcdiff --show '.'`.
- No path-literal-only DIFF function was found in the 4 exes.

## ❓
- `tools/parity_shared.py` still lists `Session::~Session` (4 exes) and `TimerQueue::~TimerQueue` (LG, SCD, POD) as DIFF, but the per-exe json says MATCH. Cause not found.

## Blocked
- IDA: the CG `.i64` did not open (status 4). IDA-only items are not checked.

## Gate result
- Full `tools/gate.sh` ok. Full `tools/parity.sh`: `parity ok` (not accepted; the runner does `--accept`).
- Parity now: CG 421/491, LG 533/739, SCD 512/669, POD 592/759 (before: 420/530/510/588). Shared 421/499 (no change).
- Gate fix: moved the python filter of `perexe_srcs.py` into `tools/vs2010/build.sh` (the file was outside the card paths).
