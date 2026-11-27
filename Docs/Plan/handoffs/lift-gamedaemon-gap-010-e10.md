# Handoff: lift-gamedaemon-gap-010-e10 (round 1)

## Lifted

None. I changed no source file.

## Why nothing is lifted

Every function in scope reads a member of `DuelBot`.
The members are `_skillResultContext` (+0x1880) and `_abilityData` (+0x1868).
The repo header `src/Server/GameDaemon/duelbot.h` declares `DuelBot` with no base and no members.
The skeleton note in that header says: "Later waves add the PDB layouts."
`DuelBot` derives from `DuelBotCreature`. Its size is 0x1938.
A lift needs the full base chain and the member layout first.
That layout work is larger than this card and is outside its file list.

A second fact blocks the 25 `Modify` getters.
The pseudocode reads `_abilityData._record[N].type/subtype/size`.
`Data::DuelBotAbilityRecordPtr` is only a `DrRecordPtr` wrapper (8 bytes).
The real record field names are not clear from one look-up.

## Not done (all 40 functions; the reason is the missing layout above)

| RVA | Function |
| --- | --- |
| 0x97270 | DuelBot::GetLastComboSkill |
| 0x97280 | DuelBot::SetLastComboSkill |
| 0x97290 | DuelBot::GetLastComboFireLimitTime |
| 0x972a0 | DuelBot::SetLastComboFireLimitTime |
| 0x972b0 | DuelBot::GetLastComboExecFirstLimitTime |
| 0x972c0 | DuelBot::SetLastComboExecFirstLimitTime |
| 0x972d0 | DuelBot::GetLastComboExecLastLimitTime |
| 0x972e0 | DuelBot::SetLastComboExecLastLimitTime |
| 0x972f0 | DuelBot::GetLastComboExecFirstResult |
| 0x97300 | DuelBot::SetLastComboExecFirstResult |
| 0x97310 | DuelBot::GetLastComboExecLastResult |
| 0x97320 | DuelBot::SetLastComboExecLastResult |
| 0x97330 | DuelBot::GetLastAttackLimitTime |
| 0x97340 | DuelBot::SetLastAttackLimitTime |
| 0x97350 | DuelBot::GetLastAttackedLimitTime |
| 0x97360 | DuelBot::SetLastAttackedLimitTime |
| 0x97370 - 0x974e0 | DuelBot::Get*Modify (24 getters, step 0x10) |

## Next step

Add the `DuelBot` and `DuelBotCreature` layouts (from `include/pdb/GameDaemon/types.h`, line 89365) to `duelbot.h` in a layout card.
Then lift this card.

## Files changed

- `Docs/Plan/handoffs/lift-gamedaemon-gap-010-e10.md` only.
