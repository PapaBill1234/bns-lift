// NumberTheory.obj (BloodCrypto). The code follows libtommath
// (mp_exptmod_fast, mp_invmod_slow, fast_mp_invmod).
// The compiler put Add, Sub and RightShift inline in invMod and InvMod. The lift calls them.
#include "BigInteger.h"
#include <string.h>

namespace
{
// ❓ Inline helper. No PDB symbol.
inline bool isOdd(BigInteger const& x)
{
    return x.bits != 0 && (x.digits[0] & 1) != 0;
}

// ❓ Inline helper. No PDB symbol. A value is "even" for the loops when bits != 0 and bit 0 is clear.
inline bool isEvenNonZero(BigInteger const& x)
{
    return x.bits != 0 && (x.digits[0] & 1) == 0;
}

// ❓ Inline helper. No PDB symbol. Same test as the code: sign, bits, then the digits.
inline bool isEqual(BigInteger const& x, BigInteger const& y, int (*absCompare)(BigInteger const*, BigInteger const*))
{
    return x.sign == y.sign && x.bits == y.bits && absCompare(&x, &y) == 0;
}
} // namespace

// 0x4ae30
void BigInteger::expMod(BigInteger const* a, BigInteger const* e, BigInteger const* n)
{
    BigInteger M[64];
    BigInteger res;

    int winsize;
    int ebits = e->bits;
    if (ebits <= 21)
        winsize = 1;
    else if (ebits <= 36)
        winsize = 3;
    else if (ebits <= 140)
        winsize = 4;
    else
        winsize = ebits > 450 ? 6 : 5;

    if ((n->digits[0] & 1) == 0)
    {
        memset(res.digits, 0, sizeof(res.digits));
        return;
    }

    // mp_montgomery_setup
    unsigned int b = n->digits[0];
    unsigned int x = (((b + 2) & 4) << 1) + b;
    x *= 2 - b * x;
    x *= 2 - b * x;
    x *= 2 - b * x;
    unsigned int rho = 0u - x;

    res.montgomeryNormalize(n);

    BigInteger M1;
    if (absCompare(n, a) > 0)
    {
        if (a != &M1)
        {
            M1.sign = a->sign;
            M1.bits = a->bits;
            memcpy(M1.digits, a->digits, sizeof(M1.digits));
        }
    }
    else
    {
        Divide(a, n, 0, &M1);
    }

    BigInteger tmp;
    tmp.Mul(&M1, &res);
    Divide(&tmp, n, 0, &M1);

    int half = 1 << (winsize - 1);
    BigInteger* top = &M[half];
    if (&M1 != top)
    {
        top->sign = M1.sign;
        top->bits = M1.bits;
        for (int i = 0; i < MAX_DIGITS; ++i)
            top->digits[i] = M1.digits[i];
    }
    for (int i = 0; i < winsize - 1; ++i)
    {
        top->Sqr(top);
        top->montgomeryReduce(n, rho);
    }
    for (int i = half + 1; i < (1 << winsize); ++i)
    {
        M[i].Mul(&M[i - 1], &M1);
        M[i].montgomeryReduce(n, rho);
    }

    int mode = 0;
    int bitcnt = 1;
    int bitcpy = 0;
    int bitbuf = 0;
    int digidx = e->digitCount() - 1;
    unsigned int buf = 0;
    for (;;)
    {
        if (--bitcnt == 0)
        {
            if (digidx == -1)
                break;
            buf = e->digits[digidx--];
            bitcnt = 32;
        }
        int y = static_cast<int>(buf >> 31);
        buf <<= 1;
        if (mode == 0 && y == 0)
            continue;
        if (mode == 1 && y == 0)
        {
            res.Sqr(&res);
            res.montgomeryReduce(n, rho);
            continue;
        }
        bitbuf |= y << (winsize - ++bitcpy);
        mode = 2;
        if (bitcpy == winsize)
        {
            for (int i = 0; i < winsize; ++i)
            {
                res.Sqr(&res);
                res.montgomeryReduce(n, rho);
            }
            res.Mul(&res, &M[bitbuf]);
            res.montgomeryReduce(n, rho);
            bitcpy = 0;
            bitbuf = 0;
            mode = 1;
        }
    }

    if (mode == 2 && bitcpy > 0)
    {
        for (int i = 0; i < bitcpy; ++i)
        {
            res.Sqr(&res);
            res.montgomeryReduce(n, rho);
            bitbuf <<= 1;
            if ((bitbuf & (1 << winsize)) != 0)
            {
                res.Mul(&res, &M1);
                res.montgomeryReduce(n, rho);
            }
        }
    }

    res.montgomeryReduce(n, rho);
    if (&res != this)
    {
        sign = res.sign;
        bits = res.bits;
        memcpy(digits, res.digits, sizeof(digits));
    }
    memset(res.digits, 0, sizeof(res.digits));
}

