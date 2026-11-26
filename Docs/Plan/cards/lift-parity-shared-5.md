# lift-parity-shared-5: Shared library: crypto, BloodLib, EH state -2

Repo: bns-lift (PUBLIC). Never commit binaries, PDBs, IDA databases or abuse notes. IDA only when the pseudocode, the PDB line map and funcdiff are not enough (`<work-root>/ida/lift/LobbyGate/LobbyGate.exe`). Close the database when you are done.

## Goal
The shared crypto and BloodLib DIFF functions are MATCH, or the handoff gives the cause of each. The shared library moves toward 99 %.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/review-4.md` (sections 5 and 6), `Docs/Parity/lessons.md` (the sections below, and B, C4, D) and `Docs/Parity/triage.md`.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function. This includes LobbyDaemon.
- LobbyDaemon is done by another system. Do not change `src/Server/LobbyDaemon/`. Its MATCH count must not drop.
- `Docs/Parity/excluded.tsv`, `Docs/Parity/baseline/` and `Docs/Parity/progress.tsv`: do not change them.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
  For a quick loop, use `tools/parity.sh <EXE>` (about 30 s) and the quick loop of lessons C4.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/`. PDB line maps: `LIFT_IDA_DIR=<work-root>/ida/lift tools/pdbq.py <EXE> lines <lo> <hi>` (A29).
- Main at review 4: CG 456/491 (92.9 %), LG 658/739 (89.0 %), SCD 630/669 (94.2 %), POD 694/759 (91.4 %). Goal: 95 % per exe
  (CG 467, LG 703, SCD 636, POD 722).
- Before a source change, read the PDB facts and the PDB line map of the function (A21, A29). On a `tls:` or vtable-name DIFF, check the tool output first (A1).
- This card runs in parallel with the other round-5 cards. Change only the files in "Files". Each card touches other files.
- Lessons for this card: A25 (BloodCrypto forms), A9 (crypto forms), A3 (closed-lib callers), A4 (`noinline`), A20 (`inline_depth(0)`), A14 (EH state -2, `::new`, global placement delete), A16 (allocation), A17 (error tails), C2 (`.tls` order), F "Placement delete and shared functions".
- Estimate (review-4 section 6): LG +8, SCD +4, POD +5, CG +1 (shared fixes count in each exe).
- Stop rule: stop a function after 3 tries with no score gain. Write it in the handoff. Do not try the stop list (lessons D) without a new idea.
- Named functions (exe, score, signals c=calls r=refs k=consts):
- Crypto (`src/Security/`): `BigInteger::invMod` LG/SCD/POD 83.1 (c59 k90; 2 tries in crypto-4, B), `BigInteger::InvMod` LG/SCD/POD 89.7 (c85 k84),
  `BigInteger::Divide` SCD/POD 76.7 and the LG overload `?Divide@BigInteger@@SAXPEBV1@0PEAV1@1@Z` 76.7 (c75 r67 k89),
  LG `BigInteger::IsPrime` 82.2 (r80 k67), LG `BigInteger::isPrimeMR` 88.4 (c81 k84), LG `Crypto::Create` 34.0 (c29 r40 k33),
  LG `Crypto::InstanceSize` 44.4 (r0 k33), LG `Dh::Process` 77.8 (c67 k67), LG `Dh::getValue` 98.0 (k94), LG `Dh::~Dh` 66.7 (r0: vtable ref),
  LG `BroadcastCrypt::Initialize` 95.6 (k87; ours +0x4, +0x60, 0x2840 against orig 0x2847, not tried), LG `BroadcastCrypt::clear` 85.7 (k57).
- EH state -2 (A14; fold of lift-parity-ehstate-4): `FragmentPacketConcatenater::Clone` LG/POD 93.3 (k80), LG `IdleWatcher::run` 96.3 (k89),
  POD `operator delete[]` 0.0 (compare with `src/crt/new_delete.c` and `include/vs2010/new`).
- BloodLib: `IoWorker::run` x4 84.9 (c69 r97 k88; `tls:` ref, see C2 first), POD `Channel::Send` 97.0 (c91), LG `AlertSender::init` 99.1 (r97),
  SCD `Session::Connect` 98.0 (k94; the original keeps a `reconnect` test; look at the callers, net-4 B).
- Misses (only in the original; `funcdiff.py <EXE> --build build-vs2010 --only`): `RefCntObject::operator delete` x4 (93 bytes; the original calls it
  out of line), CG `Packet::Concatenate` (310 bytes), POD `Packet::Decompose(uint,int,char const*,...)` (173 bytes), POD `DaemonConfig::Dump` (644 bytes; ours pairs no POD copy),
  LG `operator delete` and POD `??3@YAXPEAX@Z` (3 bytes, folded as `Console::Flush`). Each miss counts in the parity denominator.
- Stop list (do not try): `aes128Table*`, `Session::Session`, `StaticPageMemoryManager::Initialize`, `ThreadManager::Initialize`, `Daemon::Start`,
  `PipeConsole::*`, `WindowConsole::Open`, `Session::HandleEvent`, `Network::OpenPort`, `Rsa::decrypt`, `ZSTD_compressBegin_internal`.
- A change in `src/Server/BloodLib/` or `src/Security/` goes into each exe, LobbyDaemon too. Run the full `tools/parity.sh` (all 5 exes) after each kept change.
- The global placement `operator delete(void*, void*)` with the crash body is already lifted (beb4669). Do not add a second one.
- Do not change `wmain` or exe files. The exe cards own them (and the `wmain$dtor$0` misses).
## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. List the DIFF functions of your scope with score and signal.
2. Work in groups of functions with the same form: run `funcdiff.py --show`, read the pseudocode and the PDB line map, change the source, build, measure again.
3. Keep a change only if the MATCH count goes up and no exe loses a MATCH function. Undo a change that does not help.
4. Write each fix pattern that worked and each that did not work in the handoff, section `## Lessons`, with tables "worked" and "failed"
   (function, before, after, count). Do not edit `Docs/Parity/lessons.md`: the round-5 cards run in parallel, and the review merges the handoff lessons into A and B.
5. For each DIFF function of your scope that you cannot fix, write one line in the handoff: function, signal, cause, why you stopped.
   Write the MATCH count per exe before and after, and `Turns: <n>`, in the handoff.

## Files
- `src/Security/`
- `src/Server/BloodLib/source/IoWorkerThread.cpp`
- `src/Server/BloodLib/source/IdleWatcher.cpp`
- `src/Server/BloodLib/source/Channel.cpp`
- `src/Server/BloodLib/source/AlertSender.cpp`
- `src/Server/BloodLib/source/Session.cpp` (only `Session::Connect`)
- `src/Server/BloodLib/source/Security.cpp`
- `src/Server/BloodLib/source/RefCntObject.cpp`, `src/Server/BloodLib/source/Packet.cpp`, `src/Server/BloodLib/source/DaemonConfig.cpp` (only for the misses)
- `src/Server/BloodLib/include/`
- `src/Server/Packet/FragmentPacket.cpp` (only `FragmentPacketConcatenater::Clone`)
- `src/crt/new_delete.c`, `include/vs2010/new`
- `Docs/Plan/handoffs/lift-parity-shared-5.md`

## Done when
- Each named function is MATCH, or the handoff gives its cause.
- No exe loses a MATCH function (LobbyDaemon included).
- `tools/gate.sh` and `tools/parity.sh` pass.
