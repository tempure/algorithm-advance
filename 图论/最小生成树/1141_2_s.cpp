#include <bits/stdc++.h>
using namespace std;

/*
题目是非连通图，要求每一个连通块的MST
只能用 kruskal，prim只能一次性bfs求出一个连通块的MST
*/

const int N = 110, M = 210;
int n, k, m;
int p[N];

struct Edge {
    int a, b, w;
    bool operator< (const Edge & t) {
        return w < t.w;
    }
} e[M];

int find(int x) {
    if (x != p[x]) return p[x] = find(p[x]);
    return p[x];
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) p[i] = i;

    for (int i = 0; i < m; i++) {
        int a, b , w;
        cin >> a >> b >> w;
        e[i] = {a, b, w};
    }
    sort(e, e + m);
    int res = 0;
    for (int i = 0; i < m; i++) {
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if (a != b) p[a] = b;
        else res += w;
    }
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}