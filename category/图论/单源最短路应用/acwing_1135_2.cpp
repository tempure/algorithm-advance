#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
using pii = pair<int, int>;

/*
6个位置为起点分别求一边dijkstra预处理
然后暴力dfs从1开始后面5个数的全排列顺序
代表了这5个位置的访问顺序，同时更新答案即可
*/

const int N = 50010, M = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int dist[6][N];
bool v[N];
int h[N], ne[M], e[M], w[M], idx;
int source[6];
priority_queue<pii, vector<pii>, greater<pii> > q;
int n, m;

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void dijkstra(int start, int dist[]) {
    memset(dist, 0x3f, N * 4); //一个int 4 byte
    memset(v, 0, sizeof v);
    dist[start] = 0;

    q.push({0, start});

    while (q.size()) {
        auto t = q.top().second; q.pop();
        if (v[t]) continue;
        v[t] = 1;
        for (int i =  h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                q.push({dist[j], j});
            }
        }
    }
}

int dfs(int u, int start, int d) {
    if (u == 6) return d;
    int res = INF;
    for (int i = 1; i <= 5; i++) {
        if (!v[i]) {
            int next = source[i];
            v[i] = true;
            res = min(res, dfs(u + 1, i, d + dist[start][next]));
            v[i] = false;
        }
    }
    return res;
}

int main() {
    cin >> n >> m;
    source[0] = 1; //home
    for (int i = 1; i <= 5; i++) cin >> source[i];

    memset(h, -1, sizeof h);
    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c); add(b, a , c);
    }
    for (int i = 0; i < 6; i++) dijkstra(source[i], dist[i]);
    memset(v, 0, sizeof v);

    cout << dfs(1, 0, 0) << endl;

    return 0;
}