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

//高难度の神秘构造。。。
//https://codeforces.com/blog/entry/101211

typedef vector<vi> vvi;
vvi al;
vi ans;

void dfs(int u, int p, int c) {
    ans[u] = ((int)al[u].size()) * c;
    for (int v : al[u]) {
        if (v != p) {
            dfs(v, u, -c);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    al = vvi(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        al[u].push_back(v);
        al[v].push_back(u);
    }
    ans = vi(n);
    dfs(0, -1, 1); //选1号点为root 不影响答案
    for (int i = 0; i < n; ++i) {
        cout << ans[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}