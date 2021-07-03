#include <bits/stdc++.h>
using namespace std;

/*
倍增求LCA, 预处理O(N*logN) 单次查询O(logN)

模板条件：点编号从1开始，大数据范围注意离散化
root的层数是1,题目需要说明root是几号点

bfs同时倍增预处理 fa[][]数组

细节：
哨兵：如果从i开始跳2^j跳出root，那么fa[i][j] = 0，这个在数组全局变量初始化即可
所以在同时往上跳的过程中，k是从大到小枚举，当k大的时候，会跳出，但是依然fa结果是0，还是相同的，保证正确
0号点的层数是0,root层数是1

fa[][]第二维开 K是不超过N的最大二次幂指数,考虑二进制拆分N，一个点计算fa[j][k]是用fa[fa[j][k-1]][k-1]来更新，也就是相当于跳2次，考虑最大的范围跳2次能跳到即可也就是不超过最大范围的2的次幂
*/

const int N = 40010, M = 2 * N; //无向边
const int K = 16; // 0 ~ 15 一共16个数 k是 不超过40000的最大二次幂指数 2^15 = 32768
int n, m;
int h[N], e[M], ne[M], idx, fa[N][K];
int depth[N], q[N]; //bfs队列 depth深度

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void bfs(int root) {
    memset(depth, 0x3f, sizeof depth); //本质就是从root开始bfs最短路,所以初始化为正无穷
    depth[0] = 0, depth[root] = 1; //边界
    int hh = 0, tt = 0;
    q[0] = root;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++tt] = j;
                fa[j][0] = t;
                for (int k = 1; k <= 15; k++)
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
            }
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 15; k >= 0; k --)
        if (depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    if (a == b) return a;

    //同时跳
    for (int k = 15; k >= 0; k--)
        if (fa[a][k] != fa[b][k]) {
            a = fa[a][k];
            b = fa[b][k];
        }
    return fa[a][0];
}

void solve() {
    cin >> n;
    int root = 0;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (b == -1) root = a;
        else add(a, b), add(b, a);
    }
    bfs(root);
    cin >> m;
    while (m --) {
        int a, b;
        cin >> a >> b;
        int p = lca(a, b);
        if (p == a) cout << 1 << endl;
        else if (p == b) cout << 2 << endl;
        else cout << 0 << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t --) solve();

    return 0;
}