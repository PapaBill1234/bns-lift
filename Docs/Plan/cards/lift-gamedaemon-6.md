# lift-gamedaemon-6: Shared gaps and FsdReader: numbertheory, biarithmetic, prng, fsdcomposer, ...

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
| Depends on | `lift-gamedaemon-0e` |
| Pattern | `src/Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

10 functions, about 2,265 pseudocode lines (about 18,120 tokens). Stems: `numbertheory`, `biarithmetic`, `prng`, `fsdcomposer`, `fsd`, `fsddecomposer`.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6e0480` | `BigInteger::InvMod` | numbertheory | 600 |
| 2 | GD | `0x6e1390` | `BigInteger::isPrimeMR` | numbertheory | 173 |
| 3 | GD | `0x6e17f0` | `BigInteger::invMod` | numbertheory | 696 |
| 4 | GD | `0x6e3220` | `BigInteger::Divide` | biarithmetic | 493 |
| 5 | GD | `0x6e3bf0` | `BigInteger::Divide` | biarithmetic | 60 |
| 6 | GD | `0x6e45e0` | `Prng::Initialize` | prng | 27 |
| 7 | GD | `0x6e9900` | `FsdComposer::ComposeV` | fsdcomposer | 154 |
| 8 | GD | `0x6e9be0` | `FsdComposer::Compose` | fsdcomposer | 10 |
| 9 | GD | `0x6ea0c0` | `Fsd::Compose` | fsd | 14 |
| 10 | GD | `0x6ea040` | `FsdDecomposer::GetString` | fsddecomposer | 38 |

### Shared functions

These functions are in shared source. They are not MATCH in each lifted exe that has them.

| PDB name | Shared file | Other exes | Note |
| --- | --- | --- | --- |
| `BigInteger::InvMod` | `src/Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp` | LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `BigInteger::isPrimeMR` | `src/Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp` | LobbyGate | - |
| `BigInteger::invMod` | `src/Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp` | LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `BigInteger::Divide` | `src/Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp` | LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `BigInteger::Divide` | `src/Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp` | LobbyGate, PostOfficeDaemon, SmartCouponDaemon | - |
| `Prng::Initialize` | `src/Security/source/BloodCrypto/math/prng/prng.cpp` | CacheGate, LobbyDaemon, LobbyGate, PostOfficeDaemon, SmartCouponDaemon | EXCLUDED in LobbyDaemon: read its `excluded.tsv` row first |
| `FsdDecomposer::GetString` | `src/library/FsdReader/FsdDecomposer.cpp` | LobbyDaemon | - |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Shared functions: fix them in the shared file. If GameDaemon needs another form, use a per-exe copy in `lift_common_gd` or a `LIFT_EXE_` wrapper (A22, pattern 35). The 5 other exes must keep each MATCH. A MATCH to DIFF change needs an `allow-worse.txt` row with the counts.
6. An EXCLUDED function has a proof that no honest source fix exists in that exe. Read the proof first. If the same cause applies to GameDaemon, write the function under "Not done" with the proof reference. Do not edit `excluded.tsv`.
7. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp`
- `src/Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp`
- `src/Security/source/BloodCrypto/math/prng/prng.cpp`
- `src/Server/GameDaemon/fsdcomposer.cpp`
- `src/Server/GameDaemon/fsdcomposer.h`
- `src/Server/GameDaemon/fsd.cpp`
- `src/Server/GameDaemon/fsd.h`
- `src/library/FsdReader/FsdDecomposer.cpp`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-6.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
