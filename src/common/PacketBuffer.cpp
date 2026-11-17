// PacketBuffer.obj (SmartCouponDaemon PDB).
#include "PacketBuffer.h"
#include <windows.h>
#include <stdarg.h>
#include <string.h>
#include <wchar.h>
#include <new>
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Log.h"
#include "MemoryManager.h"
#include "SysInfo.h"

static wchar_t const PACKETBUFFER_FILE[] = L"source\\PacketBuffer.cpp";

// Inlined crash macro.
#define PACKETBUFFER_ASSERT_CRASH(line)                                                  \
    do                                                                                   \
    {                                                                                    \
        Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(PACKETBUFFER_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\PacketBuffer.cpp", line, L"");                  \
    } while (0)

__declspec(thread) PacketBufferPool* PacketBufferAllocator::_Local = nullptr;
long long PacketBufferAllocator::Using = 0;
long long PacketBufferAllocator::Allocated = 0;
SpinLock PacketBufferAllocator::_Lock;
PacketBuffer* PacketBufferAllocator::_Pool = nullptr;
long long PacketBufferAllocator::_Count = 0;
PagePoolMemoryManager* PacketBufferAllocator::_Allocator = nullptr;

// 0x235B0 (SmartCouponDaemon) scalar deleting destructor
PacketBuffer::~PacketBuffer()
{
    sendSize = 0;
    sendBuffer = nullptr;
}

// 0x235E0 (SmartCouponDaemon)
// LTCG gives fmtCount as (unsigned long long)-1. The loop stops at the format terminator.
unsigned short PacketBuffer::Compose(char* buffer, unsigned int count, char const* format,
                                     unsigned long long fmtCount, char* args)
{
    char* p = buffer;
    char* end = buffer + count;
    for (unsigned long long i = 0; i < fmtCount && format[i] != '\0'; ++i)
    {
        switch (format[i])
        {
        case ';':
            break;
        case 'C':
        case 'E':
        case 'U':
        case 'h':
        case 'u':
            if (p + 2 > end)
                goto compose_overflow;
            *reinterpret_cast<short*>(p) = static_cast<short>(va_arg(args, int));
            p += 2;
            break;
        case 'K':
        case 'b':
        {
            void const* data = va_arg(args, void const*);
            unsigned short size = static_cast<unsigned short>(va_arg(args, int));
            char* next = p + size + 2;
            if (next > end)
                goto compose_overflow;
            *reinterpret_cast<short*>(p) = static_cast<short>(size);
            memcpy(p + 2, data, size);
            p = next;
            break;
        }
        case 'P':
        {
            if (p + 1 > end)
                goto compose_overflow;
            *p = static_cast<char>(va_arg(args, int));
            if (p + 3 > end)
                goto compose_overflow;
            *reinterpret_cast<short*>(p + 1) = static_cast<short>(va_arg(args, int));
            void const* data = va_arg(args, void const*);
            unsigned short size = static_cast<unsigned short>(va_arg(args, int));
            char* next = p + 5 + size;
            if (next > end)
                goto compose_overflow;
            *reinterpret_cast<short*>(p + 3) = static_cast<short>(size);
            memcpy(p + 5, data, size);
            p = next;
            break;
        }
        case 'Q':
        case 'c':
            if (p + 1 > end)
                goto compose_overflow;
            *p++ = static_cast<char>(va_arg(args, int));
            break;
        case 'd':
        case 'i':
            if (p + 4 > end)
                goto compose_overflow;
            *reinterpret_cast<int*>(p) = va_arg(args, int);
            p += 4;
            break;
        case 'f':
            if (p + 4 > end)
                goto compose_overflow;
            *reinterpret_cast<float*>(p) = static_cast<float>(va_arg(args, double));
            p += 4;
            break;
        case 'o':
        {
            if (p + 16 > end)
                goto compose_overflow;
            long long const* src = va_arg(args, long long const*);
            reinterpret_cast<long long*>(p)[0] = src[0];
            reinterpret_cast<long long*>(p)[1] = src[1];
            p += 16;
            break;
        }
        case 'q':
            if (p + 8 > end)
                goto compose_overflow;
            *reinterpret_cast<long long*>(p) = va_arg(args, long long);
            p += 8;
            break;
        case 's':
        {
            wchar_t const* str = va_arg(args, wchar_t const*);
            short len = static_cast<short>(wcslen(str));
            size_t size = 2 * static_cast<size_t>(len);
            char* next = p + size + 2;
            if (next > end)
                goto compose_overflow;
            *reinterpret_cast<short*>(p) = len;
            memcpy(p + 2, str, size);
            p = next;
            break;
        }
        default:
            Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 177, L"Unknown type %C", format[i]);
            PACKETBUFFER_ASSERT_CRASH(178);
            return 0;
        }
    }
    return static_cast<unsigned short>(p - buffer);

compose_overflow:
    Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 188, L"Compose overflow.");
    PACKETBUFFER_ASSERT_CRASH(189);
    return 0;
}

