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

int n, m;
const int N = 30, M = N * N;
int h[N], e[M], ne[M], idx;
bool v[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) { //必要时写个 dfs检测0能不能走到所有点 来决定是否初始所有点入队
    v[u] = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (v[j]) continue;
        dfs(j);
    }
}

void solve() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    while (m --) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!v[i]) {
            dfs(i);
            cnt++;
        }
    }
    cout << cnt << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}