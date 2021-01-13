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
//head

/*
n个点分成m个部分，这m个部分连通，每部分都是一个简单环
求方案数，本质就是：有标号点仙人掌计数（每个点至多在一个环中）
大佬の题解：https://www.acwing.com/solution/content/20187/
*/

const int N = 210;

int n, m;
int C[N][N], g[N], f[N][N]; //C是组合数, g[k] = (k)!/2, f[][]是DP

void init() { //预处理g[] 以及组合数
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= i; j++)
            if (!j)  C[i][j] = 1;
            else C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % m;

    g[1] = 1, g[3] = 3; //2个点的环不存在 g[2] = 0
    for (int i = 4; i <= n; i++)  g[i] = g[i - 1] * i % m;

}

int main() {
    scanf("%d%d", &n, &m);
    init();

    //dp
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            for (int k = 1; k <= i - j + 1; k++)
                f[i][j] = (f[i][j] + f[i - k][j - 1] * (ll)C[i - 1][k - 1] * g[k]) % m;

    ll res = g[n - 1]; //n个点为一个环的情况 特判加上 直接作为初始答案
    ll p = 1;

    //直接从分成2个环开始枚举
    for (int k = 2; k <= n; k++) {
        res += f[n][k] * p;
        p = p * n % m;
    }

    printf("%lld\n", res % m);

    return 0;
}