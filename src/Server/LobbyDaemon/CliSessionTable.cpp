// CliSessionTable.obj (LobbyDaemon PDB, 2019 + PDB). Source file name from log strings: "CliSessionTable.cpp".
// LIFT: this object has the upper case build path of StlMemory.h (from the HR strings, 0x3d0a0).
#define LIFT_STLMEMORY_FILE \
    L"E:\\DailyBuild02\\LobbyDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\StlMemory.h"
// LIFT: the original Memory.h (line 181) gives its own placement array new and delete. This stops <new> from giving them.
#define __PLACEMENT_VEC_NEW_INLINE
#include <windows.h>
#include <new>
#include "CliSessionTable.h"
#include "CliSession.h"
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "MemoryManager.h"

// PDB S_GTHREAD32 (void*). The original operator delete[] only keeps the pointer here. ❓ module of the definition.
__declspec(thread) void* __delv_buf__;

// LIFT: inlined in CliSessionTable::~CliSessionTable 0x3d0a0.
inline void __cdecl operator delete[](void* p)
{
    __delv_buf__ = p;
}

inline void* __cdecl operator new[](size_t, void* buf) throw()
{
    return buf;
}

// 0x3cfe0
inline void __cdecl operator delete[](void*, void*)
{
    Log::Write(Log::LT_ERROR,
               L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Memory.h",
               181, L"== CRASH == [memory], DO NOT USE THIS DEL OPERATOR");
    AlertSender::Write(
        L"e:\\dailybuild02\\lobbydaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Memory.h",
        181, L"== CRASH == [memory], DO NOT USE THIS DEL OPERATOR");
}

static wchar_t const* const kFile = L"CliSessionTable.cpp";

// LIFT: not in the PDB. The account hash is inlined in Insert_index_account 0x3e670 and the other account functions.
// It adds the 4 dwords of the id128 as 64-bit values.
static inline int AccountHash(id128 const& account, int accountMod)
{
    unsigned long const* d = reinterpret_cast<unsigned long const*>(&account);
    return (int)(((unsigned long long)d[0] + d[1] + d[2] + d[3]) % accountMod);
}

// Inlined in GateNode::`scalar deleting destructor' 0x3d020.
GateNode::~GateNode()
{
    if (_clisession != nullptr)
        _clisession->removeReferenceCount(kFile, 25);
}

// 0x3d0a0
CliSessionTable::~CliSessionTable()
{
    if (_lock_index_pcid != nullptr)
    {
        delete[] _lock_index_pcid;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 74);
        _lock_index_pcid = nullptr;
    }
    if (_index_pcid != nullptr)
    {
        for (int i = 0; i < _sizeGamewid; ++i)
        {
            for (PcidIndexMap::iterator it = _index_pcid[i].begin(); it != _index_pcid[i].end(); ++it)
            {
                if (it->second != nullptr)
                    it->second->removeReferenceCount(kFile, 83);
            }
            _index_pcid[i].clear();
        }
        delete[] _index_pcid;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 87);
        _index_pcid = nullptr;
    }
    if (_lock_index_gatekey != nullptr)
    {
        delete[] _lock_index_gatekey;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 92);
        _lock_index_gatekey = nullptr;
    }
    if (_index_gatekey != nullptr)
    {
        for (int i = 0; i < _sizeGatewid; ++i)
        {
            for (GatekeyIndexMap::iterator it = _index_gatekey[i].begin(); it != _index_gatekey[i].end(); ++it)
            {
                if (it->second != nullptr)
                    it->second->removeReferenceCount(kFile, 101);
            }
            _index_gatekey[i].clear();
        }
        delete[] _index_gatekey;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 105);
        _index_gatekey = nullptr;
    }
    if (_lock_index_gate != nullptr)
    {
        delete[] _lock_index_gate;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 110);
        _lock_index_gate = nullptr;
    }
    if (_index_gate != nullptr)
    {
        delete[] _index_gate;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 112);
        _index_gate = nullptr;
    }
    if (_lock_index_account != nullptr)
    {
        delete[] _lock_index_account;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 116);
        _lock_index_account = nullptr;
    }
    if (_index_account != nullptr)
    {
        for (int i = 0; i < _accountMod; ++i)
        {
            for (AccountIndexMap::iterator it = _index_account[i].begin(); it != _index_account[i].end(); ++it)
            {
                if (it->second != nullptr)
                    it->second->removeReferenceCount(kFile, 124);
            }
            _index_account[i].clear();
        }
        delete[] _index_account;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 128);
        _index_account = nullptr;
    }
    if (_lock != nullptr)
    {
        delete[] _lock;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 133);
        _lock = nullptr;
    }
    if (_table != nullptr)
    {
        for (int i = 0; i < _clikeyMod; ++i)
        {
            for (CliSessionMap::iterator it = _table[i].begin(); it != _table[i].end(); ++it)
            {
                if (it->second != nullptr)
                    it->second->removeReferenceCount(kFile, 139);
            }
            _table[i].clear();
        }
        delete[] _table;
        Memory::_Manager[2]->Free(__delv_buf__, kFile, 143);
        _table = nullptr;
    }
}

