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

const int N = 1e5 + 10, M = 2 * N;
int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dout[N]; //出度
double f[N]; //DP

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a];
    h[a] = idx ++;
}

double dp(int u) {
    if (f[u] >= 0) return f[u]; //记忆化
    if (u == n) return f[u] = 0; //终点
    f[u] = 0; //当前点先初始置为0 然后再加
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        f[u] += (w[i] + dp(j)) / dout[u];  //递归反向搜
    }
    return f[u];
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        dout[a]++;
    }

    memset(f, -1, sizeof f);
    printf("%.2lf\n", dp(1));

    return 0;
}