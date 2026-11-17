// Console.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
#pragma once
#include "LogMedia.h"
#include "Log.h"

class Console : public LogMedia
{
public:
    Console();
    virtual ~Console() {}                    // inline (0x17600 folds the LogMedia part)
    virtual int GetType() const;             // slot 4
    virtual void Flush();                    // slot 2

    virtual bool Open() = 0;                 // slot 6
    virtual void Close() = 0;                // slot 7
    virtual void SetState(int state) = 0;    // slot 8
    virtual void WriteStartLog(int type, wchar_t const* format, ...) = 0;              // slot 9
    virtual void WriteStatusLog(wchar_t const* format, ...) = 0;                       // slot 10
    virtual void Write(Log::Type type, wchar_t const* file, int line,
                       wchar_t const* format, char* args) = 0;                         // slot 11
protected:  // PDB: controlHandler and setTitle are protected. The other methods are public.
    virtual bool controlHandler(unsigned long ctrlCode) = 0;                           // slot 12
    virtual void setTitle(wchar_t const* title);                                       // slot 13

public:
    void SetTitle(wchar_t const* def_title);

    // LIFT: access helpers. No PDB in the set has friend records (LF_FRIENDCLS count 0).
    // TextConsoleControlHandler (0x140f0) and WinServiceControlHandler (0x17630) call controlHandler.
    friend int __stdcall TextConsoleControlHandler(unsigned long ctrlCode);
    friend void WinServiceControlHandler(unsigned long ctrlCode);
};
static_assert(sizeof(Console) == 0xB0, "sizeof Console");