// 0x3d940
bool CliSessionTable::Initialize(int clikeyMod, int accountMod, short minGatewid, short maxGatewid, short minGamewid,
                                 short maxGamewid)
{
    if (clikeyMod <= 0 || accountMod <= 0 || minGatewid <= 0 || minGatewid > maxGatewid || minGamewid <= 0 ||
        minGamewid > maxGamewid)
    {
        Log::Write(Log::LT_ERROR, kFile, 155,
                   L"[cs-table], initialize fail; invalid parameter, cli-key-modulus:%d, account-modulus:%d, "
                   L"min-gatewid:%d, max-gatewid:%d, min-gamewid:%d, max-gamewid:%d",
                   clikeyMod, accountMod, minGatewid, maxGatewid, minGamewid, maxGamewid);
        return false;
    }
    int sizeGatewid = maxGatewid - minGatewid + 1;
    int sizeGamewid = maxGamewid - minGamewid + 1;
    if (sizeGatewid <= 0 || sizeGamewid <= 0)
    {
        Log::Write(Log::LT_ERROR, kFile, 163, L"[cs-table], initialize fail; zero or negative size");
        return false;
    }
    _size = 0;
    _clikeyMod = clikeyMod;
    _accountMod = accountMod;
    _minGatewid = minGatewid;
    _sizeGatewid = sizeGatewid;
    _minGamewid = minGamewid;
    _sizeGamewid = sizeGamewid;
    // BUG: 0x3d940 the result of each Alloc call is not checked.
    _lock = new (Memory::_Manager[2]->Alloc(sizeof(CriticalSection) * clikeyMod + 8, kFile, 176))
        CriticalSection[clikeyMod];
    _table = new (Memory::_Manager[2]->Alloc(sizeof(CliSessionMap) * _clikeyMod + 8, kFile, 177))
        CliSessionMap[_clikeyMod];
    _lock_index_gatekey = new (Memory::_Manager[2]->Alloc(sizeof(CriticalSection) * _sizeGatewid + 8, kFile, 179))
        CriticalSection[_sizeGatewid];
    _index_gatekey = new (Memory::_Manager[2]->Alloc(sizeof(GatekeyIndexMap) * _sizeGatewid + 8, kFile, 180))
        GatekeyIndexMap[_sizeGatewid];
    _lock_index_gate = new (Memory::_Manager[2]->Alloc(sizeof(CriticalSection) * _sizeGatewid + 8, kFile, 182))
        CriticalSection[_sizeGatewid];
    _index_gate = new (Memory::_Manager[2]->Alloc(sizeof(RefCntList) * _sizeGatewid + 8, kFile, 183))
        RefCntList[_sizeGatewid];
    _lock_index_pcid = new (Memory::_Manager[2]->Alloc(sizeof(CriticalSection) * _sizeGamewid + 8, kFile, 185))
        CriticalSection[_sizeGamewid];
    _index_pcid = new (Memory::_Manager[2]->Alloc(sizeof(PcidIndexMap) * _sizeGamewid + 8, kFile, 186))
        PcidIndexMap[_sizeGamewid];
    _lock_index_account = new (Memory::_Manager[2]->Alloc(sizeof(CriticalSection) * _accountMod + 8, kFile, 188))
        CriticalSection[_accountMod];
    _index_account = new (Memory::_Manager[2]->Alloc(sizeof(AccountIndexMap) * _accountMod + 8, kFile, 189))
        AccountIndexMap[_accountMod];
    return true;
}

