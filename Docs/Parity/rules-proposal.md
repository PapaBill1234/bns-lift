# Rules proposal for the GameDaemon lift (lift-parity-review-1, 2026-11-18)

Source: `lessons.md` (A1 to A16, C, D), `review-1.md`, and the behaviour misses of an older port review (rev-small-348).
Each rule has a reason. "Lift step" refers to the lift method in `Docs/Plan/plan.md` (steps 1 to 6).
A later docs card copies the accepted rules into `Docs/Plan/plan.md` and the lift rules of the runner.

## 1. Changes to the lift method

| # | Rule | Reason |
| --- | --- | --- |
| M1 | Add lift step 5a: after `tools/gate.sh`, run `tools/vs2010/build.sh` and `tools/funcdiff.py` on each module that you lifted. Each function of the module must be MATCH, or the handoff gives its signal and cause. | Round 1 fixed 861 functions after the lift. Each fix needed a second read of the same code. A fix in the lift card costs less. |
| M2 | Lift step 5a also reads the miss list of the module. A function that the original has and our exe does not have is a lift error until you find the cause. | A miss shows a missing call or an inline choice. In lg-1 a miss showed a missing `SetEvent` call (a behaviour error). |
| M3 | Before you change source for a DIFF, check that the DIFF is not tool noise (`noise.md`, `lessons.md` C1 to C3). | Tool noise made 2 good changes look bad (Patterns 47, 49). The tool card gave 396 MATCH, more than any source card. |
| M4 | `tools/vs2010/build.sh` must rebuild each object whose headers changed (dependency files). | 5 cards measured stale objects after a header change. |
| M5 | Find the compile flags of each original library from the PDB (`S_ENVBLOCK` command line of each module) before the lift. Give each library these flags in the VS2010 build. | The crypto misses (LG 60, SCD 39, POD 39) probably come from other flags of the BloodCrypto lib ❓. One flag error makes a full library DIFF. |
| M6 | Write each shared path literal as a macro with an `#ifndef` default and a per-exe wrapper `.cpp` from the start (lessons A5). Record the project-relative path of each source file of the new exe in `Docs/layout.md`. | The original compiles each shared `.cpp` in each exe project. 45 functions needed a fix later; more are open. |
| M7 | Each handoff has a line `Turns: <n>`. | Review 1 could not give the cost of a card. |
| M8 | Cut parity cards by cause, not by exe. A cause in 2 or more exes is one card. | Each exe-only card of round 1 stopped far below 90 %. The causes were shared. |
| M9 | Do not spend turns on a cause from the stop list (`review-1.md` section 5: `.tls` order, constant propagation, constant CSE, ICF names, CRT funclets). Write the function in the handoff with the stop-list reason. | About 10 tries on LTCG choices gave 0 MATCH. |

## 2. Changes to the lift rules (source form)

| # | Rule | Reason (lessons, count) |
| --- | --- | --- |
| R1 | Use the exact upstream commit of third-party code. Find it: count the calls of one function on both sides, then bisect the commits. | A2: the wrong zstd version made 73 functions DIFF. |
| R2 | When the original calls a small function out of line from each caller, put `__declspec(noinline)` on it and mark it `// LIFT:`. Check all callers in all exes first. Then check the inline choice of the callers again. | A3: 53 functions. LTCG inlines small functions that the original kept. |
| R3 | When the original calls a global object through its vtable (HR: indirect call), call it through a base reference (`static_cast<Base const&>(obj).f()`), not on the object. | A4: 49 functions. A direct call binds statically and LTCG inlines it. |
| R4 | Copy each `__FILE__`-style literal and each header path literal of the original byte for byte, with the per-exe path and case (M6). | A5: 45 functions. The literal is a data ref. |
| R5 | Write the `if` body that is first in the original address order first. Read the block order in the disassembly when the HR is not clear. The HR condition can be the inverse of the source condition. | A6: 30 functions. VS2010 lays out the `if` body first. |
| R6 | Give each member the exact PDB type, with the same `volatile` and `const`. Do not add `volatile` for thread safety. `tools/pdb_layout.py` must compare the type qualifiers. | A7: 25+ functions. A volatile store keeps dead stores. |
| R7 | When the original calls `swprintf_s<N>` (or another CRT template), use the 2-argument form with an array destination. | A8: 25 functions. |
| R8 | Give STL containers the allocator and pair types of the PDB names (`std::pair<K, V>`, key not const). Insert with `std::pair<K, V>(k, v)`. | A9: 18 functions. |
| R9 | Write loops in the form of the HR: the same counter direction, the same pointer steps, the same `break` test. Do not unroll or merge loops. | A10: 18 functions. |
| R10 | Copy each data ref and each read of the original one to one: the literal `L""` (not a named array), one local for a repeated value, a compare with the named global, member stores in the original order. | A11: 20 functions. |
| R11 | Write one full error block per failed call when the original has one per call. Write one shared cleanup tail when the original has one. Use `__try`/`__finally` when the HR shows `$__FINALLY_n`. | A12: 12 functions. |
| R12 | Do not declare a destructor when the original destructor is a thunk with no vtable store. | A13: 12 functions. |
| R13 | Copy the allocation form of the original: placement array new with the 8-byte count, null-checked placement new. | A14: 10 functions. |
| R14 | Do not add a lift helper as a real function. If a helper makes the source clear, make it `static __forceinline` and mark it `// LIFT:`. Check the miss and "ours calls more" lists after the build. | A15 and `review-1.md` section 5: LG and POD helpers made 19 "ours calls more" DIFF and 67 ref DIFF. |
| R15 | Write a UTF-8 BOM in each source file with Korean literals. | A16: the literal bytes differ without it. |

