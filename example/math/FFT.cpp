#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);
using cd = complex<double>;

void fft(vector<cd>& a, int invert)
{
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        while (j & bit)
        {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wn(cos(ang), sin(ang));

        for (int i = 0; i < n; i += len)
        {
            cd w(1);
            for (int j = 0; j < len / 2; j++)
            {
                cd u = a[i + j];
                cd v = w * a[i + j + len / 2];
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wn;
            }
        }
    }

    if (invert)
    {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

vector<long long> multiply(vector<int>& A, vector<int>& B)
{
    vector<cd> fa(A.begin(), A.end()), fb(B.begin(), B.end());

    int n = 1;
    while (n < (int)A.size() + (int)B.size()) n <<= 1;

    fa.resize(n);
    fb.resize(n);

    fft(fa, 0);
    fft(fb, 0);

    for (int i = 0; i < n; i++) fa[i] *= fb[i];

    fft(fa, 1);

    vector<long long> res(n);
    for (int i = 0; i < n; i++)
        res[i] = (long long)(fa[i].real() + 0.5);

    return res;
}

int main()
{
    int n, m;
    cin >> n >> m;   // A 的次数, B 的次数

    vector<int> A(n + 1), B(m + 1);
    for (int i = 0; i <= n; i++) cin >> A[i];
    for (int i = 0; i <= m; i++) cin >> B[i];

    vector<long long> C = multiply(A, B);

    for (int i = 0; i <= n + m; i++)
        cout << C[i] << " ";
    cout << endl;

    return 0;
}