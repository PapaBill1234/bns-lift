// LIFT: Build wrapper, no PDB module. The PostOfficeDaemon project builds MemoryManager.cpp with its own
// __FILE__ path for include\MemoryManager.h (pseudocode of PostOfficeDaemon).
#define LIFT_MEMORYMANAGER_H_FILE \
    L"E:\\DailyBuild02\\PostOfficeDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\MemoryManager.h"
#define LIFT_MEMORY_H_FILE \
    L"e:\\dailybuild02\\postofficedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Memory.h"
#include "MemoryManager.cpp"
