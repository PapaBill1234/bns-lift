# Handoff: lift-parity-review-4

Card: parity review 4. Main a57d889. Result: round 5 queued (6 parallel cards and review-5).

## Measurement
- `tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok. MATCH -> DIFF 0 in all 5 exes.

| Exe | Review 3 | Now | Change | State |
| --- | ---: | ---: | ---: | --- |
| CacheGate | 448/491 = 91.2 % | 456/491 = 92.9 % | +8 | below goal (95 %); round 5 card cgscd-5 |
| LobbyGate | 627/739 = 84.8 % | 658/739 = 89.0 % | +31 | below checkpoint (90 %); round 5 cards lg-5a, lg-5b |
| SmartCouponDaemon | 582/669 = 87.0 % | 630/669 = 94.2 % | +48 | below goal; round 5 card cgscd-5 |
| PostOfficeDaemon | 665/759 = 87.6 % | 694/759 = 91.4 % | +29 | below goal; round 5 cards pod-5a, pod-5b |
| LobbyDaemon | - | 1024/2204 = 46.5 %, excluded 127 | - | other system; not in this review |

## Shared library
- `tools/parity_shared.py --list`: 516/549 = 94.0 % (review 3: 490/549 = 89.3 %, +26).
- 33 shared names are DIFF. By cause: stop list 19 (`aes128Table*` x4, `Daemon::Start`, `PipeConsole::*` x4, `PipeCommandProcess::processCommand`,
  `Session::Session`, `Session::HandleEvent`, `StaticPageMemoryManager::Initialize`, `ThreadManager::Initialize`, `WindowConsole::Open`, `Rsa::decrypt`,
  `Network::OpenPort` x2, `DaemonConfig::Dump`, `FragmentPacketConcatenater::Add`); crypto 3 (`Divide`, `InvMod`, `invMod`); EH state -2 3
  (`wmain`, `FragmentPacketConcatenater::Clone`, `operator delete[]`); BloodLib 2 (`IoWorker::run`, `Session::Connect`);
  CacheGate relay names 5 (`HandleCacheGate*`, CG and POD source).
- Shared card: lift-parity-shared-5 (first in the plan). The `HandleCacheGate*` names go to cgscd-5 (CG) and pod-5a (POD).

## Round 4 summary
- 6 of 9 cards built: +116 MATCH, 907 turns, 12.8 MATCH per 100 turns. ehstate-4, lg-4 and cg-4 were not built; their lists are in the round-5 cards.
- CG gained 1.6 %. Stall check: no CG card was built, so it is not a method stall (review-4 section 7).

## Lessons
- `lessons.md` cleaned: round-4 card sections merged into A, B, D. New A30, A31, A32. Numbers A1 to A29 are stable. `ld-*` sections not touched.
- `rules-proposal.md` section 6: P12 to P18.

## Round 5 (queue `Docs/Plan/queue/lift-parity-review-4.tsv`)
All `opus`, deps only on review-4, disjoint files: shared-5, lg-5a, lg-5b, pod-5a, pod-5b, cgscd-5. Last: review-5.
Estimate: CG about 465, LG about 686, SCD about 639, POD about 714. SCD and CG can reach 95 %. LG and POD likely need round 6.

Turns: 45
