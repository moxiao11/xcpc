#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct Point
{
    long long x, y;
};

long long cross(const Point& a, const Point& b, const Point& c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cmp(const Point& a, const Point& b)
{
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

// 传入所有点 p
// 返回凸包上的点，逆时针顺序
vector<Point> convexHull(vector<Point> p)
{
    sort(p.begin(), p.end(), cmp);

    int n = p.size();
    if (n <= 1) return p;

    vector<Point> stk(2 * n);
    int top = 0;

    // 下凸壳
    for (int i = 0; i < n; i++)
    {
        while (top >= 2 && cross(stk[top - 2], stk[top - 1], p[i]) <= 0) top--;
        stk[top++] = p[i];
    }

    // 上凸壳
    for (int i = n - 2, t = top + 1; i >= 0; i--)
    {
        while (top >= t && cross(stk[top - 2], stk[top - 1], p[i]) <= 0) top--;
        stk[top++] = p[i];
    }

    stk.resize(top - 1); // 去掉重复起点
    return stk;
}
int main()
{
    vector<Point> p = {
        {0, 0},
        {1, 1},
        {2, 0},
        {1, 2},
        {0, 2}
    };

    vector<Point> hull = convexHull(p);

    for (auto pt : hull)
        cout << pt.x << " " << pt.y << endl;

    return 0;
}