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

//排序，然后暴力判断，O(NlogN)

const int N = 2e5 + 10;
ll a[N];
pii p[N];

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], p[i] = {a[i], i};
    ll res = 0;
    sort(a + 1, a + 1 + n);
    sort(p + 1, p + 1 + n );
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n && a[i] * a[j] <= 2 * n; j++) {
            if (a[i]*a[j] == p[i].second + p[j].second) res++;
        }
// l:;
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}