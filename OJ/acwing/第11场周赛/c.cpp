#include <bits/stdc++.h>
using namespace std;

//https://www.acwing.com/solution/content/61074/ 容易理解的题解

const int N = 2e5 + 10, M = 2 * N;
int h[N], e[M], ne[M], idx;
int q[N], p[N]; //p is special point
int dist1[N], dist2[N];
int n, m, k;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a],  h[a] = idx++;
}

void bfs(int start, int dist[]) {
    memset(dist, 0x3f, 4 * N);
    dist[start] = 0;
    q[0] = start;

    int hh = 0, tt = 0;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + 1) {
                dist[j] = dist[t] + 1;
                q[++tt] = j;
            }
        }
    }
}

void solve() {
    cin >> n >> m >> k;
    memset(h, -1, sizeof h);

    for (int i = 0; i < k; i++) cin >> p[i];
    while (m --) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    bfs(1, dist1);
    bfs(n, dist2);

    sort(p, p + k, [&](int a, int b) {
        return dist1[a] - dist2[a] < dist1[b] - dist2[b];
    });

    int res = 0, x = dist1[p[0]];
    for (int i = 1; i < k; i++) {
        int t = p[i];
        res = max(res, dist2[t] + x + 1);
        x = max(x, dist1[t]);
    }
    cout << min(res, dist1[n]) << endl;
}

int main() {
    solve();
    return 0;
}