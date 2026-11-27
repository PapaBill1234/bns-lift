cmake_minimum_required(VERSION 3.20)
project(bns-lift LANGUAGES C CXX RC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/lift.cmake)

# No _Init_thread_header/_footer/_epoch in the /nodefaultlib link. VS2010 has no thread-safe statics either.
# Here (not in the toolchain file) so that an old CMakeCache keeps working.
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/Zc:threadSafeInit->)

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

# Source tree as in the original depot (Program\\...). See Docs/layout.md.
set(LIFT_SRC_INCLUDE
  ${CMAKE_SOURCE_DIR}/src/Security/source/BloodCrypto/crypto
  ${CMAKE_SOURCE_DIR}/src/Security/source/BloodCrypto/crypto/encoder
  ${CMAKE_SOURCE_DIR}/src/Security/source/BloodCrypto/crypto/mode
  ${CMAKE_SOURCE_DIR}/src/Security/source/BloodCrypto/hash
  ${CMAKE_SOURCE_DIR}/src/Security/source/BloodCrypto/key
  ${CMAKE_SOURCE_DIR}/src/Security/source/BloodCrypto/math/bignumber
  ${CMAKE_SOURCE_DIR}/src/Security/source/BloodCrypto/math/prng
  ${CMAKE_SOURCE_DIR}/src/Security/source/BloodPacketCrypt
  ${CMAKE_SOURCE_DIR}/src/Security/source/BloodCert
  ${CMAKE_SOURCE_DIR}/src/Server/BloodLib/include
  ${CMAKE_SOURCE_DIR}/src/Server/BloodLib/source
  ${CMAKE_SOURCE_DIR}/src/Server/Economy/CacheGate
  ${CMAKE_SOURCE_DIR}/src/Server/Economy/PostOfficeDaemon
  ${CMAKE_SOURCE_DIR}/src/Server/Economy/MarketDealerDaemon
  ${CMAKE_SOURCE_DIR}/src/Server/Economy/Shared
  ${CMAKE_SOURCE_DIR}/src/Server/LobbyDaemon
  ${CMAKE_SOURCE_DIR}/src/Server/LobbyGate
  ${CMAKE_SOURCE_DIR}/src/Server/Packet
  ${CMAKE_SOURCE_DIR}/src/Server/Shared
  ${CMAKE_SOURCE_DIR}/src/Server/SmartCouponDaemon
)

lift_exe(lift_selftest
  SOURCES src/selftest/main.cpp src/selftest/stl_layout.cpp src/selftest/pdb_types.cpp
          src/selftest/pdb_types_LobbyGate.cpp src/selftest/pdb_types_PostOfficeDaemon.cpp
          src/selftest/pdb_types_MarketDealerDaemon.cpp
          src/selftest/pdb_types_SmartCouponDaemon.cpp
          src/selftest/pdb_types_LobbyDaemon.cpp
  IMPORTS msvcr100 kernel32)
# msvcr100 from Wine has no type_info vftable in the import lib. No RTTI for the selftest.
target_compile_options(lift_selftest PRIVATE /GR-)
target_include_directories(lift_selftest BEFORE PRIVATE ${LIFT_STL_INCLUDE} ${LIFT_PDB_INCLUDE})
add_dependencies(lift_selftest lift_msvcp100_implib)
target_link_libraries(lift_selftest PRIVATE ${LIFT_MSVCP100_IMPLIB})

# Load the BloodLib placement operators before the STL headers.
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/FIPlacementNew.h>)

# Common server code (BloodLib). Static lib, shared by the server exes.
# lift_common has no MemoryManager.cpp and RefCntObject.cpp: LG, SCD and POD link a per-exe copy (lessons.md
# pattern 35). lift_common_cg is the full list for CacheGate. tools/vs2010/build.sh sorts the objects of a lib by
# path, so the full list keeps the old CacheGate object order.
set(LIFT_COMMON_SOURCES
  src/Server/BloodLib/source/BaseMemory.cpp
  src/Server/BloodLib/source/Memory.cpp
  src/Server/BloodLib/source/Log.cpp
  src/Server/BloodLib/source/LogBuffer.cpp
  src/Server/BloodLib/source/LogMedia.cpp
  src/Server/BloodLib/source/StringUtil.cpp
  src/Server/BloodLib/source/SystemInformation.cpp
  src/Server/BloodLib/source/DelayedRelease.cpp
  src/Server/BloodLib/source/Timer.cpp
  src/Server/BloodLib/source/AlertSender.cpp
  src/Server/BloodLib/source/Thread.cpp
  src/Server/BloodLib/source/Console.cpp
  src/Server/BloodLib/source/TextConsole.cpp
  src/Server/BloodLib/source/PipeConsole.cpp
  src/Server/BloodLib/source/WindowConsole.cpp
  src/Server/BloodLib/source/WinServiceConsole.cpp
  src/Server/BloodLib/source/Daemon.cpp
  src/Server/BloodLib/source/DaemonConfig.cpp
  src/Security/source/BloodCrypto/crypto/Crypto.cpp
  src/Security/source/BloodCrypto/crypto/aes128.cpp
  src/Security/source/BloodCrypto/crypto/aes128Table.cpp
  src/Security/source/BloodCrypto/crypto/aes128NI.cpp
  src/Security/source/BloodCrypto/crypto/blowfish.cpp
  src/Security/source/BloodCrypto/crypto/mode/ctr.cpp
  src/Security/source/BloodCrypto/math/prng/prng.cpp
  src/Security/source/BloodCrypto/hash/ripemd160.cpp
  src/Security/source/BloodCrypto/hash/ripemd128.cpp
  src/Security/source/BloodCrypto/crypto/encoder/mgf.cpp
  src/Security/source/BloodCrypto/crypto/encoder/oaep_encoder.cpp
  src/Security/source/BloodCrypto/crypto/rsa.cpp
  src/Security/source/BloodCrypto/key/CryptoKey.cpp
  src/Security/source/BloodCrypto/math/bignumber/BigInteger.cpp
  src/Security/source/BloodCrypto/math/bignumber/biArithmetic.cpp
  src/Security/source/BloodCrypto/math/bignumber/biMultiplication.cpp
  src/Security/source/BloodCrypto/math/bignumber/biSqr.cpp
  src/Security/source/BloodCrypto/math/bignumber/biMontgomery.cpp
  src/Security/source/BloodCrypto/math/bignumber/NumberTheory.cpp
  src/Server/BloodLib/source/LogFile.cpp
  src/Server/BloodLib/source/PacketBuffer.cpp
  src/Server/BloodLib/source/Packet.cpp
  src/Server/BloodLib/source/Connection.cpp
  src/Server/BloodLib/source/SessionBuffer.cpp
  src/Server/BloodLib/source/Session.cpp
  src/Server/BloodLib/source/Listener.cpp
  src/Server/BloodLib/source/IoWorkerThread.cpp
  src/Server/BloodLib/source/Channel.cpp
  src/Server/BloodLib/source/Network.cpp
  src/Server/BloodLib/source/Port.cpp
  src/Server/BloodLib/source/PacketBufferHandler.cpp
  src/Server/BloodLib/source/IdleWatcher.cpp
  src/Server/BloodLib/source/PacketUtil.cpp
  src/Server/BloodLib/source/Security.cpp
  src/Security/source/BloodCert/BloodCert.cpp
  src/Security/source/BloodPacketCrypt/PacketCrypt.cpp
  src/Server/BloodLib/source/CrashHandler.cpp
  src/Server/Packet/FragmentPacket.cpp
  src/Server/BloodLib/source/Db.cpp)
# LIFT: these modules have a per-exe path literal (lessons.md pattern A5). LG, SCD and POD link a per-exe
# wrapper (or the plain file) in lift_common_{lg,scd,pod}. CacheGate keeps the plain file and its default macro.
set(LIFT_COMMON_PATH_SOURCES
  src/Server/BloodLib/source/Timer.cpp
  src/Server/BloodLib/source/Channel.cpp
  src/Server/BloodLib/source/Port.cpp
  src/Server/BloodLib/source/PacketUtil.cpp
  src/Server/Packet/FragmentPacket.cpp)
set(LIFT_COMMON_SHARED_SOURCES ${LIFT_COMMON_SOURCES})
list(REMOVE_ITEM LIFT_COMMON_SHARED_SOURCES ${LIFT_COMMON_PATH_SOURCES})
add_library(lift_common STATIC ${LIFT_COMMON_SHARED_SOURCES})
add_library(lift_common_cg STATIC ${LIFT_COMMON_SOURCES}
  src/Server/BloodLib/source/MemoryManager.cpp
  src/Server/BloodLib/source/RefCntObject.cpp)
