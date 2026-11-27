// fsdshowcaserecord_gd.h: fsdshowcaserecord.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

bool __cdecl DecomposeShowcaseFsd(char const *, short, ::FsdShowcaseRecord &);  // 0xbcdc0
bool __cdecl ComposeShowcaseFsd(char *const, short *, ::FsdShowcaseRecord const &);  // 0xbd3e0
