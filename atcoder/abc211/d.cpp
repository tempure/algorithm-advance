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

const int N = 2e5 + 10, M = 4e5 + 10, MOD = 1e9 + 7;
int h[N], e[M], ne[M], idx;
int d[N];
int cnt[N];
int n, m;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void bfs() {
    memset(d, 0x3f, sizeof d);
    queue<int> q;
    q.push(1);
    cnt[1] = 1;
    d[1] = 0;

    while (q.size()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (d[j] > d[t] + 1) {
                d[j] = d[t] + 1;
                cnt[j] = cnt[t];
                q.push(j);
            }
            else if (d[j] == d[t] + 1)
                cnt[j] = (cnt[j] + cnt[t]) % MOD;
        }
    }
}

void solve() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    while (m --) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    bfs();
    // for (int i = 1; i <= n; i++) cout << cnt[i] << endl;
    cout << cnt[n] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}