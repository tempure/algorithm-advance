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

const int N = 5010;
int n;
int c[N], f[N][N];

void solve() {
    cin >> n;
    for (int i =  0; i < n; i++) {
        cin >> c[i];
        if (i && c[i] == c[i - 1]) {
            i --; //缩点 初始把所有颜色相同的块缩成一个点
            n --;
        }
    }
    //区间DP
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            if (c[l] != c[r]) f[l][r] = min(f[l + 1][r], f[l][r - 1])  + 1;
            else f[l][r] = f[l + 1][r - 1] + 1;
        }
    cout << f[0][n - 1] << '\n';
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}