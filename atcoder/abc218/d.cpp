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

//https://atcoder.jp/contests/abc218/editorial/2628
//暴力枚举做下角和右上角的坐标，然后同时二分检查左上角和右下角的点是否在图中
//当然也可以直接把所有点都初始放在set里面，查询起来更快

//O(N^2)

void solve() {
    int n;
    cin >> n;
    vector<pii> v(n);
    set<pii> S;
    for (int i = 0; i < n; i++) {
        cin >> v[i].x >> v[i].y;
        S.insert({v[i].x, v[i].y});
    }
    int res = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (v[i].x < v[j].x && v[i].y < v[j].y) {
                if (S.count({v[i].x, v[j].y}) && S.count({v[j].x, v[i].y}))
                    res ++;
            }
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}