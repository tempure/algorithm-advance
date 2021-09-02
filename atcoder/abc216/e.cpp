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

const int N = 1e5 + 10;
int a[N];

void solve() {
    int n, k;
    cin >> n >> k;
    ll sum = 0;
    for (int i = 0; i < n; i++) cin >> a[i], sum += a[i];

    if (sum <= k) {
        ll res = 0;
        for (int i = 0; i < n; i++)
            res += (a[i] + 1) * a[i] / 2;
        cout << res << endl;
        return;
    }
    sort(a, a + n, greater<int>());

    int cnt = 0;
    ll res = 0;
    for (int i = 0; i < n - 1; i ++) {
        while (a[i] >= a[i + 1]) {
            cnt++;
            res += a[i];
            // cout << "***" << a[i] << endl;
            a[i] --;
            if (cnt >= k) break;
        }
    }
    // if (cnt < k) {
    //     while (a[n - 1] > 0 && cnt < k) {
    //         res += a[n - 1];
    //         cout << "##" <<  a[n-1] << endl;
    //         cnt++;
    //         a[n - 1]--;
    //     }
    // }
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}