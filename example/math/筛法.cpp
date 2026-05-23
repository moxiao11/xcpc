#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

int primes[N], cnt;
bool st[N]; 
// st[i] = true 表示 i 不是质数

void get_primes(int n) {
    cnt = 0;

    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
        }

        for (int j = 0; j < cnt && 1LL * primes[j] * i <= n; j++) {
            st[primes[j] * i] = true;

            if (i % primes[j] == 0) {
                break;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;

    get_primes(n);

    for (int i = 0; i < cnt; i++) {
        cout << primes[i] << " ";
    }

    return 0;
}