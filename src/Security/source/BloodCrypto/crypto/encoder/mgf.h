// mgf.obj (LobbyGate PDB). MGF1 mask generator.
// The PDB has no type records for this class. The layout comes from the code.
// LIFT: Member names. The PDB has no field list.
#pragma once
#include <stddef.h>
#include <string.h>
#include "CryptoHash.h"

class MaskGenerator
{
    friend class OaepEncoder;

public:
    MaskGenerator() : _size(0), _hash(0) { memset(_digest, 0, sizeof(_digest)); }
    ~MaskGenerator()
    {
        memset(_digest, 0, sizeof(_digest));
        _size = 0;
        _hash = 0;
    }

private:
    bool generate(unsigned char const* seed, int seedSize, unsigned char* out, int outSize);

public:
    int _size;                 // +0 (LobbyGate OaepEncoder+0x20, Setup 0x5ac32), digest size of _hash
    unsigned char _digest[64]; // +4 (LobbyGate OaepEncoder+0x24, dtor 0x5ab56)
    CryptoHash* _hash;         // +72 (LobbyGate OaepEncoder+0x68, Setup 0x5ac18)
};
static_assert(sizeof(MaskGenerator) == 80, "sizeof MaskGenerator");
static_assert(offsetof(MaskGenerator, _hash) == 72, "MaskGenerator::_hash");
