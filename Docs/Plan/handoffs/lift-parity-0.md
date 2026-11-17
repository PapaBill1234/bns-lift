# lift-parity-0 handoff

## Done
- Task 1: `tools/gate.sh` ok. `tools/parity.sh` ok (run after the funcdiff fixes).
- Task 2: `tools/funcdiff.py --only` prints ONLY-ORIG and ONLY-OURS (name, rva, size, mangled name).
- Task 3/4: 4 noise fixes in `tools/funcdiff.py` (`signals()`, `Image.data_below`, `Image.const_ptr`).
  Each fix has its disassembly proof in `Docs/Parity/noise.md`. No MATCH lost, no key lost.
- Task 5/6: `Docs/Parity/triage.md` has cause classes (with rules), counts, top 10, a shared table
  (169 DIFF, 81 misses, 35 only-ours) and a table per exe. All 937 DIFF entries and all 342 misses have a class.
- Task 7: zstd result in `triage.md`: the original is a zstd `dev` snapshot (`08c5be5d`..`ac4f7ead`, May 2018),
  not v1.3.5.

## Parity (MATCH, baseline -> now)
- CacheGate 216 -> 293, LobbyGate 280 -> 377, SmartCouponDaemon 225 -> 334, PostOfficeDaemon 262 -> 375.
- The rise is from the tool fixes only. The runner must accept the new baseline (`--accept`).

## Top causes (entries)
- `__FILE__` path 222, constant 173, not referenced in ours 153, inlined but should not be 129,
  memory manager callee 105, RefCntObject base vtable store 76, zstd version 73.

## Not done
- Optional fix A (name TLS offsets after `gs:[0x58]` from PDB thread symbols). Not proven, not changed.

## ❓
- RefCntObject base vtable store: maybe `__declspec(novtable)` in the original. Not proven.
- Noise candidates B, C, D in `noise.md`: judged real, not fixed.
- The classifier is by rule (`.scratch/triage.py`). A fix card must check its function with `--show`.

## Blocked
- None.

## Gate result
- `tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok, MATCH -> DIFF 0, MATCH name gone 0 in all 4 exes.
- Gate fix: `tools/funcdiff.py` sets `LIFT_IDA_DIR` to `~/Documents/Codex/private-project/ida/lift` when it is not set and no parent dir has `ida/lift` (worktree). `tools/parity.sh` without `LIFT_IDA_DIR`: parity ok, 0 MATCH lost.
