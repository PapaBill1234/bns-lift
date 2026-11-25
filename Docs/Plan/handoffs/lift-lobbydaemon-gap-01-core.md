# Handoff: lift-lobbydaemon-gap-01-core

| Item | Value |
| --- | --- |
| Card | `design/parity-v2/gap-cards/gap-01-core.md` (private project) |
| Branch | `gap-01-core` (scratch clone only, not pushed) |
| Base | `d5b3dc3` |
| Code commit | `1b0f305` |
| Source | LobbyDaemon 2019 + PDB (VS2010 SP1), HR pseudocode. IDA was not opened. |
| Author and committer | `Claude <noreply@anthropic.com>` |

## Result

| Check | Result |
| --- | --- |
| Gate `pilot.py gate --rev 1b0f305` | 24 of 24 card IDs have no reason. Eligible pool: 173 -> 197. |
| Full 5-exe build (`gate_full.sh`, cold, fresh clone of `1b0f305`) | rc 0, "parity ok", 442 s |
| Proof (`proof.py`, strict rules not changed) | verdict `review`: 0 lost MATCH, 0 strict regress, 28 new MATCH, 3 credited (strict full), 25 need review (new MATCH, strict not full) |
| Lost MATCH, LobbyDaemon REF | 0 (645 -> 673) |
| Lost MATCH, LobbyDaemon NOREF | 0 (879 -> 927) |

## MATCH per exe (cold gate build)

| Exe | Before (`d5b3dc3`) | After (`1b0f305`) | Delta | Lost |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 0 | 0 |
| LobbyGate | 658 | 658 | 0 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 | 0 |
| LobbyDaemon | 645 | 673 | +28 | 0 |

LobbyDaemon NOREF build (preview, overlay): 879 -> 927 MATCH (+48), 0 lost.

## Classes and layouts

| Class | Size | File |
| --- | ---: | --- |
| `LobbyJobStateDef` | 0x10 | `LobbyJob.h` |
| `LobbyJobDef` | 0x20 | `LobbyJob.h` |
| `LobbyJobTaskParam` | 0x8 | `LobbyJob.h` |
| `LobbyJobManager` | 0x20 | `LobbyJob.h` |
| `LobbyJobTaskEvent` | 0x30 | `LobbyJob.h` |
| `TransactionChannel::Manager` | 0x78 | `TransactionChannel.h` |
| `LobbyJobTransaction` | 0x48 | `TransactionChannel.h` |
| `NPLobbyJobTransaction` | 0x18 | `NPServiceChannel.h` |
| `NPLobbyMessageHandleEvent` | 0x38 | `LobbyEvent.h` |
| `StopPlayTimerEvent` | 0x48 | `LobbyEvent.h` (layout only) |

## Bodies

Status: funcdiff of the NOREF and REF builds with the overlay of `1b0f305`. "-" = not in the build (no caller, /OPT:REF removes it).

