#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

/*
VDCC缩点+分类讨论每个V-DCC里面含有的割点数量，类似于点的度数的思想

细节解释：关于求VDCC弹栈是while(y != j),也就是多个VDCC的交汇处的点没有被弹栈，
这是因为因为一个割点最少属于2个VDCC，删了其他VDCC就找不到这个割点了，考虑d->a->b->c->a这样一个环+一个点的图
abc三个点成环，但是a,d两个点连边这样的简单结构也是VDCC，所以当处理完abc环之后，此时是满足dfn[u]==low[j]，
当处理到d->a的边时候，此时满足的是dfn[u] < low[j],此时a必须还在栈中才能被d弹栈时候找到
*/

const int N = 1010, M = 510;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], ts, stk[N], top;
vector<int> vdcc[N]; //存放每个vdcc的所有点
int root, vdcc_cnt;
bool cut[N]; //判断是否是割点
int n, m, t = 1;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ts;
    stk[++top] = u;
    if (u == root && h[u] == -1) {
        vdcc_cnt ++;
        vdcc[vdcc_cnt].push_back(u);
        return;
    }
    int cnt = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (dfn[u] <= low[j]) {
                cnt ++; //u节点的子树的数量
                if (u != root || cnt > 1) cut[u] = true; //判断割点
                ++vdcc_cnt;
                int y;
                do {
                    y = stk[top --];
                    vdcc[vdcc_cnt].push_back(y);
                } while (y != j); //注意此处不会把割点出栈，因为一个割点最少属于2个VDCC，删了其他VDCC就找不到这个割点了
                vdcc[vdcc_cnt].push_back(u);
            }
        }
        else low[u] = min(low[u], dfn[j]);
    }
}

void solve() {
    memset(h, -1, sizeof h);
    memset(dfn, 0, sizeof dfn);
    for (int i = 1; i <= vdcc_cnt; i++) vdcc[i].clear();
    idx = ts = n = vdcc_cnt = top = 0;
    memset(cut, 0, sizeof cut);

    while (m --) {
        int a, b;
        cin >> a >> b;
        n = max(n, a), n = max(b, n);
        add(a, b), add(b, a);
    }

    for (root = 1; root <= n; root++)
        if (!dfn[root]) tarjan(root);

    ull res = 0, num = 1;
    for (int i = 1; i <= vdcc_cnt; i++) {
        int cnt = 0;//每个VDCC周围连接的割点数量
        for (int j = 0; j < (int)vdcc[i].size(); j++)
            if (cut[vdcc[i][j]]) cnt++;
        if (cnt == 0) {
            //判断孤立点
            if ((int)vdcc[i].size() > 1) res += 2, num *= (int)vdcc[i].size() * ((int)vdcc[i].size() - 1) / 2;
            else res ++;
        }
        else if (cnt == 1) {
            res ++;
            //判断孤立点
            if ((int)vdcc[i].size() > 1) num *= (int)vdcc[i].size() - 1;
        }
    }
    printf("Case %d: %llu %llu\n", t++, res, num);
}

int main() {
    while (cin >> m && m)
        solve();
    return 0;
}