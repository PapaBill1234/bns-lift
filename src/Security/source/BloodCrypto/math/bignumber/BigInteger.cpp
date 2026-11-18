// BigInteger.obj (BloodCrypto).
#include "BigInteger.h"
#include <string.h>

// 0x5AA60
unsigned int const BigInteger::digit_bit_r[32] = {
    0x80000000u, 0x40000000u, 0x20000000u, 0x10000000u, 0x08000000u, 0x04000000u, 0x02000000u, 0x01000000u,
    0x00800000u, 0x00400000u, 0x00200000u, 0x00100000u, 0x00080000u, 0x00040000u, 0x00020000u, 0x00010000u,
    0x00008000u, 0x00004000u, 0x00002000u, 0x00001000u, 0x00000800u, 0x00000400u, 0x00000200u, 0x00000100u,
    0x00000080u, 0x00000040u, 0x00000020u, 0x00000010u, 0x00000008u, 0x00000004u, 0x00000002u, 0x00000001u,
};

// 0x5AAE0
// BUG: 0x5AAE0 has wrong values at [8], [16] and [24]. The correct values are 0x1ff, 0x1ffff and 0x1ffffff.
unsigned int const BigInteger::digit_mask[32] = {
    0x00000001u, 0x00000003u, 0x00000007u, 0x0000000fu, 0x0000001fu, 0x0000003fu, 0x0000007fu, 0x000000ffu,
    0x00001fffu, 0x000003ffu, 0x000007ffu, 0x00000fffu, 0x00001fffu, 0x00003fffu, 0x00007fffu, 0x0000ffffu,
    0x001fffffu, 0x0003ffffu, 0x0007ffffu, 0x000fffffu, 0x001fffffu, 0x003fffffu, 0x007fffffu, 0x00ffffffu,
    0x1fffffffu, 0x03ffffffu, 0x07ffffffu, 0x0fffffffu, 0x1fffffffu, 0x3fffffffu, 0x7fffffffu, 0xffffffffu,
};

// 0x48c70
void BigInteger::setBit(int n)
{
    int count = 32;
    bits = 32 * n;
    for (int i = n - 1; i >= 0; --i)
    {
        if (count != 32)
            break;
        count = 0;
        while (count < 32 && (digits[i] & digit_bit_r[count]) == 0)
            ++count;
        bits -= count;
    }
    if (bits == 0)
    {
        bits = 1;
        sign = 1;
    }
}

// 0x48cf0
void BigInteger::Set(BigInteger const* src, int sign)
{
    if (src != this)
    {
        this->sign = sign * src->sign;
        bits = src->bits;
        for (int i = 0; i < MAX_DIGITS; ++i)
            digits[i] = src->digits[i];
    }
}

// 0x48d30
void BigInteger::Set(long long value)
{
    sign = 1;
    bits = 1;
    if (value >= 0)
    {
        memset(digits, 0, sizeof(digits));
        if (value != 0)
        {
            unsigned long long mask = 0x8000000000000000ull;
            int i;
            for (i = 63; i > 0; --i)
            {
                if ((mask & static_cast<unsigned long long>(value)) != 0)
                    break;
                mask >>= 1;
            }
            digits[0] = static_cast<unsigned int>(value);
            bits = i + 1;
            digits[1] = static_cast<unsigned int>(static_cast<unsigned long long>(value) >> 32);
        }
    }
    else
    {
        memset(digits, 0, sizeof(digits));
        unsigned long long abs = 0ull - static_cast<unsigned long long>(value);
        if (abs != 0)
        {
            unsigned long long mask = 0x8000000000000000ull;
            int i;
            for (i = 63; i > 0; --i)
            {
                if ((mask & abs) != 0)
                    break;
                mask >>= 1;
            }
            digits[0] = static_cast<unsigned int>(abs);
            bits = i + 1;
            digits[1] = static_cast<unsigned int>(abs >> 32);
        }
        sign = -sign;
    }
}

// 0x48e10
bool BigInteger::Set(int sign, unsigned char const* data, int size)
{
    if (data == 0 || static_cast<unsigned int>(size) > 0x200)
        return false;
    memset(digits, 0, sizeof(digits));
    this->sign = sign;
    bits = 1;
    memcpy(digits, data, size);
    setBit((8 * size + 24) >> 5);
    return true;
}

// 0x48eb0
int BigInteger::absCompare(BigInteger const* a, BigInteger const* b)
{
    if (a->bits < b->bits)
        return -1;
    if (a->bits > b->bits)
        return 1;
    for (int i = ((b->bits + 31) >> 5) - 1; i >= 0; --i)
    {
        long long diff = static_cast<long long>(a->digits[i]) - static_cast<long long>(b->digits[i]);
        if (diff != 0)
            return diff < 0 ? -1 : 1;
    }
    return 0;
}
