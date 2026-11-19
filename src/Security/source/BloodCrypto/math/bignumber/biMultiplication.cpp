// biMultiplication.obj (BloodCrypto). Comba multiply of BigInteger.
#include "BigInteger.h"

// 0x4fb10
void BigInteger::mul(BigInteger const* a, BigInteger const* b, BigInteger* r)
{
    int digs = (a->bits + b->bits + 31) >> 5;
    if (digs >= MAX_DIGITS)
        digs = MAX_DIGITS - 1;
    int usedA = a->digitCount();
    int usedB = b->digitCount();
    // The accumulator has 3 words of 32 bits: c0, c1 and c2.
    unsigned int c0 = 0;
    unsigned int c1 = 0;
    unsigned int c2 = 0;
    for (int ix = 0; ix < digs; ++ix)
    {
        int ty = ix < usedB - 1 ? ix : usedB - 1;
        int tx = ix - ty;
        unsigned int const* px = &a->digits[tx];
        unsigned int const* py = &b->digits[ty];
        c0 = c1;
        c1 = c2;
        c2 = 0;
        int iy = usedA - tx;
        if (iy > ty + 1)
            iy = ty + 1;
        for (int iz = 0; iz < iy; ++iz)
        {
            unsigned long long t = static_cast<unsigned long long>(*px++) * *py-- + c0;
            c0 = static_cast<unsigned int>(t);
            t = (t >> 32) + c1;
            c1 = static_cast<unsigned int>(t);
            c2 += static_cast<unsigned int>(t >> 32);
        }
        r->digits[ix] = c0;
    }
    r->setBit(digs);
}

// 0x4fa30
void BigInteger::mul(unsigned int m)
{
    int n = digitCount();
    int count = 0;
    unsigned long long carry = 0;
    for (int i = 0; i < n; ++i)
    {
        carry += static_cast<unsigned long long>(digits[i]) * m;
        digits[i] = static_cast<unsigned int>(carry);
        carry >>= 32;
        count = n;
    }
    // BUG: 0x4FA30 when n is 128, the last carry is lost.
    if (carry != 0 && n < MAX_DIGITS)
    {
        digits[n] = static_cast<unsigned int>(carry);
        count = n + 1;
    }
    // BUG: 0x4FA30 setBit reads digits[count], and count can be 128.
    setBit(count + 1);
}
