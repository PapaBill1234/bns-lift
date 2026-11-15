// prng.obj (CacheGate PDB).
#include "prng.h"
#include <stdlib.h>
#include <string.h>
#include <new>
#include "ripemd160.h"

// ❓ The PDB has no name for this TLS variable (TLS block offset +8).
static __declspec(thread) Prng* _Instance = 0;

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
