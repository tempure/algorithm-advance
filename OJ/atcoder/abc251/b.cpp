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
#define rep(i,a,n) for (int i=a;i<n;i++)
//head

const int N = 310;
int n, w, a[N], ans;
bool vis[3010000];

void solve() {
    scanf("%d%d", &n, &w);
    rep(i, 0, n) {
        scanf("%d", a + i);
        vis[a[i]] = 1;
    }
    rep(i, 0, n) rep(j, i + 1, n)
    vis[a[i] + a[j]] = 1;
    rep(i, 0, n) rep(j, i + 1, n) rep(k, j + 1, n)
    vis[a[i] + a[j] + a[k]] = 1;
    rep(i, 0, w + 1) ans += vis[i];
    printf("%d\n", ans);
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}