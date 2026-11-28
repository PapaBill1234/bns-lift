# Handoff: lift-gamedaemon-gap-129-e129 (round 1)

Card: `lift-gamedaemon-e129`. GameDaemon forms of the 4 shared log functions.
All GameDaemon changes are inside `#if defined(LIFT_EXE_GD)` (or `LIFT_LOG_ADD_MEMBER`, which only
`Log.cpp` sets for GameDaemon). The other 5 exes keep their source form.

## Lifted

| Function | RVA (GD) | Change |
| --- | --- | --- |
| `Log::Write` (`?Write@Log@@SAXW4Type@1@PEB_WH1ZZ`) | 0x687a10 | GD `Log::Add` (0x687b70) is a private member, not static. `Log.h` declares the member form under `LIFT_LOG_ADD_MEMBER`. `Log::Write` and `Log::WriteV` call `instance->Add(logbuf)` for GD. Keep pragma added. |
| `LogBuffer::Acquire` | 0x69d2e0 | The body stays the same. The GD `RefCntObject::addReferenceCount` form (already in `RefCntObject.cpp`) gives the 4-argument call. Keep pragma added. |
| `LogMedia::Add` | 0x69ed80 | The body stays the same, as for `LogBuffer::Acquire`. Keep pragma added. |
| `AlertSender::writev2` | 0x686da0 | The GD form reads all members through `_alertSender` (LTCG removed `this`). The list test puts the "full" branch first. The tail test puts the empty-list branch first. The log copy size is the int product `2 * logCount`. Keep pragma added. |

## Notes for review

- `AlertSender::writev2`: formtest (VS2010, no /GL) gives the same `jg` branch order and the same block order as the original. The remaining difference is register allocation. The original keeps the constant 2 in r15. That adds one save slot, so the original frame is 0x16e0 and the formtest frame is 0x16d0. The real build uses LTCG and drops `this`, so its register pressure can differ. If review still rejects on P3 (frame size), put the GD form back to `LIFT_STUB(0x686da0);`.
- The formtest snippet does not stay in the repo.

## Not done

None.

## Changed files

- `src/Server/BloodLib/include/Log.h`
- `src/Server/BloodLib/source/Log.cpp`
- `src/Server/BloodLib/source/LogBuffer.cpp`
- `src/Server/BloodLib/source/LogMedia.cpp`
- `src/Server/BloodLib/source/AlertSender.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-129-e129.md`
