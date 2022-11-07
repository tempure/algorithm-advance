#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

/*
点分治基本思路不变，但是要同时维护到重心的距离和边的数量
开一个哈希数组f[]，每层递归的时候用来配对dist,也就是当前子树用之前子树更新的f[]来继续更新答案
每次递归完当前root的子树，用该子树更新f[]即可,每递归完一层，要恢复f[]来进行子树中路径的求解
不能用memset因为f[]是1e6级别的，开个数组p来记录每次递归对f[]的修改，恢复即可
*/

typedef pair<int, int> pii;

const int N = 200010, M = N * 2, S = 1e6 + 10, INF = 0x3f3f3f3f;

int n, m; //m->k
int h[N], e[M], ne[M], w[M], idx;
int f[S], ans = INF; //f[]哈希表 距离重心距离为x的最少边数为f[x]
pii p[N], q[N]; //分别存储当前递归层的所有子树和一个子树信息
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int get_size(int u, int fa) {
    if (st[u]) return 0;
    int res = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        res += get_size(j, u);
    }
    return res;
}

int get_wc(int u, int fa, int tot, int &wc) {
    if (st[u]) return 0;
    int sum = 1, ms = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        int t = get_wc(j, u, tot, wc);
        ms = max(ms, t);
        sum += t;
    }
    ms = max(ms, tot - sum);
    if (ms <= tot >> 1) wc = u;
    return sum;
}

void get_dist(int u, int fa, int dist, int cnt, int &qt) {
    if (st[u] || dist > m) return;
    q[qt++] = {dist, cnt}; //同时存储距离和边数
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        get_dist(j, u, dist + w[i], cnt + 1, qt);
    }
}

void calc(int u) {
    if (st[u]) return;
    get_wc(u, -1, get_size(u, -1), u);
    st[u] = true;

    int pt = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i], qt = 0;
        get_dist(j, u, w[i], 1, qt);
        for (int k = 0; k < qt; k++) {
            auto &t = q[k];
            if (t.x == m) ans = min(ans, t.y); //该子树上的点到重心距离为k直接更新答案
            ans = min(ans, f[m - t.x] + t.y);
            p[pt++] = t;
        }
        for (int k = 0; k < qt; k++) { //用该子树来更新f[]
            auto &t = q[k];
            f[t.x] = min(f[t.x], t.y);
        }
    }
    for (int i = 0; i < pt; i ++) //不能memset会超时，要恢复f[]用于下一层来递归子树
        f[p[i].x] = INF;

    for (int i = h[u]; i != -1; i = ne[i])
        calc(e[i]); //递归处理子树中符合条件的路径来更新ans
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }
    memset(f, 0x3f, sizeof f);
    calc(0);

    if (ans == INF) ans = -1;
    printf("%d\n", ans);

    return 0;
}