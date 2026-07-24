#include <iostream>
#include <algorithm>
#include <vector>
using namespace std; 
using ll = long long;

struct BIT {
    int n;
    vector<int> tr;

    BIT(int n = 0) {
        init(n);
    }

    void init(int _n) {
        n = _n;
        tr.assign(n + 1, 0);
    }

    int lowbit(int x) {
        return x & -x;
    }

    void add(int x, int v) {
        for (int i = x; i <= n; i += lowbit(i)) {
            tr[i] += v;
        }
    }

    int sum(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= lowbit(i)) {
            res += tr[i];
        }
        return res;
    }
};

ll inversion_count(vector<int> a) {
    int n = a.size();

    vector<int> nums = a;
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    BIT bit(nums.size());

    ll ans = 0;

    for (int i = 0; i < n; i++) {
        int x = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin() + 1;

        ans += i - bit.sum(x);
        bit.add(x, 1);
    }

    return ans;
}
int main()
{
    return 0 ; 
}