| Name | RVA | NOREF | REF | Card ID |
| --- | --- | --- | --- | --- |
| `LobbyJob::~LobbyJob` | 0x12270 | MATCH | - | yes |
| `LobbyJob::dispatch_work` | 0x122b0 | MATCH | - | yes |
| `CliSessionJob::dispatch_work` | 0x3c010 | MATCH | - | yes |
| `NPLobbyMessageHandleEvent::~NPLobbyMessageHandleEvent` | 0xbbad0 | MATCH | - | yes |
| `NPLobbyMessageHandleEvent::HandleEvent` | 0xbbb60 | MATCH | - | yes |
| `PacketHandleEvent::HandleEvent` | 0xbbc60 | MATCH | MATCH | yes |
| `PacketHandleEvent::~PacketHandleEvent` | - | MATCH | MATCH | no |
| `LobbyJobTaskEvent::~LobbyJobTaskEvent` | 0xc1670 | MATCH | - | yes |
| `LobbyJob::transit` | 0xc1710 | MATCH | MATCH | yes |
| `LobbyJob::execute` | 0xc18d0 | MATCH | MATCH | added |
| `LobbyJob::resume` | 0xc1990 | MATCH | - | added |
| `LobbyJobManager::~LobbyJobManager` | 0xc1a60 | DIFF 95.2 | - | yes |
| `LobbyJobManager::Initialize` | 0xc1b40 | DIFF 94.4 | - | yes |
| `LobbyJobManager::Register` | 0xc1c90 | MATCH | - | yes |
| `LobbyJobManager::Clear` | 0xc1d20 | MATCH | - | yes |
| `LobbyJobManager::Start` | 0xc1ed0 | MATCH | - | yes |
| `LobbyJobManager::Postpone` | 0xc1f30 | DIFF 77.4 | - | yes |
| `LobbyJobManager::Execute` | - | MATCH | MATCH | added |
| `LobbyJobManager::ExecuteW` | 0xc20a0 | MATCH | MATCH | yes |
| `LobbyJobManager::ResumeW` | - | MATCH | - | added |
| `LobbyJobManager::add` | 0xc21f0 | MATCH | - | yes |
| `LobbyJobManager::remove` | 0xc22d0 | MATCH | MATCH | yes |
| `LobbyJobManager::find` | 0xc23d0 | MATCH | MATCH | yes |
| `LobbyJobTaskEvent::HandleEvent` | 0xc24c0 | MATCH | - | yes |
| `NPLobbyJobTransaction::Expire` | 0xd2250 | MATCH | - | yes |
| `NPLobbyJobTransaction::Set` | 0xd22c0 | MATCH | - | yes |
| `LobbyJobTransaction::GetTid` | 0x7b0d0 | MATCH | - | yes |
| `LobbyJobTransaction::Expire` | 0x7b7a0 | MATCH | - | yes |
| `LobbyJobTransaction::Set` | - | MATCH | - | added |
| `TransactionChannel::InitializeTransactionChannel` | 0x7b170 | DIFF 92.6 | MATCH | yes |
| `TransactionChannel::~TransactionChannel` | - | MATCH | DIFF 65.6 | added |
| `TransactionChannel::Manager::Tick` | - | DIFF 93.0 | DIFF 93.0 | added |
| `TransactionChannel::Manager::add` | - | MATCH | - | added |
| `TransactionChannel::Manager::remove` | - | MATCH | - | added |
| `RefCntPoolObj::~RefCntPoolObj` | - | MATCH | - | added |

Side effect: 18 handlers in REF went from DIFF to MATCH (`HandleLobbyGame_*`, `HandlePostOfficeRegisterPost*`). Their callees are no longer `LIFT_STUB`, so /LTCG does not mark them noreturn.

## Open DIFFs (card IDs that pair but do not MATCH)

| Name | RVA | Score | Cause |
| --- | --- | ---: | --- |
| `LobbyJobManager::~LobbyJobManager` | 0xc1a60 | 95.2 | The original calls the `std::map::~map` symbol. Ours calls `std::_Tree::~_Tree` (ICF picks another name for the same body). ❓ |
| `LobbyJobManager::Initialize` | 0xc1b40 | 94.4 | The same map dtor and ctor naming as above. ❓ |
| `LobbyJobManager::Postpone` | 0xc1f30 | 77.4 | The original inlines the `LobbyJobTaskEvent` ctor and stores 0 to `_param` (all callers pass `nullptr`, LTCG constant). Ours calls the ctor out of line. ❓ |
| `TransactionChannel::InitializeTransactionChannel` | 0x7b170 | 92.6 (NOREF) | MATCH in REF. In NOREF the `Manager` ctor is not inlined, so the vtable refs are missing. |
| `TransactionChannel::Manager::Tick` | - | 93.0 | The original inlines the local `RefCntList` dtor. Ours calls `RefCntList::~RefCntList`. |

## Not done

| Name | RVA | Reason |
| --- | --- | --- |
| `CliSessionJob::CliSessionJob` | 0x3bef0 | Not in the card ID table. Still `LIFT_STUB`. |
| `CliSessionJob::~CliSessionJob` | 0x3bfa0 | Not in the card ID table. Still `LIFT_STUB`. |
| `StopPlayTimerEvent::HandleEvent` | 0xbbcf0 | Not in the card ID table. It needs `KickJob` (other card). Still `LIFT_STUB`. |
| `TransactionChannel::Manager::expireAll` | - | Not declared. No caller in this card. |

All 24 card IDs are done (they pair and the gate gives no reason). 5 of them are DIFF (see the table above).

## Rules kept

- No inline asm, no byte tricks, no `/INCLUDE`. funcdiff and strict are not changed.
- PDB names only. Server checks are kept (the `transit` state checks, the `Register` null and `add` checks, the null job checks in `Execute` and `ExecuteW`, and the `Initialize` hash count check).
- No binaries, PDBs, IDBs or keys in this commit.
