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

//贪心 O(N)
//直接每次一直向右枚举就行了。。。

const int N = 1010;

int n, r;
int q[N], cnt;

void solve() {
    cin >> n >> r;
    for (int i = 1; i <= n; i ++ )
    {
        int a;
        cin >> a;
        if (a) q[cnt ++ ] = i;
    }

    int res = 0, last = 0;
    for (int i = 0; i < cnt; i ++ )
    {
        if (last >= n) break;
        if (q[i] - r > last)
        {
            res = -1;
            break;
        }

        int j = i;
        while (j + 1 < cnt && q[j + 1] - r <= last) j ++ ;
        last = q[j] + r - 1;
        res ++ ;
        i = j;
    }

    if (last < n) res = -1;
    cout << res << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}