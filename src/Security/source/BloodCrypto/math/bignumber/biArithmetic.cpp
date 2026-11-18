// biArithmetic.obj (BloodCrypto). Add, Sub, Mul, Sqr, shifts and Divide of BigInteger.
#include "BigInteger.h"
#include <string.h>

namespace
{
// LIFT: No PDB symbol. The compiler put this loop inline. It counts the zero bits above the top set bit.
int leadingZeros(unsigned int value, unsigned int const* bitTable)
{
    int count = 0;
    while (count < 32 && (value & bitTable[count]) == 0)
        ++count;
    return count;
}
} // namespace

// 0x4ca80
void BigInteger::leftShiftDigit(BigInteger const* a, int n, bool clear)
{
    int count = n + a->digitCount();
    if (count > MAX_DIGITS)
        count = MAX_DIGITS;
    for (int i = count - 1; i >= n; --i)
        digits[i] = a->digits[i - n];
    if ((this != a || clear) && n > 0)
        memset(digits, 0, 4 * n);
    bits = a->bits + 32 * n;
}

// 0x4c900
void BigInteger::sub(BigInteger const* a, BigInteger const* b, int sign)
{
    int na = a->digitCount();
    int nb = b->digitCount();
    int old = digitCount();
    int i = 0;
    long long borrow = 0;
    for (; i < nb; ++i)
    {
        long long t = static_cast<long long>(a->digits[i]) - static_cast<long long>(b->digits[i]) - borrow;
        digits[i] = static_cast<unsigned int>(t);
        borrow = (t >> 32) & 1;
    }
    for (; i < na; ++i)
    {
        // BUG: 0x4C9D1 the propagated borrow is -1 (no "& 1"), so the next digit is incremented.
        long long t = static_cast<long long>(a->digits[i]) - borrow;
        digits[i] = static_cast<unsigned int>(t);
        borrow = t >> 32;
    }
    if (i < old)
        memset(&digits[i], 0, (old - i) * sizeof(unsigned int));
    this->sign = sign;
    setBit(i);
}

// 0x4c7b0
void BigInteger::add(BigInteger const* a, BigInteger const* b, int sign)
{
    int old = digitCount();
    int maxBits = a->bits > b->bits ? a->bits : b->bits;
    int count = (maxBits + 31) >> 5;
    int n = 0;
    if (count > 0)
    {
        unsigned int carry = 0;
        for (int i = 0; i < count; ++i)
        {
            unsigned long long t = static_cast<unsigned long long>(a->digits[i]) + b->digits[i] + carry;
            digits[i] = static_cast<unsigned int>(t);
            carry = static_cast<unsigned int>(t >> 32);
        }
        n = count;
        if (carry != 0 && count < MAX_DIGITS)
            digits[count] = carry;
    }
    // BUG: 0x4C82B reads digits[128] when n is 128, and reads an old digits[n] when there is no carry.
    setBit(n + 1);
    this->sign = sign;
    // BUG: 0x4C88A the clear starts at n, so it also clears the carry digit at digits[n].
    if (n < old)
        memset(&digits[n], 0, 4 * (old - n));
}

// 0x4c650
// LIFT: 0x5a0ad calls Set out of line. inline_depth(0) keeps Set out of line (lessons A20).
#pragma inline_depth(0)
void BigInteger::Sqr(BigInteger const* a)
{
    if (a->bits == 0)
    {
        sign = a->sign;
        bits = 0;
        return;
    }
    if (a->isZero())
    {
        setZero();
        return;
    }
    if (a->bits == 1)
    {
        if (a != this)
        {
            sign = a->sign * a->sign;
            bits = a->bits;
            for (int i = 0; i < MAX_DIGITS; ++i)
                digits[i] = a->digits[i];
        }
        return;
    }
    BigInteger tmp;
    BigInteger* r = this;
    if (a == this)
        r = &tmp;
    else
        setZero();
    // LIFT: 0x5a08b computes the rounded bit count before the call, as in Mul. Both paths call sqr. // ❓
    if (((a->bits + 31) & ~31) < 0x1000)
        sqr(a, r);
    else
        sqr(a, r);
    r->sign = 1;
    if (r != this)
        Set(r, 1);
}
#pragma inline_depth()

