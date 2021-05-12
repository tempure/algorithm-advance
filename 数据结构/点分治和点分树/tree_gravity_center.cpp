//acwing846 树的重心
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 2 * N;
int h[N], e[M], ne[M], idx, sz[N];
bool v[N];
int n;
int ans = 0x3f3f3f3f;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int x) {
    sz[x] = 1;
    v[x] = true;

    int maxp = 0;
    for (int i = h[x]; ~i ; i = ne[i]) {
        int y = e[i];
        if (v[y]) continue;
        dfs(y);
        sz[x] += sz[y];
        maxp = max(maxp, sz[y]);
    }
    maxp = max(maxp, n - sz[x]);
    ans = min(ans, maxp);
}

int main() {
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    dfs(1);
    cout << ans << endl;

    return 0;
}