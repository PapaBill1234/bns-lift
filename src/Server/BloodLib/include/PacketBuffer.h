// PacketBuffer.obj (SmartCouponDaemon PDB): PacketBuffer, PacketBufferPool, PacketBufferAllocator.
// Layouts from include/pdb/CacheGate/types.h. The SmartCouponDaemon PDB has the same layouts.
#pragma once
#include <stddef.h>
#include "RefCntObject.h"
#include "Lock.h"

class PagePoolMemoryManager;

// PDB global typedef (S_UDT ExternalCompressFunc, type 0x11FD, LobbyGate).
typedef int (*ExternalCompressFunc)(unsigned char* dest, int* destLen, unsigned char const* src, int srcLen,
                                    unsigned char const* dict, int dictSize);

class PacketCrypt
{
public:
    enum ErrCode
    {
        SPCE_NO_ERROR = 0,
        UNKOWN_ERROR = 1,
        NO_RESULT = 2,
        NOT_INITIALIZED = 3,
        ALREADY_INITIALIZED = 4,
        INVALID_PARAM = 5,
        FAILED_SETUP_CRYPTO = 6,
        FAILED_INVALID_CODE = 7,
        FAILED_TOO_LARGE_PACKET = 8,
        FAILED_INSUFFIENT_BUFFER = 9,
        FAILED_NOT_COMPLETE_PACKET = 10,
        FAILED_KEYGEN = 11,
        FAILED_ENCRYPT = 12,
        FAILED_DECRYPT = 13,
        ALREADY_CHANGE_KEY = 14,
        FAILED_SET_EXT_COMP_FUNC = 15,
        FAILED_COMP = 16,
    };
    enum Code
    {
        NONE = 0,
        INITIAL_KEY = 4,
        CLI_HANDSHAKE_KEY = 5,
        SESSION_KEY_1 = 8,
        SESSION_KEY_2 = 9,
        SESSION_KEY_1_AND_3RD_PARTY = 10,
        SESSION_KEY_2_AND_3RD_PARTY = 11,
        BROADCAST_LOCAL_KEY = 12,
        BROADCAST_LOCAL_KEY_COMPRESS = 13,
        BROADCAST_GLOBAL_KEY = 14,
    };
    enum Type
    {
        NO_CRYPT = 0x0,
        NO_HANDSHAKE_CRYPT = 0x1,
        HANDSHAKE_CRYPT = 0x2,
        SESSION_CRYPT = 0x3,
        BROADCAST_CRYPT = 0x4,
    };
    enum Param
    {
        PARAM_NONE = 0x0,
        PARAM_HANDSHAKE_FAIL = 0x1,
        PARAM_BROADCAST_LOCAL = 0x2,
        PARAM_BROADCAST_GLOBAL = 0x3,
        PARAM_BROADCAST_LOCAL_COMPRESS = 0x4,
    };
    enum Algorithm
    {
        ALGORITHM_DEFAULT = 0x0,
        ALGORITHM_TYPE1 = 0x1,
        ALGORITHM_TYPE2 = 0x2,
        ALGORITHM_TYPE3 = 0x3,
        ALGORITHM_TYPE4 = 0x4,
    };
    enum CompressType
    {
        COMPRESS_NONE = 0,
        COMPRESS_TYPE1 = 1,
        COMPRESS_TYPE2 = 2,
    };
    typedef unsigned char Byte;
    union Header
    {
        struct
        {
            unsigned short size : 12;
            unsigned short code : 4;
        } enc;
        struct
        {
            unsigned short size : 14;
            unsigned short code : 2;
        } plain;
    };

    static ErrCode Setup(int maxSize);  // 0x327E0 (PacketCrypt module, not in this card)
    static int InstanceSize(Type type, Algorithm algorithm);                                   // 0x4CC60 (LobbyGate, PacketCrypt module)
    static PacketCrypt* Create(Type type, Algorithm algorithm, unsigned char* buffer, int size);  // 0x4CCE0 (LobbyGate, PacketCrypt module)

protected:
    static int _MaxSize;

public:
    virtual int GetType() = 0;                                                        // slot 0
    virtual ErrCode SetEncryptParam(Param param) = 0;                                 // slot 1
    virtual ErrCode SetKey(unsigned char const* key, int keySize) = 0;                // slot 2
    virtual ErrCode GenerateKey(unsigned char* key1, int* size1, unsigned char* key2, int* size2) = 0;  // slot 3
    virtual ErrCode Encrypt(unsigned char* buffer, int* bufferSize, int size, bool with3rdParty) = 0;   // slot 4
    virtual ErrCode Decrypt(unsigned char* buffer, int size, int* outSize, bool* with3rdParty) = 0;     // slot 5
    virtual ErrCode SetExternalCompressFunc(ExternalCompressFunc func, unsigned char const* data, int size) = 0;  // slot 6
    virtual ~PacketCrypt() {}  // slot 7, vector deleting destructor (BroadcastPacketCrypt 0x4DBB0, LobbyGate)
};
static_assert(sizeof(PacketCrypt::Header) == 0x2, "sizeof PacketCrypt::Header");
static_assert(sizeof(PacketCrypt) == 0x8, "sizeof PacketCrypt");

class Security3rdParty
{
public:
    // PDB type 0x333E (CacheGate).
    enum ErrCode
    {
        S3ERR_SUCCESS = 0,
        S3ERR_FAILED = 1,
        S3ERR_NO_NEED_ENCRYPT = 2,
        S3ERR_INSUFFICIENT_BUFFER = 3,
    };

    virtual ~Security3rdParty() {}                                                      // slot 0
    virtual ErrCode Encrypt(unsigned char* buffer, int* size, bool* with3rdParty) = 0;  // slot 1
    virtual ErrCode Decrypt(unsigned char* buffer, int* size, bool with3rdParty) = 0;   // slot 2
};
static_assert(sizeof(Security3rdParty) == 0x8, "sizeof Security3rdParty");

class PacketBuffer : public RefCntObject
{
public:
    PacketBuffer()  // LIFT: inlined in PacketBufferPool::allocate (0x23EC0) and PacketBufferAllocator::allocate (0x241B0)
        : sendSize(0), sendBuffer(nullptr), Next(nullptr)
    {
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
    static unsigned short CheckCompose(char* buffer, unsigned int count, char const* format, char** args);
    static unsigned short Decompose(char const* buffer, unsigned int count, char const* format,
                                    unsigned long long fmtCount, char* args);
    // LIFT: The PostOfficeDaemon PDB has these as protected. Packet calls them, so they are public here.
    // LTCG removed fmtCount (always -1); the PDB signature is kept.
    static unsigned short ComposeText(char* buffer, unsigned int count, char const* format,
                                      unsigned long long fmtCount, char* args);       // 0x2F530 (PostOfficeDaemon)
    static unsigned short DecomposeText(char const* buffer, unsigned int count, char const* format,
                                        unsigned long long fmtCount, char* args);     // 0x2FAB0 (PostOfficeDaemon)
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
    PacketBufferPool() : _count(0), _pool(nullptr) {}  // LIFT: inlined in PacketBufferAllocator::Initialize (0x24090)
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
