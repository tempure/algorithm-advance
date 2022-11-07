#include <bits/stdc++.h>
using namespace std;

//都是无向图 有向图是最小平树形图 用朱刘算法

const int N = 310, M = 8010;
int p[N];
int n, m;

struct Edge {
    int a, b, w;
    bool operator<(const Edge & t) {
        return w < t.w;
    }
} e[M];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) p[i] = i;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        e[i] = {a, b, w};
    }

    sort(e, e + m);
    int cnt = 0, res = 0;
    for (int i = 0; i < m; i++) {
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if (a != b) {
            p[a] = b;
            cnt++;
            res = max(res, w);
        }
    }
    cout << cnt << ' ' << res << endl;
}

int main() {
    solve();
    return 0;
}