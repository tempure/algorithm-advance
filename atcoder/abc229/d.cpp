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

const int N = 2e5 + 10;
char s[N];
int cnt[N];
ll k;

void solve() {
    cin >> s + 1;
    cin >> k;
    int n = strlen(s + 1);

    for (int i = 1; i <= n; i++) {
        if (s[i] == '.')cnt[i] = cnt[i - 1] + 1;
        else cnt[i] = cnt[i - 1];
    }
    ll ans = 0;
    ll r = 1;
    for (ll l = 1; l <= n; l++) {
        while (r <= n && cnt[r] - cnt[l - 1] <= k) {
            r = r + 1;
        }
        ans = max(ans, r - l + 1);
    }
    cout << ans - 1 << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}