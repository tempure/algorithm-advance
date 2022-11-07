#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 2e5 + 10, M = 2 * N;
int h[N], e[M], ne[M], idx;
bool v[N];
int n;
int cnt;
int tmp;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {
    cout << u << ' ';
    if (u == 1) tmp++;
    if (tmp == cnt + 2) {
        return;
    }

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        // cout << j << ' ';
        dfs(j);
    }
}

void solve() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    for (int i = h[1]; ~i; i = ne[i]) {
        cnt++;
    }
    dfs(1);
}


int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}