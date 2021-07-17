#include <bits/stdc++.h>
using namespace std;

//注意是二分>mid的所有边，因为要求的是不满足的第一个mid，也就是>mid的全部可以分成二分图

const int N = 20010, M = 200010;
int h[N], e[M], ne[M], w[M], idx;
int n, m;
int color[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

bool dfs(int u, int c, int mid) {
    color[u] = c;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (w[i] <= mid) continue;
        if (color[j]) {
            if (color[j] == c) return false;
        }
        else if (!dfs(j, 3 - c, mid)) return false;
    }
    return true;
}

bool check(int mid) {
    memset(color, 0, sizeof color);
    for (int i = 1; i <= n; i++)
        if (!color[i])
            if (!dfs(i, 1, mid)) return false;
    return true;
}

void solve() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    int l = 0, r = 1e9;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << r << endl;
}

int main() {
    solve();
    return 0;
}