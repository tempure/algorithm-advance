#include <bits/stdc++.h>
using namespace std;

/*
1~n 旧 n + 1 ~ 2n 需要的新的
左列的点是第1,2..i天，右列也一样
建图看详细注释
*/


const int N = 1610, M = 1e4 + 10, INF = 0x3f3f3f3f;

int n, p, x, xp, y, yp, S, T;
int h[N], e[M], ne[M], idx, w[M], f[M];
int q[N], d[N], pre[N], incf[N];
bool st[N];

void add(int a, int b, int c, int d) {
    e[idx] = b, f[idx] = c, ne[idx] = h[a], w[idx] = d, h[a] = idx++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
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
    return incf[T] > 0;
}

int EK() {
    int cost = 0;
    while (spfa()) {
        int t = incf[T];
        cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    return cost;
}

void solve() {
    cin >> n >> p >> x >> xp >> y >> yp;
    S = 0, T = 2 * n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        int r;
        cin >> r;
        add(S, i, r, 0); //每天的旧毛巾 S向左边点连边
        add(n + i, T, r, 0); //每天需要的毛巾 向T连边
        add(S, n + i, INF, p); //直接购买新的毛巾
        if (i < n) add(i, i + 1, INF, 0); //停留到下一天
        if (i + x <= n) add(i, n + i + x, INF, xp); //当前天用完，向快洗后可以用的那天连边
        if (i + y <= n) add(i, n + i + y, INF, yp); //慢洗后的那天连边
    }
    cout << EK() << endl;
}

int main() {
    solve();
    return 0;
}