// LogMedia.obj (SmartCouponDaemon PDB).
#include "LogMedia.h"
#include "LogBuffer.h"

// 0xAAD0 (SmartCouponDaemon) folded with other "return true" bodies.
bool LogMedia::Writable()
{
    return true;
}

// 0x1D7A0 (SmartCouponDaemon) folded with other "return 0" bodies.
wchar_t* LogMedia::GetLastFileName()
{
    return nullptr;
}

// 0x285B0 (SmartCouponDaemon)
// LIFT: noinline. The original calls it from its only caller Log::Add (CacheGate 0xa2c0) in all 4 exes.
// GameDaemon 0x69ed80: the same body. The GD addReferenceCount form (RefCntObject.cpp) keeps the bool in edx.
#if defined(LIFT_EXE_GD)
#pragma comment(linker, "/INCLUDE:?Add@LogMedia@@IEAAHPEAVLogBuffer@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#endif
__declspec(noinline) int LogMedia::Add(LogBuffer* logbuffer)
{
    int first = 0;
    logbuffer->addReferenceCount(false, L"source\\LogMedia.cpp", 40);
    _lock.Enter();
    if (_bufferNodePos >= 0)
        logbuffer->_next[_bufferNodePos] = nullptr;
    if (_tail != nullptr)
    {
        if (_bufferNodePos >= 0)
            _tail->_next[_bufferNodePos] = logbuffer;
    }
    else
    {
        _head = logbuffer;
        first = 1;
    }
    _tail = logbuffer;
    _lock.Leave();
    return first;
}

// 0x28650 (SmartCouponDaemon)
#if defined(_MSC_VER) && !defined(__clang__)
#pragma inline_depth(0)
#endif
void LogMedia::Write()
{
    _lock.Enter();
    LogBuffer* head = _head;
    _tail = nullptr;
    _head = nullptr;
    _lock.Leave();
    if (head == nullptr)
        return;

    write(head);
    do
    {
        LogBuffer* next;
        if (_bufferNodePos >= 0)
        {
            next = head->_next[_bufferNodePos];
            head->_next[_bufferNodePos] = nullptr;
        }
        else
        {
            next = nullptr;
        }
        head->removeReferenceCount(L"source\\LogMedia.cpp", 83);
        head = next;
    } while (head != nullptr);
}
#if defined(_MSC_VER) && !defined(__clang__)
#pragma inline_depth()
#endif
