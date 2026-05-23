#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

struct Edge {
    int u, v, w;

    bool operator < (const Edge& other) const {
        return w < other.w;
    }
};

int n, m;
int p[N];
vector<Edge> edges;

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int kruskal() {
    sort(edges.begin(), edges.end());

    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }

    int res = 0;   // 最小生成树总权值
    int cnt = 0;   // 已经加入的边数

    for (auto e : edges) {
        int a = find(e.u);
        int b = find(e.v);

        if (a != b) {
            p[a] = b;
            res += e.w;
            cnt++;
        }
    }

    if (cnt < n - 1) {
        return -1; // 图不连通，不存在最小生成树
    }

    return res;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    int ans = kruskal();

    if (ans == -1) {
        cout << "impossible" << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}