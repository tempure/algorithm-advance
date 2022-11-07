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

//DFS生成法 只生成有效状态 比枚举法快
//从第i行生成第i+1行的合法状态
//https://www.acwing.com/activity/content/code/content/592418/
//https://www.acwing.com/video/1962/

vector<int> next_states;
int n, m;
long long f[12][1 << 11];

void dfs(int state, int x, int ns) { //第x列 ns下一个状态
    if (x == m) { //注意递归时候 x == m-1 时候就结束了在这里，列号是0~m-1
        next_states.push_back(ns);
        return;
    }
    // 竖着的长方形需要结束，必须填0
    if (state >> x & 1) {
        dfs(state, x + 1, ns);
        return;
    }
    // 竖着放一个新的1
    dfs(state, x + 1, ns | 1 << x);
    // 横着放一个00
    if (x < m - 1 && (state >> (x + 1) & 1) == 0)
        dfs(state, x + 2, ns);
}

void solve() {
    while (cin >> n >> m && n) {
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for (int i = 0; i < n; i++) //第0行全0生成第1行，意味着第一行可以任意填
            for (int j = 0; j < 1 << m; j++)
                if (f[i][j] > 0) {
                    next_states.clear();
                    dfs(j, 0, 0); // 使用“生成法”实现状压DP 列从0开始
                    for (int k = 0; k < next_states.size(); k++)
                        f[i + 1][next_states[k]] += f[i][j];
                }
        cout << f[n][0] << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}