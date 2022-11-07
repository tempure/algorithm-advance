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
餐厅计划问题 最小费用流
*/

const int N = 1610, M = 10010, INF = 0x3f3f3f3f;

int n, p, x, xp, y, yp, S, T; // 天数 一块新的费用 快洗一块的天数 快洗一块的费用 慢洗一块的天数 慢洗一块的费用
int h[N], e[M], f[M], w[M], ne[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];

void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

bool spfa() {
    int hh = 0, tt = 1;
    memset(d, 0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (f[i] && d[ver] > d[t] + w[i]) {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(f[i], incf[t]);
                if (!st[ver]) {
                    q[tt++] = ver;
                    if (tt == N) tt = 0;
                    st[ver] = true;
                }
            }
        }
    }
    return incf[T] > 0; //如果大于0说明S可以走到T 不然就不连通
}

int EK() {
    int cost = 0;
    while (spfa()) {
        int t = incf[T]; //当前找到的新的增广路的流量
        cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    return cost;
}


int main() {
    scanf("%d%d%d%d%d%d", &n, &p, &x, &xp, &y, &yp);
    S = 0, T = n * 2 + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        int r;
        scanf("%d", &r);
        add(S, i, r, 0); //每天的旧毛巾 S向左边点连边
        add(n + i, T, r, 0); //每天需要的毛巾 向T连边
        add(S, n + i, INF, p); //直接购买新的毛巾
        if (i < n) add(i, i + 1, INF, 0); //停留到下一天
        if (i + x <= n) add(i, n + i + x, INF, xp); //当前天用完，向快洗后可以用的那天连边
        if (i + y <= n) add(i, n + i + y, INF, yp); //慢洗后的那天连边
    }

    printf("%d\n", EK());

    return 0;
}
