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

void solve() {
    int n;
    cin >> n;
    vi v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    for (int len = 1; len <= n - 1; len++) {
        int max1 = -1, min1 = 0x3f3f3f3f;
        int max2 = -1, min2 = 0x3f3f3f3f;
        for (int i = 0; i < len; i++) {
            if (v[i] > max1) max1 = v[i];
            if (v[i] < min1) min1 = v[i];
        }
        for (int i = len; i < n; i++) {
            if (v[i] > max2) max2 = v[i];
            if (v[i] < min2) min2 = v[i];
        }
        // cout << len <<  ' ' << max1 << ' ' << min2 << endl;
        if (max1 > min2) {
            puts("YES");
            return;
        }
    }
    puts("NO");
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}