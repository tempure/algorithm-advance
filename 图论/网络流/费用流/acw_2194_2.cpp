#include <bits/stdc++.h>
using namespace std;

/*
注意一点:在费用流问题中，无向边必须建2次，不像最大流建一次即可，最大流的流量是可以合并的，但是费用流不行
费用流的2条正向边可能一正一负，不能合并，2点之间，加上残留网络的边，必须要建4倍边
此题是有向图不用考虑这个问题


消圈法始终没有用到 记得找模板
*/

const int N  = 110, M = 3 * N * 2 + 10, INF = 0x3f3f3f3f;
int h[N], e[M], ne[M], f[M], w[M], idx;
int a[N];
int q[N], d[N], pre[N], incf[N];
bool st[N];
int n, S, T;


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

int EK(int & flow, int & cost) {
    flow = cost = 0;
    while (spfa()) {
        int t = incf[T]; //当前找到的新的增广路的流量
        flow += t, cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }

    return cost;
}


void solve() {
    cin >> n;
    S = 0, T = n + 1;
    memset(h, -1, sizeof h);

    int tot = 0;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        tot += a[i];
        //向左右连边
        add(i, i < n ? i + 1 : 1, INF, 1); //如果是n号点 就向1号点连边
        add(i, i > 1 ? i - 1 : n, INF, 1); //如果是1号点 就向n号点连边
    }

    tot /= n;

    for (int i = 1; i <= n; i++)
        if (tot < a[i]) add(S, i, a[i] - tot, 0);
        else if (tot > a[i]) add(i, T, tot - a[i], 0);

    int flow, cost;
    printf("%d\n", EK(flow, cost));
}


int main() {
    solve();
    return 0;
}