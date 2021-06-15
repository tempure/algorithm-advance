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

/*
考虑floyd算法的本质：
如果d[i][j] = d[i][k] + d[k][j] 被更新，那么意味着此时i,j之间的最短路上点的编号最大就是k
对此性质考虑DP，将环上最大的点的编号为依据划分集合，环上最大的点为1，2，.... k
然后对于floyd过程中的每个循环变量k，都找一次最小环，此时d[i][j]已经是路径中最大编号点为k时求得的最短路
*/

const int N = 110, INF = 0x3f3f3f3f;
int n, m;
int d[N][N], g[N][N], pos[N][N];
int path[N], cnt;

void get_path(int i, int j) { //不包括
    if (pos[i][j] == 0) return;
    int k = pos[i][j];
    get_path(i, k);
    path[cnt++] = k;
    get_path(k, j);
}

void solve() {
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);
    for (int i = 1; i <= n; i++) g[i][i] = 0;

    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(g[a][b], c);
    }

    int res = INF;
    memcpy(d, g, sizeof d);
    for (int k = 1; k <= n; k++) {
        //对于当前循环的k 就是DP中的一个集合 直接求出以当前k为最大编号点的最小环和答案取min
        //floyd 一定要和dp过程同时进行，因为要保证当前状态是k为最短路径上最大编号的点来DP
        for (int i = 1; i < k; i++)
            for (int j = i + 1; j < k; j++)
                if (1ll * d[i][j] + g[j][k] + g[k][i] < res) {
                    res = d[i][j] + g[j][k] + g[k][i];
                    cnt = 0;
                    path[cnt++] = k;
                    path[cnt++] = i;
                    get_path(i, j);
                    path[cnt++] = j;
                }

        //floyd
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    pos[i][j] = k;
                }
    }

    if (res == INF) puts("No solution.");
    else {
        for (int i = 0; i < cnt; i++) cout << path[i] << ' ';
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}