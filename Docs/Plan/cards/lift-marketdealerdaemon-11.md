# lift-marketdealerdaemon-11: MarketDealerDaemon lift: JobContext part 4 (abandon bid, purchase jobs)

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/MarketDealerDaemon/MarketDealerDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/MarketDealerDaemon/bin/MarketDealerDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" and `Docs/layout.md` first. Read the handoffs of `lift-marketdealerdaemon-1` to `-10`.

## Modules (in `src/Server/Economy/MarketDealerDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are real functions without EH funclets and scalar deleting destructors. Pseudocode: `.scratch/hr/<Module>.c` (copy of `~/.cache/bns-lift/hr/MarketDealerDaemon/`). Before you lift a function, look for it in `src/` (grep the PDB name). Do not lift it two times.
- JobContext `JobContext.obj` (20 functions, lines 6,683 to 8,933 of `JobContext.c`): AbandonBidJob 0x123e0 (5), ReservePurchaseJob 0x131f0 (5), CancelPurchaseReservationJob 0x13f70 (5), RegisterPurchaseJob 0x149d0 (5).
- Add the bodies to `JobContext.cpp`. The classes are in `JobContext.h` (card 8).
- The job destructors `JobContext::~JobContext` and `<Job>::~<Job>` in `AgentPacketHandler.obj` are the same code. Lift each one time.
- Total: 20 functions, 2,251 pseudocode lines.

Pattern: `src/Server/SmartCouponDaemon/CouponJob.cpp` (job classes). Read each pattern one time. Do not search other servers.

## Tasks
1. Read `JobContext.c` lines 6,683 to 8,933 only. Write the C++ of each half before you read the next half. Lift the functions to C++ with the PDB types (`include/pdb/MarketDealerDaemon/types.h`). Calls to code of later cards stay as declarations.
2. Add the new `.cpp` files to `lift_marketdealerdaemon` in `CMakeLists.txt`.
3. Run `.scratch/gate_errors.sh` after each module. CacheGate, SmartCouponDaemon, LobbyGate and PostOfficeDaemon must still link.

## Files
- `src/Server/Economy/MarketDealerDaemon/`
- `include/pdb/`
- `include/vs2010/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
