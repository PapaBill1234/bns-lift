// TextConsole.obj (CacheGate PDB).
#include "TextConsole.h"
#include "LogBuffer.h"
#include "Daemon.h"
#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>

unsigned short TextConsole::COLOR_TABLE[8] = {
    0x0C, 0x00, 0x08, 0x02, 0x09, 0x00, 0x00, 0x00,
};

// 0x13fe0
TextConsole::TextConsole()
{
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    originalAttr = 0;
    originalTitle[0] = 0;
    CONSOLE_SCREEN_BUFFER_INFO sb;
    memset(&sb, 0, sizeof(sb));
    GetConsoleScreenBufferInfo(stdoutHandle, &sb);
    originalAttr = sb.wAttributes;
    COLOR_TABLE[1] = sb.wAttributes;
    // The Wine headers use char16_t for WCHAR; the cast is for the toolchain only.
    GetWindowTextW(GetConsoleWindow(), (LPWSTR)originalTitle, 1024);
}

// 0x140a0 (scalar deleting destructor; the body is inline)
TextConsole::~TextConsole()
{
    SetConsoleTextAttribute(stdoutHandle, originalAttr);
}

// 0x140f0
int __stdcall TextConsoleControlHandler(unsigned long ctrlCode)
{
    if (Daemon::Instance != nullptr)
    {
        Console* console = Daemon::Instance->console;
        if (console != nullptr && console->controlHandler(ctrlCode))
            return TRUE;
    }
    return FALSE;
}

// 0x14130
bool TextConsole::Open()
{
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)TextConsoleControlHandler, TRUE);
    return true;
}

// 0x14150
void TextConsole::Close()
{
    SetConsoleTextAttribute(stdoutHandle, originalAttr);
    SetWindowTextW(GetConsoleWindow(), (LPCWSTR)originalTitle);
}

// 0x16f50 (folded: empty function)
void TextConsole::SetState(int state)
{
}

// 0x14190
void TextConsole::WriteStartLog(int type, wchar_t const* format, ...)
{
    va_list args;
    va_start(args, format);
    if (type == 0)
    {
        vwprintf(format, args);
        wprintf(L"\n");
    }
    va_end(args);
}

// 0x13fd0 (folded with WindowConsole::WriteStatusLog: empty function)
void TextConsole::WriteStatusLog(wchar_t const* format, ...)
{
}

// 0x141d0
bool TextConsole::controlHandler(unsigned long ctrlCode)
{
    if (ctrlCode > CTRL_CLOSE_EVENT)
        return false;
    if (Daemon::Instance != nullptr && Daemon::Instance->EndEvent.Event != nullptr)
        SetEvent(Daemon::Instance->EndEvent.Event);
    return true;
}

// 0x14210
void TextConsole::setTitle(wchar_t const* title)
{
    SetWindowTextW(GetConsoleWindow(), (LPCWSTR)title);
}

// 0x14240
void TextConsole::write(LogBuffer const* logbuf)
{
    DWORD written = 0;
    for (LogBuffer const* node = logbuf; node != nullptr;
         node = (_bufferNodePos >= 0) ? node->_next[_bufferNodePos] : nullptr)
    {
        if (node->_flush)
            continue;
        // BUG: 0x14240 COLOR_TABLE has 8 entries; a user log type (6..10) reads past the end.
        SetConsoleTextAttribute(stdoutHandle, COLOR_TABLE[node->_type]);
        WriteConsoleW(stdoutHandle, node->_log, (DWORD)wcslen(node->_log), &written, nullptr);
        WriteConsoleW(stdoutHandle, L"\n", 1, &written, nullptr);
    }
    SetConsoleTextAttribute(stdoutHandle, originalAttr);
}

// 0x14330
void TextConsole::Write(Log::Type type, wchar_t const* file, int line, wchar_t const* format, char* args)
{
    SetConsoleTextAttribute(stdoutHandle, COLOR_TABLE[type]);
    vwprintf(format, args);
    wprintf(L"\n");
    SetConsoleTextAttribute(stdoutHandle, originalAttr);
}
