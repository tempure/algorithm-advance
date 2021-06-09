#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
const int N = 110, M = 200 * 2;
int h[N], ne[M], e[M], w[M], idx;
bool v[N];
int d[N];
int n, m;

priority_queue<pii, vector<pii>, greater<pii>> q;

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void dijkstra() {
    d[1] = 0;
    q.push({0, 1});

    while (q.size()) {
        auto t = q.top().second; q.pop();
        if (v[t]) continue;
        v[t] = 1;
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (d[j] > d[t] + w[i]) {
                d[j] = d[t] + w[i];
                q.push({d[j], j});
            }
        }
    }
}

int main() {
    cin >> n >> m;
    memset(d, 0x3f, sizeof d);
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }

    dijkstra();
    int res = -2e9;
    for (int i = 1; i <= n ; i++) {
        if (d[i] == 0x3f3f3f3f) {
            res = -1;
            break;
        }
        else res = max(res, d[i]);
    }

    if (res == -1) puts("-1");
    else cout << res << endl;

    // cout << res << endl;
}