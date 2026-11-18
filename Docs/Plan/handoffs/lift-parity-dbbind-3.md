# lift-parity-dbbind-3 handoff

## Done
- `DB_BIND_COL` and `DB_BIND_COL_NI` macros in `Db.h`: direct `SQLBindCol` with the orig error log (bind macro form).
- SCD `DbTransaction::BindCol` 0x20e40: MATCH (+1 SCD).
- SCD: 6 loaders use the macro for column 1 (95-97.8 %).
- POD `PostOfficeDB.cpp`: 4 loaders in orig form (forceinline helpers, bind macros). 0x14e50 98.3, 0x190f0 98.6, 0x15fa0 88.4, 0x18010 88.8. No new MATCH, no MATCH lost.
- `Docs/Parity/lessons.md` section "dbbind-3": patterns that worked and did not work.

## Not done (DIFF)
- SCD loaders 0x117c0, 0x12170, 0x13620, 0x13a30, 0x13dd0, 0x145f0 (`SmartCouponDB::Load*`, `Process*GameEventLog`): signal extra `Fetch` call, consts 0x2/0x3, extra `L"db"`/`L""` ref. Cause: VS2010 /LTCG inlines the bind only for column 1; other columns stay calls. Stopped: cause of the inline choice not found.
- POD 0x14e50, 0x190f0 `PostOfficeDB::Load*`: signal extra `memset, memset, Fetch` and an extra `Log::Write` before `SQLSetStmtAttrW`; const 0x23 missing. Cause: our fetch loop is rotated (duplicated first Fetch). Stopped: turn budget. Next: `while (true)` with the Fetch check at the top.
- POD 0x15fa0 LoadSinglePost, 0x18010 LoadRetryReadySinglePost: signal orig has one shared `statmentErrorLog` site for 17 columns and logs "Not initialized" before the binds. Cause: orig binds jump to one shared error label. Stopped: turn budget. Next: macro that sets index/type/buffer/size/result in variables and jumps to one label.
- POD `PostOfficeDB::RegisterPost` 0x16f20 (84.0): not looked at (turn budget).

## ❓
- Why VS2010 /LTCG inlines only column 1 in the SCD loaders.

## Blocked
- None.

## Gate result
- Stage 2 start: gate ok, parity ok (CG 436, LG 601, SCD 558, POD 645).
- Final: `tools/gate.sh` ok. `tools/parity.sh` ok: CG 436 (+0), LG 601 (+0), SCD 558 (+1), POD 645 (+0). MATCH -> DIFF 0 for all exes.

Turns: 42
