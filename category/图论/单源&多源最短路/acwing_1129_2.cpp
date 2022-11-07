#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> pii;

const int N = 2500 + 10, M = 15000;
int h[N], ne[M], e[M], idx, w[M];
int d[N];
bool v[N];
int n, m;
int s, t;
priority_queue<pii , vector<pii>, greater<pii> > q; //第一维度是dist  第二维是节点编号 pair默认按照第一维排序

void add(int a, int b, int u) {
    e[idx] = b;
    w[idx] = u;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void dijkstra() {
    d[s] = 0;
    q.push({0, s});  //初始化第一个节点 距离为0

    while (q.size()) {
        int x = q.top().second; q.pop();
        if (v[x]) continue;
        v[x] = 1;
        for (int i = h[x]; i != -1; i = ne[i]) {
            int y = e[i], u = w[i];
            if (d[y] > d[x] + u) {
                d[y] = d[x] + u;
                q.push({d[y], y});
            }
        }
    }
}

int main() {
    memset(h, -1, sizeof h);
    memset(d, 0x3f, sizeof d);
    // int s, t;
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    dijkstra();
    cout << d[t] << endl;

    return 0;
}