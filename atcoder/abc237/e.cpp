#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
#define endl '\n'
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
const int M = 2 * N;
bool v[N];
int h[N], e[M], ne[M], w[M], idx;
int n, m;
int H[N];
int d[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a];
    if (H[a] > H[b]) w[idx] = H[a] - H[b];
    else if (H[a] < H[b]) w[idx] = -2 * (H[b] - H[a]);
    else w[idx] = 0;
    h[a] = idx++;
}

queue<int> q;
void spfa() {
    d[1] = 0; v[1] = 1;  //在队列中就是1 不在就是0
    q.push(1);
    while (q.size()) {
        int x = q.front(); q.pop();
        v[x] = 0;
        for (int i = h[x]; i != -1; i = ne[i]) {
            int y = e[i]; int u = w[i];
            if (d[x] + u > d[y]) {
                d[y] = d[x] + u;
                if (!v[y]) q.push(y), v[y] = 1;
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    memset(d, 0xcf, sizeof d);

    for (int i = 1; i <= n; i++) cin >> H[i];
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }
    spfa();
    int res = 0xcfcfcfcf;
    for (int i = 1; i <= n; i++) res = max(res, d[i]);
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}