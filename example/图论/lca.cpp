#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int n, LOG;
    vector<int> dep;
    vector<vector<int>> fa;
    vector<vector<int>> g;

    LCA(int n = 0) {
        init(n);
    }

    void init(int _n) {
        n = _n;
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        dep.assign(n + 1, 0);
        fa.assign(n + 1, vector<int>(LOG, 0));
        g.assign(n + 1, vector<int>());
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int u, int father) {
        fa[u][0] = father;
        dep[u] = dep[father] + 1;

        for (int i = 1; i < LOG; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }

        for (int v : g[u]) {
            if (v == father) continue;
            dfs(v, u);
        }
    }

    void build(int root = 1) {
        dfs(root, 0);
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);

        for (int i = LOG - 1; i >= 0; i--) {
            if (dep[fa[u][i]] >= dep[v]) {
                u = fa[u][i];
            }
        }

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; i--) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }

        return fa[u][0];
    }

    int dist(int u, int v) {
        int p = lca(u, v);
        return dep[u] + dep[v] - 2 * dep[p];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    LCA tree(n);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree.add_edge(u, v);
    }

    tree.build(1);

    while (q--) {
        int u, v;
        cin >> u >> v;

        cout << tree.lca(u, v) << '\n';

        // 如果题目问距离，用这个：
        // cout << tree.dist(u, v) << '\n';
    }

    return 0;
}