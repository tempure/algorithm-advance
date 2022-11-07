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

//https://blog.51cto.com/u_15127562/4151717

//DFS brute search divide by cases

int n, m, a, b, ans;
bool f[30][30];

void dfs(int x, int y, int z) {
    if (y == m + 1) {
        x++;
        y = 1;
    }
    if (z == a) {
        ans++;
        return;
    }
    if (x == n + 1) return;

    if (f[x][y]) dfs(x, y + 1, z);
    else {
        if (!f[x][y + 1] && y + 1 <= m) {
            f[x][y + 1] = true;
            dfs(x, y + 2, z + 1);
            f[x][y + 1] = false;
        }
        if (!f[x + 1][y] && x + 1 <= n)  {
            f[x + 1][y] = true;
            dfs(x, y + 1, z + 1);
            f[x + 1][y] = false;
        }
        dfs(x, y + 1, z);
    }
}

void solve() {
    scanf("%d%d%d%d", &n, &m, &a, &b);
    dfs(1, 1, 0);
    cout << ans;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}