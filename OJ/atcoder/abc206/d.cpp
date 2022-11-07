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

const int N = 2e5 + 10;
int a[N], e[N], h[N], w[N], ne[N], idx;
int p[N];
int v[N];
int n, cnt;
unordered_set<int> s;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int x, int fa) {
    v[x] = cnt;
    for (int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if (v[j] || j == fa) continue;
        dfs(j, x);
    }
}

void solve() {
    memset(h, -1, sizeof h);
    cin >> n;
    if (n == 1) {
        cout << 0 << endl;
        return;
    }

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s.insert(a[i]);
    }

    for (int i = 1; i <= n / 2; i++) {
        if (a[i] == a[n + 1 - i]) continue;
        int x = a[i], y = a[n + 1 - i];
        add(x, y), add(y, x);
    }

    for (int i = 1; i <= n; i++)
        if (!v[a[i]]) {
            dfs(a[i], -1);
            cnt++;
        }
    cout << sz(s) - cnt + 1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}