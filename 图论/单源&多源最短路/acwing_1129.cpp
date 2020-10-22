/*
* @Description: 1129. 热浪
* @Author: Xiaobin Ren
* @Date:   2020-10-22 19:43:51
* @Last Modified time: 2020-10-22 19:44:05
*/
// #pragma GCC optimize(3)
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

//裸单源最短路 可以spfa 可以dijkstra

const int M = 6200 * 2 + 10;
const int N = 2510;

int n, m, S, T;
int h[N], e[M], ne[M], w[M], idx;
int d[N], q[N];
bool st[N];

void add(int a, int b, int c){
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx ++;
}

// void spfa(){
//     memset(dist, 0x3f, sizeof dist);
//     dist[S] = 0;
    
//     int hh = 0, tt = 1;
//     q[0] = S, st[S] = 1;
    
//     while(hh != tt){
//         int t =q[hh++];
//         if(hh == N) hh = 0;  //循环队列
//         st[t] = false;
        
//         for(int i = h[t]; ~i; i = ne[i]){
//             int j = e[i];
//             if(dist[j] > dist[t] + w[i]){
//                 dist[j] = dist[t] + w[i];
//                 if(!st[j]){
//                     q[tt ++] = j;
//                     if(tt == N) tt = 0;  //循环队列
//                     st[j] = 1;
//                 }
//             }
//         }
//     }
// }


//stl的queue 比手写的循环队列更快
void spfa(){
    queue<int> q;
    q.push(S);
    d[S] = 0;
    st[S] = 1;
    
    while(q.size()){
        int x = q.front(); q.pop();
        st[x] = 0;
        
        for(int i = h[x]; ~i; i = ne[i]){
            int y = e[i]; int u = w[i];
            if(d[x] + u < d[y]){
                d[y] = d[x] + u;
                if(!st[y]) q.push(y), st[y] = 1;
            }
        }
    }
    
}
int main(){
    
    cin >> n >> m >> S >> T;
    memset(h, -1, sizeof h);
    memset(d, 0x3f, sizeof d);
    for(int i = 0; i < m; i++){
        int a,b , c;
        cin >> a >> b >> c;
        add(a, b, c); add(b, a, c);
    }
    
    spfa();
    
    cout << d[T] << endl;
    
    return 0;
}
