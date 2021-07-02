#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
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
第一次写的注释是错的，这题只求最短路，和最长路没关系
约束条件：xi <= x[i+1] + 0, xb <= xa + l, xa <= xb - d

一个盲点：不存在一个点能到其他所有点，但是i+1都向i连边了，n号点可以到所有点，但是从n开始跑spfa是WA。。不知道为什么
只能暴力所有点入队列来强制连通来判负环了

由于固定1号点，而且1号作为源点开始spfa，就是相当于初始只1号点入队，这样就可以判断n号是否可达，如果n号和1号根本没有连通，也就是n号和1号并没有什么
联系，没有被约束，也对应n号不能被spfa更新到，所以距离还是INF

小细节：最短路算法判断是否连通，只有bellman-ford和floyd需要判断是否>INF/2这种，因为即使不连通的点也会被更新到
*/
const int N = 1010, M = 21010, INF = 0x3f3f3f3f;
int q[N], h[N], e[M], ne[M], dix, w[M], cnt[N];
bool st[N];
int dist[N];
int n, m1, m2, idx;

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

bool spfa(int sz) {
    memset(cnt, 0, sizeof cnt);
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);

    int hh = 0, tt = 1;
    for (int i = 1; i <= sz; i++) {
        dist[i] = 0; //注意初始化距离为0
        q[tt++] = i;
        st[i] = true;
    }

    while (hh != tt) {
        int t = q[--tt];
        st[t] = false;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n) return true; //存在负环
                if (!st[j]) {
                    q[tt++]  = j;
                    st[j] = true;
                }
            }
        }
    }
    return false;
}

void solve() {
    cin >> n >> m1 >> m2;
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; i++) add(i + 1, i, 0); // x[i]<=x[i+1] +0
    while (m1 --) {
        int a, b, c;
        cin >> a >> b >> c;
        if (b < a) swap(a, b);
        add(a, b, c); //x[b] <= x[a] + c
    }
    while (m2 --) {
        int a, b, c;
        cin >> a >> b >> c;
        if (b < a) swap(a, b);
        add(b, a, -c); //x[a] <= x[b] - c
    }
    if (spfa(n)) cout << -1 << endl; //全图强制连通做一次 有负环 无解
    else {
        spfa(1); //从1号点开始，不强制连通 求一次最短路
        if (dist[n] == INF) cout << -2 << endl; //1 号点和n号点没连通 n号点不受限制
        else cout << dist[n] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}