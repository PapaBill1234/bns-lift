# lift-parity-arraynew-3 handoff

Turns: 3 in this session (stage 3); the earlier stages used 2 sessions of 25 turns.

## Done
- LG `Client.cpp`: array new pattern (`new (buffer) T[n]` with `eh vector constructor iterator`). LG 595 -> 600.
- `Session::send` (BloodLib `Session.cpp`, 0xFE90) is `__declspec(noinline)`. `ClientManager::broadcast` 0x6410 is MATCH.
- `Docs/Parity/lessons.md`: sections "lift-parity-arraynew-3, stage 1" and "stage 2" (facts, tries, stop list).
- Gate: ok (`.scratch/gate_errors.sh`). Parity: ok. CG 436, LG 600, SCD 556, POD 637. No MATCH lost.

## DIFF functions not fixed
- `GateKeyManager::Finalize` 0x3b10 (97.0) and `ClientManager::Finalize` 0x5cf0 (95.2): constants, `.tls` offset of `__delv_buf__` (0x18 in the original, 0x10 in ours), link order. Stopped: the stop list in lessons.md.
- `ClientManager::BroadcastAnnounceNotify` 0x62c0 (95.8): calls and block layout (`Log::Write` order, 2 `Packet::Clear`). The Compose-branch swap gave no gain and was reverted.
- `GateKeyManager::MakeGateKey` 0x3ec0 (94.3): the original calls `GateKeyEntry::scalar deleting destructor`, ours calls `RefCntObject::removeReferenceCount`. Not tried.
- Scalar placement `operator delete(void*,void*)` (LG orig 0x1000, score 0 in all 4 exes): global fix not tried. Plan in lessons.md stage 2 (non-inline declaration in `include/vs2010/new`, crash body in `BloodLib/source/Memory.cpp` with a per-exe path).

## ❓
- Module of `__delv_buf__` (kept in `Client.cpp`).
- LG path form of `Memory.h` in `operator delete[]` is lower case (from HR). Other LG `Memory.h` references are not checked.
