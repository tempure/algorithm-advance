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


pii a[110];
int n;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[i] = {x, i};
    }
    sort(a + 1, a + 1 + n);
    // for(int i = 1; i <= n; i++) cout << a[i].second;
    //     cout << endl;
    int xmin =  min(a[1].second, a[n].second);
    int xmax = max(a[n].second, a[1].second);
    // int t = min(a[1].second, n - a[1].second + 1) + min(a[n].second, n - a[n].second + 1);
    int t = xmin + n + 1 - xmax;
    // int tt = min(max(xmin, xmax), n + 1 - min(xmin, xmax));
    int tt = min(xmax, n + 1 - xmin);

    cout << min(tt, t) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}