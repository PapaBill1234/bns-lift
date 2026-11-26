# Handoff: lift-lobbydaemon-gap-10-job-account

Date: 2026-11-25. Branch: `gap-10`. Base: `e68e5d0` (fix7).
Code commits: `9959c13`, `1ff36c8`, `02f6ef5`, `fe2fb70`. This handoff is in the next commit.

## Scope

| Module | Card IDs | NOREF MATCH | NOREF DIFF |
| --- | --- | --- | --- |
| DepositMileageJob | 6 | 5 | 1 |
| SecondPasswordGetStatusJob | 7 | 6 | 1 |
| SecondPasswordIsVerifiedJob | 7 | 6 | 1 |
| SetupNpScheduleInfoJob | 7 | 1 | 6 |
| TakeAccountTimeBasedPlayRewardJob | 8 | 4 | 4 |
| Total | 35 | 22 | 13 |

All 35 card IDs are paired in the NOREF build. No card ID is paired in the REF build: no live code creates these jobs, so LTCG drops them.

Not card IDs, but lifted:

| Item | NOREF |
| --- | --- |
| `DepositMileageJob` ctor, `depositReq` | MATCH |
| `TakeAccountTimeBasedPlayRewardJob::takeAccountTimeBasedPlayRewardResponse` | DIFF 90.1 |
| `CliSessionJob` ctor and dtor (were LIFT_STUB; a stub callee folds under ICF and /LTCG) | MATCH |
| `NPGameServiceChannel::SendRequestPresenceMessage`, `SendRequestVirtualCurrencyDeposit` (PDB inline methods; declared in `NPServiceChannel.h`, bodies in `DepositMileageJob.cpp`) | inlined |

Not done:

| Function | Reason |
| --- | --- |
| `SetupNpScheduleInfoJob::getPromotionPolicyAck` (0x73630) | About 3000 bytes. It builds `TimeBasedPlaySeasonSchedule` data. It stays `LIFT_STUB`. Later card. |
| `deallocate_me` of the 5 jobs | `ObjPool` is not in lift_lobbydaemon. They stay `LIFT_STUB`. |

## What changed

- Class layouts come from `tools/pdbcls.py LobbyDaemon <Class>`: State enums, `_def`, members, nested types and static_asserts.
- Bodies come from the 2019 + PDB pseudocode. PDB names and PDB return types only. The server checks stay (null params, range checks, user id vs `ID128_GUID_ZERO`).
- The transaction delete is `tran->~NPLobbyJobTransaction()` and then `Memory::_Manager[2]->Free(tran, kFile, line)`.
- The log macros check `this != nullptr` in every log call, as the original does.
- `DepositMileageJob` ctor copies `ID128_GUID_ZERO` into `_userId` (the original loads the global; the pseudocode shows 0).
- `TakeAccountTimeBasedPlayRewardJob` reads the contents rule through the public `ContentsRuleConfig` getter.
- `SecondPasswordIsVerifiedJob::init` sends `SendSecondPasswordGetStatusFail` on one path. The original does this too. It is client-visible, so it stays.
- `SendRequestVirtualCurrencyDeposit` writes the client address with `inet_ntoa` only when the address is not 0. The non-zero path is not in the binary ❓.
- CMakeLists.txt is not changed. Baselines are not changed. No inline asm or byte tricks. IDA was not opened.

## Checks

| Check | Result |
| --- | --- |
| NOREF build `fe2fb70` (`g10/builds/main/noref-build-Dchmnihz`) | 1246 paired, 999 MATCH (base 1205 / 973), lost 0 |
| REF build `fe2fb70` (`g10/builds/main/main-build-XrDjmXOZ`) | 841 paired, 674 MATCH (no change) |
| `pilot.py gate` (35 IDs, `/data/parity-v2/gap/gate-gap10.json`) | 35 of 35 clear (before: 0 of 35); eligible pool 264 -> 301 |
| `gate_fast.sh` on a fresh clone of `fe2fb70` | rc 0, "parity ok"; REF MATCH per exe unchanged |
| strict (cfg), `/data/parity-v2/gap/full-10-strict` vs `base-06/strict` | no regress; LobbyGate cfg 515 -> 516; LobbyDaemon cc 515 -> 517, cfg 594 -> 596 |
| `proof.py --base e68e5d0 --candidate fe2fb70` | pass; lost 0, strict_regress 0, cfg_regress 0, reasons 0, review 0; `integrate.check_proof` dry run PASS |

## Card IDs that DIFF (NOREF)

| ID | Score | Cause |
| --- | --- | --- |
| `DepositMileageJob::depositAck` 0x4aa40 | 97.1 | Register allocation and block order ❓ |
| `SecondPasswordGetStatusJob::requestGetStatus` 0x71a60 | 91.8 | Register allocation (r12/rbp vs rbp/r13) ❓ |
| `SecondPasswordIsVerifiedJob::requestIsVerified` 0x72640 | 91.8 | Same as requestGetStatus ❓ |
| `SetupNpScheduleInfoJob` ctor 0x72d90, dtor 0x72e40 | 83.3, 91.7 | The deque array ctor/dtor helpers differ (eh vector iterator callees) ❓ |
| `SetupNpScheduleInfoJob::work` 0x72eb0 | 84.2 | Calls `getPromotionPolicyAck`, a stub |
| `SetupNpScheduleInfoJob::tryListCurrentPromotions` 0x72ff0, `tryGetPromotionPolicy` 0x733e0 | 63.5, 59.3 | Call the stub send functions 0xd1de0 and 0xd1f00 (gap-04 scope) |
| `SetupNpScheduleInfoJob::listCurrentPromotionsAck` 0x73160 | 98.2 | deque push_back codegen ❓ |
| `TakeAccountTimeBasedPlayRewardJob::init` 0x78a50 | 95.2 | Register allocation ❓ |
| `TakeAccountTimeBasedPlayRewardJob::takeAccountTimeBasedPlayRewardReq` 0x78ec0 | 59.8 | Calls stubs in the NP reward chain ❓ |
| `TakeAccountTimeBasedPlayRewardJob::sendOk` 0x79b30, `sendFail` 0x79eb0 | 63.0, 66.7 | LTCG changes the argument registers (one caller); the frame differs ❓ |

## Open items

- `NPServiceChannel.h` gets 2 inline declarations. gap-04 also edits this file. Expect a small merge conflict.
- The 3 packet handlers 0x91ab0, 0x91e80 and 0x94910 are still `LIFT_STUB`. When they are lifted, the jobs become live in the REF build.
- vendor/zstd/src is git-ignored. Copy it into each scratch clone.
