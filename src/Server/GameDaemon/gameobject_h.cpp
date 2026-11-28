// gameobject_h.cpp: gameobject.h (GameDaemon PDB, 2019 + PDB).
#include "gameobject.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Make@GameObjectIdManager@@QEAA_K_K@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x1d080
__cdecl GameObject::~GameObject(void)
{
    // LIFT: Not done. The original calls the RelationalRefCntObject base destructor; the skeleton has no base.
    LIFT_STUB(0x1d080);
}

// 0x1d090
unsigned __int64 __cdecl GameObjectIdManager::Make(unsigned __int64 subIndex)
{
    int tryCount = 0;
    while (true)
    {
        Index = (Index + 1) % MaxIndex;
        if (Index != 0)
        {
            unsigned __int64 id = (Type << 48)
                + (Mask[1] & (subIndex << Bit[1]))
                + (Mask[0] & (static_cast<unsigned __int64>(Index) << Bit[0]));
            if (!IsExist(id))
                return id;
        }
        if (++tryCount > MaxIndex)
            return 0;
    }
}
