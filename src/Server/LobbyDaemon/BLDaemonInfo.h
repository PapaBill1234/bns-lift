// BLDaemonInfo.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from the PDB.
#pragma once
#include "Lock.h"
#include "StlMemory.h"
#include <map>

// PDB enum BLDaemonKind (0x5DC9).
enum BLDaemonKind
{
    BLDAEMONKIND_INVALID = 0,
    BLDAEMONKIND_GAMED = 1,
    BLDAEMONKIND_CACHED = 2,
    BLDAEMONKIND_LOBBY_GATE = 3,
    BLDAEMONKIND_INFO_GATE = 4,
    BLDAEMONKIND_MOBILE_GATE = 5,
    BLDAEMONKIND_MAX = 6
};

// PDB struct BLDaemonID (0x60ED), size 0x8.
struct BLDaemonID
{
    // LIFT: the two constructors are inline and have no body in the binary. ❓ bodies.
    BLDaemonID() : kind(BLDAEMONKIND_INVALID), wid(0) {}
    BLDaemonID(int kind_, int wid_) : kind(kind_), wid(static_cast<short>(wid_)) {}
    // LIFT: inline. Comparison from BLDaemonInfoTable::Find 0x41210.
    bool operator==(BLDaemonID const& other) const { return kind == other.kind && wid == other.wid; }
    bool operator<(BLDaemonID const& other) const
    {
        return kind < other.kind || (kind == other.kind && wid < other.wid);
    }

    int kind;    // +0x0
    short wid;   // +0x4
};
static_assert(sizeof(BLDaemonID) == 0x8, "sizeof BLDaemonID");

// PDB struct BLDaemonInfo (0x6013), size 0x10.
struct BLDaemonInfo
{
    BLDaemonID id;                // +0x0
    unsigned long internal_ipv4;  // +0x8
    union
    {
        struct
        {
            unsigned short internal_port;
        } gamed, cached, lobby_gate, infogate;
    } ind;                        // +0xc
};
static_assert(sizeof(BLDaemonInfo) == 0x10, "sizeof BLDaemonInfo");

class BLDaemonInfoTable
{
public:
    typedef std::map<BLDaemonID, BLDaemonInfo*, std::less<BLDaemonID>,
                     StlAllocator<std::pair<BLDaemonID, BLDaemonInfo*>, 2> >
        BLDaemonInfoMap;

    BLDaemonInfoTable();  // 0x403c0
    ~BLDaemonInfoTable();  // 0x40490
    bool Load(wchar_t const*);  // 0x40f30
    void Update(wchar_t const*);  // 0x41090
    BLDaemonInfo const* Find(BLDaemonID const&) const;  // 0x41210
    void Clear();  // 0x412d0
private:
    bool load(wchar_t const*, BLDaemonInfo**&, int&);  // 0x40510
    bool add(BLDaemonInfo*);  // 0x40e30

    CriticalSection _lock;      // +0x0
    BLDaemonInfoMap _daemons;   // +0x28
};
