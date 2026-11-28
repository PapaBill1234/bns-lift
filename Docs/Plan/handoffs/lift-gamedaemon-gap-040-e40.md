# Handoff: lift-gamedaemon-gap-040-e40 (card lift-gamedaemon-e40)

The skeleton classes have no PDB members and no bases. The lifted bodies use local `...View` structs (PDB offsets) for member access.

## Lifted

- `CombatSequence::finishSpecial` (0x4080b0). It calls `Zone::GetTickTime`. That callee is still a `LIFT_STUB`, so the body can stay DIFF until a later card lifts it.
- `CombatSequence::registerLastAction` (0x408970).
- `FieldItemIdManager::IsExist` (0x5a06b0). `FieldItemList::Get` and `FieldItemList::find` are now PDB inline members in `fielditem.h`.
- `FieldItem::GetRemainedDecomposition` (0x5a0a90).
- `FieldItem::GetRemainedExplosion` (0x5a0af0).
- `BrainCitizen::GetState` (0x402a80).

## Not done

- `BossCombatSequence::~BossCombatSequence` (0x630d0): the original stores the `CombatSequence` vftable. The skeleton has no `CombatSequence` base class.
- `isSufficentHpCondition` (0x4059c0): `HP_PERCENT_COND_TABLE` is not declared and its values are not known. The function is static and has no public, so a keep pragma is not possible.
- `CombatSequence::checkSpecialFired` (0x407c80): the pseudocode cache has no body (`None`).
- `SerializedObject::~SerializedObject` (0x663090): the original calls the `RelationalRefCntObject` and `RefCntObject` base destructors. The skeleton has no base class.
