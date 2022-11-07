#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 1e6 + 10;
int n, m;
int h[M], e[N], ne[N], idx;
int color[N], sz[M], p[M];
int ans;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    sz[a]++;
}

void merge(int &x, int &y) {
    if (x == y) return;
    if (sz[x] > sz[y]) swap(x, y);
    for (int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        ans -= (color[j - 1] == y) + (color[j + 1] == y);
    }
    for (int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        color[j] = y;
        if (ne[i] == -1) {
            ne[i] = h[y], h[y] = h[x];
            break;
        }
    }
    h[x] = -1;
}

void solve() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
        if (color[i] != color[i - 1]) ans++;
        /*
        这里他妈的是把数组中对应颜色的编号挂到对应的颜色下面
        链表头节点代表的直接是颜色

        p[]本质记录的是邻接表某一条链的代表颜色
        也就是说唯一记录颜色的只有p[]和开始的color[]

        由于启发式合并，如果直接swap color[]会被swap改变
        所以需要p[]来存一份 color，然后操作，color维护最初数组颜色的相邻关系

        用p[]就可以快速定位到当前swap很多次之后的邻接表中的哪一条链
        */
        add(color[i], i);
    }

    for (int i = 0; i < M; i++) p[i] = i;

    while (m --) {
        int op;
        cin >> op;
        if (op == 2) cout << ans << endl;
        else {
            int x, y;
            cin >> x >> y;
            merge(p[x], p[y]);
        }
    }
}

int main() {
    solve();
    return 0;
}