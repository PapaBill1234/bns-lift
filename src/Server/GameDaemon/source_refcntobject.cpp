// source_refcntobject.cpp: refcntobject.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "refcntobject_gd.h"
#include <stddef.h>
#include "LiftStub.h"

// 0x6934a0
void __cdecl RelationalRefCntObject::initRole(void)
{
    LIFT_STUB(0x6934a0);
}

// 0x6935c0
void __cdecl RelationalRefCntObject::clearRole(void)
{
    LIFT_STUB(0x6935c0);
}

// 0x693640
void __cdecl RelationalRefCntObject::AddChild(::RelationalRefCntObject *, wchar_t const *, int)
{
    LIFT_STUB(0x693640);
}

// 0x693800
void __cdecl RelationalRefCntObject::removeChild(::RelationalRefCntObject *, wchar_t const *, int)
{
    LIFT_STUB(0x693800);
}

// 0x6939a0
void __cdecl RelationalRefCntObject::removeParent(wchar_t const *, int)
{
    LIFT_STUB(0x6939a0);
}

#pragma comment(linker, "/INCLUDE:?remove_child@RelationalRefCntObject@@AEAAXPEAV1@PEB_WH@Z")  // LIFT: dead-strip keep (no live caller yet)

// LIFT: partial views of the PDB layouts. RelationalRefCntObject has no members in the header yet.
// PDB: RelationalRefCntObject::ChildRole, size 0x18.
struct RelationalRefCntObjectChildRoleView
{
    RelationalRefCntObject *_prev;    // +0
    RelationalRefCntObject *_next;    // +8
    RelationalRefCntObject *_parent;  // +16
};
// PDB: RelationalRefCntObject::ParentRole, size 0x30 (_lock +0, _objects +40).
struct RelationalRefCntObjectParentRoleView
{
    char _lock[0x28];
    RelationalRefCntObject *_objects;  // +40
};
// PDB: RelationalRefCntObject, size 0x28: base RefCntObject +0 (size 0x18), _parentRole +0x18, _childRole +0x20.
struct RelationalRefCntObjectView
{
    char base[0x18];
    RelationalRefCntObjectParentRoleView *_parentRole;
    RelationalRefCntObjectChildRoleView *_childRole;
};
static_assert(offsetof(RelationalRefCntObjectView, _parentRole) == 0x18, "RelationalRefCntObject::_parentRole");
static_assert(offsetof(RelationalRefCntObjectView, _childRole) == 0x20, "RelationalRefCntObject::_childRole");

// 0x693a60
void __cdecl RelationalRefCntObject::remove_child(::RelationalRefCntObject *child, wchar_t const *, int)
{
    RelationalRefCntObjectView *self = reinterpret_cast<RelationalRefCntObjectView *>(this);
    RelationalRefCntObjectView *childView = reinterpret_cast<RelationalRefCntObjectView *>(child);

    RelationalRefCntObjectParentRoleView *parentRole = self->_parentRole;
    if (parentRole->_objects == child)
        self->_parentRole->_objects =
            reinterpret_cast<RelationalRefCntObjectView *>(parentRole->_objects)->_childRole->_next;
    RelationalRefCntObjectChildRoleView *childRole = childView->_childRole;
    if (childRole->_prev != nullptr)
        reinterpret_cast<RelationalRefCntObjectView *>(childRole->_prev)->_childRole->_next = childRole->_next;
    RelationalRefCntObjectChildRoleView *role = childView->_childRole;
    if (role->_next != nullptr)
        reinterpret_cast<RelationalRefCntObjectView *>(role->_next)->_childRole->_prev = role->_prev;
    childView->_childRole->_prev = nullptr;
    childView->_childRole->_next = nullptr;
    childView->_childRole->_parent = nullptr;
}

// 0x693ae0
void __cdecl RelationalRefCntObject::deallocate_object(wchar_t const *, int)
{
    LIFT_STUB(0x693ae0);
}
