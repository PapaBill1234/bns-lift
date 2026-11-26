// CliSessionTable.obj (LobbyDaemon PDB, 2019 + PDB). Layout from the PDB (types.h CliSessionTable, size 0x80).
#pragma once
#include <stddef.h>
#include <map>
#include <vector>
#include "Lock.h"
#include "StlMemory.h"
#include "StringUtil.h"
#include "RefCntList.h"

class CliSession;

// PDB GateNode (size 0x38). The binary has only the scalar deleting destructor (0x3d020).
class GateNode : public RefCntListNode
{
public:
    // LIFT: inlined in LobbyGatePresence::OnSet (0x3a7d0). The body is in CliSession.cpp (CliSession is incomplete here).
    explicit GateNode(CliSession* clisession);
    virtual ~GateNode();  // inlined in 0x3d020
    CliSession* _clisession;  // +48
};

// LIFT: not in the PDB. std::less<id128> needs operator<. The order comes from the inlined compare in
// the AccountIndexMap find of CliSessionTable::Delete_index_account 0x3e750 (id[0] first, then id[1]).
inline bool operator<(id128 const& a, id128 const& b)
{
    return a.id[0] < b.id[0] || (a.id[0] == b.id[0] && a.id[1] < b.id[1]);
}

class CliSessionTable
{
public:
    // The PDB has the names CliSessionList, CliSessionMap, GatekeyIndexMap, PcidIndexMap and AccountIndexMap.
    // ❓ scope of the typedefs (class or global).
    typedef std::vector<CliSession*, StlAllocator<CliSession*, 2> > CliSessionList;
    typedef std::map<unsigned long long, CliSession*, std::less<unsigned long long>,
                     StlAllocator<std::pair<unsigned long long, CliSession*>, 2> >
        CliSessionMap;
    typedef CliSessionMap GatekeyIndexMap;
    typedef CliSessionMap PcidIndexMap;
    typedef std::map<id128, CliSession*, std::less<id128>, StlAllocator<std::pair<id128, CliSession*>, 2> >
        AccountIndexMap;

    struct Gateindex
    {
        short wid;
        unsigned long long gatekey;
    };

    // LIFT: PDB inline ctor (2 overloads in the PDB). Inlined in LobbyDaemon::initialize (0x9b300, line 1587).
    explicit CliSessionTable(unsigned long long (*clikeygen)())
        : _clikeygen(reinterpret_cast<void*>(clikeygen)), _size(0), _clikeyMod(0), _accountMod(0), _minGatewid(0),
          _sizeGatewid(0), _minGamewid(0), _sizeGamewid(0), _lock(nullptr), _table(nullptr), _lock_index_gatekey(nullptr),
          _index_gatekey(nullptr), _lock_index_gate(nullptr), _index_gate(nullptr), _lock_index_account(nullptr),
          _index_account(nullptr), _lock_index_pcid(nullptr), _index_pcid(nullptr)
    {
    }
    virtual ~CliSessionTable();  // 0x3d0a0
    bool Initialize(int clikeyMod, int accountMod, short minGatewid, short maxGatewid, short minGamewid,
                    short maxGamewid);  // 0x3d940
    bool Insert(CliSession* s);  // 0x3de80
    bool Insert_index_gate(short gatewid, GateNode* node);  // 0x3df60
    void Delete(unsigned long long clikey);  // 0x3dff0
    void Delete_index_gate(short gatewid, GateNode* node);  // 0x3e100
    CliSession* Select(unsigned long long clikey);  // 0x3e180
    bool Insert_index_gatekey(short gatewid, unsigned long long gatekey, CliSession* s);  // 0x3e270
    void Delete_index_gatekey(short gatewid, unsigned long long gatekey);  // 0x3e350
    CliSession* Select_index_gatekey(short gatewid, unsigned long long gatekey);  // 0x3e450
    bool SelectAll_index_gatekey(short gatewid, CliSessionList& out);  // 0x3e550
    bool Insert_index_account(id128 const& account, CliSession* s);  // 0x3e670
    void Delete_index_account(id128 const& account);  // 0x3e750
    CliSession* Select_index_account(id128 const& account);  // 0x3e870
    bool Insert_index_pcid(short wid, unsigned long long pcid, CliSession* s);  // 0x3e980
    void Delete_index_pcid(short wid, unsigned long long pcid);  // 0x3ea50
    CliSession* Select_index_pcid(short wid, unsigned long long pcid);  // 0x3eb40
    bool SelectAll_index_pcid(short wid, CliSessionList& out);  // 0x3ec40
    bool SelectAll(CliSessionList& out);  // 0x3ed50
    bool Select_index_gate(short gatewid, CliSessionList& out);  // 0x3eef0

