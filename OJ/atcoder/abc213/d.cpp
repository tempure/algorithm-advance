#include <bits/stdc++.h>
using namespace std;

// Euler tour on a tree

vector<vector<int>> G;
vector<int> ans;

void dfs(int u, int father) {
    ans.push_back(u);
    for (auto t : G[u]) {
        if (t == father)continue;
        dfs(t, u);
        ans.push_back(u);
    }
}

void solve() {
    int n;
    cin >> n;
    G.resize(n + 1); //点编号从1开始，0空出来
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int i = 1; i <= n; i++)
        sort(G[i].begin(), G[i].end());

    dfs(1, -1);

    for (int i = 0; i < (int)ans.size(); i++)
        cout << ans[i] << ' ';
}

int main() {
    solve();
    return 0;
}