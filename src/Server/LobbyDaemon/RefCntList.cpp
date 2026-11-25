// RefCntList.obj (LobbyDaemon PDB, 2019 + PDB). Lift from the Hex-Rays pseudocode of LobbyDaemon.exe.
#include "RefCntList.h"
#include "Log.h"
#include "AlertSender.h"

// 0x64c80
RefCntList::RefCntList()
{
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}

// 0x64c90
// LIFT: the loop body is an inline Popfront (PDB: RefCntList::Popfront, no body in the binary).
RefCntList::~RefCntList()
{
    RefCntListNode* head;
    while ((head = _head) != nullptr)
    {
        if (head == _tail)
        {
            _tail = nullptr;
            _head = nullptr;
        }
        else
        {
            head->_next->_prev = nullptr;
            _head = _head->_next;
        }
        head->_next = nullptr;
        head->_prev = nullptr;
        head->_list = nullptr;
        --_size;
        head->removeReferenceCount(L"RefCntList.cpp", 21);
    }
}

// 0x64d00
bool RefCntList::Pushback(RefCntListNode* node)
{
    if (node->_list != nullptr)
    {
        Log::Write(Log::LT_ERROR, L"RefCntList.cpp", 30, L"== CRASH == [refcnt-list], pushback fail; already pushed");
        AlertSender::Write(L"RefCntList.cpp", 30, L"== CRASH == [refcnt-list], pushback fail; already pushed");
        return false;
    }
    node->_list = this;
    node->_next = nullptr;
    node->_prev = nullptr;
    if (_tail != nullptr)
    {
        _tail->_next = node;
        node->_prev = _tail;
    }
    else
    {
        _head = node;
    }
    ++_size;
    _tail = node;
    node->addReferenceCount(false, L"RefCntList.cpp", 50);
    return true;
}

// 0x64da0
bool RefCntList::Remove(RefCntListNode* node)
{
    if (node == nullptr)
        return false;
    if (node->_list == nullptr)
        return false;
    if (node->_list != this)
    {
        Log::Write(Log::LT_ERROR, L"RefCntList.cpp", 64, L"[refcnt-list], remove fail; not exists");
        return false;
    }
    if (node->_prev != nullptr)
        node->_prev->_next = node->_next;
    if (node->_next != nullptr)
        node->_next->_prev = node->_prev;
    if (_head == node)
        _head = node->_next;
    if (_tail == node)
        _tail = node->_prev;
    node->_next = nullptr;
    node->_prev = nullptr;
    node->_list = nullptr;
    --_size;
    node->removeReferenceCount(L"RefCntList.cpp", 82);
    return true;
}
