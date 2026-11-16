cmake_minimum_required(VERSION 3.20)
project(bns-lift LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/lift.cmake)

# msvcp100.dll import lib. Wine has no libmsvcp100.a, so make one from a .def file.
# include/vs2010 calls only these msvcp100 exports.
set(LIFT_MSVCP100_DEF ${CMAKE_BINARY_DIR}/msvcp100.def)
set(LIFT_MSVCP100_IMPLIB ${CMAKE_BINARY_DIR}/msvcp100.lib)
file(WRITE ${LIFT_MSVCP100_DEF}
"LIBRARY msvcp100.dll
EXPORTS
    ?_Xinvalid_argument@std@@YAXPEBD@Z
    ?_Xlength_error@std@@YAXPEBD@Z
    ?_Xout_of_range@std@@YAXPEBD@Z
    ?_Xoverflow_error@std@@YAXPEBD@Z
    ?_Xruntime_error@std@@YAXPEBD@Z
")
find_program(LIFT_LLVM_LIB NAMES llvm-lib llvm-lib-21 REQUIRED)
add_custom_command(OUTPUT ${LIFT_MSVCP100_IMPLIB}
  COMMAND ${LIFT_LLVM_LIB} /def:${LIFT_MSVCP100_DEF} /machine:x64 /out:${LIFT_MSVCP100_IMPLIB}
  DEPENDS ${LIFT_MSVCP100_DEF}
  COMMENT "msvcp100.lib from .def")
add_custom_target(lift_msvcp100_implib DEPENDS ${LIFT_MSVCP100_IMPLIB})

# Header-only VS2010 STL subset and the PDB type headers.
set(LIFT_STL_INCLUDE ${CMAKE_SOURCE_DIR}/include/vs2010)
set(LIFT_PDB_INCLUDE ${CMAKE_SOURCE_DIR}/include)

lift_exe(lift_selftest
  SOURCES src/selftest/main.cpp src/selftest/stl_layout.cpp src/selftest/pdb_types.cpp
  IMPORTS msvcr100 kernel32)
# msvcr100 from Wine has no type_info vftable in the import lib. No RTTI for the selftest.
target_compile_options(lift_selftest PRIVATE /GR-)
target_include_directories(lift_selftest BEFORE PRIVATE ${LIFT_STL_INCLUDE} ${LIFT_PDB_INCLUDE})
add_dependencies(lift_selftest lift_msvcp100_implib)
target_link_libraries(lift_selftest PRIVATE ${LIFT_MSVCP100_IMPLIB})

# Common server code (BloodLib). Static lib, shared by the server exes.
add_library(lift_common STATIC
  src/common/BaseMemory.cpp
  src/common/Memory.cpp
  src/common/MemoryManager.cpp
  src/common/RefCntObject.cpp
  src/common/Log.cpp
  src/common/LogBuffer.cpp
  src/common/LogMedia.cpp
  src/common/StringUtil.cpp
  src/common/SystemInformation.cpp
  src/common/DelayedRelease.cpp
  src/common/Timer.cpp
  src/common/AlertSender.cpp
  src/common/Thread.cpp
  src/common/Console.cpp
  src/common/TextConsole.cpp
  src/common/PipeConsole.cpp
  src/common/WindowConsole.cpp
  src/common/WinServiceConsole.cpp
  src/common/Daemon.cpp
  src/common/DaemonConfig.cpp
  src/common/BnsCommonConfig.cpp
  src/common/Crypto.cpp
  src/common/aes128.cpp
  src/common/aes128Table.cpp
  src/common/aes128NI.cpp
  src/common/blowfish.cpp
  src/common/ctr.cpp
  src/common/prng.cpp
  src/common/ripemd160.cpp
  src/common/ripemd128.cpp
  src/common/mgf.cpp
  src/common/oaep_encoder.cpp
  src/common/rsa.cpp
  src/common/CryptoKey.cpp
  src/common/BigInteger.cpp
  src/common/biArithmetic.cpp
  src/common/biMultiplication.cpp
  src/common/biSqr.cpp
  src/common/biMontgomery.cpp
  src/common/NumberTheory.cpp
  src/common/LogFile.cpp
  src/common/PacketBuffer.cpp
  src/common/Packet.cpp
  src/common/Connection.cpp
  src/common/SessionBuffer.cpp
  src/common/Listener.cpp
  src/common/IoWorkerThread.cpp
  src/common/Channel.cpp
  src/common/Network.cpp
  src/common/Port.cpp
  src/common/PacketBufferHandler.cpp
  src/common/IdleWatcher.cpp
  src/common/PacketUtil.cpp
  src/common/Security.cpp
  src/common/CrashHandler.cpp)
# clang-cl needs the AES target feature for the <wmmintrin.h> intrinsics.
set_source_files_properties(src/common/aes128NI.cpp PROPERTIES COMPILE_OPTIONS "-maes")
target_compile_options(lift_common PRIVATE /GR-)
# AlertSender.h includes winsock2.h after windows.h.
target_compile_definitions(lift_common PUBLIC WIN32_LEAN_AND_MEAN)
target_include_directories(lift_common BEFORE PRIVATE ${LIFT_STL_INCLUDE})
target_include_directories(lift_common PUBLIC ${CMAKE_SOURCE_DIR}/src/common)
add_dependencies(lift_common lift_msvcp100_implib)
# Wine import libs for the BloodLib modules (Db: odbc32, SystemInformation: ws2_32 iphlpapi, String: ole32).
foreach(imp odbc32 ws2_32 iphlpapi ole32)
  target_link_libraries(lift_common INTERFACE "${WINE_LIBDIR}/lib${imp}.a")
endforeach()

# Upstream zstd (see vendor/zstd/README.md). Build it only if the source is present.
set(LIFT_ZSTD_DIR ${CMAKE_SOURCE_DIR}/vendor/zstd/src)
if(EXISTS ${LIFT_ZSTD_DIR}/lib/zstd.h)
  file(GLOB LIFT_ZSTD_SOURCES
    ${LIFT_ZSTD_DIR}/lib/common/*.c
    ${LIFT_ZSTD_DIR}/lib/compress/*.c
    ${LIFT_ZSTD_DIR}/lib/decompress/*.c)
  add_library(lift_zstd STATIC ${LIFT_ZSTD_SOURCES})
  target_include_directories(lift_zstd PUBLIC ${LIFT_ZSTD_DIR}/lib ${LIFT_ZSTD_DIR}/lib/common)
  target_compile_definitions(lift_zstd PRIVATE ZSTD_MULTITHREAD=0)
  target_link_libraries(lift_common PUBLIC lift_zstd)
endif()