// 0x4c3e0
// LIFT: LeftShift jumps to this function in LobbyGate (0x59bca).
__declspec(noinline) void BigInteger::RightShift(BigInteger const* a, int n)
{
    if (n == 0)
        return;
    if (n < 0)
    {
        LeftShift(a, -n);
        return;
    }
    if (a->bits <= n || a->isZero())
    {
        setZero();
        return;
    }
    if (a->bits - 1 == n)
    {
        Set(static_cast<long long>(a->sign));
        return;
    }
    int top = 1;
    int shiftDigits = n >> 5;
    if (this != a)
    {
        setZero();
        sign = a->sign;
        bits = a->bits;
    }
    if (shiftDigits > 0)
    {
        int count = a->digitCount() - shiftDigits;
        for (int i = 0; i < count; ++i)
            digits[i] = a->digits[i + shiftDigits];
        bits = a->bits - 32 * shiftDigits;
    }
    int shiftBits = n & 0x1F;
    if (shiftBits != 0)
    {
        // BUG: 0x4C4C0 when this == a and shiftDigits > 0, the bit shift reads digits that are already shifted.
        int count = a->digitCount();
        digits[0] = a->digits[shiftDigits] >> shiftBits;
        if (count > 1)
        {
            top = count;
            for (int i = 1; i < count; ++i)
            {
                unsigned int d = a->digits[shiftDigits + i];
                digits[i - 1] += (d & digit_mask[shiftBits]) << (32 - shiftBits);
                digits[i] = d >> shiftBits;
            }
        }
        if (this == a && bits % 32 == shiftBits)
            digits[top] = 0;
        bits -= shiftBits;
    }
}

// 0x4c270
void BigInteger::LeftShift(BigInteger const* a, int n)
{
    if (n == 0)
        return;
    if (n < 0)
    {
        RightShift(a, -n);
        return;
    }
    if (n >= 4096 || a->isZero())
    {
        setZero();
        return;
    }
    int shiftDigits = n >> 5;
    if (this != a)
    {
        setZero();
        sign = a->sign;
        bits = a->bits;
    }
    if (shiftDigits > 0)
        leftShiftDigit(a, shiftDigits, false);
    int shiftBits = n & 0x1F;
    if (shiftBits != 0)
    {
        // BUG: 0x4C330 the bit shift reads a->digits[i] and writes digits[i], so it ignores the digit shift.
        unsigned int carry = 0;
        unsigned int next = 0;
        int count = a->digitCount();
        if (count > 0)
        {
            for (int i = 0; i < count; ++i)
            {
                unsigned int d = a->digits[i];
                next = d >> (32 - shiftBits);
                digits[i] = carry + (d << shiftBits);
                carry = next;
            }
            if (next != 0 && count < MAX_DIGITS)
                digits[count] = next;
        }
        if (shiftDigits > 0 && this == a)
            digits[0] = 0;
        bits += shiftBits;
    }
}

// 0x4b640
void BigInteger::Mul(BigInteger const* a, BigInteger const* b)
{
    if (a == 0 || b == 0)
        return;
    if (a->bits == 0)
    {
        sign = a->sign;
        bits = 0;
        return;
    }
    if (b->bits == 0)
    {
        sign = b->sign;
        bits = 0;
        return;
    }
    if (a->isZero() || b->isZero())
    {
        setZero();
    }
    else if (a->bits == 1)
    {
        Set(b, a->sign);
    }
    else if (b->bits == 1)
    {
        Set(a, b->sign);
    }
    else
    {
        BigInteger tmp;
        BigInteger* r = this;
        if (a == this || b == this)
            r = &tmp;
        else
            setZero();
        // LIFT: 0x58fbd computes the rounded bit count and compares it with 0x1000. Both paths call mul,
        // and the compiler merged them. The source name of the second path is not known. // ❓
        if (((a->bits + b->bits + 31) & ~31) < 0x1000)
            mul(a, b, r);
        else
            mul(a, b, r);
        r->sign = a->sign * b->sign;
        if (r != this)
            Set(r, 1);
    }
}

