# lift-0: toolchain, CMake skeleton, crt0

Repo: bns-lift (PRIVATE). No IDA in this card.

## Goal
A CMake project that builds a small test exe with clang-cl + lld-link + Wine headers. The exe runs under wine64.

## Facts (verified 2026-11-15, see Docs/Plan/plan.md "Toolchain")
- Compile: `clang-cl /nologo /c /O2 /GS- /X -imsvc /usr/include/wine/wine/msvcrt -imsvc /usr/include/wine/wine/windows /D_WIN64 /D_MSVCR_VER=100`
- Link: `lld-link /nologo /subsystem:console /entry:mainCRTStartup /nodefaultlib <objs> /usr/lib/x86_64-linux-gnu/wine/x86_64-windows/libmsvcr100.a .../libkernel32.a`
- crt0: `mainCRTStartup` calls `__getmainargs`, then `exit(main(argc, argv))`.
- Do not use `-fms-compatibility-version=16`.
- CacheGate imports: KERNEL32, USER32, ADVAPI32, SHELL32, ole32, MSVCP100, MSVCR100, SHLWAPI, VERSION, WS2_32, IPHLPAPI. Wine has an import lib `lib<name>.a` for each.

## Tasks
1. `cmake/clangcl-wine.cmake`: toolchain file. Set the compiler (clang-cl), the linker (lld-link), the flags above, and a variable `WINE_LIBDIR`.
2. `cmake/lift.cmake`: function `lift_exe(name SOURCES ... IMPORTS ...)`. It adds crt0 and the Wine import libs by short name (kernel32 → `${WINE_LIBDIR}/libkernel32.a`).
3. `src/crt/crt0.c`: the entry point. Add the C++ static init: call `_initterm` on the `.CRT$XCA`..`.CRT$XCZ` section ranges before `main`. Run `atexit` handlers through `exit`.
4. `CMakeLists.txt`: project `bns-lift`, languages C CXX, C++17. Target `lift_selftest` from `src/selftest/main.cpp`. Test a virtual class, a static object with a constructor, `new`/`delete` and `printf`.
5. `tools/run_selftest.sh`: build, then run `wine64 build/lift_selftest.exe` with `WINEDEBUG=-all`. Check the output line.
6. `tools/gate_extra.sh`: call `tools/run_selftest.sh`. Make it executable.

## Files
- `CMakeLists.txt`
- `cmake/`
- `src/crt/`
- `src/selftest/`
- `tools/run_selftest.sh`
- `tools/gate_extra.sh`

## Done when
- `tools/gate.sh` prints `gate ok`.
- The handoff gives the selftest output.
