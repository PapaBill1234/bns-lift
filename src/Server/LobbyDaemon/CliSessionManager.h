// CliSessionManager.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "CliSessionTable.h"

// Layout: include/pdb/LobbyDaemon/types.h (sizeof 0x80). The PDB base is CliSessionTable.
class CliSessionManager : public CliSessionTable
{
public:
    void OnCloseLobbyGateChannel(short);  // 0x3cbd0
    void OnCloseGamedChannel(short);  // 0x3cdd0
};
static_assert(sizeof(CliSessionManager) == 0x80, "sizeof CliSessionManager");
