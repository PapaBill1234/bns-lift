// Security.obj (LobbyGate PDB).
#include "Security.h"
#include <string.h>
#include <new>
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Crypto.h"
#include "Daemon.h"
#include "IoWorkerThread.h"
#include "Log.h"
#include "MemoryManager.h"

struct ZSTD_CCtx_s;
struct ZSTD_CDict_s;
// zstd is a vendor library (lift_zstd). zstd.h is not in the tree, thus the lift declares it here.
extern "C" size_t ZSTD_compress_usingCDict(ZSTD_CCtx_s* cctx, void* dst, size_t dstCapacity, void const* src,
                                           size_t srcSize, ZSTD_CDict_s const* cdict);

static wchar_t const SECURITY_FILE[] = L"source\\Security.cpp";

// Inlined crash macro.
#define SECURITY_ASSERT_CRASH(line)                                                  \
    do                                                                               \
    {                                                                                \
        Log::Write(Log::LT_ERROR, SECURITY_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(SECURITY_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\Security.cpp", line, L"");                  \
    } while (0)

// Inlined destroy of a PacketCrypt. The types 0, 2, 3 and 4 call the destructor (slot 7, flag 0).
static inline void destroyCrypt(PacketCrypt* crypt)
{
    int type = crypt->GetType();
    if (type == PacketCrypt::NO_CRYPT || type == PacketCrypt::HANDSHAKE_CRYPT ||
        type == PacketCrypt::SESSION_CRYPT || type == PacketCrypt::BROADCAST_CRYPT)
        crypt->~PacketCrypt();
}

// 0x22F50
int zstdPacketCompress(unsigned char* dest, int* destLen, unsigned char const* src, int srcLen,
                       unsigned char const* args)
{
    ZSTD_CCtx_s* cctx = IoWorker::ZstdCCtx;
    if (cctx == nullptr || (args != nullptr && *reinterpret_cast<unsigned short const*>(args) > srcLen))
        return PacketCrypt::FAILED_COMP;
    size_t result = ZSTD_compress_usingCDict(cctx, dest + 2, *destLen - 2, src, srcLen, Daemon::Instance->_zstdCDic);
    if (result > static_cast<size_t>(-120))  // Inlined ZSTD_isError.
        return PacketCrypt::FAILED_COMP;
    *reinterpret_cast<short*>(dest) = static_cast<short>(result);
    *destLen = static_cast<int>(result) + 2;
    return PacketCrypt::SPCE_NO_ERROR;
}

// 0x22FF0
BroadcastCrypt::~BroadcastCrypt()
{
    clear();
}

// 0x23000
bool BroadcastCrypt::Initialize(Type type, PacketCrypt::Algorithm algorithm, int broadcastCompressType)
{
    clear();
    unsigned char compressType = 1;  // ❓ local name
    int paramSize = 1;               // ❓ local name
    int keySize = 64;                // ❓ local name
    unsigned char keyBuf[64];        // ❓ local name

    // Inlined allocation of a BroadcastPacketCrypt (0x2840 bytes) with its Crypto object after it.
    int cryptoSize = Crypto::InstanceSize(static_cast<Crypto::Type>(2));
    int totalSize = 16 * ((cryptoSize + 15) / 16 + 0x284);
    char* mem = static_cast<char*>(BaseMemoryManager::_Instance.Alloc(totalSize, SECURITY_FILE, 91));
    BroadcastPacketCrypt* broadcast = nullptr;
    if (mem != nullptr && totalSize > 0 && totalSize >= static_cast<int>((((cryptoSize + 15) & ~15) + 0x2847) & ~15))
    {
        Crypto* crypto = Crypto::Create(mem + 0x2840, totalSize - 0x2840, static_cast<Crypto::Type>(2));
        broadcast = new (mem) BroadcastPacketCrypt(crypto);
    }
    crypt = broadcast;
    if (crypt == nullptr)
        SECURITY_ASSERT_CRASH(96);

    crypt->SetExternalCompressFunc(reinterpret_cast<void*>(&zstdPacketCompress), nullptr, 0);
    if (crypt->SetEncryptParam(PacketCrypt::PARAM_BROADCAST_GLOBAL) != PacketCrypt::SPCE_NO_ERROR)
    {
        // BUG: 0x23000 logs the constant 0 as the type, not the type argument.
        Log::Write(Log::LT_ERROR, SECURITY_FILE, 102,
                   L"BroadcastCrypt, initialize failed;setup encryption parameter failed, type:%d, param:%d", 0,
                   PacketCrypt::PARAM_BROADCAST_GLOBAL);
        if (crypt != nullptr)
            destroyCrypt(crypt);
        BaseMemoryManager::_Instance.Free(crypt, SECURITY_FILE, 104);
        crypt = nullptr;
        return false;
    }
    if (crypt->GenerateKey(keyBuf, &keySize, &compressType, &paramSize) != PacketCrypt::SPCE_NO_ERROR)
    {
        Log::Write(Log::LT_ERROR, SECURITY_FILE, 110,
                   L"BroadcastCrypt, initialize failed;generate broadcast key failed, type:%d", 0);
        if (crypt != nullptr)
            destroyCrypt(crypt);
        BaseMemoryManager::_Instance.Free(crypt, SECURITY_FILE, 112);
        crypt = nullptr;
        return false;
    }
    key = static_cast<char*>(BaseMemoryManager::_Instance.Alloc(keySize, SECURITY_FILE, 116));
    memcpy(key, keyBuf, keySize);
    size = keySize;
    return true;
}

// 0x232F0
void BroadcastCrypt::clear()
{
    if (crypt != nullptr)
    {
        destroyCrypt(crypt);
        BaseMemoryManager::_Instance.Free(crypt, SECURITY_FILE, 142);
        crypt = nullptr;
    }
    if (key != nullptr)
    {
        BaseMemoryManager::_Instance.Free(key, SECURITY_FILE, 145);
        key = nullptr;
    }
}
