# Handoff lift-0: toolchain, CMake skeleton, crt0

## Done
- `cmake/clangcl-wine.cmake`: clang-cl, lld-link, llvm-lib, llvm-mt, llvm-rc (searched in /usr/lib/llvm-21/bin and /usr/bin). Flags from plan.md. Adds `/Zc:sizedDealloc-` for C++. Sets `WINE_LIBDIR`. try_compile makes a static lib (no crt0 there).
- `cmake/lift.cmake`: `lift_exe(name SOURCES ... IMPORTS ...)`. Adds the crt0 object lib and `${WINE_LIBDIR}/lib<name>.a`. msvcr100 and kernel32 are always added. Clears CMake default `kernel32.lib ...`.
- `src/crt/crt0.c`: `mainCRTStartup` → `_set_app_type`, `__getmainargs`, `_initterm_e` (.CRT$XIA..XIZ), `_initterm` (.CRT$XCA..XCZ), `exit(main(...))`. Defines `_fltused`.
- `CMakeLists.txt`, `src/selftest/main.cpp`: virtual class, static object, new/delete, printf, static destructor through atexit.
- `tools/run_selftest.sh`, `tools/gate_extra.sh`.
- Expected selftest output: `lift ok 2 32`, then `lift exit`, then `selftest ok`.

## Not done
- No build and no run. Bash was denied in this session ("don't ask" mode). The selftest output is NOT verified.
- `chmod +x tools/gate_extra.sh tools/run_selftest.sh` is not done (needs Bash). If gate_extra.sh is not executable, gate.sh skips the selftest.

## Facts found
- Wine libmsvcr100.a has no `??3@YAXPEAX_K@Z` (sized delete) and no `??_7type_info@@6B@`. Thus `/Zc:sizedDealloc-` (global) and `/GR-` (selftest only). Later cards that need RTTI must solve `type_info` (for example a local `type_info` vftable in crt).
- Glob does not show clang-cl / lld-link / llvm-lib (symlinks?). Check that they exist.
- No `__chkstk` yet. Functions with more than 4 KB stack will not link.

## ❓
- None.

## Blocked
- Gate not run: no Bash permission.

## Gate result
- Fix: link failed (`atexit` undefined; msvcr100.dll does not export it). crt0.c now defines `atexit` over `_onexit`. `tools/gate.sh` prints `gate ok`.
- The selftest did not run: `tools/gate_extra.sh` and `tools/run_selftest.sh` are not executable (mode 664), and chmod was denied. Next step: `chmod +x tools/gate_extra.sh tools/run_selftest.sh && tools/gate.sh`.
