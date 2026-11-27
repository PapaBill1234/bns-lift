# lift-gamedaemon-gap-028-e28 handoff

## effectcontent_cpp_1

Lifted:

- `HpDamageEffect::checkApply` (0x5b8250)
- `InitializeRecycleGroupEffect::checkApply` (0x5bca00)
- `AdditionalHpEffect::checkApply` (0x5bf3e0)
- `DesireIncreaseEffect::checkApply` (0x5bf4d0)
- `DifficultyTypeDispelAttributeHpDamageEffect::checkApply` (0x5bf850)
- `ReturnSimSkillEffect::checkApply` (0x5c5de0)
- `ModifyRecycleTimeEffect::checkApply` (0x5c6200)
- `SetImmuneBreakerEffect::checkApply` (0x5c65d0)

The effect classes of the skeleton have no `Effect` base. The bodies read `target` and `casterId` through a local view of `Effect`. Each body has a dead-strip keep pragma.

**Not done:**

- `AttackPassiveEffect::checkApply` (0x5b76f0): it reads a 64-bit flag field at Creature+0x1D0. The PDB name of that field is not known.
- `ExtendLinkEffect::checkApply` (0x5be900): same field at Creature+0x1D0.
- `ProvocationEffect::checkApply` (0x5c4bb0): same field at Creature+0x1D0.
- `GuardGaugeHealEffect::checkApply` (0x5b8590): it reads fields of a derived effect record after `Data::EffectRecord`. The record type is not known.
- `GuardGaugeDamageEffect::checkApply` (0x5b86f0): same cause.
- `CastCancelEffect::apply` (0x5b8ab0): it calls a virtual function through a member at Creature+0x8A0. The member and the slot are not known.
- `ReturnSimSkillEffect::apply` (0x5c5e00): same member at Creature+0x8A0, and a derived effect record.
- `TransitEffect::TransitEffect` (0x5c5530): the skeleton has no `InstantEffect` base and no `TransitEffect` members.
