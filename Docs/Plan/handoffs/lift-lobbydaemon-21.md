# lift-lobbydaemon-21: LobbyGamePacketHandler part 2

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). Pseudocode: the indexed cache. IDA was not opened.
The card has 20 functions (`0x8c660` to `0x907e0`). 15 are lifted. 5 are Not done.
Base: 8cddc33 (main with card lift-lobbydaemon-16; LobbyDaemon 442 MATCH on main). The branch was rebased onto it (repair round 2).

## Result

| Item | Value |
| --- | --- |
| Lifted | 15 |
| Not done | 5 |
| Gate (`tools/gate.sh`, `LIFT_BUILD_DIR=build-ld-21`) | gate ok |
| Parity (`tools/parity.sh`) | parity ok |
| LobbyDaemon MATCH | 442 -> 461 (+19) over main (baseline 8cddc33) |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |
| Card 16 MATCH (`ServiceOpenNotify`, `UpdateBotScoreNotify`, `UpdateCharacterDataReq`, `Session::Send`, `Session::SendV`) | All kept (MATCH -> DIFF 0) |

No card handler is MATCH. The 19 new MATCH are shared functions that the handlers now reach:
`NPChannel::checkLibError`, `NPTransactionRegistry::Register`, 4 `Packet::Decompose` forms, `PacketBuffer::Decompose`,
`PacketDecomposer::Reset`, `PacketFormatIterator::CurrentFormat`, `Forward`, `Rewind`, `skipRepeatFormat`,
`RepeatPacketDecomposer::Reset`, `SharedChannel::IsConnected`, `String::UnicodeToMultibyte`, the 3 `_StsMsgRequest` virtuals
and `TimeBasedPlayInfoList::~TimeBasedPlayInfoList`.
Before the rebase the gain was +20 over 436. `CliSessionTable::Select_index_pcid` is now in card 16's count.

## Rebase onto main (repair round 2)

