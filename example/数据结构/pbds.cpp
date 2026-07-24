/**
 * __gnu_pbds::priority_queue (Policy-Based Data Structures)
 *
 * 头文件: <ext/pb_ds/priority_queue.hpp>
 * 命名空间: __gnu_pbds
 *
 * 模板参数:
 *   template<typename Value_Type,
 *            typename Cmp_Fn = std::less<Value_Type>,
 *            typename Tag = pairing_heap_tag,
 *            typename Allocator = std::allocator<char>>
 *   class priority_queue;
 *
 * 五种底层堆 (Tag):
 *   - pairing_heap_tag     : push/join O(1), pop 均摊 O(log n)  ★推荐
 *   - binomial_heap_tag    : push 均摊 O(1), pop O(log n), join O(log n)
 *   - binary_heap_tag      : push/pop 最坏 O(log n), 不支持 join
 *   - thin_heap_tag        : push O(1), pop 均摊 O(log n)
 *   - rc_binomial_heap_tag : push/pop 最坏 O(log n)
 *
 * 核心 API:
 *   push(x)        -> 入队，返回 point_iterator
 *   pop()          -> 出队（无返回值）
 *   top()          -> 获取堆顶引用
 *   empty() / size() -> 判空 / 大小
 *   modify(it, x)  -> 修改迭代器指向的元素为 x
 *   erase(it)      -> 删除迭代器指向的元素
 *   join(other)    -> 合并另一个堆（other 被清空）
 *   begin()/end()  -> 遍历（不保证有序）
 */

#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;

// ==================== 1. 基础用法 (pairing_heap) ====================

void basic_usage() {
    // 默认大顶堆 (less = 大的在前)
    __gnu_pbds::priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(5);
    cout << pq.top() << '\n';  // 5

    // 小顶堆
    __gnu_pbds::priority_queue<int, greater<int>> min_pq;
    min_pq.push(3);
    min_pq.push(1);
    min_pq.push(5);
    cout << min_pq.top() << '\n';  // 1

    // 指定底层堆类型
    __gnu_pbds::priority_queue<int, less<int>, pairing_heap_tag> pq2;
    __gnu_pbds::priority_queue<int, less<int>, binomial_heap_tag> pq3;
    // __gnu_pbds::priority_queue<int, less<int>, binary_heap_tag> pq4;  // 不常用
}

// ==================== 2. 迭代器用法（核心优势）====================

void iterator_usage() {
    __gnu_pbds::priority_queue<int> pq;
    auto it1 = pq.push(10);
    auto it2 = pq.push(20);
    auto it3 = pq.push(30);

    // 修改元素（常用于 Dijkstra 的 decrease-key）
    pq.modify(it1, 100);  // 把 10 改成 100，内部自动调整堆

    // 删除元素
    pq.erase(it2);        // 删除 20

    // 遍历（不保证顺序，但可以遍历所有元素）
    for (auto it = pq.begin(); it != pq.end(); ++it)
        cout << *it << ' ';

    // 用 range-based for 也可以（C++11）
    for (int x : pq) cout << x << ' ';
}

// ==================== 3. 合并两个堆 ====================

void join_example() {
    __gnu_pbds::priority_queue<int> pq1, pq2;
    pq1.push(1);
    pq1.push(5);
    pq2.push(3);
    pq2.push(7);

    pq1.join(pq2);            // pq2 的全部元素合并到 pq1
    cout << pq2.size() << '\n'; // 0 — pq2 被清空
    cout << pq1.top() << '\n';  // 7

    // 可以用 begin()/end() 另存为 vector
    vector<int> saved(pq1.begin(), pq1.end());
}

// ==================== 4. 结构体优先队列 ====================

struct Node {
    int id, dist;
    bool operator<(const Node& o) const { return dist > o.dist; }  // 小顶堆
};

void struct_example() {
    __gnu_pbds::priority_queue<Node> pq;
    auto it1 = pq.push({1, 100});
    auto it2 = pq.push({2, 50});
    cout << pq.top().id << '\n';  // 2（dist 最小）

    // 典型的 Dijkstra decrease-key
    pq.modify(it1, {1, 30});
    cout << pq.top().id << '\n';  // 1
}

// ==================== 5. Dijkstra with decrease-key ====================

void dijkstra_example() {
    int n = 100000;
    vector<vector<pair<int, int>>> g(n);
    const int INF = 1e9;

    using pq_t = __gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>>;
    pq_t pq;
    vector<pq_t::point_iterator> it(n);
    vector<int> dist(n, INF);

    dist[0] = 0;
    it[0] = pq.push({0, 0});  // {dist, node}

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (it[v] == nullptr)  // 尚未入队
                    it[v] = pq.push({dist[v], v});
                else
                    pq.modify(it[v], {dist[v], v});  // decrease-key
            }
        }
    }
}

// ==================== 6. 左偏树可并堆替代 ====================
// pbds 的 pairing_heap 的 join 是 O(1)，可以完美替代手写左偏树

void leftist_tree_replacement() {
    __gnu_pbds::priority_queue<int, less<int>, pairing_heap_tag> pq1, pq2;
    pq1.push(5); pq1.push(3);
    pq2.push(7); pq2.push(1);
    pq1.join(pq2);  // O(1) 合并
    while (!pq1.empty()) {
        cout << pq1.top() << ' ';
        pq1.pop();
    }
    // 输出: 7 5 3 1
}

int main() {
    basic_usage();
    iterator_usage();
    join_example();
    struct_example();
    leftist_tree_replacement();
}
