#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int N=1e5 +10 ;
int n , m ;
int h[N] ,e[N] , ne[N] ,idx ,w[N]; 
int dist[N] ; 
bool st[N]; 
void add(int a, int b,int c)
{
    e[idx] = b ;  w[idx] = c ; ne[idx] = h[a] ; h[a] = idx ++ ;
}
typedef pair<int,int> PII; 
int dijkstra()
{
    memset(dist ,0x3f,sizeof dist) ;
    priority_queue<PII,vector<PII> , greater<PII>> heap ;
    heap.push({ 0,1 });
    dist[1] = 0 ; 
    while(heap.size())
    {
        auto t = heap.top() ; heap.pop() ; 
        int ver =t.second ; 
        if(st[ver]) continue ;
        st[ver] = true ;
        for(int i = h[ver] ; i!= -1 ; i = ne[i])
        {
            int j=e[i] ;
            if(dist[j] >dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i] ;
                heap.push({dist[j] , j});
            }
        }
    }
    if(dist[n] == 0x3f3f3f3f) return -1 ;
    return dist[n];
}
int main()
{
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 0; i <m ; i++)
    {
        int a, b , c ;scanf("%d%d%d",&a ,&b ,&c) ;
        add(a ,b , c);
    }
    int t = dijkstra(); cout << t<<endl; 
    return 0 ;
}
