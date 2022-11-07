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

//https://atcoder.jp/contests/abc189/submissions/19597299
//https://atcoder.jp/contests/abc189/editorial/591


//dp[x][1] 让（X1...Xn) 为真的方案数
//dp[x][0] 让（X1...Xn) 为假的方案数

void solve() {
    int N; cin >> N;
    ll dp[N + 1][2];
    dp[0][0] = 1; dp[0][1] = 1;
    for (int i = 0; i < N; i++) {
        string S; cin >> S;
        if (S == "AND") {
            dp[i + 1][1] = dp[i][1];
            dp[i + 1][0] = dp[i][0] * 2 + dp[i][1];
        } else {
            dp[i + 1][0] = dp[i][0];
            dp[i + 1][1] = dp[i][1] * 2 + dp[i][0];
        }
    }
    cout << dp[N][1] << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}