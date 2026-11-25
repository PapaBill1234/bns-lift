# lift-parity-0: parity tooling: make funcdiff exact, list the misses, triage all DIFF functions

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`<work-root>/ida/lift/CacheGate/CacheGate.exe`).

## Goal
The parity number is true. Each DIFF function and each miss has a cause class. The fix cards after this card use the triage.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md` and `Docs/Parity/lessons.md` if they exist.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- `tools/funcdiff.py` compares 3 signals per function: calls, data refs and constants. It pairs by mangled name, then by unique PDB name.
- Known noise ❓: some constants look like image offsets (0x6280.. against 0x5660.. in `ClientManager::ReleaseSession`). Some template names differ only in form (`StlAllocator<pair<K,V>>` against `pair<K const,V>`). Each can also be a real difference.
- Known real differences: `Daemon::Start` in the original calls `BaseMemoryManager::_Instance` through indirect calls; ours calls `import:HeapAlloc`. `ThreadManager::Initialize` is missing. 2 `L"source\Daemon.cpp"` refs are missing (`__FILE__`, `__LINE__` arguments).
- Shared code (in 2 or more exes) has 270 DIFF entries. The largest groups: free functions 28, Session 20, Daemon 11, Network 11, ZSTD 10, Packet 9, DbTransaction 9.

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`.
2. Add `--only` to `tools/funcdiff.py`: it prints the functions that are only in the original (name, rva, size) and the functions that are only in ours.
3. Find the noise in funcdiff. Look at 20 or more DIFF functions with `--show`. For each signal difference, decide: noise of the tool, or a real code difference. Prove each case with the disassembly of both exes.
4. Fix only the proven noise in `tools/funcdiff.py` (for example: constants that are image addresses, name forms that are equal). Write each fix and its proof in `Docs/Parity/noise.md`.
5. Write `Docs/Parity/triage.md`: a table for each exe and one for the shared code. Columns: function, signal, cause class, source file. Cause classes (add more if needed): missing function, inlined but should not be, not inlined but should be, wrong callee, missing `__FILE__`/`__LINE__` or string ref, constant differs, STL form differs, zstd version, compiler noise that the source cannot change.
6. Count the functions per cause class. Put the counts at the top of `triage.md`. Give the top 10 causes by count.
7. Check the vendored zstd version against the version string or the code in the original exe. Write the result in `triage.md`.

## Files
- `tools/funcdiff.py`
- `Docs/Parity/`
- `Docs/Plan/handoffs/lift-parity-0.md`

## Done when
- `Docs/Parity/triage.md` has a cause class for each DIFF function and each miss of the 4 exes.
- `Docs/Parity/noise.md` lists each tool fix with its proof, or says that no noise was found.
- `tools/parity.sh` passes.
