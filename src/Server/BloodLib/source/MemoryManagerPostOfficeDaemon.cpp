// LIFT: Build wrapper, no PDB module. The PostOfficeDaemon project builds MemoryManager.cpp with its own
// __FILE__ path for include\MemoryManager.h (pseudocode of PostOfficeDaemon).
#define LIFT_MEMORYMANAGER_H_FILE \
    L"E:\\DailyBuild02\\PostOfficeDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\MemoryManager.h"
#include "MemoryManager.cpp"
