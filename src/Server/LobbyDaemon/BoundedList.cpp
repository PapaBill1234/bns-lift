// BoundedList.obj (LobbyDaemon PDB, 2019 + PDB). Source file: "BoundedList.cpp".
#include "BoundedList.h"

#include "Memory.h"
#include "MemoryManager.h"

// LIFT: inlined private helper (no body in the binary). It gives the node back to the pool.
__forceinline void BoundedList::push_pool(short node)
{
    _list[node].data = nullptr;
    _list[node].prev = _NIL;
    _list[node].next = _pool;
    _list[node].pool = true;
    --_size;
    _pool = node;
}

// LIFT: inlined private helper (no body in the binary). It takes a node from the pool.
__forceinline short BoundedList::pop_pool()
{
    short node = _pool;
    if (node == _NIL)
        return _NIL;
    _pool = _list[node].next;
    _list[node].next = _NIL;
    return node;
}

// 0x18540
bool BoundedList::Init(int capacity)
{
    if (_list != nullptr)
    {
        Memory::_Manager[2]->Free(_list, L"BoundedList.cpp", 47);
        _list = nullptr;
    }

    _capacity = capacity;
    _size = 0;
    _head = _NIL;
    _tail = _NIL;
    _pool = _NIL;

    if (capacity > 0)
    {
        _list = static_cast<Node*>(Memory::_Manager[2]->AllocZero(sizeof(Node) * capacity, L"BoundedList.cpp", 56));
        for (short i = 0; i < capacity; ++i)
        {
            _list[i].prev = _NIL;
            _list[i].next = i + 1;
            _list[i].pool = true;
        }
        _list[capacity - 1].next = _NIL;
        _pool = 0;
    }
    return true;
}

// 0x18650
short BoundedList::Pushback(void* data)
{
    short node = pop_pool();
    if (node == _NIL)
        return _NIL;

    _list[node].pool = false;
    _list[node].data = data;
    if (_head == _NIL)
    {
        _head = node;
    }
    else
    {
        _list[_tail].next = node;
        _list[node].prev = _tail;
    }
    ++_size;
    _tail = node;
    return node;
}

// 0x186f0
void* BoundedList::Popfront()
{
    short node = _head;
    if (node == _NIL)
        return nullptr;

    if (node == _tail)
    {
        _tail = _NIL;
        _head = _NIL;
    }
    else
    {
        _list[_list[node].next].prev = _NIL;
        _head = _list[_head].next;
    }

    void* data = _list[node].data;
    push_pool(node);
    return data;
}

// 0x18790
bool BoundedList::Remove(short node)
{
    if (node < 0 || node >= _capacity)
        return false;
    if (_list[node].pool)
        return false;

    if (_list[node].prev != _NIL)
        _list[_list[node].prev].next = _list[node].next;
    if (_list[node].next != _NIL)
        _list[_list[node].next].prev = _list[node].prev;
    if (_head == node)
        _head = _list[_head].next;
    if (_tail == node)
        _tail = _list[_tail].prev;

    push_pool(node);
    return true;
}
