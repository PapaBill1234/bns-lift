// RefCntObject.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>

class RefCntObject;

class RefCntHistoryItem
{
public:
    long long _time;
    wchar_t const* _file;
    int _line;
    unsigned long _threadId;
    long _seq;
    short _ref;
    char _op;
};
static_assert(sizeof(RefCntHistoryItem) == 0x20, "sizeof RefCntHistoryItem");
static_assert(offsetof(RefCntHistoryItem, _op) == 0x1E, "RefCntHistoryItem::_op");

class RefCntHistory
{
public:
    enum Operation
    {
        OP_NONE = 0,
        OP_ADDREF = 1,
        OP_DELREF = 2,
    };

private:
    bool add(long ref, wchar_t const* file, int line, Operation op);
    void dump(RefCntObject* ptr);

public:
    long volatile _dumped;
    long volatile _historyPos;
    long _historyMax;
    RefCntHistoryItem* _history;

    friend class RefCntObject;
};
static_assert(sizeof(RefCntHistory) == 0x18, "sizeof RefCntHistory");
static_assert(offsetof(RefCntHistory, _history) == 0x10, "RefCntHistory::_history");

class RefCntObject
{
public:
    // Inlined in Session::Session (0xdee0) and Port::Port: _ref = 1, _tag = 10, _history = nullptr.
    RefCntObject() : _tag(10), _ref(1), _history(nullptr) {}
    virtual ~RefCntObject();                                                   // slot 0
private:
    virtual void deallocate_object(wchar_t const* file, int line);             // slot 1
    virtual void deallocate_me(void* ptr, wchar_t const* file, int line) = 0;  // slot 2
public:
    virtual void DumpRefCntHistory();                                          // slot 3

    static void operator delete(void* ptr, wchar_t const* file, int line);
    // ❓ Not in the PDB. The placement form above hides the global form. The virtual
    // destructor needs a usual form (MSVC does not require it).
    static void operator delete(void* ptr) { ::operator delete(ptr); }
    // ❓ The PDB name is addReferenceCount(bool,wchar_t const *,int). The code at 0x2150
    // reads arg 1 as the file and arg 2 as the line. Callers give (file, line).
    long addReferenceCount(wchar_t const* file, int line);
    long removeReferenceCount(wchar_t const* file, int line);

    long _tag;
    long volatile _ref;
    RefCntHistory* _history;
};
static_assert(sizeof(RefCntObject) == 0x18, "sizeof RefCntObject");
static_assert(offsetof(RefCntObject, _tag) == 0x8, "RefCntObject::_tag");
static_assert(offsetof(RefCntObject, _ref) == 0xC, "RefCntObject::_ref");
static_assert(offsetof(RefCntObject, _history) == 0x10, "RefCntObject::_history");

class BaseRefCntObj : public RefCntObject
{
public:
    virtual ~BaseRefCntObj();
protected:
    virtual void deallocate_me(void* ptr, wchar_t const* file, int line);
};
static_assert(sizeof(BaseRefCntObj) == 0x18, "sizeof BaseRefCntObj");

class DynamicRefCntObj : public RefCntObject
{
public:
    virtual ~DynamicRefCntObj();
private:
    virtual void deallocate_me(void* ptr, wchar_t const* file, int line);
};
static_assert(sizeof(DynamicRefCntObj) == 0x18, "sizeof DynamicRefCntObj");
