# bns-lift

PRIVATE. C++ lift of the 2019 + PDB BnS server executables.

- Plan: [Docs/Plan/plan.md](Docs/Plan/plan.md)
- Build: clang-cl + lld-link with Wine headers. Run with wine64.
- Gate: `tools/gate.sh`

Do not push this code to a public repo. Do not commit binaries or keys.

## Parity

<!-- parity:start -->
Last update: card `lift-parity-scd-2` (2026-11-18). Tool: `tools/parity.sh` (VS2010 /GL /LTCG build vs original, funcdiff).

| Exe | Parity | MATCH | DIFF | Only in original | Total | Mean score | Start | Change | Level |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| CacheGate | **85.5 %** | 420 | 67 | 4 | 491 | 98.5 | 44.0 % | +41.5 | below 90 % |
| LobbyGate | **71.7 %** | 530 | 128 | 81 | 739 | 98.0 | 37.9 % | +33.8 | below 90 % |
| SmartCouponDaemon | **76.2 %** | 510 | 109 | 50 | 669 | 98.3 | 33.6 % | +42.6 | below 90 % |
| PostOfficeDaemon | **77.5 %** | 588 | 118 | 53 | 759 | 98.3 | 34.5 % | +43.0 | below 90 % |
| **All 4** | **77.1 %** | 2048 | | | 2658 | | 37.0 % | +40.1 | below 90 % |

| Shared library (functions in 2+ exes) | Parity | MATCH in each exe | DIFF in 1+ exe | Total | Goal |
| --- | ---: | ---: | ---: | ---: | --- |
| BloodLib, Shared, Packet, CRT | **84.4 %** | 421 | 78 | 499 | 99 % |

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
<!-- parity:end -->
