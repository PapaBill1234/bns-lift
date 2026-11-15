// PacketBuffer.obj (SmartCouponDaemon PDB): PacketBuffer, PacketBufferPool, PacketBufferAllocator.
// Layouts from include/pdb/CacheGate/types.h. The SmartCouponDaemon PDB has the same layouts.
#pragma once
#include <stddef.h>
#include "RefCntObject.h"
#include "Lock.h"

class PagePoolMemoryManager;

class PacketCrypt
{
public:
    virtual int GetType() = 0;                                                     // slot 0
    virtual int SetEncryptParam(int param) = 0;                                    // slot 1
    virtual int SetKey(unsigned char const* key, int keySize) = 0;                 // slot 2
    virtual int GenerateKey(unsigned char* key1, int* size1, unsigned char* key2, int* size2) = 0;  // slot 3
    virtual int Encrypt(unsigned char* buffer, int* bufferSize, int size, bool with3rdParty) = 0;   // slot 4
    virtual int Decrypt(unsigned char* buffer, int size, int* outSize, bool* with3rdParty) = 0;     // slot 5
    virtual int SetExternalCompressFunc(void* func, unsigned char const* data, int size) = 0;        // slot 6
};
static_assert(sizeof(PacketCrypt) == 0x8, "sizeof PacketCrypt");

class Security3rdParty
{
public:
    virtual ~Security3rdParty() {}                                                  // slot 0
    virtual int Encrypt(unsigned char* buffer, int* size, bool* with3rdParty) = 0;  // slot 1
    virtual int Decrypt(unsigned char* buffer, int* size, bool with3rdParty) = 0;   // slot 2
};
static_assert(sizeof(Security3rdParty) == 0x8, "sizeof Security3rdParty");

class PacketBuffer : public RefCntObject
{
public:
    PacketBuffer()  // ❓ inlined in PacketBufferPool::allocate (0x23EC0) and PacketBufferAllocator::allocate (0x241B0)
        : sendSize(0), sendBuffer(nullptr), Next(nullptr)
    {
        _ref = 1;
        _history = nullptr;
        _tag = 1290;
        *reinterpret_cast<long long*>(&Buffer[0]) = 0;
        *reinterpret_cast<short*>(&Buffer[8]) = 0;
    }
    virtual ~PacketBuffer();
protected:
    virtual void deallocate_me(void* ptr, wchar_t const* file, int line);

public:
    static unsigned short Compose(char* buffer, unsigned int count, char const* format,
                                  unsigned long long fmtCount, char* args);
    static unsigned short Decompose(char const* buffer, unsigned int count, char const* format,
                                    unsigned long long fmtCount, char* args);
    bool encrypt(PacketCrypt* crypt, Security3rdParty* crypt3rd);

    char Buffer[4008];
    int sendSize;
    char const* sendBuffer;
    PacketBuffer* Next;
};
static_assert(sizeof(PacketBuffer) == 0xFD8, "sizeof PacketBuffer");
static_assert(offsetof(PacketBuffer, Buffer) == 0x18, "PacketBuffer::Buffer");
static_assert(offsetof(PacketBuffer, sendSize) == 0xFC0, "PacketBuffer::sendSize");
static_assert(offsetof(PacketBuffer, sendBuffer) == 0xFC8, "PacketBuffer::sendBuffer");
static_assert(offsetof(PacketBuffer, Next) == 0xFD0, "PacketBuffer::Next");

class PacketBufferPool
{
public:
    PacketBufferPool() : _count(0), _pool(nullptr) {}  // ❓ inlined in PacketBufferAllocator::Initialize (0x24090)
    PacketBuffer* allocate();
    void deallocate(PacketBuffer* pktbuf);

    int _count;
    PacketBuffer* _pool;
};
static_assert(sizeof(PacketBufferPool) == 0x10, "sizeof PacketBufferPool");

class PacketBufferAllocator
{
public:
    static void Initialize();

    // PDB S_GTHREAD32, .tls +0x28.
    static __declspec(thread) PacketBufferPool* _Local;
    static long long Using;
    static long long Allocated;

protected:
    static PacketBuffer* allocate(int count);

private:
    static void initAllocator();

    static SpinLock _Lock;
    static PacketBuffer* _Pool;
    static long long _Count;
    static PagePoolMemoryManager* _Allocator;

    friend class PacketBufferPool;
};
