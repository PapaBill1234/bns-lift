// ripemd128.obj (LobbyGate PDB). The PDB has no type records for this class.
// The layout comes from the code. ❓ member names.
#pragma once
#include "CryptoHash.h"

// Vtable 0x87000 (LobbyGate).
class Ripemd128 : public CryptoHash
{
public:
    Ripemd128() : _flag(false) {}
    virtual int GetType() const;
    virtual int Size() const;
    virtual bool Digest(unsigned char const* in, int size, unsigned char* digest, int* digestSize) const;

    bool _flag; // ❓ +8, the constructor sets 0. No code reads it.
};
static_assert(sizeof(Ripemd128) == 16, "sizeof Ripemd128");
