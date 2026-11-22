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
| LobbyDaemon MATCH, final | 460 (+24) |
| Card functions at MATCH | 22 of 26 |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |

LobbyDaemon parity: 460/2204 = 20.9 %. Paired 585, mean score 96.1.
The +24 are 22 card functions and 2 functions that are not on this card: `Character::SetLevel` and `Character::SetSlotId`. Both became MATCH once the lifted `LobbyDB` functions they call were linked and paired.
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
| `0xa4d30` | `LobbyDB::RetrieveExpiredDeletionWaitingList` | 89.2 | no |
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
| `0xa70b0` | `LobbyDB::LoadJumpingCharacterCreationQuota` | 98.0 | no |
| `0xa7570` | `LobbyDB::BindCharacterSlot` | 100.0 | yes |
| `0xa77e0` | `LobbyDB::UpdateJumpingCharacterStateComplete` | 100.0 | yes |
| `0xa79f0` | `LobbyDB::LoadGameAccounExpInfo` | 86.5 | no |
| `0xa7e90` | `LobbyDB::RegisterGameAccountExpInfo` | 100.0 | yes |
| `0xa81e0` | `LobbyDB::UpdateGameAccountExpInfo` | 100.0 | yes |
| `0xa84f0` | `LobbyDB::LoadGameAccountContentQuotaList` | 80.6 | no |
| `0xa8a00` | `LobbyDB::UpdateGameAccountContentQuota` | 100.0 | yes |

## Not done

None.

## Remaining DIFF (not Not done)

| RVA | Function | Score | Cause |
| --- | --- | ---: | --- |
| `0xa4d30` | `RetrieveExpiredDeletionWaitingList` | 89.2 | Not tried. Fetch loop and vector growth forms differ. |
| `0xa70b0` | `LoadJumpingCharacterCreationQuota` | 98.0 | Not tried. Ours has 1 extra `DbTransaction::Fetch` call, and `ID128_ID_ZERO` ref order differs. Fetch loop form. |
| `0xa79f0` | `LoadGameAccounExpInfo` | 86.5 | Not tried. Same family. |
| `0xa84f0` | `LoadGameAccountContentQuotaList` | 80.6 | Not tried. Vector loop form. |

## Changes beyond the stub bodies

| File | Change |
| --- | --- |
| `LobbyDB.h` | `EndWaitDeletionInfo` (PDB UDT, 0x20 bytes). 7 new declarations: `RetrieveExpiredDeletionWaitingList`, `LoadJumpingCharacterCreationQuota`, `LoadGameAccounExpInfo`, `RegisterGameAccountExpInfo`, `UpdateGameAccountExpInfo`, `LoadGameAccountContentQuotaList`, `UpdateGameAccountContentQuota` (names checked against the PDB publics). Includes `StlMemory.h`, `StringUtil.h`, `<vector>`. |
| `LobbyDB.cpp` | 24 `/INCLUDE` pragmas (dead-strip rule). The callers are still `LIFT_STUB` bodies. Each pragma names its caller RVA. |

Without the pragmas, the build had +3 MATCH. With them, +21. The 3 codegen trials gave +3 more (+24).

## Codegen trials (limit 3)

| Function | Form | Result |
| --- | --- | --- |
| `UpdateCharacterLevel` `0xa5ca0` | `if (dbrtn == 0) return true; return false;` instead of `return dbrtn == 0;` (A17, ld-15) | 98.9 -> 100 |
| `UpdateCharacterData` `0xa58b0` | same | 99.0 -> 100 |
| `RegisterGameAccountExpInfo` `0xa7e90` | same | 99.0 -> 100 |

Not tried (trial limit): `RetrieveExpiredDeletionWaitingList`, `LoadJumpingCharacterCreationQuota`, `LoadGameAccounExpInfo`,
`LoadGameAccountContentQuotaList`. The same early-return form was not applied to the 4 functions above, which have a different tail.
`LoadGameAccountContentQuotaList` is below 85 %, so no trial was due by the card rule.

## Safety differences

None found in this card. The null-pointer tests on output arguments (`until`, `outGuildid`, `outRenamekey`) are in the original
(`HR` `LobbyDB.c`, `TryGuildRegistration`). The execute-fail log of `UpdateCharacterData` keeps the original stray arguments (`// LIFT:`).
No key or secret is logged.

## Environment

The worktree had no ignored `vendor/zstd/src`. The first `tools/parity.sh` failed on all 5 links (`ZSTD_*` unresolved).
The source was copied from `/home/ubuntu/Documents/Codex/private-project/bns-lift/vendor/zstd/src` (bb6eaf64). It is not tracked.
`vendor/zstd` is unchanged.
