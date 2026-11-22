# lift-lobbydaemon-7: CliSession part 2

Source: LobbyDaemon 2019 + PDB. This handoff covers all 32 `CliSession` entries from `0x35fc0` through `0x392c0` in the function index. Each entry occurs once. This card lifts 17 bodies. It leaves 9 stubs and 6 functions without a declaration or body. No IDA session or live server test ran.

## Files

| File | Purpose |
| --- | --- |
| `src/Server/LobbyDaemon/CliSession.cpp` | Lift the listed bodies. |
| `src/Server/LobbyDaemon/CliSession.h` | Declare the lifted methods that the skeleton did not declare. |
| `src/Server/LobbyDaemon/StsMsgGrade.h` | Define the PDB response types used by the lifted methods. |
| `src/Server/LobbyDaemon/LobbyService.h` | Add the PDB `GetDB()` accessor. Keep `_db` protected. |
| `Docs/Parity/lessons.md` | Record the code generation trials. |

## Lifted

All functions in this table belong to `CliSession`. The main baseline did not pair these functions.

| RVA | PDB name | Funcdiff score | MATCH |
| --- | --- | ---: | --- |
| `0x360a0` | `NotifyChangedGrade` | 85.7 | DIFF |
| `0x36170` | `NotifyChangedGradeLevel` | 88.9 | DIFF |
| `0x366e0` | `setContentBans` | 85.2 | DIFF |
| `0x36960` | `setRMSInquiryResult` | 100.0 | MATCH |
| `0x36df0` | `fetchContentBans` | 100.0 | MATCH |
| `0x373a0` | `addLobbyService` | 100.0 | MATCH |
| `0x37530` | `removeLobbyService` | 100.0 | MATCH |
| `0x37670` | `getLobbyServiceByType` | 100.0 | MATCH |
| `0x376b0` | `queryLobbyService` | 100.0 | MATCH |
| `0x37790` | `addRenameUserService` | 100.0 | MATCH |
| `0x379b0` | `FetchCharacterInfoList` | 98.0 | DIFF |
| `0x37af0` | `FetchCharacterInfo` | 97.0 | DIFF |
| `0x37c70` | `FetchServiceEntryList` | 98.0 | DIFF |
| `0x37de0` | `UpdateBotScore` | 100.0 | MATCH |
| `0x37eb0` | `BindCharacterSlot` | 73.3 | DIFF |
| `0x381c0` | `UpdateCharacterData` | 55.0 | DIFF |
| `0x38380` | `UpdateCharacterLevel` | 78.5 | DIFF |

The card lifts bodies, not their full call paths. Grade changes can reach a `GradeService` stub. The character slot and update paths still need the corresponding `LobbyDB` bodies. `UpdateCharacterData` calls `getCharacter` (`0x35cf0`) out of line, as the original does. That stub belongs to part 1. LTCG inlines the stub, so the rest of the body is dead code in our build. The score goes up when part 1 lifts `getCharacter`.

## Not done

All functions in this table belong to `CliSession`.

| RVA | PDB name | Reason |
| --- | --- | --- |
| `0x35fc0` | `cleanupCharge` | Needs the `LobbyDaemon` singleton and verified `_npServchmgr` and `_gameServChannel` layouts. |
| `0x36240` | `HandleGameGetGradeList` | Needs `GamedChannel` and `TransactionChannel` layouts for `_rawChannel` and `SharedChannel::Send`. |
| `0x36a50` | `setUserPromotionStatus` | Needs the `LobbyDaemon` singleton, schedule layout, and STS response type. |
| `0x36fa0` | `fetchAccountContentQuotaList` | `LobbyDB` has no quota loader. |
| `0x371b0` | `fetchAccountRecycleTimeList` | `LobbyDB` has no recycle-time loader. |
| `0x37890` | `setScheduledEndTime` | The node type and release operation are incomplete. |
| `0x37950` | `releaseScheduledEndTime` | The source lacks scheduler access. `Unschedule` is a stub. |
| `0x38500` | `UpdateAccountData` | Needs the LobbyDaemon `ContentsRuleConfig` dependency. |
| `0x38670` | `UpdateTimeBasedPlayReward` | Needs the reward and schedule layouts. |
| `0x38930` | `UpdateAccountExp` | Needs verified config and database declarations. |
| `0x38b50` | `UpdateAccountContentQuota` | `LobbyDB` lacks the quota update method. |
| `0x38cc0` | `UpdateAccountRecycleTime` | `LobbyDB` lacks `UpdateGameAccountRecycleTime`. |
| `0x38e30` | `GetGameWorldWaitInfo` | Needs the `WaitInfo` layout and `GameWorldCluster::getWaitInfo`. |
| `0x38f60` | `EndWaitCharacterDeletion` | `removeCharacter` is a stub. `LobbyDaemon` lacks the channel manager member. |
| `0x392c0` | `NotifyGoodsInventoryChangedAlongPresence` | Needs the notification parameter layout and channel manager members. `getPlayingCharacter` is a stub. |

## Safety differences

| RVA | PDB name | Difference | Effect on funcdiff |
| --- | --- | --- | --- |
| `0x381c0` | `UpdateCharacterData` | The original tests only `showcaseSize != 0`. The lift also rejects a negative size or a size above `0x200`, the same bound as `Character::SetShowcase` (`0x32510`). The invalid-parameter path logs and returns `false`, as the original does. | One extra constant `0x1ff`. |

## Code generation

See `Docs/Parity/lessons.md`, section `ld-7`. The two inline-depth trials reduced the caller scores. The state-order trial did not change the score. The final source does not use those forms.

The `ID128_ID_ZERO` comparisons improve the scores of `FetchCharacterInfo` and `BindCharacterSlot`. The four callers that use `GetDB()` still match. The resumed run checked the three DIFF functions above 85 % that had no trial:

| Function | Score | Cause | Action |
| --- | ---: | --- | --- |
| `NotifyChangedGrade` | 85.7 | LTCG inlines the `GradeService::ApplyChangedGrade` stub (`abort`). | None. The score goes up when the `GradeService` card lands. |
| `NotifyChangedGradeLevel` | 88.9 | The code is the same as the original, instruction for instruction. Funcdiff drops `0x40000` in the original because the value is below the original image size (RVA filter). Our image is smaller, so the value stays a constant. | None in source. Tool noise. |
| `setContentBans` | 85.2 | Our build inlines `push_back`. The original calls it out of line. | A20 trial: 85.2 → 91.7, reverted. See lessons. |

`UpdateCharacterLevel` (78.5), `BindCharacterSlot` (73.3), and `UpdateCharacterData` (55.0) are below 85 %. They got no trial.

## Checks

`tools/gate.sh` printed `gate ok`. `tools/parity.sh` printed `parity ok`. Both used `LIFT_BUILD_DIR=build-ld-7`. The zstd source is at `bb6eaf64`. The rebuilt LobbyDaemon PDB contains all 16 card retention names. The baseline is main at `5627050`. No baseline changed.

| Server | Baseline MATCH | Final MATCH | Gain | Parity |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 0 | 92.9% |
| LobbyGate | 658 | 658 | 0 | 89.0% |
| SmartCouponDaemon | 630 | 630 | 0 | 94.2% |
| PostOfficeDaemon | 694 | 694 | 0 | 91.4% |
| LobbyDaemon | 82 | 106 | 24 | 4.8% |

No baseline MATCH name changed to DIFF or disappeared. Eight new matches are in this card. Sixteen are outside the card.
