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

const int N = 1010, M = 21010; //注意加了虚拟源点 要多加N条边！！！
int h[N], e[M], ne[M], w[M], idx;
bool v[N];
int d[N];
int n, m, s, p;
pq<pii, vector<pii>, greater<pii>> q;

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int dijkstra() {
    memset(d, 0x3f, sizeof d);
    memset(v, 0, sizeof v);
    d[0] = 0;
    q.push({d[0], 0});
    while (q.size()) {
        auto t = q.top().second;
        q.pop();
        if (v[t]) continue;
        v[t] = true;
        for (int i = h[t]; ~i ; i = ne[i]) {
            int j = e[i];
            if (d[j] > d[t] + w[i]) {
                d[j] = d[t] + w[i];
                q.push({d[j], j});
            }
        }
    }
    if (d[s] == 0x3f3f3f3f) return -1;
    else return d[s];
}

void solve() {
    memset(h, -1, sizeof h);
    idx = 0;
    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    cin >> p;
    while (p --) {
        int x; cin >> x;
        add(0, x, 0);
    }
    cout << dijkstra() << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // memset(h, -1, sizeof h);
    // int t = 1;
    // cin >> t;
    while (cin >> n >> m >> s) solve();

    return 0;
}