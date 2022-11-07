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

const int N = 6010;
int n;

//边权从小到大排序  然后kruskal 合并集合
//每次合并2个连通块时候 需要连接2个连通块内部所有的边 原来的树肯定至少有一条边已经连通这2个块
//假设原来树连通这2 块的最小边权是 w 那么新加的边权就是w + 1
//由于计算连通块内的点数 需要维护并查集的SIZE

struct Edge {
    int a, b, w;
    bool operator<(const Edge & t) {
        return w < t.w;
    }
} e[N];

int p[N], sz[N];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void solve() {
    cin >> n;
    memset(p, 0, sizeof p);
    memset(sz, 0, sizeof sz);
    memset(e, 0, sizeof e);
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        e[i] = {a, b, w};
    }
    sort(e, e + n - 1); //n-1条边
    for (int i = 0; i < n; i++) p[i] = i, sz[i] = 1;
    ll res = 0;
    for (int i = 0; i < n; i++) {
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if (a != b) {
            res += (sz[a] * sz[b] - 1) * (w + 1);
            sz[b] += sz[a];
            p[a] = b;
        }
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}