## 3. Behaviour misses (rev-small-348)

The older review compared a port of SmartCouponDaemon with the original (348 = the 2019 + PDB build).
For each miss class: can funcdiff parity find it? If not, which check can find it, and which lift step runs it.

| Miss class | Example in the review | funcdiff finds it? | Check that finds it | Lift step |
| --- | --- | --- | --- | --- |
| SQL store not called | Empty publication store, no SQL load or reload | Yes: the SQL functions are misses, the callers have fewer calls | funcdiff miss list | Lift card, step 5a (M2) |
| NP transport not called | NP init and send not called | Yes: misses and fewer calls | funcdiff miss list | Lift card, step 5a |
| Runtime selection from config | NP on/off ignored | No: the calls exist, the condition is wrong | Runtime test with each config value (NP on, NP off), log compare with the original exe | Verify card |
| Async dispatch | One worker waits for each NP result | No: control flow and job order | Runtime test with a slow NP peer: send 2 requests, the second reply must come before the first NP result | Verify card |
| Error code routing | NP error 5809 on the wrong path | Partly: a missing or extra 5809 const shows; a wrong branch with the same const does not | Table test: one NP reply per row of the NP result table, compare the DB call and the reason with the original | Verify card |
| String compare form | `"Success"` exact compare against `_wcsicmp` | Yes: other callee | funcdiff calls | Lift card, step 5a |
| Number parse form | Full parse against `_wtoi` | Yes: other callee | funcdiff calls | Lift card, step 5a |
| Request decoding | A decoded `tid` is kept after a short later field | No: the store order of the outputs | Short-packet test: cut each request at each field limit, compare the reply bytes with the original exe | Verify card |
| Config load control flow | Bad entry skipped (`continue`) against full abort; child name check | Partly: the `_wcsicmp` call and the `L"event"` ref show; the `continue` does not | Malformed-config test: load a config with bad entries, dump the loaded list, compare with the original | Verify card |
| Guard condition | Repeated Hello: `GetId() != 0` guard | No: the condition form | Packet replay: Hello 2 times with ID 0 and with ID not 0 | Verify card |
| Handler table contents | Only commands 1, 4, 7 have a handler | No: funcdiff compares only the table ref | Handler-table dump: read each table slot of both exes and compare the symbol names; add it to `tools/pdb_layout.py` or funcdiff data compare | Lift card, step 5a |
| Packet formats and widths | `hqiohq`, `o` = 16 bytes | Yes when the format is a string literal (data ref); field widths come from the PDB types | funcdiff refs; `tools/pdb_layout.py` for the packet structs | Lift card, step 5 and 5a |
| Reply field order | Last 2 fields swapped in a reply | No: the argument order of the same calls | Packet replay and byte compare of each reply with the original exe | Verify card |
| Fixed intervals | 5 s connect timeout, 30000 ms ping | Yes: consts | funcdiff consts | Lift card, step 5a |
| Gate order and reason codes | Hello reasons 2, 9, 8, 2, 11, 13 | Partly: the const set shows, the order does not | Packet replay of each fail case, compare the reason with the original | Verify card |

### Proposed rules from section 3

| # | Rule | Reason |
| --- | --- | --- |
| B1 | Each lift card runs step 5a (M1, M2). A miss or a different callee is a lift error until the handoff gives the cause. | funcdiff finds missing calls, other callees, consts and literals (6 of the 15 classes, and part of 4 more). |
| B2 | Each lift card dumps each handler table and each vtable of its modules and compares the slots with the original. | funcdiff sees only the table ref. A wrong slot changes the command set. |
| B3 | Each verify card runs a packet replay of each command (good, short and bad forms) on the original exe and on the lifted exe, and compares the reply bytes and the log lines. | Argument order, decode order, guard conditions and gate order give equal code signals. Only a runtime compare finds them. |
| B4 | Each verify card runs the exe with each config switch (for example NP on and off) and with a malformed config. Compare the loaded lists (config dump) and the logs. | Runtime selection and skip-or-abort loaders do not show in funcdiff. |
| B5 | Each verify card runs with a real SQL DB and a slow peer (NP stub with delay). | The SQL store and async dispatch show only at runtime. |
