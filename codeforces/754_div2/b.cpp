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

//又是什么奇怪的思维题啊我超....

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (is_sorted(all(s))) {
        cout << 0 << '\n';
        return;
    }
    string t = s;
    sort(all(t));
    cout << 1 << '\n';
    vi ans;
    for (int i = 0; i < n; i++) {
        if (s[i] != t[i]) ans.pb(i + 1);
    }
    cout << sz(ans) << ' ';
    for (int i = 0; i < sz(ans); i++)
        cout << ans[i] << " \n"[i + 1 == sz(ans)];
}

int32_t main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}