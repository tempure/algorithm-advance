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
反向BFS，建反向，有向图，判断是否当前点属于最短路只需要判断三角不等式即可
对于最短路中的边a->b，跑完最短路后显然有dist[b] <= dist[a] + w[i]，
当dist[b] < dist[a] + w[i]时候，也就是说只有小于号的关系，那么a->b就不是最短路路径的边。
当等于号成立，即dist[b] ==dist[a] + w[i],才说明a->b是最短路里面的边, 跑完后必然满足<=,但是只有==才是最短路的边。
建反向图BFS目的是求每个点到终点的最短路距离
cnt[]记录反向BFS的过程中每个点的出边的点，属于最短路的有几个出点

为啥跑反向不是正向。。。说是为了快速判断正向图中每个点的出边有多少种最短路走法？
*/

int n, m;
const int N = 2e5 + 10;
int h[N], e[N], ne[N], idx;
int dist[N], cnt[N], q[N];
int path[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void bfs(int start) {
    int hh = 0, tt = 0;
    memset(dist, 0x3f, sizeof dist);
    dist[start] = 0;
    q[0] = start;

    while (hh <= tt) {
        auto t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + 1) {
                dist[j] = dist[t] + 1;
                cnt[j] = 1;
                q[++tt] = j;
            }
            else if (dist[j] == dist[t] + 1) cnt[j] ++;
        }
    }
}

void solve() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b;
        cin >> a >> b;
        add(b, a); //反向建图
    }
    int k;
    cin >> k;

    for (int i = 1; i <= k; i++) cin >> path[i];
    bfs(path[k]); //从终点反向bfs

    int minc = 0, maxc = 0;
    for (int i = 1; i < k; i++) {
        int a = path[i], b = path[i + 1];
        if (dist[a] != dist[b] + 1) minc++, maxc++;//也可以判断dist[a] < dist[b] + 1就不是最短路的边
        else if (cnt[a] > 1) maxc++;
    }
    cout << minc << ' ' << maxc << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}