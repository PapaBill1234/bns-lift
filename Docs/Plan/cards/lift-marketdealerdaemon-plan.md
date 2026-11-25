# lift-marketdealerdaemon-plan: plan the lift of MarketDealerDaemon

Repo: bns-lift (PRIVATE). You are a planner card. You do not lift code. You write cards and queue rows.

| Item | Value |
| --- | --- |
| Server | MarketDealerDaemon |
| Slug | marketdealerdaemon |
| IDA database | `<work-root>/ida/lift/MarketDealerDaemon/MarketDealerDaemon.exe` |
| PDB | `<work-root>/Service_348_8349/Service/MarketDealerDaemon/bin/MarketDealerDaemon.pdb` |
| Dep of your first card | `lift-postofficedaemon-5` |

Read `Docs/Plan/plan.md` ("Lift method", "Server order", "Planner chain") first. Read the handoffs in `Docs/Plan/handoffs/` for the state of `src/common/`.

## Tasks
1. List the PDB modules and their function counts. Use `llvm-pdbutil dump -modules -symbols` on the PDB. Write the output to `.scratch/`. Read only the parts that you need. Use IDA only if the PDB tool fails.
2. Remove the CRT modules (wcrtexe, crtexe, ehvecdtr, gshandler, chkstk, atonexit, pesect, merr, ti_inst, unhandld, gs_*) and the library modules that `vendor/` already holds.
3. Compare each remaining module with `src/common/`. A module that is already lifted there is skipped. A module with the same name but other functions gets a card only for the missing functions.
4. Group the remaining modules into cards. Each card has 20 to 40 functions (real functions, not EH funclets or scalar deleting destructors) and 2,500 pseudocode lines or fewer. Get the line counts from `.scratch/hr/index.tsv` (last line of each module). One card holds one large module, or 2 to 4 small modules. Split a module with more than 2,500 pseudocode lines over more cards, and give the function addresses of each part. A card must finish in one stage of 25 turns: a card that needs more stages reads its pseudocode again in each stage. Shared framework modules go first, in `src/common/`. Server modules go last, in `src/MarketDealerDaemon/`. The last lift card builds the full exe (CMake target `MarketDealerDaemon` with `lift_exe`, linked to `lift_common`).
5. Write each card as `Docs/Plan/cards/lift-marketdealerdaemon-N.md` (N = 1, 2, ...). If a module has the same role as a module of an earlier server (for example the daemon main module, the DB module, a channel or a packet handler), name that source file in the card as the pattern: "Pattern: `src/<Server>/<File>.cpp`". The session then reads the pattern one time and does not search for it. Use the format of `Docs/Plan/cards/lift-cg-5.md`: title, IDA + PDB paths, modules with function counts, tasks, Files, Done when.
6. Write `Docs/Plan/cards/lift-marketdealerdaemon-verify.md`. Use the format of `Docs/Plan/cards/lift-cg-verify.md`.
7. Write the next planner card `Docs/Plan/cards/lift-<next slug>-plan.md` from `Docs/Plan/planner-template.md`. Replace `{SERVER}`, `{SLUG}` and `{PREV_DEP}`. The next server is the next row in "Server order". `{PREV_DEP}` is the id of your last lift card (not the verify card). If MarketDealerDaemon is the last server, do not write a next planner.
8. Write `Docs/Plan/queue/lift-marketdealerdaemon-plan.tsv` (format below).
9. Run `tools/gate.sh`.

## Queue file format
One row per line. 9 columns, separated by one TAB. No header is necessary.

| Column | Value |
| --- | --- |
| id | `lift-marketdealerdaemon-N`, `lift-marketdealerdaemon-verify` or `lift-<next slug>-plan` |
| kind | `lift` |
| model | `opus` |
| crate | `-` |
| paths | Comma list of the card "Files" (no spaces). Planner: `Docs/Plan/cards/,Docs/Plan/queue/` |
| deps | Card 1: `lift-postofficedaemon-5`. Card N: `lift-marketdealerdaemon-<N-1>`. Verify and next planner: the last lift card. |
| turns | `150` for lift cards and verify. `100` for the planner. |
| status | `ready` |
| title | `Lift MarketDealerDaemon: <short scope>` (no TAB) |

Put the rows in this order: lift cards, verify, next planner.

## Files
- `Docs/Plan/cards/`
- `Docs/Plan/queue/`

## Blocked
Write Blocked in the handoff and write no queue file if:
- the exe or the PDB is missing, or
- the PDB GUID does not match the exe, or
- the server needs game DLLs that the toolchain cannot link.

## Done when
- The cards, the verify card, the next planner card and the queue file exist.
- `tools/gate.sh` prints `gate ok`.
