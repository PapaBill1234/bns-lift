// CliSessionTable.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class GateNode;
union id128;

class CliSessionTable
{
public:
    virtual ~CliSessionTable();  // 0x3d0a0
    bool Initialize(int, int, short, short, short, short);  // 0x3d940
    bool Insert(CliSession*);  // 0x3de80
    bool Insert_index_gate(short, GateNode*);  // 0x3df60
    void Delete(unsigned long long);  // 0x3dff0
    void Delete_index_gate(short, GateNode*);  // 0x3e100
    CliSession* Select(unsigned long long);  // 0x3e180
    bool Insert_index_gatekey(short, unsigned long long, CliSession*);  // 0x3e270
    void Delete_index_gatekey(short, unsigned long long);  // 0x3e350
    CliSession* Select_index_gatekey(short, unsigned long long);  // 0x3e450
    bool Insert_index_account(id128 const&, CliSession*);  // 0x3e670
    void Delete_index_account(id128 const&);  // 0x3e750
    CliSession* Select_index_account(id128 const&);  // 0x3e870
    bool Insert_index_pcid(short, unsigned long long, CliSession*);  // 0x3e980
    void Delete_index_pcid(short, unsigned long long);  // 0x3ea50
    CliSession* Select_index_pcid(short, unsigned long long);  // 0x3eb40
};
