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

//EK最大流 复杂度O(n*m^2)

/*
对EK求最大流的理解:初始化残留图的边权就就是每条边的容量值
将整个求最大流的过程理解为灌水，开始网络中没有水，所以能灌的剩余量就是容量
然后每次找到一个能灌的值，这个值就是最小流量的水管的容量，灌水之后就更新剩余灌水量
*/

const int N = 1010, M = 20010, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], ne[M], idx;
int f[M]; //残留网络图的边权
int d[N]; //从起点到当前点的路径中，最小的剩余流量大小
int pre[N]; //前驱边 不是 前驱点
bool st[N];
int q[N]; //bfs队列

void add(int a, int b, int c) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++; //正向边
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++; //反向边
}

bool bfs() {
    int hh = 0, tt = 0;
    memset(st, false, sizeof st);
    q[0] = S, st[S] = true, d[S] = INF;

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (!st[ver] && f[i]) {
                st[ver] = true;
                d[ver] = min(f[i], d[t]);
                pre[ver] = i; //ver点的前驱边是i
                if (ver == T) return true;
                q[++tt] = ver;
            }
        }
    }
    return false; //没有增广路
}

int EK() {
    int r = 0;
    while (bfs()) {
        r += d[T]; //当前的最大流
        //从终点开始反向更新残留图，不断找前驱边，前驱点由前驱边推出
        for (int  i = T; i != S; i = e[pre[i] ^ 1]) //反向边对应的点就是e[pre[i] ^ 1]
            //残留图正向边减去最小路径的边权，反向边加上
            f[pre[i]] -= d[T], f[pre[i] ^ 1] += d[T];
    }
    return r;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &S, &T);
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); //维护残留网络的图 不连通边的流量就是0
    }
    cout << EK() << endl;

    return 0;
}