| Item | Action |
| --- | --- |
| `LobbyErrorDesc` | One definition (main's). |
| `NPServiceChannelManager::_init`, `_gameServChannel` | One block (main's, with its static_asserts). The `NPChannelBase.h` include and `NPGameServiceChannel : public NPChannel` stay. |
| `ChannelIdOf`, `WorkerIdOf` | Merged into card 16's `LgpChannelId` and `LgpWid`. They are now `static __forceinline` and take `SharedChannel const*`. No score changed in any function. |
| `BnsCommonConfig::Config` | Card 16's placeholder removed. `BnsCommonConfigDefinition.cpp` defines it (LNK2005 otherwise). |
| `lessons.md` | Both `## ld-16` and `## ld-21` kept. |

## Review of the checkpoints

The 5 checkpoint files hold 20 rows. They do not overlap. They did not match the card index in 2 rows:

| Row | Problem | Action |
| --- | --- | --- |
| `0x8d990` (cold chunk of `0x8d590`) | Not an index entry. `0x8d590` has no row. | `0x8d590` listed as Not done. |
| `0x8e620` (chunk of `0x8e520`) | Not an index entry. `0x8e520` has no row. | `0x8e520` is lifted (the row says it was lifted with it). |

## Lifted

Scores are from funcdiff on the VS2010 build. The scores are low where a callee is still a `LIFT_STUB` (see "Why the scores are low").

| RVA | Function | Score |
| --- | --- | ---: |
| `0x8c660` | `HandleLobbyGame_UpdateAccountDataReq` | 14.2 |
| `0x8d9a0` | `HandleLobbyGame_FinishRegisterGuildNotify` | 81.5 |
| `0x8db10` | `HandleLobbyGame_CancelRegisterGuildNotify` | 81.5 |
| `0x8e010` | `HandleLobbyGame_FinishRenameGuildNotify` | 85.6 |
| `0x8e220` | `HandleLobbyGame_CancelRenameGuildNotify` | 65.1 |
| `0x8e390` | `HandleLobbyGame_DeleteGuildNotify` | 79.8 |
| `0x8e520` | `HandleLobbyGame_ChangeCharacterAppearanceOk` | 44.3 |
| `0x8e820` | `HandleLobbyGame_ChangeCharacterAppearanceFail` | 43.2 |
| `0x8eab0` | `HandleLobbyGame_ChangeCharacterSexOk` | 44.3 |
| `0x8edb0` | `HandleLobbyGame_ChangeCharacterSexFail` | 43.2 |
| `0x8f040` | `HandleLobbyGame_ChangeCharacterRaceOk` | 44.3 |
| `0x8f340` | `HandleLobbyGame_ChangeCharacterRaceFail` | 43.2 |
| `0x8f5d0` | `HandleLobbyGame_RenameCharacterOk` | 43.2 |
| `0x8f870` | `HandleLobbyGame_RenameCharacterFail` | 43.2 |
| `0x907e0` | `HandleLobbyGame_SetAppDataNotify` | 99.2 |

Each lifted handler has a `#pragma comment(linker, "/INCLUDE:...")` with a LIFT comment. Its caller (the handler list) is still a stub.

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| `0x8d590` | `HandleLobbyGame_TryRegisterGuildReq` | Calls `RuleSet::CheckName` (`0x6bfc0`). `RuleSet.h` has no class and `RuleSet.cpp` has no stub. The RuleSet card must add them. |
| `0x8dc80` | `HandleLobbyGame_TryRenameGuildReq` | Same `RuleSet::CheckName` gap. `LobbyDB.h` declares `TryRenameGuild` (`0xa68f0`) with 7 arguments. The caller and callee use 6. LobbyDB must fix the declaration. |
| `0x8fb00` | `HandleLobbyGame_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemReq` | Needs `ExtendJumpingCharacterCreationQuotaJob::_pool` (`0x2040a0`) and `ObjPool::Checkout` (`0x628c0`). The LobbyDaemon ObjectPool module is not lifted. `ObjectPool.cpp` is the SmartCouponDaemon form (3-argument constructor). The VS2010 link fails with LNK2001 without them. |
| `0x8ffc0` | `HandleLobbyGame_UpgradeJumpingCharacterStateWithCreationQuotaReq` | Needs `UpgradeJumpingCharacterStateJob::_pool` (`0x204150`) and `ObjPool::Checkout`. Same reason. |
| `0x903d0` | `HandleLobbyGame_UpdateJumpingCharacterStateReq` | Same pool as `0x8ffc0`. |

The three pool handlers were lifted and compiled with clang. The VS2010 link failed (LNK2001 for the pools and `Checkout`).
They were put back to stubs. A later ObjectPool card must lift the pools, then these 3 bodies. The logic is in the PDB and in
`LobbyGamePacketHandler.c` (lines of `0x8fb00`, `0x8ffc0`, `0x903d0`): `Checkout`, placement new of the job, `GetDefinition`
task ids 30 and 142, cli-key check, fail codes 5 and 2.

## Why the scores are low

LTCG inlines a `LIFT_STUB` body (`abort`, noreturn). The code after the call vanishes from the function. This holds for
`LobbyDB::FinishRenameGuild`, `CancelRenameGuild`, `DeleteGuild`, `LobbyJobManager::ExecuteW` and `CliSession::UpdateAccount*`.
The scores rise when those callees are lifted. This is not a codegen problem.

## Link fixes found during verify

The checkpoints only compiled with clang. The VS2010 link of LobbyDaemon failed. The fixes:

| Problem | Fix |
| --- | --- |
| All 5 exes: `ZSTD_*` unresolved | The worktree had no `vendor/zstd/src` (ignored checkout). Copied from the main checkout (bb6eaf64). Not committed. |
| `_StsMsgRequest::GetCommand` and 2 more: LNK2005 | `AuctionEscrow.h` had in-class bodies. They are now declarations. NPChannel2.cpp defines them (0x4440, 0x4450, 0x4460). |
| `CliSession::UpdateAccountExp`, `UpdateAccountContentQuota`, `UpdateAccountRecycleTime` | `LIFT_STUB` bodies in `CliSession.cpp` (0x38930, 0x38b50, 0x38cc0). The CliSession card lifts them. |
| `LobbyErrorDesc` | Defined in `LobbyGamePacketHandler.cpp` by card 16 (28 enumerator names). No module owns it yet ❓. Move it when the owner is known. |
| `BnsCommonConfig::Config` | `Shared/BnsCommonConfigDefinition.cpp` added to `lift_lobbydaemon` in CMakeLists.txt. |

## Codegen trials (max 3 per function)

| Function | Form | Result |
| --- | --- | --- |
| `HandleLobbyGame_SetAppDataNotify` | A4: `__declspec(noinline)` on `String::UnicodeToMultibyte` (the original calls it out of line) | 96.4 -> 97.2. `String::UnicodeToMultibyte` becomes MATCH (+1). Kept. |
| `HandleLobbyGame_SetAppDataNotify` | A10: `static __forceinline` on all file helpers (`assertCrash`, `LobbyErrorText`, `UpdateFailCode`, `ChannelIdOf` (now `LgpChannelId`), `WorkerIdOf` (now `LgpWid`), `SetupDecomposer`, `HandleShowcaseOk`) | 97.2 -> 99.2. The 3 `ChangeCharacter*Ok` handlers 11.9 -> 44.3. Kept. |
| `HandleLobbyGame_SetAppDataNotify` | A8: read `channel->_rawChannel` with no `channel != nullptr` test in `ChannelIdOf` | No score change in any function. Not kept. The original has the test in most handlers; only the log lines of `0x8c660` and `0x907e0` omit it (see Safety differences). |

Not tried:

| Function | Reason |
| --- | --- |
| `HandleLobbyGame_SetAppDataNotify` rest | One call to `PacketFormatIterator::skipRepeatFormat` (out of line here, inlined in the original) and doubled assert strings. No simple source form found. |
| `HandleLobbyGame_FinishRenameGuildNotify` 85.6 | Stub-limited (inlined `abort`). No source form changes this. |
| `HandleLobbyGame_FinishRegisterGuildNotify`, `CancelRegisterGuildNotify` 81.5 | Same. |

## Header and string fixes (repair round)

| Item | Fix |
| --- | --- |
| `HandleLobbyGame_ChangeCharacterAppearanceFail` | The execute-job-fail line logs `appearance-ok` as the original does (`// BUG:` copy-paste kept). |
| `NPChannel` ODR | `NPServiceChannel.h` had a second, empty `class NPChannel`. It now includes `SmartCouponDaemon/NPChannelBase.h`, the real class. `NPChannel.h` was split without content change: `NPChannelBase.h` holds everything up to `NPChannel`. `NPChannel.h` keeps the SmartCouponDaemon-only `NPServiceChannel` types, which clash with the LobbyDaemon `NPServiceChannelManager`. |
| `LobbyGamePacketHandler.cpp` | No longer includes `AuctionEscrow.h` (it clashed with `NPChannelBase.h`: both define `StsMsgLib::_StsMsgRequest`). The handler needs only the `NPChannelBase.h` form. |

## Safety differences

| Place | Difference |
| --- | --- |
| `HandleLobbyGame_SetAppDataNotify` | Keeps the key length and value length checks. The `AllocZero` results are not checked (as in the original). |
| `ChannelIdOf`, `WorkerIdOf` in the log lines of `0x8c660` and `0x907e0` | Test `channel != nullptr` before `channel->_rawChannel`. The original tests only `_rawChannel` there. Removing the test gave no score change (A8 trial), so the guard stays. The other handlers have the same test as the original (`channel != nullptr && channel->_rawChannel != nullptr`). |
| `HandleLobbyGame_UpdateAccountDataReq` | Keeps the token, cli-key and session checks. No key is logged. |

## Open points for later cards

- `0x8d590` and `0x8dc80`: RuleSet card, LobbyDB declaration.
- 3 pool handlers: ObjectPool card for LobbyDaemon.
- `LobbyErrorDesc` has no owner.
- `LIFT_STUB` for `UpdateAccount*` lives in `CliSession.cpp`. Expect a merge conflict if the CliSession card also defines them.
