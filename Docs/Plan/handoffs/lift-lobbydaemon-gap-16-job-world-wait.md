# Handoff: lift-lobbydaemon-gap-16-job-world-wait

Date: 2026-11-25. Branch: `gap-16`. Base: `e68e5d0` (fix7).
Code commits: `bc30ac4`, `8f95c13`. This handoff is in the next commit.
The gate, strict and the proof use `8f95c13`.

## Scope

| Module | Card IDs | NOREF MATCH | NOREF DIFF |
| --- | --- | --- | --- |
| EndWaitGameWorldJob | 5 | 3 | 2 |
| EnterGameWorldJob | 5 | 4 | 1 |
| GiveupWaitGameWorldJob | 6 | 6 | 0 |
| LeaveGameWorldJob | 6 | 5 | 1 |
| Total | 22 | 18 | 4 |

The card IDs are `GetDefinition`, `_vtbl`, `Initialize`, `work`, `init` and the state handler of each job.
`EndWaitGameWorldJob` has no `Initialize` card ID. `EnterGameWorldJob::enterGameWorld` is not a card ID.
The dtors are lifted too. They are not card IDs.

Scope additions:

| Item | Reason | NOREF |
| --- | --- | --- |
| `CliSessionJob::CliSessionJob`, `~CliSessionJob` (same text as gap-06) | They were LIFT_STUB. A stub callee folds under ICF and /LTCG and makes the caller noreturn. | MATCH |
| `LobbyTokenDesk::Issue` | `endWait` and `leaveGameWorld` call it. | MATCH |
| `EnterGameWorldToken`, `LeaveGameWorldToken` (ctor, dtor, `GetKind`) | The jobs allocate them. `LeaveGameWorldToken` is new (sizeof 0x48). | `LeaveGameWorldToken::GetKind` MATCH |
| `CliSession::getCharacter`, `removeCharacter`, `getPlayingCharacter` | The jobs call them. | MATCH |
| Friend lines in `CliSession.h` and `LobbyToken.h` | Access to private members, as the original code has. | n/a |

## What changed

- Class layouts come from the PDB: State enums, `_def`, `_pool`, `_lgate` at +0x58, sizeof 0x60 static_asserts.
- `_def` tables come from the exe: EndWait type 9, GiveupWait 10, EnterGameWorld 11, LeaveGameWorld 13. Each job has the states INIT, the handler state and FIN (fin = 2).
- Bodies come from the 2019 + PDB pseudocode. PDB names only. The server checks stay.
- Session states use `ECliSessionState` values (CSS_L2W_wait 0x30002, CSS_WORLD 0x40000, CSS_W2L_wait 0x50001, CSS_FIN 0x60000).
- A new `JOB_CRASH` macro writes Log, then AlertSender, with the original line number.
- `_vtbl` uses placement new on a stack buffer and returns the vfptr, as in gap-06.

## Checks

| Check | Result |
| --- | --- |
| `pilot.py gate` (22 card IDs, REF `main-build-FSUiGf0u`, NOREF `noref-build-Tuey6JE5`, both `bc30ac4`) | 22 of 22 clear (0 of 22 before); eligible pool 265 -> 291; 9 dropped in both runs (5 alias_match, 4 not_measurable) |
| `gate_fast.sh` (fresh clone of `8f95c13`) | rc 0, gate ok, parity ok, 0 link FAIL |
| `strict.py` (5 exes, `cfg` level) | no FAIL. The base strict was made again at `e68e5d0` with the current strict.py (fix13). |
| `proof.py --base e68e5d0 --candidate 8f95c13` | verdict `pass`; 0 lost, 0 strict regress, 0 cfg regress, 0 review items, 2 credited |
| `integrate.check_proof` (dry) | PASS |

The first proof (`bc30ac4`) gave verdict `review` with one item, `CliSession::getCharacter`.
The review precheck rejected it (P2_cc: the original has `jne` first, the build `je`).
The original keeps the found pointer in one variable and leaves the loop with `break`.
`8f95c13` uses that shape. Now strict full proves the function.

## MATCH

| Exe | Before | After | Lost |
| --- | --- | --- | --- |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon (REF) | 674 (841 paired) | 676 (843 paired) | 0 |
| LobbyDaemon (NOREF) | 973 (1205 paired) | 997 (1233 paired) | 0 |

The REF gain is `CliSession::getCharacter` and `Character::SetShowcase` (new pairs).
No live code creates the four jobs yet, so REF does not pair the card IDs.

## DIFF card IDs

| ID | Score | Cause |
| --- | --- | --- |
| `EndWaitGameWorldJob::init` | 93.8 | `CliSession::finalize` calls the `cleanupCharge` stub (0x35fc0). The stub is noreturn, so the code after `finalize` goes away. |
| `EndWaitGameWorldJob::endWait` | 93.0 | Same cause. |
| `LeaveGameWorldJob::leaveGameWorld` | 92.0 | Same cause. |
| `EnterGameWorldJob::work` | 83.3 | It calls the `enterGameWorld` stub (0x85240). |

Expect the three `finalize` DIFFs to become MATCH when gap-15 lifts `cleanupCharge`. ❓

## Not done

| Function | RVA | Reason |
| --- | --- | --- |
| `EnterGameWorldJob::enterGameWorld` | 0x85240 | Large body. Not a card ID. LIFT_STUB stays. |
| `deallocate_me` x4 | 0x4aff0, 0x52d00, 0x84e10, 0x877c0 | `ObjPool` is not in the lift. LIFT_STUB stays. |

## Merge notes

- The `CliSession.cpp` hunk (`getCharacter`, `removeCharacter`, `getPlayingCharacter`) comes from gap-15 `f95b4e4`.
  `8f95c13` changes `getCharacter` (result variable and `break`). Keep the gap-16 form when the two merge.
  The gap-15 form fails the review precheck (P2_cc).
- The `GameWorldPresence` friend line in `CliSession.h` has the same text as gap-15.
- The `CliSessionJob.cpp` ctor and dtor have the same text as gap-06.
- Merge gap-15 first. Then a rebuild shows if the `finalize` DIFFs clear.
- `vendor/zstd/src` is git-ignored. Scratch clones must copy it in.
