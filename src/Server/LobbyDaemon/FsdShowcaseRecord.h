// FsdShowcaseRecord.obj (LobbyDaemon PDB, 2019 + PDB).
#pragma once

struct FsdShowcaseRecord
{
    static int const NAME_MAXLEN = 32;
    static int const TITLE_MAXLEN = 64;

    char race;
    char sex;
    char job;
    char appearance[92];
    wchar_t name[NAME_MAXLEN + 1];
    wchar_t title[TITLE_MAXLEN + 1];
    int geo_zone;
    short x;
    short y;
    short z;
    char level;
    int exp;
    int hp;
    short fp;
    __int64 money;
    int equip_hand;
    char equip_hand_level;
    int equip_hand_alt;
    int equip_body;
    char equip_body_custom1;
    char equip_body_custom2;
    char equip_body_custom3;
    char equip_body_custom4;
    char equip_body_custom5;
    char equip_body_custom6;
    char equip_body_custom7;
    char equip_body_custom8;
    int equip_ear;
    int equip_eye;
    char equip_eye_custom1;
    char equip_eye_custom2;
    char equip_eye_custom3;
    int equip_head;
    char equip_head_custom1;
    char equip_head_custom2;
    char equip_head_custom3;
    int equip_body_attach;
    char equip_body_attach_custom1;
    char equip_body_attach_custom2;
    char equip_body_attach_custom3;
    unsigned __int64 equip_body_guild_id;
    int equip_hand_appearance_item;
    char equip_hand_appearance_item_level;
    int equip_pet_1;
    int equip_pet_2;
    int equip_pet_1_appearance_item;
    int equip_pet_2_appearance_item;
    char masteryLevel;
    char daily_challenge_quest_count;
    char weekly_challenge_quest_count;
    char craft_union_1_type;
    short craft_union_1_exp;
    char craft_union_2_type;
    short craft_union_2_exp;
    char daily_challenge_reward_taken_count;
    char weekly_challenge_reward_taken_count;
    int equip_badge_gear_score;
    int equip_badge_appearance_item;
};
static_assert(sizeof(FsdShowcaseRecord) == 0x1B8, "sizeof FsdShowcaseRecord");

bool DecomposeShowcaseFsd(char const*, short, FsdShowcaseRecord&);  // 0x2e0b0
