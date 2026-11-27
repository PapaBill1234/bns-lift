# Handoff: lift-gamedaemon-gap-002-e2

## Lifted (33 getters)

- ClientOption: TypeId (14), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- CollectingProperty: TypeId (36), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- ContentQuotaProperty: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- CostumeProperty: Version (29), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- DiscoveryArea: TypeId (12), Name, FieldMax, FieldDefine, SyncMax, SyncDefine.
- EffectProperty: Name, FieldMax, FieldDefine, SyncMax, SyncDefine.

The static members fieldMax, fieldDefine, syncMax and syncDefine follow the pilot form of ActivatedTeleport.
Each function has a `/INCLUDE` pragma with a `// LIFT:` note (no live caller yet).

## Open questions

- CostumeProperty::Version: the old stub used the folded name RaidDungeonBindProperty::TypeId. The PDB name is CostumeProperty::Version. I declared it virtual (`int Version() const`). The mangled name in the `/INCLUDE` pragma (`?Version@CostumeProperty@@UEBAHXZ`) is not checked against the publics. If the link fails, check this name first.
- The 6 ActivatedTeleport functions of the card list were already lifted in the base. I did not change them.

## Not done

None. The driver runs the build and the proof. I did not run them.

## Changed files

- src/Server/GameDaemon/{clientoption_h,collectingproperty,contentquotaproperty,costumeproperty,discoveryarea,effectproperty_h}.cpp
- src/Server/GameDaemon/{clientoption,collectingproperty,contentquotaproperty,costumeproperty,discoveryarea,effectproperty}.h
- Docs/Plan/handoffs/lift-gamedaemon-gap-002-e2.md