# clang-cl needs the AES target feature for the <wmmintrin.h> intrinsics.
set_source_files_properties(src/Security/source/BloodCrypto/crypto/aes128NI.cpp PROPERTIES COMPILE_OPTIONS "-maes")
foreach(lift_l IN ITEMS lift_common lift_common_cg)
  target_compile_options(${lift_l} PRIVATE /GR-)
  # AlertSender.h includes winsock2.h after windows.h.
  target_compile_definitions(${lift_l} PUBLIC WIN32_LEAN_AND_MEAN)
  target_include_directories(${lift_l} BEFORE PRIVATE ${LIFT_STL_INCLUDE})
  target_include_directories(${lift_l} PUBLIC ${LIFT_SRC_INCLUDE})
  add_dependencies(${lift_l} lift_msvcp100_implib)
  # Wine import libs for the BloodLib modules (Db: odbc32, SystemInformation: ws2_32 iphlpapi, String: ole32).
  foreach(imp odbc32 ws2_32 iphlpapi ole32 advapi32 shell32 version user32 shlwapi)
    target_link_libraries(${lift_l} INTERFACE "${WINE_LIBDIR}/lib${imp}.a")
  endforeach()
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
  # Do not define ZSTD_MULTITHREAD. zstd tests it with #ifdef, so any value turns multithreading on.
  set(LIFT_ZSTD_LINK lift_zstd)
else()
  # Without vendor/zstd, the exes use src/crt/zstd_stub.c.
  set(LIFT_ZSTD_LINK lift_zstd_stub)
  add_library(lift_zstd_stub STATIC src/crt/zstd_stub.c)
endif()
target_link_libraries(lift_common PUBLIC ${LIFT_ZSTD_LINK})
target_link_libraries(lift_common_cg PUBLIC ${LIFT_ZSTD_LINK})

# CacheGate server exe. wmain_bridge.c gives the narrow main that crt0.c calls.
lift_exe(CacheGate
  SOURCES src/Server/Economy/CacheGate/CacheGate.cpp src/Server/Economy/CacheGate/CacheGate.rc src/Server/Economy/CacheGate/CacheD.cpp src/Server/Economy/CacheGate/CacheDChannel.cpp
          src/Server/Economy/CacheGate/ClientManager.cpp src/Server/Economy/CacheGate/CacheGateSessionHandler.cpp
          src/Server/Economy/CacheGate/CacheGateServerSideHandlerList.cpp src/crt/wmain_bridge.c
          src/crt/tlssup.c src/crt/new_delete.c src/Server/Shared/BnsCommonConfigDefinition.cpp
  IMPORTS msvcr100 kernel32)
target_compile_options(CacheGate PRIVATE /GR-)
target_include_directories(CacheGate BEFORE PRIVATE ${LIFT_STL_INCLUDE})
add_dependencies(CacheGate lift_msvcp100_implib)
# BloodLib sources with a per-exe __FILE__ path (lessons.md pattern 35).
foreach(lift_e IN ITEMS LobbyGate:lg SmartCouponDaemon:scd PostOfficeDaemon:pod)
  string(REPLACE ":" ";" lift_p "${lift_e}")
  list(GET lift_p 0 lift_x)
  list(GET lift_p 1 lift_s)
  set(lift_w
    src/Server/BloodLib/source/MemoryManager${lift_x}.cpp
    src/Server/BloodLib/source/RefCntObject${lift_x}.cpp)
  foreach(lift_f IN LISTS LIFT_COMMON_PATH_SOURCES)
    get_filename_component(lift_d ${lift_f} DIRECTORY)
    get_filename_component(lift_n ${lift_f} NAME_WE)
    if(EXISTS ${CMAKE_SOURCE_DIR}/${lift_d}/${lift_n}${lift_x}.cpp)
      list(APPEND lift_w ${lift_d}/${lift_n}${lift_x}.cpp)
    else()
      list(APPEND lift_w ${lift_f})
    endif()
  endforeach()
  add_library(lift_common_${lift_s} STATIC ${lift_w})
endforeach()
foreach(lift_s IN ITEMS lg scd pod)
  target_compile_options(lift_common_${lift_s} PRIVATE /GR-)
  target_include_directories(lift_common_${lift_s} BEFORE PRIVATE ${LIFT_STL_INCLUDE})
  add_dependencies(lift_common_${lift_s} lift_msvcp100_implib)
  target_link_libraries(lift_common_${lift_s} PUBLIC lift_common)
endforeach()
target_link_libraries(CacheGate PRIVATE lift_common_cg ${LIFT_MSVCP100_IMPLIB})

# SmartCouponDaemon app modules (static lib).
add_library(lift_smartcoupondaemon STATIC
  src/Server/Shared/BnsCommonConfigDefinitionShortPath.cpp
  src/Server/SmartCouponDaemon/CouponJob.cpp
  src/Server/SmartCouponDaemon/EventNotiJob.cpp
  src/Server/SmartCouponDaemon/GameEventWorker.cpp
  src/Server/LobbyDaemon/ObjectPool.cpp
  src/Server/Shared/SharedChannel.cpp
  src/Server/SmartCouponDaemon/ManagerChannel.cpp
  src/Server/SmartCouponDaemon/ManagerPacketHandler.cpp
  src/Server/SmartCouponDaemon/SmartCouponManagerPacketSmartCouponSideHandlerList.cpp
  src/Server/SmartCouponDaemon/SmartCouponDB.cpp
  src/Server/SmartCouponDaemon/DaemonChannel.cpp
  src/Server/SmartCouponDaemon/DaemonPacketHandler.cpp
  src/Server/SmartCouponDaemon/SmartCouponPacketSmartCouponSideHandlerList.cpp
  src/Server/Shared/CouponGameEventConfig.cpp
  src/Server/Shared/NPChannel2.cpp
  src/Server/SmartCouponDaemon/NPServiceChannel.cpp
  src/Server/SmartCouponDaemon/NPMessageHandler.cpp
  src/Server/SmartCouponDaemon/SmartCouponDaemon.cpp)
target_compile_options(lift_smartcoupondaemon PRIVATE /GR-)
target_include_directories(lift_smartcoupondaemon BEFORE PRIVATE ${LIFT_STL_INCLUDE})
target_include_directories(lift_smartcoupondaemon PUBLIC ${LIFT_SRC_INCLUDE})
target_link_libraries(lift_smartcoupondaemon PUBLIC lift_common)

# LobbyGate app modules (static lib).
add_library(lift_lobbygate STATIC
  src/Server/Economy/Shared/ThreadFreePacketPump.cpp
  src/Server/Shared/BnsCommonConfigDefinitionShortPath.cpp
  src/Server/LobbyGate/Client.cpp
  src/Server/LobbyGate/LobbyDChannel.cpp
  src/Server/LobbyGate/LobbyGatePredefine.cpp
  src/Server/LobbyGate/PcCafeMileageFeverTimeScheduleList.cpp
  src/Server/LobbyGate/WorldListManager.cpp
  src/Server/LobbyGate/LobbyGateConfig.cpp
  src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp
  src/Server/LobbyGate/LobbyGate.cpp
  src/Server/LobbyGate/LobbyGatePacketHandler.cpp
  src/Server/LobbyGate/LobbyDPacketHandler.cpp)
target_compile_options(lift_lobbygate PRIVATE /GR-)
target_include_directories(lift_lobbygate BEFORE PRIVATE ${LIFT_STL_INCLUDE})
target_include_directories(lift_lobbygate PUBLIC ${LIFT_SRC_INCLUDE})
target_link_libraries(lift_lobbygate PUBLIC lift_common)

