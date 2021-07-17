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


void solve() {
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    int cnt1 = 0, cnt0 = 0;
    for (int i = 0; i < n; i++) {
        char x; cin >> x;
        if (x == '1') cnt1++;
        else cnt0++;
    }
    if (b > a + c) cout << cnt1 * (a + c) + cnt0 *a << endl;
    else if (a > b + c) cout << cnt0 * (b + c) + cnt1 *b << endl;
    else cout << cnt0 * a + cnt1 * b << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}