#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

//定理: 一定存在一个次小生成树，和最小生成树只有一条边不同
//此定理同时适用于 严格以及非严格的次小生成树
//次小生成树：当最小生成树不唯一 次小可以等于最小
//严格次小生成树：最小生成树即使不唯一 但是次小必须权值大于最小

/*
先求最小生成树 然后在非树边中加入一条边 形成环 然后在环上去掉一个树边
那么次小生成树 必定在所有这样的方案中 所有方案取MIN即可
对于新边连接的2个点 环上的树边就是这两点的路径 然后在这个路径中去掉权值最大的树边
这是贪心的思路 因为最小的肯定是最小生成树，那么次小的 也要尽量小 所以去掉的是环上的权值最大的树边
如果和最大的边权相同，那么就还要预处理一遍次大值
问题转化为 求树上2点路径边的最值和次大值 可以动态树 或者树链剖分 还有LCA倍增 
此题可以直接暴力 做一次dfs 预处理所有点对路径的边权最值和次大值 复杂度O(N ^ 2)
*/

typedef long long ll;

const int N = 510, M = 10010;
int n, m;

struct Edge{
    int a, b, w;
    bool f; //是否是树边
    bool operator< (const Edge & t){
        return w < t.w;
    }
}edge[M];

int p[N];
int dist[N][N];  //路径最大值
int dist2[N][N]; //路径次大值
int h[N], e[N * 2], w[N * 2], ne[N * 2], idx;

void add(int a, int b, int c){
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

int find(int x){
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}

//当前点 当前点父节点 当前最大边权 当前次大边权 存储最大和次大边权的数组
void dfs(int u, int fa, int max1, int max2, int d[], int d2[]){
    d[u] = max1;
    d2[u] = max2; // 次大值
    for(int i = h[u]; ~i; i = ne[i]){
        int j = e[i];
        if(j != fa){ //没有往回搜 因为是树路径 直接从根搜到叶节点即可
            int t1 = max1, t2 = max2;
            if(w[i] > t1) t2 = t1, t1 = w[i]; //比最大值大 那么最大就给次大
            else if(w[i] < t1 && w[i] > t2) t2 = w[i];
            dfs(j, u, t1, t2, d, d2);
        }
    }
}

int main(){
    scanf("%d%d", &n, &m);  
    memset(h, -1, sizeof h);

    for(int i = 0; i < m; i++){
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edge[i] = {a, b, w};
    }
    
    sort(edge, edge + m);
    
    for(int i = 1; i <= n; i++) p[i] = i;

    ll sum = 0;
    for(int i = 0; i < m; i++ ){
        int a = edge[i].a, b = edge[i].b, w = edge[i].w;
        int pa = find(a), pb = find(b);
        if(pa != pb){
            p[pa] = pb;
            sum += w;
            add(a, b, w); add(b, a , w);
            edge[i].f = true;  //加入最小生成树
        }
    }

    //每两个点路径的边权最大值和次大值
    for(int i = 1; i <= n; i++) dfs(i, -1, 0, 0, dist[i], dist2[i]);

    ll res = 1e18;
    
    //枚举非树边
    for(int i = 0; i < m; i++)
        if(!edge[i].f){
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            if(w > dist[a][b])
                res = min(res, sum + w - dist[a][b]);
            else 
                res = min(res, sum + w - dist2[a][b]);
        }

    printf("%lld\n", res);

    return 0;
}