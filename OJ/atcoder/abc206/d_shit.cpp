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

const int N = 2e5 + 10;
int a[N];
int n;
set<pii> s;

void solve() {
    cin >> n;
    if (n == 1) {
        cout << 0 << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int res = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (a[i] != a[n + 1 - i]) {
            if (s.count({a[i], a[n + 1 - i]}) || s.count({a[n + 1 - i], a[i]})) continue;
            else res ++;
        }
    }
    // cout << sz(s) - 1 << endl;
    cout << res - 1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}