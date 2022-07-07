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

const int N = 3010;

char a[N][N];
int n;
bitset<N> b[N];

//无向图三元环计数裸题
//bitset 优化一下 O(N^3 / 64)
//https://zhuanlan.zhihu.com/p/536825969

void solve() {
    cin >> n;
    for (int i = 0; i < n; i ++ ) cin >> a[i];

    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < n; j ++ )
            b[i][j] = a[i][j] - '0';

    ll ans = 0;
    for (int i = 0; i < n; i ++ )
        for (int j = i + 1; j < n; j ++ )
            if (a[i][j] - '0')
                ans += (b[i] & b[j]).count();

    cout << ans / 3 << endl;

}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}