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


//https://blog.csdn.net/m0_62325831/article/details/123889298

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    s = " " + s;
    vector<int> pos(26), pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        pre[i] = pos[s[i] - 'a'];
        pos[s[i] - 'a'] = i;
    }
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1];
        if (pre[i]) {
            dp[i] = max(dp[i], dp[pre[i] - 1] + 2);
        }
        // cout << i << ' ' << pre[i] << ' ' << dp[i] << endl;
    }
    cout << n - dp[n] << "\n";
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}