# PostOfficeDaemon lifted modules (static library). Calls to code of later cards stay as declarations.
add_library(lift_postofficedaemon STATIC
  src/Server/Economy/Shared/ThreadFreePacketPumpShortPath.cpp
  src/Server/Shared/BnsCommonConfigDefinition.cpp
  src/Server/Economy/PostOfficeDaemon/RelayContext.cpp
  src/Server/Economy/PostOfficeDaemon/RelayTimeContext.cpp
  src/Server/Economy/PostOfficeDaemon/RelayTimeoutChecker.cpp
  src/Server/Economy/PostOfficeDaemon/RelayTimeoutEvent.cpp
  src/Server/Economy/PostOfficeDaemon/PingRelay.cpp
  src/Server/Economy/PostOfficeDaemon/PingGenerator.cpp
  src/Server/Economy/PostOfficeDaemon/CachedWatchdog.cpp
  src/Server/Economy/PostOfficeDaemon/CacheGateChannel.cpp
  src/Server/Economy/PostOfficeDaemon/CacheGatePacketHandler.cpp
  src/Server/Economy/PostOfficeDaemon/CacheGateClientSideHandlerList.cpp
  src/Server/Economy/PostOfficeDaemon/AgentChannel.cpp
  src/Server/Economy/PostOfficeDaemon/AgentPacketHandler.cpp
  src/Server/Economy/PostOfficeDaemon/PostOfficePacketServerSideHandlerList.cpp
  src/Server/Economy/PostOfficeDaemon/ManagementSessionHandler.cpp
  src/Server/Economy/PostOfficeDaemon/ManagementPacketHandler.cpp
  src/Server/Economy/PostOfficeDaemon/PostOfficeManagementPacketHandlerList.cpp
  src/Server/Economy/PostOfficeDaemon/WorldChannel.cpp
  src/Server/Economy/PostOfficeDaemon/WorldPacketHandler.cpp
  src/Server/Economy/PostOfficeDaemon/PostOfficeServicePacketServerSideHandlerList.cpp
  src/Server/Economy/PostOfficeDaemon/PostContext.cpp
  src/Server/Economy/PostOfficeDaemon/PostDeliveryEvent.cpp
  src/Server/Economy/PostOfficeDaemon/DeliverPostRelay.cpp
  src/Server/Economy/PostOfficeDaemon/CheckPostCapacityRelay.cpp
  src/Server/Economy/PostOfficeDaemon/RetrieveCharacterInfoRelay.cpp
  src/Server/Economy/PostOfficeDaemon/CacheEconomyPacketHandler.cpp
  src/Server/Economy/PostOfficeDaemon/CacheEconomyClientSideHandlerList.cpp
  src/Server/Economy/PostOfficeDaemon/WorldConfigManager.cpp
  src/Server/Economy/PostOfficeDaemon/UnsentPostContext.cpp
  src/Server/Economy/PostOfficeDaemon/UnsentPostChecker.cpp
  src/Server/Economy/PostOfficeDaemon/PostOfficeDB.cpp
  src/Server/Economy/PostOfficeDaemon/PostOfficeDaemon.cpp)
target_compile_options(lift_postofficedaemon PRIVATE /GR-)
target_include_directories(lift_postofficedaemon BEFORE PRIVATE ${LIFT_STL_INCLUDE})
target_include_directories(lift_postofficedaemon PUBLIC ${LIFT_SRC_INCLUDE})
target_link_libraries(lift_postofficedaemon PUBLIC lift_common)

# MarketDealerDaemon lifted modules (static library). Calls to code of later cards stay as declarations.
add_library(lift_marketdealerdaemon STATIC
  src/Server/BloodLib/source/MemoryManager.cpp
  src/Server/BloodLib/source/RefCntObject.cpp
  src/Server/Economy/Shared/ThreadFreePacketPumpShortPath.cpp
  src/Server/Shared/BnsCommonConfigDefinition.cpp
  src/Server/Economy/MarketDealerDaemon/SaleContext.cpp
  src/Server/Economy/MarketDealerDaemon/BidContext.cpp
  src/Server/Economy/MarketDealerDaemon/PurchaseContext.cpp
  src/Server/Economy/MarketDealerDaemon/Postman.cpp
  src/Server/Economy/MarketDealerDaemon/DeliveryContext.cpp
  src/Server/Economy/MarketDealerDaemon/TaxRateDataManager.cpp
  src/Server/Economy/MarketDealerDaemon/SaleTimeContext.cpp
  src/Server/Economy/MarketDealerDaemon/AgentChannel.cpp
  src/Server/Economy/MarketDealerDaemon/ManagerChannel.cpp
  src/Server/Economy/MarketDealerDaemon/MarketDB.cpp
  src/Server/Economy/MarketDealerDaemon/DeliveryTimer.cpp
  src/Server/Economy/MarketDealerDaemon/TimeoutTimer.cpp
  src/Server/Economy/MarketDealerDaemon/ManagementJobContext.cpp
  src/Server/Economy/MarketDealerDaemon/JobContext.cpp
  src/Server/Economy/MarketDealerDaemon/TimeoutEvent.cpp
  src/Server/Economy/MarketDealerDaemon/ManagerPacketHandler.cpp
  src/Server/Economy/MarketDealerDaemon/MarketManagerServerSideHandlerList.cpp)
target_compile_options(lift_marketdealerdaemon PRIVATE /GR-)
target_include_directories(lift_marketdealerdaemon BEFORE PRIVATE ${LIFT_STL_INCLUDE})
target_include_directories(lift_marketdealerdaemon PUBLIC ${LIFT_SRC_INCLUDE})
target_link_libraries(lift_marketdealerdaemon PUBLIC lift_common)

# SmartCouponDaemon server exe. LinkStubs.cpp has stub bodies for the modules in the handoff "Not done" list.
lift_exe(SmartCouponDaemon
  SOURCES src/Server/SmartCouponDaemon/LinkStubs.cpp src/Server/SmartCouponDaemon/SmartCouponDaemon.rc src/crt/wmain_bridge.c
          src/crt/tlssup.c src/crt/new_delete.c
  IMPORTS msvcr100 kernel32 odbc32 iphlpapi version shlwapi ws2_32)
target_compile_options(SmartCouponDaemon PRIVATE /GR-)
target_include_directories(SmartCouponDaemon BEFORE PRIVATE ${LIFT_STL_INCLUDE})
add_dependencies(SmartCouponDaemon lift_msvcp100_implib)
target_link_libraries(SmartCouponDaemon PRIVATE lift_smartcoupondaemon lift_common lift_common_scd ${LIFT_MSVCP100_IMPLIB})

# LobbyGate server exe. XmlReader_sv64.dll, bsConsole_sv64.dll and dbghelp.dll load at run time (not linked).
lift_exe(LobbyGate
  SOURCES src/Server/LobbyGate/LinkStubs.cpp src/Server/LobbyGate/LobbyGate.rc src/crt/wmain_bridge.c src/crt/tlssup.c src/crt/new_delete.c
  IMPORTS msvcr100 kernel32 user32 advapi32 shell32 ole32 shlwapi version ws2_32 iphlpapi)
target_compile_options(LobbyGate PRIVATE /GR-)
target_include_directories(LobbyGate BEFORE PRIVATE ${LIFT_STL_INCLUDE})
add_dependencies(LobbyGate lift_msvcp100_implib)
target_link_libraries(LobbyGate PRIVATE lift_lobbygate lift_common lift_common_lg ${LIFT_MSVCP100_IMPLIB})

# PostOfficeDaemon server exe. XmlReader_sv64.dll, bsConsole_sv64.dll and dbghelp.dll load at run time (not linked).
lift_exe(PostOfficeDaemon
  SOURCES src/Server/Economy/PostOfficeDaemon/LinkStubs.cpp src/Server/Economy/PostOfficeDaemon/PostOfficeDaemon.rc src/crt/wmain_bridge.c src/crt/tlssup.c src/crt/new_delete.c
  IMPORTS msvcr100 kernel32 user32 advapi32 shell32 ole32 odbc32 shlwapi version ws2_32 iphlpapi)
target_compile_options(PostOfficeDaemon PRIVATE /GR-)
target_include_directories(PostOfficeDaemon BEFORE PRIVATE ${LIFT_STL_INCLUDE})
add_dependencies(PostOfficeDaemon lift_msvcp100_implib)
target_link_libraries(PostOfficeDaemon PRIVATE lift_postofficedaemon lift_common lift_common_pod ${LIFT_MSVCP100_IMPLIB})

# LobbyDaemon BloodLib sources with a per-exe __FILE__ path. LobbyDaemon has no wrappers yet, so it uses
# the plain files and their default path literals. LIFT: a later wave adds the LobbyDaemon wrappers.
add_library(lift_common_ld STATIC
  src/Server/BloodLib/source/MemoryManager.cpp
  src/Server/BloodLib/source/RefCntObject.cpp
  ${LIFT_COMMON_PATH_SOURCES})
target_compile_options(lift_common_ld PRIVATE /GR-)
target_include_directories(lift_common_ld BEFORE PRIVATE ${LIFT_STL_INCLUDE})
add_dependencies(lift_common_ld lift_msvcp100_implib)
target_link_libraries(lift_common_ld PUBLIC lift_common)