// 0x4b500
void BigInteger::Sub(BigInteger const* a, BigInteger const* b)
{
    if (b == 0)
        return;
    if (a->bits == 0)
    {
        sign = a->sign;
        bits = 0;
        return;
    }
    if (b->bits == 0)
    {
        bits = 0;
        sign = -b->sign;
        return;
    }
    if (b->isZero())
    {
        Set(a, 1);
    }
    else if (a->isZero())
    {
        Set(b, -1);
    }
    else if (a->sign != b->sign)
    {
        add(a, b, a->sign);
    }
    else
    {
        int cmp = absCompare(a, b);
        if (cmp == 0)
        {
            setZero();
            return;
        }
        int resultSign = a->sign;
        if (cmp < 0)
        {
            resultSign = -b->sign;
            BigInteger const* larger = b;
            b = a;
            a = larger;
        }
        sub(a, b, resultSign);
    }
}

// 0x4b3d0
void BigInteger::Add(BigInteger const* a, BigInteger const* b)
{
    if (a == 0 || b == 0)
        return;
    if (a->bits == 0)
    {
        sign = a->sign;
        bits = 0;
        return;
    }
    if (b->bits == 0)
    {
        sign = b->sign;
        bits = 0;
        return;
    }
    if (a->isZero())
    {
        Set(b, 1);
    }
    else if (b->isZero())
    {
        Set(a, 1);
    }
    else if (a->sign == b->sign)
    {
        add(a, b, a->sign);
    }
    else
    {
        int cmp = absCompare(a, b);
        if (cmp == 0)
            setZero();
        else if (cmp > 0)
            sub(a, b, a->sign);
        else
            sub(b, a, b->sign);
    }
}

// 0x4c5d0
void BigInteger::Pow2(int n)
{
    Set(1LL);
    LeftShift(this, n);
}

