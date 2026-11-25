# lift-lobbygate-2: LobbyGate lift: base module delta, RSA and DH crypto (common)

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/LobbyGate/LobbyGate.exe`. PDB: `<work-root>/Service_348_8349/Service/LobbyGate/bin/LobbyGate.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of the earlier lift cards (CacheGate, SmartCouponDaemon, LobbyGate) for the state of `src/common/`.

## Modules (in `src/common/`, one `.cpp` + `.h` per PDB module)
Function counts are PDB symbol counts. They include EH funclets (`dtor$N`, `catch$N`) and scalar deleting destructors. The real lift count is lower. Before you lift a function, look for it in `src/common/` (grep the PDB name). Do not lift it two times.
- Missing functions in base modules: PipeConsole (17), AlertSender (12), Timer (10: `std::priority_queue<Timer*>`, TimerQueue), WindowConsole (8: WindowConsoleOnLogoff, WindowConsoleOnShutdown), Daemon (7: cooldown), TextConsole (7: Console base members), LogFile (5), BaseMemory (4: DumpLeak), MemoryManager (4: HeapMemoryManager::Clear), LogBuffer (3), Log (2), LogMedia (2), WinServiceConsole (2), RefCntObject (1), DaemonConfig (1), Thread (1), Console (1), DelayedRelease (1). About 88.
- Crypto (BloodCrypto): NumberTheory (31 missing; `NumberTheory.cpp` is not in `lift_common` yet), rsa (26), dh (14), oaep_encoder (9), CryptoKey (6), biArithmetic (6 missing), ripemd128 (4), prng (4: Prng::Generate, GeneratePrime), ripemd160 (2), Crypto (2: InstanceSize, Create), aes128 (1), mgf (1). About 106.
- Shared config: ContentsRuleConfigDefinition (9). Put it in `src/common/` like `BnsCommonConfigDefinition.cpp` ❓ (source path not in the PDB module name).
- About 203 symbols. Read `Docs/Plan/handoffs/lift-smartcoupondaemon-3.md` for the open crypto items (BUG addresses, `RSA = 65 // ❓`).
- Add `LogFile.cpp` and `NumberTheory.cpp` to `lift_common`, if they are not in it.

## Tasks
1. List the functions of each module from the PDB (`llvm-pdbutil dump -modules -symbols`, section of the module). Compare the names with `src/common/`.
2. Decompile the missing functions in batches to `.scratch/`. Lift them to C++ with the PDB types.
3. Add each new `.cpp` to `lift_common` in `CMakeLists.txt`.
4. Run `tools/gate.sh` after each module.

## Files
- `src/common/`
- `include/vs2010/`
- `include/pdb/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
