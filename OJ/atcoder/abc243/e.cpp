#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define fi first
#define se second
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

//https://atcoder.jp/contests/abc243/editorial/3563

struct Edge {
    int a, b, c;
};

vector<Edge> e(1010);
const int N = 310;
int d[N][N];
int n, m;

void solve() {
    memset(d, 0x3f, sizeof d);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        e.pb({a - 1, b - 1, c});
        d[a - 1][b - 1] = d[b - 1][a - 1] = c;
    }
    for (int k = 0; k < n; k++)
        for (int i =  0; i < n; i++)
            for (int j = 0; j < n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    int res = 0;
    for (auto t : e) {
        int a = t.a, b = t.b, c = t.c;
        bool flag = false;
        for (int i = 0; i < n; i++) {
            if (d[a][i] + d[i][b] <= c) flag = true;
        }
        if (flag) res++;
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}