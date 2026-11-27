// worldserializedobject_h.cpp: worldserializedobject.h (GameDaemon PDB, 2019 + PDB). childRoleAllocator lifted (card lift-gamedaemon-gap-006-e6).
#include "worldserializedobject.h"
#include "gameobject.h"
#include "LiftStub.h"
#include "Memory.h"
#include "MemoryManager.h"

// 0x1d070
::MemoryManager * __cdecl GameObject::childRoleAllocator(void)
{
    return const_cast< ::MemoryManager * >(Memory::_Manager[2]);
}

// 0x8c240
bool __cdecl WorldSerializedObject::SetTimer(long)
{
    LIFT_STUB(0x8c240);
}
