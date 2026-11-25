# lift-lobbydaemon-19: LobbyDB part 2

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). IDA was not opened.
The card has 26 functions (RVA `0xa4320` to `0xa8a00`). All 26 are lifted. 0 are Not done.

## Result

| Item | Value |
| --- | --- |
| Lifted | 26 |
| Not done | 0 |
| `tools/gate.sh` (`LIFT_BUILD_DIR=build-ld-19`) | gate ok |
| `tools/parity.sh` (same build, `VS2010_OUT=build-vs2010-ld-19`) | parity ok |
| LobbyDaemon MATCH, baseline (main 480a25b) | 436 |
| LobbyDaemon MATCH, final | 462 (+26) |
| Card functions at MATCH | 24 of 26 |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |

LobbyDaemon parity: 462/2204 = 21.0 %. Paired 585, mean score 96.2.
The +26 are 24 card functions and 2 functions that are not on this card: `Character::SetLevel` and `Character::SetSlotId`. Both became MATCH once the lifted `LobbyDB` functions they call were linked and paired.
Baseline files are unchanged. No `--accept` was run.

## Checkpoint check

| Check | Result |
| --- | --- |
| Rows in `checkpoint-1..4.tsv` | 8 + 7 + 6 + 5 = 26 |
| Overlap between checkpoints | none |
| Match with the card index (`index.tsv`, `LobbyDB`, `0xa4320` to `0xa8a00`) | 26 of 26, same RVA and name |
| Diff | only `LobbyDB.cpp` and `LobbyDB.h` |

## Lifted

Score = funcdiff score of the final VS2010 build.

| RVA | Function | Score | MATCH |
| --- | --- | ---: | --- |
| `0xa4320` | `LobbyDB::TryCharacterDeletion` | 100.0 | yes |
| `0xa44f0` | `LobbyDB::FinishCharacterDeletion` | 100.0 | yes |
| `0xa47c0` | `LobbyDB::CancelCharacterDeletion` | 100.0 | yes |
| `0xa4990` | `LobbyDB::TryCharacterRestoration` | 100.0 | yes |
| `0xa4b60` | `LobbyDB::FinishCharacterRestoration` | 100.0 | yes |
| `0xa4d30` | `LobbyDB::RetrieveExpiredDeletionWaitingList` | 97.8 | no |
| `0xa5220` | `LobbyDB::ExpireCharacterDeletionWaiting` | 100.0 | yes |
| `0xa53f0` | `LobbyDB::UpdateLastPlayStart` | 100.0 | yes |
| `0xa5690` | `LobbyDB::UpdateLastPlayEnd` | 100.0 | yes |
| `0xa58b0` | `LobbyDB::UpdateCharacterData` | 100.0 | yes |
| `0xa5ca0` | `LobbyDB::UpdateCharacterLevel` | 100.0 | yes |
| `0xa5f80` | `LobbyDB::TryGuildRegistration` | 100.0 | yes |
| `0xa6310` | `LobbyDB::FinishGuildRegistration` | 100.0 | yes |
| `0xa64e0` | `LobbyDB::CancelGuildRegistration` | 100.0 | yes |
| `0xa66b0` | `LobbyDB::DeleteGuild` | 100.0 | yes |
| `0xa68f0` | `LobbyDB::TryRenameGuild` | 100.0 | yes |
| `0xa6c60` | `LobbyDB::FinishRenameGuild` | 100.0 | yes |
| `0xa6ec0` | `LobbyDB::CancelRenameGuild` | 100.0 | yes |
| `0xa70b0` | `LobbyDB::LoadJumpingCharacterCreationQuota` | 100.0 | yes |
| `0xa7570` | `LobbyDB::BindCharacterSlot` | 100.0 | yes |
| `0xa77e0` | `LobbyDB::UpdateJumpingCharacterStateComplete` | 100.0 | yes |
| `0xa79f0` | `LobbyDB::LoadGameAccounExpInfo` | 100.0 | yes |
| `0xa7e90` | `LobbyDB::RegisterGameAccountExpInfo` | 100.0 | yes |
| `0xa81e0` | `LobbyDB::UpdateGameAccountExpInfo` | 100.0 | yes |
| `0xa84f0` | `LobbyDB::LoadGameAccountContentQuotaList` | 95.3 | no |
| `0xa8a00` | `LobbyDB::UpdateGameAccountContentQuota` | 100.0 | yes |

## Not done

None.

