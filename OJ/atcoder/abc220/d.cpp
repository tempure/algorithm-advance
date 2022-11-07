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
const ll mod = 998244353;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head

const int N = 1e5 + 10;
ll dp[N][10];
int a[N];

void solve() {
    ll n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    dp[1][a[1]] = 1;

    for (ll i = 1; i <= n - 1; i++)
        for (ll j = 0; j <= 9; j++) {
            dp[i + 1][(j + a[i + 1]) % 10] =  (dp[i + 1][(j + a[i + 1]) % 10] + dp[i][j]) % mod;
            dp[i + 1][(j * a[i + 1]) % 10] =  (dp[i + 1][(j * a[i + 1]) % 10] + dp[i][j]) % mod;
        }
    for (ll k = 0; k <= 9; k++) {
        cout << dp[n][k] << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}