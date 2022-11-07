#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

//建立虚拟原点 所有发电站都和原点连边，边权都是点上的权
//这样就只有边权了，问题转化为求n + 1个点的连通图的最小生成树
//稠密图 用prim算法 当然kruskal也能写 此题图默认是连通图

const int N = 310;

int n;
int w[N][N];
bool st[N];
int dist[N];

int prim(){
    memset(dist, 0x3f, sizeof dist);
    memset(st,0, sizeof st);
    dist[0] = 0;

    int res = 0;
    for(int i = 0; i < n + 1; i++){ //循环次数是点数 不是边数
        int t = -1;
        for(int j = 0; j <= n; j++) //加上虚拟原点一共n + 1 个点
            if(!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;
                
        st[t] = true;
        res += dist[t];

        for(int j = 0; j <= n; j++) 
            if(!st[j]) dist[j] = min(dist[j], w[t][j]);
    }
    return res;
}

int main(){
    memset(w, 0x3f, sizeof w);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &w[0][i]);
        w[i][0] = w[0][i];  //和虚拟原点连边
    }

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%d", &w[i][j]);
            
    printf("%d\n", prim());

    return 0;
}