
#include <iostream>

// 快速幂求逆元
long long inv1(long long a, long long p)
{
    long long res = 1, b = p - 2;
    while (b)
    {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
// exgcd求逆元
long long exgcd(long long a, long long b, long long &x, long long &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }
    long long d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

long long inv2(long long a, long long mod)
{
    long long x, y;
    if (exgcd(a, mod, x, y) != 1) return -1;
    return (x % mod + mod) % mod;
}
