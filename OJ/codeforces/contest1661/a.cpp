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

//直接贪心，a[2]-a[1] 只会考虑是否交换 a[1],b[1] 和 a[3]-a[2] 没关系

void solve() {
    int n; cin >> n;
    int a[n + 1], b[n + 1];
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    ll ans = 0;
    for (int i = 2; i <= n; i++) {
        ans += min(abs(a[i] - a[i - 1]) + abs(b[i] - b[i - 1]),
                   abs(a[i] - b[i - 1]) + abs(b[i] - a[i - 1]));
    }
    cout << ans << '\n';
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}