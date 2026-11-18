// LIFT: Build wrapper, no PDB module. The LobbyGate project builds RefCntObject.cpp with its own
// __FILE__ path for include\RefCntObject.h (pseudocode of LobbyGate).
#define REFCNT_HEADER \
    L"e:\\dailybuild02\\lobbygate-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\RefCntObject.h"
#include "RefCntObject.cpp"
