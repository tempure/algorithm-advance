#include <bits/stdc++.h>
using namespace std;
int edges[100010][2];
int n;

int dfs(vector<int> g[], int u, bool visit[], int& res) {
    visit[u] = true;
    int currComponentNode = 0;

    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!visit[v]) {
            int subtreeNodeCount = dfs(g, v, visit, res);

            if (subtreeNodeCount % 2 == 0)
                res++;

            else
                currComponentNode += subtreeNodeCount;
        }
    }

    return (currComponentNode + 1);
}


int maxEdgeRemovalToMakeForestEven(vector<int> g[], int N) {

    bool visit[N + 1];
    for (int i = 0; i <= N; i++)
        visit[i] = false;
    int res = 0; // Passed as reference
    // calling the dfs from node-0
    dfs(g, 1, visit, res);

    return res;
}

void addEdge(vector<int> g[], int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

int main() {
    cin >> n;
    if (n & 1) {
        cout << -1 << endl;
        return 0;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        edges[i][0] = a;
        edges[i][1] = b;
    }

    int N = n;
    vector<int> g[N + 1];
    for (int i = 0; i < N; i++)
        addEdge(g, edges[i][0], edges[i][1]);

    cout << maxEdgeRemovalToMakeForestEven(g, N);
    return 0;
}
