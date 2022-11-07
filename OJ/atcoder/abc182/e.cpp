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

//https://cp-wiki.vercel.app/en/tutorial/atcoder/ABC182/#problem-e-akari
//https://atcoder.jp/contests/abc182/editorial/326

void solve() {
    int h, w, n, m;
    cin >> h >> w >> n >> m;
    int a, b, c, d;
    vector<vector<int>> mat(h, vector<int>(w));
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        mat[a - 1][b - 1] = 1;
    }
    for (int i = 0; i < m; ++i) {
        cin >> c >> d;
        mat[c - 1][d - 1] = -1;
    }
    for (int i = 0; i < h; ++i) {
        bool light = false;
        for (int j = 0; j < w; ++j) {
            if (mat[i][j] == 1) {
                light = true;
            } else if (mat[i][j] == -1) {
                light = false;
            } else if (light)
                mat[i][j] = 2;
        }
        light = false;
        for (int j = w - 1; j >= 0; --j) {
            if (mat[i][j] == 1) {
                light = true;
            } else if (mat[i][j] == -1) {
                light = false;
            } else if (light)
                mat[i][j] = 2;
        }
    }
    for (int j = 0; j < w; ++j) {
        bool light = false;
        for (int i = 0; i < h; ++i) {
            if (mat[i][j] == 1) {
                light = true;
            } else if (mat[i][j] == -1) {
                light = false;
            } else if (light)
                mat[i][j] = 2;
        }
        light = false;
        for (int i = h - 1; i >= 0; --i) {
            if (mat[i][j] == 1) {
                light = true;
            } else if (mat[i][j] == -1) {
                light = false;
            } else if (light)
                mat[i][j] = 2;
        }
    }
    int ans = 0;
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
            ans += mat[i][j] > 0;
    cout << ans;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}