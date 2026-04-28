#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<cassert>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<deque>
#include<iomanip>
#include<list>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<vector>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> PII ; 
#define x first
#define y second

const double PI=acos(-1.0);
const double eps=1e-6;
const ll mod=1e9+7;
const int inf=0x3f3f3f3f;
const int maxn=1e5+10;
const int maxm=100+10;

inline void write(int x);
inline int read();

int main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);


    return 0 ;
}


inline int read() {
    int num=0, w=0;
    char ch=0;
    while (!isdigit(ch)) {
        w|=ch=='-';
        ch = getchar();
    }
    while (isdigit(ch)) {
        num = (num<<3) + (num<<1) + (ch^48);
        ch = getchar();
    }
    return w? -num: num;
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