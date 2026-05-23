#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define endl '\n'
const int N = 1e7 + 10 ;

int phi[N + 1];
int primes[N + 1], cnt;
bool st[N + 1];


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

void get_phi(int n)
{
    phi[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        if (!st[i])
        {
            primes[cnt++] = i;
            phi[i] = i - 1;
        }

        for (int j = 0; j < cnt && 1LL * i * primes[j] <= n; j++)
        {
            int p = primes[j];
            st[i * p] = true;

            if (i % p == 0)
            {
                phi[i * p] = phi[i] * p;
                break;
            }
            else
            {
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    get_phi(N);
    int t ; cin >> t;
    while(t -- ) 
    {
        int n ; cin >> n ;
       

        vector<int> a (n) ; 
        vector<int> b(n) ; 
        
        for(int i = 0 ; i < n; i ++ ) cin >> a[i]; 
        for(int i = 0 ; i < n ; i ++ ) cin >> b[i]; 
        if(n > 1000) {
            cout << 0 << endl;
            continue ;
        }
        vector<vector<ll>> c(n, vector<ll>(n));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                ll x = (a[i] ^ b[j]) % MOD ; 
                ll y = (phi[a[i]] + phi[b[j]] ) % MOD ; 
                c[i][j] = x * y % MOD ;                
            }
        }
        cout << det(c) << endl; 
    }

    return 0;
}