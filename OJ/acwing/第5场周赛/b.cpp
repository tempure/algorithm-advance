#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
typedef vector<long long> vi;
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

const int N = 35;
ll a[N];
map<ll, int> m;

void get(ll x, vi &v, int k) {
    while (x) {
        v.pb(x % k);
        x /= k;
    }
    // reverse(all(v));
}

void solve() {
    int n, k;
    m.clear();
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    bool flag = true;
    for (int i = 0; i < n; i++) {
        vi v;
        get(a[i], v, k);
        // for (auto t : v) cout << t << ' ' ;
        // cout << endl;
        for (int i = 0; i < sz(v); i++) {
            if(v[i] > 1) flag = false;
            else if (v[i]) m[i] ++;
        }
    }
    for (auto t : m) if (t.second > 1) flag = false;
    if (flag) cout << "YES" << endl;
    else cout << "NO" << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}