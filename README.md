# bns-lift

C++ lift of the 2019 + PDB BnS server executables.

- Plan: [Docs/Plan/plan.md](Docs/Plan/plan.md)
- Build: clang-cl + lld-link with Wine headers. Run with wine64.
- Gate: `tools/gate.sh`

This repo is public. Do not commit binaries, keys, PDBs or IDA databases.

## Status (2026-11-27)

| Item | State |
| --- | --- |
| First 4 exes | 96.2 % parity (2558 of 2658). All 4 are at their level: CacheGate, SmartCouponDaemon and PostOfficeDaemon above 95 %, LobbyGate 94.9 %. |
| Open functions (first 4) | 100. Each has a written proof in [Docs/Parity/unmatchable.md](Docs/Parity/unmatchable.md) (level A). 0 at level B. |
| LobbyDaemon | Lift in progress: 1038 counted MATCH (47.1 %), 128 excluded MATCH not counted. Most of the other functions are still `LIFT_STUB` bodies. |
| Method | Gap cards. Each card lifts the PDB class layout and the stub bodies of one class or job group. |
| Last landed | pkt3 (packet helpers; PostOfficeDaemon +2; 2 review rejects excluded), t9 (LobbyGate HandleEvent, KickNotify, AddJobTimer; +3), fpc (FragmentPacketConcatenater::Clone; LobbyGate +1, PostOfficeDaemon +1). 0 lost in all 5 exes. |
| Checks per landing | Full VS2010 build of all 5 exes, funcdiff against the original, 0 lost MATCH, 0 strict regress. Review v2 (prechecks P1-P5, P9 and a model review) checks each new MATCH without a strict full proof. |
| Next | GameDaemon full lift: plan in `Docs/Plan/gamedaemon-lift.md` (in progress). |

## Parity

<!-- parity:start -->
Last update: card `lift-gamedaemon-gap-021-e21` (2026-11-27). Tool: `tools/parity.sh` (VS2010 /GL /LTCG build vs original, funcdiff).

| Exe | Parity | MATCH | DIFF | Excluded | Only in original | Total | Mean score | Start | Change | Level |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| CacheGate | **96.7 %** | 475 | 16 | 0 | 0 | 491 | 99.8 | 44.0 % | +52.7 | 95 % ✅ |
| LobbyGate | **94.9 %** | 701 | 37 | 0 | 1 | 739 | 99.6 | 37.9 % | +57.0 | 90 % ✅ |
| SmartCouponDaemon | **97.0 %** | 649 | 19 | 1 | 0 | 669 | 99.8 | 33.6 % | +63.4 | 95 % ✅ |
| PostOfficeDaemon | **96.6 %** | 733 | 25 | 0 | 1 | 759 | 99.7 | 34.5 % | +62.1 | 95 % ✅ |
| LobbyDaemon | **47.1 %** | 1038 | 286 | 128 | 752 | 2204 | 97.4 | 2.2 % | +44.9 | below 90 % |
| GameDaemon | **4.0 %** | 517 | 81 | 0 | 12253 | 12851 | 96.5 | 0.4 % | +3.6 | Lift in progress |
| **First 4** | **96.2 %** | 2558 | | | | 2658 | | 37.0 % | +59.3 | 95 % ✅ |

| Shared library (functions in 2+ exes) | Parity | MATCH in each exe | DIFF in 1+ exe | Total | Goal |
| --- | ---: | ---: | ---: | ---: | --- |
| BloodLib, Shared, Packet, CRT | **96.2 %** | 530 | 21 | 551 | 99 % |

First 4 and shared library: CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon. LobbyDaemon: lift in progress; most functions are still stubs (only in original). GameDaemon: lift in progress. Goal: 95 % per exe, 99 % preferred. Shared library: 99 % preferred. MATCH never holds excluded symbols (review rejected, no honest source fix: [Docs/Parity/excluded.tsv](Docs/Parity/excluded.tsv)); they are in the column Excluded (129 now). Rules: [Docs/Parity/README.md](Docs/Parity/README.md). History: [Docs/Parity/progress.tsv](Docs/Parity/progress.tsv).

