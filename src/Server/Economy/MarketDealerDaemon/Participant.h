// Participant.h (MarketDealerDaemon PDB). No code in the PDB. Layout from include/pdb/MarketDealerDaemon/types.h.
#pragma once
#include <stddef.h>
#include "StringUtil.h"  // id128

class Participant
{
public:
    short _participantWid;
    long long _participantPcId;
    id128 _participantAccountId;
    wchar_t _participantWorldName[33];
    wchar_t _participantName[33];
};
static_assert(sizeof(Participant) == 0xA8, "sizeof Participant");
static_assert(offsetof(Participant, _participantAccountId) == 0x10, "Participant::_participantAccountId");
static_assert(offsetof(Participant, _participantName) == 0x62, "Participant::_participantName");
