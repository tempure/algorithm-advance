#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head

/*
最短路树，加边同时存每条边的编号，然后跑 dijkstra，最后dfs即可
最多保留K条边，那么最后图中最多只有K+1个点保留下来

定理:最短路树中包括源点在内的任何一个大小为k+1的连通块都符合答案
所以跑完dijkstra后直接dfs，如果一个点u的出边点j满足dist[j] == dist[u] = w[i], 那么j是满足最短路树的
但是最短路树不唯一，也就是说点j满足多个点u的最短路，即j会被多个点u更新，但是需要保留1条路径即可
只需要在dfs时标记每个满足最短路树的点是否已经被搜过即可

k可能会小于n-1，也就是说不能保留所有的最短路树的边
从源点开始dfs一个大小为k的连通块即可，不需要考虑边数的问题
*/

const int N = 1e5 + 10, M = 2 * N;

int n, m, k;
int h[N], e[M], ne[M], id[M], w[M], idx; //id 是边的编号
ll dist[N];
bool st[N];
vector<int> ans;

void add(int a, int b, int c, int i) {
    e[idx] = b, ne[idx] = h[a], id[idx] = i, w[idx] = c, h[a] = idx++;
}

void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> heap;
    heap.push({0, 1});

    while (heap.size()) {
        auto t =  heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;
        if (st[ver]) continue;
        st[ver] = true;
        for (int i = h[ver]; ~i ; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}

void dfs(int u) {
    st[u] = true;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!st[j] && dist[j] == dist[u] + w[i]) { //满足j没有被搜过
            if (sz(ans) < k) ans.push_back(id[i]);
            dfs(j);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> k;
    memset(h, -1, sizeof h);

    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c, i), add(b, a, c, i);
    }
    dijkstra();
    memset(st, 0, sizeof st); //复用
    dfs(1); //从源点开始dfs

    cout << sz(ans) << endl;
    for (auto x : ans) cout << x << ' ';

    return 0;
}