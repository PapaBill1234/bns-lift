# lift-lobbydaemon-11: LobbyService part 2 and LobbyLocale

Source: LobbyDaemon 2019 + PDB. The lift uses the indexed pseudocode cache and the PDB types. IDA was not opened. The card has 33 function RVAs. All 33 are lifted. Not done is 0. The count excludes the scalar deleting destructor at `0x70840`.

## Coverage check

| Check | Result |
| --- | --- |
| Checkpoint rows (`build-ld-11/checkpoint-1..5.tsv`) | 33 rows, all `lifted` |
| Card index rows | 33 |
| Missing RVAs | 0 |
| Duplicate or overlapping RVAs | 0 |
| `/INCLUDE` names found in `build-vs2010/LobbyDaemon.pdb` | 27 of 27 (all card pragmas in `src/Server/LobbyDaemon/*.cpp`, checked with `grep -a -F`) |

## Lifted

Scores come from `build-vs2010/LobbyDaemon.funcdiff.json` of the final run. "Not paired" means that the function is not in the funcdiff output. "Folded" means that the PDB has the name, but `/OPT:ICF` gave it the same address as another function (`llvm-pdbutil dump --publics`).

| Module | RVA | Function | Score | Status |
| --- | --- | --- | ---: | --- |
| LobbyService | `0x6edf0` | `RenameUserService::Finish` | 63.7 | DIFF |
| LobbyService | `0x6ef90` | `ExtendJumpingCharacterCreationQuotaService::Setup` | 100.0 | MATCH |
| LobbyService | `0x6f000` | `ExtendJumpingCharacterCreationQuotaService::Fetch` | - | folded into `0x70900` |
| LobbyService | `0x6f1b0` | `ExtendJumpingCharacterCreationQuotaService::Start` | 40.7 | DIFF |
| LobbyService | `0x6f360` | `ExtendJumpingCharacterCreationQuotaService::ConsumeItemTried` | 59.9 | DIFF |
| LobbyService | `0x6f560` | `ExtendJumpingCharacterCreationQuotaService::TaskDone` | 63.1 | DIFF |
| LobbyService | `0x6f760` | `ExtendJumpingCharacterCreationQuotaService::ConsumeItemFinished` | 63.1 | DIFF |
| LobbyService | `0x6f960` | `ExtendJumpingCharacterCreationQuotaService::Finish` | 63.1 | DIFF |
| LobbyService | `0x6fb60` | `ChangeCharacterSexService::Setup` | 100.0 | MATCH |
| LobbyService | `0x6fc10` | `ChangeCharacterSexService::Fetch` | - | folded into `0x70900` |
| LobbyService | `0x6fe20` | `ChangeCharacterSexService::Start` | 52.4 | DIFF |
| LobbyService | `0x70040` | `ChangeCharacterSexService::ConsumeItemTried` | 59.9 | DIFF |
| LobbyService | `0x70240` | `ChangeCharacterSexService::TaskDone` | 63.1 | DIFF |
| LobbyService | `0x70440` | `ChangeCharacterSexService::ConsumeItemFinished` | 63.1 | DIFF |
| LobbyService | `0x70640` | `ChangeCharacterSexService::Finish` | 63.1 | DIFF |
| LobbyService | `0x70850` | `ChangeCharacterRaceService::Setup` | 100.0 | MATCH |
| LobbyService | `0x70900` | `ChangeCharacterRaceService::Fetch` | 0.0 | DIFF |
| LobbyService | `0x70b10` | `ChangeCharacterRaceService::Start` | 55.6 | DIFF |
| LobbyService | `0x70d50` | `ChangeCharacterRaceService::ConsumeItemTried` | 59.9 | DIFF |
| LobbyService | `0x70f50` | `ChangeCharacterRaceService::TaskDone` | 63.1 | DIFF |
| LobbyService | `0x71150` | `ChangeCharacterRaceService::ConsumeItemFinished` | 63.1 | DIFF |
| LobbyService | `0x71350` | `ChangeCharacterRaceService::Finish` | 63.1 | DIFF |
| LobbyService | `0xefb20` | `LobbyService::IsServiceTarget` | - | not paired (folded) |
| LobbyLocale | `0x57ab0` | `LobbyLocale::IsAllowedChar` | 99.3 | DIFF |
| LobbyLocale | `0x57d20` | `LobbyLocale::GetLanguageTypeOfChar` | 99.4 | DIFF |
| LobbyLocale | `0x57eb0` | `LobbyLocale::IsMonolingualString` | 96.3 | DIFF |
| LobbyLocale | `0x57fc0` | `LobbyLocale::IsSentenceCase` | 98.0 | DIFF |
| LobbyLocale | `0x580e0` | `LobbyLocale::IsWupperNotApplied` | 100.0 | MATCH |
| LobbyLocale | `0x58120` | `LobbyLocale::GetNextThaiCell` | 100.0 | MATCH |
| LobbyLocale | `0x58260` | `LobbyLocale::GetVietVowelType` | 100.0 | MATCH |
| LobbyLocale | `0x58460` | `LobbyLocale::GetVietToneMarkType` | 100.0 | MATCH |
| LobbyLocale | `0x584a0` | `LobbyLocale::GetStringLengthWithCellCombination` | 81.5 | DIFF |
| LobbyLocale | `0x585d0` | `IsVietnamese` | 100.0 | MATCH |

