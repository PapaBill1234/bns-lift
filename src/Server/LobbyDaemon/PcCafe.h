// PcCafe.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class TencentNetBar;

// PDB class PcCafe (size 0x8). Abstract base. CliSession::setPcCafe (0x3a100) calls onSet and onUnset.
class PcCafe
{
public:
    enum Type
    {
        TYPE_None = 0,
        TYPE_TencentNetBar = 1,
        TYPE_Max = 2,
    };

    // LIFT: the original global operator delete(void*) (0x32b50) is empty. The caller does "delete p;" and then
    // Memory::_Manager[2]->Free(p, ...) (CliSession::setPcCafe 0x3a100). This empty class operator delete keeps
    // that shape and frees the memory only once (in Free).
    static void operator delete(void*) {}

    virtual ~PcCafe();  // 0x63340 (scalar deleting destructor)
    virtual Type GetType() = 0;

protected:
    virtual void onSet(CliSession*) = 0;
    virtual void onUnset(CliSession*) = 0;

    // LIFT: CliSession::setPcCafe (0x3a100) calls the protected onSet and onUnset. ❓ The PDB has no friend record.
    friend class CliSession;
};

class TencentNetBar
{
public:
    static TencentNetBar* CreateFromExternalAuthData(char const*, CliSession const*);  // 0x62e90
private:
    virtual void onSet(CliSession*);  // 0x63350
};
