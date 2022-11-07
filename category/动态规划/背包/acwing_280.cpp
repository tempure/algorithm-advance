#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>


//https://www.acwing.com/video/1973/

using namespace std;
int n, m, d[205], p[205];
int f[21][801]; //向右平移400
bool choose[205][21][801];
void print(int i, int j, int k) {
    if (j == 0) return;
    if (choose[i][j][k + 400]) {
        print(i - 1, j - 1, k - (d[i] - p[i]));
        printf(" %d", i);
    } else {
        print(i - 1, j, k);
    }
}
int main() {
    int T = 0;
    while (cin >> n >> m && n) {
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &p[i], &d[i]);
        memset(f, 0xcf, sizeof(f));
        f[0][0 + 400] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = m; j; j--)
                for (int k = -20 * m; k <= 20 * m; k++) {
                    choose[i][j][k + 400] = false; // 默认不选
                    if (k - (d[i] - p[i]) < -20 * m || k - (d[i] - p[i]) > 20 * m) continue;
                    if (f[j][k + 400] < f[j - 1][k - (d[i] - p[i]) + 400] + d[i] + p[i]) { // 选
                        f[j][k + 400] = f[j - 1][k - (d[i] - p[i]) + 400] + d[i] + p[i];
                        choose[i][j][k + 400] = true;
                    }
                }
        int delta = 1 << 30;
        int raw_delta;
        int sum = 0;
        int ansk;
        for (int k = -20 * m; k <= 20 * m; k++)
            if (f[m][k + 400] >= 0 && (abs(k) < delta || abs(k) == delta && f[m][k + 400] > sum)) // f[m][k]合法
                delta = abs(k), raw_delta = k, sum = f[m][k + 400], ansk = k;
        // d-p=raw_delta
        // d+p=sum
        printf("Jury #%d\n", ++T);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", (sum - raw_delta) / 2, (sum + raw_delta) / 2);
        print(n, m, ansk);
        puts("\n");
    }
}