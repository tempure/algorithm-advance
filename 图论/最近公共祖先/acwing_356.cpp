#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i = a; i< n; i++)
#define per(i,a,n) for(int i=n-1; i>=a; i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
//#define x first
//#define y second
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res=0;a%=mod;assert(b>=0);for(;b;b>>=1){if(b&1)res=(res+a)%mod;a=2*a%mod;}return res;}
ll powmod(ll a, ll b) {ll res=1;a%=mod;assert(b>=0);for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head


//倍增 LCA 优化寻找最大和次大边权的过程 暴力dfs改为倍增求最大次大
//其余步骤不变 先kruskal 然后枚举所有非树边
//d1[i][j] 表示从i开始向上跳2^j步 过程当中，路上的最小边权
//d2[i][j] 表示从i开始向上跳2^j步 路径上的次小边权

const int N = 100010, M = 300010;
const int INF = 0x3f3f3f3f;

int n, m;
int h[N], e[M], w[M], ne[M], idx;

struct Edge {
    int a, b, w;
    bool used; //是否是树边
    bool operator< (const Edge &t) {
        return w < t.w;
    }
} edge[M];

int p[N]; //kruskal的并查集
int depth[N], fa[N][17], d1[N][17], d2[N][17]; //最大边和次大边
int q[N]; //BFS求节点的树深度

void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

ll kruskal() {
    for (int i = 1; i <= n; i++) p[i] = i;
    sort(edge, edge + m);
    ll res = 0;

    for (int i = 0; i < m; i++) {
        int a = find(edge[i].a), b = find(edge[i].b), w = edge[i].w;
        if (a != b) {
            p[a] = b;
            res += w;
            edge[i].used = true;
        }
    }
    
    return res;
}

void build() {
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++)
        if (edge[i].used) {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            add(a, b, w); add(b, a, w);
        }
}

void bfs() { //预处理节点深度 以及每个点跳2^k后路径上的最大边和次大边
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1;
    int hh = 0, tt = 0;
    q[0] = 1;
    while (hh <= tt) {
        int t = q[hh ++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++tt] = j;
                fa[j][0] = t;
                d1[j][0] = w[i], d2[j][0] = -INF;
                for (int k = 1; k <= 16; k++) {
                    int anc =  fa[j][k - 1];
                    fa[j][k] = fa[anc][k - 1];
                    int distance[4] = {d1[j][k - 1], d2[j][k - 1], d1[anc][k - 1], d2[anc][k - 1]};
                    d1[j][k] = d2[j][k] = -INF;
                    for (int u = 0; u < 4; u++) {
                        int d = distance[u];
                        if (d > d1[j][k]) d2[j][k] = d1[j][k], d1[j][k] = d;
                        else if (d != d1[j][k] && d > d2[j][k]) d2[j][k] = d;
                    }
                }
            }
        }
    }
}

int lca(int a, int b, int w){
    static int distance[N * 2];  //缓存每一次跳的一段路上的最大和次大 最后取max 
    int cnt = 0;
    if(depth[a] < depth[b]) swap(a, b);

    for(int k = 16; k >= 0; k--)
        if(depth[fa[a][k]] >= depth[b]){
            distance[cnt++] = d1[a][k];
            distance[cnt++] = d2[a][k];
            a = fa[a][k];
        }
    if(a!=b){
        for(int k = 16; k >= 0; k--)
            if(fa[a][k] != fa[b][k]){
                distance[cnt++] = d1[a][k];
                distance[cnt++] = d2[a][k];
                distance[cnt++] = d1[b][k];
                distance[cnt++] = d2[b][k];
                a = fa[a][k],  b = fa[b][k];
            }
        distance[cnt++] = d1[a][0];
        distance[cnt++] = d1[b][0]; //最后加上到lca的一步
    }

    int dist1 = -INF, dist2 = -INF;  //最大值和次大值

    for(int i = 0; i < cnt; i++){
        int d = distance[i];
        if(d > dist1) dist2 = dist1, dist1 = d;
        else if(d != dist1 && d > dist2) dist2 = d;
    }

    if(w > dist1) return w - dist1;
    if(w > dist2) return w - dist2;

    return INF;

}


int main() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edge[i] = {a, b, c};
    }
    ll sum = kruskal(); //最小生成树的权值和
    build(); //建图
    bfs(); //预处理

    ll res = 1e18;
    //枚举非树边
    for (int i = 0; i < m; i++)
        if (!edge[i].used) {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            res = min(res, sum + lca(a, b, w)); //lca返回的是加上最大的边 然年减去原来的树边的值
        }

    printf("%lld\n", res);

    return 0;
}