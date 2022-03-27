#include <bits/stdc++.h>
using namespace std;

//思路就是反向的拓扑排序
//考虑一个成环的路径，这个路径上没有点的出度为0 所以会被全部保留
//最后保留下来的所有点出发都会经过环

int main(void) {
    int n, m;
    cin >> n >> m;

    vector<vector<int> > e(n);
    vector<int> out(n, 0);
    int x, y, sz, cur;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        e[y - 1].push_back(x - 1);
        out[x - 1]++;
    }

    queue<int>que;
    int ans = n;

    for (int i = 0; i < n; i++)if (out[i] == 0)que.push(i);
    while (!que.empty()) {
        ans--;
        cur = que.front();
        que.pop();
        sz = e[cur].size();
        for (int i = 0; i < sz; i++) {
            out[e[cur][i]]--;
            if (out[e[cur][i]] == 0)que.push(e[cur][i]);
        }
    }
    cout << ans << endl;
    return 0;
}