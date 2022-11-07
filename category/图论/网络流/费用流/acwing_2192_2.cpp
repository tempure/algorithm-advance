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

//运输问题直接改spfa代码版本：

const int N = 160, M = 5150 * 2 + 10, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], ne[M], f[M], w[M], idx;
int q[N], d[N], pre[N], incf[N];
bool st[N];

void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

bool spfa1() {
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

bool spfa2() {
    int hh = 0, tt = 1;
    memset(d, 0xcf, sizeof d);  //注意此处是0xcf
    memset(incf, 0, sizeof incf);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int ver = e[i];
            if (f[i] && d[ver] < d[t] + w[i]) {  //改符号
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

int EK1(int & flow, int & cost) {
    flow = cost = 0;
    while (spfa1()) {
        int t = incf[T]; //当前找到的新的增广路的流量
        flow += t, cost += t * d[T]; //此题没有单位费用，直接费用就是路径长度*流量
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    return cost;
}

int EK2(int & flow, int & cost) {
    flow = cost = 0;
    while (spfa2()) {
        int t = incf[T]; //当前找到的新的增广路的流量
        flow += t, cost += t * d[T]; //此题没有单位费用，直接费用就是路径长度*流量
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    return cost;
}


int main() {
    scanf("%d%d", &m, &n);
    S = 0, T = m + n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; i++) {
        int a;
        scanf("%d", &a);
        add(S, i, a, 0);
    }

    for (int i = 1; i <=  n; i++) {
        int b;
        scanf("%d", &b);
        add(m + i, T, b, 0);
    }

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            int c;
            scanf("%d", &c);
            add(i, m + j, INF, c);
        }

    int flow, cost;
    printf("%d\n", EK1(flow, cost));

    for (int i = 0; i < idx; i += 2) {  //一定要恢复原图，或者直接重新建图
        f[i] += f[i ^ 1], f[i ^ 1] = 0;
    }

    printf("%d\n", EK2(flow, cost));

    // for (int i = 0; i < idx; i += 2) {
    //     f[i] += f[i ^ 1], f[i ^ 1] = 0;
    //     w[i] = -w[i], w[i ^ 1] = - w[i ^ 1];
    // }
    // flow = cost = 0;
    // printf("%d\n", -EK(flow, cost));


    return 0;
}