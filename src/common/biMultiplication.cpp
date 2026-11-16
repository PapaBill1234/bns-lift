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
    // The accumulator has 96 bits: accLow (64 bits) and accHigh (32 bits).
    unsigned long long accLow = 0;
    unsigned int accHigh = 0;
    for (int ix = 0; ix < digs; ++ix)
    {
        int ty = ix < usedB - 1 ? ix : usedB - 1;
        int tx = ix - ty;
        int iy = usedA - tx;
        if (iy > ty + 1)
            iy = ty + 1;
        for (int iz = 0; iz < iy; ++iz)
        {
            unsigned long long p = static_cast<unsigned long long>(a->digits[tx + iz]) * b->digits[ty - iz];
            accLow += p;
            if (accLow < p)
                ++accHigh;
        }
        r->digits[ix] = static_cast<unsigned int>(accLow);
        accLow = (accLow >> 32) | (static_cast<unsigned long long>(accHigh) << 32);
        accHigh = 0;
    }
    r->setBit(digs);
}

// 0x4fa30
void BigInteger::mul(unsigned int m)
{
    int count = 0;
    int n = digitCount();
    if (n > 0)
    {
        unsigned int carry = 0;
        for (int i = 0; i < n; ++i)
        {
            unsigned long long t = static_cast<unsigned long long>(m) * digits[i] + carry;
            digits[i] = static_cast<unsigned int>(t);
            carry = static_cast<unsigned int>(t >> 32);
        }
        count = n;
        // BUG: 0x4FA30 when n is 128, the last carry is lost.
        if (carry != 0 && n < MAX_DIGITS)
        {
            digits[n] = carry;
            count = n + 1;
        }
    }
    // BUG: 0x4FA30 setBit reads digits[count], and count can be 128.
    setBit(count + 1);
}