// 0x23760 (LobbyGate)
// Checks one format item. Each argument slot is 8 bytes. Returns 5000 on overflow.
unsigned short PacketBuffer::CheckCompose(char* buffer, unsigned int count, char const* format, char** args)
{
    char* end = &buffer[count];
    if (strlen(format) == 0)
    {
        Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 203, L"[PacketBuffer] %s, invalid format", L"PacketBuffer::CheckCompose");
        return 0;
    }
    char type = *format;
    char* a = *args;
    switch (type)
    {
    case ';':
        Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 325, L"[PacketBuffer] %s, Repeat End type %C",
                   L"PacketBuffer::CheckCompose", type);
        return 0;
    case 'C':
    case 'E':
    case 'U':
    case 'h':
    case 'u':
        if (buffer + 2 > end)
            goto compose_overflow;
        *args = a + 8;
        return 2;
    case 'K':
    case 'b':
    {
        short size = *reinterpret_cast<short*>(a + 8);
        if (&buffer[size + 2] > end)
            goto compose_overflow;
        *args = a + 16;
        return static_cast<unsigned short>(size + 2);
    }
    case 'P':
    {
        if (buffer + 1 > end)
            goto compose_overflow;
        if (buffer + 2 > end)
            goto compose_overflow;
        short size = *reinterpret_cast<short*>(a + 24);
        if (&buffer[size + 2] > end)
            goto compose_overflow;
        *args = a + 32;
        return static_cast<unsigned short>(size + 5);
    }
    case 'Q':
    case 'c':
        if (buffer + 1 > end)
            goto compose_overflow;
        *args = a + 8;
        return 1;
    case 'd':
    case 'f':
    case 'i':
        if (buffer + 4 > end)
            goto compose_overflow;
        *args = a + 8;
        return 4;
    case 'o':
        if (buffer + 16 > end)
            goto compose_overflow;
        *args = a + 8;
        return 16;
    case 'q':
        if (buffer + 8 > end)
            goto compose_overflow;
        *args = a + 8;
        return 8;
    case 's':
    {
        short len = static_cast<short>(wcslen(*reinterpret_cast<wchar_t const**>(a)));
        if (&buffer[2 * len + 2] > end)
            goto compose_overflow;
        *args = a + 8;
        return static_cast<unsigned short>(2 * (len + 1));
    }
    default:
        Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 331, L"[PacketBuffer] %s, Unknown type %C",
                   L"PacketBuffer::CheckCompose", type);
        PACKETBUFFER_ASSERT_CRASH(332);
        return 0;
    }

compose_overflow:
    Log::Write(Log::LT_DEBUG, PACKETBUFFER_FILE, 342, L"[PacketBuffer] %s, Compose overflow", L"PacketBuffer::CheckCompose");
    return 5000;
}

