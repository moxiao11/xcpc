#include <iostream>
using namespace std;

typedef long long LL;

const int N = 100010;
const int mod = 1000000007;

int fact[N], infact[N];

LL qmi(LL a, LL b, LL p)
{
    LL res = 1;
    while (b)
    {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

void init()
{
    fact[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fact[i] = (LL)fact[i - 1] * i % mod;
    }

    infact[N - 1] = qmi(fact[N - 1], mod - 2, mod);

    for (int i = N - 2; i >= 0; i--)
    {
        infact[i] = (LL)infact[i + 1] * (i + 1) % mod;
    }
}

LL C(int a, int b)
{
    if (b < 0 || b > a) return 0;
    return (LL)fact[a] * infact[b] % mod * infact[a - b] % mod;
}

int main()
{
    init();

    int n;
    cin >> n;

    while (n--)
    {
        int a, b;
        cin >> a >> b;
        cout << C(a, b) << endl;
    }

    return 0;
}