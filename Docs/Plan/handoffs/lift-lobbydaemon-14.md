# lift-lobbydaemon-14: LobbyDB part 1

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). Pseudocode from the indexed cache and the PDB types. IDA was not opened.
The card index has 14 functions (RVA `0x9fdb0` to `0xa4150`). 11 are lifted. 3 are Not done.
Branch base: main 75f0769. The lift was built in 5 checkpoints. This run checked them against the card index and finished the 2 functions that no checkpoint covered.

## Result

| Item | Value |
| --- | --- |
| Lifted | 11 |
| Not done | 3 |
| Gate (`tools/gate.sh`, `LIFT_BUILD_DIR=build-ld-14`) | gate ok |
| Parity (`tools/parity.sh`) | parity ok |
| LobbyDaemon MATCH, baseline (main 75f0769) | 195 (paired 281) |
| LobbyDaemon MATCH, final | 216 (paired 307) = +21 |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |

The gain is 6 card functions and 15 shared `Db::*` functions. All 21 are new pairs.

| Group | New MATCH |
| --- | --- |
| Card (6) | `AutoDbTran::~AutoDbTran`, `LobbyDB::UpdateLastLogout`, `CheckValidityOfCharacterName`, `TryCharacterCreation`, `FinishCharacterCreation`, `CancelCharacterCreation` |
| Shared (15) | `Db::AllocTransaction`, `Db::ConvertTime`, `Db::Log`, `Db::ReleaseTransaction`, `Db::errorLog`, `DbTransaction::BindParam`, `Execute`, `Fetch`, `Prepare`, `close`, `connect`, `connectionErrorLog`, `initStatement`, `initialize`, `statmentErrorLog` |

## Checkpoint check

| Check | Result |
| --- | --- |
| Rows in checkpoints 1 to 5 | 14 rows. No row is listed twice. |
| Rows match the index | 12 of 14. Rows `0xa2440` and `0xa29d0` are not function starts (interior blocks of `LoadCharacterList` and `LoadGameWorldCluster`). They are not in `index.tsv`. They are dropped. |
| Index functions with no row | `LoadGameWorldCluster` `0xa24c0` and `LoadGameWorld` `0xa2dd0`. Lifted in this run. |
| Card address `0xa0a50` | Wrong. The PDB function starts at `0xa0a40`. |
| Saved diff | `LobbyDB.cpp` and `LobbyDB.h` only. The source and build inputs match the commit. |

## Lifted

| RVA | Function | Funcdiff score | MATCH |
| --- | --- | ---: | --- |
| `0x9fdb0` | `AutoDbTran::~AutoDbTran` | 100.0 | yes |
| `0x9fe00` | `LobbyDB::LoadGameAccount` | 78.9 | no |
| `0xa0a40` | `LobbyDB::UpdateGameAccountTimeBasedPlayInfo` | 97.4 | no |
| `0xa1580` | `LobbyDB::UpdateLastLogout` | 100.0 | yes |
| `0xa17f0` | `LobbyDB::LoadCharacterList` | 78.1 | no |
| `0xa24c0` | `LobbyDB::LoadGameWorldCluster` | 84.2 | no |
| `0xa2dd0` | `LobbyDB::LoadGameWorld` | 77.5 | no |
| `0xa37e0` | `LobbyDB::CheckValidityOfCharacterName` | 100.0 | yes |
| `0xa39b0` | `LobbyDB::TryCharacterCreation` | 100.0 | yes |
| `0xa3da0` | `LobbyDB::FinishCharacterCreation` | 100.0 | yes |
| `0xa4150` | `LobbyDB::CancelCharacterCreation` | 100.0 | yes |

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| `0xa03e0` | `LobbyDB::LoadGameAccountTimeBasedPlayInfo` | Needs `LobbyDaemon::_instance`, `_timeBasedPlaySeasonSchedule` and `TimeBasedPlaySeasonSchedule::Data::GetNextResetTimeUTC`. `LobbyDaemon.h` has no layout. Cards ld-15 and ld-20 add it. The stub stays. ❓ |
| `0xa0eb0` | `LobbyDB::RegisterGameAccount` | Needs `LobbyDaemon::_instance->_config` (`_storeUserIpAddress`, `_storeGameAccountName`). `LobbyDaemon.h` and `LobbyConfig.h` have no layout. The stub stays. ❓ |
| `0xa12a0` | `LobbyDB::UpdateLastLogin` | Needs `LobbyDaemon::_instance->_config->_storeUserIpAddress`. Same missing layout. The stub stays. ❓ |

