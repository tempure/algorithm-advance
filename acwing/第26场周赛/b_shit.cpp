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

void solve() {
    unordered_map<char, vi> m;
    string s;
    cin >> s;
    int temp[26];
    meset(temp, 0xcf, sizeof temp);
    for (int i = 1; i <= sz(s); i++)
        m[s[i - 1]].pb(i);
    // for (auto t : m) sort(all(t.second));
    int res = 0x3f3f3f3f;
    for (auto t : m) {
        auto p = t.first - 'a';
        auto v = t.second;
        for (int i = 1; i < sz(v); i++) {
            temp[p] = max(temp[p], v[i] - v[i - 1] - 1);
        }
    }
    for (int i = 0; < 26; i++) {
        if (temp[i] >= 0) res = min(res, temp[i]);
    }
    cout << res << endl;
    // int res = 0;
    // if (res == 0x3f3f3f3f) res = (sz(s)) / 2 + 1;
    // cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}