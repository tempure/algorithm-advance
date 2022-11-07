#include <bits/stdc++.h>
using namespace std;

/*
先重链剖分，每次计算一个子树，只保留重子树的信息
意思就是先计算所有轻子树，最后计算重子树，然后将轻重合起来计算
重节点子树只会被计算一次，所有轻链不超过O(log)
每个点最多被重复计算log 总复杂度O(n*logn)
*/

typedef long long ll;
const int N = 100010, M = 2 * N;

int n;
int h[N], e[M], ne[M], idx;
int color[N], cnt[N], sz[N], son[N];
ll ans[N], sum;
int mx;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

//重链剖分
int dfs_son(int u, int father) {
    sz[u] = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
        sz[u] += dfs_son(j, u);
        if (sz[j] > sz[son[u]]) son[u] = j;
    }
    return sz[u];
}

void update(int u, int father, int sign, int pson) {
    int c = color[u];
    cnt[c] += sign;
    if (cnt[c] > mx) mx = cnt[c], sum = c;
    else if (cnt[c] == mx) sum += c;

    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == father || j == pson) continue;
        update(j, u, sign, pson);
    }
}

void dfs(int u, int father, int op) {
    //先计算所有轻子树
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == father || j == son[u]) continue;
        dfs(j, u, 0);
    }
    //如果有重子树 直接更新当前树
    if (son[u]) dfs(son[u], u, 1);
    update(u, father, 1, son[u]); //避开son[u]

    ans[u] = sum;
    if (!op) update(u, father, -1, 0), sum = mx = 0; //当前树的父节点不是重的，那就直接清空整个子树
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &color[i]);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    dfs_son(1, -1);
    dfs(1, -1, 1);

    for (int i = 1; i <= n; i++) printf("%lld ", ans[i]);

    return 0;
}