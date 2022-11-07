#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

//每个点可以经过多次 求遍历所有点 需要的最短路径
//先预处理从1.2....5出发到其他点的单源最短路径 也就是6次 
//然后dfs 5的阶乘次数 暴搜所有拜访顺序 每个点求出与下一个点的最短距离 可以直接查表

typedef pair<int, int> pii;
const int N = 50010, M = 200010;
const int INF = 0x3f3f3f3f;
int n, m;
int source[6];
int h[N], e[M], w[M], ne[M], idx;
int q[N], dist[6][N];
bool st[N];

void add(int a, int b, int c){
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
//spfa会被卡掉
// void spfa(int start, int dist[]){
//     memset(dist, 0x3f, N * 4);
//     // memset(st, 0, sizeof st);
//     dist[start] = 0;
//     int hh = 0, tt = 1;
//     q[0] = start;
    
//     while(hh != tt){
//         int t = q[hh++];
//         if(hh == N) hh = 0;
//         st[t] = false;
//         for(int i = h[t]; ~i; i = ne[i]){
//             int j = e[i];
//             if(dist[j] > dist[t] + w[i]){
//                 dist[j] = dist[t] + w[i];
//                 if(!st[j]){
//                     q[tt++] = j;
//                     if(tt == N) tt = 0;
//                     st[j] = true;
//                 }
//             }
//         }
//     }
// }

//堆优化dijkstra
void dijkstra(int start, int dist[]){
    memset(dist, 0x3f, N * 4);
    dist[start] = 0;
    memset(st, 0, sizeof st);
    
    priority_queue<pii, vector<pii>, greater<pii> > heap;
    heap.push({0, start});
    
    while(heap.size()){
        auto t = heap.top();
        heap.pop();
        
        int ver = t.second;
        if(st[ver]) continue;
        st[ver] = true;
        
        for(int i = h[ver]; ~i; i = ne[i]){
            int j = e[i];
            if(dist[j] > dist[ver] + w[i]){
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}



int dfs(int u, int start, int distance){ //当前拜访第u个亲戚，start是起点，当前的距离是distance
    if(u == 6) return distance;
    int res = INF;
    
    for(int i= 1;i <= 5; i++)
        if(!st[i]){
            int next = source[i]; //准备要拜访的亲戚
            st[i] = true;
            res = min(res, dfs(u + 1, i, distance + dist[start][next]));
            st[i] = false;
        }
        
    return res;
        
}

int main(){
    scanf("%d%d", &n, &m);
    source[0] = 1;
    for(int i =1 ; i <= 5; i++) scanf("%d", &source[i]);
    memset(h, -1, sizeof h);
    while(m --){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); add(b, a, c);
    }
    
    for(int i = 0; i < 6; i++) dijkstra(source[i], dist[i]);
    
    memset(st, 0, sizeof st); //注意在dfs之前 要清空一下st
    
    printf("%d\n", dfs(1, 0, 0));
    
    return 0;
}