| Card | CacheGate | LobbyGate | SmartCouponDaemon | PostOfficeDaemon | LobbyDaemon | GameDaemon |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| `baseline-vs2010` | 44.0 % | 37.9 % | 33.6 % | 34.5 % |  |  |
| `lift-parity-0` | 59.7 % | 51.0 % | 49.9 % | 49.4 % |  |  |
| `lift-parity-s1` | 67.4 % | 54.1 % | 54.9 % | 53.6 % |  |  |
| `lift-parity-s2` | 70.3 % | 57.5 % | 58.0 % | 55.7 % |  |  |
| `lift-parity-s3` | 76.2 % | 62.5 % | 64.1 % | 62.5 % |  |  |
| `lift-parity-cg-1` | 78.4 % | 62.5 % | 64.1 % | 62.5 % |  |  |
| `lift-parity-lg-1` | 78.6 % | 65.8 % | 65.3 % | 63.1 % |  |  |
| `lift-parity-scd-1` | 78.8 % | 65.9 % | 68.9 % | 63.8 % |  |  |
| `lift-parity-pod-1` | 78.8 % | 65.9 % | 68.9 % | 67.1 % |  |  |
| `lift-parity-review-1` | 78.8 % | 65.9 % | 68.9 % | 67.1 % |  |  |
| `lift-parity-tool-2` | 82.5 % | 68.5 % | 72.3 % | 69.7 % |  |  |
| `lift-parity-paths-2` | 82.7 % | 69.3 % | 72.9 % | 70.5 % |  |  |
| `lift-parity-crypto-2` | 83.7 % | 70.0 % | 73.7 % | 71.1 % |  |  |
| `lift-parity-bloodlib-2` | 85.1 % | 70.6 % | 74.4 % | 71.8 % |  |  |
| `lift-parity-noinline-2` | 85.5 % | 71.4 % | 75.3 % | 72.9 % |  |  |
| `lift-parity-helpers-2` | 85.5 % | 71.7 % | 75.3 % | 75.1 % |  |  |
| `lift-parity-pod-2` | 85.5 % | 71.7 % | 75.3 % | 77.5 % |  |  |
| `lift-parity-scd-2` | 85.5 % | 71.7 % | 76.2 % | 77.5 % |  |  |
| `lift-parity-review-2` | 85.5 % | 71.7 % | 76.2 % | 77.5 % |  |  |
| `lift-parity-perexe-3` | 85.7 % | 72.1 % | 76.5 % | 78.0 % |  |  |
| `lift-parity-cryptolib-3` | 85.7 % | 77.7 % | 80.7 % | 81.7 % |  |  |
| `lift-parity-inline-3` | 86.4 % | 78.9 % | 81.2 % | 82.5 % |  |  |
| `lift-parity-order-3` | 87.6 % | 79.6 % | 82.2 % | 83.1 % |  |  |
| `lift-parity-consts-3` | 88.8 % | 80.5 % | 83.1 % | 83.9 % |  |  |
| `lift-parity-arraynew-3` | 88.8 % | 81.2 % | 83.1 % | 83.9 % |  |  |
| `lift-parity-handlers-3` | 88.8 % | 81.3 % | 83.3 % | 85.0 % |  |  |
| `manual-parity (astra + opus 6.2)` | 91.2 % | 84.8 % | 87.0 % | 87.6 % |  |  |
| `lift-parity-dbbind-3` | 91.2 % | 84.8 % | 87.0 % | 87.6 % |  |  |
| `lift-parity-crypto-4` | 91.2 % | 87.0 % | 88.6 % | 89.1 % |  |  |
| `lift-parity-net-4` | 92.1 % | 87.6 % | 89.2 % | 89.5 % |  |  |
| `lift-parity-packet-4` | 92.5 % | 88.4 % | 89.7 % | 90.4 % |  |  |
| `lift-parity-scd-4` | 92.5 % | 88.4 % | 93.6 % | 90.4 % |  |  |
| `lift-parity-pod-4` | 92.5 % | 88.4 % | 93.9 % | 91.2 % |  |  |
| `lift-parity-console-4` | 92.9 % | 89.0 % | 94.2 % | 91.4 % |  |  |
| `lift-lobbydaemon-0` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 2.2 % |  |
| `lift-lobbydaemon-2` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 2.2 % |  |
| `lift-lobbydaemon-1` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 2.2 % |  |
| `lift-lobbydaemon-3` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 2.2 % |  |
| `lift-lobbydaemon-4` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 2.2 % |  |
| `lift-lobbydaemon-5` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 2.2 % |  |
| `lift-lobbydaemon-6` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 3.7 % |  |
| `lift-lobbydaemon-8` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 3.9 % |  |
| `lift-lobbydaemon-10` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 4.4 % |  |
| `lift-lobbydaemon-7` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 5.5 % |  |
| `lift-lobbydaemon-11` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 5.9 % |  |
| `lift-lobbydaemon-9` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 7.9 % |  |
| `lift-lobbydaemon-12` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 8.8 % |  |
| `lift-lobbydaemon-13` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 9.9 % |  |
| `lift-lobbydaemon-17` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 9.9 % |  |
| `lift-lobbydaemon-14` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 10.9 % |  |
| `lift-lobbydaemon-18` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 13.7 % |  |
| `lift-lobbydaemon-15` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 19.8 % |  |
| `lift-lobbydaemon-16` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 20.1 % |  |
| `lift-lobbydaemon-19` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 21.2 % |  |
| `lift-lobbydaemon-20` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 24.6 % |  |
| `lift-lobbydaemon-23` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 26.5 % |  |
| `lift-lobbydaemon-21` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 27.4 % |  |
| `lift-lobbydaemon-24` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 29.3 % |  |
| `lift-lobbydaemon-22` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 29.3 % |  |
| `lift-lobbydaemon-gap-int-2` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.6 % |  |
| `fix7-stub-headers` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.6 % |  |
| `lift-lobbydaemon-gap-05-job-charge` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.6 % |  |
| `lift-lobbydaemon-gap-06-job-goods` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.6 % |  |
| `tools-pdbq-pdbcls-funcdiff-imm` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.7 % |  |
| `fix3b-ids-12-17` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.8 % |  |
| `tools-honest-totals` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.8 % |  |
| `tools-public-clean` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.8 % |  |
| `lift-lobbydaemon-gap-07-job-wnp-a` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.8 % |  |
| `lift-lobbydaemon-gap-08-job-session` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.9 % |  |
| `lift-lobbydaemon-gap-19` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 33.5 % |  |
| `lift-lobbydaemon-gap-11` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |  |
| `lift-lobbydaemon-gap-09` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |  |
| `fix-pdb-layout` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |  |
| `tools-pdb-layout` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |  |
| `lift-lobbydaemon-gap-10` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |  |
| `lift-lobbydaemon-gap-16` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |  |
| `lift-lobbydaemon-gap-14` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |  |
| `lift-lobbydaemon-gap-12` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |  |
| `lift-lobbydaemon-gap-26` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 36.2 % |  |
| `lift-lobbydaemon-gap-25` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 36.7 % |  |
| `lift-lobbydaemon-gap-04-npgame` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 37.3 % |  |
| `lift-lobbydaemon-gap-15` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 37.8 % |  |
| `lift-misc-a` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 37.8 % |  |
| `lift-lobbydaemon-gap-20` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 39.7 % |  |
| `lift-lobbydaemon-gap-17` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 45.7 % |  |
| `lift-lobbydaemon-gap-23` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 46.1 % |  |
| `lift-lobbydaemon-gap-24` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 46.5 % |  |
| `lift-parity-shared-5` | 93.1 % | 89.6 % | 94.2 % | 91.6 % | 46.5 % |  |
| `lift-parity-lg-5a` | 93.1 % | 91.5 % | 94.2 % | 91.6 % | 46.5 % |  |
| `lift-parity-lg-5b` | 93.1 % | 93.1 % | 94.2 % | 91.6 % | 46.5 % |  |
| `lift-parity-pod-5a` | 93.1 % | 93.1 % | 94.2 % | 93.0 % | 46.5 % |  |
| `lift-parity-pod-5b` | 93.1 % | 93.1 % | 94.2 % | 93.8 % | 46.5 % |  |
| `lift-parity-cgscd-5` | 94.3 % | 93.1 % | 94.6 % | 93.8 % | 46.5 % |  |
| `lift-lobbydaemon-v2b-pod-01` | 94.3 % | 93.1 % | 94.6 % | 94.3 % | 46.5 % |  |
| `lift-lobbydaemon-v2b-wmain-01` | 94.5 % | 93.1 % | 94.9 % | 94.3 % | 46.5 % |  |
| `lift-lobbydaemon-v2b-cg-02` | 94.7 % | 93.1 % | 94.9 % | 94.3 % | 46.5 % |  |
| `lift-lobbydaemon-v2b-merge-01` | 94.7 % | 93.1 % | 94.9 % | 94.3 % | 46.5 % |  |
| `lift-lobbydaemon-v2b-merge-02` | 94.7 % | 93.1 % | 94.9 % | 94.6 % | 46.5 % |  |
| `lift-lobbydaemon-v2b-merge-03c` | 94.9 % | 93.2 % | 95.1 % | 94.9 % | 46.5 % |  |
| `lift-lobbydaemon-v2b2-m28` | 95.1 % | 93.2 % | 95.2 % | 95.0 % | 46.5 % |  |
| `lift-lobbydaemon-v2b2-m27` | 95.1 % | 93.2 % | 95.2 % | 95.0 % | 46.8 % |  |
| `lift-lobbydaemon-v2b2-ses3` | 95.7 % | 93.6 % | 95.7 % | 95.4 % | 46.9 % |  |
| `tools-d05-gate` | 95.7 % | 93.6 % | 95.7 % | 95.4 % | 46.9 % |  |
| `lift-lobbydaemon-v2b2-tm1` | 96.1 % | 93.9 % | 96.0 % | 95.7 % | 47.0 % |  |
| `lift-lobbydaemon-v2b2-aes` | 96.5 % | 94.2 % | 96.3 % | 95.9 % | 47.1 % |  |
| `lift-lobbydaemon-v2b2-job3` | 96.5 % | 94.2 % | 96.6 % | 95.9 % | 47.1 % |  |
| `lift-lobbydaemon-v2b2-op` | 96.5 % | 94.2 % | 96.9 % | 95.9 % | 47.1 % |  |
| `lift-lobbydaemon-v2b2-chs` | 96.5 % | 94.2 % | 96.9 % | 96.0 % | 47.1 % |  |
| `lift-lobbydaemon-v2b2-wco` | 96.7 % | 94.2 % | 97.0 % | 96.2 % | 47.1 % |  |
| `lift-lobbydaemon-v2b2-bip2` | 96.7 % | 94.3 % | 97.0 % | 96.2 % | 47.1 % |  |
| `lift-lobbydaemon-v2b2-fpc` | 96.7 % | 94.5 % | 97.0 % | 96.3 % | 47.1 % |  |
| `lift-lobbydaemon-v2b2-t9` | 96.7 % | 94.9 % | 97.0 % | 96.3 % | 47.1 % |  |
| `lift-lobbydaemon-v2b2-pkt3` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % |  |
| `tools-gamedaemon-0a` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % |  |
| `tools-gamedaemon-0c` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % |  |
| `tools-gamedaemon-0e` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 0.4 % |
| `lift-gamedaemon-0d` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 0.5 % |
| `lift-gamedaemon-gap-002-e2` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 0.8 % |
| `lift-gamedaemon-gap-003-e3` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 1.1 % |
| `lift-gamedaemon-gap-001-e1` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 1.1 % |
| `lift-gamedaemon-gap-008-e8` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 1.2 % |
| `lift-gamedaemon-gap-004-e4` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 1.5 % |
| `lift-gamedaemon-gap-007-e7` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 1.6 % |
| `lift-gamedaemon-gap-006-e6` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 1.9 % |
| `lift-gamedaemon-gap-009-e9` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 2.0 % |
| `lift-gamedaemon-gap-010-e10` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 2.3 % |
| `lift-gamedaemon-gap-011-e11` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 2.5 % |
| `lift-gamedaemon-gap-005-e5` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 2.8 % |
| `lift-gamedaemon-gap-013-e13` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 2.9 % |
| `lift-gamedaemon-gap-012-e12` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 3.0 % |
| `lift-gamedaemon-gap-016-e16` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 3.0 % |
| `lift-gamedaemon-gap-014-e14` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 3.2 % |
| `lift-gamedaemon-gap-015-e15` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 3.5 % |
| `lift-gamedaemon-gap-126-s2` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 3.5 % |
| `lift-gamedaemon-gap-017-e17` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 3.5 % |
| `lift-gamedaemon-gap-018-e18` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 3.8 % |
| `lift-gamedaemon-gap-019-e19` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 3.9 % |
| `lift-gamedaemon-gap-020-e20` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 4.0 % |
| `lift-gamedaemon-gap-021-e21` | 96.7 % | 94.9 % | 97.0 % | 96.6 % | 47.1 % | 4.0 % |
<!-- parity:end -->
