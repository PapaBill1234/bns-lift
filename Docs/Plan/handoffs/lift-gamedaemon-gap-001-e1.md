# lift-gamedaemon-gap-001-e1 handoff

## Lifted (3)
- `LogArchive::Name` (0x694060): returns `L"LogArchive"`.
- `LogServerSessionHandler::~LogServerSessionHandler` (0x6ba560): empty body. The compiler sets the vftable.
- `DrTable::CanBeLoadedPieceByPiece` (0x455420, folded with `ActSequenceLoader::ReadFromBuffer`): returns `false`.

## Not done
- `DrElIter::~DrElIter` (0x1d050): `table.h` has no members of `DrElIter`. It also has no `DrDataTable` with the PDB vtable (`removeInnerIter` is slot 25). The skeleton header cannot make the call with the right slot. A later card must add the layouts first.

## Files changed
- `src/Server/GameDaemon/include_logarchive.cpp`
- `src/Server/GameDaemon/logserversessionhandler_h.cpp`
- `src/Server/GameDaemon/winserviceconsole_h.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-001-e1.md`

No `/INCLUDE` pragma added. Gate and MATCH counts: the driver records them.
