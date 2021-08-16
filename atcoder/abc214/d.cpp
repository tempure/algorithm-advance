#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
// #define sz(x) ((int)(x).sz())
#define x first
#define y second
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

const int N = 1e5 + 10;
int p[N], sz[N];

struct Edge {
    int x, y, v;
    bool operator<(const Edge & t) {
        return v < t.v;
    }
} e[N];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

ll merge(int x, int y) {
    int a = find(x), b = find(y);
    ll cnt = 1ll * sz[a] * sz[b];
    sz[a]  += sz[b];
    p[b] = a;
    return cnt;
}

void solve() {
    int n;
    vector<Edge> save;
    cin >> n;
    for (int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;
    for (int i = 0; i < n - 1; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        save.push_back({x, y, w});
    }
    sort(all(save));
    ll  res = 0;
    for (auto it : save) res += 1ll * it.v * merge(it.x, it.y);
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --)solve();
    return 0;
}