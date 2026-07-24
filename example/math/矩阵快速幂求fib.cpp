#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Matrix {
    int a[2][2];

    Matrix() {
        memset(a, 0, sizeof a);
    }
};

int mod;

// 矩阵乘法
Matrix mul(Matrix A, Matrix B) {
    Matrix C;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % mod;
            }
        }
    }

    return C;
}

// 矩阵快速幂
Matrix qpow(Matrix A, int b) {
    Matrix res;

    // 单位矩阵
    res.a[0][0] = 1;
    res.a[1][1] = 1;

    while (b) {
        if (b & 1) res = mul(res, A);
        A = mul(A, A);
        b >>= 1;
    }

    return res;
}

// 求 Fibonacci 第 n 项，F0 = 0, F1 = 1
int fib(int n) {
    if (n == 0) return 0 % mod;
    if (n == 1) return 1 % mod;

    Matrix base;
    base.a[0][0] = 1;
    base.a[0][1] = 1;
    base.a[1][0] = 1;
    base.a[1][1] = 0;

    Matrix ans = qpow(base, n - 1);

    return ans.a[0][0] % mod;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n >> mod;

    cout << fib(n) << '\n';

    return 0;
}