# LobbyDaemon modules (static lib). Wave 0: declarations and LIFT_STUB bodies only (grep -rn "LIFT_STUB(" src).
# The 6 common modules (BannedWordFilter, FsdDecomposer, PerfCounterProvider) are in this lib only,
# so that the other exes do not change.
add_library(lift_lobbydaemon STATIC
  src/External/BannedWordFilter/BannedWordFilterLib.cpp
  src/External/BannedWordFilter/BannedWordFilterLoader.cpp
  src/External/BannedWordFilter/ConstFilterChat.cpp
  src/External/BannedWordFilter/ConstFilterName.cpp
  src/library/FsdReader/FsdDecomposer.cpp
  src/Server/BloodLib/source/PerfCounterProvider.cpp
  src/Server/Shared/SharedChannel.cpp
  src/Server/Shared/NPChannel2.cpp  # LIFT: Packet::FreeSize (0x29d0) and NPMsgHelper::LocaleHourToUTCTime (0x2be0), called by lift-lobbydaemon-15
  src/Server/Shared/BnsCommonConfigDefinition.cpp  # LIFT: BnsCommonConfig::Config, read by lift-lobbydaemon-21 (0x907e0)
  src/Server/LobbyDaemon/AbandonChargeJob.cpp
  src/Server/LobbyDaemon/AccountInventory.cpp  # LIFT: Goods::Fetch (0x6010) stub; no card owns the module, SendListGoodsOk (0xbe770) calls it
  src/Server/LobbyDaemon/AccountInventoryChannel.cpp
  src/Server/LobbyDaemon/AccountInventoryLobbyPacketHandler.cpp
  src/Server/LobbyDaemon/AccountInventoryLobbyPacketLobbySideHandlerList.cpp
  src/Server/LobbyDaemon/ActivateGradeJob.cpp
  src/Server/LobbyDaemon/AddSlotJob.cpp
  src/Server/LobbyDaemon/AuctionBidJob.cpp
  src/Server/LobbyDaemon/AuctionDeliverJob.cpp
  src/Server/LobbyDaemon/AuctionEscrow.cpp
  src/Server/LobbyDaemon/AuctionEscrowJob.cpp
  src/Server/LobbyDaemon/AuctionRollbackEscrowJob.cpp
  src/Server/LobbyDaemon/BLDaemonInfo.cpp
  src/Server/LobbyDaemon/BindCharacterSlotJob.cpp
  src/Server/LobbyDaemon/BoundedList.cpp
  src/Server/LobbyDaemon/CancelWaitCharacterDeletionJob.cpp
  src/Server/LobbyDaemon/ChangeCharacterAppearanceJob.cpp
  src/Server/LobbyDaemon/ChangeCharacterRaceJob.cpp
  src/Server/LobbyDaemon/ChangeCharacterSexJob.cpp
  src/Server/LobbyDaemon/ChangeUserNameJob.cpp
  src/Server/LobbyDaemon/Character.cpp
  src/Server/LobbyDaemon/CliSession.cpp
  src/Server/LobbyDaemon/CliSessionJob.cpp
  src/Server/LobbyDaemon/CliSessionManager.cpp
  src/Server/LobbyDaemon/CliSessionTable.cpp
  src/Server/LobbyDaemon/ContentsRuleConfigDefinition.cpp
  src/Server/LobbyDaemon/CreateCharacterJob.cpp
  src/Server/LobbyDaemon/CreateInitialUserNameJob.cpp
  src/Server/LobbyDaemon/DeleteCharacterJob.cpp
  src/Server/LobbyDaemon/DepositMileageJob.cpp
  src/Server/LobbyDaemon/EndWaitGameWorldJob.cpp
  src/Server/LobbyDaemon/EnterGameWorldJob.cpp
  src/Server/LobbyDaemon/ExtendJumpingCharacterCreationQuotaJob.cpp
  src/Server/LobbyDaemon/FsdShowcaseRecord.cpp
  src/Server/LobbyDaemon/GameTimeSchedule.cpp
  src/Server/LobbyDaemon/GameWorld.cpp
  src/Server/LobbyDaemon/GamedChannel.cpp
  src/Server/LobbyDaemon/GetChargeInfoJob.cpp
  src/Server/LobbyDaemon/GetGoodsCountJob.cpp
  src/Server/LobbyDaemon/GetLobbyServiceItemJob.cpp
  src/Server/LobbyDaemon/GiveupWaitGameWorldJob.cpp
  src/Server/LobbyDaemon/GradeService.cpp
  src/Server/LobbyDaemon/InfoGateChannel.cpp
  src/Server/LobbyDaemon/InitCliSessionWlobbyTokenJob.cpp
  src/Server/LobbyDaemon/InitCliSessionWnpTokenJob.cpp
  src/Server/LobbyDaemon/KickJob.cpp
  src/Server/LobbyDaemon/LeaveGameWorldJob.cpp
  src/Server/LobbyDaemon/ListGoodsJob.cpp
  src/Server/LobbyDaemon/ListLobbyServiceItemJob.cpp
  src/Server/LobbyDaemon/LobbyCharacterDeletionScheduler.cpp
  src/Server/LobbyDaemon/LobbyConfig.cpp
  src/Server/LobbyDaemon/LobbyConfigDef.cpp
  src/Server/LobbyDaemon/LobbyDB.cpp
  src/Server/LobbyDaemon/LobbyDaemon.cpp
  src/Server/LobbyDaemon/LobbyEvent.cpp
  src/Server/LobbyDaemon/LobbyGamePacketHandler.cpp
  src/Server/LobbyDaemon/LobbyGateChannel.cpp
  src/Server/LobbyDaemon/LobbyInfoGatePacketHandler.cpp
  src/Server/LobbyDaemon/LobbyInfoGatePacketLobbySideHandlerList.cpp
  src/Server/LobbyDaemon/LobbyJSON.cpp
  src/Server/LobbyDaemon/LobbyJob.cpp
  src/Server/LobbyDaemon/LobbyLobbyGatePacketHandler.cpp
  src/Server/LobbyDaemon/LobbyLobbyGatePacketLobbySideHandlerList.cpp
  src/Server/LobbyDaemon/LobbyLocale.cpp
  src/Server/LobbyDaemon/LobbyManagePacketHandler.cpp
  src/Server/LobbyDaemon/LobbyMessage.cpp
  src/Server/LobbyDaemon/LobbyPerfMonitor.cpp
  src/Server/LobbyDaemon/LobbyPredefine.cpp
  src/Server/LobbyDaemon/LobbyService.cpp
  src/Server/LobbyDaemon/LobbyStats.cpp
  src/Server/LobbyDaemon/LobbyTick.cpp
  src/Server/LobbyDaemon/LobbyToken.cpp
  src/Server/LobbyDaemon/LogoutInGameWorldJob.cpp
  src/Server/LobbyDaemon/LogoutJob.cpp
  src/Server/LobbyDaemon/ManageChannel.cpp
  src/Server/LobbyDaemon/MembershipMileage.cpp
  src/Server/LobbyDaemon/Mileage.cpp
  src/Server/LobbyDaemon/MileageDailyLimit.cpp
  src/Server/LobbyDaemon/NPLobbyMessageHandler.cpp
  src/Server/LobbyDaemon/NPServiceChannel.cpp
  src/Server/LobbyDaemon/ObjectPoolLobbyDaemon.cpp
  src/Server/LobbyDaemon/PcCafe.cpp
  src/Server/LobbyDaemon/PcCafeMileage.cpp
  src/Server/LobbyDaemon/PostOfficeChannel.cpp
  src/Server/LobbyDaemon/PostOfficeClientSideHandlerList.cpp
  src/Server/LobbyDaemon/PostOfficePacketHandler.cpp
  src/Server/LobbyDaemon/RecoverPcJob.cpp
  src/Server/LobbyDaemon/RefCntList.cpp
  src/Server/LobbyDaemon/RenameCharacterJob.cpp
  src/Server/LobbyDaemon/RuleSet.cpp
  src/Server/LobbyDaemon/SecondPasswordGetStatusJob.cpp
  src/Server/LobbyDaemon/SecondPasswordIsVerifiedJob.cpp
  src/Server/LobbyDaemon/SetupNpScheduleInfoJob.cpp
  src/Server/LobbyDaemon/StartChargeJob.cpp
  src/Server/LobbyDaemon/StartCliSessionWlobbyTokenJob.cpp
  src/Server/LobbyDaemon/StartCliSessionWnpTokenJob.cpp
  src/Server/LobbyDaemon/StopChargeJob.cpp
  src/Server/LobbyDaemon/TakeAccountTimeBasedPlayRewardJob.cpp
  src/Server/LobbyDaemon/TakeGoodsJob.cpp
  src/Server/LobbyDaemon/TencentUIC.cpp
  src/Server/LobbyDaemon/TransactionChannel.cpp
  src/Server/LobbyDaemon/TryEnterGameWorldJob.cpp
  src/Server/LobbyDaemon/WaitQueue.cpp)
target_compile_options(lift_lobbydaemon PRIVATE /GR-)
target_include_directories(lift_lobbydaemon BEFORE PRIVATE ${LIFT_STL_INCLUDE})
target_include_directories(lift_lobbydaemon PUBLIC ${LIFT_SRC_INCLUDE})
add_dependencies(lift_lobbydaemon lift_msvcp100_implib)
target_link_libraries(lift_lobbydaemon PUBLIC lift_common)

