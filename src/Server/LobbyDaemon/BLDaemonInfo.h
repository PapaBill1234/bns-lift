// BLDaemonInfo.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

// Layouts: include/pdb/LobbyDaemon/types.h (BLDaemonID sizeof 0x8, BLDaemonInfo sizeof 0x10).
struct BLDaemonID
{
    int kind;
    short wid;
};
static_assert(sizeof(BLDaemonID) == 0x8, "sizeof BLDaemonID");

struct BLDaemonInfo
{
    BLDaemonID id;
    unsigned long internal_ipv4;
    union
    {
        struct
        {
            unsigned short internal_port;
        } gamed;
        struct
        {
            unsigned short internal_port;
        } cached;
        struct
        {
            unsigned short internal_port;
        } lobby_gate;
        struct
        {
            unsigned short internal_port;
        } infogate;
    } ind;
};
static_assert(sizeof(BLDaemonInfo) == 0x10, "sizeof BLDaemonInfo");

class BLDaemonInfoTable
{
public:
    BLDaemonInfoTable();  // 0x403c0
    ~BLDaemonInfoTable();  // 0x40490
    bool Load(wchar_t const*);  // 0x40f30
    void Update(wchar_t const*);  // 0x41090
    BLDaemonInfo const* Find(BLDaemonID const&) const;  // 0x41210
    void Clear();  // 0x412d0
private:
    bool load(wchar_t const*, BLDaemonInfo**&, int&);  // 0x40510
    bool add(BLDaemonInfo*);  // 0x40e30
};