## Remaining DIFF (not Not done)

| RVA | Function | Score | Cause |
| --- | --- | ---: | --- |
| `0xa4d30` | `RetrieveExpiredDeletionWaitingList` | 97.8 | 2 call differences. The original calls `vector<LobbyService::DB*>::_Reserve` (the linker folded the identical `vector<Character*>` pointer-vector code, so the PDB name is another type). Ours calls the `EndWaitDeletionInfo*` one. The original calls `vector::clear` out of line. Ours inlines it (`memmove`). Both come from the stub callers: the vector code has few call sites in this build. Third form not tried: no honest source form changes the inline choice of a std member. |
| `0xa84f0` | `LoadGameAccountContentQuotaList` | 95.3 | The original calls `vector<AccountContentQuota>::push_back` out of line. Ours inlines it (2 `_Reserve` calls). Same cause: the other callers of this `push_back` are stubs. A `noinline` wrapper or an explicit specialisation would only fool funcdiff, so it is not used. |

## Changes beyond the stub bodies

| File | Change |
| --- | --- |
| `LobbyDB.h` | `EndWaitDeletionInfo` (PDB UDT, 0x20 bytes). 7 new declarations: `RetrieveExpiredDeletionWaitingList`, `LoadJumpingCharacterCreationQuota`, `LoadGameAccounExpInfo`, `RegisterGameAccountExpInfo`, `UpdateGameAccountExpInfo`, `LoadGameAccountContentQuotaList`, `UpdateGameAccountContentQuota` (names checked against the PDB publics). Includes `StlMemory.h`, `StringUtil.h`, `<vector>`. |
| `LobbyDB.cpp` | 24 `/INCLUDE` pragmas (dead-strip rule). Each pragma names the stub caller that keeps it needed (the lifted `Character::*` callers are dead-stripped too, because their own callers are stubs). The pragma of `UpdateCharacterData` was tested: without it the pair is lost (585 -> 584 paired, 461 MATCH), because the lifted `CliSession::UpdateCharacterData` calls the stub `CliSession::getCharacter` (0x35cf0) before it. |

Without the pragmas, the build had +3 MATCH. With them, +21. The A17 tail (3 functions) gave +3. The repairs gave +2 more
(+26 in total).

## Codegen trials (limit 3 forms per function)

| Function | Form | Result |
| --- | --- | --- |
| `UpdateCharacterLevel` `0xa5ca0` | 1: `if (dbrtn == 0) return true; return false;` (A17, ld-15) | 98.9 -> 100 |
| `UpdateCharacterData` `0xa58b0` | 1: same | 99.0 -> 100 |
| `RegisterGameAccountExpInfo` `0xa7e90` | 1: same | 99.0 -> 100 |
| `LoadJumpingCharacterCreationQuota` `0xa70b0` | 1: A17 tail, `ID128_ID_ZERO` copy (A8), do-while fetch loop. 2: `BindCol` member call for column 1 | 98.0 -> 100 with form 1. It fell to 97.3 when `LoadGameAccounExpInfo` changed. Form 2 gives 100 again |
| `LoadGameAccounExpInfo` `0xa79f0` | 1: A17 tail, A8, do-while. 2: `BindCol` member call for the 4 columns | 86.5 -> 88.4 -> 100 |
| `LoadGameAccountContentQuotaList` `0xa84f0` | 1: A17 tail, A8, do-while. 2: `BindCol` member call for the 5 columns | 80.6 -> 82.5 -> 95.3 |
| `RetrieveExpiredDeletionWaitingList` `0xa4d30` | 1: do-while fetch loop. 2: `BindCol` member call for the 3 columns | 89.2 -> 89.7 -> 97.8 |

Each of the 4 loaders used 2 of the 3 forms. No third form is left that is real source for the 2 that stay DIFF (see above).

## Safety differences

None found in this card. The null-pointer tests on output arguments (`until`, `outGuildid`, `outRenamekey`) are in the original
(`LobbyDB.c`, `TryGuildRegistration`). The execute-fail log of `UpdateCharacterData` keeps the original stray arguments (`// BUG:`, 0xa58b0).
No key or secret is logged.

## Environment

The worktree had no ignored `vendor/zstd/src`. The first `tools/parity.sh` failed on all 5 links (`ZSTD_*` unresolved).
The source was copied from `<lift-root>/vendor/zstd/src` (bb6eaf64). It is not tracked.
`vendor/zstd` is unchanged.
