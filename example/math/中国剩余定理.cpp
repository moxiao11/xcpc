#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    ll x1, y1;
    ll g = exgcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - a / b * y1;

    return g;
}

// 合并：
// x ≡ a1 (mod m1)
// x ≡ a2 (mod m2)
bool merge(ll &a1, ll &m1, ll a2, ll m2) {
    ll x, y;
    ll c = a2 - a1;

    ll g = exgcd(m1, m2, x, y);

    if (c % g != 0) return false;

    i128 mod = m2 / g;

    i128 t = (i128)(c / g) * x;
    t = (t % mod + mod) % mod;

    i128 new_mod = (i128)m1 / g * m2;
    i128 new_ans = (i128)a1 + (i128)m1 * t;

    a1 = (ll)((new_ans % new_mod + new_mod) % new_mod);
    m1 = (ll)new_mod;

    return true;
}

// m[i] 是模数，a[i] 是余数
pair<bool, ll> exCRT(vector<ll> m, vector<ll> a) {
    int n = m.size();

    ll ans = a[0];
    ll lcm = m[0];

    ans = (ans % lcm + lcm) % lcm;

    for (int i = 1; i < n; i++) {
        if (!merge(ans, lcm, a[i], m[i])) {
            return {false, -1};
        }
    }

    return {true, ans};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    vector<ll> a(k), r(k);

    for (int i = 0; i < k; i++) {
        cin >> a[i] >> r[i];
    }

    // x mod a[i] = r[i]
    // 即 x ≡ r[i] (mod a[i])
    auto t = exCRT(a, r);

    if (!t.first) {
        cout << -1 << '\n';
    } else {
        cout << t.second << '\n';
    }

    return 0;
}