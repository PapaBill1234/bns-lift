<<<<<<< HEAD
// gametran.h: gametran.cpp, gametran.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: GameTran and UserTran have the PDB layouts. The other classes have no members and no bases yet.
=======
// gametran.h: gametran.cpp, gametran.h (GameDaemon PDB, 2019 + PDB).
// GameTran, UserTran and SessionTran have their PDB layouts. GameTranManager has no members yet.
>>>>>>> refs/author/pre-rebase/2
#pragma once
#include "GameDaemonFwd.h"
#include "transactionexpirechecker.h"
#include "RefCntObject.h"
#include "Lock.h"

<<<<<<< HEAD
// PDB: GameTran, size 0x50. The vtable order is the PDB slot order.
=======
class GameTranDef;
class GameTranStateDef;

// PDB: class GameTran, size 0x50, base DynamicRefCntObj.
>>>>>>> refs/author/pre-rebase/2
class GameTran : public DynamicRefCntObj
{
public:
    enum Result {};
public:
    // PDB: GameTran(); inlined (no rva). Order of the stores from UserTran::UserTran (0x27e60).
    GameTran() : _id(0), _state(0), _lastState(0) {}
    virtual __cdecl ~GameTran(void);  // 0x27e10
<<<<<<< HEAD
    unsigned __int64 __cdecl GetId(void) const { return _id; }
    virtual ::GameTranDef const * __cdecl GetDefinition(void) const = 0;  // slot 4
protected:
    virtual bool __cdecl run(int, void *);  // 0x27e50, slot 5
    virtual bool __cdecl work(int, void *) = 0;  // slot 6
    bool __cdecl transit(int);  // 0xd5950
    ::GameTran::Result __cdecl execute(int, void *);  // 0xd5b60
    ::GameTran::Result __cdecl resume(int, int, void *);  // 0xd5c20
private:
    unsigned __int64 _id;  // +0x18
    int _state;  // +0x20
    int _lastState;  // +0x24
    ::CriticalSection _lock;  // +0x28
=======
    virtual GameTranDef const * GetDefinition() const = 0;  // slot 4
protected:
    bool __cdecl transit(int);  // 0xd5950
    ::GameTran::Result __cdecl execute(int, void *);  // 0xd5b60
    ::GameTran::Result __cdecl resume(int, int, void *);  // 0xd5c20
    virtual bool __cdecl run(int, void *);  // 0x27e50, slot 5
    virtual bool work(int, void *) = 0;  // slot 6
private:
    unsigned __int64 _id;   // +24 (0x18)
    int _state;             // +32 (0x20)
    int _lastState;         // +36 (0x24)
    CriticalSection _lock;  // +40 (0x28)
>>>>>>> refs/author/pre-rebase/2
};
static_assert(sizeof(GameTran) == 0x50, "sizeof GameTran");

class GameTranManager
{
public:
    __cdecl ~GameTranManager(void);  // 0xd5cf0
    bool __cdecl Initialize(unsigned __int64 (__cdecl *)(void));  // 0xd5dd0
    bool __cdecl SetExpireChecker(long);  // 0xd5ea0
    bool __cdecl Start(::GameTran *, int, void *);  // 0xd5f50
    void __cdecl Execute(::GameTran *, int, void *);  // 0xd5ff0
    bool __cdecl ExecuteW(unsigned __int64, int, void *);  // 0xd6070
    bool __cdecl ResumeW(unsigned __int64, int, int, void *);  // 0xd6100
    bool __cdecl SetExpireToken(::TransactionExpireChecker::ExpireToken *);  // 0xd61a0
private:
    bool __cdecl add(::GameTran *);  // 0xd6240
    void __cdecl remove(unsigned __int64);  // 0xd63a0
    ::GameTran * __cdecl find(unsigned __int64);  // 0xd6460
};

// PDB: class SessionTran, size 0x58, base GameTran.
class SessionTran : public GameTran
{
public:
    __cdecl SessionTran(::Session *);  // 0x1105e0
    virtual __cdecl ~SessionTran(void);  // 0x110670
private:
    ::Session * _session;  // +80 (0x50)
};
static_assert(sizeof(SessionTran) == 0x58, "sizeof SessionTran");

<<<<<<< HEAD
// PDB: UserTran, size 0x58.
=======
// PDB: class UserTran, size 0x58, base GameTran.
>>>>>>> refs/author/pre-rebase/2
class UserTran : public GameTran
{
public:
    __cdecl UserTran(::User *);  // 0x27e60
    virtual __cdecl ~UserTran(void);  // 0x27ef0
<<<<<<< HEAD
    ::User * __cdecl GetUser(void) { return _user; }
private:
    ::User *_user;  // +0x50
=======
private:
    ::User * _user;  // +80 (0x50)
>>>>>>> refs/author/pre-rebase/2
};
static_assert(sizeof(UserTran) == 0x58, "sizeof UserTran");
