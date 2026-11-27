# Handoff: lift-gamedaemon-gap-126-s2 (GameDaemon forms of the shared log functions)

Card: `lift-gamedaemon-s2`, round 1. Source: GameDaemon 2019 + PDB pseudocode.

## Lifted

### Live callers (task 4)

- `src/Server/GameDaemon/item_h_1.cpp`: the 4 `SetCount` bodies are back
  (`WeaponItem` 0x4542d0, `CostumeItem` 0x454630, `GemItem` 0x4548f0, `AccessoryItem` 0x454ad0).
  The file includes `AlertSender.h` and `Log.h` last.
- The `/INCLUDE` pragmas of E16 round 1 are NOT back. The hard rules of the author run forbid `/INCLUDE` pragmas.
  If the linker removes the 4 virtual functions, the 5 shared functions have no live GD caller. Then funcdiff cannot pair them.
  The lead must decide how to keep them.

### GD forms (all under `#if defined(LIFT_EXE_GD)`; the other 5 exes keep their form)

| Function | GD RVA | GD form | Evidence |
| --- | --- | --- | --- |
| `RefCntObject::addReferenceCount` | 0xa870 | Reads `ignoreHistory` (`if (!ignoreHistory && _history != nullptr)`). Reads `_ref` one time. | GD pseudocode. The shared form does not read the bool, so LTCG removes it. This is the cause of the `LogBuffer::Acquire` DIFF (no `xor edx,edx`). |
| `LogBuffer::Acquire` | 0x69d2e0 | No source change. The source passes `false, file, 100`. The fix is in `addReferenceCount`. | GD pseudocode is the same as the source. |
| `RefCntHistory::add` | 0x693d00 | Store order `_file`, `_threadId`, `_line`, `_op`, `_ref` (lesson A19). | GD pseudocode. |
| `LogMedia::Add` | 0x69ed80 | No source change. The GD body calls `addReferenceCount` out of line. ❓ The review row shows the `_file` store order of `RefCntHistory::add`. The fix is in `RefCntHistory::add`. | GD pseudocode is the same as the source. |
| `AlertSender::writev2` | 0x686da0 | All buffers in the function scope, in the GD stack order (`lstr`, `fstr`, `ext`, `name`, `log`). Nested blocks in place of early returns. | GD pseudocode stack offsets. ❓ Not checked with an object dump. |

## Not done

- `Log::Write` (0x687a10 GD): TLS offset of `LogBufferAllocator::_Local`. The original is `0x30`. The build is `0xfa88`.
  Cause: the `.tls` layout of the link. In the build, about 0xfa80 bytes of other thread variables come before `_Local`.
  The fix needs a change of the TLS variables of other files or of the link order (lessons C2). That is outside the files of this card.
  The GD `Log::Add` (0x687b70) is `Log::Add(LogBuffer*)`, the same as the source. ❓ The reported `Log::Add` signature DIFF can come from LTCG in the build. Check it with an object dump.
- `LogBuffer::deallocate_me` (0x69d2c0 GD): the same TLS cause as `Log::Write`. The body is the same as the source.
- `AlertSender::writev2`: the frame size and the `jg` branch are not proven. The next round must check them with `llvm-objdump` on the GD object.

## Round 2: cause of the +0 result

Round 1 gained 0 MATCH. Round 2 found the cause. The cause is not in the GD forms.

- The round 1 GD link map (`build-vs2010/GameDaemon.map`) has no `SetCount`, no `AlertSender::writev2`,
  no `Log::Write` and no `RefCntObject::addReferenceCount`.
- `build-vs2010/GameDaemon.funcdiff.json` has no `*Item::*` function, no `Log::*`, no `LogBuffer::*` and no `LogMedia::*` function.
  From AlertSender it pairs only `AlertSender`, `Name`, `createSocket`, `fini`, `run` and `sendRemain`.
- Cause: the 4 `SetCount` bodies are virtual. No live GD code refers to the vtables of `WeaponItem`, `CostumeItem`, `GemItem` or `AccessoryItem`.
  `/OPT:REF` removes the 4 bodies. Then the 5 shared log functions have no live GD caller. The linker removes them too. funcdiff cannot pair them.
- In E16 round 1, the `/INCLUDE` pragmas kept the 4 bodies. The hard rules of the author run forbid new `/INCLUDE` pragmas.
  The other GD files use `/INCLUDE` pragmas as dead-strip keeps (for example `accessoryproperty.cpp`), but an author cannot add one.
- A different live caller needs a change of other GameDaemon files. The card forbids that.
- Thus no source change in the files of this card can give a MATCH gain. Round 2 makes no code change.
  An object dump cannot prove the GD forms of round 1, because the functions are not in the GD image.

### Decision for the lead

Do one of these:

1. Let the lead (not the author) add the 4 `/INCLUDE` pragmas of E16 round 1 to `src/Server/GameDaemon/item_h_1.cpp`
   (`?SetCount@WeaponItem@@UEAAXF@Z` and the 3 other forms). Then run the gate and read the funcdiff rows of the 5 functions,
   `RefCntObject::addReferenceCount` and `RefCntHistory::add`.
2. Or land this card after a card that lifts a live GD caller of `Log::Write` (for example the constructor of an item class).

### Open item in the GD forms (not checked)

- ❓ `REFCNT_HEADER` has no GD value. The GD build uses the CacheGate path in `RefCntObject::addReferenceCount`.
  The GD literal (in the pseudocode a reference into `zone._extraPublicProp`) is not known. Check the string when the function is live (lessons A6).

## Changed files

- `src/Server/GameDaemon/item_h_1.cpp`
- `src/Server/BloodLib/source/RefCntObject.cpp`
- `src/Server/BloodLib/source/AlertSender.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-126-s2.md`
