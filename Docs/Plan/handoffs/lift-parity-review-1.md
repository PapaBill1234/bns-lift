# lift-parity-review-1 handoff

## Done
- Task 1: gate ok, parity ok. +0 in each exe (this card changes only docs).
- Task 2: `Docs/Parity/review-1.md` (measurement, gains per card, what did not work, cause classes, round-2 plan).
- Task 3: `Docs/Parity/lessons.md` cleaned (A1-A16 sorted by functions fixed; B did not work; C tool facts; D open).
- Task 4: `Docs/Parity/rules-proposal.md` (method rules M1-M9, source rules R1-R15, section "Behaviour misses (rev-small-348)" with rules B1-B5).
- Task 5: 9 cards in `Docs/Plan/cards/` (tool, paths, crypto, bloodlib, noinline, helpers, pod, scd -2; review-2). Rows in `Docs/Plan/queue/lift-parity-review-1.tsv`, serial deps from this card. Shared cards come first.
- Measured tool fix as `Docs/Parity/tool-2-fix.patch` (for lift-parity-tool-2).

## State of each exe (all below 90 %: round 2 queued, no 90+ round, no `plus-state.tsv`)
| Exe | Parity | Change in round 1 | With Fix V + T (measured) |
| --- | ---: | ---: | ---: |
| CacheGate | 387/491 = 78.8 % | +171 | 401 |
| LobbyGate | 487/739 = 65.9 % | +207 | 501 |
| SmartCouponDaemon | 461/669 = 68.9 % | +236 | 480 |
| PostOfficeDaemon | 509/759 = 67.1 % | +247 | 525 |

## Shared library (task 6a)
- `tools/parity_shared.py --list`: 369/489 = 75.5 % (394/489 with Fix V + T). Target 99 %.
- Shared DIFF by cause: consts only 115 (crypto, LTCG, TLS), path literal 61, refs only 38, call order 34, other callee 32, orig calls more 18, tool noise 4.
- Shared cards: tool-2, paths-2, crypto-2, bloodlib-2, noinline-2 (before the exe cards helpers-2, pod-2, scd-2). CacheGate has no exe card: its 12 exe-only DIFF are on the stop list.

## ❓
- Crypto misses: probably other compile flags of the original BloodCrypto lib (crypto-2 checks `S_ENVBLOCK`).
- POD `Lock.h` literal in 7 functions (ours only); 6 more `source\Memory.cpp` refs in `BloodDaemonMain`, `Daemon::start`.
- Turn cost per card: not in the handoffs. Rule M7 and the new cards ask for a `Turns:` line.

## Blocked
- None.

## Gate result
- `tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok, MATCH -> DIFF 0 in each exe. No file outside `Docs/` changed after the run.
