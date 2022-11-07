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
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head

//https://atcoder.jp/contests/abc214/editorial/2450

//循环2n的理解：考虑极限情况，只有最后一个人最先拿到，其余的人默认的ti都是非常大的
//那么第二次循环，才能传遍，如果只循环一次，那么前面那些人都拿不到了

void solve() {
    int n;
    cin >> n;
    vi s(n), t(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> t[i];
    vi dp = t;
    for (int i = 0; i < n * 2; i++)
        dp[(i + 1) % n] = min(dp[(i + 1) % n], dp[i % n] + s[i % n]);
    for (auto x : dp) cout << x << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --)solve();
    return 0;
}