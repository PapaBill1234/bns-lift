# Toolchain: clang-cl + lld-link + Wine headers and Wine import libs.
# Use: cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/clangcl-wine.cmake
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR AMD64)

set(LIFT_LLVM_HINTS /usr/lib/llvm-21/bin /usr/lib/llvm-20/bin /usr/lib/llvm-19/bin /usr/bin)
find_program(LIFT_CLANG_CL NAMES clang-cl clang-cl-21 HINTS ${LIFT_LLVM_HINTS} REQUIRED)
find_program(LIFT_LLD_LINK NAMES lld-link lld-link-21 HINTS ${LIFT_LLVM_HINTS} REQUIRED)
find_program(LIFT_LLVM_LIB NAMES llvm-lib llvm-lib-21 HINTS ${LIFT_LLVM_HINTS} REQUIRED)
find_program(LIFT_LLVM_MT NAMES llvm-mt llvm-mt-21 HINTS ${LIFT_LLVM_HINTS})
find_program(LIFT_LLVM_RC NAMES llvm-rc llvm-rc-21 HINTS ${LIFT_LLVM_HINTS})

set(CMAKE_C_COMPILER   "${LIFT_CLANG_CL}")
set(CMAKE_CXX_COMPILER "${LIFT_CLANG_CL}")
set(CMAKE_LINKER       "${LIFT_LLD_LINK}")
set(CMAKE_AR           "${LIFT_LLVM_LIB}")
if(LIFT_LLVM_MT)
  set(CMAKE_MT "${LIFT_LLVM_MT}")
endif()
if(LIFT_LLVM_RC)
  set(CMAKE_RC_COMPILER "${LIFT_LLVM_RC}")
endif()

set(WINE_INCDIR "/usr/include/wine/wine" CACHE PATH "Wine header root")
set(WINE_LIBDIR "/usr/lib/x86_64-linux-gnu/wine/x86_64-windows" CACHE PATH "Wine import libs (lib<name>.a)")

# Compile flags (plan.md "Toolchain"). Do not add -fms-compatibility-version=16.
set(LIFT_COMMON_FLAGS "--target=x86_64-pc-windows-msvc /GS- /X -imsvc ${WINE_INCDIR}/msvcrt -imsvc ${WINE_INCDIR}/windows /D_WIN64 /D_MSVCR_VER=100")
set(CMAKE_C_FLAGS_INIT   "${LIFT_COMMON_FLAGS}")
# msvcr100 has no sized operator delete (??3@YAXPEAX_K@Z). Do not emit calls to it.
set(CMAKE_CXX_FLAGS_INIT "${LIFT_COMMON_FLAGS} /Zc:sizedDealloc-")
set(CMAKE_C_FLAGS_RELEASE_INIT   "/O2 /DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "/O2 /DNDEBUG")

# Link flags. Our own crt0 gives mainCRTStartup. No Microsoft libs.
set(CMAKE_EXE_LINKER_FLAGS_INIT "/subsystem:console /entry:mainCRTStartup /nodefaultlib /manifest:no")

# The try_compile checks cannot link an exe without crt0. Make a static lib instead.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