// 0x23950 (SmartCouponDaemon)
// LTCG gives fmtCount as (unsigned long long)-1. The loop stops at the format terminator.
unsigned short PacketBuffer::Decompose(char const* buffer, unsigned int count, char const* format,
                                       unsigned long long fmtCount, char* args)
{
    char const* p = buffer;
    char const* end = buffer + count;
    for (unsigned long long i = 0; i < fmtCount && format[i] != '\0'; ++i)
    {
        switch (format[i])
        {
        case ';':
            break;
        case 'C':
        case 'E':
        case 'U':
        case 'h':
        case 'u':
            if (end < p + 2)
                goto decompose_overflow;
            *va_arg(args, short*) = *reinterpret_cast<short const*>(p);
            p += 2;
            break;
        case 'K':
        case 'b':
        {
            if (end < p + 2)
                goto decompose_overflow;
            char const* src = p + 2;
            short size = *reinterpret_cast<short const*>(p);
            void* dest = va_arg(args, void*);
            short* destSize = va_arg(args, short*);
            if (size < 0)
            {
                Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 453, L"src size underflow");
                return 0;
            }
            if (*destSize < size)
            {
                Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 458, L"not enough buffer");
                return 0;
            }
            p += size + 2;
            if (end < p)
            {
                Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 463, L"buffer overflow");
                return 0;
            }
            memcpy(dest, src, size);
            *destSize = size;
            break;
        }
        case 'P':
        {
            if (end < p + 5)
                goto decompose_overflow;
            char type = *p;
            short propCount = *reinterpret_cast<short const*>(p + 1);
            short size = *reinterpret_cast<short const*>(p + 3);
            char* destType = va_arg(args, char*);
            short* destCount = va_arg(args, short*);
            void* dest = va_arg(args, void*);
            short* destSize = va_arg(args, short*);
            if (type <= 0)
            {
                Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 489, L"invalid property type id");
                return 0;
            }
            if (propCount < 0)
            {
                Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 494, L"src count underflow");
                return 0;
            }
            if (size < 0)
            {
                Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 499, L"src size underflow");
                return 0;
            }
            if (*destSize < size)
            {
                Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 504, L"not enough buffer");
                return 0;
            }
            // BUG: 0x23950 (SmartCouponDaemon) the check uses p+size+4, but the data ends at p+size+5.
            if (end < p + size + 4)
            {
                Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 509, L"buffer overflow");
                return 0;
            }
            memcpy(dest, p + 5, size);
            *destType = type;
            *destSize = size;
            p = p + size + 5;
            *destCount = propCount;
            break;
        }
        case 'Q':
        case 'c':
            if (end < p + 1)
                goto decompose_overflow;
            *va_arg(args, char*) = *p++;
            break;
        case 'd':
        case 'f':
        case 'i':
            if (end < p + 4)
                goto decompose_overflow;
            *va_arg(args, int*) = *reinterpret_cast<int const*>(p);
            p += 4;
            break;
        case 'o':
        {
            if (end < p + 16)
                goto decompose_overflow;
            long long* dest = va_arg(args, long long*);
            dest[0] = reinterpret_cast<long long const*>(p)[0];
            dest[1] = reinterpret_cast<long long const*>(p)[1];
            p += 16;
            break;
        }
        case 'q':
            if (end < p + 8)
                goto decompose_overflow;
            *va_arg(args, long long*) = *reinterpret_cast<long long const*>(p);
            p += 8;
            break;
        case 's':
        {
            if (end < p + 2)
                goto decompose_overflow;
            char const* src = p + 2;
            short len = *reinterpret_cast<short const*>(p);
            wchar_t* dest = va_arg(args, wchar_t*);
            short destSize = static_cast<short>(va_arg(args, int));
            *dest = L'\0';
            if (len < 0)
            {
                Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 421, L"length underflow");
                return 0;
            }
            if (destSize < len + 1)
            {
                Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 426, L"string buffer is too small");
                return 0;
            }
            p += len * 2 + 2;
            if (end < p)
            {
                Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 431, L"length overflow");
                return 0;
            }
            memcpy(dest, src, 2 * static_cast<size_t>(len));
            dest[len] = L'\0';
            break;
        }
        default:
            Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 556, L"Unknown type %C", format[i]);
            return 0;
        }
    }
    return static_cast<unsigned short>(p - buffer);

decompose_overflow:
    Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 566, L"Decompose overflow.");
    return 0;
}

// 0x23D90 (SmartCouponDaemon)
bool PacketBuffer::encrypt(PacketCrypt* crypt, Security3rdParty* crypt3rd)
{
    if (crypt == nullptr)
        return true;
    int encBufSize = 0;
    bool with3rdParty = false;
    for (PacketBuffer* pktbuf = this; pktbuf != nullptr; pktbuf = pktbuf->Next)
    {
        if (pktbuf->sendBuffer != nullptr)
            continue;
        encBufSize = 4002;
        int size = *reinterpret_cast<short*>(&pktbuf->Buffer[8]);
        if (crypt3rd != nullptr)
        {
            int size3rd = size - 2;
            if (crypt3rd->Encrypt(reinterpret_cast<unsigned char*>(&pktbuf->Buffer[10]), &size3rd, &with3rdParty) ==
                Security3rdParty::S3ERR_SUCCESS)
                size = size3rd + 2;
        }
        PacketCrypt::ErrCode error =
            crypt->Encrypt(reinterpret_cast<unsigned char*>(&pktbuf->Buffer[6]), &encBufSize, size, with3rdParty);
        if (error != PacketCrypt::SPCE_NO_ERROR)
        {
            Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 1221, L"PacketBuffer, cannot ecrypt packet, error-code:%d", error);
            return false;
        }
        pktbuf->sendBuffer = &pktbuf->Buffer[6];
        pktbuf->sendSize = encBufSize;
    }
    return true;
}

