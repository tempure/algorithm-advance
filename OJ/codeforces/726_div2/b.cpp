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


//放在任意2个对角线顶点即可
//本质就是两个点作为对角线围成的最大矩形

void solve() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;

    if (x == 1 && y == 1 )
        cout << 1 << ' ' << m << ' ' << n << ' ' << 1 << endl;
    else if (x == n && y == 1)
        cout << 1 <<  ' ' << 1 << ' ' << n << ' ' << m << endl;
    else if (x == 1 && y == m)
        cout << 1 << ' ' << 1 << ' ' << n << ' ' <<  m  << endl;
    else if (x == n && y == m)
        cout << 1 << ' ' << m << ' ' << n << ' ' << 1 << endl;
    else cout << 1 << ' ' << 1 << ' ' << n << ' ' << m << endl;

    // pii a[4] = {{1, 1}, {1, m}, {n, 1}, {n, m}};
    // int mx = -2e9;
    // pii ans1, ans2;
    // for (auto t : a)
    //     if (abs(t.first - x) + abs(t.second - y) > mx) {
    //         mx = abs(t.first - x) + abs(t.second - y);

    //     }
    // cout << ans.first
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t --) solve();

    return 0;
}