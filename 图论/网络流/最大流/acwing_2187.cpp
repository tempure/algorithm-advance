#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head

/*
用并查集判断起点终点是否连通，不连通则无解
边权: 太空船转移的边权就是最大容量，源点到day1的(0,0)也就是地球的边权为总人数
每个day的月球站到汇点T的边权为INF，也就是容量没限制

题目要求的就是最小的day的数量，可以二分，但没必要
直接从1开始暴力即可，因为数据量很小，而且day数和点数呈线性增长关系，二分建图很麻烦
当前day的图局面最大流>=K(总人数)时，即求出答案
*/

/*
点数最坏情况：m个太空船，k个人，每个太空船一次只能移动到下一个 那么每个人都要乘所有船
那么最大的排数Day就是m*k, 再乘上每排的太空站个数
边数最坏情况: 依据点数来算，源点汇点连的边，停留在某个空间站的边，太空船转移的边
*/

const int N = 1101 * 13 + 10, M = (N + 1100 + 13 * 1101) + 10;
const int INF = 0x3f3f3f3f;


int n, m, k, S, T;
int h[N], f[M], ne[M], e[M], idx;
int q[N], d[N], cur[N];

struct Ship {
    //每个船的容量，停靠数量，停靠的位置
    int h, r, id[30];
} ships[30];

int p[30]; //并查集

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int get(int i, int day) { //返回第i个空间站的第day天的点的编号
    return  day * (n + 2) + i;
}

//Dinic
void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx ++;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

bool bfs() {
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i]) {
                d[ver] = d[t] + 1; //层数
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}

int find(int u, int limit) { //当前u 从S到u最大的可增加流量是limit
    if (u == T) return limit;
    int flow = 0; //从当前点往后流的流量最多是多少
    for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) {
        cur[u] = i; //当前搜的弧
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i]) { //只搜下一层的点 防止环的干扰
            int t = find(ver, min(f[i], limit - flow));
            if (!t) d[ver] = -1; //当前边到终点没有增广路 就层数设为-1，之后不会再搜到了
            f[i] -= t, f[i ^ 1] += t, flow += t; //存在增广路 就更新残留网络
        }
    }
    return flow;
}

int dinic() {
    int r = 0, flow;
    while (bfs())  //bfs同时建立分层图 以及返回是否有增广路
        while (flow = find(S, INF)) r += flow; //所有能够增广的流量累加

    return r;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    S = N - 2, T = N - 1;
    memset(h, -1, sizeof h);

    //初始化并查集
    for (int i = 0; i < 30; i++) p[i] = i;
    for (int i = 0; i < m; i++) {
        //太空船
        int a, b;
        scanf("%d%d", &a, &b); //容量和停靠数量
        ships[i] = {a, b};
        for (int j = 0; j < b; j++) {
            int id;
            scanf("%d", &id);
            if (id == -1) id = n + 1; //月球记录为n + 1号太空站
            ships[i].id[j] = id;
            if (j) { //并查集合并船经过的太空站，将其加入并查集
                int x = ships[i].id[j - 1];
                p[find(x)] = find(id);
            }
        }
    }
    int res = 0;
    if (find(0) != find(n + 1)) puts("0");
    else {
        add(S, get(0, 0), k); //源点向地球的边
        add(get(n + 1, 0), T, INF); //第一排，day=0时候的月球向终点连边
        int day = 1;
        while (1) { //枚举天数
            add(get(n + 1, day), T, INF); //每一天的月球都向汇点连边
            for (int i = 0; i < n + 1; i++)
                add(get(i, day - 1), get(i, day), INF); //停留一天的边
            for (int i = 0; i < m;  i++) {
                int r = ships[i].r; //停靠的总数量
                int a = ships[i].id[(day - 1) % r]; //这个船在前一天停靠的位置
                int b = ships[i].id[day % r]; //当前day停靠的位置
                add(get(a, day - 1), get(b, day), ships[i].h);
            }
            res += dinic(); //每加一排，加一个day，求一次最大流
            if (res >= k) break;
            day ++;
        }
        cout << day << endl;
    }
    return 0;
}
