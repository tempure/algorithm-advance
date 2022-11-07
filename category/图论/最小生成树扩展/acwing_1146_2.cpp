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

/*
虚拟源点，稠密图，prim，注意最外层循环次数是点数，每次处理一个点，然后用最优的点去更新其他点
内层循环是n+1个点，不要落了虚拟源点
*/

const int N = 310;
int d[N], w[N][N];
bool st[N];
int n;
ll res = 0;

void prim() {
    memset(d, 0x3f, sizeof d);
    d[0] = 0;
    for (int i = 0; i < n + 1 ; i++) {
        int x = -1;
        for (int j = 0; j < n + 1; j++)
            if (!st[j] && (x == -1 || d[j] < d[x]))
                x = j;
        st[x] = true;
        res += d[x];
        for (int y = 0; y < n + 1; y++)
            if (!st[y]) d[y] = min(d[y], w[x][y]);
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[0][i];
        w[i][0] = w[0][i];
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> w[i][j];
    prim();
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}