#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;


//01  BFS

const int N = 5e2 + 10;
const int dx[] = { -1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

int n, m;
char s[N][N];
int dis[N][N];
bool vis[N][N];

bool chk(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> s[i] + 1;
    deque<pii> q;
    memset(dis, 0x3f, sizeof dis);
    dis[1][1] = 0;
    q.push_back({1, 1}); //start

    while (q.size()) {
        int x = q.front().first, y = q.front().second;
        q.pop_front();
        if (vis[x][y]) continue;
        vis[x][y] = 1;
        for (int k = 0; k < 4; ++k) { //无障碍能直接走的方法
            int xx = x + dx[k], yy = y + dy[k];
            if (!chk(xx, yy) || s[xx][yy] == '#' || dis[xx][yy] <= dis[x][y]) continue;
            dis[xx][yy] = dis[x][y];
            q.push_front(make_pair(xx, yy));
        }

        for (int i = -2; i <= 2; ++i) //不能直接走的
            for (int j = -2; j <= 2; ++j) if (abs(i) + abs(j) < 4) {
                    int xx = x + i, yy = y + j;
                    if (!chk(xx, yy) || dis[xx][yy] <= dis[x][y] + 1) continue;
                    dis[xx][yy] = dis[x][y] + 1;
                    q.push_back(make_pair(xx, yy));
                }
    }
    cout << dis[n][m] << endl;
}


int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}