#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define x first
#define y second

/*
若干个连通块之间加一条边，要图的直径最小

一个显然的性质：加一条边连接2个连通块后大连通块的直径必然大于原来的2个之一任何一个连通块的直径

所以要么最大直径属于一个独立的连通块，尝试连接其他的所有任何2个连通块得到的直径都小于该独立连通块
要么最大就是该独立连通块的直径

如果尝试连接2个连通块后得到的最小直径都大于最大的独立连通块直径，那么答案就是该连通块连接后的直径

两种情况取max即可得到较大的那个 必须要取的直径
*/

const int N = 150;
const double INF = 1e20;
int n;
pii q[N];
char g[N][N];
double d[N][N], maxd[N];

double get(pii a, pii b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++)cin >> q[i].x >> q[i].y;
    for (int i = 0; i < n; i++) cin >> g[i];

    for (int i = 0; i < n; i++)
        for (int j =  0; j < n; j++)
            if (i != j)
                if (g[i][j] == '1') d[i][j] = get(q[i], q[j]);
                else d[i][j] = INF;

    //floyd
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j =  0; j < n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j ++)
            if (d[i][j] < INF)
                maxd[i] = max(maxd[i], d[i][j]);

    //连通块内的最长直径
    double res1 = 0;
    for (int i = 0; i < n; i++) res1 = max(res1, maxd[i]);

    double res2 = INF;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (d[i][j] >= INF)
                res2 = min(res2, get(q[i], q[j]) + maxd[i] + maxd[j]);

    printf("%lf", max(res1, res2));
}

int main() {
    solve();
    return 0;
}