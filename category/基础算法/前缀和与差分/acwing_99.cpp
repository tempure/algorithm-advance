#include <iostream>
using namespace std;

const int N = 5010;
int g[N][N];

int main() {
    int N, R;
    cin >> N >> R;
    int n = R, m = R; //最小的边界，边R的正方形可能包括素有的点
    for (int i = 0, x, y, w; i < N; i++) {
        cin >> x >> y >> w;
        x ++, y ++;  //前缀和从1开始计算，防止边界问题
        n = max(n, x), m = max(m, y); //更新最大边界
        g[x][y] += w;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            g[i][j] += g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1];

    int res = 0;

    for (int i = R; i <= n; i ++) //枚举右下角坐标
        for (int j = R; j <= m; j++)
            res = max(res, g[i][j] - g[i - R][j] - g[i][j - R] + g[i - R][j - R]);
    cout << res << endl;
    return 0;
}