## Dead-strip

The 10 `LobbyDB` card functions have only stub callers. Each has `#pragma comment(linker, "/INCLUDE:...")` with the decorated PDB name and the caller RVA. `AutoDbTran::~AutoDbTran` needs none: the kept functions reach it. The verify card removes the pragmas.

| Function | Caller kept for |
| --- | --- |
| `LoadGameAccount` | `CliSession::login` `0x33f00` |
| `UpdateGameAccountTimeBasedPlayInfo` | `CliSession::UpdateAccountData` `0x38500` |
| `UpdateLastLogout` | `CliSession::logout` `0x34750` |
| `LoadCharacterList` | `CliSession::loadDB` `0x349a0` |
| `LoadGameWorldCluster`, `LoadGameWorld` | `GameWorldRegistry::Setup` `0x4ed00` |
| `CheckValidityOfCharacterName` | `CreateCharacterJob::init` `0x41b10` |
| `TryCharacterCreation`, `FinishCharacterCreation`, `CancelCharacterCreation` | `Character::TryCreation` `0x31550`, `FinishCreation` `0x319b0`, `CancelCreation` `0x31c00` |

## Codegen trials

3 trials, 3 kept. Details are in `Docs/Parity/lessons.md`, section ld-14.

| Function | Trial | Score |
| --- | --- | --- |
| `UpdateLastLogout` | A8: compare with `ID128_ID_ZERO` | 97.4 -> 100 |
| `TryCharacterCreation` | A8: same, both ids | 97.4 -> 100 |
| `FinishCharacterCreation` | A17: explicit `if (dbrtn == 0) return true; return false;` | 99.1 -> 100 |

Not tried (limit of 3 trials):

| Function | Score | Idea |
| --- | ---: | --- |
| `UpdateGameAccountTimeBasedPlayInfo` | 97.4 | Same A8 `ID128_ID_ZERO` form as the 3 kept trials. The refs diff is identical. |
| `LoadGameAccount`, `LoadCharacterList` | 78.9, 78.1 | A8 `ID128_ID_ZERO`. Then a `static __forceinline` BindCol helper with one shared error tail (A10, A17). The original has one `statmentErrorLog` call for all bind-column errors. |
| `LoadGameWorldCluster`, `LoadGameWorld` | 84.2, 77.5 | The same BindCol helper. Both are below the 85 % threshold. |

## Safety differences

| Function | Difference |
| --- | --- |
| `LoadCharacterList` (`0xa17f0`) | The showcase `memcpy` is limited to the 512 byte bound buffer. The original copies `showcaseSize` bytes with no limit. The showcase allocation result is checked before the copy. |
| `LoadGameWorldCluster`, `LoadGameWorld` | None. The lift keeps the original allocation and copy code. The `// BUG:` comments mark two copied log texts: "load game world group" and "load character list". |

## Notes

- `LobbyDB::CheckValidityOfCharacterName` does not read its third argument. The PDB keeps it.
- `LobbyDB::TryCharacterCreation` keeps the PDB signature. LTCG folds the `right` argument to 1 in the binary. The lift binds the argument. `Character::TryCreation` passes 1.
- `vendor/zstd/src` was copied from the `lift-lobbydaemon-12` worktree (HEAD bb6eaf64). It is not committed.
