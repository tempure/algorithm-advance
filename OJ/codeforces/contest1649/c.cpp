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

//https://codeforces.com/contest/1649/submission/148636953
//https://codeforces.com/blog/entry/100592

vector<int> x[200000];
vector<int> y[200000];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int v;
            cin >> v;
            x[v].pb(i);
            y[v].pb(j);
        }
    }
    ll ans = 0;
    for (int i = 1; i <= 100000; i++) {
        sort(x[i].begin(), x[i].end());
        sort(y[i].begin(), y[i].end());
        ll sum = 0;
        for (int j = 1; j < x[i].size(); j++) {
            sum += j * (x[i][j] - x[i][j - 1]);
            ans += sum;
        }
        sum = 0;
        for (int j = 1; j < y[i].size(); j++) {
            sum += j * (y[i][j] - y[i][j - 1]);
            ans += sum;
        }
    }
    cout << ans << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}