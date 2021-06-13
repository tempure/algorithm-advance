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

const int N = 1e5 + 10, M = 2e6 + 10;
int hs[N], ht[N], ne[M], w[N], e[M], idx;
int dmin[N], dmax[N];
int q[N];
int v[N];
int n, m;

void add(int h[], int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void spfa(int h[], int d[], int flag) {
    int hh = 0, tt = 1;
    if (flag == 0) {
        memset(d, 0x3f, sizeof dmin); //注意不要 memset 指针
        d[1] = w[1];
        q[0] = 1;
    }
    else {
        memset(d, 0xcf, sizeof dmax);
        d[n] = w[n];
        q[0] = n;
    }
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        v[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (flag == 0 && d[j] > min(d[t], w[j]) || flag == 1 && d[j] < max(d[t], w[j])) {
                if (flag == 0) d[j] = min(d[t], w[j]);
                else d[j] = max(d[t], w[j]);

                if (!v[j]) {
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                    v[j] = true;
                }
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    memset(hs, -1, sizeof hs);
    memset(ht, -1, sizeof ht);

    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(hs, a, b), add(ht, b, a);
        if (c == 2) add(hs, b, a), add(ht, a, b);
    }
    spfa(hs, dmin, 0);
    spfa(ht, dmax, 1);

    int res = 0;
    for (int i = 1; i <= n; i++) res = max(res, dmax[i] - dmin[i]);

    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}