// 0x23EA0 (SmartCouponDaemon)
void PacketBuffer::deallocate_me(void* ptr, wchar_t const* file, int line)
{
    PacketBufferAllocator::_Local->deallocate(this);
}

// 0x23EC0 (SmartCouponDaemon)
PacketBuffer* PacketBufferPool::allocate()
{
    if (_pool == nullptr)
    {
        if (_count != 0)
        {
            Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 1285,
                       L"== CRASH == [PacketBuffer], _list는 NULL이지만 _count(%d)는 0이 아닙니다.", _count);
            AlertSender::Write(PACKETBUFFER_FILE, 1285,
                               L"== CRASH == [PacketBuffer], _list는 NULL이지만 _count(%d)는 0이 아닙니다.", _count);
        }
        // PDB: allocate has 1 argument. LTCG removed it: allocate (SmartCouponDaemon 0x241b0) does not read ecx and uses 0x10 (0x241e0, 0x24238).
        _pool = PacketBufferAllocator::allocate(16);
        _count = 16;
    }
    PacketBuffer* pktbuf = _pool;
    --_count;
    _pool = pktbuf->Next;
    pktbuf->Next = nullptr;
    InterlockedIncrement(&pktbuf->_ref);
    new (pktbuf) PacketBuffer();
    InterlockedIncrement64(&PacketBufferAllocator::Using);
    return pktbuf;
}

// 0x23F90 (SmartCouponDaemon)
void PacketBufferPool::deallocate(PacketBuffer* pktbuf)
{
    InterlockedDecrement64(&PacketBufferAllocator::Using);
    pktbuf->~PacketBuffer();
    pktbuf->Next = _pool;
    _pool = pktbuf;
    if (++_count > 64)
    {
        PacketBuffer* last = nullptr;
        PacketBuffer* head = pktbuf;
        for (int i = 0; i < _count / 2; ++i)
        {
            last = head;
            head = head->Next;
        }
        last->Next = nullptr;
        _count /= 2;

        int count = 1;
        PacketBuffer* tail = head;
        while (tail->Next != nullptr)
        {
            tail = tail->Next;
            ++count;
        }

        PacketBufferAllocator::_Lock.Enter();
        PacketBufferAllocator::_Count += count;
        tail->Next = PacketBufferAllocator::_Pool;
        PacketBufferAllocator::_Pool = head;
        PacketBufferAllocator::_Lock.Leave();
    }
}

// 0x24090 (SmartCouponDaemon)
void PacketBufferAllocator::Initialize()
{
    if (_Local == nullptr)
    {
        void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(PacketBufferPool), PACKETBUFFER_FILE, 1350);
        _Local = memory != nullptr ? new (memory) PacketBufferPool() : nullptr;
    }
    initAllocator();
}

// 0x24100 (SmartCouponDaemon)
void PacketBufferAllocator::initAllocator()
{
    if (_Allocator == nullptr)
    {
        unsigned long long size = 1024;
        while (size < sizeof(PacketBuffer))
            size *= 2;
        void* memory = BaseMemoryManager::_Instance.Alloc(sizeof(PagePoolMemoryManager), PACKETBUFFER_FILE, 1374);
        _Allocator = memory != nullptr ? new (memory) PagePoolMemoryManager(SysInfo::MemnoryAllocationGranularity()) : nullptr;
        // BUG: 0x24100 (SmartCouponDaemon) no null check of _Allocator before Initialize. No lock.
        _Allocator->Initialize(size);
    }
}

// 0x241B0 (SmartCouponDaemon)
PacketBuffer* PacketBufferAllocator::allocate(int count)
{
    int taken = 0;
    PacketBuffer* last = nullptr;
    _Lock.Enter();
    PacketBuffer* head = _Pool;
    PacketBuffer* node = _Pool;
    while (node != nullptr && taken < count)
    {
        last = node;
        node = node->Next;
        ++taken;
    }
    _Pool = node;
    _Count -= taken;
    if (node != nullptr)
        last->Next = nullptr;
    _Lock.Leave();

    for (int i = taken; i < count; ++i)
    {
        void* memory = _Allocator->Alloc();
        PacketBuffer* pktbuf = memory != nullptr ? new (memory) PacketBuffer() : nullptr;
        // BUG: 0x241B0 (SmartCouponDaemon) pktbuf can be null here.
        InterlockedDecrement(&pktbuf->_ref);
        if (last != nullptr)
            last->Next = pktbuf;
        else
            head = pktbuf;
        last = pktbuf;
        InterlockedIncrement64(&Allocated);
    }
    return head;
}

