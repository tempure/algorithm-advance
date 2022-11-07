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

//最小费用最大流模板
//最大费用只需要改为最长路求解即可
//此模板费用 = 流量 * 路径长度 路径权值是单位费用

// 求最大费用的方法：将w[]数组元素取负，恢复原图流量，再求最短路，求出的就是负值的最长路
// 最后取反输出答案即可

const int N = 5010, M = 100010, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], f[M], w[M], ne[M], idx; //w[]是每条边的费用
int q[N], d[N], pre[N], incf[N]; //此处的d是最短路的距离 incf是从起点到当前点的路径中，最小的剩余流量大小
bool st[N];


void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

bool spfa() {
    int hh = 0, tt = 1;
    memset(d, 0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (f[i] && d[ver] > d[t] + w[i]) {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(f[i], incf[t]);
                if (!st[ver]) {
                    q[tt++] = ver;
                    if (tt == N) tt = 0;
                    st[ver] = true;
                }
            }
        }
    }
    return incf[T] > 0; //如果大于0说明S可以走到T 不然就不连通
}

//无返回值模板
void EK(int & flow, int & cost) {
    flow = cost = 0;
    while (spfa()) {
        int t = incf[T]; //当前找到的新的增广路的流量
        flow += t, cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
}

//返回费用模板
int EK2(int & flow, int & cost) {
    flow = cost = 0;
    while (spfa()) {
        int t = incf[T]; //当前找到的新的增广路的流量
        flow += t, cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    return cost; //返回最小费用
}

int main() {

    scanf("%d%d%d%d", &n, &m, &S, &T);
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b, c, d; //边的起点 终点 容量 费用
        scanf("%d%d%d%d", &a, &b, &c, &d);
        add(a, b, c, d);
    }
    int flow, cost; //最大流以及费用

    //最小费用
    EK(flow, cost);
    printf("%d %d\n", flow, cost);

    //最大流以及最大费用
    //取反w[] 以及恢复原图
    for (int i = 0; i < idx; i += 2) {
        f[i] += f[i ^ 1], f[i ^ 1] = 0;
        w[i] = -w[i], w[i ^ 1] = - w[i ^ 1];
    }
    //最大费用
    printf("%d\n", -EK2(flow, cost));

    return 0;
}