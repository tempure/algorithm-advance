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

#define int long long
bool get(pii a, pii b, pii c) {
    return (b.x - c.x) * (b.y - a.y) == (b.y - c.y) * (b.x - a.x);
}

void solve() {
    int n;
    cin >> n;
    vector<pii> v(n + 10);
    for (int i = 1; i <= n; i++) {
        cin >> v[i].x >> v[i].y;
    }
    sort(v.begin() + 1, v.begin() + 1 + n);
    int res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
            for (int k = 1; k < j; k++) {
                if (!get(v[i], v[j], v[k]))
                    res++;
            }
    cout << res << endl;
}

signed main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}