// PostOfficeDaemon PDB: text packets.

// PDB S_CONSTANT HEX_PREFIX_LEN (const int, 2) and S_LDATA32 HEX_PREFIXES (const wchar_t*[3]).
static int const HEX_PREFIX_LEN = 2;
static wchar_t const* HEX_PREFIXES[3] = {L"0x", L"0X", nullptr};

// 0x2F530 (PostOfficeDaemon)
unsigned short PacketBuffer::ComposeText(char* buffer, unsigned int count, char const* format,
                                         unsigned long long fmtCount, char* args)
{
    wchar_t* start = reinterpret_cast<wchar_t*>(buffer + 2);
    char* end = &buffer[count];
    wchar_t* cur = start;
    for (char const* f = format; *f != 0; ++f)
    {
        if (static_cast<unsigned long long>(f - format) == fmtCount)
            break;
        int written;
        size_t room = static_cast<size_t>((end - reinterpret_cast<char*>(cur)) >> 1);
        switch (*f)
        {
        case ';':
            continue;
        case 'C':
        case 'h':
            written = swprintf_s(cur, room, L"%d ", static_cast<int>(static_cast<short>(va_arg(args, int))));
            break;
        case 'c':
            written = swprintf_s(cur, room, L"%d ", static_cast<int>(static_cast<char>(va_arg(args, int))));
            break;
        case 'd':
        case 'i':
            written = swprintf_s(cur, room, L"%d ", va_arg(args, int));
            break;
        case 'f':
            written = swprintf_s(cur, room, L"%f ", static_cast<double>(static_cast<float>(va_arg(args, double))));
            break;
        case 'q':
            written = swprintf_s(cur, room, L"%I64d ", va_arg(args, long long));
            break;
        case 's':
            written = swprintf_s(cur, room, L"%s ", va_arg(args, wchar_t*));
            break;
        default:
            Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 764, L"Unknown type %C", static_cast<int>(*f));
            PACKETBUFFER_ASSERT_CRASH(765);
            return 0;
        }
        if (written < 0)
        {
            Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 783, L"Compose Text overflow.");
            PACKETBUFFER_ASSERT_CRASH(784);
            return 0;
        }
        cur += written;
    }
    // The last space is removed from the text length.
    if (cur == start)
        *reinterpret_cast<short*>(buffer) = 0;
    else
        *reinterpret_cast<short*>(buffer) = static_cast<short>((reinterpret_cast<char*>(--cur) - buffer) >> 1);
    return static_cast<unsigned short>(reinterpret_cast<char*>(cur) - buffer);
}

// 0x2F7D0 (PostOfficeDaemon)
bool isHex(wchar_t const* num)
{
    for (long long i = 0; HEX_PREFIXES[i] != nullptr; ++i)
    {
        if (wcsncmp(num, HEX_PREFIXES[i], HEX_PREFIX_LEN) == 0)
            return true;
    }
    return false;
}

// 0x2F850 (PostOfficeDaemon)
int parseHexInt(wchar_t const* str, wchar_t const* end, long long& value)
{
    if (str >= end)
        return -1;
    wchar_t const* p = str + 2;
    value = 0;
    while (*p != 0 && *p != L' ')
    {
        if (p >= end)
            break;
        value *= 16;
        int digit;
        if (iswdigit(*p))
            digit = *p - L'0';
        else
        {
            if (towupper(*p) < L'A' || towupper(*p) > L'F')
                return -1;
            digit = towupper(*p) - 55;
        }
        ++p;
        value += digit;
    }
    if (*p == L' ')
        ++p;
    return static_cast<int>(p - str);
}

// 0x2F940 (PostOfficeDaemon)
int parseDecInt(wchar_t const* str, wchar_t const* end, long long& value)
{
    if (str >= end)
        return -1;
    wchar_t const* p = str;
    int sign = 1;
    if (*str == L'-')
    {
        sign = -1;
        ++p;
    }
    else if (*str == L'+')
        ++p;
    value = 0;
    while (*p != 0 && *p != L' ')
    {
        if (p >= end)
            break;
        if (!iswdigit(*p))
            return -1;
        int ch = *p++;
        value = ch - L'0' + 10 * value;
    }
    if (*p == L' ')
        ++p;
    value *= sign;
    return static_cast<int>(p - str);
}

