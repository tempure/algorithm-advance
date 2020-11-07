#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
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
//snippet-head


//2个格子可以放 那么就把这2格子连一条边 然后求最大匹配即可
//整个图可以用二染色，那么就可以就是二分图了 继而可以用匈牙利算法
//点的行列下标从1开始 然后下标和为奇数的是一类点 偶数的是一类点

#define x first
#define y second

const int N = 110;
int n, m;
pii match[N][N];
bool g[N][N], st[N][N]; //每个点是不是能放 以及判重数组

int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

bool dfs(int x, int y) {
    for (int i = 0 ; i < 4; i++) {
        int a = x + dx[i], b = y + dy[i];
        if (a < 1 || a > n || b < 1 || b > n) continue;

        if (!st[a][b] && !g[a][b]) {  //坐标是ab的妹子还没匹配，而且这个位置合法
            pii t = match[a][b]; //坐标是ab的妹子以及匹配的男生
            st[a][b] = true;
            if (t.x == 0 || dfs(t.x, t.y)) {
                match[a][b] = {x, y};
                return true;
            }
        }
    }

    return false;
}

int main() {
    cin >> n >> m;
    while (m --) {
        int x, y;
        cin >> x >> y;
        g[x][y] = true; //不能放
    }

    int res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i + j & 1 && !g[i][j]) {
                memset(st, 0, sizeof st);
                if (dfs(i, j)) res ++;
            }

    cout << res << endl;

    return 0;
}