#include <bits/stdc++.h>
using namespace std;

struct Trie01 {
    /*
        B 表示二进制位数。

        如果 x <= 1e9，B = 31，枚举 30 ~ 0。
        如果 x 是 int 非负数，B = 31 基本够用。
        如果需要 unsigned int，可以改成 B = 32。
        如果是 long long，可以改成 B = 63，并把 int 改 long long。
    */
    static const int B = 31;

    struct Node {
        int son[2];
        int cnt; // 当前子树中有多少个数
        int mn;  // 当前子树中的最小值

        Node() {
            son[0] = son[1] = -1;
            cnt = 0;
            mn = INT_MAX;
        }
    };

    vector<Node> tr;

    Trie01() {
        clear();
    }

    void clear() {
        tr.clear();
        tr.push_back(Node()); // 0 是根节点
    }

    int newNode() {
        tr.push_back(Node());
        return (int)tr.size() - 1;
    }

    int size() {
        return tr[0].cnt;
    }

    bool empty() {
        return tr[0].cnt == 0;
    }

    // 插入 x
    void insert(int x) {
        int p = 0;
        tr[p].cnt++;
        tr[p].mn = min(tr[p].mn, x);

        for (int i = B - 1; i >= 0; i--) {
            int b = (x >> i) & 1;

            if (tr[p].son[b] == -1) {
                tr[p].son[b] = newNode();
            }

            p = tr[p].son[b];
            tr[p].cnt++;
            tr[p].mn = min(tr[p].mn, x);
        }
    }

    // 判断 x 是否存在
    bool contains(int x) {
        int p = 0;

        for (int i = B - 1; i >= 0; i--) {
            int b = (x >> i) & 1;

            if (tr[p].son[b] == -1) {
                return false;
            }

            p = tr[p].son[b];
        }

        return tr[p].cnt > 0;
    }

    // 删除 x
    // 如果 x 不存在，返回 false
    bool erase(int x) {
        if (!contains(x)) {
            return false;
        }

        int p = 0;
        tr[p].cnt--;

        for (int i = B - 1; i >= 0; i--) {
            int b = (x >> i) & 1;
            p = tr[p].son[b];
            tr[p].cnt--;
        }

        return true;
    }

    // 查询 x 与 Trie 中某个数的最大异或值
    int maxXor(int x) {
        if (empty()) {
            return -1;
        }

        int p = 0;
        int ans = 0;

        for (int i = B - 1; i >= 0; i--) {
            int b = (x >> i) & 1;
            int want = b ^ 1;

            if (tr[p].son[want] != -1 && tr[tr[p].son[want]].cnt > 0) {
                ans |= 1 << i;
                p = tr[p].son[want];
            } else {
                p = tr[p].son[b];
            }
        }

        return ans;
    }

    // 查询 x 与 Trie 中某个数的最小异或值
    int minXor(int x) {
        if (empty()) {
            return -1;
        }

        int p = 0;
        int ans = 0;

        for (int i = B - 1; i >= 0; i--) {
            int b = (x >> i) & 1;

            if (tr[p].son[b] != -1 && tr[tr[p].son[b]].cnt > 0) {
                p = tr[p].son[b];
            } else {
                ans |= 1 << i;
                p = tr[p].son[b ^ 1];
            }
        }

        return ans;
    }

    // 查询 x 与 Trie 中所有数异或后的第 k 大值
    // k 从 1 开始
    // 如果 k 超过元素个数，返回 -1
    int kthMaxXor(int x, int k) {
        if (k <= 0 || k > size()) {
            return -1;
        }

        int p = 0;
        int ans = 0;

        for (int i = B - 1; i >= 0; i--) {
            int b = (x >> i) & 1;
            int want = b ^ 1;

            int right = tr[p].son[want];
            int rightCnt = 0;

            if (right != -1) {
                rightCnt = tr[right].cnt;
            }

            if (rightCnt >= k) {
                ans |= 1 << i;
                p = right;
            } else {
                k -= rightCnt;
                p = tr[p].son[b];
            }
        }

        return ans;
    }

// 给你一个数 x，再给一个限制 limit，
// 只允许在 Trie 里面选择 值 <= limit 的数 y，
// 问 x ^ y 的最大值是多少。
    int maxXorWithLimitVal(int x, int limit) {
        if (empty() || tr[0].mn > limit) {
            return -1;
        }

        int p = 0;
        int ans = 0;

        for (int i = B - 1; i >= 0; i--) {
            int b = (x >> i) & 1;
            int want = b ^ 1;

            int nxt = tr[p].son[want];

            if (nxt != -1 && tr[nxt].cnt > 0 && tr[nxt].mn <= limit) {
                ans |= 1 << i;
                p = nxt;
            } else {
                p = tr[p].son[b];
            }
        }

        return ans;
    }

    // 统计有多少个 y 满足：
    // x ^ y <= limit
    int countXorLE(int x, int limit) {
        if (empty() || limit < 0) {
            return 0;
        }

        /*
            统计 x ^ y <= limit
            等价于统计 x ^ y < limit + 1

            当 high 的某一位是 1：
            当前位异或值可以取 0，后面随便取；
            然后继续走当前位异或值为 1 的分支。
        */

        long long high = 1LL + limit;
        int p = 0;
        int ans = 0;

        for (int i = B - 1; i >= 0; i--) {
            if (p == -1) {
                break;
            }

            int b = (x >> i) & 1;

            if ((high >> i) & 1) {
                int same = tr[p].son[b];

                if (same != -1) {
                    ans += tr[same].cnt;
                }

                p = tr[p].son[b ^ 1];
            } else {
                p = tr[p].son[b];
            }
        }

        return ans;
    }
};