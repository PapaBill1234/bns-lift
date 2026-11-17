// CryptoKey.obj (BloodCrypto, LobbyGate PDB). CryptoKey and Dh.
// The PDB has no type records for these classes. The layout comes from the code.
// LIFT: Member names. The PDB has no field list. LIFT: file. The PDB puts Dh in dh.obj (BloodCrypto, Mod 0071). It is here with CryptoKey.
#pragma once
#include <stddef.h>
#include "BigInteger.h"

class CryptoKey
{
public:
    CryptoKey() : _alloc(false) {}
    virtual int GetType() const = 0; // LIFT: slot 0. Dh slot 0 = xor eax,eax; ret, folded with Rsa::KeySize (LobbyGate 0x86ED8, 0x27fc0)
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
    bool _alloc; // LIFT: +8. Dh::Dh writes byte [rcx+8] = 0 (LobbyGate 0x554c0)

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
    int _state;     // LIFT: +16. 0 = new (Setup 0x55610), 1 = started (Start 0x5595e), -1 = done (Process 0x559e2). LobbyGate.
    int _bits;      // LIFT: +20. Setup writes [rcx+14h] (LobbyGate 0x55610)
    BigInteger _g;  // LIFT: +24. Dh::Dh header +0x18 (LobbyGate 0x554c0)
    BigInteger _p;  // LIFT: +544. Dh::Dh header +0x220 (LobbyGate 0x554c0)
    BigInteger _x;  // LIFT: +1064, private value. getValue sets it from generateBigNumber (LobbyGate 0x55e41)
    BigInteger _y;  // LIFT: +1584, peer value. Process sets it from the input (LobbyGate 0x559a5)
};
static_assert(offsetof(Dh, _state) == 16, "Dh::_state");
static_assert(offsetof(Dh, _g) == 24, "Dh::_g");
static_assert(offsetof(Dh, _y) == 1584, "Dh::_y");
static_assert(sizeof(Dh) == 2104, "sizeof Dh");
