// LIFT: Build wrapper, no PDB module. LobbyGate and SmartCouponDaemon build BnsCommonConfigDefinition.cpp
// from a project directory one level up from the CacheGate and PostOfficeDaemon projects. Their literal
// is L"..\Shared\BnsCommonConfigDefinition.cpp" (pseudocode of LG and SCD).
#define BNS_COMMON_CONFIG_FILE_NAME L"..\\Shared\\BnsCommonConfigDefinition.cpp"
#include "BnsCommonConfigDefinition.cpp"
