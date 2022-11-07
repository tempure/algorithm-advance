#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10, M = 2 * N, INF = 0x3f3f3f3f;
int n, m;
int h[N], e[M], ne[M], w[M], idx;

struct Edge {
    int a, b, w;
    bool used;
    bool operator< (const Edge & t) {
        return w < t.w;
    }
} edge[300010]; //所有边 数据范围是题目 单向边

int p[N]; //DSU kruskal
int q[N]; //BFS queue
int depth[N], fa[N][17], d1[N][17], d2[N][17]; //d1 最大边权 d2 次大

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
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
    depth[0] = 0, depth[2] = 1;
    int hh = 0, tt = 0;
    q[0] = 2;
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
                    //注意每次更新一段 都是用2小段来更新，先预处理2次都跳2^(k-1)步 然后遍历 一次求出
                    //2个小段更新一个大段 因为k是从小到大枚举的
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

int lca(int a, int b, int w) {
    static int distance[N * 2];  //缓存每一次跳的一段路上的最大和次大 最后取max
    int cnt = 0;
    if (depth[a] < depth[b]) swap(a, b);

    for (int k = 16; k >= 0; k--)
        if (depth[fa[a][k]] >= depth[b]) {
            distance[cnt++] = d1[a][k];
            distance[cnt++] = d2[a][k];
            a = fa[a][k];
        }
    if (a != b) {
        for (int k = 16; k >= 0; k--)
            if (fa[a][k] != fa[b][k]) { //将
                distance[cnt++] = d1[a][k];
                distance[cnt++] = d2[a][k];
                distance[cnt++] = d1[b][k];
                distance[cnt++] = d2[b][k];
                a = fa[a][k], b = fa[b][k];
            }
        distance[cnt++] = d1[a][0];
        distance[cnt++] = d1[b][0]; //最后加上到lca的一步
    }

    int dist1 = -INF, dist2 = -INF;  //最大值和次大值

    for (int i = 0; i < cnt; i++) {
        int d = distance[i];
        if (d > dist1) dist2 = dist1, dist1 = d;
        else if (d != dist1 && d > dist2) dist2 = d;
    }

    if (w > dist1) return w - dist1;
    if (w > dist2) return w - dist2;

    // return INF;
}


void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edge[i] = {a, b, c};
    }
    ll sum = kruskal();
    build();
    bfs();

    ll res = 1e18;
    for (int i = 0; i < m; i++)
        if (!edge[i].used) {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            res = min(res, sum + lca(a, b, w));
        }
    cout << res << endl;
}

signed main() {
    solve();
    return 0;
}