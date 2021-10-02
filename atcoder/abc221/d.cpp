#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
// #define x first
// #define y second
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


//本质还是统计区间厚度问题
//注意1, -1 的技巧

const int N = 2e5 + 10;
int ans[N] = {0};

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> x;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        x.pb({a, 1});
        x.pb({a + b, -1});
    }
    sort(all(x));
    int cnt = 0;
    for (int i = 0; i < sz(x) - 1; i++) {
        cnt += x[i].second;
        ans[cnt] += x[i + 1].first - x[i].first;
    }
    for (int i = 0; i < n; i++) cout << ans[i + 1] << ' ';
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}