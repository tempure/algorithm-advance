#include <bits/stdc++.h>
using namespace std;
const int INF = INT_MAX / 2, dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
bool chmin(int& a, int b) { if (a > b) { a = b; return 1; } return 0; }

//https://atcoder.jp/contests/abc184/editorial/375
//std::tie: https://littlefall.blog.csdn.net/article/details/89367406

int main() {
    int H, W;
    cin >> H >> W;
    vector<string> a(H);
    for (auto& i : a) cin >> i;

    vector cost(H, vector(W, INF));
    vector tele(128, vector<pair<int, int>> {});
    int sx, sy, gx, gy;
    for (int x = 0; x < H; x++) for (int y = 0; y < W; y++) {
            const char c = a[x][y];
            if (islower(c)) tele[c].emplace_back(x, y);
            else if (c == 'S') tie(sx, sy) = pair{x, y};
            else if (c == 'G') tie(gx, gy) = pair{x, y};
        }
    cost[sx][sy] = 0;
    queue<pair<int, int>> q;
    q.emplace(sx, sy);

    while (q.size()) {
        auto [x, y] = q.front();
        q.pop();
        const int c2 = cost[x][y] + 1;
        for (int d = 0; d < 4; d++) {
            const int x2 = x + dx[d], y2 = y + dy[d];
            if (x2 < 0 || x2 >= H || y2 < 0 || y2 >= W || a[x2][y2] == '#') continue;
            if (chmin(cost[x2][y2], c2)) q.emplace(x2, y2);
        }
        if (islower(a[x][y])) {
            auto& t = tele[a[x][y]];
            for (auto [x2, y2] : t) if (chmin(cost[x2][y2], c2)) q.emplace(x2, y2);
            t.clear();
        }
    }

    int ans = cost[gx][gy];
    if (ans == INF) ans = -1;
    cout << ans << endl;
}