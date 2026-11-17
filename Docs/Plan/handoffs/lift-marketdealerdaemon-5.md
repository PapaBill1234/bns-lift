# lift-marketdealerdaemon-5: handoff

## Done
- MarketDB.cpp: 16 functions added (pseudocode lines 2,429..4,684 have 16, not 17).
  RetrieveSaleList 0x1f840, RetrieveBidList 0x20000, RetrieveReservationList 0x20760, ReserveSale 0x20b90,
  CancelSaleReservation 0x21150, RegisterSale 0x213c0, UpdateSalePrice 0x21b00, AbandonSale 0x21ec0,
  ReserveBid 0x222a0, CancelBidReservation 0x22710, RegisterBid 0x22980, UpdateBidPrice 0x22d20,
  AbandonBid 0x23070, ReservePurchase 0x23450, CancelPurchaseReservation 0x238d0, RegisterPurchase 0x23b40.
- New JobContext.h: JobContext, MySaleInfo, MyBidInfo, MyReservationInfo and the 16 job classes that
  MarketDB uses. Members, order and Param/Column enums come from the PDB types (types.h).
  Only the virtuals and addMySaleInfo 0x93c0, addMyBidInfo 0xa5a0, addMyReservationInfo 0x17b00 are
  declared. The JobContext module (135 functions) stays for a later card.
- Inlined DbTransaction::BindCol calls (SQLBindCol + SQL_NTS pre-set) are BindCol calls again.
- Length slot arrays use the Param/Column enums for size and index, as in the binary.
- CMake: no change (no new .cpp).

## Not done
- MarketDB card 6 and 7 functions (0x24100..0x28f50). Declarations only.

## BUG marks
- None new.

## ❓
- addMySaleInfo, addMyBidInfo, addMyReservationInfo: parameter is `const&` or `const*` (pseudocode shows a pointer).
- Parameter name of verifyParameter/handleJob (`short& result`) is a guess.
- Return type of the MarketDB members stays `bool const` (card 4).

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: no build errors, `gate ok`. CacheGate, SCD, LobbyGate, POD still link.
