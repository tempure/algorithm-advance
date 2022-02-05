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

//匈牙利 或者贪心
//贪心思路：排序后任何交叉排序关系，都可以改为不交叉
//对方小的先配对

const int N = 110;

int n, m;
int a[N], b[N];


void solve() {
    cin >> n;
    for (int i = 0; i < n; i ++ ) cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; i ++ ) cin >> b[i];

    sort(a, a + n);
    sort(b, b + m);

    int res = 0;
    for (int i = 0, j = 0; i < n; i ++ ) {
        while (j < m && a[i] > b[j] + 1) j ++ ;
        if (j < m && a[i] >= b[j] - 1) {
            res ++ ;
            j ++ ;
        }
    }

    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}