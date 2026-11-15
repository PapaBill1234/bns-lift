// ripemd160.obj (CacheGate PDB). The PDB has no type records for this class.
#pragma once

class Ripemd160
{
public:
    virtual bool Digest(unsigned char const* in, int size, unsigned char* digest, int* digestSize) const;
};
