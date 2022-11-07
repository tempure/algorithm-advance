#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
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
//snippet-head


/*
在 n×m 的矩形中，枚举底为 i，高为 j 的直角三角形，共有 (n−i+1)(m−j+1)(n−i+1)(m−j+1) 种
只考虑斜边斜率大于 0 的情况
这样的直角三角形，其斜边上的两个端点一定在格点上，只需要考察斜边上除了端点
还存在的格点的数量，结论：有 gcd(i,j)−1 个。
那么这个三角形的斜边对三点共线的贡献即为：(gcd(i,j)−1)(gcd(i,j)−1) 种。
*/

ll C(ll n) { //计算C(n, 3)
    return 1ll * n * (n - 1) * (n - 2) /  6;
}

int main() {
    int n, m;
    cin >> n >> m;
    n++, m ++; //格点数
    //所有的选三个，减去三点共线情况(斜率为0，无穷，正负三种情况)
    ll res =  1ll * C(n * m) -  1ll * n * C(m) - 1ll * m * C(n);
    //减去斜率正负的 情况j
    n -- , m --; //还原成边长
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            res -= 2ll * (__gcd(i, j) - 1) * (n - i + 1) * (m - j + 1);
    cout << res << endl;
}