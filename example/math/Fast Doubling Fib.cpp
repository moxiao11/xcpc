#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;

// 返回 {F(n), F(n + 1)}
pair<ll, ll> fib(ll n) {
    if (n == 0) return {0, 1};

    auto [a, b] = fib(n / 2);
    // a = F(k), b = F(k + 1)

    ll c = a * ((2 * b % MOD - a + MOD) % MOD) % MOD;
    ll d = (a * a % MOD + b * b % MOD) % MOD;

    if (n & 1) {
        return {d, (c + d) % MOD};
    } else {
        return {c, d};
    }
}

int main() {
    ll n;
    cin >> n;

    auto [fn, fn1] = fib(n);

    cout << fn << ' ' << fn1 << endl;

    return 0;
}