// 0x49db0
bool BigInteger::invMod(BigInteger const* a, BigInteger const* b)
{
    // b must be positive and not zero.
    if (b->bits != 0 && b->sign == -1)
        return false;
    if (b->sign == 1 && b->bits == 1 && b->digits[0] == 0)
        return false;

    BigInteger x;
    BigInteger y;
    BigInteger u;
    BigInteger v;
    BigInteger A;
    BigInteger B;
    BigInteger C;
    BigInteger D;
    BigInteger one;
    one.Set(1LL);
    BigInteger zero;

    Divide(a, b, 0, &x);
    y.Set(b, 1);
    if (isEvenNonZero(x) && isEvenNonZero(y))
        return false;

    u.Set(&x, 1);
    v.Set(&y, 1);
    A.Set(1LL);
    D.Set(1LL);

    do
    {
        while (isEvenNonZero(u))
        {
            u.RightShift(&u, 1);
            if (isOdd(A) || isOdd(B))
            {
                A.Add(&A, &y);
                B.Sub(&B, &x);
            }
            A.RightShift(&A, 1);
            B.RightShift(&B, 1);
        }
        while (isEvenNonZero(v))
        {
            v.RightShift(&v, 1);
            if (isOdd(C) || isOdd(D))
            {
                C.Add(&C, &y);
                D.Sub(&D, &x);
            }
            C.RightShift(&C, 1);
            D.RightShift(&D, 1);
        }
        int c = u.sign;
        if (u.sign < v.sign)
            c = -1;
        else if (u.bits != 0)
            c = absCompare(&u, &v);
        if (c < 0)
        {
            v.Sub(&v, &u);
            C.Sub(&C, &A);
            D.Sub(&D, &B);
        }
        else
        {
            u.Sub(&u, &v);
            A.Sub(&A, &C);
            B.Sub(&B, &D);
        }
    } while (!(u.sign == 1 && u.bits == 1 && u.digits[0] == 0));

    if (!isEqual(v, one, absCompare))
        return false;

    while (C.sign <= zero.sign && (C.sign < zero.sign || (C.bits != 0 && absCompare(&C, &zero) < 0)))
        C.Add(&C, b);
    while (absCompare(&C, b) >= 0)
        C.Sub(&C, b);

    if (&C != this)
    {
        sign = C.sign;
        bits = C.bits;
        memcpy(digits, C.digits, sizeof(digits));
    }
    return true;
}

// 0x48f10
bool BigInteger::InvMod(BigInteger const* a, BigInteger const* b)
{
    if (b->bits != 0 && (b->digits[0] & 1) == 0)
        return invMod(a, b);

    BigInteger x;
    BigInteger y;
    BigInteger u;
    BigInteger v;
    BigInteger B;
    BigInteger D;
    BigInteger one;
    one.Set(1LL);

    x.Set(b, 1);
    y.Set(a, 1);
    y.sign = 1;
    u.Set(&x, 1);
    v.Set(&y, 1);
    D.Set(1LL);

    do
    {
        while (isEvenNonZero(u))
        {
            u.RightShift(&u, 1);
            if (isOdd(B))
                B.Sub(&B, &x);
            B.RightShift(&B, 1);
        }
        while (isEvenNonZero(v))
        {
            v.RightShift(&v, 1);
            if (isOdd(D))
                D.Sub(&D, &x);
            D.RightShift(&D, 1);
        }
        int c = u.sign;
        if (u.sign < v.sign)
            c = -1;
        else if (u.bits != 0)
            c = absCompare(&u, &v);
        if (c < 0)
        {
            v.Sub(&v, &u);
            D.Sub(&D, &B);
        }
        else
        {
            u.Sub(&u, &v);
            B.Sub(&B, &D);
        }
    } while (!(u.sign == 1 && u.bits == 1 && u.digits[0] == 0));

    if (!isEqual(v, one, absCompare))
        return false;

    while (D.bits != 0 && D.sign == -1)
        D.Add(&D, b);

    if (&D != this)
    {
        sign = a->sign * D.sign;
        bits = D.bits;
        memcpy(digits, D.digits, sizeof(digits));
    }
    return true;
}
