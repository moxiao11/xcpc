#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long 
const int N = 5050 ;
int f[N][N];  
int a[N]; 
vector<int> s ; 
signed  main()
{
    int n , m , k ; cin >> n >> m >> k ;
    for(int i =1 ; i <= n ; i ++ )  cin >> a[i]; 
    for(int i = 1; i <=n - m + 1  ; i ++ )  
    {
        int sum = 0 ; 
        for(int j = 0 ; j < m ; j ++ ) 
        {
            sum += a[i + j ] ; 
        }
        s.push_back(sum) ; 
    }
    sort(s.begin() , s.end() , [](int a, int b) 
    {
        return a > b ; 
    }) ;
    int ans =0  ;
    for(int i = 0 ; i < k ; i ++ ) 
    {
        ans += s[i];         
    }
    cout << ans << endl; 
    return 0 ; 
}