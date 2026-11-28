// drstlmemory.h: datareader/src/stlmemory.h (GameDaemon PDB, 2019 + PDB). STL allocator on DrMemoryManager.
// LIFT: the file name differs from the original (stlmemory.h) because the BloodLib StlMemory.h has the same name.
#pragma once
#include "GameDaemonFwd.h"
#include "defmemory.h"
#include <cstddef>
#include <new>

// LIFT: per-exe path literal of the 2019 build (lessons A6).
#define DR_STLMEMORY_FILE L"e:\\dailybuild02\\platformbinary-common-0.0.346\\depot\\branch\\346nc\\program\\library\\datareader\\src\\StlMemory.h"

template <class T0, int T1>
class DrStlAllocator
{
public:
    typedef T0 value_type;
    typedef T0 * pointer;
    typedef T0 & reference;
    typedef T0 const * const_pointer;
    typedef T0 const & const_reference;
    typedef unsigned __int64 size_type;
    typedef __int64 difference_type;

    template <class U>
    struct rebind
    {
        typedef DrStlAllocator<U, T1> other;
    };

    DrStlAllocator() {}
    DrStlAllocator(DrStlAllocator const &) {}
    template <class U>
    DrStlAllocator(DrStlAllocator<U, T1> const &) {}
    template <class U>
    DrStlAllocator & operator=(DrStlAllocator<U, T1> const &) { return *this; }

    pointer address(reference _Val) const { return &_Val; }
    const_pointer address(const_reference _Val) const { return &_Val; }

    pointer allocate(size_type _Count)
    {
        return static_cast<pointer>(DrMemoryManager::Memory(static_cast<DrMemoryManager::Section>(T1))->Alloc(_Count * sizeof(T0), DR_STLMEMORY_FILE, 72));
    }

    pointer allocate(size_type _Count, void const *)
    {
        return allocate(_Count);
    }

    void deallocate(pointer _Ptr, size_type)
    {
        DrMemoryManager::Memory(static_cast<DrMemoryManager::Section>(T1))->Free(_Ptr, DR_STLMEMORY_FILE, 76);
    }

    void construct(pointer _Ptr, T0 const & _Val) { ::new (static_cast<void *>(_Ptr)) T0(_Val); }
    void destroy(pointer _Ptr) { _Ptr->~T0(); }

    size_type max_size() const
    {
        size_type _Count = static_cast<size_type>(-1) / sizeof(T0);
        return 0 < _Count ? _Count : 1;
    }
};

template <class T0, class U, int T1>
inline bool operator==(DrStlAllocator<T0, T1> const &, DrStlAllocator<U, T1> const &) { return true; }

template <class T0, class U, int T1>
inline bool operator!=(DrStlAllocator<T0, T1> const &, DrStlAllocator<U, T1> const &) { return false; }
