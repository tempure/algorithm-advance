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

//这个题本质应该是K-queens问题 选出K个不在同一行同一列的点
//好像用二分图应该可以优化（？
//但是数据范围较小可以直接暴力。。。
//https://www.cnblogs.com/zcr-blog/p/13253488.html

int n, m, T;
char mp[10][10];
bool mark[10][10];
int ans;

void solve() {
    cin >> n >> m >> T;
    for (int i = 1; i <= n; i++) {
        scanf("%s", mp[i] + 1);
    }
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < (1 << m); j++) {
            memset(mark, 0, sizeof(mark));
            for (int k = 0; k < n; k++) {
                if ((i >> k) & 1) {
                    for (int l = 1; l <= m; l++) {
                        mark[k + 1][l] = 1;
                    }
                }
            }
            for (int k = 0; k < m; k++) {
                if ((j >> k) & 1) {
                    for (int l = 1; l <= n; l++) {
                        mark[l][k + 1] = 1;
                    }
                }
            }
            int cnt = 0;
            for (int k = 1; k <= n; k++) for (int l = 1; l <= m; l++) if (!mark[k][l] && mp[k][l] == '#') cnt++;
            if (cnt == T) ans++;
        }
    }
    cout << ans;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}