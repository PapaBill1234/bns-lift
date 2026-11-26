// external\bannedwordfilter\src\STLMemory.h (LobbyDaemon PDB, 2019 + PDB).
// BannedWordFilterMemoryManager (field list 0x6FEC), BannedWordFilterMemory (field list 0x810C),
// BannedWordFilterAllocator<T> (size 1, no base).
// The allocator has the VS2010 allocator interface that the include/vs2010 containers call.
// ❓ The folder name src/External/BannedWordFilter is not verified. The PDB path is external\bannedwordfilter\src.
#pragma once
#include <memory>

// LIFT: A6. The path literal of the original build (rva 0x1e1c60). A .cpp file can define it before the first include.
#ifndef LIFT_BWF_STLMEMORY_FILE
#define LIFT_BWF_STLMEMORY_FILE \
    L"d:\\development\\sphawk_sphawk4_bl04\\program\\external\\bannedwordfilter\\src\\STLMemory.h"
#endif

// PDB: 3 public pure virtual functions (vftable offsets 0, 8, 16), sizeof 8.
class BannedWordFilterMemoryManager
{
public:
    virtual void* Alloc(unsigned long long size, wchar_t const* file, int line) = 0;
    virtual void* Realloc(void* p, unsigned long long size, wchar_t const* file, int line) = 0;
    virtual void Free(void* p, wchar_t const* file, int line) = 0;
};

// PDB: public static SetupMemoryManager and Memory, private static _memoryManager (rva 0x209898),
// private constructor and destructor.
class BannedWordFilterMemory
{
public:
    // LIFT: inline. LobbyDaemon::initialize (0x9b300) has the test and the store.
    static bool SetupMemoryManager(BannedWordFilterMemoryManager* const memoryManager)
    {
        if (_memoryManager != NULL)
            return false;
        _memoryManager = memoryManager;
        return true;
    }
    static BannedWordFilterMemoryManager* Memory() { return _memoryManager; }

private:
    BannedWordFilterMemory();
    ~BannedWordFilterMemory();

    static BannedWordFilterMemoryManager* _memoryManager;
};

template<class T>
class BannedWordFilterAllocator
{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    template<class U>
    struct rebind
    {
        typedef BannedWordFilterAllocator<U> other;
    };

    BannedWordFilterAllocator() {}
    BannedWordFilterAllocator(const BannedWordFilterAllocator&) {}
    template<class U>
    BannedWordFilterAllocator(const BannedWordFilterAllocator<U>&) {}

    pointer address(reference v) const { return &v; }
    const_pointer address(const_reference v) const { return &v; }

    pointer allocate(size_type count)
    {
        return static_cast<pointer>(BannedWordFilterMemory::Memory()->Alloc(count * sizeof(value_type), LIFT_BWF_STLMEMORY_FILE, 46));
    }
    void deallocate(pointer p, size_type)
    {
        BannedWordFilterMemory::Memory()->Free(p, LIFT_BWF_STLMEMORY_FILE, 49);
    }

    void construct(pointer p, const value_type& v) { ::new (static_cast<void*>(p)) value_type(v); }
    template<class U>
    void construct(pointer p, U&& v) { ::new (static_cast<void*>(p)) value_type(std::forward<U>(v)); }
    void destroy(pointer p) { p->~value_type(); }

    size_type max_size() const
    {
        size_type n = (size_type)(-1) / sizeof(value_type);
        return 0 < n ? n : 1;
    }
};

template<class T, class U>
inline bool operator==(const BannedWordFilterAllocator<T>&, const BannedWordFilterAllocator<U>&) { return true; }
template<class T, class U>
inline bool operator!=(const BannedWordFilterAllocator<T>&, const BannedWordFilterAllocator<U>&) { return false; }