## Not done

None. All 33 RVAs are lifted.

## Known gaps in the lifted code

| Item | Functions | Reason |
| --- | --- | --- |
| No client session key in logs (safety difference, see below) | 16 Start, ConsumeItemTried, TaskDone, ConsumeItemFinished and Finish functions (45 log calls) | The lift does not write `cli-key:0x%I64X` and `owner->_clikey`. One shared `// LIFT:` note at the top of `LobbyService.cpp` covers all 45 calls. Each function also has its own `// LIFT:` note. The client cannot see this change. It costs the calls, consts and refs signals (scores near 60). The lift does not log session keys or other secrets. This is a deliberate safety difference. |
| Three derived `Fetch` functions score 0.0 | `0x6f000`, `0x6fc10`, `0x70900` | Cause: each one calls `LobbyService::Fetch` (`0x6c330`) first. `0x6c330` is still a `LIFT_STUB` (Not done in lift-lobbydaemon-6). /LTCG sees that the stub does not return, so it removes the rest of each caller. Then `/OPT:ICF` folds the three callers into one body at one address. Funcdiff scores the folded body as `ChangeCharacterRaceService::Fetch`. Fix: lift `0x6c330`. `__declspec(noinline)` on the stub was tried. It does not help (see trial 4). |
| `LobbyService::IsServiceTarget` not paired | `0xefb20` | The body is `return false`. The linker folds it. IDA shows the folded body as `WinServiceConsole::IsServiceTarget`. |
| Kanji table form | `IsAllowedChar`, `GetLanguageTypeOfChar` | The original uses one byte table `byte_140161BD0` (kanji, French, German, Brazilian Portuguese at offsets `0x5200`, `0x52C0`, `0x5300`). The lift uses a bit table for kanji and three small tables. This is the last consts gap (98). One shared byte table is a suggestion for a later round. |
| `// BUG:` marks, original behavior kept | the three `Setup` functions, `IsVietnamese` (`0xaea7`) | The lift keeps the original behavior and marks it. |

## Safety differences

These differences are deliberate. The lift keeps them. A missing MATCH or a branch difference that comes only from one of them is not a problem.

| # | Function (RVA) | Original | Lift | Effect on funcdiff |
| --- | --- | --- | --- | --- |
| 1 | 16 Start, ConsumeItemTried, TaskDone, ConsumeItemFinished and Finish functions (`0x6f1b0` to `0x71350`, 45 log and alert calls) | Writes `cli-key:0x%I64X` with `owner->_clikey` | Does not write the client session key. The rest of each message is the original text. | calls, consts and refs signals; scores near 60 |
| 2 | `ChangeCharacterSexService::Start` (`0x6fe20`) | Tests only `newAppearanceDataSize != 0` (`// BUG:`) | Rejects `newAppearanceDataSize <= 0` (input validation) | one branch; DIFF |
| 3 | `ChangeCharacterRaceService::Start` (`0x70b10`) | Tests only `newAppearanceDataSize != 0` (`// BUG:`) | Rejects `newAppearanceDataSize <= 0` (input validation) | one branch; DIFF |
| 4 | `GetThaiCharType`, inline in `GetNextThaiCell` (`0x58159`) | Wrong range test; can read past the table (`// BUG:`) | Reads the table only inside its bounds (bounds check) | none; `GetNextThaiCell` is MATCH |
| 5 | `LobbyLocale::GetNextThaiCell` (`0x58120`) | Tests only `strLen` | Also tests `str == nullptr` (input validation) | none; MATCH |
| 6 | `LobbyLocale::GetStringLengthWithCellCombination` (`0x584a0`) | Reads `str[0]` before any null test | Returns 0 for a null `str` before the loop (input validation). The in-loop `str + i` tests of the original stay. | small; 81.5 |

