// LobbyDaemon form of ObjectPool.h. Each LobbyDaemon file includes this header, not ObjectPool.h.
// LIFT: LobbyDaemon inlines the ObjPool ctor and dtor, and its GObjPoolMemAlloc is a LobbyObjPoolMemAllocator*.
#pragma once
#define LIFT_OBJPOOL_LOBBYDAEMON 1
#include "ObjectPool.h"
