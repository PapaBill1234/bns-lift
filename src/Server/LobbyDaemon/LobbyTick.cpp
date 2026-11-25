// LobbyTick.obj (LobbyDaemon 2019 + PDB).
#include "PlacementNew.h"
#include "LobbyTick.h"
#include "Daemon.h"
#include "Log.h"
#include "Memory.h"
#include "Network.h"

#pragma comment(linker, "/INCLUDE:??1LobbyTick@@UEAA@XZ")  // LIFT: keep until the caller is lifted (0x5a610).
#pragma comment(linker, "/INCLUDE:?Add@LobbyTick@@QEAA_NPEAVListener@1@@Z")  // LIFT: keep until the caller is lifted (0x5a6e0).
#pragma comment(linker, "/INCLUDE:?HandleEvent@LobbyTick@@UEAA_NPEAUEventContext@@K@Z")  // LIFT: keep until the caller is lifted (0x5a7f0).

// 0x5a610
LobbyTick::~LobbyTick()
{
    while (RefCntListNode* head = _list.Popfront())
        head->removeReferenceCount(L"LobbyTick.cpp", 25);
}

// 0x5a6e0
bool LobbyTick::Add(Listener* listener)
{
    if (listener == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyTick.cpp", 54, L"[tick],add fail;invalid parameter");
        return false;
    }
    _lock.Enter();
    bool result = _list.Pushback(listener);
    _lock.Leave();
    if (result)
        listener->SetListen(true);
    return result;
}

// 0x5a770
// LIFT: the event handler calls Remove out of line (0x5aa20).
__declspec(noinline) bool LobbyTick::Remove(Listener* listener)
{
    if (listener == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyTick.cpp", 73, L"[tick],remove fail;invalid parameter");
        return false;
    }
    _lock.Enter();
    bool result = _list.Remove(listener);
    _lock.Leave();
    return result;
}

// 0x5a7f0
bool LobbyTick::HandleEvent(EventContext*, unsigned long)
{
    if (_run)
    {
        process();
        Daemon::Instance->AddTimer(_period, this);
    }
    return true;
}

// 0x5a830
// LIFT: the timer handler calls process out of line (0x5a7f0).
__declspec(noinline) void LobbyTick::process()
{
    long long elapsed = GetTickCount64() - Daemon::Instance->StartSystemTick64;
    _lock.Enter();
    for (Listener* listener = static_cast<Listener*>(_list.Begin()); listener != nullptr;
         listener = static_cast<Listener*>(listener->NextNode()))
    {
        if (listener->IsListen())
        {
            listener->SetListen(false);
            void* mem = Memory::_Manager[2]->Alloc(sizeof(LobbyTickEvent), L"LobbyTick.cpp", 105);
            LobbyTickEvent* event = mem != nullptr ? ::new (mem) LobbyTickEvent(this, listener, elapsed) : nullptr;
            PostQueuedCompletionStatus(Network::iocpHandle(), 0, reinterpret_cast<ULONG_PTR>(event), nullptr);
        }
    }
    _lock.Leave();
}

// 0x5a900
// LIFT: process calls the constructor out of line (0x5a830).
__declspec(noinline) LobbyTickEvent::LobbyTickEvent(LobbyTick* owner, LobbyTick::Listener* listener, long long elapsed)
    : _owner(owner), _listener(listener), _elapsed(elapsed)
{
    if (_owner != nullptr)
        _owner->addReferenceCount(false, L"LobbyTick.cpp", 123);
    if (_listener != nullptr)
        _listener->addReferenceCount(false, L"LobbyTick.cpp", 126);
}

// 0x5a9b0
// LIFT: the scalar deleting destructor calls the destructor out of line (0x5a990).
__declspec(noinline) LobbyTickEvent::~LobbyTickEvent()
{
    if (_owner != nullptr)
        _owner->removeReferenceCount(L"LobbyTick.cpp", 132);
    if (_listener != nullptr)
        _listener->removeReferenceCount(L"LobbyTick.cpp", 135);
}

// 0x5aa20
bool LobbyTickEvent::HandleEvent(EventContext*, unsigned long)
{
    if (_listener != nullptr)
    {
        if (_listener->Tick(_elapsed))
            _listener->SetListen(true);
        else if (_owner != nullptr)
            _owner->Remove(_listener);
    }
    removeReferenceCount(L"LobbyTick.cpp", 149);
    return true;
}
