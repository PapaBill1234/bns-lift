// Job parameter structs (LobbyDaemon PDB, 2019 + PDB). Filled by LobbyGamePacketHandler.cpp (0x8a560, 0x8a7c0, 0x8ad30).
// LIFT: the PDB has these as public structs without a home header. This header holds the layouts that lift-lobbydaemon-16 needs.
#pragma once
#include <stddef.h>

struct WorldKickFailParam
{
    short reason;
};
static_assert(sizeof(WorldKickFailParam) == 0x2, "sizeof WorldKickFailParam");
static_assert(offsetof(WorldKickFailParam, reason) == 0x0, "WorldKickFailParam::reason");

struct CreateCharacterOkParam
{
    short job;
    short level;
    char showcaseData[512];
    short showcaseDataSize;
};
static_assert(sizeof(CreateCharacterOkParam) == 0x206, "sizeof CreateCharacterOkParam");
static_assert(offsetof(CreateCharacterOkParam, job) == 0x0, "CreateCharacterOkParam::job");
static_assert(offsetof(CreateCharacterOkParam, level) == 0x2, "CreateCharacterOkParam::level");
static_assert(offsetof(CreateCharacterOkParam, showcaseData) == 0x4, "CreateCharacterOkParam::showcaseData");
static_assert(offsetof(CreateCharacterOkParam, showcaseDataSize) == 0x204, "CreateCharacterOkParam::showcaseDataSize");

struct DeleteCharacterOkParam
{
    short level;
};
static_assert(sizeof(DeleteCharacterOkParam) == 0x2, "sizeof DeleteCharacterOkParam");
static_assert(offsetof(DeleteCharacterOkParam, level) == 0x0, "DeleteCharacterOkParam::level");
