// tencentprotect.cpp: tencentprotect.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "tencentprotect.h"
#include "LiftStub.h"

// 0x21ea80
// LIFT: feature off (owner scope)
::Security3rdParty::ErrCode __cdecl TpDPSecurity::Encrypt(unsigned char *, int *, bool *)
{
    return static_cast<::Security3rdParty::ErrCode>(0);
}

// 0x21eb00
// LIFT: feature off (owner scope)
::Security3rdParty::ErrCode __cdecl TpDPSecurity::Decrypt(unsigned char *, int *, bool)
{
    return static_cast<::Security3rdParty::ErrCode>(0);
}
