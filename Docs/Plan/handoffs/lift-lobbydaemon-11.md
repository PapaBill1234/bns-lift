# lift-lobbydaemon-11: LobbyService part 2 and LobbyLocale

Source: LobbyDaemon 2019 + PDB. The lift uses the indexed pseudocode cache and the PDB types. IDA was not opened. The card has 33 function RVAs. All 33 are lifted. Not done is 0. The count excludes the scalar deleting destructor at `0x70840`.

## Coverage check

| Check | Result |
| --- | --- |
| Checkpoint rows (`build-ld-11/checkpoint-1..5.tsv`) | 33 rows, all `lifted` |
| Card index rows | 33 |
| Missing RVAs | 0 |
| Duplicate or overlapping RVAs | 0 |
| `/INCLUDE` names found in `build-vs2010/LobbyDaemon.pdb` | 30 of 30 |

## Lifted

Scores come from `build-vs2010/LobbyDaemon.funcdiff.json` of the final run. "Not paired" means that the function is not in the funcdiff output.

| Module | RVA | Function | Score | Status |
| --- | --- | --- | ---: | --- |
| LobbyService | `0x6edf0` | `RenameUserService::Finish` | 63.7 | DIFF |
| LobbyService | `0x6ef90` | `ExtendJumpingCharacterCreationQuotaService::Setup` | 100.0 | MATCH |
| LobbyService | `0x6f000` | `ExtendJumpingCharacterCreationQuotaService::Fetch` | 0.0 | DIFF |
| LobbyService | `0x6f1b0` | `ExtendJumpingCharacterCreationQuotaService::Start` | 40.7 | DIFF |
| LobbyService | `0x6f360` | `ExtendJumpingCharacterCreationQuotaService::ConsumeItemTried` | 59.9 | DIFF |
| LobbyService | `0x6f560` | `ExtendJumpingCharacterCreationQuotaService::TaskDone` | 63.1 | DIFF |
| LobbyService | `0x6f760` | `ExtendJumpingCharacterCreationQuotaService::ConsumeItemFinished` | 63.1 | DIFF |
| LobbyService | `0x6f960` | `ExtendJumpingCharacterCreationQuotaService::Finish` | 63.1 | DIFF |
| LobbyService | `0x6fb60` | `ChangeCharacterSexService::Setup` | 100.0 | MATCH |
| LobbyService | `0x6fc10` | `ChangeCharacterSexService::Fetch` | - | not paired |
| LobbyService | `0x6fe20` | `ChangeCharacterSexService::Start` | 52.4 | DIFF |
| LobbyService | `0x70040` | `ChangeCharacterSexService::ConsumeItemTried` | 59.9 | DIFF |
| LobbyService | `0x70240` | `ChangeCharacterSexService::TaskDone` | 63.1 | DIFF |
| LobbyService | `0x70440` | `ChangeCharacterSexService::ConsumeItemFinished` | 63.1 | DIFF |
| LobbyService | `0x70640` | `ChangeCharacterSexService::Finish` | 63.1 | DIFF |
| LobbyService | `0x70850` | `ChangeCharacterRaceService::Setup` | 100.0 | MATCH |
| LobbyService | `0x70900` | `ChangeCharacterRaceService::Fetch` | - | not paired |
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
| LobbyLocale | `0x584a0` | `LobbyLocale::GetStringLengthWithCellCombination` | 75.0 | DIFF |
| LobbyLocale | `0x585d0` | `IsVietnamese` | 100.0 | MATCH |

## Not done

None. All 33 RVAs are lifted.

## Known gaps in the lifted code

| Item | Functions | Reason |
| --- | --- | --- |
| No client session key in logs | 16 Start, ConsumeItemTried, TaskDone, ConsumeItemFinished and Finish functions (45 log calls) | The lift does not write `cli-key:0x%I64X` and `owner->_clikey`. This follows ld-6. It costs the calls, consts and refs signals (scores near 60). Restoring the key is a user decision. It was not tried. |
| `ExtendJumping...::Fetch` score 0.0 | `0x6f000` | Funcdiff finds no shared signal. The cause is not checked ❓. |
| Sex and Race `Fetch` not paired | `0x6fc10`, `0x70900` | No `/INCLUDE` and no lifted caller, so `/OPT:REF` drops them. |
| `LobbyService::IsServiceTarget` not paired | `0xefb20` | The body is `return false`. The linker folds it. IDA shows the folded body as `WinServiceConsole::IsServiceTarget`. |
| Kanji table form | `IsAllowedChar`, `GetLanguageTypeOfChar` | The original uses one byte table `byte_140161BD0` (kanji, French, German, Brazilian Portuguese at offsets `0x5200`, `0x52C0`, `0x5300`). The lift uses a bit table for kanji and three small tables. This is the last consts gap (98). |
| `// BUG:` marks kept | Sex and Race `Start` (`newAppearanceDataSize`), the three `Setup` functions, `IsVietnamese` (`0xaea7`) | The lift keeps the original behavior and marks it. |
| Corrected range check | `GetThaiCharType` (inline in `GetNextThaiCell`, `0x58159`) | The original range test is wrong. The lift uses the table bounds and marks it `// BUG:`. `GetNextThaiCell` still matches. |

## Codegen trials

| # | Function | Change | Before | After | Kept |
| --- | --- | --- | ---: | ---: | --- |
| 1 | `IsSentenceCase` | Digit test `(c < L'0' \|\| c > L'9')` in place of `(unsigned short)(c - L'0') > 9` | 94.1 | 98.0 | yes |
| 2 | `IsMonolingualString` | Same digit test, digit test before the space test (both loops) | 88.9 | 96.3 | yes |
| 3 | `GetLanguageTypeOfChar` | `unsigned int` index for the Brazilian Portuguese table | 99.4 | 99.4 | no (reverted) |

Not tried:
- Restore the client session key in the 45 log calls (user decision).
- Make one shared byte table for the locale tables (large data change).
- Add `/INCLUDE` for the Sex and Race `Fetch` functions.
- Check the `ExtendJumping...::Fetch` 0.0 score.
- `GetStringLengthWithCellCombination` consts 25. The detail tool (`funcdiff.py --show`) did not run in this session.

## Checks

| Run | Source | Result |
| --- | --- | --- |
| `tools/gate.sh` (`LIFT_BUILD_DIR=build-ld-11`) | uncommitted edits before trials | `gate ok` |
| `tools/parity.sh` | uncommitted edits before trials | `parity ok` |
| `tools/parity.sh` | trial build | `parity ok` |
| `tools/gate.sh` and `tools/parity.sh` | final commit | see below |

| Server | Baseline MATCH | Final MATCH | MATCH lost | Names gone |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 0 | 0 |
| LobbyGate | 658 | 658 | 0 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 | 0 |
| LobbyDaemon | 82 | 91 | 0 | 0 |

Eight of the 9 new LobbyDaemon MATCH names are card functions. The ninth is `LobbyDaemon::setArgument`. It is not a card function. No baseline, progress file or README table changed. No `--accept` ran.
