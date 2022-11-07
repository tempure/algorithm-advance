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

//https://atcoder.jp/contests/abc238/editorial/3370

const int N = 2e5 + 10;
int p[N];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i <= n; i++) p[i] = i;
    while (q --) {
        int l, r;
        cin >> l >> r;
        if (find(l - 1) != find(r)) p[find(l - 1)] = p[find(r)];
    }
    if (find(0) == find(n)) puts("Yes");
    else puts("No");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}