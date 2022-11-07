//https://codeforces.com/blog/entry/99563
#include <bits/stdc++.h>

#define len(x) (int) (x).size()
#define all(x) (x).begin(), (x).end()
#define endl "\n"

using namespace std;

const int N = 4e5 + 100, H = 2e5 + 50;
vector <pair <int, int>> g[N];
string ans[N];
int pos[N];


void dfs(int v) {
    if (pos[v] == 0) {
        ans[v] = string(len(g[v]), 'L');
    }

    while (pos[v] < len(g[v])) {
        auto [i, ind] = g[v][pos[v]];
        if (i == -1) {
            pos[v]++;
            continue;
        }
        g[i][ind].first = -1, g[v][pos[v]].first = -1;
        if (v < H) {
            ans[v][pos[v]] = 'R';
        }
        pos[v]++;
        dfs(i);
    }
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;
    map <int, int> ind, cnt;
    int fre_ind = 0;

    vector <vector <int>> nums(m);
    for (int i = 0; i < m; i++) {
        int n;
        cin >> n;
        for (int _ = 0; _ < n; _++) {
            int x;
            cin >> x;
            if (!ind.count(x)) {
                ind[x] = fre_ind++;
            }
            x = ind[x];
            cnt[x]++;
            nums[i].push_back(x);
            g[i].emplace_back(x + H, len(g[x + H]));
            g[x + H].emplace_back(i, len(g[i]) - 1);
        }
    }

    for (auto [num, cn] : cnt) {
        if (cn % 2 == 1) {
            cout << "NO" << endl;
            return 0;
        }
    }

    for (int i = 0; i < N; i++) {
        dfs(i);
    }

    cout << "YES" << endl;
    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}