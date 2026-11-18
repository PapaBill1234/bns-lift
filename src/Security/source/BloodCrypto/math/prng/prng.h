// prng.obj (CacheGate PDB). The PDB has no type records for this class.
// The layout comes from the code. LIFT: Member names. The PDB has no field list.
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
    __declspec(noinline) bool addEntropy(unsigned char const* entropy, int size); // LIFT: noinline, 0x35d60 calls it
    // LIFT: No PDB symbol. CryptoKey::Initialize reads the TLS instance directly.
    static Prng* instance();

public:
    unsigned char _state[20]; // +0 (LobbyGate Prng::setSeed 0x5a7ff), RIPEMD-160 digest
    Ctr _ctr;                 // +24 (LobbyGate Prng::setSeed 0x5a7ef)
    Aes128 _aes;              // +112 (LobbyGate Prng::setSeed 0x5a7fb)
};
static_assert(sizeof(Prng) == 480, "sizeof Prng");
static_assert(offsetof(Prng, _ctr) == 24, "Prng::_ctr");
static_assert(offsetof(Prng, _aes) == 112, "Prng::_aes");
