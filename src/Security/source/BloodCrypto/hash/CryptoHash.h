// CryptoHash (BloodCrypto). Base class of Ripemd128 and Ripemd160.
// The PDB has no type records for this class. The vtable comes from the code.
#pragma once

// Vtable: GetType, Size, Digest. No virtual destructor.
class CryptoHash
{
public:
    virtual int GetType() const = 0;
    virtual int Size() const = 0;
    virtual bool Digest(unsigned char const* in, int size, unsigned char* digest, int* digestSize) const = 0;
};
