#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 998244353;

ll qpow(ll a, ll b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll det(vector<vector<ll>> a)
{
    int n = a.size();
    ll ans = 1;

    for (int i = 0; i < n; i++)
    {
        int pos = -1;

        for (int j = i; j < n; j++)
        {
            if (a[j][i] != 0)
            {
                pos = j;
                break;
            }
        }

        if (pos == -1) return 0;

        if (pos != i)
        {
            swap(a[pos], a[i]);
            ans = (MOD - ans) % MOD;
        }

        ll pivot = a[i][i];
        ans = ans * pivot % MOD;

        ll inv = qpow(pivot, MOD - 2);

        for (int j = i + 1; j < n; j++)
        {
            ll factor = a[j][i] * inv % MOD;

            for (int k = i; k < n; k++)
            {
                a[j][k] = (a[j][k] - factor * a[i][k]) % MOD;
                if (a[j][k] < 0) a[j][k] += MOD;
            }
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<ll>> a(n, vector<ll>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
            a[i][j] %= MOD;
            if (a[i][j] < 0) a[i][j] += MOD;
        }
    }

    cout << det(a) << '\n';

    return 0;
}