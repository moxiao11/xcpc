#include <iostream>
using namespace std;
#define int long long

int qmi(int a, int b, int p)
{
    int res = 1 % p;
    while (b)
    {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int C(int n, int m, int p)
{
    if (m > n) return 0;
    int up = 1, down = 1;
    for (int i = 1; i <= m; i++)
    {
        up = up * (n - i + 1) % p;
        down = down * i % p;
    }
    return up * qmi(down, p - 2, p) % p;
}

int lucas(int n, int m, int p)
{
    if (m == 0) return 1;
    return C(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
}

signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, m, p;
        cin >> n >> m >> p;
        cout << lucas(n, m, p) << endl;
    }
    return 0;
}