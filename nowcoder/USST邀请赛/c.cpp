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

map<string, int> m;

void solve() {
    int n; cin >> n;
    while (n --) {
        string s; cin >> s;
        m[s]++;
    }
    ll res = 0;
    res += min(m["c"], m["at"]);
    m["c"] -= min(m["c"], m["at"]);
    m["at"] -= min(m["at"], m["c"]);

    if (m["c"] && m["a"] && m["t"]) {
        int mm = min({m["c"], m["a"], m["t"]});
        res += mm;
        m["c"] -= mm, m["a"] -= mm, m["t"] -= mm;
    }

    res += min(m["ca"], m["t"]);
    res += m["cat"];

    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}