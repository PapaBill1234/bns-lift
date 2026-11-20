// BLDaemonInfo.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct BLDaemonID;
struct BLDaemonInfo;

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
