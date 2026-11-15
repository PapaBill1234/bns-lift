// Selftest for include/vs2010/ (VS2010 STL subset).
// 1. static_assert: container sizes and member offsets. The values come from the CacheGate PDB
//    (x64, VS2010 SP1 release). The test allocator is 1 byte, as StlAllocator<T, 2> in the PDB.
// 2. Explicit instantiation: all members of each container must compile.
// 3. lift_stl_selftest(): a quiet runtime test. main() calls it. It returns 0 when all checks pass.
#include <stdlib.h>
#include <xstring>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <algorithm>

#pragma clang diagnostic ignored "-Winvalid-offsetof"

namespace lift_test {
// 1-byte allocator with the VS2010 allocator interface (same size as StlAllocator<T, 2>).
template<class T>
class TestAlloc
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    template<class U>
    struct rebind
    {
        typedef TestAlloc<U> other;
    };

    TestAlloc() {}
    TestAlloc(const TestAlloc&) {}
    template<class U>
    TestAlloc(const TestAlloc<U>&) {}

    pointer allocate(size_type count) { return static_cast<pointer>(malloc(count * sizeof(T))); }
    void deallocate(pointer p, size_type) { free(p); }
    template<class U>
    void construct(pointer p, U&& v) { ::new (static_cast<void*>(p)) T(std::forward<U>(v)); }
    void destroy(pointer p) { p->~T(); }
    size_type max_size() const { return (size_type)(-1) / sizeof(T); }
};

struct Timer;  // as CacheGate Timer: only the pointer is used.

struct GreaterBySlotIndex  // as TimerQueue::GreaterBySlotIndex (1 byte)
{
    bool operator()(const Timer* l, const Timer* r) const { return l > r; }
};

typedef std::basic_string<char, std::char_traits<char>, TestAlloc<char> > TString;
typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, TestAlloc<wchar_t> > TWString;
typedef std::vector<int, TestAlloc<int> > TVector;
typedef std::map<unsigned short, void*, std::less<unsigned short>, TestAlloc<std::pair<const unsigned short, void*> > > TMap;
typedef std::set<int, std::less<int>, TestAlloc<int> > TSet;
typedef std::deque<void*, TestAlloc<void*> > TDeque;
typedef std::priority_queue<Timer*, std::vector<Timer*, TestAlloc<Timer*> >, GreaterBySlotIndex> TPrioQueue;

struct PrioQueueProbe : TPrioQueue
{
    static constexpr size_t OffC() { return offsetof(PrioQueueProbe, c); }
    static constexpr size_t OffComp() { return offsetof(PrioQueueProbe, comp); }
};
} // namespace lift_test

using namespace lift_test;

// basic_string<char> and basic_string<wchar_t>: 0x28.
static_assert(sizeof(TString) == 0x28, "string size");
static_assert(offsetof(TString, _Bx) == 0x00, "string _Bx");
static_assert(offsetof(TString, _Mysize) == 0x10, "string _Mysize");
static_assert(offsetof(TString, _Myres) == 0x18, "string _Myres");
static_assert(offsetof(TString, _Alval) == 0x20, "string _Alval");
static_assert(sizeof(TWString) == 0x28, "wstring size");
static_assert(offsetof(TWString, _Mysize) == 0x10, "wstring _Mysize");
static_assert(offsetof(TWString, _Myres) == 0x18, "wstring _Myres");
static_assert(offsetof(TWString, _Alval) == 0x20, "wstring _Alval");
static_assert(sizeof(std::string) == 0x28, "std::string size");
static_assert(sizeof(std::wstring) == 0x28, "std::wstring size");

// vector: 0x20.
static_assert(sizeof(TVector) == 0x20, "vector size");
static_assert(offsetof(TVector, _Myfirst) == 0x00, "vector _Myfirst");
static_assert(offsetof(TVector, _Mylast) == 0x08, "vector _Mylast");
static_assert(offsetof(TVector, _Myend) == 0x10, "vector _Myend");
static_assert(offsetof(TVector, _Alval) == 0x18, "vector _Alval");

