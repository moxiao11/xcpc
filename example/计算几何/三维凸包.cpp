#include <bits/stdc++.h>
using namespace std;

struct ConvexHull3D {
    static constexpr int MAXN = 2010;
    static constexpr double EPS = 1e-9;

    struct Point {
        double x, y, z;

        Point() {}
        Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

        Point operator-(const Point& other) const {
            return Point(x - other.x, y - other.y, z - other.z);
        }

        Point operator*(const Point& other) const { // 叉乘
            return Point(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            );
        }

        double operator&(const Point& other) const { // 点乘
            return x * other.x + y * other.y + z * other.z;
        }

        double len() const {
            return sqrt(x * x + y * y + z * z);
        }

        static double Rand() {
            return rand() / (double)RAND_MAX;
        }

        static double reps() {
            return (Rand() - 0.5) * EPS;
        }

        void shake() {
            x += reps();
            y += reps();
            z += reps();
        }
    };

    struct Face {
        int v[3];

        Face() {}
        Face(int a, int b, int c) {
            v[0] = a;
            v[1] = b;
            v[2] = c;
        }
    };

    int n;                       // 点数
    int cnt;                     // 当前三角面数
    int vis[MAXN][MAXN];         // 有向边是否是“可见面”的边
    Point p[MAXN];
    Face f[MAXN * 8], tmp[MAXN * 8];

    ConvexHull3D() {
        n = cnt = 0;
        memset(vis, 0, sizeof(vis));
    }

    Point normal(const Face& face) const {
        return (p[face.v[1]] - p[face.v[0]]) * (p[face.v[2]] - p[face.v[0]]);
    }

    double area(const Face& face) const {
        return normal(face).len() / 2.0;
    }

    bool see(const Face& face, const Point& q) const {
        return ((q - p[face.v[0]]) & normal(face)) > 0;
    }

    // pts 下标从 1 开始传入更方便
    void build(int _n, Point pts[]) {
        n = _n;
        cnt = 0;
        memset(vis, 0, sizeof(vis));

        for (int i = 1; i <= n; i++) {
            p[i] = pts[i];
            p[i].shake(); // 防止共面/共线/共点退化
        }

        if (n < 4) return; // 点太少无法形成三维凸包

        f[++cnt] = Face(1, 2, 3);
        f[++cnt] = Face(3, 2, 1);

        for (int i = 4; i <= n; i++) {
            int cc = 0;

            for (int j = 1; j <= cnt; j++) {
                bool visible = see(f[j], p[i]);
                if (!visible) tmp[++cc] = f[j];

                for (int k = 0; k < 3; k++) {
                    int x = f[j].v[k];
                    int y = f[j].v[(k + 1) % 3];
                    vis[x][y] = visible;
                }
            }

            for (int j = 1; j <= cnt; j++) {
                for (int k = 0; k < 3; k++) {
                    int x = f[j].v[k];
                    int y = f[j].v[(k + 1) % 3];
                    if (vis[x][y] && !vis[y][x]) {
                        tmp[++cc] = Face(x, y, i);
                    }
                }
            }

            for (int j = 1; j <= cc; j++) f[j] = tmp[j];
            cnt = cc;
        }
    }

    int triangle_face_count() const {
        return cnt;
    }

    double surface_area() const {
        double ans = 0;
        for (int i = 1; i <= cnt; i++) ans += area(f[i]);
        return ans;
    }
};

int main() {
    int n;
    cin >> n;

    ConvexHull3D hull;
    static ConvexHull3D::Point pts[2010];

    for (int i = 1; i <= n; i++) {
        cin >> pts[i].x >> pts[i].y >> pts[i].z;
    }

    hull.build(n, pts);

    cout << hull.triangle_face_count() << '\n';
    cout << fixed << setprecision(3) << hull.surface_area() << '\n';

    return 0;
}