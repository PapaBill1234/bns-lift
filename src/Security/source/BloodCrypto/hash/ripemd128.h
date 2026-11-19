// ripemd128.obj (LobbyGate PDB). The PDB has no type records for this class.
// The layout comes from the code. LIFT: Member names. The PDB has no field list.
#pragma once
#include "CryptoHash.h"

// Vtable 0x87000 (LobbyGate).
class Ripemd128 : public CryptoHash
{
public:
    Ripemd128() : _flag(false) {}
    // LIFT: non-virtual user dtor (0x5AB30, 0x531F0). Orig OaepEncoder and RsaPublic dtors store
    // ??_7Ripemd128 (0x87000). Vtable 0x87000 has no dtor slot, so the dtor is not virtual.
    ~Ripemd128() {}
    virtual int GetType() const;
    virtual int Size() const;
    virtual bool Digest(unsigned char const* in, int size, unsigned char* digest, int* digestSize) const;

    bool _flag; // LIFT: name. +8, the constructor sets 0. No code reads it. The PDB has no type records for Ripemd128.
};
static_assert(sizeof(Ripemd128) == 16, "sizeof Ripemd128");
