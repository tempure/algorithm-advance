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

//  ./a.out <../data/p067_triangle.txt > 67.txt
// ans = 7273

int a[110][110];
const int N = 110;
ll dp[N][N];

void solve() {
    for (int i = 1; i <= 100; i++)
        for (int j = 1; j <= i; j++)
            cin >> a[i][j];
    dp[1][1] = a[1][1];
    for (int i = 1; i < N; i++)
        for (int j = 1; j < N; j++) {
            if (i > 1 && j > 1) dp[i][j] = max(dp[i][j], a[i][j] + dp[i - 1][j - 1]);
            if (i > 1) dp[i][j] =  max(dp[i][j], a[i][j] + dp[i - 1][j]);
        }
    ll res = -1;
    for (int i = 1; i <= 100; i++)
        res = max(res, dp[100][i]);
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}