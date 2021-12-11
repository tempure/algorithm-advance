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
#define watch(x) cerr << (#x) << " is " << (x) << endl
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

const int N = 1e5 + 10, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], idx;
int w[M];
int q[N], pre[N]; //pre store the previous veterx
ll dist[N];
bool st[N];
int path[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void spfa() {
    int hh = 0, tt = 1;
    memset(dist, 0x3f, sizeof dist);
    memset(pre, -1, sizeof pre);
    dist[1] = 0;
    q[0] = 1;
    st[1] = true;

    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                pre[j] = t;
                if (!st[j]) {
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }
    spfa();
    if (pre[n] == -1) puts("-1");
    else {
        int cnt = 0;
        for (int i = n; i != -1; i = pre[i])
            path[cnt++] = i;
        for (int i = cnt - 1; i >= 0; i--)
            cout << path[i] << ' ';
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}