// 0x3de80
bool CliSessionTable::Insert(CliSession* s)
{
    if (s == nullptr || s->_clikey == 0)
        return false;
    int hash = (int)(s->_clikey % _clikeyMod);
    EnterCriticalSection(&_lock[hash].CS);
    std::pair<CliSessionMap::iterator, bool> r =
        _table[hash].insert(std::pair<unsigned long long, CliSession*>(s->_clikey, s));
    if (r.second)
        s->addReferenceCount(kFile, 207);
    LeaveCriticalSection(&_lock[hash].CS);
    if (r.second)
        InterlockedIncrement(reinterpret_cast<long volatile*>(&_size));
    return r.second;
}

// 0x3df60
bool CliSessionTable::Insert_index_gate(short gatewid, GateNode* node)
{
    if (node == nullptr)
        return false;
    int hash = gatewid - _minGatewid;
    if (hash < 0 || hash >= _sizeGatewid)
        return false;
    EnterCriticalSection(&_lock_index_gate[hash].CS);
    bool r = _index_gate[hash].Pushback(node);
    LeaveCriticalSection(&_lock_index_gate[hash].CS);
    return r;
}

// 0x3dff0
void CliSessionTable::Delete(unsigned long long clikey)
{
    if (clikey == 0)
        return;
    int hash = (int)(clikey % _clikeyMod);
    bool deleted = false;
    EnterCriticalSection(&_lock[hash].CS);
    CliSessionMap::iterator it = _table[hash].find(clikey);
    if (it != _table[hash].end())
    {
        if (it->second != nullptr)
            it->second->removeReferenceCount(kFile, 250);
        _table[hash].erase(it);
        deleted = true;
    }
    LeaveCriticalSection(&_lock[hash].CS);
    if (deleted)
        InterlockedDecrement(reinterpret_cast<long volatile*>(&_size));
}

// 0x3e100
void CliSessionTable::Delete_index_gate(short gatewid, GateNode* node)
{
    if (node == nullptr)
        return;
    int hash = gatewid - _minGatewid;
    if (hash < 0 || hash >= _sizeGatewid)
        return;
    EnterCriticalSection(&_lock_index_gate[hash].CS);
    _index_gate[hash].Remove(node);
    LeaveCriticalSection(&_lock_index_gate[hash].CS);
}

// 0x3e180
CliSession* CliSessionTable::Select(unsigned long long clikey)
{
    if (clikey == 0)
        return nullptr;
    int hash = (int)(clikey % _clikeyMod);
    CliSession* s = nullptr;
    EnterCriticalSection(&_lock[hash].CS);
    CliSessionMap::iterator it = _table[hash].find(clikey);
    if (it != _table[hash].end())
    {
        s = it->second;
        // BUG: 0x3e180 no null check of the session before addReferenceCount (the other Select functions have one).
        s->addReferenceCount(kFile, 290);
    }
    LeaveCriticalSection(&_lock[hash].CS);
    return s;
}

// 0x3e270
bool CliSessionTable::Insert_index_gatekey(short gatewid, unsigned long long gatekey, CliSession* s)
{
    if (gatewid == 0 || gatekey == 0 || s == nullptr)
        return false;
    int hash = gatewid - _minGatewid;
    if (hash < 0 || hash >= _sizeGatewid)
        return false;
    EnterCriticalSection(&_lock_index_gatekey[hash].CS);
    std::pair<GatekeyIndexMap::iterator, bool> r =
        _index_gatekey[hash].insert(std::pair<unsigned long long, CliSession*>(gatekey, s));
    if (r.second)
        s->addReferenceCount(kFile, 315);
    LeaveCriticalSection(&_lock_index_gatekey[hash].CS);
    return r.second;
}

// 0x3e350
void CliSessionTable::Delete_index_gatekey(short gatewid, unsigned long long gatekey)
{
    if (gatewid == 0 || gatekey == 0)
        return;
    int hash = gatewid - _minGatewid;
    if (hash < 0 || hash >= _sizeGatewid)
        return;
    CliSession* s = nullptr;
    EnterCriticalSection(&_lock_index_gatekey[hash].CS);
    GatekeyIndexMap::iterator it = _index_gatekey[hash].find(gatekey);
    if (it != _index_gatekey[hash].end())
    {
        s = it->second;
        _index_gatekey[hash].erase(it);
    }
    LeaveCriticalSection(&_lock_index_gatekey[hash].CS);
    if (s != nullptr)
        s->removeReferenceCount(kFile, 348);
}

