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

#define int long long

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y  = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

ll lowbit(ll x){
    return x & -x;
}

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto &x : a) cin >> x;
    sort(all(a));
    for (int i = 0; i < n - 1; i++) {
        ll bb = a[n - 1] - a[i];
        ll mm = 10;
        ll aa = a[i];

        ll x, y;
        ll d = exgcd(aa, mm, x, y);
        // if (bb % d) {
        //     puts("No1");
        //     return;
        // } else {
            ll tmp = x + 1;
            if (tmp == lowbit(tmp)) {
                puts("Yes");
                return;
            }
            else {
                puts("No2");
                return;
            }
        }
    // }
}

signed main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}