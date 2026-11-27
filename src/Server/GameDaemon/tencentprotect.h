// tencentprotect.h: tencentprotect.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class TpDPSecurity
{
public:
    virtual ::Security3rdParty::ErrCode __cdecl Encrypt(unsigned char *, int *, bool *);  // 0x21ea80
    virtual ::Security3rdParty::ErrCode __cdecl Decrypt(unsigned char *, int *, bool);  // 0x21eb00
};

