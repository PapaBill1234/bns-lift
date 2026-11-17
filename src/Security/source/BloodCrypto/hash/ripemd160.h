// ripemd160.obj (CacheGate PDB). The PDB has no type records for this class.
#pragma once
#include "CryptoHash.h"

// Vtable 0x86E68 (LobbyGate).
class Ripemd160 : public CryptoHash
{
public:
    ~Ripemd160();
    virtual int GetType() const;
    virtual int Size() const;
    virtual bool Digest(unsigned char const* in, int size, unsigned char* digest, int* digestSize) const;
};
