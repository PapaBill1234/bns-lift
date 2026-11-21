// BoundedList.obj (LobbyDaemon PDB, 2019 + PDB). Layout from the PDB (BoundedList, size 0x18).
// LIFT: the ctors, the dtor, Clear and the accessors have no body in the binary. They are inline in WaitQueue.
// Only the inline forms that the lifted code uses are declared here.
#pragma once
#include "Memory.h"
#include "MemoryManager.h"

class BoundedList
{
public:
    struct Node
    {
        void* data;  // +0
        short prev;  // +8
        short next;  // +10
        bool pool;   // +12
    };
    typedef short NodePtr;

    static short const _NIL = -1;

    // LIFT: inline (WaitQueue::WaitQueue 0xdc540). The PDB has 2 ctors.
    BoundedList()
    {
        _head = _NIL;
        _tail = _NIL;
        _pool = _NIL;
        _capacity = 0;
        _size = 0;
        _list = nullptr;
    }
    // LIFT: inline (WaitQueue::~WaitQueue 0xdc590). The literal is "BoundedList.cpp", line 38.
    ~BoundedList()
    {
        if (_list != nullptr)
        {
            Memory::_Manager[2]->Free(_list, L"BoundedList.cpp", 38);
            _list = nullptr;
        }
    }

    bool Init(int capacity);       // 0x18540
    short Pushback(void* data);    // 0x18650
    void* Popfront();              // 0x186f0
    bool Remove(short node);       // 0x18790

    // LIFT: inline accessors (WaitQueue::Remove 0xdc720, WaitQueue::QueryTurn 0xdc870).
    short Head() const { return _head; }
    short Next(short node) const
    {
        if (node >= 0 && node < _capacity)
            return _list[node].next;
        return _NIL;
    }
    Node const* GetNode(short node) const
    {
        if (node < 0 || node >= _capacity || _list[node].pool)
            return nullptr;
        return &_list[node];
    }
    bool Empty() const { return _size == 0; }
    int Size() const { return _size; }
    int Capacity() const { return _capacity; }

private:
    void push_pool(short node);
    short pop_pool();

    int _capacity;  // +0
    int _size;      // +4
    short _head;    // +8
    short _tail;    // +10
    short _pool;    // +12
    Node* _list;    // +16
};