// map: 0x20, node 0x30.
static_assert(sizeof(TMap) == 0x20, "map size");
static_assert(offsetof(TMap, comp) == 0x00, "map comp");
static_assert(offsetof(TMap, _Myhead) == 0x08, "map _Myhead");
static_assert(offsetof(TMap, _Mysize) == 0x10, "map _Mysize");
static_assert(offsetof(TMap, _Alnod) == 0x18, "map _Alnod");
static_assert(offsetof(TMap, _Alval) == 0x19, "map _Alval");
static_assert(sizeof(TMap::_Node) == 0x30, "map node size");
static_assert(offsetof(TMap::_Node, _Left) == 0x00, "map node _Left");
static_assert(offsetof(TMap::_Node, _Parent) == 0x08, "map node _Parent");
static_assert(offsetof(TMap::_Node, _Right) == 0x10, "map node _Right");
static_assert(offsetof(TMap::_Node, _Myval) == 0x18, "map node _Myval");
static_assert(offsetof(TMap::_Node, _Color) == 0x28, "map node _Color");
static_assert(offsetof(TMap::_Node, _Isnil) == 0x29, "map node _Isnil");
static_assert(sizeof(TMap::iterator) == 0x08, "map iterator size");
static_assert(sizeof(std::pair<const unsigned short, void*>) == 0x10, "pair size");
static_assert(sizeof(TSet) == 0x20, "set size");
static_assert(offsetof(TSet, _Myhead) == 0x08, "set _Myhead");
static_assert(offsetof(TSet, _Mysize) == 0x10, "set _Mysize");

// deque: 0x30, iterator 0x18.
static_assert(sizeof(TDeque) == 0x30, "deque size");
static_assert(offsetof(TDeque, _Myproxy) == 0x00, "deque _Myproxy");
static_assert(offsetof(TDeque, _Map) == 0x08, "deque _Map");
static_assert(offsetof(TDeque, _Mapsize) == 0x10, "deque _Mapsize");
static_assert(offsetof(TDeque, _Myoff) == 0x18, "deque _Myoff");
static_assert(offsetof(TDeque, _Mysize) == 0x20, "deque _Mysize");
static_assert(offsetof(TDeque, _Alval) == 0x28, "deque _Alval");
static_assert(offsetof(TDeque, _Almap) == 0x29, "deque _Almap");
static_assert(sizeof(TDeque::iterator) == 0x18, "deque iterator size");
static_assert(offsetof(TDeque::iterator, _Myoff) == 0x10, "deque iterator _Myoff");
static_assert(sizeof(std::_Container_proxy) == 0x10, "_Container_proxy size");

// priority_queue<Timer*, vector, GreaterBySlotIndex>: 0x28.
static_assert(sizeof(TPrioQueue) == 0x28, "priority_queue size");
static_assert(PrioQueueProbe::OffC() == 0x00, "priority_queue c");
static_assert(PrioQueueProbe::OffComp() == 0x20, "priority_queue comp");

// All members must compile.
template class std::basic_string<char, std::char_traits<char>, TestAlloc<char> >;
template class std::basic_string<wchar_t, std::char_traits<wchar_t>, TestAlloc<wchar_t> >;
template class std::vector<int, TestAlloc<int> >;
template class std::vector<Timer*, TestAlloc<Timer*> >;
template class std::_Tree<std::_Tmap_traits<unsigned short, void*, std::less<unsigned short>,
                                            TestAlloc<std::pair<const unsigned short, void*> >, false> >;
template class std::map<unsigned short, void*, std::less<unsigned short>,
                        TestAlloc<std::pair<const unsigned short, void*> > >;
template class std::_Tree<std::_Tset_traits<int, std::less<int>, TestAlloc<int>, false> >;
template class std::set<int, std::less<int>, TestAlloc<int> >;
template class std::deque<void*, TestAlloc<void*> >;
template class std::priority_queue<Timer*, std::vector<Timer*, TestAlloc<Timer*> >, GreaterBySlotIndex>;
template class std::queue<void*, TDeque>;

