#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
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

//一定有一种走法会1和n直连，所以直接求另外一种走法的最短路即可
//没有重边

const int N = 410;

int n, m;
int f[N][N], g[N][N]; //两种路线

int floyd(int d[][N]) {
    if (d[1][n] == 1) return 1; //优化
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    return d[1][n];
}

void solve() {
    cin >> n >> m;
    memset(f, 0x3f, sizeof f);
    memset(g, 0x3f, sizeof g);

    while (m --) {
        int a, b;
        cin >> a >> b;
        f[a][b] = f[b][a] = 1;
    }

    //公路
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j && f[i][j] != 1)
                g[i][j] = g[j][i] = 1;

    int a = floyd(f), b = floyd(g);
    int res = max(a, b);
    if (res == 0x3f3f3f3f) res = -1;
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}
