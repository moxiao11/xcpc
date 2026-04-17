#include <iostream>
using namespace std;

const int N = 200010;

struct DSU {
    int fa[N], sz[N];

    void init(int n) {
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }
} dsu;