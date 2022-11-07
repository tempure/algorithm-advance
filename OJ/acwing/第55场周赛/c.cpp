#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 2010;

int n, m, sx, sy, X, Y;
int dist[N][N];
char g[N][N];
bool st[N][N];

//DP + 01BFS最短路 O(N*M)
//https://www.acwing.com/video/3952/

/*
dist[i][j] 表示从出发点到(i,j) 需要向右走的最短步数，用bfs求这个最短路
最短步数肯定就是净走向右的，把向左走的减去得到的净向右的
知道出发点和(i,j)的坐标后，以及需要向右走的最短步数，就可以求出向左走的步数了

假设从(sx, sy)出发点走到了(i,j), 向左走了a, 向右走了b
那么 b - a = j - sy => a = b - (j - sy), 仔细考虑一下起始 sy 和 j 的大小关系，减去无论正负不影响答案
*/

void bfs() {
    memset(dist, 0x3f, sizeof dist);
    dist[sx][sy] = 0;
    deque<PII> q;
    q.push_back({sx, sy});

    int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    while (q.size()) {
        auto t = q.front();
        q.pop_front();
        if (st[t.x][t.y]) continue;
        st[t.x][t.y] = true;

        for (int i = 0; i < 4; i ++ ) {
            int x = t.x + dx[i], y = t.y + dy[i];
            if (x < 0 || x >= n || y < 0 || y >= m || g[x][y] == '*') continue;
            int w = 0;
            if (i == 1) w = 1;
            if (dist[x][y] > dist[t.x][t.y] + w) {
                dist[x][y] = dist[t.x][t.y] + w;
                if (w) q.push_back({x, y});
                else q.push_front({x, y});
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d%d%d", &n, &m, &sx, &sy, &X, &Y);
    sx --, sy -- ; //下标改为 0 开始

    for (int i = 0; i < n; i ++ ) scanf("%s", g[i]);

    bfs();

    int res = 0;
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; j ++ ) {
            int b = dist[i][j];
            if (b <= Y && b - (j - sy) <= X)
                res ++ ;
        }

    printf("%d\n", res);
    return 0;
}