namespace {
unsigned int g_seed = 12345;

unsigned int NextRandom()
{
    g_seed = g_seed * 1103515245u + 12345u;
    return (g_seed >> 8) & 0xffff;
}

// Returns the black height, or -1 if the subtree is not a valid red-black tree.
int CheckRedBlack(TMap::_Nodeptr p)
{
    if (p->_Isnil)
        return 1;
    if (p->_Color == TMap::_Red && (p->_Left->_Color == TMap::_Red || p->_Right->_Color == TMap::_Red))
        return -1;
    if (!p->_Left->_Isnil && (p->_Left->_Parent != p || !(p->_Left->_Myval.first < p->_Myval.first)))
        return -1;
    if (!p->_Right->_Isnil && (p->_Right->_Parent != p || !(p->_Myval.first < p->_Right->_Myval.first)))
        return -1;
    int l = CheckRedBlack(p->_Left);
    int r = CheckRedBlack(p->_Right);
    if (l < 0 || l != r)
        return -1;
    return l + (p->_Color == TMap::_Black ? 1 : 0);
}

int TestString()
{
    TString s("abc");
    if (s.size() != 3 || s._Myres != 15)
        return 1;
    for (int i = 0; i < 10; ++i)
        s.append("0123456789");
    if (s.size() != 103 || s.c_str()[103] != 0 || s[3] != '0')
        return 2;
    if (s.find("9012") != 12 || s.find('x') != TString::npos)
        return 3;
    s.erase(3, 100);
    if (!(s == TString("abc")) || s.compare("abc") != 0)
        return 4;
    TString t = s + "def";
    if (t.substr(2, 2) != TString("cd"))
        return 5;
    TWString w(L"x");
    w.append(40, L'y');
    if (w.size() != 41 || w[40] != L'y')
        return 6;
    return 0;
}

int TestVector()
{
    TVector v;
    for (int i = 0; i < 100; ++i)
        v.push_back(i);
    v.push_back(v[5]);  // _Inside path
    if (v.size() != 101 || v[100] != 5 || v.capacity() < 101)
        return 11;
    v.insert(v.begin() + 1, 77);
    v.erase(v.begin() + 2);
    if (v[1] != 77 || v[2] != 2 || v.size() != 101)
        return 12;
    TVector c(v);
    v.clear();
    if (!v.empty() || c.size() != 101 || c[100] != 5)
        return 13;
    return 0;
}

int TestMap()
{
    TMap m;
    int added = 0;
    for (int i = 0; i < 500; ++i) {
        unsigned short key = (unsigned short)(NextRandom() % 1000);
        if (m.insert(std::pair<const unsigned short, void*>(key, (void*)(size_t)(key + 1))).second)
            ++added;
    }
    if ((int)m.size() != added || CheckRedBlack(m._Root()) < 0 || m._Root()->_Color != TMap::_Black)
        return 21;
    int erased = 0;
    for (unsigned short key = 0; key < 1000; key += 2)
        erased += (int)m.erase(key);
    if ((int)m.size() != added - erased || CheckRedBlack(m._Root()) < 0)
        return 22;
    unsigned int prev = 0;
    bool first = true;
    for (TMap::iterator it = m.begin(); it != m.end(); ++it) {
        if ((it->first & 1) == 0 || (!first && it->first <= prev) || it->second != (void*)(size_t)(it->first + 1))
            return 23;
        prev = it->first;
        first = false;
    }
    m[2000] = 0;
    if (m.find(2000) == m.end() || m.find(2) != m.end() || m.count(2000) != 1)
        return 24;
    TMap c(m);
    m.clear();
    if (!m.empty() || c.size() != (size_t)(added - erased + 1) || CheckRedBlack(c._Root()) < 0)
        return 25;
    return 0;
}

int TestDeque()
{
    TDeque d;
    for (size_t i = 0; i < 100; ++i) {
        d.push_back((void*)(i + 1000));
        d.push_front((void*)(999 - i));
    }
    if (d.size() != 200)
        return 31;
    for (size_t i = 0; i < 200; ++i)
        if (d[i] != (void*)(900 + i))
            return 32;
    for (int i = 0; i < 50; ++i) {
        d.pop_front();
        d.pop_back();
    }
    if (d.size() != 100 || d.front() != (void*)950 || d.back() != (void*)1049)
        return 33;
    d.erase(d.begin() + 10);
    if (d.size() != 99 || d[10] != (void*)961 || d[9] != (void*)959)
        return 34;
    std::queue<void*, TDeque> q;
    q.push((void*)1);
    q.push((void*)2);
    q.pop();
    if (q.front() != (void*)2 || q.size() != 1)
        return 35;
    return 0;
}

int TestPrioQueue()
{
    TPrioQueue q;
    for (int i = 0; i < 100; ++i)
        q.push((Timer*)(size_t)(NextRandom() + 1));
    Timer* prev = 0;
    while (!q.empty()) {
        Timer* top = q.top();
        if (top < prev)  // GreaterBySlotIndex: the smallest is on top.
            return 41;
        prev = top;
        q.pop();
    }
    return 0;
}
} // namespace

int lift_stl_selftest()
{
    int rc;
    if ((rc = TestString()) != 0)
        return rc;
    if ((rc = TestVector()) != 0)
        return rc;
    if ((rc = TestMap()) != 0)
        return rc;
    if ((rc = TestDeque()) != 0)
        return rc;
    return TestPrioQueue();
}