// 0x2FA20 (PostOfficeDaemon)
// The code never returns -2.
int parseString(wchar_t const* str, wchar_t const* end, wchar_t* buffer, short count)
{
    bool quoted = false;
    wchar_t const* p = str;
    wchar_t* last = &buffer[count];
    if (str >= end)
        return -1;
    if (*str == L'"')
    {
        p = str + 1;
        quoted = true;
    }
    while (*p != 0 && p < end)
    {
        wchar_t ch = *p;
        if (quoted)
        {
            if (ch == L'"')
            {
                ++p;
                break;
            }
        }
        else if (ch == L' ')
            break;
        *buffer++ = ch;
        ++p;
        if (buffer >= last)
            return -1;
    }
    *buffer = 0;
    if (*p == L' ')
        ++p;
    return static_cast<int>(p - str);
}

// 0x2FAB0 (PostOfficeDaemon)
// LTCG removed count (not used) and fmtCount (always -1).
unsigned short PacketBuffer::DecomposeText(char const* buffer, unsigned int count, char const* format,
                                           unsigned long long fmtCount, char* args)
{
    wchar_t const* cur = reinterpret_cast<wchar_t const*>(buffer + 2);
    wchar_t const* end =
        reinterpret_cast<wchar_t const*>(&buffer[2 * *reinterpret_cast<short const*>(buffer) + 2]);
    for (char const* f = format; *f != 0; ++f)
    {
        if (static_cast<unsigned long long>(f - format) == fmtCount)
            break;
        long long v;
        int n;
        int errorLine;
        switch (*f)
        {
        case 'C':
        case 'h':
            if (cur >= end)
                goto decompose_text_overflow;
            n = isHex(cur) ? parseHexInt(cur, end, v) : parseDecInt(cur, end, v);
            if (n < 0)
                goto decompose_text_overflow;
            cur += n;
            if (static_cast<unsigned long long>(v + 0x8000) > 0xFFFF)
            {
                errorLine = 1038;
                goto decompose_text_range;
            }
            *va_arg(args, short*) = static_cast<short>(v);
            continue;
        case 'c':
            if (cur >= end)
                goto decompose_text_overflow;
            n = isHex(cur) ? parseHexInt(cur, end, v) : parseDecInt(cur, end, v);
            if (n < 0)
                goto decompose_text_overflow;
            cur += n;
            if (static_cast<unsigned long long>(v + 128) > 0xFF)
            {
                errorLine = 1030;
                goto decompose_text_range;
            }
            *va_arg(args, char*) = static_cast<char>(v);
            continue;
        case 'd':
        case 'i':
            if (cur >= end)
                goto decompose_text_overflow;
            n = isHex(cur) ? parseHexInt(cur, end, v) : parseDecInt(cur, end, v);
            if (n < 0)
                goto decompose_text_overflow;
            cur += n;
            if (static_cast<unsigned long long>(v + 0x80000000LL) > 0xFFFFFFFF)
            {
                errorLine = 1046;
                goto decompose_text_range;
            }
            *va_arg(args, int*) = static_cast<int>(v);
            continue;
        case 'q':
            if (cur >= end)
                goto decompose_text_overflow;
            n = isHex(cur) ? parseHexInt(cur, end, v) : parseDecInt(cur, end, v);
            if (n < 0)
                goto decompose_text_overflow;
            cur += n;
            *va_arg(args, long long*) = v;
            continue;
        case 's':
        {
            wchar_t* dst = va_arg(args, wchar_t*);
            short size = static_cast<short>(va_arg(args, int));
            n = parseString(cur, end, dst, size);
            if (n == -2)
            {
                Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 1084, L"Decompose Text, invalid string");
                return 0;
            }
            if (n < 0)
                goto decompose_text_overflow;
            cur += n;
            continue;
        }
        default:
            Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 1143, L"Unknown type %C", static_cast<int>(*f));
            return 0;
        }
    decompose_text_range:
        // BUG: The call (0x2FD16) gives only v (rcx at 0x2FD01, stack +0x20). %C gets the value. %I64d gets no argument.
        Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, errorLine, L"Decompose Text, format('%C'), value(%I64d)", v);
        return 0;
    }
    return static_cast<unsigned short>(reinterpret_cast<char const*>(cur) - buffer);

decompose_text_overflow:
    Log::Write(Log::LT_ERROR, PACKETBUFFER_FILE, 1153, L"Decompose Text overflow.");
    return 0;
}
