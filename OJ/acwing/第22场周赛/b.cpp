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


//较好的题解：https://www.acwing.com/solution/content/70864/

const int N = 2e5 + 10;
pii a[N];
int t[N];
int b[N];
int res[N];
int n, k;

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x;
        t[i] = a[i].x;
        a[i].y = i;
    }
    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        b[x] = b[x] + (t[x] > t[y]);
        b[y] = b[y] + (t[y] > t[x]);
    }
    sort(a + 1, a + n + 1);
    sort(t + 1, t + 1 + n);
    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(t + 1, t + n + 1, a[i].x) - t - 1;
        res[a[i].y] = pos - b[a[i].y];
    }
    for (int i = 1; i <= n; i++) printf("%d ", res[i]);
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}