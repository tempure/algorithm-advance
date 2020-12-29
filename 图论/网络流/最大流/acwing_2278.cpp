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
最大流拆点：
每个虚拟源点向所有点连边，边权为该点企鹅的初始数量
接着枚举每个点为汇点，如果2个点之间能跳到，则双向连边
拆点: 每个点的入点流量是该点企鹅的初始数量，要拆点的原因是：如果一个点有n个企鹅，但是起跳数量
小于n，要控制起跳的数量，所以只能有起跳数量个企鹅流过该点, 所以出入点的边权就是每个点的起跳数量限制
*/

#define x first
#define y second

const int N = 210, M = 21000;
const int INF = 0x3f3f3f3f;
const double eps = 1e-8; //浮点数比较误差

int n, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];
double D; //距离

pii p[N]; //点的编号

bool check(pii a, pii b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy < D * D + eps;
}

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
    int cases;
    scanf("%d", &cases);
    while (cases --) {
        memset(h, -1, sizeof h);
        idx = 0;
        scanf("%d%lf", &n, &D);
        S = 0;

        int tot = 0;  //总的企鹅数量
        for (int i = 1; i <= n; i++) {
            int x, y, a, b;
            scanf("%d%d%d%d", &x, &y, &a, &b);
            p[i] = {x, y};
            add(S, i, a);//向每个有企鹅的点连边 边权就是企鹅的数量
            add(i, i + n, b); //出点 n + 1 ~ 2n 出入点的边权是起跳数量
            tot += a;
        }

        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                if (check(p[i], p[j])) { //两个点能跳到就连边INF, 这个边权没有限制
                    add(n + i, j, INF);
                    add(n + j, i, INF);
                }

        int cnt = 0; //枚举所有点做为汇点
        for (int i = 1; i <= n; i++) {
            T = i; //当前点作为汇点
            //每次枚举新的汇点都要还原图
            for (int j = 0; j < idx; j += 2) {
                f[j] += f[j ^ 1]; //残留网络正向边加上反向边的流量就还原了 本质上一直在维护的是残留网络
                f[j ^ 1] = 0; //反向边清空
            }

            if (dinic() == tot) {
                printf("%d ", i - 1); //题目点从0开始，但是代码0设为虚拟源点，点从1开始 要减去1
                cnt ++;  //记录可以汇聚的点的数量
            }
        }
        if (cnt == 0) puts("-1");
        else puts("");
    }

    return 0;
}
