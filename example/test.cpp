#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>
#include <cmath>
#include <queue>

#define endl '\n' 
#define all(x) (x).begin() , (x).end() 
#define pb push_back
#define x first 
#define y second 
#define debug(x) cerr << #x << " = " << x << endl

using namespace std; 

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

