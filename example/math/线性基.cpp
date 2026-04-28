#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

struct LinearBasis {
    static const int LOG = 63; // ull 最大到 2^64 - 1
    ull p[LOG + 1];

    LinearBasis() {
        memset(p, 0, sizeof p);
    }

    // 插入 x，成功返回 true，说明 x 线性无关
    bool insert(ull x) {
        for (int i = LOG; i >= 0; i--) {
            if (((x >> i) & 1) == 0) continue;

            if (!p[i]) {
                p[i] = x;
                return true;
            }

            x ^= p[i];
        }
        return false;
    }

    // 查询当前集合能异或出的最大值
    ull query_max() {
        ull res = 0;
        for (int i = LOG; i >= 0; i--) {
            res = max(res, res ^ p[i]);
        }
        return res;
    }

    // 查询 x 与集合中若干数异或后能得到的最大值
    ull query_max_with(ull x) {
        ull res = x;
        for (int i = LOG; i >= 0; i--) {
            res = max(res, res ^ p[i]);
        }
        return res;
    }

    // 查询最小非零异或值
    ull query_min() {
        for (int i = 0; i <= LOG; i++) {
            if (p[i]) return p[i];
        }
        return 0;
    }

    // 判断 x 是否能被当前线性基表示
    bool check(ull x) {
        for (int i = LOG; i >= 0; i--) {
            if (((x >> i) & 1) == 0) continue;

            if (!p[i]) return false;
            x ^= p[i];
        }
        return true;
    }

    // 合并另一个线性基
    void merge(const LinearBasis& other) {
        for (int i = 0; i <= LOG; i++) {
            if (other.p[i]) insert(other.p[i]);
        }
    }

    // 清空
    void clear() {
        memset(p, 0, sizeof p);
    }
};

int main() {
    int n;
    cin >> n;

    LinearBasis lb;

    for (int i = 1; i <= n; i++) {
        ull x;
        cin >> x;
        lb.insert(x);
    }

    cout << lb.query_max() << endl;

    return 0;
}