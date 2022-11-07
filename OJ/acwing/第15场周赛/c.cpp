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

//记忆话搜索 + dfs 同时判断环是否存在, 也可以求SCC，拓扑排序什么的，比较麻烦判环

const int N = 1010;

int n, m;
char g[N][N];
bool st[N][N]; //存储当前点出发能搜到的点，判断环
int f[N][N];
bool is_inf;
int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int dfs(int x, int y) {
    if (is_inf) return -1;
    int &v = f[x][y];
    if (v != -1) return v;
    st[x][y] = true;

    v = 1;
    for (int i = 0; i < 4; i++) {
        int a = x + dx[i], b = y + dy[i];
        if (a >= 0 && a < n && b >= 0 && b < m && g[a][b] == (g[x][y] + 1) % 4) {
            if (st[a][b]) {
                is_inf = true;
                return -1;
            }
            v = max(v, dfs(a, b) + 1); //存在环返回-1，这里结果就是0取max，很巧妙返回-1
        }
    }
    st[x][y] = false; //搜完每个点出发所有能走到的点后直接恢复现场,找环也是相对于每个点出发的所有搜索的点来说的
    return v;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> g[i];
        for (int j = 0; j < m; j++) {
            auto &c = g[i][j];
            if (c == 'Q') c = 0;
            else if (c == 'W') c = 1;
            else if (c == 'E') c = 2;
            else c = 3;
        }
    }
    memset(f, -1, sizeof f);
    int res = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int t = dfs(i, j);
            if (g[i][j]) t -= 4 - g[i][j]; //减去头部多余的几个，要从Q开始的才算
            res = max(res, t / 4); //如果<4的长度直接下取整就是0
        }
    if (is_inf) puts("infinity");
    else if (!res) puts("none");
    else cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}