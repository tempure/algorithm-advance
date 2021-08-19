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

const ll pm = (ll)2e18;
vector<string> ts;

void init() {
    for (ll p2 = 1; p2 <= pm; p2 *= 2)
        ts.push_back(to_string(p2));
}

int calc(string s, string t) {
    int tp = 0;
    int sp = 0;
    int taken = 0;
    while (sp < s.length() && tp < t.length()) {
        if (s[sp] == t[tp]) {
            taken++;
            tp++;
        }
        sp ++;
    }
    return sz(s) + sz(t) - 2 * taken;
}

void solve() {
    string n;
    cin >> n;
    int ans = sz(n) + 1;
    for (auto p2 : ts)
        ans = min(ans, calc(n, p2));
    cout << ans << endl;
}

int main() {
    init();
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}