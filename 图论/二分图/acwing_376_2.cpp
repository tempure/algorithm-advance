#include <bits/stdc++.h>
using namespace std;

/*
最小点覆盖板子题
注意初始读入忽略掉0模式，初始就在0，不需要转换
*/

const int N = 210, M = 1010; //注意点数和边数
int n, m, k;
int h[N], e[M], ne[M], idx;
int mc[N];
bool st[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool dfs(int u) {
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (st[j]) continue;
        st[j] = true;
        int t = mc[j];
        if (t == 0 || dfs(t)) {
            mc[j] = u;
            return true;
        }
    }
    return false;
}

void solve() {
    while (cin >> n && n) {
        cin >> m >> k;
        idx = 0;
        memset(h, -1, sizeof h);
        memset(mc, 0, sizeof mc);

        while (k --) {
            int a, b , t;
            cin >> t >> a >> b;
            if (!a || !b) continue;
            add(a, b);
        }

        int res = 0;
        for (int i = 1; i < n; i++) {
            memset(st, 0, sizeof st);
            if (dfs(i)) res++;
        }
        cout << res << endl;
    }
}

int main() {
    solve();
    return 0;
}