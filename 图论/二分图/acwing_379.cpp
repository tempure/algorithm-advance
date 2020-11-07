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


//问题转化为 给N个点，选出最多的点的集合，
//让集合中任意2点之间都没有路径可以到达 求这个点集合的大小

//最小(重复)路径覆盖问题 一般都是有向无环图

//本题的答案就是最小重复路径覆盖的路径条数 先传递闭包 然后拆点求最大匹配 然后减去即可

//拆点的过程完全不需要在代码中实现，直接在原图中传递闭包，然后原图上求最大匹配即可

const int N = 210, M = 30010;

int n, m;
bool st[N], d[N][N];
int match[N];

bool dfs(int x) {
    for (int i = 1; i <= n; i++)
        if (d[x][i] && !st[i]) {
            st[i] = true;
            int t = match[i];
            if (t == 0 || dfs(t)) {
                match[i] = x;
                return true;
            }
        }
    return false;
}


int main() {
    scanf("%d%d", &n , &m);
    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        d[a][b] = true;
    }

    //传递闭包 求出新图
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] |= d[i][k] & d[k][j];

    int res = 0;

    //求最大匹配
    for (int i = 1; i <= n; i++) {
        memset(st, 0, sizeof st);
        if (dfs(i)) res ++;
    }

    printf("%d\n", n - res);

    return 0;
}