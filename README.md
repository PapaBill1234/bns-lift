# bns-lift

C++ lift of the 2019 + PDB BnS server executables.

- Plan: [Docs/Plan/plan.md](Docs/Plan/plan.md)
- Build: clang-cl + lld-link with Wine headers. Run with wine64.
- Gate: `tools/gate.sh`

This repo is public. Do not commit binaries, keys, PDBs or IDA databases.

## Status (2026-11-26)

| Item | State |
| --- | --- |
| First 4 exes | 91.7 % parity. 3 of 4 are above 90 %. LobbyGate is at 89.0 %. |
| LobbyDaemon | Lift in progress: 1151 MATCH (52.2 %), 127 excluded MATCH not counted. Most of the other functions are still `LIFT_STUB` bodies. |
| Method | Gap cards. Each card lifts the PDB class layout and the stub bodies of one class or job group. |
| Last landed | Gap card 24 (AccountInventoryLobbyPacketHandler, +20 MATCH; 11 review rejects excluded), 23 (ExtendJumpingCharacterCreationQuotaJob, +15 MATCH; 7 review rejects excluded), 17 (GameTimeQueue, LobbyDaemon::initialize and the LobbyDaemon ObjPool module, +173 MATCH; 40 review rejects excluded), 20 (NPLobbyMessageHandler part 1, +45 MATCH; 5 review rejects excluded), lift-misc-a (+0 MATCH), 15 (CliSession bodies, +16 MATCH; 3 review rejects excluded) and 04 (NP game service channel and LobbyDaemon startup, +17 MATCH; 4 review rejects excluded). 0 lost in all 5 exes. |
| Checks per landing | Full VS2010 build of all 5 exes, funcdiff against the original, 0 lost MATCH, 0 strict regress. A model review checks each new MATCH without a strict full proof. |
| Next | Engine switch (the gap-04 chain is on main). |

## Parity

<!-- parity:start -->
Last update: card `lift-lobbydaemon-v2b2-m27` (2026-11-26). Tool: `tools/parity.sh` (VS2010 /GL /LTCG build vs original, funcdiff).

| Exe | Parity | MATCH | DIFF | Excluded | Only in original | Total | Mean score | Start | Change | Level |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| CacheGate | **95.1 %** | 467 | 24 | 0 | 0 | 491 | 99.6 | 44.0 % | +51.1 | 95 % ✅ |
| LobbyGate | **93.2 %** | 689 | 49 | 0 | 1 | 739 | 99.4 | 37.9 % | +55.3 | 90 % ✅ |
| SmartCouponDaemon | **95.2 %** | 637 | 32 | 0 | 0 | 669 | 99.6 | 33.6 % | +61.6 | 95 % ✅ |
| PostOfficeDaemon | **95.0 %** | 721 | 37 | 0 | 1 | 759 | 99.6 | 34.5 % | +60.5 | 90 % ✅ |
| LobbyDaemon | **46.8 %** | 1031 | 294 | 127 | 752 | 2204 | 97.3 | 2.2 % | +44.6 | below 90 % |
| **First 4** | **94.6 %** | 2514 | | | | 2658 | | 37.0 % | +57.6 | 90 % ✅ |

| Shared library (functions in 2+ exes) | Parity | MATCH in each exe | DIFF in 1+ exe | Total | Goal |
| --- | ---: | ---: | ---: | ---: | --- |
| BloodLib, Shared, Packet, CRT | **94.7 %** | 522 | 29 | 551 | 99 % |

First 4 and shared library: CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon. LobbyDaemon: lift in progress; most functions are still stubs (only in original). Goal: 95 % per exe, 99 % preferred. Shared library: 99 % preferred. MATCH never holds excluded symbols (review rejected, no honest source fix: [Docs/Parity/excluded.tsv](Docs/Parity/excluded.tsv)); they are in the column Excluded (127 now). Rules: [Docs/Parity/README.md](Docs/Parity/README.md). History: [Docs/Parity/progress.tsv](Docs/Parity/progress.tsv).

