// TextConsole.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
#pragma once
#include "Console.h"

class TextConsole : public Console
{
public:
    TextConsole();
    virtual ~TextConsole();
    virtual bool Open();
    virtual void Close();
    virtual void SetState(int state);
protected:
    virtual void WriteStartLog(int type, wchar_t const* format, ...);
    virtual void WriteStatusLog(wchar_t const* format, ...);
    virtual void Write(Log::Type type, wchar_t const* file, int line, wchar_t const* format, char* args);
    virtual bool controlHandler(unsigned long ctrlCode);
    virtual void setTitle(wchar_t const* title);
private:
    virtual void write(LogBuffer const* logbuf);

    // 0x140059110. Index 1 is set from the console in the constructor.
    static unsigned short COLOR_TABLE[8];

public:
    void* stdoutHandle;
    unsigned short originalAttr;
    wchar_t originalTitle[1024];
};
static_assert(sizeof(TextConsole) == 0x8C0, "sizeof TextConsole");
static_assert(offsetof(TextConsole, stdoutHandle) == 0xB0, "TextConsole::stdoutHandle");
static_assert(offsetof(TextConsole, originalAttr) == 0xB8, "TextConsole::originalAttr");
static_assert(offsetof(TextConsole, originalTitle) == 0xBA, "TextConsole::originalTitle");

int __stdcall TextConsoleControlHandler(unsigned long ctrlCode);
