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


//DFS 搜索所有18种可能组合


char op[5];
ll ans = 1e18;

void dfs(vector<ll> v, int u) { //u 搜索到第几位运算符
    if (sz(v) == 1) ans = min(ans, v[0]);
    else {
        for (int i = 0; i < sz(v); i++)
            for (int j = i + 1; j < sz(v); j++) {
                vector<ll> t;
                for (int k = 0; k < sz(v); k++)
                    if (k != i && k != j)
                        t.pb(v[k]);

                if (op[u] == '*') t.pb(v[i] * v[j]);
                else t.pb(v[i] + v[j]);
                dfs(t, u + 1);
            }
    }
}

void solve() {
    vector<ll> v(4);
    for (int i = 0; i < 4; i++) cin >> v[i];
    for (int i = 0; i < 3; i++)cin >> op[i];
    dfs(v, 0);
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}