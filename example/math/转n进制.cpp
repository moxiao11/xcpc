#include <bits/stdc++.h>
using namespace std;

string convertBase(long long x, int base) {
    if (x == 0) return "0";

    string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string res = "";

    while (x > 0) {
        int r = x % base;
        res += chars[r];
        x /= base;
    }

    reverse(res.begin(), res.end());
    return res;
}

int main() {
    long long x;
    int n;
    cin >> x >> n;

    cout << convertBase(x, n) << endl;

    return 0;
}