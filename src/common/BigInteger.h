// BigInteger (BloodCrypto). Modules: CryptoKey.obj (ctor, dtor), BigInteger.obj,
// NumberTheory.obj, biArithmetic.obj, biMontgomery.obj, biSqr.obj, biMultiplication.obj.
// The PDB has no type records for this class. The layout comes from the code.
// LIFT: Member names. The PDB has no field list.
#pragma once
#include <stddef.h>
#include <string.h>

class BigInteger
{
    friend class Dh; // LIFT: Dh uses the inline compare (absCompare).

public:
    enum { MAX_DIGITS = 128 }; // ❓

    // 0x46580
    BigInteger()
    {
        sign = 1;
        bits = 1;
        memset(digits, 0, sizeof(digits));
    }
    // 0x465B0
    ~BigInteger() { memset(digits, 0, sizeof(digits)); }

    void Set(BigInteger const* src, int sign);
    void Set(long long value);
    // ❓ The PDB name is Set(int,uchar const*,int). The code uses only (data, size).
    bool Set(unsigned char const* data, int size);
    bool InvMod(BigInteger const* a, BigInteger const* b);
    void Sqr(BigInteger const* a);
    void RightShift(BigInteger const* a, int n);
    void LeftShift(BigInteger const* a, int n);
    void Mul(BigInteger const* a, BigInteger const* b);
    void Sub(BigInteger const* a, BigInteger const* b);
    void Add(BigInteger const* a, BigInteger const* b);
    void Pow2(int n);
    static void Divide(BigInteger const* a, BigInteger const* b, BigInteger* quot, BigInteger* rem);

    static void Divide(BigInteger const* a, unsigned int b, BigInteger* quot, unsigned int* rem);
    void ExpMod(BigInteger const* a, BigInteger const* e, BigInteger const* n);
    bool IsPrime() const;

    // LIFT: Inline helpers. The compiler put this code inline. No PDB symbol.
    int digitCount() const { return (bits + 31) >> 5; }
    bool isZero() const { return sign == 1 && bits == 1 && digits[0] == 0; }
    void setZero()
    {
        sign = 1;
        bits = 1;
        memset(digits, 0, sizeof(digits));
    }

private:
    void setBit(int n);
    void expMod(BigInteger const* a, BigInteger const* e, BigInteger const* n);
    bool invMod(BigInteger const* a, BigInteger const* b);
    void leftShiftDigit(BigInteger const* a, int n, bool clear);
    void sub(BigInteger const* a, BigInteger const* b, int sign);
    void add(BigInteger const* a, BigInteger const* b, int sign);
    void montgomeryReduce(BigInteger const* n, unsigned int rho);
    void montgomeryNormalize(BigInteger const* b);
    void mul(unsigned int m);

    static unsigned int const digit_bit_r[32]; // 0x5AA60
    static unsigned int const digit_mask[32];  // 0x5AAE0

    static int absCompare(BigInteger const* a, BigInteger const* b);
    static bool isPrimeMR(BigInteger const* n, unsigned long long b);
    static void sqr(BigInteger const* a, BigInteger* r);
    static void mul(BigInteger const* a, BigInteger const* b, BigInteger* r);

public:
    int sign;                         // ❓ +0, 1 or -1
    int bits;                         // ❓ +4, bit count (1 for zero, 0 for an invalid value)
    unsigned int digits[MAX_DIGITS];  // ❓ +8, 32-bit digits, low digit first
};
static_assert(sizeof(BigInteger) == 0x208, "sizeof BigInteger");
static_assert(offsetof(BigInteger, digits) == 8, "BigInteger::digits");
