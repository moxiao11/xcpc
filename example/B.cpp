#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef long long  ll ; 
inline void write(__int128_t x)
{
    if(x<0) {
        putchar('-');
        x = -x;
    }
    if(x>9) write(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
    int t ; cin >> t; 
    while(t -- ) 
    {
        int n ; cin >> n ;
        priority_queue<ll>  q ;
        for(int i = 0 ; i < n ;i ++ ) 
        {
            ll a; cin >> a ;
            q.push(a) ; 
        }    
        __int128_t sum = 0 ;
        for(int i = 0 ; i < n - 1; i ++ ) 
        {
            __int128_t a = q.top() ; q.pop() ; 
            __int128_t b = q.top() ; q.pop() ; 
            __int128_t t = a + b ; 
            q.push(t) ; 
            sum += max(a, b) ;       
        }
        write(sum)  ;
        printf("\n") ; 
    }
    return 0 ; 
}