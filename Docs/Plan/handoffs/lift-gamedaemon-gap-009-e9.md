# lift-gamedaemon-gap-009-e9 handoff

## Lifted (36 functions)

- 33 `GetDefinition` getters in `guildtran_h` (17), `posttran_h` (3), `instantpaymenttran_h` (1) and `accountinventorytran_h` (13). Each returns `&_def`.
- `InstantPaymentJob::DataId` (0x1107d0): returns `DataId(0)`. The PDB calls virtual slot 14 (`DataId(short)`).
- `InstantPaymentDrawSlateNewStoneSubJob::DataId` (0x1ee480): returns `_cashId`.

## Notes

- Each class gets `static ::GameTranDef _def;`. The `.cpp` defines it with zero data.
  This is a stand-in. The real `_def` data (PDB data symbols, for example `TryRegisterGuildTran::_def`) is not lifted. The data owner must lift it later.
- `InstantPaymentJob` now declares `virtual int DataId(short) = 0;` (PDB slot 14).
- `InstantPaymentDrawSlateNewStoneSubJob` has `char _pad0[0x160]; int _cashId;` so that `_cashId` is at offset 0x168 as in the PDB. The base layout is not lifted yet.
- No dead-strip pragma was added. The driver must check whether `/OPT:REF` pairs the getters. The getters are virtual, so the class vtables may keep them.
- The gate, the build and the MATCH comparison were not run in this session. The driver does them.

## Not done

None.

## Files changed

- `src/Server/GameDaemon/guildtran.h`, `guildtran_h.cpp`
- `src/Server/GameDaemon/posttran.h`, `posttran_h.cpp`
- `src/Server/GameDaemon/instantpaymenttran.h`, `instantpaymenttran_h.cpp`
- `src/Server/GameDaemon/accountinventorytran.h`, `accountinventorytran_h.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-009-e9.md`
