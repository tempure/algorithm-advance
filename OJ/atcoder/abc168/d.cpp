#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 1e5 + 10;

//裸BFS
//https://blog.csdn.net/weixin_44282912/article/details/106185617

int N, M;
vector<int> g[MAX];
int ans[MAX], vis[MAX];
queue<int> q;

bool bfs() {
    q.push(1); vis[1] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &v : g[u])
            if (!vis[v]) {
                ans[v] = u;
                q.push(v); vis[v] = 1;
            }
    }
    for (int i = 1; i <= N; i++)
        if (!vis[i]) return false;
    return true;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        g[u].push_back(v), g[v].push_back(u);
    }
    if (bfs()) {
        printf("Yes\n");
        for (int i = 2; i <= N; i++)
            printf("%d\n", ans[i]);
    }
    else printf("No\n");



    return 0;
}