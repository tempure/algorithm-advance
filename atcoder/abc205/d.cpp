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

// const int N = 1e5 + 10;
vector<ll> v;
// ll s[N];

ll findKthPositive(vector<ll>& arr, ll k) {
    if (arr[0] > k) {
        return k;
    }

    ll l = 0, r = arr.size();
    while (l < r) {
        ll mid = (l + r) >> 1;
        ll x = mid < 1ll * arr.size() ? arr[mid] : LLONG_MAX;
        if (x - mid - 1 >= k) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    return k - (arr[l - 1] - (l - 1) - 1) + arr[l - 1];
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i =  1; i <= n; i++) {
        ll x; cin >> x;
        v.push_back(x);
    }
    // for (int i = 1; i <= n; i++) cin >> a[i], s[i] += s[i - 1];
    sort(all(v));
    while (q --) {
        ll k;
        cin >> k;
        cout << findKthPositive(v, k) << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}