#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using u128 = __uint128_t;
//判断longlong以内的质数
// 快速乘法：防止 long long 乘法溢出
ull qmul(ull a, ull b, ull mod) {
    return (u128)a * b % mod;
}

// 快速幂
ull qpow(ull a, ull b, ull mod) {
    ull res = 1;
    while (b) {
        if (b & 1) res = qmul(res, a, mod);
        a = qmul(a, a, mod);
        b >>= 1;
    }
    return res;
}

// Miller-Rabin 判素数
bool isPrime(ull n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    // 把 n-1 写成 d * 2^s
    ull d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    // 这些底数对 64 位整数范围内是够用的
    vector<ull> test = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (ull a : test) {
        if (a >= n) continue;
        ull x = qpow(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool ok = false;
        for (ull r = 1; r < s; r++) {
            x = qmul(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }
    return true;
}

int main() {
    ull n;
    cin >> n;
    if (isPrime(n)) cout << "Prime\n";
    else cout << "Not Prime\n";
    return 0;
}