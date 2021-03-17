#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 500010, M = N * 2;

int n, root;
int h[N], e[M], w[M],  ne[M], idx;
ll d[N], ans;

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int father) {
    for (int i = h[u]; i != - 1; i = ne[i]) {
        int j = e[i];
        if (j == father)continue;
        dfs(j, u);
        d[u] = max(d[u], d[j] + w[i]);
    }

    for (int i = h[u]; i != - 1; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
        ans += d[u] - (d[j] + w[i]);
    }
}

int main() {
    scanf("%d%d", &n, &root);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }
    dfs(root, -1);
    printf("%lld\n", ans);

    return 0;
}