Skeptic 2 findings 1 to 5 ask to remove items 1 to 5. The verify round keeps them under the safety rule. Findings 6 (`this` null test in the log blocks) and 7 (in-loop `str + i` tests of `0x584a0`) are fixed. Finding 8 (DIFF functions at 90 or more in LobbyLocale) is a suggestion for a later parity round.

## Codegen trials

| # | Function | Change | Before | After | Kept |
| --- | --- | --- | ---: | ---: | --- |
| 1 | `IsSentenceCase` | Digit test `(c < L'0' \|\| c > L'9')` in place of `(unsigned short)(c - L'0') > 9` | 94.1 | 98.0 | yes |
| 2 | `IsMonolingualString` | Same digit test, digit test before the space test (both loops) | 88.9 | 96.3 | yes |
| 3 | `GetLanguageTypeOfChar` | `unsigned int` index for the Brazilian Portuguese table | 99.4 | 99.4 | no (reverted) |
| 4 | three derived `Fetch` | `__declspec(noinline)` on the `0x6c330` stub | 0.0 | 0.0 | no (reverted). The callers call the stub, but the code after the call is still removed and folded. |
| 5 | Sex and Race `Fetch` | Add `/INCLUDE` | not in PDB | in PDB, folded | yes |
| 6 | `GetStringLengthWithCellCombination` | Shape of the PDB line map (lines 635-669): `for` loop with `i += count`, `cell` at function scope, `str + i` tests in the Thai and Vietnamese branches, one `count <= 0` test. The safety null test before the loop stays. | 75.0 | 81.5 | yes |
| 7 | `GetStringLengthWithCellCombination` | Read `str[i]` in each range test in place of a local | 81.5 | 81.5 | no (reverted). The gap is the consts of the Thai range test (orig `0xe3a`, `0xe5b`; ours `0xe01`, `0xe3f`, `0x1c`). |
| 8 | 19 null-owner and compose-fail log blocks (`0x6edf0` to `0x71350`) | `Xxx const* s = this;` and `s != nullptr ? s->_db.field : 0` for each log argument (ld-2 form, macro `LOBBY_SERVICE_DB_LOG_ARGS`) | same | same | yes (source form of the original) |

Not tried:
- Make one shared byte table for the locale tables (large data change).
- Lift `0x6c330` (owned by lift-lobbydaemon-6, out of scope for this card).
- `GetStringLengthWithCellCombination` third form (max 3 forms). The consts gap is the Thai range test (see trial 7).

## Checks

| Run | Source | Result |
| --- | --- | --- |
| `tools/gate.sh` (`LIFT_BUILD_DIR=build-ld-11`) | uncommitted edits before trials | `gate ok` |
| `tools/parity.sh` | uncommitted edits before trials | `parity ok` |
| `tools/parity.sh` | trial build | `parity ok` |
| `tools/gate.sh` (`LIFT_BUILD_DIR=build-ld-11`) | repair 2 final candidate | `gate ok`, exit 0 |
| `tools/parity.sh` (`LIFT_BUILD_DIR=build-ld-11`) | repair 2 final candidate | `parity ok`, exit 0; LobbyDaemon paired 139 |

| Server | Baseline MATCH | Final MATCH | MATCH lost | Names gone |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 0 | 0 |
| LobbyGate | 658 | 658 | 0 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 | 0 |
| LobbyDaemon | 82 | 91 | 0 | 0 |

Eight of the 9 new LobbyDaemon MATCH names are card functions. The ninth is `LobbyDaemon::setArgument`. It is not a card function. No baseline, progress file or README table changed. No `--accept` ran.