| Card | CacheGate | LobbyGate | SmartCouponDaemon | PostOfficeDaemon | LobbyDaemon |
| --- | ---: | ---: | ---: | ---: | ---: |
| `baseline-vs2010` | 44.0 % | 37.9 % | 33.6 % | 34.5 % |  |
| `lift-parity-0` | 59.7 % | 51.0 % | 49.9 % | 49.4 % |  |
| `lift-parity-s1` | 67.4 % | 54.1 % | 54.9 % | 53.6 % |  |
| `lift-parity-s2` | 70.3 % | 57.5 % | 58.0 % | 55.7 % |  |
| `lift-parity-s3` | 76.2 % | 62.5 % | 64.1 % | 62.5 % |  |
| `lift-parity-cg-1` | 78.4 % | 62.5 % | 64.1 % | 62.5 % |  |
| `lift-parity-lg-1` | 78.6 % | 65.8 % | 65.3 % | 63.1 % |  |
| `lift-parity-scd-1` | 78.8 % | 65.9 % | 68.9 % | 63.8 % |  |
| `lift-parity-pod-1` | 78.8 % | 65.9 % | 68.9 % | 67.1 % |  |
| `lift-parity-review-1` | 78.8 % | 65.9 % | 68.9 % | 67.1 % |  |
| `lift-parity-tool-2` | 82.5 % | 68.5 % | 72.3 % | 69.7 % |  |
| `lift-parity-paths-2` | 82.7 % | 69.3 % | 72.9 % | 70.5 % |  |
| `lift-parity-crypto-2` | 83.7 % | 70.0 % | 73.7 % | 71.1 % |  |
| `lift-parity-bloodlib-2` | 85.1 % | 70.6 % | 74.4 % | 71.8 % |  |
| `lift-parity-noinline-2` | 85.5 % | 71.4 % | 75.3 % | 72.9 % |  |
| `lift-parity-helpers-2` | 85.5 % | 71.7 % | 75.3 % | 75.1 % |  |
| `lift-parity-pod-2` | 85.5 % | 71.7 % | 75.3 % | 77.5 % |  |
| `lift-parity-scd-2` | 85.5 % | 71.7 % | 76.2 % | 77.5 % |  |
| `lift-parity-review-2` | 85.5 % | 71.7 % | 76.2 % | 77.5 % |  |
| `lift-parity-perexe-3` | 85.7 % | 72.1 % | 76.5 % | 78.0 % |  |
| `lift-parity-cryptolib-3` | 85.7 % | 77.7 % | 80.7 % | 81.7 % |  |
| `lift-parity-inline-3` | 86.4 % | 78.9 % | 81.2 % | 82.5 % |  |
| `lift-parity-order-3` | 87.6 % | 79.6 % | 82.2 % | 83.1 % |  |
| `lift-parity-consts-3` | 88.8 % | 80.5 % | 83.1 % | 83.9 % |  |
| `lift-parity-arraynew-3` | 88.8 % | 81.2 % | 83.1 % | 83.9 % |  |
| `lift-parity-handlers-3` | 88.8 % | 81.3 % | 83.3 % | 85.0 % |  |
| `manual-parity (astra + opus 6.2)` | 91.2 % | 84.8 % | 87.0 % | 87.6 % |  |
| `lift-parity-dbbind-3` | 91.2 % | 84.8 % | 87.0 % | 87.6 % |  |
| `lift-parity-crypto-4` | 91.2 % | 87.0 % | 88.6 % | 89.1 % |  |
| `lift-parity-net-4` | 92.1 % | 87.6 % | 89.2 % | 89.5 % |  |
| `lift-parity-packet-4` | 92.5 % | 88.4 % | 89.7 % | 90.4 % |  |
| `lift-parity-scd-4` | 92.5 % | 88.4 % | 93.6 % | 90.4 % |  |
| `lift-parity-pod-4` | 92.5 % | 88.4 % | 93.9 % | 91.2 % |  |
| `lift-parity-console-4` | 92.9 % | 89.0 % | 94.2 % | 91.4 % |  |
| `lift-lobbydaemon-0` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 2.2 % |
| `lift-lobbydaemon-2` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 2.2 % |
| `lift-lobbydaemon-1` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 2.2 % |
| `lift-lobbydaemon-3` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 2.2 % |
| `lift-lobbydaemon-4` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 2.2 % |
| `lift-lobbydaemon-5` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 2.2 % |
| `lift-lobbydaemon-6` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 3.7 % |
| `lift-lobbydaemon-8` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 3.9 % |
| `lift-lobbydaemon-10` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 4.4 % |
| `lift-lobbydaemon-7` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 5.5 % |
| `lift-lobbydaemon-11` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 5.9 % |
| `lift-lobbydaemon-9` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 7.9 % |
| `lift-lobbydaemon-12` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 8.8 % |
| `lift-lobbydaemon-13` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 9.9 % |
| `lift-lobbydaemon-17` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 9.9 % |
| `lift-lobbydaemon-14` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 10.9 % |
| `lift-lobbydaemon-18` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 13.7 % |
| `lift-lobbydaemon-15` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 19.8 % |
| `lift-lobbydaemon-16` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 20.1 % |
| `lift-lobbydaemon-19` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 21.2 % |
| `lift-lobbydaemon-20` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 24.6 % |
| `lift-lobbydaemon-23` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 26.5 % |
| `lift-lobbydaemon-21` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 27.4 % |
| `lift-lobbydaemon-24` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 29.3 % |
| `lift-lobbydaemon-22` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 29.3 % |
| `lift-lobbydaemon-gap-int-2` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.6 % |
| `fix7-stub-headers` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.6 % |
| `lift-lobbydaemon-gap-05-job-charge` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.6 % |
| `lift-lobbydaemon-gap-06-job-goods` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.6 % |
| `tools-pdbq-pdbcls-funcdiff-imm` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.7 % |
| `fix3b-ids-12-17` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.8 % |
| `tools-honest-totals` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.8 % |
| `tools-public-clean` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.8 % |
| `lift-lobbydaemon-gap-07-job-wnp-a` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.8 % |
| `lift-lobbydaemon-gap-08-job-session` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 30.9 % |
| `lift-lobbydaemon-gap-19` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 33.5 % |
| `lift-lobbydaemon-gap-11` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |
| `lift-lobbydaemon-gap-09` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |
| `fix-pdb-layout` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |
| `tools-pdb-layout` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |
| `lift-lobbydaemon-gap-10` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |
| `lift-lobbydaemon-gap-16` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |
| `lift-lobbydaemon-gap-14` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |
| `lift-lobbydaemon-gap-12` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 34.7 % |
| `lift-lobbydaemon-gap-26` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 36.2 % |
| `lift-lobbydaemon-gap-25` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 36.7 % |
| `lift-lobbydaemon-gap-04-npgame` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 37.3 % |
| `lift-lobbydaemon-gap-15` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 37.8 % |
| `lift-misc-a` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 37.8 % |
| `lift-lobbydaemon-gap-20` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 39.7 % |
| `lift-lobbydaemon-gap-17` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 45.7 % |
| `lift-lobbydaemon-gap-23` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 46.1 % |
| `lift-lobbydaemon-gap-24` | 92.9 % | 89.0 % | 94.2 % | 91.4 % | 46.5 % |
| `lift-parity-shared-5` | 93.1 % | 89.6 % | 94.2 % | 91.6 % | 46.5 % |
| `lift-parity-lg-5a` | 93.1 % | 91.5 % | 94.2 % | 91.6 % | 46.5 % |
| `lift-parity-lg-5b` | 93.1 % | 93.1 % | 94.2 % | 91.6 % | 46.5 % |
| `lift-parity-pod-5a` | 93.1 % | 93.1 % | 94.2 % | 93.0 % | 46.5 % |
| `lift-parity-pod-5b` | 93.1 % | 93.1 % | 94.2 % | 93.8 % | 46.5 % |
| `lift-parity-cgscd-5` | 94.3 % | 93.1 % | 94.6 % | 93.8 % | 46.5 % |
| `lift-lobbydaemon-v2b-pod-01` | 94.3 % | 93.1 % | 94.6 % | 94.3 % | 46.5 % |
| `lift-lobbydaemon-v2b-wmain-01` | 94.5 % | 93.1 % | 94.9 % | 94.3 % | 46.5 % |
| `lift-lobbydaemon-v2b-cg-02` | 94.7 % | 93.1 % | 94.9 % | 94.3 % | 46.5 % |
| `lift-lobbydaemon-v2b-merge-01` | 94.7 % | 93.1 % | 94.9 % | 94.3 % | 46.5 % |
| `lift-lobbydaemon-v2b-merge-02` | 94.7 % | 93.1 % | 94.9 % | 94.6 % | 46.5 % |
| `lift-lobbydaemon-v2b-merge-03c` | 94.9 % | 93.2 % | 95.1 % | 94.9 % | 46.5 % |
| `lift-lobbydaemon-v2b2-m28` | 95.1 % | 93.2 % | 95.2 % | 95.0 % | 46.5 % |
| `lift-lobbydaemon-v2b2-m27` | 95.1 % | 93.2 % | 95.2 % | 95.0 % | 46.8 % |
<!-- parity:end -->
