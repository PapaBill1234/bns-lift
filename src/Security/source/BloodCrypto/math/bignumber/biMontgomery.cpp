// biMontgomery.obj (BloodCrypto). Montgomery reduction of BigInteger.
#include "BigInteger.h"
#include <string.h>

// 0x4f550
void BigInteger::montgomeryReduce(BigInteger const* n, unsigned int rho)
{
    int used = n->digitCount();
    for (int ix = 0; ix < used; ++ix)
    {
        unsigned int mu = rho * digits[ix];
        unsigned int* p = &digits[ix];
        unsigned int carry = 0;
        for (int iy = 0; iy < used; ++iy)
        {
            unsigned long long t = static_cast<unsigned long long>(*p) + carry +
                                   static_cast<unsigned long long>(mu) * n->digits[iy];
            *p++ = static_cast<unsigned int>(t);
            carry = static_cast<unsigned int>(t >> 32);
        }
        // BUG: 0x4F5E0 the carry loop has no limit, so it can write after digits[127].
        while (carry != 0)
        {
            unsigned long long t = static_cast<unsigned long long>(*p) + carry;
            *p++ = static_cast<unsigned int>(t);
            carry = static_cast<unsigned int>(t >> 32);
        }
    }
    // BUG: 0x4F610 setBit reads digits[2 * used], and this can be digits[128].
    setBit(2 * used + 1);
    int count = digitCount();
    int keep = count - used;
    for (int i = 0; i < keep; ++i)
        digits[i] = digits[i + used];
    // BUG: 0x4F6A0 when keep < 0, the clear starts before digits[0].
    if (keep < count)
        memset(&digits[keep], 0, 4 * (count - keep));
    bits -= 32 * used;
    if (absCompare(this, n) >= 0)
        Sub(this, n);
}

// 0x4f3e0
void BigInteger::montgomeryNormalize(BigInteger const* b)
{
    int topBits = b->bits % 32;
    if (topBits == 0)
        topBits = 32;
    if (((b->bits + 31) & ~31) > 32)
    {
        Pow2(b->bits - 1);
    }
    else
    {
        Set(1LL);
        topBits = 1;
    }
    for (int x = topBits - 1; x < 32; ++x)
    {
        if (isZero())
        {
            setZero();
        }
        else
        {
            // Inline multiply by 2.
            unsigned int carry = 0;
            int n = digitCount();
            int last = 0;
            for (int i = 0; i < n; ++i)
            {
                last = static_cast<int>(digits[i]);
                digits[i] = carry + 2 * digits[i];
                carry = static_cast<unsigned int>(last) >> 31;
            }
            if (n > 0 && last < 0 && n < MAX_DIGITS)
                digits[n] = static_cast<unsigned int>(last) >> 31;
            ++bits;
        }
        if (absCompare(this, b) >= 0)
            Sub(this, b);
    }
}