// 0x3e450
CliSession* CliSessionTable::Select_index_gatekey(short gatewid, unsigned long long gatekey)
{
    if (gatewid == 0 || gatekey == 0)
        return nullptr;
    int hash = gatewid - _minGatewid;
    if (hash < 0 || hash >= _sizeGatewid)
        return nullptr;
    CliSession* s = nullptr;
    EnterCriticalSection(&_lock_index_gatekey[hash].CS);
    GatekeyIndexMap::iterator it = _index_gatekey[hash].find(gatekey);
    if (it != _index_gatekey[hash].end())
    {
        s = it->second;
        if (s != nullptr)
            s->addReferenceCount(kFile, 372);
    }
    LeaveCriticalSection(&_lock_index_gatekey[hash].CS);
    return s;
}

// 0x3e550
bool CliSessionTable::SelectAll_index_gatekey(short gatewid, CliSessionList& out)
{
    int hash = gatewid - _minGatewid;
    if (hash < 0 || hash >= _sizeGatewid)
        return false;
    EnterCriticalSection(&_lock_index_gatekey[hash].CS);
    for (GatekeyIndexMap::iterator it = _index_gatekey[hash].begin(); it != _index_gatekey[hash].end(); ++it)
    {
        if (it->second != nullptr)
        {
            out.push_back(it->second);
            it->second->addReferenceCount(kFile, 399);
        }
    }
    LeaveCriticalSection(&_lock_index_gatekey[hash].CS);
    return true;
}

// 0x3e670
bool CliSessionTable::Insert_index_account(id128 const& account, CliSession* s)
{
    int hash = AccountHash(account, _accountMod);
    EnterCriticalSection(&_lock_index_account[hash].CS);
    std::pair<AccountIndexMap::iterator, bool> r =
        _index_account[hash].insert(std::pair<id128, CliSession*>(account, s));
    if (r.second)
        s->addReferenceCount(kFile, 420);
    LeaveCriticalSection(&_lock_index_account[hash].CS);
    return r.second;
}

// 0x3e750
void CliSessionTable::Delete_index_account(id128 const& account)
{
    CliSession* s = nullptr;
    int hash = AccountHash(account, _accountMod);
    EnterCriticalSection(&_lock_index_account[hash].CS);
    AccountIndexMap::iterator it = _index_account[hash].find(account);
    if (it != _index_account[hash].end())
    {
        s = it->second;
        _index_account[hash].erase(it);
    }
    LeaveCriticalSection(&_lock_index_account[hash].CS);
    if (s != nullptr)
        s->removeReferenceCount(kFile, 447);
}

// 0x3e870
CliSession* CliSessionTable::Select_index_account(id128 const& account)
{
    CliSession* s = nullptr;
    int hash = AccountHash(account, _accountMod);
    EnterCriticalSection(&_lock_index_account[hash].CS);
    AccountIndexMap::iterator it = _index_account[hash].find(account);
    if (it != _index_account[hash].end() && it->second != nullptr)
    {
        s = it->second;
        s->addReferenceCount(kFile, 466);
    }
    LeaveCriticalSection(&_lock_index_account[hash].CS);
    return s;
}

// 0x3e980
bool CliSessionTable::Insert_index_pcid(short wid, unsigned long long pcid, CliSession* s)
{
    int hash = wid - _minGamewid;
    if (hash < 0 || hash >= _sizeGamewid)
        return false;
    EnterCriticalSection(&_lock_index_pcid[hash].CS);
    std::pair<PcidIndexMap::iterator, bool> r =
        _index_pcid[hash].insert(std::pair<unsigned long long, CliSession*>(pcid, s));
    if (r.second)
        s->addReferenceCount(kFile, 488);
    LeaveCriticalSection(&_lock_index_pcid[hash].CS);
    return r.second;
}

