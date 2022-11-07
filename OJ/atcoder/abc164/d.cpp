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

//https://atcoder.jp/contests/abc164/submissions/12357027
//https://img.atcoder.jp/abc164/editorial.pdf
//DP

const int MAXN = 200005, MOD = 2019;
int n;
char a[MAXN];
int f[MAXN], cnt[MAXN];

void solve() {
    scanf("%s", a + 1);
    n = strlen(a + 1);
    ll ans = 0;
    int cur = 1;
    ++cnt[0];
    for (int i = n; i; --i) //逆着算因为前面次幂高
    {
        f[i] = (f[i + 1] + (a[i] - '0') * cur) % MOD, cur = cur * 10 % MOD;
        ans += cnt[f[i]];
        ++cnt[f[i]];
    }
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}