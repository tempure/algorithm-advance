#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
/*
最小生成树的问题中 一般都是无向边 有向边要用 朱刘算法 
题意暗示已经是一个连通图了 而且修改之后不能破坏连通性
本题有区别：要求最小生成树的最大的边权最小 
二分最大边权 如果满足 则缩小右端点 ? 显然没有必要
因为kruskal算法默认从小到大枚举边 保持最优
最后最大的边 就是最后加进去的边 
*/


const int N = 310, M = 8010;
int p[N];
int n, m;
int cnt;

struct Edge{
    int a, b ,w;
    bool operator< (const Edge & t){
        return w < t.w;
    }
}e[M];

int find(int x){
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}

int main(){

    cin >> n >> m;
    for(int i =1 ;i <= n; i++) p[i] = i;
    
    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        e[i] = {a, b, c};
    }
    sort(e, e + m);
    int max_val = 0;
    for(int i = 0; i < m; i++){
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if(a != b){
            p[a] =b;
            cnt ++;
            max_val = w;
        }
    }
    
    cout << cnt << ' ' << max_val << endl;
    
    return 0;
}