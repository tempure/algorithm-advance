#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
#define endl '\n'
#define watch(x) cerr << (#x) << " is " << (x) << endl
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

//https://atcoder.jp/contests/abc215/editorial/2513
// Eratosthenes’ sieve, 暴力求质因子 O(N*sqrt(N))

const int N = 1e5 + 10;

vi pfact(int x) {
    vi res;
    for (int i = 2; i * i <= x; i++) {
        while (x % i == 0) {
            x /= i;
            res.pb(i);
        }
    }
    if (x != 1) res.pb(x);
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<bool> fl(N, true);
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        vi v = pfact(a);
        for (auto &nx : v) {
            if (fl[nx]) { //一个素数被筛过就不用再次筛了
                for (int j = nx; j < N; j += nx)
                    fl[j] = false;
            }
        }
    }
    vi res;
    for (int i = 1; i <= m; i++)
        if (fl[i]) res.pb(i);
    cout << sz(res) << endl;
    for (auto x : res) {
        cout << x << endl;
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}