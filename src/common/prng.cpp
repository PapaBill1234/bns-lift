// prng.obj (CacheGate PDB).
#include "prng.h"
#include <stdlib.h>
#include <string.h>
#include <new>
#include "ripemd160.h"

// ❓ The PDB has no name for this TLS variable (TLS block offset +8).
static __declspec(thread) Prng* _Instance = 0;

// ❓ Accessor for CryptoKey. The original code reads the TLS slot inline.
Prng* Prng::instance()
{
    return _Instance;
}

// 0x35ce0
bool Prng::Initialize()
{
    if (_Instance == 0)
    {
        // BUG: 0x35ce0 does not check the malloc result for null.
        void* mem = malloc(sizeof(Prng));
        _Instance = new (mem) Prng();
    }
    return true;
}

// 0x35d60
bool Prng::setSeed()
{
    unsigned char buf[128];
    for (long long i = 0; i < 128; ++i)
        buf[i] = static_cast<unsigned char>(rand());
    bool result = addEntropy(buf, sizeof(buf));
    if (!result)
        return result;
    return _ctr.Setup(&_aes, 0, _state, 20, _state, 20) != 0;
}

// 0x35e10
bool Prng::addEntropy(unsigned char const* entropy, int /*size*/)
{
    // BUG: 0x35e10 ignores size. It always copies 128 bytes of entropy.
    unsigned char buf[148];
    memcpy(buf, _state, 20);
    memcpy(buf + 20, entropy, 128);
    Ripemd160 ripemd;
    int hashSize = 20;
    bool result = ripemd.Digest(buf, sizeof(buf), _state, &hashSize);
    memset(buf, 0, sizeof(buf));
    return result;
}

// 0x5A520 (LobbyGate)
bool Prng::Generate(unsigned char* buffer, int size)
{
    memset(buffer, 0, size);
    if (_Instance == 0 && !(Initialize() && _Instance->setSeed()))
        return false;
    return _Instance->_ctr.Encrypt(buffer, size, buffer, &size);
}

// 0x5A5C0 (LobbyGate)
bool Prng::GeneratePrime(int bits, BigInteger* out)
{
    int bytes = (bits + 7) >> 3;
    unsigned char top = static_cast<unsigned char>(1 << ((bits - 1) & 7));
    if (out == 0 || static_cast<unsigned int>(bits) > 0x800)
        return false;
    unsigned char mask = static_cast<unsigned char>(255 >> (8 - (bits & 7)));
    if (mask == 0)
        mask = 0xFF;
    for (;;)
    {
        int count = bytes;
        unsigned char buffer[256];
        memset(buffer, 0, bytes);
        if (_Instance == 0 && !(Initialize() && _Instance->setSeed()))
            break;
        if (!_Instance->_ctr.Encrypt(buffer, bytes, buffer, &count))
            break;
        buffer[bytes - 1] = top | (mask & buffer[bytes - 1]);
        buffer[0] |= 1;
        if (bytes <= 0x200)
            out->Set(buffer, bytes);
        if (out->IsPrime())
            return true;
    }
    return false;
}
