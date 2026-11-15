# lift_exe(<name> SOURCES <src>... IMPORTS <dll short name>...)
# Adds crt0 and the Wine import libs (kernel32 -> ${WINE_LIBDIR}/libkernel32.a).
# Include this file after project().

# CMake adds kernel32.lib user32.lib ... by default. These files do not exist here.
set(CMAKE_C_STANDARD_LIBRARIES   "" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD_LIBRARIES "" CACHE STRING "" FORCE)

set(LIFT_CRT0_SOURCE "${CMAKE_CURRENT_LIST_DIR}/../src/crt/crt0.c")
# crt0 always needs these two.
set(LIFT_CRT0_IMPORTS msvcr100 kernel32)

if(NOT TARGET lift_crt0)
  add_library(lift_crt0 OBJECT "${LIFT_CRT0_SOURCE}")
endif()

function(lift_exe name)
  cmake_parse_arguments(L "" "" "SOURCES;IMPORTS" ${ARGN})
  if(NOT L_SOURCES)
    message(FATAL_ERROR "lift_exe(${name}): no SOURCES")
  endif()
  add_executable(${name} ${L_SOURCES} $<TARGET_OBJECTS:lift_crt0>)

  set(imports ${L_IMPORTS} ${LIFT_CRT0_IMPORTS})
  list(TRANSFORM imports TOLOWER)
  list(REMOVE_DUPLICATES imports)
  foreach(imp IN LISTS imports)
    set(lib "${WINE_LIBDIR}/lib${imp}.a")
    if(NOT EXISTS "${lib}")
      message(FATAL_ERROR "lift_exe(${name}): no Wine import lib ${lib}")
    endif()
    target_link_libraries(${name} PRIVATE "${lib}")
  endforeach()
endfunction()
