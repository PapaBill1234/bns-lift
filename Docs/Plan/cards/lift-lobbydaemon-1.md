# lift-lobbydaemon-1: Common: filters, FsdReader, missing functions

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/LobbyDaemon/<Module>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` |
| Wave | 1 |
| Model | opus |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Read sections A2 (block order), A6 (shared path literals), A21 (PDB facts), and A22 (per-exe source form) in `Docs/Parity/lessons.md`.
- Use the existing source files in Part A as patterns.
- No pattern file is available for the new modules.

## Modules

46 functions, about 2,179 pseudocode lines.

The ranges give inclusive function start RVAs. Use the module name and the RVA together.
Do not lift compiler-generated deleting destructors as separate functions.

### Part A: Missing functions in existing modules

18 functions, about 585 pseudocode lines.

| Module | Functions | Names and RVAs | Pattern |
| --- | ---: | --- | --- |
| `ContentsRuleConfigDefinition` | 4 | `ContentsRuleConfigReload::Load` at `0x29730`<br>`ContentsRuleConfig::ReloadContentsRuleConfig` at `0x29980`<br>`ContentsRuleConfig::UpdateReloadedVariable` at `0x2a090`<br>`ContentsRuleConfig::CompareMatch` at `0x2a210` | `src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp` |
| `SharedChannel` | 6 | `SharedChannel::Send` at `0x4b70`<br>`SharedChannel::Send` at `0x4ba0`<br>`SharedChannel::sendV` at `0x4c50`<br>`SharedChannelList::~SharedChannelList` at `0x4d20`<br>`SharedChannelList::Initialize` at `0x4d60`<br>`SharedChannelList::Set` at `0x4e20` | `src/Server/Shared/SharedChannel.cpp` |
| `NPChannel2` | 4 | `String::UnicodeToMultibyte` at `0x2700`<br>`Packet::FreeSize` at `0x29d0`<br>`EventObject::~EventObject` at `0x2a20`<br>`NPMsgHelper::LocaleHourToUTCTime` at `0x2be0` | `src/Server/Shared/NPChannel2.cpp` |
| `Db` | 1 | `Db::ConvertTimeStamp` at `0xe81f0` | `src/Server/BloodLib/source/Db.cpp` |
| `CryptoKey` | 2 | `BigInteger::BigInteger` at `0x10dfb0`<br>`BigInteger::~BigInteger` at `0x10dfe0` | `src/Security/source/BloodCrypto/key/CryptoKey.cpp` |
| `Network` | 1 | `Network::GetAddress` at `0xe4900` | `src/Server/BloodLib/source/Network.cpp` |

### Part B: New common modules

28 functions, about 1,594 pseudocode lines.

| Module | Scope | RVA range | Functions | Pseudocode lines |
| --- | --- | --- | ---: | ---: |
| `BannedWordFilterLib` | Whole module | `0x118a70` to `0x118e80` | 7 | 348 |
| `BannedWordFilterLoader` | Whole module | `0x118fa0` to `0x119720` | 8 | 392 |
| `ConstFilterChat` | Whole module | `0x119760` | 1 | 12 |
| `ConstFilterName` | Whole module | `0x119770` to `0x119870` | 2 | 264 |
| `FsdDecomposer` | Whole module | `0x119c10` to `0x11a040` | 6 | 403 |
| `PerfCounterProvider` | Whole module | `0xe7ae0` to `0x11f3a0` | 4 | 175 |

- `Program\External\BannedWordFilter` maps to `src/External/BannedWordFilter/`. The source folder name is not verified: `// ❓`.
- `Program\library\FsdReader` maps to `src/library/FsdReader/`. The source folder name is not verified: `// ❓`.
- Put `PerfCounterProvider.cpp` in `src/Server/BloodLib/source/`.

## Tasks

1. Use the listed exe and PDB only. Do not use `LobbyDaemon2019.exe` or a 381 file.
2. Use the index to select the functions in this card. Read their pseudocode. Use IDA only if the cached output is not sufficient. Close the database when you finish.
3. Use PDB types and names. Restore STL calls in place of inlined STL code.
4. Check each Part A function against the existing lift. Add only the functions in the table. Replace stub bodies where they exist. Keep the existing LobbyGate behavior.
5. Lift all six Part B modules. Use the PDB object paths to check the proposed source folders.
6. Check that `lift-lobbydaemon-0` added the six new source files to `lift_common` in `CMakeLists.txt`. Add a file only if it is not there. Keep the order of the existing objects.
7. Run `tools/gate.sh` after each module.
8. Compare `tools/funcdiff.py` results with the pre-card baseline. Use the same build settings for both runs. Check function identities as well as counts for the four earlier servers.

## Files

- `src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp`
- `src/Server/Shared/SharedChannel.cpp`
- `src/Server/Shared/NPChannel2.cpp`
- `src/Server/BloodLib/source/Db.cpp`
- `src/Security/source/BloodCrypto/key/CryptoKey.cpp`
- `src/Server/BloodLib/source/Network.cpp`
- `src/External/BannedWordFilter/BannedWordFilterLib.cpp`
- `src/External/BannedWordFilter/BannedWordFilterLoader.cpp`
- `src/External/BannedWordFilter/ConstFilterChat.cpp`
- `src/External/BannedWordFilter/ConstFilterName.cpp`
- `src/library/FsdReader/FsdDecomposer.cpp`
- `src/Server/BloodLib/source/PerfCounterProvider.cpp`
- `CMakeLists.txt`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-1.md`.
List the modules and functions that you lifted. List each remaining function under "Not done" with its RVA and the reason.
Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon lose no MATCH functions.
- The LobbyDaemon MATCH count does not decrease.
