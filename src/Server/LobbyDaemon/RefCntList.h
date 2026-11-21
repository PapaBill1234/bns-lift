// RefCntList.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from the PDB (RefCntListNode size 0x30, RefCntList size 0x18).
#pragma once
#include <stddef.h>
#include "RefCntObject.h"

class RefCntList;

class RefCntListNode : public DynamicRefCntObj
{
public:
    // LIFT: the PDB has 2 ctors. The binary has no out-of-line body for them. This ctor is the inline form.
    RefCntListNode() : _prev(nullptr), _next(nullptr), _list(nullptr) {}
    // LIFT: ~RefCntListNode has no body in the binary (lessons.md A18). The implicit virtual dtor is used.
    RefCntListNode* PrevNode() { return _prev; }
    RefCntListNode* NextNode() { return _next; }

private:
    RefCntListNode* _prev;  // +24
    RefCntListNode* _next;  // +32
    RefCntList* _list;      // +40

    // LIFT: not in the PDB. RefCntList writes the private links (RefCntList.cpp).
    friend class RefCntList;
};

class RefCntList
{
public:
    RefCntList();   // 0x64c80
    ~RefCntList();  // 0x64c90
    bool Pushback(RefCntListNode* node);  // 0x64d00
    bool Remove(RefCntListNode* node);    // 0x64da0
    RefCntListNode* Begin() { return _head; }
    int Size() { return _size; }

private:
    RefCntListNode* _head;  // +0
    RefCntListNode* _tail;  // +8
    int _size;              // +16
};
