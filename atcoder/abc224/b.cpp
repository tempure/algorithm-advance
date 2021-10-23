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

const int N = 60;
int g[N][N];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> g[i][j];

    for (int i2 = 1; i2 <= n; i2++ )
        for (int i1 = 1; i1 < i2; i1++)
            for (int j2 = 1; j2 <= m; j2++)
                for (int j1 = 1; j1 < j2; j1++) {
                    if (g[i1][j1] + g[i2][j2] > g[i2][j1] + g[i1][j2]) {
                        puts("No");
                        return;
                    }
                }
    puts("Yes");
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}