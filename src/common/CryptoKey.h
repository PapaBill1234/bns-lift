// CryptoKey.obj (BloodCrypto, LobbyGate PDB). CryptoKey and Dh.
// The PDB has no type records for these classes. The layout comes from the code.
// LIFT: Member names. The PDB has no field list. ❓ The PDB module of Dh is not known. It is here with CryptoKey.
#pragma once
#include <stddef.h>
#include "BigInteger.h"

class CryptoKey
{
public:
    CryptoKey() : _alloc(false) {}
    virtual int GetType() const = 0; // ❓ slot 0
    virtual bool Setup(int bits) = 0;
    virtual void Cleanup() = 0;
    virtual bool Start(unsigned char const* in, int inSize, unsigned char* out, int* outSize) = 0;
    virtual bool Process(unsigned char const* in, int inSize, unsigned char* out, int* outSize) = 0;
    virtual bool GetKey(unsigned char* out, int* size) const = 0;
    virtual ~CryptoKey() {}

    static bool Initialize();

protected:
    static bool generateBigNumber(int bits, unsigned char* out, int* size);
    static bool generatePrimeNumber(int bits, unsigned char* out, int* size);

public:
    bool _alloc; // ❓ +8

private:
    static long s_initializedCount; // 0x94108
};

// Diffie-Hellman key exchange. vtable 0x86ED8.
class Dh : public CryptoKey
{
public:
    Dh();
    virtual int GetType() const;
    virtual bool Setup(int bits);
    virtual void Cleanup();
    virtual bool Start(unsigned char const* in, int inSize, unsigned char* out, int* outSize);
    virtual bool Process(unsigned char const* in, int inSize, unsigned char* out, int* outSize);
    virtual bool GetKey(unsigned char* out, int* size) const;
    virtual ~Dh();

private:
    void clear();
    bool setupFactors(unsigned char const* data, int size);
    bool getValue(unsigned char* out, int* size);
    // LIFT: Inline code: (p <= g).
    bool pNotAboveG() const
    {
        return _p.sign <= _g.sign &&
               ((&_p == &_g || _p.bits == 0) ? 0 : BigInteger::absCompare(&_p, &_g)) <= 0;
    }

public:
    int _state;     // ❓ +16. 0 = new, 1 = started, -1 = done.
    int _bits;      // ❓ +20
    BigInteger _g;  // ❓ +24
    BigInteger _p;  // ❓ +544
    BigInteger _x;  // ❓ +1064, private value
    BigInteger _y;  // ❓ +1584, peer value
};
static_assert(offsetof(Dh, _state) == 16, "Dh::_state");
static_assert(offsetof(Dh, _g) == 24, "Dh::_g");
static_assert(offsetof(Dh, _y) == 1584, "Dh::_y");
static_assert(sizeof(Dh) == 2104, "sizeof Dh");
