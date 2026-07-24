#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
const int K = 20;

int st[N][K];
int lg[N];

// 初始化 RMQ
// a[] 下标从 1 开始
void init_rmq(vector<int>& a, int n)
{
    // 预处理 log
    lg[1] = 0;
    for(int i = 2; i <= n; i++)
    {
        lg[i] = lg[i / 2] + 1;
    }

    // 初始化长度为 1 的区间
    for(int i = 1; i <= n; i++)
    {
        st[i][0] = a[i];
    }

    // 建 ST 表
    for(int j = 1; (1 << j) <= n; j++)
    {
        for(int i = 1; i + (1 << j) - 1 <= n; i++)
        {
            st[i][j] = max(
                st[i][j - 1],
                st[i + (1 << (j - 1))][j - 1]
            );
        }
    }
}

// 查询区间 [l, r] 最大值
int query_max(int l, int r)
{
    if(l > r) swap(l, r);

    int k = lg[r - l + 1];

    return max(
        st[l][k],
        st[r - (1 << k) + 1][k]
    );
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);

    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    init_rmq(a, n);

    while(m--)
    {
        int l, r;
        cin >> l >> r;

        cout << query_max(l, r) << '\n';
    }

    return 0;
}