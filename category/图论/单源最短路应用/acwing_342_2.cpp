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

const int N = 25010, M = 150010, INF = 0x3f3f3f3f;
int h[N], ne[M], e[M], idx, w[M];
vector<int> block[N];
int bcnt, id[N]; //bcnt 连通块个数 id[x] x点所在的连通块编号
bool v[N];
int din[N]; //每个连通块的入度
int d[N]; //dijkstra 最短路距离
int mr, mp, s, n;
queue<int> q;

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void dfs(int u, int bid) {
    id[u] = bid;
    block[bid].push_back(u);
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!id[j]) dfs(j, bid);
    }
}

void dijkstra(int bid) {
    memset(v, 0, sizeof v);
    pq<pii, vector<pii>, greater<pii>> heap;

    /*
    模板题测了初始情况下将待求dij的所有点加入堆中是不会影响dij算法的正确性
    首先此题必须全部加入才知道哪些点是待求的

    正确性：将所有点入堆，不影响这些点dist[]的优先顺序，没被更新的依然dist是INF
    更新过的在本次dij开始会清空v数组，重新从dist最小的点开始bfs邻边然后更新
    bfs过程没有改变，所以算法依然正确
    */
    for (auto u : block[bid]) heap.push({d[u], u});

    while (heap.size()) {
        auto t = heap.top().second;
        heap.pop();
        if (v[t])continue;
        v[t] = 1;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (d[j] > d[t] + w[i]) {
                d[j] = d[t] + w[i];
                if (id[j] == id[t]) heap.push({d[j], j});
            }
            if (id[j] != id[t] && --din[id[j]] == 0) q.push(id[j]);
        }
    }
}

void topsort() {
    memset(d, 0x3f, sizeof d);
    d[s] = 0;
    for (int i = 1; i <= bcnt; i++)
        if (!din[i]) q.push(i);

    while (q.size()) {
        int t = q.front();
        q.pop();
        dijkstra(t);
    }

}

void solve() {
    cin >> n >> mr >> mp >> s;
    memset(h, -1, sizeof h);
    while (mr --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c); add(b, a, c);
    }

    for (int i = 1; i <= n; i++) {
        if (!id[i]) dfs(i, ++bcnt);
    }

    while (mp --) {
        int a, b, c;
        cin >> a >> b  >> c;
        add(a, b, c);
        din[id[b]]++;
    }

    topsort();

    for (int i = 1; i <= n; i++) {
        if (d[i] > INF / 2) cout << "NO PATH" << '\n';
        else cout << d[i] << '\n';
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
