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

//https://atcoder.jp/contests/abc197/tasks/abc197_c
//bitwise exhaustive search

void solve() {
    int n;
    cin >> n;
    int a[n];

    for (int i = 0; i < n; i++) cin >> a[i];
    // int res = 0x3f3f3f3f;  //0x3f 会WA....
    int res = INT_MAX;
    for (int i = 0; i < 1 << (n - 1); i++) {
        int xors = 0, ors = 0;
        for (int j = 0; j <= n; j++) { //当前枚举的二进制i那些位是1,如果是1就当前位置插一个隔板
            if (j < n) ors |= a[j];
            if (j == n || (i >> j & 1)) xors ^= ors, ors = 0;
        }
        res = min(res, xors);
    }
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}