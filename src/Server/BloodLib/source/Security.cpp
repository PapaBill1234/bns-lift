// Security.obj (LobbyGate PDB).
#include "Security.h"
#include <string.h>
#include <stdlib.h>
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
static inline void destroyCrypt(PacketCrypt* crypt)  // LIFT: lift helper name, not in any PDB
{
    // LIFT: compare chain as in Session::deallocateCrypt (LG 0x194c0). LG 0x232f0: v == 0, v - 1, v - 2, v - 3, v - 4.
    int type = crypt->GetType();
    int rest1;
    int rest2;
    if (type == 0 || ((rest1 = type - 1) != 0 && ((rest2 = rest1 - 1) == 0 || static_cast<unsigned int>(rest2 - 1) <= 1)))
        crypt->~PacketCrypt();
}

// 0x22F50
int zstdPacketCompress(unsigned char* dest, int* destLen, unsigned char const* src, int srcLen,
                       unsigned char const* args, int argsSize)
{
    (void)argsSize;
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
    char compressType = 1;
    int paramSize = 1;
    int keySize = 64;
    unsigned char keyBuf[64];

    // Inlined allocation of a BroadcastPacketCrypt (0x2840 bytes) with its Crypto object after it.
    int cryptoSize = Crypto::InstanceSize(static_cast<Crypto::Type>(2));
    int totalSize = 16 * ((cryptoSize + 15) / 16 + 0x284);
    char* mem = static_cast<char*>(BASE_MEMORY_MANAGER.Alloc(totalSize, SECURITY_FILE, 91));
    BroadcastPacketCrypt* broadcast = nullptr;
    if (mem != nullptr && totalSize > 0 && totalSize >= static_cast<int>((((cryptoSize + 15) & ~15) + 0x2847) & ~15))
    {
        Crypto* crypto = Crypto::Create(mem + 0x2840, totalSize - 0x2840, static_cast<Crypto::Type>(2));
        broadcast = new (mem) BroadcastPacketCrypt(crypto);
    }
    crypt = broadcast;
    if (crypt == nullptr)
        SECURITY_ASSERT_CRASH(96);

    crypt->SetExternalCompressFunc(&zstdPacketCompress, nullptr, 0);
    if (crypt->SetEncryptParam(PacketCrypt::PARAM_BROADCAST_GLOBAL) != PacketCrypt::SPCE_NO_ERROR)
    {
        // BUG: 0x23000 logs the constant 0 as the type, not the type argument.
        Log::Write(Log::LT_ERROR, SECURITY_FILE, 102,
                   L"BroadcastCrypt, initialize failed;setup encryption parameter failed, type:%d, param:%d", 0,
                   PacketCrypt::PARAM_BROADCAST_GLOBAL);
        if (crypt != nullptr)
            destroyCrypt(crypt);
        BASE_MEMORY_MANAGER.Free(crypt, SECURITY_FILE, 104);
        crypt = nullptr;
        return false;
    }
    if (crypt->GenerateKey(keyBuf, &keySize, reinterpret_cast<unsigned char*>(&compressType), &paramSize) != PacketCrypt::SPCE_NO_ERROR)
    {
        Log::Write(Log::LT_ERROR, SECURITY_FILE, 110,
                   L"BroadcastCrypt, initialize failed;generate broadcast key failed, type:%d", 0);
        if (crypt != nullptr)
            destroyCrypt(crypt);
        BASE_MEMORY_MANAGER.Free(crypt, SECURITY_FILE, 112);
        crypt = nullptr;
        return false;
    }
    key = static_cast<char*>(BASE_MEMORY_MANAGER.Alloc(keySize, SECURITY_FILE, 116));
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
        BASE_MEMORY_MANAGER.Free(crypt, SECURITY_FILE, 142);
        crypt = nullptr;
    }
    if (key != nullptr)
    {
        BASE_MEMORY_MANAGER.Free(key, SECURITY_FILE, 145);
        key = nullptr;
    }
}

// LIFT: name. 0x4DFE0 is in compress.obj (BloodPacketCrypt, Mod 0098). That module has no debug info,
// so the PDB has no name. The function takes 4 arguments (the level is fixed inside).
// zlib is not in the tree. A non-zero result makes Encrypt send the packet without compression.
extern "C" int compress2(unsigned char* dest, int* destLen, unsigned char const* source, int sourceLen)
{
    (void)dest;
    (void)destLen;
    (void)source;
    (void)sourceLen;
    return -2;  // TODO(lift-lobbygate-4) link zlib. -2 is Z_STREAM_ERROR.
}

// 0x4CF60
PacketCrypt::ErrCode BroadcastPacketCrypt::SetKey(unsigned char const* key, int keySize)
{
    (void)key;
    (void)keySize;
    return PacketCrypt::NO_RESULT;
}

// 0x4DBA0
int BroadcastPacketCrypt::GetType()
{
    return PacketCrypt::BROADCAST_CRYPT;
}

// 0x4DBB0 (vector deleting destructor)
BroadcastPacketCrypt::~BroadcastPacketCrypt()
{
    _keySet = false;
    Crypto::Destroy(_crypto);
    _crypto = nullptr;
    if (_dict != nullptr)
    {
        // BUG: 0x4DBB0 the destructor clears _dict but does not free it (SetExternalCompressFunc mallocs it).
        _dict = nullptr;
        _dictSize = 0;
    }
}

