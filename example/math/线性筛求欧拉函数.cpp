#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

int phi[N + 1];
int primes[N + 1], cnt;
bool st[N + 1];

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
    int n;
    cin >> n;

    get_phi(n);

    for (int i = 1; i <= n; i++)
    {
        cout << "phi[" << i << "] = " << phi[i] << '\n';
    }

    return 0;
}