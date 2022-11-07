#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//多起点 唯一终点 问题
//建立虚拟原点 与每个原点 连一条权值为0的边
//这样就不用每个起点都跑一次最短路了 只需要全图一次最短路即可

const int N = 1010, M = 21010, INF = 0x3f3f3f3f;
//注意M边数的范围，多加了虚拟原点到所有起点的边
int n,m, T;
int h[N], ne[M], e[M], idx, w[M];
int dist[N];
int q[N];
bool st[N];

void add(int a,int b, int c){
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

int spfa(){
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[0] = 0; //0号是虚拟原点
    int hh = 0, tt = 1;
    q[0] = 0;
    st[0] = 1;
    
    while(hh!= tt){
        int t = q[hh++];
        if(hh == N) hh = 0;
        st[t] = false;
        for(int i = h[t]; ~i; i = ne[i]){
            int j = e[i];
            if(dist[j] > dist[t] + w[i]){
                dist[j] = dist[t] + w[i];
                if(!st[j]){
                    q[tt++] = j;
                    if(tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    } 
    if(dist[T] == INF) return -1;
    return dist[T];
}

int main(){
    while(scanf("%d%d%d", &n,&m, &T) != -1){
        memset(h, -1, sizeof h);
        idx = 0;
        while(m--){
            int a, b,c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c);
        }
        int s;
        scanf("%d", &s);
        while(s --){
            int ver;
            scanf("%d", &ver);
            add(0, ver, 0); //添加虚拟原点 并且连接权值为0的边
        }
        
        printf("%d\n", spfa());
    }    
    
    return 0;
}