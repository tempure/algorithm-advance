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

//https://blog.csdn.net/mrcrack/article/details/107242298
//https://blog.csdn.net/Ratina/article/details/107163248

//森林（点导出子图）中树（连通块）的数量 = 总顶点数 − 总边数

void solve() {
    int n, i, u, v;
    ll ans = 0;
    scanf("%d", &n);
    //i 就是区间长度其实
    for (i = 1; i <= n; i++)ans += (ll)i * (n - i + 1); //i表示每次选择点的个数，(n-i+1)表示选择点集的可能数量。若无连线，全是孤立点，对应不同的连通分量。

    //枚举每条边
    for (i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        if (u > v)swap(u, v); //无向图，让边的节点，左小右大，方便处理
        ans -= (ll)u * (n - v + 1); //乘法原理,等价于(u-1+1)*(n-v+1).u-1+1代表区间[1,u]内的节点个数.(n-v+1)代表区间[v,n]内的节点个数
    }
    printf("%lld\n", ans);
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}