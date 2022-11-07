#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int d[N];
bool v[N];
int g[N][N];
int n;

/*
prim算法是每次加点 kruskal 是每次加边

prim每次只更新一个点，然后bfs边缘的所有点，同时用已经维护的树来更新还没加入集合的点到集合的最小距离
正确性由BFS保证
*/

void prim() {
    d[1] = 0;
    for (int i = 1; i <= n - 1; i ++) {
        int x = -1;
        for (int j = 1; j <= n; j++)
            if (!v[j] && (x == -1 || d[x] > d[j]))
                x = j;
        v[x] = 1;
        for (int y = 1; y <= n; y++)
            if (!v[y]) d[y] = min(d[y], g[x][y]);
    }
}

int main() {
    cin >> n;
    memset(d, 0x3f, sizeof d);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> g[i][j];
    prim();
    int res = 0;
    for (int i = 1; i <= n; i++) res += d[i];
    cout << res << endl;

    return 0;
}