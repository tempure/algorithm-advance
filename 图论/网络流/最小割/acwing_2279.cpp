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
01分数规划 浮点数最大流 二分
考虑分数规划。存在一个平均值不大于xx的割集等价于：
∃C,∑e∈C w(e) / |C| <= x
⇒∃C,∑e∈C (w(e)−x) <= 0
故存在一个平均值不大于x的割集⇔将边权全部减少x后，最小割权值不超过0
二分答案+最小割即可
注意图中会出现负权边，没法直接最大流，但最小割中必然包含所有负权边，提前选上即可。
所有负权边先加上，然后剩下的就是正边，然后求最小割即可
*/


const int N = 100, M = 810, INF = 0x3f3f3f3f;
const double eps = 1e-8; //二分eps

int n, m, S, T;
int h[N], e[M], ne[M], w[M], idx;
double f[M];  //二分浮点数 λ  边的流量是小数
int q[N], d[N], cur[N];

void add(int a, int b, int c) {
    // 建双向边
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = c; ne[idx] = h[b], h[b] = idx ++;
}

bool bfs() {
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);

    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (d[ver] == -1 && f[i] > 0) {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false;
}

double find(int u, double limit) {
    if (u == T) return limit;
    double flow = 0;
    for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i] > 0) {
            double t = find(ver, min(f[i], limit -  flow));
            if (t < eps) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

double dinic(double mid) { //mid就是λ 在dinic里面建图
    double res = 0;
    for (int i = 0; i < idx; i += 2)
        if (w[i] <= mid) { //此时的边权为负数 直接加上 然后删掉这条边
            res += w[i] - mid;
            f[i] = f[i ^ 1] = 0; //删掉负权边
        } else f[i] = f[i ^ 1] = w[i] - mid;

    double r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return res + r;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &S, &T);
    memset(h, -1, sizeof h);

    while (m --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b , &c);
        add(a, b, c);
    }

    double l = 0, r = 1e7;  //二分答案 mid
    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (dinic(mid) < 0) r = mid;
        else l = mid;
    }

    printf("%.2lf\n", r);

    return 0;
}