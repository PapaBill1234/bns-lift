// BloodLib include\StlMemory.h (CacheGate PDB): StlAllocator<T, N>.
// The allocator uses Memory::_Manager[N] (see 0x16BB0 std::vector<Timer*,StlAllocator<Timer*,2>>::reserve).
// It has the VS2010 allocator interface that include/vs2010 containers call.
#pragma once
#include <memory>
#include "Memory.h"

// LIFT: each exe has its own build path. A .cpp file can define LIFT_STLMEMORY_FILE before the first include.
// LIFT: per-exe form, all exes (inlined COMDAT copy of the first object keeps the path of its exe, TimerQueue::~TimerQueue).
#ifndef LIFT_STLMEMORY_FILE
#if defined(LIFT_EXE_LG)
#define LIFT_STLMEMORY_EXE L"lobbygate"
#elif defined(LIFT_EXE_SCD)
#define LIFT_STLMEMORY_EXE L"smartcoupondaemon"
#elif defined(LIFT_EXE_POD)
#define LIFT_STLMEMORY_EXE L"postofficedaemon"
#elif defined(LIFT_EXE_LD)
#define LIFT_STLMEMORY_EXE L"lobbydaemon"
#else
#define LIFT_STLMEMORY_EXE L"cachegate"
#endif
#define LIFT_STLMEMORY_FILE \
    L"e:\\dailybuild02\\" LIFT_STLMEMORY_EXE L"-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\StlMemory.h"
#endif

template<class T, int N>
class StlAllocator : public std::_Allocator_base<T>
{
public:
    typedef std::_Allocator_base<T> _Mybase;
    typedef typename _Mybase::value_type value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    template<class U>
    struct rebind
    {
        typedef StlAllocator<U, N> other;
    };

    StlAllocator() {}
    StlAllocator(const StlAllocator&) {}
    template<class U>
    StlAllocator(const StlAllocator<U, N>&) {}

    pointer allocate(size_type count)
    {
        return static_cast<pointer>(Memory::_Manager[N]->Alloc(count * sizeof(value_type), LIFT_STLMEMORY_FILE, 60));
    }
    void deallocate(pointer p, size_type)
    {
        Memory::_Manager[N]->Free(p, LIFT_STLMEMORY_FILE, 64);
    }

    template<class U>
    void construct(pointer p, U&& v) { ::new (static_cast<void*>(p)) value_type(std::forward<U>(v)); }
    void destroy(pointer p) { p->~value_type(); }

    size_type max_size() const
    {
        size_type n = (size_type)(-1) / sizeof(value_type);
        return 0 < n ? n : 1;
    }
};

template<class T, class U, int N>
inline bool operator==(const StlAllocator<T, N>&, const StlAllocator<U, N>&) { return true; }
template<class T, class U, int N>
inline bool operator!=(const StlAllocator<T, N>&, const StlAllocator<U, N>&) { return false; }
