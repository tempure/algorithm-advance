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

const int N = 55;
int n, m;
int row[N], col[N];

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int c;
            cin >> c;
            if (c) {
                row[i] ++;
                col[j] ++;
            }
        }
    ll res = 0;
    for (int i = 0; i < n; i++) {
        res += (1ll << row[i]) - 1;
        res += (1ll << m - row[i]) - 1;
    }
    for (int i = 0; i < m; i++) {
        res += (1ll << col[i]) - 1;
        res += (1ll << n - col[i]) - 1;
    }
    cout << res  - n * m << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}