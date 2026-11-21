# bns-lift

C++ lift of the 2019 + PDB BnS server executables.

- Plan: [Docs/Plan/plan.md](Docs/Plan/plan.md)
- Build: clang-cl + lld-link with Wine headers. Run with wine64.
- Gate: `tools/gate.sh`

This repo is public. Do not commit binaries, keys, PDBs or IDA databases.

## Parity

<!-- parity:start -->
Last update: card `lift-lobbydaemon-3` (2026-11-21). Tool: `tools/parity.sh` (VS2010 /GL /LTCG build vs original, funcdiff).

| Exe | Parity | MATCH | DIFF | Only in original | Total | Mean score | Start | Change | Level |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| CacheGate | **92.9 %** | 456 | 32 | 3 | 491 | 99.3 | 44.0 % | +48.9 | 90 % ✅ |
| LobbyGate | **89.0 %** | 658 | 78 | 3 | 739 | 98.9 | 37.9 % | +51.2 | below 90 % |
| SmartCouponDaemon | **94.2 %** | 630 | 37 | 2 | 669 | 99.5 | 33.6 % | +60.5 | 90 % ✅ |
| PostOfficeDaemon | **91.4 %** | 694 | 60 | 5 | 759 | 99.1 | 34.5 % | +56.9 | 90 % ✅ |
| **All 4** | **91.7 %** | 2438 | | | 2658 | | 37.0 % | +54.7 | 90 % ✅ |

| Shared library (functions in 2+ exes) | Parity | MATCH in each exe | DIFF in 1+ exe | Total | Goal |
| --- | ---: | ---: | ---: | ---: | --- |
| BloodLib, Shared, Packet, CRT | **94.0 %** | 516 | 33 | 549 | 99 % |

Goal: 95 % per exe, 99 % preferred. Shared library: 99 % preferred. Rules: [Docs/Parity/README.md](Docs/Parity/README.md). History: [Docs/Parity/progress.tsv](Docs/Parity/progress.tsv).

| Card | CacheGate | LobbyGate | SmartCouponDaemon | PostOfficeDaemon |
| --- | ---: | ---: | ---: | ---: |
| `baseline-vs2010` | 44.0 % | 37.9 % | 33.6 % | 34.5 % |
| `lift-parity-0` | 59.7 % | 51.0 % | 49.9 % | 49.4 % |
| `lift-parity-s1` | 67.4 % | 54.1 % | 54.9 % | 53.6 % |
| `lift-parity-s2` | 70.3 % | 57.5 % | 58.0 % | 55.7 % |
| `lift-parity-s3` | 76.2 % | 62.5 % | 64.1 % | 62.5 % |
| `lift-parity-cg-1` | 78.4 % | 62.5 % | 64.1 % | 62.5 % |
| `lift-parity-lg-1` | 78.6 % | 65.8 % | 65.3 % | 63.1 % |
| `lift-parity-scd-1` | 78.8 % | 65.9 % | 68.9 % | 63.8 % |
| `lift-parity-pod-1` | 78.8 % | 65.9 % | 68.9 % | 67.1 % |
| `lift-parity-review-1` | 78.8 % | 65.9 % | 68.9 % | 67.1 % |
| `lift-parity-tool-2` | 82.5 % | 68.5 % | 72.3 % | 69.7 % |
| `lift-parity-paths-2` | 82.7 % | 69.3 % | 72.9 % | 70.5 % |
| `lift-parity-crypto-2` | 83.7 % | 70.0 % | 73.7 % | 71.1 % |
| `lift-parity-bloodlib-2` | 85.1 % | 70.6 % | 74.4 % | 71.8 % |
| `lift-parity-noinline-2` | 85.5 % | 71.4 % | 75.3 % | 72.9 % |
| `lift-parity-helpers-2` | 85.5 % | 71.7 % | 75.3 % | 75.1 % |
| `lift-parity-pod-2` | 85.5 % | 71.7 % | 75.3 % | 77.5 % |
| `lift-parity-scd-2` | 85.5 % | 71.7 % | 76.2 % | 77.5 % |
| `lift-parity-review-2` | 85.5 % | 71.7 % | 76.2 % | 77.5 % |
| `lift-parity-perexe-3` | 85.7 % | 72.1 % | 76.5 % | 78.0 % |
| `lift-parity-cryptolib-3` | 85.7 % | 77.7 % | 80.7 % | 81.7 % |
| `lift-parity-inline-3` | 86.4 % | 78.9 % | 81.2 % | 82.5 % |
| `lift-parity-order-3` | 87.6 % | 79.6 % | 82.2 % | 83.1 % |
| `lift-parity-consts-3` | 88.8 % | 80.5 % | 83.1 % | 83.9 % |
| `lift-parity-arraynew-3` | 88.8 % | 81.2 % | 83.1 % | 83.9 % |
| `lift-parity-handlers-3` | 88.8 % | 81.3 % | 83.3 % | 85.0 % |
| `manual-parity (astra + opus 6.2)` | 91.2 % | 84.8 % | 87.0 % | 87.6 % |
| `lift-parity-dbbind-3` | 91.2 % | 84.8 % | 87.0 % | 87.6 % |
| `lift-parity-crypto-4` | 91.2 % | 87.0 % | 88.6 % | 89.1 % |
| `lift-parity-net-4` | 92.1 % | 87.6 % | 89.2 % | 89.5 % |
| `lift-parity-packet-4` | 92.5 % | 88.4 % | 89.7 % | 90.4 % |
| `lift-parity-scd-4` | 92.5 % | 88.4 % | 93.6 % | 90.4 % |
| `lift-parity-pod-4` | 92.5 % | 88.4 % | 93.9 % | 91.2 % |
| `lift-parity-console-4` | 92.9 % | 89.0 % | 94.2 % | 91.4 % |
| `lift-lobbydaemon-0` | 92.9 % | 89.0 % | 94.2 % | 91.4 % |
| `lift-lobbydaemon-2` | 92.9 % | 89.0 % | 94.2 % | 91.4 % |
| `lift-lobbydaemon-1` | 92.9 % | 89.0 % | 94.2 % | 91.4 % |
| `lift-lobbydaemon-3` | 92.9 % | 89.0 % | 94.2 % | 91.4 % |
<!-- parity:end -->
