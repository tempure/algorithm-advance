#include <bits/stdc++.h>

using namespace std;


//https://atcoder.jp/contests/abc176/submissions/16117065
//https://atcoder.jp/contests/abc176/editorial/79
//BFS嗯搜

int n, m, sx, sy, tx, ty;
int x[1005][1005];
char y[1005][1005];
deque<pair<int, int>> q;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int main() {
    scanf("%d%d%d%d%d%d", &n, &m, &sx, &sy, &tx, &ty);
    for (int i = 1; i <= n; i++)
        scanf("%s", y[i] + 1);
    x[sx][sy] = 1;
    q.emplace_back(sx, sy);
    while (!q.empty()) {
        tie(sx, sy) = q.front();
        q.pop_front();
        for (int i = 0; i < 4; i++) {
            int ta = sx + dx[i];
            int tb = sy + dy[i];
            if (y[ta][tb] == '.' && (!x[ta][tb] || x[sx][sy] < x[ta][tb])) {
                x[ta][tb] = x[sx][sy];  //不需要 magic
                q.emplace_front(ta, tb);
            }
        }
        for (int i = sx - 2; i <= sx + 2; i++)
            for (int j = sy - 2; j <= sy + 2; j++) {
                if (y[i][j] == '.' && !x[i][j]) {
                    x[i][j] = x[sx][sy] + 1; //magic
                    q.emplace_back(i, j);
                }
            }
    }
    // for (int i = 1; i <= n; i++) {for (int j = 1; j <= m; j++) printf("%d", x[i][j]); puts("");}
    printf("%d\n", x[tx][ty] ? x[tx][ty] - 1 : -1);
}