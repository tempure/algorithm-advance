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

//DSU 维护连通块
//每个连通块中如果点读书都是2 就行

const int N = 200010;

int n, m;
int p[N], d[N];
bool st[N];

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) p[i] = i;

    while (m -- ) {
        int a, b;
        scanf("%d%d", &a, &b);
        p[find(a)] = find(b);
        d[a] ++, d[b] ++ ;
    }

    for (int i = 1; i <= n; i ++ )
        if (d[i] != 2)
            st[find(i)] = true; //将 root 标记就行，表示这个集合不符合条件

    int res = 0;
    for (int i = 1; i <= n; i ++ )
        if (p[i] == i && !st[i])
            res ++ ;

    printf("%d\n", res);
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}