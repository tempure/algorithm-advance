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

// #define int long long
int a[25];
unordered_map<int, int> m;

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        // int x;
        // cin >> x;
        // m[x]++;
        cin >> a[i];
    }
    int cnt = 0;
    for (int i = 1; i <= 1000; i++)
        for (int j = 1; j <= 1000; j ++) {
            m[4 * i * j + 3 * i + 3 * j]++;
            // cnt++;
            // m.erase(4 * i * j + 3 * i + 3 * j);
        }
    // for (auto t : m) cnt += t.second;
    for (int i = 0; i < n; i++) {
        if (m[a[i]] > 0) cnt++;
    }
    cout << n - cnt << endl;
}

signed main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}