#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
const int N = 1000, M = 1500 * 2; //N要开成牧场数，本质是牧场间连边，奶牛只是在牧场里面
int h[N], ne[M], e[M], w[M], idx;
bool v[N];
int d[N];
int id[N];
int n, m, p;

priority_queue<pii, vector<pii>, greater<pii>> q;

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int dijkstra(int x) {
    memset(v, 0, sizeof v);
    memset(d, 0x3f, sizeof d);
    d[x] = 0;

    // priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, x});

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
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (d[id[i]] == 0x3f3f3f3f) return 0x3f3f3f3f;
        res += d[id[i]];
    }
    return res;
}

int main() {
    cin >> n >> p >>  m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) cin >> id[i];
    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }

    int res = 0x3f3f3f3f;
    for (int i = 1; i <= p; i++) res = min(res, dijkstra(i));
    cout << res << endl;

    return 0;
}