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
  src/common/Thread.cpp
  src/common/Console.cpp
  src/common/TextConsole.cpp
  src/common/PipeConsole.cpp
  src/common/WindowConsole.cpp
  src/common/WinServiceConsole.cpp
  src/common/Daemon.cpp
  src/common/DaemonConfig.cpp
  src/common/BnsCommonConfig.cpp)
target_compile_options(lift_common PRIVATE /GR-)
# AlertSender.h includes winsock2.h after windows.h.
target_compile_definitions(lift_common PUBLIC WIN32_LEAN_AND_MEAN)
target_include_directories(lift_common BEFORE PRIVATE ${LIFT_STL_INCLUDE})
target_include_directories(lift_common PUBLIC ${CMAKE_SOURCE_DIR}/src/common)
add_dependencies(lift_common lift_msvcp100_implib)
