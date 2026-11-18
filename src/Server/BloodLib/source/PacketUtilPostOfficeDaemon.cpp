// LIFT: Build wrapper, no PDB module. The PostOfficeDaemon project builds PacketUtil.cpp with its own
// path for include\PacketUtil.h (pseudocode of PostOfficeDaemon).
#define LIFT_PACKETUTIL_H_PATH \
    "e:\\dailybuild02\\postofficedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\PacketUtil.h"
#include "PacketUtil.cpp"
