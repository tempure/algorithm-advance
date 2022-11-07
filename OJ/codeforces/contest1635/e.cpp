#include <bits/stdc++.h>
using namespace std;

//https://codeforces.com/blog/entry/100153

const int N = 200001;

struct edge {
    int type, u, v;
};

vector <int> adj[N];
int col[N], topo[N];

void dfs(int v) {
    for (int u : adj[v]) if (col[u] == -1) {
            col[u] = col[v] ^ 1;
            dfs(u);
        }
}

bool BipartiteColoring(int n) {
    for (int i = 1; i <= n; ++i)
        col[i] = -1;
    for (int i = 1; i <= n; ++i) if (col[i] == -1) {
            col[i] = 0;
            dfs(i);
        }
    for (int i = 1; i <= n; ++i) for (int j : adj[i]) {
            if (col[i] == col[j]) {
                return false;
            }
        }
    return true;
}

bool TopologicalSort(int n) {
    vector <int> in(n + 1, 0);
    for (int i = 1; i <= n; ++i) for (int j : adj[i]) {
            in[j]++;
        }
    queue <int> q;
    for (int i = 1; i <= n; ++i) if (in[i] == 0) {
            q.push(i);
        }
    int ord = 0;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        topo[v] = ord++;
        for (int u : adj[v]) {
            in[u]--;
            if (in[u] == 0) {
                q.push(u);
            }
        }
    }
    return ord == n;
}

int main () {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector <edge> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i].type >> a[i].u >> a[i].v;
        adj[a[i].u].push_back(a[i].v);
        adj[a[i].v].push_back(a[i].u);
    }
    if (!BipartiteColoring(n)) {
        cout << "NO" << endl;
        return 0;
    }
    // col = 0 -> orient left, col = 1 -> orient right
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
    }
    for (edge e : a) {
        if (col[e.u] == 1)
            swap(e.u, e.v);
        if (e.type == 1) {
            adj[e.u].push_back(e.v);
        } else {
            adj[e.v].push_back(e.u);
        }
    }
    if (!TopologicalSort(n)) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    for (int i = 1; i <= n; ++i) {
        cout << (col[i] == 0 ? "L " : "R ") << topo[i] << endl;
    }
}
