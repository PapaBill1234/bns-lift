# lift-gamedaemon-9: Shared gaps and BloodLib: channel

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W1 |
| Model | opus |
| Depends on | `lift-gamedaemon-2`, `lift-gamedaemon-8` |
| Pattern | `src/Server/BloodLib/source/Channel.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/BloodLib/source/Channel.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

24 functions, about 979 pseudocode lines (about 7,832 tokens). Stems: `channel`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x699ea0` | `Channel::MakeSession` | channel | 51 |
| 2 | GD | `0x69a3e0` | `DaemonChannel::Send` | channel | 20 |
| 3 | GD | `0x69a440` | `DaemonChannel::Send` | channel | 15 |
| 4 | GD | `0x69a4c0` | `DaemonChannel::Send` | channel | 20 |
| 5 | GD | `0x69a540` | `ClientSideHashedDaemonChannel::OnAccept` | channel | 15 |
| 6 | GD | `0x69a570` | `ClientSideHashedDaemonChannel::OnConnect` | channel | 18 |
| 7 | GD | `0x69a5c0` | `ClientSideDaemonChannel::~ClientSideDaemonChannel` | channel | 81 |
| 8 | GD | `0x69a740` | `ClientSideDaemonChannel::initialize` | channel | 22 |
| 9 | GD | `0x69a7e0` | `ClientSideDaemonChannel::initSession` | channel | 65 |
| 10 | GD | `0x69aa70` | `ClientSideHashedDaemonChannel::~ClientSideHashedDaemonChannel` | channel | 81 |
| 11 | GD | `0x69abf0` | `ClientSideHashedDaemonChannel::Send` | channel | 24 |
| 12 | GD | `0x69ac40` | `ClientSideHashedDaemonChannel::Send` | channel | 21 |
| 13 | GD | `0x69aca0` | `ClientSideHashedDaemonChannel::OnClose` | channel | 12 |
| 14 | GD | `0x69acc0` | `ClientSideHashedDaemonChannel::initialize` | channel | 22 |
| 15 | GD | `0x69ad60` | `ClientSideHashedDaemonChannel::initSession` | channel | 71 |
| 16 | GD | `0x69af30` | `ClientSideHashedDaemonChannel::getSession` | channel | 25 |
| 17 | GD | `0x69afb0` | `ClientSideHashedDaemonChannel::releaseSession` | channel | 8 |
| 18 | GD | `0x69b000` | `ServerSideDaemonChannel::~ServerSideDaemonChannel` | channel | 31 |
| 19 | GD | `0x69b0a0` | `ServerSideDaemonChannel::Initialize` | channel | 28 |
| 20 | GD | `0x69b170` | `ServerSideDaemonChannel::CloseAll` | channel | 33 |
| 21 | GD | `0x69b260` | `ServerSideDaemonChannel::onAccept` | channel | 47 |
| 22 | GD | `0x69b340` | `ServerSideDaemonChannel::onClose` | channel | 82 |
| 23 | GD | `0x69b4c0` | `ServerSideDaemonChannel::getSession` | channel | 103 |
| 24 | GD | `0x69b670` | `ServerSideDaemonChannel::releaseSession` | channel | 84 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `Channel::MakeSession` | `src/Server/BloodLib/source/Channel.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `ClientSideDaemonChannel::~ClientSideDaemonChannel` | `src/Server/BloodLib/source/Channel.cpp` | CacheGate | - |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/channel.cpp`
- `src/Server/GameDaemon/channel.h`
- `src/Server/BloodLib/source/Channel.cpp`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-9.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
