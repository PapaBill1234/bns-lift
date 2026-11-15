// prng.obj (CacheGate PDB). The PDB has no type records for this class.
// The layout comes from the code. ❓ member names.
#pragma once
#include <stddef.h>
#include <string.h>
#include "aes128.h"
#include "ctr.h"

class Prng
{
public:
    Prng() { memset(_state, 0, sizeof(_state)); }

    static bool Initialize();

private:
    bool setSeed();
    bool addEntropy(unsigned char const* entropy, int size);

public:
    unsigned char _state[20]; // ❓ +0, RIPEMD-160 digest
    Ctr _ctr;                 // ❓ +24
    Aes128 _aes;              // ❓ +112
};
static_assert(sizeof(Prng) == 480, "sizeof Prng");
static_assert(offsetof(Prng, _ctr) == 24, "Prng::_ctr");
static_assert(offsetof(Prng, _aes) == 112, "Prng::_aes");