    // LIFT: types.h shows all members as public. The original access is not in the PDB.
    void* _clikeygen;                      // +8
    int _size;                             // +16
    int _clikeyMod;                        // +20
    int _accountMod;                       // +24
    int _minGatewid;                       // +28
    int _sizeGatewid;                      // +32
    int _minGamewid;                       // +36
    int _sizeGamewid;                      // +40
    CriticalSection* _lock;                // +48
    CliSessionMap* _table;                 // +56
    CriticalSection* _lock_index_gatekey;  // +64
    GatekeyIndexMap* _index_gatekey;       // +72
    CriticalSection* _lock_index_gate;     // +80
    RefCntList* _index_gate;               // +88
    CriticalSection* _lock_index_account;  // +96
    AccountIndexMap* _index_account;       // +104
    CriticalSection* _lock_index_pcid;     // +112
    PcidIndexMap* _index_pcid;             // +120
};
static_assert(sizeof(CliSessionTable) == 0x80, "sizeof CliSessionTable");
static_assert(offsetof(CliSessionTable, _clikeygen) == 0x8, "CliSessionTable::_clikeygen");
static_assert(offsetof(CliSessionTable, _size) == 0x10, "CliSessionTable::_size");
static_assert(offsetof(CliSessionTable, _clikeyMod) == 0x14, "CliSessionTable::_clikeyMod");
static_assert(offsetof(CliSessionTable, _accountMod) == 0x18, "CliSessionTable::_accountMod");
static_assert(offsetof(CliSessionTable, _minGatewid) == 0x1C, "CliSessionTable::_minGatewid");
static_assert(offsetof(CliSessionTable, _sizeGatewid) == 0x20, "CliSessionTable::_sizeGatewid");
static_assert(offsetof(CliSessionTable, _minGamewid) == 0x24, "CliSessionTable::_minGamewid");
static_assert(offsetof(CliSessionTable, _sizeGamewid) == 0x28, "CliSessionTable::_sizeGamewid");
static_assert(offsetof(CliSessionTable, _lock) == 0x30, "CliSessionTable::_lock");
static_assert(offsetof(CliSessionTable, _table) == 0x38, "CliSessionTable::_table");
static_assert(offsetof(CliSessionTable, _lock_index_gatekey) == 0x40, "CliSessionTable::_lock_index_gatekey");
static_assert(offsetof(CliSessionTable, _index_gatekey) == 0x48, "CliSessionTable::_index_gatekey");
static_assert(offsetof(CliSessionTable, _lock_index_gate) == 0x50, "CliSessionTable::_lock_index_gate");
static_assert(offsetof(CliSessionTable, _index_gate) == 0x58, "CliSessionTable::_index_gate");
static_assert(offsetof(CliSessionTable, _lock_index_account) == 0x60, "CliSessionTable::_lock_index_account");
static_assert(offsetof(CliSessionTable, _index_account) == 0x68, "CliSessionTable::_index_account");
static_assert(offsetof(CliSessionTable, _lock_index_pcid) == 0x70, "CliSessionTable::_lock_index_pcid");
static_assert(offsetof(CliSessionTable, _index_pcid) == 0x78, "CliSessionTable::_index_pcid");
static_assert(sizeof(CliSessionTable::Gateindex) == 0x10, "sizeof CliSessionTable::Gateindex");
static_assert(offsetof(CliSessionTable::Gateindex, gatekey) == 0x8, "CliSessionTable::Gateindex::gatekey");
static_assert(sizeof(GateNode) == 0x38, "sizeof GateNode");
static_assert(offsetof(GateNode, _clisession) == 0x30, "GateNode::_clisession");
