# lift-gamedaemon-gap-001-e1 handoff (round 2)

## Lifted (3)
- `LogArchive::Name` (0x694060): returns `L"LogArchive"`. A dead-strip `/INCLUDE` pragma keeps it.
- `LogServerSessionHandler::~LogServerSessionHandler` (0x6ba560): empty body. The compiler sets the vftable. A dead-strip pragma keeps it.
- `ActSequenceLoader::ReadFromBuffer` (0x455420): returns `false`. Round 1 used the wrong name (`DrTable::CanBeLoadedPieceByPiece`). Round 2 uses the PDB name and the PDB signature. The declaration is now in `actsequenceloader.h`. A dead-strip pragma keeps it.

Round 1 gave no MATCH because the linker removed the three functions (no live caller). Round 2 adds the `/INCLUDE` pragmas with a `// LIFT:` note.

## Not done
- `DrElIter::~DrElIter` (0x1d050): `table.h` has no members of `DrElIter`. It has no `DrDataTable` with the PDB vtable (`removeInnerIter` is slot 25). The skeleton header cannot make the call with the right slot. A later card must add the layouts first.

## Open points
- The mangled names in the pragmas come from the declarations (public names are not in the local cache). If the driver sees an unresolved symbol, check the calling convention and the const flags first.

## Files changed
- `src/Server/GameDaemon/include_logarchive.cpp`
- `src/Server/GameDaemon/logserversessionhandler_h.cpp`
- `src/Server/GameDaemon/winserviceconsole_h.cpp`
- `src/Server/GameDaemon/winserviceconsole_gd.h`
- `src/Server/GameDaemon/actsequenceloader.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-001-e1.md`

Gate and MATCH counts: the driver records them.
