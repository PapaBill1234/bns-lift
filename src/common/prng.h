// prng.obj (CacheGate PDB). The PDB has no type records for this class.
// The layout comes from the code. ❓ member names.
#pragma once
#include <stddef.h>
#include <string.h>
#include "aes128.h"
#include "ctr.h"
#include "BigInteger.h"

class Prng
{
    friend class CryptoKey;

public:
    Prng() { memset(_state, 0, sizeof(_state)); }

    static bool Initialize();
    static bool Generate(unsigned char* buffer, int size);
    static bool GeneratePrime(int bits, BigInteger* out);

private:
    bool setSeed();
    bool addEntropy(unsigned char const* entropy, int size);
    // ❓ No PDB symbol. CryptoKey::Initialize reads the TLS instance directly.
    static Prng* instance();

public:
    unsigned char _state[20]; // ❓ +0, RIPEMD-160 digest
    Ctr _ctr;                 // ❓ +24
    Aes128 _aes;              // ❓ +112
};
static_assert(sizeof(Prng) == 480, "sizeof Prng");
static_assert(offsetof(Prng, _ctr) == 24, "Prng::_ctr");
static_assert(offsetof(Prng, _aes) == 112, "Prng::_aes");
