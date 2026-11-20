// LobbyPredefine.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

union id128;

char GetLobbyGateKickReason(int);  // 0x96480
char GetGameWorldKickReason(int);  // 0x96500
bool GetId128FromGuidString(wchar_t const*, id128*);  // 0x96580
bool CreateNewId128(id128*);  // 0x966a0
