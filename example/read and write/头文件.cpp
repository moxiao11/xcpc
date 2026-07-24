#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <set>

#define endl '\n' 
#define all(x) (x).begin() , (x).end() 
#define pb push_back
#define x first 
#define y second 
#define debug(x) cerr << #x << " = " << x << endl

using namespace std; 


template<class T>
istream& operator>>(istream& in, vector<T>& a) {
    for(auto &x : a) in >> x;
    return in;
}

template<class T>
ostream& operator<<(ostream& out, const vector<T>& a) {
    for(int i = 0; i < (int)a.size(); i++) {
        if(i) out << ' ';
        out << a[i];
    }
    return out;
}

const int N = 1e6 + 10 ;
const int MOD = 1e9 + 7;

using ll = long long ;
using ull = unsigned long long;
using pii = pair<int, int>;
inline void write(int x ); 



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0 ; 
}

inline void write(int x)
{
    if(x<0) {
        putchar('-');
        x = -x;
    }
    if(x>9) write(x / 10);
    putchar(x % 10 + '0');
}

