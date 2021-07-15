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
int a[N], f[N], g[N];
bool v[N];

void solve() {
    memset(v, 0, sizeof v);
    memset(f, 0, sizeof f);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[j] <= a[i]) f[i] = max(f[i], f[j] + 1);
        }
    }

    for (int i = 1; i <= n; i++) {
        g[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[j] >= a[i]) g[i] = max(g[i], g[j] + 1);
        }
    }
    // for(int i = 1; i<= n; i++) cout << f[i] << ' ';
    //     cout << endl;
    ll res = 1ll * (n + 1) * n / 2;
    for (int i = n; i >= 1; i--) {
        if (f[i] >= 3 || g[i] >= 3) {
            res -= 1ll * (f[i] - 1) *  f[i] / 2;
            break;
        }
    }

    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}