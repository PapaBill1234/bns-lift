# Handoff: lift-gamedaemon-gap-129-e129 (round 3)

Card: `lift-gamedaemon-e129`. GameDaemon forms of the 4 shared log functions.
All GameDaemon changes are inside `#if defined(LIFT_EXE_GD)` (or `LIFT_LOG_ADD_MEMBER`, which only
`Log.cpp` sets for GameDaemon). The other 5 exes keep their source form and object code.

## Lifted

| Function | RVA (GD) | Change |
| --- | --- | --- |
| `Log::Write` (`?Write@Log@@SAXW4Type@1@PEB_WH1ZZ`) | 0x687a10 | Accepted in round 2. No change. GD `Log::Add` (0x687b70) is a private member. `Log::Write` and `Log::WriteV` call `instance->Add(logbuf)` for GD. |
| `LogBuffer::Acquire` | 0x69d2e0 | The body stays the same. Round 3: the GD `RefCntObject::addReferenceCount` (0xa870) gets a GD-only keep line. Each lifted GD caller passes `false`, so LTCG dropped the bool and the call had no `edx`. The keep line makes the symbol external, so LTCG keeps the 4-argument PDB signature (`xor edx, edx`). |
| `LogMedia::Add` | 0x69ed80 | Same fix as `LogBuffer::Acquire`. |
| `RefCntHistory::dump` | 0x693db0 | This body is live in GD only since this card (Log::Write keeps the LogBuffer vtable). Round 3: GD form reads `_history[i]` again after `swprintf` (as the GD original). Formtest: the constant 1 stays in r15 and the last `Log::Write` uses `mov ecx, r15d`. The extra `mov ecx, 0x1` is gone. The other exes alias the same item (no code change). |

## Not done

| Function | RVA (GD) | Reason |
| --- | --- | --- |
| `AlertSender::writev2` | 0x686da0 | P3_imm frame size. The original keeps the constant 2 in r15 (one more save slot, `__chkstk` 0x16e0). Formtest of 3 source forms (plain stores, `int` stores, `size_t` helper functions) gives 0x16d0 each time. The GD form is now `LIFT_STUB(0x686da0);` with `__declspec(noinline)` (so LTCG does not put the stub into `AlertSender::Write`). The keep line is removed. The lifted GD form is in the git history of this card (round 2). |

## Notes for review

- The `addReferenceCount` keep line can change other GD callers of `addReferenceCount`. The GD original passes `edx` at its call sites, so the change moves them toward the original.
- `RefCntHistory::dump`: formtest has only register name differences left (no `/GL` in formtest).

## Changed files

- `src/Server/BloodLib/include/Log.h`
- `src/Server/BloodLib/source/Log.cpp`
- `src/Server/BloodLib/source/LogBuffer.cpp`
- `src/Server/BloodLib/source/LogMedia.cpp`
- `src/Server/BloodLib/source/AlertSender.cpp`
- `src/Server/BloodLib/source/RefCntObject.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-129-e129.md`
