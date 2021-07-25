#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
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
//head

const int N = 1e5 + 10;
int dp[N][10];
// char s[N];

void solve() {
    string t = "#chokudai";
    string s;
    cin >> s;
    int n = s.length();
    s = "." + s;
    for (int i = 0; i <= n; i++) dp[i][0] = 1;
    for (int i = 1; i <= 8; i++) dp[0][i] = 0;

    //DP
    for (int j = 1; j <= 8; j++)
        for (int i = 1; i <= n; i++) {
            if (s[i] != t[j]) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % mod;
        }
    cout << dp[n][8] << endl;
}

int main() {
    solve();
    return 0;
}