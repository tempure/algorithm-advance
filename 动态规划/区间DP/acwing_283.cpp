#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;


//POJ 1179
//环形相关的DP直接拆开复杂一遍，复杂度降低一维 此题复杂度O(N^3)
//https://www.acwing.com/video/1970/

/*
同时维护当前区间合并计算得到的最大值和最小值，因为有正负，所以只记录最大或者最小不行
*/

const int N = 110, INF = 0x3f3f3f3f;
char c[N];
int a[N], FMAX[N][N], FMIN[N][N]; //f[l][r] 合并区间[l,r]点后的最优值  fmax是标准库某个函数 冲突

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        cin >> a[i];
    }
    for (int i = n + 1; i <= n * 2; i++) {
        c[i] = c[i - n];
        a[i] = a[i - n];
    }
    memset(FMAX, 0xcf, sizeof FMAX);
    memset(FMIN, 0x3f, sizeof FMIN);
    for (int i = 1; i <= n * 2; i++) FMAX[i][i] = FMIN[i][i] = a[i];

    //DP
    for (int len = 2; len <= n; len++)
        for (int l = 1; l + len - 1 <= n * 2; l++) {
            int r = l + len - 1;
            for (int k = l + 1; k <= r; k++)
                if (c[k] == 't') {
                    FMAX[l][r] = max(FMAX[l][r], FMAX[l][k - 1] + FMAX[k][r]);
                    FMIN[l][r] = min(FMIN[l][r], FMIN[l][k - 1] + FMIN[k][r]);
                }
                else {
                    FMAX[l][r] = max({FMAX[l][r], FMAX[l][k - 1] * FMAX[k][r], FMIN[l][k - 1] * FMIN[k][r]});
                    FMIN[l][r] = min({FMIN[l][r], FMAX[l][k - 1] * FMAX[k][r], FMIN[l][k - 1] * FMIN[k][r],
                                      FMAX[l][k - 1] * FMIN[k][r], FMIN[l][k - 1] * FMAX[k][r]
                                     });
                }
        }
    int ans = -INF;
    for (int i = 1; i <= n; i++) ans = max(ans, FMAX[i][i + n - 1]);
    cout << ans << endl;
    for (int i = 1; i <= n; i++)
        if (ans == FMAX[i][i + n - 1])
            cout << i << ' ';
    return 0;
}