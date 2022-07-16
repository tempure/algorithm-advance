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

const int N = 2010, MOD = 998244353;

int n, m, k;
int f[N][N];

//https://www.acwing.com/problem/content/4499/
//DP解法
//f[i][j]: 前i个人中恰好有j个人和左边的种类不一样
//f[i][j] = f[i-1][j-1] * (m-1) + f[i-1][j] * 1
//按照第 i 个人和左边是否种类相同分类DP

void solve() {
    cin >> n >> m >> k;
    f[1][0] = m; //初始值
    for (int i = 2; i <= n; i ++ )
        for (int j = 0; j <= k && j < i; j ++ ) {
            f[i][j] = f[i - 1][j]; //第i个人和左边一样
            //j-1边界问题，只有 j>=1 才行
            if (j) f[i][j] = (f[i][j] + f[i - 1][j - 1] * (m - 1ll)) % MOD;
        }
    cout << f[n][k] << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}