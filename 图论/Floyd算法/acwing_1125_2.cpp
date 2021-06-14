#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define x first
#define y second

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