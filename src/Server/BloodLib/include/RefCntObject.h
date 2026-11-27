// RefCntObject.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>
#include "MemoryManager.h"

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
    // LIFT: SessionSendBuffer::clearPacketBufferList has the removeReferenceCount body by hand (CacheGate 0x1a980).
    friend class SessionSendBuffer;
};
static_assert(sizeof(RefCntHistory) == 0x18, "sizeof RefCntHistory");
static_assert(offsetof(RefCntHistory, _history) == 0x10, "RefCntHistory::_history");

class RefCntObject
{
public:
    // Inlined in Session::Session (0xdee0) and Port::Port: _ref = 1, _tag = 10, _history = nullptr.
    RefCntObject()
    {
        // LIFT: body stores, as in ReleaseEvent (DelayedRelease.cpp). The originals store _ref before _tag
        // (LG 0x12bf0, SCD DelayedRelease).
        _ref = 1;
        _tag = 10;
        _history = nullptr;
    }
    virtual ~RefCntObject();                                                   // slot 0
private:
    virtual void deallocate_object(wchar_t const* file, int line);             // slot 1
    virtual void deallocate_me(void* ptr, wchar_t const* file, int line) = 0;  // slot 2
public:
    virtual void DumpRefCntHistory();                                          // slot 3

    static void operator delete(void* ptr, wchar_t const* file, int line);
    // LIFT: Not in the PDB. The placement form above hides the global form. The virtual
    // destructor needs a usual form for clang-cl.
    static void operator delete(void* ptr) { ::operator delete(ptr); }
    // PDB signature (all 6 server PDBs, CacheGate 0x2150): addReferenceCount(bool ignoreHistory,
    // wchar_t const* file, int line). LTCG removes ignoreHistory: it has PDB offset 0, and file is in rdx
    // (offset 104). The body (HR LobbyDaemon 0xb9e0) adds history whenever _history is set.
    // ❓ No call site in the originals passes the bool (rdx = file at each site). Each lift call site passes false.
    // false keeps the original behavior: history is added.
    long addReferenceCount(bool ignoreHistory, wchar_t const* file, int line);
    long removeReferenceCount(wchar_t const* file, int line);

    long _tag;
    long _ref;  // PDB: plain long (0x0012), not volatile. A volatile store blocks the dead-store removal of the base vptr store.
    RefCntHistory* _history;

    // LIFT: SessionSendBuffer::clearPacketBufferList has the removeReferenceCount body by hand (CacheGate 0x1a980).
    friend class SessionSendBuffer;
};
static_assert(sizeof(RefCntObject) == 0x18, "sizeof RefCntObject");
static_assert(offsetof(RefCntObject, _tag) == 0x8, "RefCntObject::_tag");
static_assert(offsetof(RefCntObject, _ref) == 0xC, "RefCntObject::_ref");
static_assert(offsetof(RefCntObject, _history) == 0x10, "RefCntObject::_history");

class BaseRefCntObj : public RefCntObject
{
public:
    virtual ~BaseRefCntObj();
    // PDB: public static operator new(unsigned __int64, wchar_t const*, int); inlined (no rva).
    // The matching delete is RefCntObject::operator delete(void*, wchar_t const*, int): the EH cleanup
    // `Port::Initialize'::`1'::dtor$0 (CacheGate 0x3a920) calls it when the constructor throws.
    // LIFT: throw() gives the null test after the call, as in the original Port::Initialize.
    static void* operator new(size_t size, wchar_t const* file, int line) throw()
    {
        return BASE_MEMORY_MANAGER.Alloc(size, file, line);
    }
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
