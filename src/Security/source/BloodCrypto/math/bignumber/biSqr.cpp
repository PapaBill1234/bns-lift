// biSqr.obj (BloodCrypto). Comba square of BigInteger.
#include "BigInteger.h"

// 0x4f750
void BigInteger::sqr(BigInteger const* a, BigInteger* r)
{
    BigInteger tmp;
    BigInteger* out = r;
    int pa = ((a->bits + 31) >> 4) & ~1;
    if (pa >= MAX_DIGITS)
        pa = MAX_DIGITS - 1;
    if (r == 0 || a == r)
        out = &tmp;
    // The accumulator has 96 bits: accLow (64 bits) and accHigh (32 bits).
    unsigned long long accLow = 0;
    unsigned int accHigh = 0;
    for (int ix = 0; ix < pa; ++ix)
    {
        // libtommath uses a->used - 1 here. This code uses pa - 1. The digits above "used" are zero.
        int ty = pa - 1 < ix ? pa - 1 : ix;
        int tx = ix - ty;
        int iy = pa - tx;
        if (iy > ty + 1)
            iy = ty + 1;
        int half = (ty - tx + 1) >> 1;
        if (iy >= half)
            iy = half;
        for (int iz = 0; iz < iy; ++iz)
        {
            unsigned long long p = static_cast<unsigned long long>(a->digits[tx + iz]) * a->digits[ty - iz];
            accLow += p;
            if (accLow < p)
                ++accHigh;
            accLow += p;
            if (accLow < p)
                ++accHigh;
        }
        if ((ix & 1) == 0)
        {
            unsigned int d = a->digits[ix >> 1];
            unsigned long long p = static_cast<unsigned long long>(d) * d;
            accLow += p;
            if (accLow < p)
                ++accHigh;
        }
        out->digits[ix] = static_cast<unsigned int>(accLow);
        accLow = (accLow >> 32) | (static_cast<unsigned long long>(accHigh) << 32);
        accHigh = 0;
    }
    out->sign = 1;
    out->setBit(pa);
    if (r != 0 && r != out)
        r->Set(out, 1);
}
