# Handoff: lift-gamedaemon-gap-011-e11

## Lifted

All 30 `Summoned::Get...Modify` getters (RVA 0x455210 to 0x4553e0). Each reads one short from the level record at `_levelData` (+0x19F0).

## Round 6 change

No live caller keeps these virtual getters, so `/OPT:REF` removed them. Each getter now has a `/INCLUDE` pragma. The pragma uses the decorated name `?<Name>@Summoned@@UEAAFXZ`. Each pragma line has the `// LIFT: dead-strip keep (no live caller yet)` note. The bodies did not change.

The decorated names follow the form of the landed cards (`UEAA`). The driver build must confirm them. A wrong name makes the linker fail with an unresolved symbol.

## Not done

None.

## Files changed

- `src/Server/GameDaemon/summoned_h.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-011-e11.md`