// 0x3ea50
void CliSessionTable::Delete_index_pcid(short wid, unsigned long long pcid)
{
    int hash = wid - _minGamewid;
    if (hash < 0 || hash >= _sizeGamewid)
        return;
    CliSession* s = nullptr;
    EnterCriticalSection(&_lock_index_pcid[hash].CS);
    PcidIndexMap::iterator it = _index_pcid[hash].find(pcid);
    if (it != _index_pcid[hash].end())
    {
        s = it->second;
        _index_pcid[hash].erase(it);
    }
    LeaveCriticalSection(&_lock_index_pcid[hash].CS);
    if (s != nullptr)
        s->removeReferenceCount(kFile, 517);
}

// 0x3eb40
CliSession* CliSessionTable::Select_index_pcid(short wid, unsigned long long pcid)
{
    int hash = wid - _minGamewid;
    if (hash < 0 || hash >= _sizeGamewid)
        return nullptr;
    CliSession* s = nullptr;
    EnterCriticalSection(&_lock_index_pcid[hash].CS);
    PcidIndexMap::iterator it = _index_pcid[hash].find(pcid);
    if (it != _index_pcid[hash].end() && it->second != nullptr)
    {
        s = it->second;
        s->addReferenceCount(kFile, 538);
    }
    LeaveCriticalSection(&_lock_index_pcid[hash].CS);
    return s;
}

// 0x3ec40
// LIFT: LTCG changed the binary form: it gets the hash in place of wid and keeps only the upper range check. This is
// the source form from the PDB signature (short wid, CliSessionList&) and the local "hash".
bool CliSessionTable::SelectAll_index_pcid(short wid, CliSessionList& out)
{
    int hash = wid - _minGamewid;
    if (hash < 0 || hash >= _sizeGamewid)
        return false;
    EnterCriticalSection(&_lock_index_pcid[hash].CS);
    for (PcidIndexMap::iterator it = _index_pcid[hash].begin(); it != _index_pcid[hash].end(); ++it)
    {
        if (it->second != nullptr)
        {
            out.push_back(it->second);
            it->second->addReferenceCount(kFile, 563);
        }
    }
    LeaveCriticalSection(&_lock_index_pcid[hash].CS);
    return true;
}

// 0x3ed50
bool CliSessionTable::SelectAll(CliSessionList& out)
{
    for (int i = 0; i < _clikeyMod; ++i)
    {
        EnterCriticalSection(&_lock[i].CS);
        for (CliSessionMap::iterator it = _table[i].begin(); it != _table[i].end(); ++it)
        {
            CliSession* s = it->second;
            if (s != nullptr)
            {
                out.push_back(s);
                s->addReferenceCount(kFile, 586);
            }
        }
        LeaveCriticalSection(&_lock[i].CS);
    }
    return true;
}

// LIFT: keep until the caller is lifted (0x3eef0).
#pragma comment(linker, "/INCLUDE:?Select_index_gate@CliSessionTable@@QEAA_NFAEAV?$vector@PEAVCliSession@@V?$StlAllocator@PEAVCliSession@@$01@@@std@@@Z")

// 0x3eef0
bool CliSessionTable::Select_index_gate(short gatewid, CliSessionList& out)
{
    int hash = gatewid - _minGatewid;
    if (hash < 0 || hash >= _sizeGatewid)
    {
        Log::Write(Log::LT_ERROR, L"CliSessionTable.cpp", 601,
                   L"[cs-table], select * from gate-index fail; gate-wid out of range, gate-wid:%d", gatewid);
        return false;
    }
    EnterCriticalSection(&_lock_index_gate[hash].CS);
    RefCntList& list = _index_gate[hash];  // LIFT: name for the indexed list (0x3eef0).
    if (list.Size() > 0)
    {
        for (RefCntListNode* i = list.Begin(); i != nullptr; i = i->NextNode())
        {
            CliSession* gateCs = static_cast<GateNode*>(i)->_clisession;
            if (gateCs != nullptr)
            {
                out.push_back(gateCs);
                gateCs->addReferenceCount(L"CliSessionTable.cpp", 614);
            }
            else
            {
                Log::Write(Log::LT_ERROR, L"CliSessionTable.cpp", 617,
                           L"== CRASH == [cs-table], select * from gate-index exception; null cli-session");
                AlertSender::Write(L"CliSessionTable.cpp", 617,
                                   L"== CRASH == [cs-table], select * from gate-index exception; null cli-session");
            }
        }
    }
    LeaveCriticalSection(&_lock_index_gate[hash].CS);
    return true;
}