# LobbyDaemon server exe. It has no LinkStubs.cpp: each stub is in its owner module.
lift_exe(LobbyDaemon
  SOURCES src/Server/LobbyDaemon/LobbyDaemon.rc src/crt/wmain_bridge.c src/crt/tlssup.c src/crt/new_delete.c
  IMPORTS msvcr100 kernel32 user32 advapi32 shell32 ole32 odbc32 shlwapi version ws2_32 iphlpapi)
target_compile_options(LobbyDaemon PRIVATE /GR-)
target_include_directories(LobbyDaemon BEFORE PRIVATE ${LIFT_STL_INCLUDE})
add_dependencies(LobbyDaemon lift_msvcp100_implib)
target_link_libraries(LobbyDaemon PRIVATE lift_lobbydaemon lift_common lift_common_ld ${LIFT_MSVCP100_IMPLIB})

# GameDaemon (card lift-gamedaemon-0c). Opt-in: configure with -DLIFT_GAMEDAEMON=ON.
# LIFT: default OFF. The 476 GameDaemon modules and the lift_common_gd copy make the default build much
# slower (more than 10 %), and no default exe needs them.
option(LIFT_GAMEDAEMON "Build the GameDaemon lift (wave 0: stubs)" OFF)
if(LIFT_GAMEDAEMON)
  # Common code for GameDaemon (lessons.md pattern 35 and A22). It is a full copy of the common sources
  # without BloodCert (vendor code, not linked into GameDaemon, plan section 1). It does not link lift_common,
  # so the other exes keep their objects and their object order.
  set(LIFT_COMMON_GD_SOURCES ${LIFT_COMMON_SOURCES})
  list(REMOVE_ITEM LIFT_COMMON_GD_SOURCES src/Security/source/BloodCert/BloodCert.cpp)
  add_library(lift_common_gd STATIC ${LIFT_COMMON_GD_SOURCES}
    src/Server/BloodLib/source/MemoryManager.cpp
    src/Server/BloodLib/source/RefCntObject.cpp
    src/Server/BloodLib/source/PerfCounterProvider.cpp
    src/External/BannedWordFilter/BannedWordFilterLib.cpp
    src/External/BannedWordFilter/BannedWordFilterLoader.cpp
    src/External/BannedWordFilter/ConstFilterChat.cpp
    src/External/BannedWordFilter/ConstFilterName.cpp
    src/library/FsdReader/FsdDecomposer.cpp
    src/Server/Shared/SharedChannel.cpp
    src/Server/Shared/NPChannel2.cpp
    src/Server/Shared/BnsCommonConfigDefinition.cpp
    src/Server/Shared/CouponGameEventConfig.cpp)
  target_compile_options(lift_common_gd PRIVATE /GR-)
  target_compile_definitions(lift_common_gd PUBLIC WIN32_LEAN_AND_MEAN)
  target_include_directories(lift_common_gd BEFORE PRIVATE ${LIFT_STL_INCLUDE})
  target_include_directories(lift_common_gd PUBLIC ${LIFT_SRC_INCLUDE})
  add_dependencies(lift_common_gd lift_msvcp100_implib)
  foreach(imp odbc32 ws2_32 iphlpapi ole32 advapi32 shell32 version user32 shlwapi)
    target_link_libraries(lift_common_gd INTERFACE "${WINE_LIBDIR}/lib${imp}.a")
  endforeach()
  target_link_libraries(lift_common_gd PUBLIC ${LIFT_ZSTD_LINK})

  # GameDaemon modules (static lib). Wave 0: declarations, LIFT_STUB bodies and feature-off bodies.
  # One source line per module (index.tsv module column). The list is inline: a card may add a source line
  # here (proof R2), but no card may edit a *.cmake file (pinned). LinkStubs.cpp holds hand-written link
  # bodies. The GameDaemon dir is not in LIFT_SRC_INCLUDE: the modules include their headers by quoted name.
  add_library(lift_gamedaemon STATIC
    src/Server/GameDaemon/accessoryproperty.cpp
    src/Server/GameDaemon/accountinventorychannel_cpp.cpp
    src/Server/GameDaemon/accountinventorychannel_h.cpp
    src/Server/GameDaemon/accountinventorytran_cpp.cpp
    src/Server/GameDaemon/accountinventorytran_h.cpp
    src/Server/GameDaemon/achievementchannel_cpp.cpp
    src/Server/GameDaemon/achievementchannel_h.cpp
    src/Server/GameDaemon/achievementdata.cpp
    src/Server/GameDaemon/acquiredskill1.cpp
    src/Server/GameDaemon/action_cpp.cpp
    src/Server/GameDaemon/action_h.cpp
    src/Server/GameDaemon/activatedteleport.cpp
    src/Server/GameDaemon/actsequence.cpp
    src/Server/GameDaemon/actsequenceloader_cpp.cpp
    src/Server/GameDaemon/actsequenceloader_h.cpp
    src/Server/GameDaemon/adler32.c
    src/Server/GameDaemon/aes128_cpp.cpp
    src/Server/GameDaemon/aliasimpl_cpp.cpp
    src/Server/GameDaemon/aliasimpl_h.cpp
    src/Server/GameDaemon/arenagamechannel_cpp.cpp
    src/Server/GameDaemon/arenalobbycommon.cpp
    src/Server/GameDaemon/arenaroommanager_cpp.cpp
    src/Server/GameDaemon/arenaroommanager_h.cpp
    src/Server/GameDaemon/associativetable_cpp.cpp
    src/Server/GameDaemon/associativetable_h.cpp
    src/Server/GameDaemon/attractionstate_cpp.cpp
    src/Server/GameDaemon/attractionstate_h.cpp
    src/Server/GameDaemon/autokeytable_cpp.cpp
    src/Server/GameDaemon/autokeytable_h.cpp
    src/Server/GameDaemon/automatedcreature.cpp
    src/Server/GameDaemon/bannedwordfilterlib.cpp
    src/Server/GameDaemon/bannedwordfiltermemorymanager.cpp
    src/Server/GameDaemon/base64.cpp
    src/Server/GameDaemon/battleroyalfield_cpp.cpp
    src/Server/GameDaemon/battleroyalfield_h.cpp
    src/Server/GameDaemon/bignumber.cpp
    src/Server/GameDaemon/binarydatafile.cpp
    src/Server/GameDaemon/bnscommonutil.cpp
    src/Server/GameDaemon/boardgacha.cpp
    src/Server/GameDaemon/bosscombatsequence.cpp
    src/Server/GameDaemon/bossnpc.cpp
    src/Server/GameDaemon/bossskillaction_cpp.cpp
    src/Server/GameDaemon/bossskillaction_h.cpp
    src/Server/GameDaemon/brainbase_cpp.cpp
    src/Server/GameDaemon/brainbase_h.cpp
    src/Server/GameDaemon/brainboss_cpp.cpp
    src/Server/GameDaemon/brainboss_h.cpp
    src/Server/GameDaemon/braincitizen_cpp.cpp
    src/Server/GameDaemon/braincitizen_h.cpp
    src/Server/GameDaemon/brainconst.cpp
    src/Server/GameDaemon/brainfactory.cpp
    src/Server/GameDaemon/brainfollower_cpp.cpp
    src/Server/GameDaemon/brainfollower_h.cpp
    src/Server/GameDaemon/brainmonster_cpp.cpp
    src/Server/GameDaemon/brainmonster_h.cpp
    src/Server/GameDaemon/brainmonstertalkable_cpp.cpp
    src/Server/GameDaemon/brainmonstertalkable_h.cpp
    src/Server/GameDaemon/brainraidboss_cpp.cpp
    src/Server/GameDaemon/brainraidboss_h.cpp
    src/Server/GameDaemon/brainstate_cpp.cpp
    src/Server/GameDaemon/brainstate_h.cpp
    src/Server/GameDaemon/builderoperationmanager.cpp
    src/Server/GameDaemon/cachedaemonchannel_1.cpp
    src/Server/GameDaemon/cachedaemonchannel_2.cpp
    src/Server/GameDaemon/cachedaemonchannel_3.cpp
    src/Server/GameDaemon/cachedaemonchannel_4.cpp
    src/Server/GameDaemon/campfire.cpp
    src/Server/GameDaemon/capturetheflag_cpp.cpp
    src/Server/GameDaemon/capturetheflag_h.cpp
    src/Server/GameDaemon/challengelistcontainer_cpp.cpp
    src/Server/GameDaemon/challengelistcontainer_h.cpp
    src/Server/GameDaemon/challengelistproperty.cpp
    src/Server/GameDaemon/challengeparty.cpp
    src/Server/GameDaemon/challengepartyattractionstate_cpp.cpp
    src/Server/GameDaemon/challengepartyattractionstate_h.cpp
    src/Server/GameDaemon/challengepartytran_cpp.cpp
    src/Server/GameDaemon/challengepartytran_h.cpp
    src/Server/GameDaemon/changeweaponappearancetran_cpp.cpp
    src/Server/GameDaemon/changeweaponappearancetran_h.cpp
    src/Server/GameDaemon/channel.cpp
    src/Server/GameDaemon/charactermanagementtran_cpp.cpp
    src/Server/GameDaemon/charactermanagementtran_h.cpp
    src/Server/GameDaemon/chattinglog.cpp
    src/Server/GameDaemon/chattingserverchannel.cpp
    src/Server/GameDaemon/clientoption_cpp.cpp
    src/Server/GameDaemon/clientoption_h.cpp
    src/Server/GameDaemon/clientsessionhandler.cpp
    src/Server/GameDaemon/closetmanager.cpp
    src/Server/GameDaemon/closettran_cpp.cpp
    src/Server/GameDaemon/closettran_h.cpp
    src/Server/GameDaemon/collectingmanager_cpp.cpp
    src/Server/GameDaemon/collectingmanager_h.cpp
    src/Server/GameDaemon/collectingproperty.cpp
    src/Server/GameDaemon/combatsequence_cpp.cpp
    src/Server/GameDaemon/combatsequence_h.cpp
    src/Server/GameDaemon/combatsequenceloader.cpp
    src/Server/GameDaemon/connection.cpp
    src/Server/GameDaemon/contentquota.cpp
    src/Server/GameDaemon/contentquotaproperty.cpp
    src/Server/GameDaemon/contentsruleconfigdefinition.cpp
    src/Server/GameDaemon/contribution_cpp.cpp
    src/Server/GameDaemon/contribution_h.cpp
    src/Server/GameDaemon/controlledcreature.cpp
    src/Server/GameDaemon/convoy.cpp
    src/Server/GameDaemon/costumeproperty.cpp
    src/Server/GameDaemon/coupongameeventconfig.cpp
    src/Server/GameDaemon/crc32.c
    src/Server/GameDaemon/creature_cpp_1.cpp
    src/Server/GameDaemon/creature_cpp_2.cpp
    src/Server/GameDaemon/creature_h.cpp
    src/Server/GameDaemon/creaturejob.cpp
    src/Server/GameDaemon/creatureproperty.cpp
    src/Server/GameDaemon/crypto.cpp
    src/Server/GameDaemon/cryptokey.cpp
    src/Server/GameDaemon/daemon.cpp
    src/Server/GameDaemon/datamanager_cpp_1.cpp
    src/Server/GameDaemon/datamanager_cpp_2.cpp
    src/Server/GameDaemon/datamanager_cpp_3.cpp
    src/Server/GameDaemon/datamanager_h.cpp
    src/Server/GameDaemon/datapacker.cpp
    src/Server/GameDaemon/datareader.cpp
    src/Server/GameDaemon/datareaderimpl.cpp
    src/Server/GameDaemon/deathmatchduelmanager_cpp.cpp
    src/Server/GameDaemon/deathmatchduelmanager_h.cpp
    src/Server/GameDaemon/deflate.c
    src/Server/GameDaemon/deflog.cpp
    src/Server/GameDaemon/defmemory_cpp.cpp
    src/Server/GameDaemon/defmemory_h.cpp
    src/Server/GameDaemon/discoveryarea.cpp
    src/Server/GameDaemon/droppedpouch.cpp
    src/Server/GameDaemon/duelbot_cpp.cpp
    src/Server/GameDaemon/duelbot_h.cpp
    src/Server/GameDaemon/duelbotaction.cpp
    src/Server/GameDaemon/duelbotchallengeattractionstate_cpp.cpp
    src/Server/GameDaemon/duelbotchallengeattractionstate_h.cpp
    src/Server/GameDaemon/duelbotdaemonchannel.cpp
    src/Server/GameDaemon/duelbotspawn.cpp
    src/Server/GameDaemon/duelbottask.cpp
    src/Server/GameDaemon/duelbottrainingroom_cpp.cpp
    src/Server/GameDaemon/duelbottrainingroom_h.cpp
    src/Server/GameDaemon/duelbottrainingroomscore.cpp
    src/Server/GameDaemon/duelbottrainingroomscorecontainer.cpp
    src/Server/GameDaemon/duelbottrainingroomtran_cpp.cpp
    src/Server/GameDaemon/duelbottrainingroomtran_h.cpp
    src/Server/GameDaemon/duelmanager_cpp.cpp
    src/Server/GameDaemon/duelmanager_h.cpp
    src/Server/GameDaemon/effect_cpp_1.cpp
    src/Server/GameDaemon/effect_cpp_2.cpp
    src/Server/GameDaemon/effect_h.cpp
    src/Server/GameDaemon/effectcontent_cpp_1.cpp
    src/Server/GameDaemon/effectcontent_cpp_2.cpp
    src/Server/GameDaemon/effectcontent_h.cpp
    src/Server/GameDaemon/effectproperty_cpp.cpp
    src/Server/GameDaemon/effectproperty_h.cpp
    src/Server/GameDaemon/elreaderimpl.cpp
    src/Server/GameDaemon/envobj_cpp.cpp
    src/Server/GameDaemon/envobj_h.cpp
    src/Server/GameDaemon/extracreatureproperty_cpp.cpp
    src/Server/GameDaemon/extracreatureproperty_h.cpp
    src/Server/GameDaemon/fielditem.cpp
    src/Server/GameDaemon/filter_cpp.cpp
    src/Server/GameDaemon/filter_h.cpp
    src/Server/GameDaemon/fishingcontainer_cpp.cpp
    src/Server/GameDaemon/fishingcontainer_h.cpp
    src/Server/GameDaemon/fishingproperty.cpp
    src/Server/GameDaemon/fragmentpacket_cpp.cpp
    src/Server/GameDaemon/fragmentpacket_h.cpp
    src/Server/GameDaemon/fsd.cpp
    src/Server/GameDaemon/fsdcomposer.cpp
    src/Server/GameDaemon/fsdmakepcrecord.cpp
    src/Server/GameDaemon/fsdshowcaserecord.cpp
    src/Server/GameDaemon/gamearenachannel_cpp_1.cpp
    src/Server/GameDaemon/gamearenachannel_cpp_2.cpp
    src/Server/GameDaemon/gamearenachannel_h.cpp
    src/Server/GameDaemon/gamebuilderpackethandler.cpp
    src/Server/GameDaemon/gamebuildertask_cpp.cpp
    src/Server/GameDaemon/gamebuildertask_h.cpp
    src/Server/GameDaemon/gamedaemon_cpp.cpp
    src/Server/GameDaemon/gamedaemon_h.cpp
    src/Server/GameDaemon/gamedconfig.cpp
    src/Server/GameDaemon/gamedebugcommand_cpp_1.cpp
    src/Server/GameDaemon/gamedebugcommand_cpp_2.cpp
    src/Server/GameDaemon/gamedebugcommand_h.cpp
    src/Server/GameDaemon/gamedebugpackethandler_1.cpp
    src/Server/GameDaemon/gamedebugpackethandler_2.cpp
    src/Server/GameDaemon/gameguard.cpp
    src/Server/GameDaemon/gamelocale.cpp
    src/Server/GameDaemon/gamelog_1.cpp
    src/Server/GameDaemon/gamelog_2.cpp
    src/Server/GameDaemon/gamelog_3.cpp
    src/Server/GameDaemon/gamelog_4.cpp
    src/Server/GameDaemon/gamemath_cpp.cpp
    src/Server/GameDaemon/gamemath_h.cpp
    src/Server/GameDaemon/gameobject_cpp.cpp
    src/Server/GameDaemon/gameobject_h.cpp
    src/Server/GameDaemon/gamepackethandler_1.cpp
    src/Server/GameDaemon/gamepackethandler_2.cpp
    src/Server/GameDaemon/gamepackethandler_3.cpp
    src/Server/GameDaemon/gamepackethandler_4.cpp
    src/Server/GameDaemon/gamepackethandlerlist.cpp
    src/Server/GameDaemon/gametran_cpp.cpp
    src/Server/GameDaemon/gametran_h.cpp
    src/Server/GameDaemon/gathersource.cpp
    src/Server/GameDaemon/gemproperty.cpp
    src/Server/GameDaemon/geomovechecker.cpp
    src/Server/GameDaemon/geopathfinder.cpp
    src/Server/GameDaemon/geoworld_cpp.cpp
    src/Server/GameDaemon/geoworld_h.cpp
    src/Server/GameDaemon/groceryproperty.cpp
    src/Server/GameDaemon/guild_cpp_1.cpp
    src/Server/GameDaemon/guild_cpp_2.cpp
    src/Server/GameDaemon/guild_h.cpp
    src/Server/GameDaemon/guildbank.cpp
    src/Server/GameDaemon/guildbattlefieldmanager.cpp
    src/Server/GameDaemon/guildcraft.cpp
    src/Server/GameDaemon/guildjointicket_cpp.cpp
    src/Server/GameDaemon/guildjointicket_h.cpp
    src/Server/GameDaemon/guildtran_cpp.cpp
    src/Server/GameDaemon/guildtran_h.cpp
    src/Server/GameDaemon/guilduniform.cpp
    src/Server/GameDaemon/httpclient.cpp
    src/Server/GameDaemon/idlewatcher_cpp.cpp
    src/Server/GameDaemon/idlewatcher_h.cpp
    src/Server/GameDaemon/include_jsoncpp.cpp
    src/Server/GameDaemon/include_logarchive.cpp
    src/Server/GameDaemon/include_packet.cpp
    src/Server/GameDaemon/include_packetutil.cpp
    src/Server/GameDaemon/include_property.cpp
    src/Server/GameDaemon/include_refcntobject.cpp
    src/Server/GameDaemon/include_stlmemory.cpp
    src/Server/GameDaemon/inffast.c
    src/Server/GameDaemon/inflate.c
    src/Server/GameDaemon/inftrees.c
    src/Server/GameDaemon/instantpaymenttran_cpp.cpp
    src/Server/GameDaemon/instantpaymenttran_h.cpp
    src/Server/GameDaemon/inventory_cpp_1.cpp
    src/Server/GameDaemon/inventory_cpp_2.cpp
    src/Server/GameDaemon/inventory_h.cpp
    src/Server/GameDaemon/inventoryaction_cpp_1.cpp
    src/Server/GameDaemon/inventoryaction_cpp_2.cpp
    src/Server/GameDaemon/inventoryaction_cpp_3.cpp
    src/Server/GameDaemon/inventoryaction_cpp_4.cpp
    src/Server/GameDaemon/inventoryaction_h.cpp
    src/Server/GameDaemon/ioapi.c
    src/Server/GameDaemon/ioworkerthread_cpp.cpp
    src/Server/GameDaemon/item_cpp_1.cpp
    src/Server/GameDaemon/item_cpp_2.cpp
    src/Server/GameDaemon/item_h_1.cpp
    src/Server/GameDaemon/item_h_2.cpp
    src/Server/GameDaemon/itempouch.cpp
    src/Server/GameDaemon/jackpotbossmanager.cpp
    src/Server/GameDaemon/leadtheballmanager_cpp.cpp
    src/Server/GameDaemon/leadtheballmanager_h.cpp
    src/Server/GameDaemon/leaveworldtran_cpp.cpp
    src/Server/GameDaemon/leaveworldtran_h.cpp
    src/Server/GameDaemon/lobbydaemonchannel_cpp.cpp
    src/Server/GameDaemon/lobbydaemonchannel_h.cpp
    src/Server/GameDaemon/lobbytokenauthtran_cpp.cpp
    src/Server/GameDaemon/lobbytokenauthtran_h.cpp
    src/Server/GameDaemon/lock.cpp
    src/Server/GameDaemon/logagent.cpp
    src/Server/GameDaemon/logagentpackethandler.cpp
    src/Server/GameDaemon/logarchivecontext.cpp
    src/Server/GameDaemon/logarchivefilemanager.cpp
    src/Server/GameDaemon/logarchivesession.cpp
    src/Server/GameDaemon/logarchiveutil.cpp
    src/Server/GameDaemon/logbuffer_cpp.cpp
    src/Server/GameDaemon/logserver.cpp
    src/Server/GameDaemon/logserversessionhandler_cpp.cpp
    src/Server/GameDaemon/logserversessionhandler_h.cpp
    src/Server/GameDaemon/managementdchannel.cpp
    src/Server/GameDaemon/managementtask.cpp
    src/Server/GameDaemon/managementtran_cpp.cpp
    src/Server/GameDaemon/managementtran_h.cpp
    src/Server/GameDaemon/manipulateaction_cpp.cpp
    src/Server/GameDaemon/manipulateaction_h.cpp
    src/Server/GameDaemon/marketdealeragentchannel.cpp
    src/Server/GameDaemon/marketreaderagentchannel.cpp
    src/Server/GameDaemon/marketservicetran_cpp.cpp
    src/Server/GameDaemon/marketservicetran_h.cpp
    src/Server/GameDaemon/md5.c
    src/Server/GameDaemon/mentoring.cpp
    src/Server/GameDaemon/mentoringproperty.cpp
    src/Server/GameDaemon/mentoringtran_cpp.cpp
    src/Server/GameDaemon/mentoringtran_h.cpp
    src/Server/GameDaemon/mileagedeposittran_cpp.cpp
    src/Server/GameDaemon/mileagedeposittran_h.cpp
    src/Server/GameDaemon/moveaction_cpp.cpp
    src/Server/GameDaemon/moveaction_h.cpp
    src/Server/GameDaemon/mtrandom_cpp.cpp
    src/Server/GameDaemon/mtrandom_h.cpp
    src/Server/GameDaemon/mysteriousstore.cpp
    src/Server/GameDaemon/ncguard.cpp
    src/Server/GameDaemon/nofile.cpp
    src/Server/GameDaemon/npc_cpp.cpp
    src/Server/GameDaemon/npc_h.cpp
    src/Server/GameDaemon/npcaction.cpp
    src/Server/GameDaemon/npcactionfactory.cpp
    src/Server/GameDaemon/npcdeadbody.cpp
    src/Server/GameDaemon/npchannel2.cpp
    src/Server/GameDaemon/npcparty_cpp.cpp
    src/Server/GameDaemon/npcparty_h.cpp
    src/Server/GameDaemon/npcspawn_cpp.cpp
    src/Server/GameDaemon/npcspawn_h.cpp
    src/Server/GameDaemon/npcsquad.cpp
    src/Server/GameDaemon/npctask.cpp
    src/Server/GameDaemon/npmessagehandler.cpp
    src/Server/GameDaemon/npservicechannel.cpp
    src/Server/GameDaemon/npservicetran_cpp.cpp
    src/Server/GameDaemon/npservicetran_h.cpp
    src/Server/GameDaemon/occupationwarmanager.cpp
    src/Server/GameDaemon/packetbuffer.cpp
    src/Server/GameDaemon/parallelworker.cpp
    src/Server/GameDaemon/partyauction.cpp
    src/Server/GameDaemon/partybattlemanager_cpp.cpp
    src/Server/GameDaemon/partybattlemanager_h.cpp
    src/Server/GameDaemon/partymatchmaker_cpp.cpp
    src/Server/GameDaemon/partymatchmaker_h.cpp
    src/Server/GameDaemon/pc_cpp_1.cpp
    src/Server/GameDaemon/pc_cpp_2.cpp
    src/Server/GameDaemon/pc_cpp_3.cpp
    src/Server/GameDaemon/pc_cpp_4.cpp
    src/Server/GameDaemon/pc_h.cpp
    src/Server/GameDaemon/pcattractionstate_cpp.cpp
    src/Server/GameDaemon/pcattractionstate_h.cpp
    src/Server/GameDaemon/petitiondaemonchannel.cpp
    src/Server/GameDaemon/petitionmanager.cpp
    src/Server/GameDaemon/petitionpacketbufferhandler.cpp
    src/Server/GameDaemon/postbox.cpp
    src/Server/GameDaemon/postofficeagentchannel.cpp
    src/Server/GameDaemon/posttran_cpp.cpp
    src/Server/GameDaemon/posttran_h.cpp
    src/Server/GameDaemon/propertydb.cpp
    src/Server/GameDaemon/propertyfield.cpp
    src/Server/GameDaemon/propertysync.cpp
    src/Server/GameDaemon/propertytran.cpp
    src/Server/GameDaemon/publicraid_cpp.cpp
    src/Server/GameDaemon/publicraid_h.cpp
    src/Server/GameDaemon/publisherlibsfunctions.cpp
    src/Server/GameDaemon/questjournal_cpp_1.cpp
    src/Server/GameDaemon/questjournal_cpp_2.cpp
    src/Server/GameDaemon/questjournal_h.cpp
    src/Server/GameDaemon/questlist.cpp
    src/Server/GameDaemon/questproperty.cpp
    src/Server/GameDaemon/questtableimpl_cpp.cpp
    src/Server/GameDaemon/questtableimpl_h.cpp
    src/Server/GameDaemon/questtask.cpp
    src/Server/GameDaemon/raiddungeon.cpp
    src/Server/GameDaemon/raiddungeonbindproperty.cpp
    src/Server/GameDaemon/raiddungeonunbindproperty.cpp
    src/Server/GameDaemon/randomstore.cpp
    src/Server/GameDaemon/randomstoremanager.cpp
    src/Server/GameDaemon/rankingchannel.cpp
    src/Server/GameDaemon/rankingreward.cpp
    src/Server/GameDaemon/rankingseason_cpp.cpp
    src/Server/GameDaemon/rankingseason_h.cpp
    src/Server/GameDaemon/reaction.cpp
    src/Server/GameDaemon/recycletimemanager.cpp
    src/Server/GameDaemon/recycletimeproperty.cpp
    src/Server/GameDaemon/refcntlist.cpp
    src/Server/GameDaemon/rsa_cpp.cpp
    src/Server/GameDaemon/rsa_h.cpp
    src/Server/GameDaemon/ruleconfig.cpp
    src/Server/GameDaemon/script.cpp
    src/Server/GameDaemon/scriptloader.cpp
    src/Server/GameDaemon/scripttable.cpp
    src/Server/GameDaemon/seasoncontentscombatrecord.cpp
    src/Server/GameDaemon/seasoncontentstimeattackrecord.cpp
    src/Server/GameDaemon/seasoncontentstran_cpp.cpp
    src/Server/GameDaemon/seasoncontentstran_h.cpp
    src/Server/GameDaemon/seasonscore.cpp
    src/Server/GameDaemon/security.cpp
    src/Server/GameDaemon/sendachievementevent.cpp
    src/Server/GameDaemon/serializedobject_cpp.cpp
    src/Server/GameDaemon/serializedobject_h.cpp
    src/Server/GameDaemon/serializer.cpp
    src/Server/GameDaemon/serializertimer_cpp.cpp
    src/Server/GameDaemon/serializertimer_h.cpp
    src/Server/GameDaemon/session.cpp
    src/Server/GameDaemon/skill.cpp
    src/Server/GameDaemon/skillaction_cpp_1.cpp
    src/Server/GameDaemon/skillaction_cpp_2.cpp
    src/Server/GameDaemon/skillaction_h.cpp
    src/Server/GameDaemon/skillpage.cpp
    src/Server/GameDaemon/skillskinproperty.cpp
    src/Server/GameDaemon/skilltask.cpp
    src/Server/GameDaemon/skilltrainingroom_cpp.cpp
    src/Server/GameDaemon/skilltrainingroom_h.cpp
    src/Server/GameDaemon/slatecontents.cpp
    src/Server/GameDaemon/slateproperty.cpp
    src/Server/GameDaemon/smartcoupondchannel.cpp
    src/Server/GameDaemon/smartcoupongamepackethandler.cpp
    src/Server/GameDaemon/source_alertsender.cpp
    src/Server/GameDaemon/source_delayedrelease.cpp
    src/Server/GameDaemon/source_jsoncpp.cpp
    src/Server/GameDaemon/source_log.cpp
    src/Server/GameDaemon/source_logarchive.cpp
    src/Server/GameDaemon/source_logfile.cpp
    src/Server/GameDaemon/source_logmedia.cpp
    src/Server/GameDaemon/source_lognetwork.cpp
    src/Server/GameDaemon/source_packet.cpp
    src/Server/GameDaemon/source_packetutil.cpp
    src/Server/GameDaemon/source_property.cpp
    src/Server/GameDaemon/source_refcntobject.cpp
    src/Server/GameDaemon/source_timer.cpp
    src/Server/GameDaemon/src_stlmemory.cpp
    src/Server/GameDaemon/stringbuilder.cpp
    src/Server/GameDaemon/summoned_cpp.cpp
    src/Server/GameDaemon/summoned_h.cpp
    src/Server/GameDaemon/summonedproperty.cpp
    src/Server/GameDaemon/summonedtask_cpp.cpp
    src/Server/GameDaemon/summonedtask_h.cpp
    src/Server/GameDaemon/systemaction_cpp.cpp
    src/Server/GameDaemon/systemaction_h.cpp
    src/Server/GameDaemon/systemobject.cpp
    src/Server/GameDaemon/table.cpp
    src/Server/GameDaemon/tableimpl_cpp.cpp
    src/Server/GameDaemon/tableimpl_h.cpp
    src/Server/GameDaemon/tagmatchduelmanager_cpp.cpp
    src/Server/GameDaemon/tagmatchduelmanager_h.cpp
    src/Server/GameDaemon/takeachievementrewardtran_cpp.cpp
    src/Server/GameDaemon/takeachievementrewardtran_h.cpp
    src/Server/GameDaemon/task_cpp_1.cpp
    src/Server/GameDaemon/task_cpp_2.cpp
    src/Server/GameDaemon/task_cpp_3.cpp
    src/Server/GameDaemon/task_cpp_4.cpp
    src/Server/GameDaemon/task_cpp_5.cpp
    src/Server/GameDaemon/task_h.cpp
    src/Server/GameDaemon/team_cpp_1.cpp
    src/Server/GameDaemon/team_cpp_2.cpp
    src/Server/GameDaemon/team_h.cpp
    src/Server/GameDaemon/teaminvitationcardbox.cpp
    src/Server/GameDaemon/teamparty.cpp
    src/Server/GameDaemon/tencentprotect.cpp
    src/Server/GameDaemon/tendencymanager_cpp.cpp
    src/Server/GameDaemon/tendencymanager_h.cpp
    src/Server/GameDaemon/timebasedplaytran_cpp.cpp
    src/Server/GameDaemon/timebasedplaytran_h.cpp
    src/Server/GameDaemon/tlog.cpp
    src/Server/GameDaemon/trade.cpp
    src/Server/GameDaemon/transactionexpirechecker.cpp
    src/Server/GameDaemon/trees.c
    src/Server/GameDaemon/twofish2.cpp
    src/Server/GameDaemon/unzip.c
    src/Server/GameDaemon/user_cpp.cpp
    src/Server/GameDaemon/user_h.cpp
    src/Server/GameDaemon/util.cpp
    src/Server/GameDaemon/warfieldattractionstate_cpp.cpp
    src/Server/GameDaemon/warfieldattractionstate_h.cpp
    src/Server/GameDaemon/warfieldmanager.cpp
    src/Server/GameDaemon/weaponproperty.cpp
    src/Server/GameDaemon/winserviceconsole_cpp.cpp
    src/Server/GameDaemon/winserviceconsole_h.cpp
    src/Server/GameDaemon/world.cpp
    src/Server/GameDaemon/worldserializedobject_cpp.cpp
    src/Server/GameDaemon/worldserializedobject_h.cpp
    src/Server/GameDaemon/worldserializer_cpp.cpp
    src/Server/GameDaemon/worldserializer_h.cpp
    src/Server/GameDaemon/xigncode3.cpp
    src/Server/GameDaemon/zone_cpp_1.cpp
    src/Server/GameDaemon/zone_cpp_2.cpp
    src/Server/GameDaemon/zone_cpp_3.cpp
    src/Server/GameDaemon/zone_h.cpp
    src/Server/GameDaemon/zonebroadcast_cpp.cpp
    src/Server/GameDaemon/zonebroadcast_h.cpp
    src/Server/GameDaemon/zonecellattributemanager.cpp
    src/Server/GameDaemon/zoneevent.cpp
    src/Server/GameDaemon/zonenpcspawnevent.cpp
    src/Server/GameDaemon/zonescore.cpp
    src/Server/GameDaemon/zoneserializedobject.cpp
    src/Server/GameDaemon/zonetimer_cpp.cpp
    src/Server/GameDaemon/zonetimer_h.cpp
    src/Server/GameDaemon/zonetriggerevent_cpp.cpp
    src/Server/GameDaemon/zonetriggerevent_h.cpp
    src/Server/GameDaemon/zutil.c
    src/Server/GameDaemon/zwave_sdk_helper.cpp
    src/Server/GameDaemon/LinkStubs.cpp
  )
  target_compile_options(lift_gamedaemon PRIVATE $<$<COMPILE_LANGUAGE:CXX>:/GR->)
  target_include_directories(lift_gamedaemon BEFORE PRIVATE ${LIFT_STL_INCLUDE})
  add_dependencies(lift_gamedaemon lift_msvcp100_implib)
  target_link_libraries(lift_gamedaemon PUBLIC lift_common_gd)

  lift_exe(GameDaemon
    SOURCES src/crt/wmain_bridge.c src/crt/tlssup.c src/crt/new_delete.c
    IMPORTS msvcr100 kernel32 user32 advapi32 shell32 ole32 odbc32 shlwapi version ws2_32 iphlpapi)
  target_compile_options(GameDaemon PRIVATE /GR-)
  target_include_directories(GameDaemon BEFORE PRIVATE ${LIFT_STL_INCLUDE})
  add_dependencies(GameDaemon lift_msvcp100_implib)
  target_link_libraries(GameDaemon PRIVATE lift_gamedaemon lift_common_gd ${LIFT_MSVCP100_IMPLIB})
endif()
