# lift-lobbydaemon-0: LobbyDaemon skeleton and stubs

| Item | Value |
| --- | --- |
| Source build | LobbyDaemon 2019 + PDB (VS2010 SP1) |
| Exe | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.exe` |
| PDB | `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyDaemon/LobbyDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/LobbyDaemon/<Module>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/LobbyDaemon/index.tsv` |
| Wave | 0 |
| Model | opus |

## Read first

- Read `Docs/Plan/plan.md`: “Lift method”, “Server order”, and “Planner chain”.
- Read `Docs/Parity/lessons.md`: A12 (PDB types), A18 (destructors), A22 (per-exe source), and C4 (build facts).
- Use `Docs/Plan/cards/lift-cg-5.md` as the pattern for the link tasks. Use the `LobbyGate` target in `CMakeLists.txt` as the pattern for the build.
- Read `Docs/Plan/cards/lift-lobbydaemon-1.md` for the common file paths and the list of missing functions.

## Modules

This wave sets up files and stubs. It does not lift function logic. The scope is the 108 modules in the tables below. The module tables of `lift-lobbydaemon-1` to `lift-lobbydaemon-57` give the function ranges of each card. Use `index.tsv` for function RVAs. Each count is the number of `index.tsv` rows of the module, without scalar deleting destructors. Each range gives the lowest and the highest RVA of these rows. A range does not assign every RVA in it to the module.

### New server modules (96)

| Module | Functions | RVA range |
| --- | ---: | --- |
| `AbandonChargeJob` | 13 | `0x4f30` to `0x11e7c0` |
| `AccountInventoryChannel` | 19 | `0x64e0` to `0x8790` |
| `AccountInventoryLobbyPacketHandler` | 24 | `0x87c0` to `0xb510` |
| `ActivateGradeJob` | 15 | `0xb9e0` to `0x11e800` |
| `AddSlotJob` | 29 | `0xd1e0` to `0x11e840` |
| `AuctionBidJob` | 10 | `0x110d0` to `0x11e880` |
| `AuctionDeliverJob` | 14 | `0x12230` to `0x11e8c0` |
| `AuctionEscrow` | 3 | `0x135e0` to `0x14770` |
| `AuctionEscrowJob` | 11 | `0x14cb0` to `0x11e900` |
| `AuctionRollbackEscrowJob` | 11 | `0x15fa0` to `0x11e940` |
| `BLDaemonInfo` | 9 | `0x403c0` to `0x416f0` |
| `BindCharacterSlotJob` | 11 | `0x16e90` to `0x11e980` |
| `BoundedList` | 4 | `0x18540` to `0x18790` |
| `CancelWaitCharacterDeletionJob` | 14 | `0x18890` to `0x11e9c0` |
| `ChangeCharacterAppearanceJob` | 27 | `0x1ab60` to `0x11ea00` |
| `ChangeCharacterRaceJob` | 26 | `0x1ea40` to `0x11ea40` |
| `ChangeCharacterSexJob` | 26 | `0x22a60` to `0x11ea80` |
| `ChangeUserNameJob` | 22 | `0x26990` to `0x11eac0` |
| `Character` | 21 | `0x30e90` to `0x328f0` |
| `CliSession` | 110 | `0x329d0` to `0x11ebc0` |
| `CliSessionJob` | 3 | `0x3bef0` to `0x3c010` |
| `CliSessionManager` | 7 | `0x3c080` to `0x61490` |
| `CliSessionTable` | 45 | `0x3cfe0` to `0xc2510` |
| `CreateCharacterJob` | 15 | `0x41840` to `0x11ec00` |
| `CreateInitialUserNameJob` | 11 | `0x2fc20` to `0x11eb80` |
| `DeleteCharacterJob` | 25 | `0x45040` to `0x11ec40` |
| `DepositMileageJob` | 11 | `0x49b40` to `0x11ec80` |
| `EndWaitGameWorldJob` | 8 | `0x4afe0` to `0x11ecc0` |
| `EnterGameWorldJob` | 9 | `0x84e00` to `0x11f1c0` |
| `ExtendJumpingCharacterCreationQuotaJob` | 34 | `0x2a300` to `0x11eb40` |
| `FsdShowcaseRecord` | 1 | `0x2e0b0` |
| `GameTimeSchedule` | 12 | `0x4b8e0` to `0x4c6a0` |
| `GameWorld` | 39 | `0x4c810` to `0x96d20` |
| `GamedChannel` | 64 | `0x80300` to `0x84d20` |
| `GetChargeInfoJob` | 11 | `0x50550` to `0x11ed00` |
| `GetGoodsCountJob` | 13 | `0x51460` to `0x11ed40` |
| `GetLobbyServiceItemJob` | 13 | `0x52060` to `0x11ed80` |
| `GiveupWaitGameWorldJob` | 9 | `0x52cf0` to `0x11edc0` |
| `GradeService` | 16 | `0x53370` to `0x547b0` |
| `InfoGateChannel` | 13 | `0x2e6d0` to `0x2f300` |
| `InitCliSessionWlobbyTokenJob` | 9 | `0x54830` to `0x11ee00` |
| `InitCliSessionWnpTokenJob` | 5 | `0x98120` to `0x11f2c0` |
| `KickJob` | 16 | `0x861a0` to `0x11f200` |
| `LeaveGameWorldJob` | 9 | `0x877b0` to `0x11f240` |
| `ListGoodsJob` | 13 | `0x54ee0` to `0x11ee40` |
| `ListLobbyServiceItemJob` | 13 | `0x55b20` to `0x11ee80` |
| `LobbyCharacterDeletionScheduler` | 4 | `0x56780` to `0x56ce0` |
| `LobbyConfig` | 2 | `0x98980` to `0x990f0` |
| `LobbyDB` | 95 | `0x9fdb0` to `0xbb3b0` |
| `LobbyDaemon` | 54 | `0x991c0` to `0x9fd70` |
| `LobbyEvent` | 11 | `0xbb7f0` to `0xbbcf0` |
| `LobbyGamePacketHandler` | 60 | `0x88220` to `0x96360` |
| `LobbyGateChannel` | 74 | `0xbbe90` to `0xc11d0` |
| `LobbyInfoGatePacketHandler` | 3 | `0x56d40` to `0x57880` |
| `LobbyJSON` | 1 | `0x2f830` |
| `LobbyJob` | 17 | `0xc1670` to `0xc24c0` |
| `LobbyLobbyGatePacketHandler` | 35 | `0xc25c0` to `0xcb330` |
| `LobbyLocale` | 10 | `0x57ab0` to `0x585d0` |
| `LobbyManagePacketHandler` | 12 | `0x58770` to `0x59820` |
| `LobbyMessage` | 6 | `0x2f9d0` to `0x2fb60` |
| `LobbyPerfMonitor` | 5 | `0x59ce0` to `0x59f40` |
| `LobbyPredefine` | 4 | `0x96480` to `0x966a0` |
| `LobbyService` | 50 | `0x6c330` to `0xefb20` |
| `LobbyStats` | 5 | `0x5a0b0` to `0x5a5c0` |
| `LobbyTick` | 8 | `0x5a610` to `0x5aa20` |
| `LobbyToken` | 10 | `0x96750` to `0x97990` |
| `LogoutInGameWorldJob` | 9 | `0x5aa80` to `0x11eec0` |
| `LogoutJob` | 9 | `0x97a10` to `0x11f280` |
| `ManageChannel` | 12 | `0x5b140` to `0x5beb0` |
| `MembershipMileage` | 13 | `0x5bff0` to `0x9f540` |
| `Mileage` | 49 | `0x5d370` to `0x62490` |
| `MileageDailyLimit` | 1 | `0x62560` |
| `NPLobbyMessageHandler` | 48 | `0xcb710` to `0xcf9e0` |
| `NPServiceChannel` | 40 | `0xcfac0` to `0xd2310` |
| `PcCafe` | 2 | `0x62e90` to `0x63350` |
| `PcCafeMileage` | 3 | `0x633b0` to `0x636b0` |
| `PostOfficeChannel` | 7 | `0x639f0` to `0x64420` |
| `PostOfficeClientSideHandlerList` | 1 | `0x32b50` |
| `PostOfficePacketHandler` | 4 | `0x646f0` to `0x64a20` |
| `RecoverPcJob` | 15 | `0x64e50` to `0x11ef00` |
| `RefCntList` | 4 | `0x64c80` to `0x64da0` |
| `RenameCharacterJob` | 27 | `0x66ae0` to `0x11ef40` |
| `RuleSet` | 1 | `0x6bfc0` |
| `SecondPasswordGetStatusJob` | 10 | `0x71550` to `0x11ef80` |
| `SecondPasswordIsVerifiedJob` | 10 | `0x72110` to `0x11efc0` |
| `SetupNpScheduleInfoJob` | 34 | `0x72cf0` to `0x11f000` |
| `StartChargeJob` | 11 | `0x75570` to `0x11f040` |
| `StartCliSessionWlobbyTokenJob` | 15 | `0x76250` to `0x11f080` |
| `StartCliSessionWnpTokenJob` | 50 | `0xd2340` to `0x11f300` |
| `StopChargeJob` | 11 | `0x77c90` to `0x11f0c0` |
| `TakeAccountTimeBasedPlayRewardJob` | 12 | `0x788a0` to `0x11f100` |
| `TakeGoodsJob` | 13 | `0x79f00` to `0x11f140` |
| `TencentUIC` | 4 | `0x7ac30` to `0x7b0a0` |
| `TransactionChannel` | 9 | `0x7b0d0` to `0x7b7e0` |
| `TryEnterGameWorldJob` | 28 | `0x7b840` to `0x11f180` |
| `WaitQueue` | 8 | `0xdc540` to `0xdca20` |

### New common modules (6)

| Module | Functions | RVA range |
| --- | ---: | --- |
| `BannedWordFilterLib` | 7 | `0x118a70` to `0x118e80` |
| `BannedWordFilterLoader` | 8 | `0x118fa0` to `0x119720` |
| `ConstFilterChat` | 1 | `0x119760` |
| `ConstFilterName` | 2 | `0x119770` to `0x119870` |
| `FsdDecomposer` | 6 | `0x119c10` to `0x11a040` |
| `PerfCounterProvider` | 4 | `0xe7ae0` to `0x11f3a0` |

### Missing common functions (18)

Use only the functions that `lift-lobbydaemon-1` lists for each module. Use the module file as the pattern. Put the stub in the implementation file that will own the function in wave 1. Do not put a second definition in the file that only uses it.

| Module | Missing functions | RVA range | Pattern |
| --- | ---: | --- | --- |
| `ContentsRuleConfigDefinition` | 4 | `0x29730` to `0x2a210` | `src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp` |
| `CryptoKey` | 2 | `0x10dfb0` to `0x10dfe0` | `src/Security/source/BloodCrypto/key/CryptoKey.cpp` |
| `Db` | 1 | `0xe81f0` | `src/Server/BloodLib/source/Db.cpp` |
| `NPChannel2` | 4 | `0x2700` to `0x2be0` | `src/Server/Shared/NPChannel2.cpp` |
| `Network` | 1 | `0xe4900` | `src/Server/BloodLib/source/Network.cpp` |
| `SharedChannel` | 6 | `0x4b70` to `0x4e20` | `src/Server/Shared/SharedChannel.cpp` |

## Tasks

1. Use only the exe and PDB in the table for LobbyDaemon. Do not use `LobbyDaemon2019.exe` or a 381 file. Check that the exe and PDB match. Use IDA only if necessary. Close the database when you are done. Never read or probe the IDA licence.
2. Run `tools/pdb2h.py` with the PDB and `LobbyDaemon` to make `include/pdb/LobbyDaemon/types.h`. Use PDB names, signatures, and layouts.
3. Write one header and one `.cpp` for each new server module in `src/Server/LobbyDaemon/`. Put each stub in its own module `.cpp`. Keep `ObjectPool.cpp` and `ObjectPool.h` unchanged. Use one owner for each definition. Do not add a shared stub file. Later cards in the same wave must not edit the same `.cpp`.
4. Set up the six new common modules at the paths for `lift-lobbydaemon-1`. Add stubs for the 18 missing common functions only. Reuse existing definitions. Keep the effective bodies of the other server builds unchanged. Use a LobbyDaemon-only source variant if a shared change would affect them.
5. Use one marker macro for all new stub bodies. Record the macro name and the grep command in the handoff. Do not let a stub report success for work it does not do. Let the compiler emit its own thunks, deleting destructors, and exception helpers. Do not add duplicate CRT or library symbols. List symbols with no lift body under “Not done” with the reason and RVA.
6. Add `LobbyDaemon` with `lift_exe` in `CMakeLists.txt`. Link it to `lift_common`. Use the existing CRT support. Include the module objects in the target and make the target link. Do not use a global stub file to fix unresolved symbols.
7. Add LobbyDaemon support to `tools/vs2010/build.sh` and `tools/parity.sh`. Check that `tools/parity.sh LobbyDaemon` builds with VS2010 and prints a LobbyDaemon MATCH count from `funcdiff`. Run the gate and the parity check for CacheGate, LobbyGate, SmartCouponDaemon, and PostOfficeDaemon. Check the set of MATCH functions. Do not rely on the total alone.

## Files

- `include/pdb/LobbyDaemon/types.h`
- `src/Server/LobbyDaemon/*.h` and `src/Server/LobbyDaemon/*.cpp` (stub bodies only; exclude existing `ObjectPool.cpp` and `ObjectPool.h`)
- New common stubs: `src/External/BannedWordFilter/BannedWordFilterLib.cpp`, `src/External/BannedWordFilter/BannedWordFilterLoader.cpp`, `src/External/BannedWordFilter/ConstFilterChat.cpp`, `src/External/BannedWordFilter/ConstFilterName.cpp`, `src/library/FsdReader/FsdDecomposer.cpp`, and `src/Server/BloodLib/source/PerfCounterProvider.cpp`.
- Missing common stubs: use the paths in the missing common table and in `lift-lobbydaemon-1`. Record any LobbyDaemon-only variant in the handoff.
- `CMakeLists.txt`
- `tools/parity.sh`
- `tools/vs2010/build.sh`

## Handoff

Write `Docs/Plan/handoffs/lift-lobbydaemon-0.md`. Give the gate result, the module paths, the stub marker, and the MATCH comparison for all five targets. Under “Not done”, list each stub and each other function with no lift body. Give each function's PDB name, RVA, and reason. If LobbyDaemon has no prior baseline, record this first MATCH count for the next wave. Do not update the committed parity baselines in this card.

## Done when

- `tools/gate.sh` prints `gate ok`.
- The LobbyDaemon target links in both build paths. `funcdiff` prints a LobbyDaemon MATCH count.
- Each function in scope is lifted or is listed under “Not done” with its RVA. A stub does not count as a lift.
- No MATCH function is lost in CacheGate, LobbyGate, SmartCouponDaemon, or PostOfficeDaemon. Count missing MATCH names as losses.
- LobbyDaemon MATCH does not go down if a prior result exists. If there is no prior result, the handoff gives the initial count.