// 0x4b7e0
void BigInteger::Divide(BigInteger const* a, BigInteger const* b, BigInteger* quot, BigInteger* rem)
{
    if (a == 0 || b == 0 || (quot == 0 && rem == 0))
        return;
    if (b->bits == 0)
    {
        if (quot != 0)
            quot->setZero();
        if (rem != 0)
            rem->Set(a, 1);
        return;
    }
    if (a->bits == 0 || b->isZero())
    {
        if (quot != 0)
        {
            quot->sign = a->sign;
            quot->bits = 0;
        }
        if (rem != 0)
        {
            rem->sign = a->sign;
            rem->bits = 0;
        }
        return;
    }
    if (a->isZero())
    {
        if (quot != 0)
            quot->setZero();
        if (rem != 0)
            rem->setZero();
        return;
    }
    if (b->bits == 1)
    {
        if (quot != 0)
            quot->Set(a, b->sign);
        if (rem != 0)
            rem->setZero();
        return;
    }
    if (absCompare(a, b) < 0)
    {
        if (quot != 0)
            quot->setZero();
        if (rem != 0)
            rem->Set(a, 1);
        return;
    }

    // This is the HAC 14.20 division (the libtommath mp_div form).
    BigInteger x(*a);
    BigInteger y(*b);
    BigInteger q;
    BigInteger t1;
    BigInteger t2;
    BigInteger t3;
    int neg = a->sign * b->sign;
    x.sign = 1;
    y.sign = 1;
    q.bits = a->bits + 64;

    int norm;
    if (y.bits % 32 >= 31)
    {
        norm = 0;
    }
    else
    {
        norm = 31 - y.bits % 32;
        x.LeftShift(&x, norm);
        y.LeftShift(&y, norm);
    }

    int n = x.digitCount() - 1;
    int t = y.digitCount() - 1;
    int shift = n - t;
    y.leftShiftDigit(&y, shift, true);
    while (x.bits >= y.bits)
    {
        if (x.bits <= y.bits && absCompare(&x, &y) < 0)
            break;
        ++q.digits[n - t];
        x.Sub(&x, &y);
    }
    {
        // Inline right shift of y by "shift" digits.
        int count = y.digitCount();
        int keep = count - shift;
        for (int i = 0; i < keep; ++i)
            y.digits[i] = y.digits[i + shift];
        if (keep < count)
            memset(&y.digits[keep], 0, 4 * (count - keep));
        y.bits -= 32 * shift;
    }

    for (int i = n; i >= t + 1; --i)
    {
        if (i > x.digitCount())
            continue;
        unsigned int* qd = &q.digits[i - t - 1];
        unsigned int xi = x.digits[i];
        unsigned int yt = y.digits[t];
        if (xi == yt)
            *qd = 0xFFFFFFFFu;
        else
            *qd = static_cast<unsigned int>(
                ((static_cast<unsigned long long>(xi) << 32) | x.digits[i - 1]) / yt);
        *qd = *qd + 1;
        unsigned int qv;
        do
        {
            qv = --*qd;
            t1.sign = 1;
            memset(t1.digits, 0, sizeof(t1.digits));
            t1.digits[0] = t - 1 >= 0 ? y.digits[t - 1] : 0;
            t1.digits[1] = yt;
            t1.bits = 64 - leadingZeros(yt, digit_bit_r);
            t1.mul(qv);
            t2.digits[0] = i - 2 >= 0 ? x.digits[i - 2] : 0;
            t2.digits[1] = i - 1 >= 0 ? x.digits[i - 1] : 0;
            t2.digits[2] = xi;
            t2.bits = 96 - leadingZeros(xi, digit_bit_r);
        } while (absCompare(&t1, &t2) > 0);

        t3.sign = y.sign;
        t3.bits = y.bits;
        memcpy(t3.digits, y.digits, sizeof(t3.digits));
        t3.mul(qv);
        t3.leftShiftDigit(&t3, i - t - 1, true);
        x.Sub(&x, &t3);
        if (x.bits != 0 && x.sign == -1)
        {
            // The sign of t3 is not set again here.
            t3.leftShiftDigit(&y, i - t - 1, false);
            x.Add(&x, &t3);
            *qd = qv - 1;
        }
    }

    if (x.isZero())
        x.sign = 1;
    else
        x.sign = a->sign;
    if (quot != 0)
    {
        q.setBit(q.digitCount());
        if (&q != quot)
            quot->Set(&q, neg);
    }
    if (rem != 0)
    {
        x.RightShift(&x, norm);
        int count = b->digitCount();
        for (int i = count; i < x.digitCount(); ++i)
            x.digits[i] = 0;
        x.setBit(count);
        if (&x != rem)
            rem->Set(&x, 1);
    }
}

// 0x59ab0 (LobbyGate)
// LIFT: LTCG removed quot. The binary gets rem in r8 (0x59AB4, 0x59ABA). The only call (0x561D2)
// passes rcx = a, edx = b, r8 = &rem. The code uses only rem.
void BigInteger::Divide(BigInteger const* a, unsigned int b, BigInteger* quot, unsigned int* rem)
{
    (void)quot;
    if (rem == 0)
        return;
    if (a->bits == 0 || b == 0 || a->isZero() || b == 1 || b == 0xFFFFFFFFu)
    {
        *rem = 0;
        return;
    }
    unsigned long long w = 0;
    if (((b - 1) & b) != 0)
    {
        // BUG: 0x59B12 starts at digits[digitCount()], one digit above the top digit.
        for (long long i = a->digitCount(); i >= 0; --i)
        {
            w = a->digits[i] | (w << 32);
            if (w >= b)
                w -= b * static_cast<unsigned long long>(static_cast<unsigned int>(w / b));
        }
        *rem = static_cast<unsigned int>(w);
    }
    else
    {
        // BUG: 0x59AF0 reads up to 128 entries of digit_bit_r, but the table has 32.
        for (unsigned int k = 0; k < 0x80; ++k)
        {
            if (b == digit_bit_r[k])
            {
                w = 31 - k;
                break;
            }
        }
        *rem = a->digits[0] & digit_mask[static_cast<int>(w)];
    }
}