// 0x4DC00
PacketCrypt::ErrCode BroadcastPacketCrypt::SetEncryptParam(Param param)
{
    if (param != PacketCrypt::PARAM_BROADCAST_LOCAL && param != PacketCrypt::PARAM_BROADCAST_GLOBAL &&
        param != PacketCrypt::PARAM_BROADCAST_LOCAL_COMPRESS)
        return PacketCrypt::INVALID_PARAM;
    _param = param;
    return PacketCrypt::SPCE_NO_ERROR;
}

// 0x4DC20
PacketCrypt::ErrCode BroadcastPacketCrypt::GenerateKey(unsigned char* key1, int* size1, unsigned char* key2, int* size2)
{
    if (key1 == nullptr || size1 == nullptr || *size1 < 16)
        return PacketCrypt::INVALID_PARAM;
    if (_keySet == true)
        return PacketCrypt::ALREADY_INITIALIZED;
    if (*size2 > 0)  // BUG: 0x4DC20 size2 and key2 are not checked for nullptr.
        _compressType = static_cast<char>(*key2);
    if (*size1 < 0 || 8 * *size1 < 128)
        return PacketCrypt::FAILED_KEYGEN;
    unsigned char* p = key1;
    for (long long i = 16; i != 0; --i)
        *p++ = static_cast<unsigned char>(rand());
    *size1 = 16;
    if (_crypto->Setup(key1, 16, 0))
    {
        _keySet = true;
        key1[(*size1)++] = static_cast<unsigned char>(_compressType);
        return PacketCrypt::SPCE_NO_ERROR;
    }
    memset(key1, 0, *size1);
    return PacketCrypt::FAILED_SETUP_CRYPTO;
}

// 0x4DD70
PacketCrypt::ErrCode BroadcastPacketCrypt::Encrypt(unsigned char* buffer, int* bufferSize, int size, bool with3rdParty)
{
    (void)with3rdParty;
    if (_keySet == false)
        return PacketCrypt::NOT_INITIALIZED;
    unsigned char const* src = buffer + 2;
    unsigned char* out = buffer + 2;
    int count = 0;
    short type;
    _bufferSize = 0x2800;
    switch (_param)
    {
    case PacketCrypt::PARAM_BROADCAST_LOCAL:
        type = PacketCrypt::BROADCAST_LOCAL_KEY;
        break;
    case PacketCrypt::PARAM_BROADCAST_GLOBAL:
        type = PacketCrypt::BROADCAST_GLOBAL_KEY;
        break;
    case PacketCrypt::PARAM_BROADCAST_LOCAL_COMPRESS:
    {
        type = PacketCrypt::BROADCAST_LOCAL_KEY_COMPRESS;
        int result;
        if (_compressType == PacketCrypt::COMPRESS_TYPE1)
            result = compress2(_buffer, &_bufferSize, src, size);
        else if (_compressType == PacketCrypt::COMPRESS_TYPE2)
            result = _compressFunc(_buffer, &_bufferSize, src, size, _dict, _dictSize);
        else
            return PacketCrypt::INVALID_PARAM;
        if (result == 0 && PacketCrypt::_MaxSize >= _crypto->EncSize(_bufferSize))
        {
            size = _bufferSize;
            src = _buffer;
        }
        else
        {
            type = PacketCrypt::BROADCAST_LOCAL_KEY;
        }
        break;
    }
    default:
        return PacketCrypt::INVALID_PARAM;
    }
    int encSize = _crypto->EncSize(size);
    if (PacketCrypt::_MaxSize < encSize)
        return PacketCrypt::FAILED_TOO_LARGE_PACKET;
    if (encSize + 2 > *bufferSize)
        return PacketCrypt::FAILED_INSUFFIENT_BUFFER;
    count = *bufferSize - 2;
    if (!_crypto->Encrypt(src, size, out, &count))
        return PacketCrypt::FAILED_ENCRYPT;
    *reinterpret_cast<unsigned short*>(buffer) = static_cast<unsigned short>((type << 12) | ((count >> 2) & 0xFFF));
    *bufferSize = count + 2;
    return PacketCrypt::SPCE_NO_ERROR;
}

// 0x4DF30
PacketCrypt::ErrCode BroadcastPacketCrypt::Decrypt(unsigned char* buffer, int size, int* outSize, bool* with3rdParty)
{
    (void)buffer;
    (void)size;
    (void)outSize;
    (void)with3rdParty;
    return PacketCrypt::FAILED_INVALID_CODE;
}

// 0x4DF40
PacketCrypt::ErrCode BroadcastPacketCrypt::SetExternalCompressFunc(ExternalCompressFunc func, unsigned char const* data, int size)
{
    size_t dataSize = size;
    if (_compressFunc != nullptr)
        return PacketCrypt::FAILED_SET_EXT_COMP_FUNC;
    _compressFunc = func;
    if (data != nullptr)
    {
        if (_dict != nullptr)
        {
            free(_dict);
            _dict = nullptr;
        }
        _dict = static_cast<unsigned char*>(malloc(dataSize));
        _dictSize = static_cast<int>(dataSize);
        memcpy(_dict, data, dataSize);
    }
    return PacketCrypt::SPCE_NO_ERROR;
}
