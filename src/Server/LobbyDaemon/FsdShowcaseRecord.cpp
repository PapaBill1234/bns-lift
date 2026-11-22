// FsdShowcaseRecord.obj (LobbyDaemon PDB, 2019 + PDB).
#include "FsdShowcaseRecord.h"
#include "../../library/FsdReader/FsdDecomposer.h"

#if !defined(__clang__)
#pragma comment(linker, "/INCLUDE:?DecomposeShowcaseFsd@@YA_NPEBDFAEAUFsdShowcaseRecord@@@Z")  // LIFT: keep until the caller is lifted (0x2e0b0).
#endif

// 0x2e0b0
bool DecomposeShowcaseFsd(char const* fsd, short fsdSize, FsdShowcaseRecord& out)
{
    Fsd frame(const_cast<char*>(fsd), fsdSize);
    FsdDecomposer d;
    if (!d.Initialize(frame))
        return false;

    while (d.Decompose())
    {
        bool ok;
        int* field;
        switch (d.GetSymbol())
        {
        case 0x00: ok = d.GetByte(&out.race); break;
        case 0x01: ok = d.GetByte(&out.sex); break;
        case 0x02: ok = d.GetByte(&out.job); break;
        case 0x03:
        {
            int index = d.GetRepeat() - d._ptr.GetRepeat();
            ok = true;
            if (index >= 0 && index < static_cast<int>(sizeof(out.appearance)))
                ok = d.GetByte(&out.appearance[index]);
            break;
        }
        case 0x04: ok = d.GetString(out.name, FsdShowcaseRecord::NAME_MAXLEN + 1) == 0; break;
        case 0x05: ok = d.GetString(out.title, FsdShowcaseRecord::TITLE_MAXLEN + 1) == 0; break;
        case 0x06: field = &out.geo_zone; goto readDword;
        case 0x07: ok = d.GetWord(&out.x); break;
        case 0x08: ok = d.GetWord(&out.y); break;
        case 0x09: ok = d.GetWord(&out.z); break;
        case 0x0A: ok = d.GetByte(&out.level); break;
        case 0x0B: field = &out.exp; goto readDword;
        case 0x0C: field = &out.hp; goto readDword;
        case 0x0D: ok = d.GetWord(&out.fp); break;
        case 0x0E: ok = d.GetQword(&out.money); break;
        case 0x0F: field = &out.equip_hand; goto readDword;
        case 0x10: field = &out.equip_hand_alt; goto readDword;
        case 0x11: field = &out.equip_body; goto readDword;
        case 0x12: field = &out.equip_ear; goto readDword;
        case 0x13: field = &out.equip_eye; goto readDword;
        case 0x14: field = &out.equip_head; goto readDword;
        case 0x15: field = &out.equip_body_attach; goto readDword;
        case 0x16: ok = d.GetQword(reinterpret_cast<__int64*>(&out.equip_body_guild_id)); break;
        case 0x17: ok = d.GetByte(&out.equip_hand_level); break;
        case 0x18: field = &out.equip_hand_appearance_item; goto readDword;
        case 0x19: ok = d.GetByte(&out.equip_hand_appearance_item_level); break;
        case 0x1A: field = &out.equip_pet_1; goto readDword;
        case 0x1B: field = &out.equip_pet_2; goto readDword;
        case 0x1C: field = &out.equip_pet_1_appearance_item; goto readDword;
        case 0x1D: field = &out.equip_pet_2_appearance_item; goto readDword;
        case 0x1E: ok = d.GetByte(&out.equip_body_custom1); break;
        case 0x1F: ok = d.GetByte(&out.equip_body_custom2); break;
        case 0x20: ok = d.GetByte(&out.equip_body_custom3); break;
        case 0x21: ok = d.GetByte(&out.equip_body_custom4); break;
        case 0x22: ok = d.GetByte(&out.equip_body_custom5); break;
        case 0x23: ok = d.GetByte(&out.equip_body_custom6); break;
        case 0x24: ok = d.GetByte(&out.equip_body_custom7); break;
        case 0x25: ok = d.GetByte(&out.equip_body_custom8); break;
        case 0x26: ok = d.GetByte(&out.equip_eye_custom1); break;
        case 0x27: ok = d.GetByte(&out.equip_eye_custom2); break;
        case 0x28: ok = d.GetByte(&out.equip_eye_custom3); break;
        case 0x29: ok = d.GetByte(&out.equip_head_custom1); break;
        case 0x2A: ok = d.GetByte(&out.equip_head_custom2); break;
        case 0x2B: ok = d.GetByte(&out.equip_head_custom3); break;
        case 0x2C: ok = d.GetByte(&out.equip_body_attach_custom1); break;
        case 0x2D: ok = d.GetByte(&out.equip_body_attach_custom2); break;
        case 0x2E: ok = d.GetByte(&out.equip_body_attach_custom3); break;
        case 0x2F: ok = d.GetByte(&out.masteryLevel); break;
        case 0x30: ok = d.GetByte(&out.daily_challenge_quest_count); break;
        case 0x31: ok = d.GetByte(&out.weekly_challenge_quest_count); break;
        case 0x32: ok = d.GetByte(&out.craft_union_1_type); break;
        case 0x33: ok = d.GetWord(&out.craft_union_1_exp); break;
        case 0x34: ok = d.GetByte(&out.craft_union_2_type); break;
        case 0x35: ok = d.GetWord(&out.craft_union_2_exp); break;
        case 0x36: ok = d.GetByte(&out.daily_challenge_reward_taken_count); break;
        case 0x37: ok = d.GetByte(&out.weekly_challenge_reward_taken_count); break;
        case 0x38: field = &out.equip_badge_gear_score; goto readDword;
        case 0x39: field = &out.equip_badge_appearance_item;
        readDword:
            ok = d.GetDword(field);
            break;
        default:
            return false;
        }
        if (!ok)
            return false;
    }
    return true;
}
