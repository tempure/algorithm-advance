#include <bits/stdc++.h>
using namespace std;

int dp[2000][2000];
int x[2000][2000], y[2000][2000], z[2000][2000];
char s[2000][2000];
const int M = 1000000007;

//https://atcoder.jp/contests/abc183/submissions/18111480
//https://atcoder.jp/contests/abc183/editorial/344

int main() {
    int h, w;
    scanf("%d%d", &h, &w);
    for (int i = 0; i < h; i++)scanf(" %s", s[i]);
    dp[0][0] = 1;
    for (int i = 0; i < h; i++)for (int j = 0; j < w; j++) {
            if (i == 0 && j == 0)continue;
            if (s[i][j] == '#')continue;
            if (j > 0)x[i][j] = (x[i][j - 1] + dp[i][j - 1]) % M;
            if (i > 0)y[i][j] = (y[i - 1][j] + dp[i - 1][j]) % M;
            if (i > 0 && j > 0)z[i][j] = (z[i - 1][j - 1] + dp[i - 1][j - 1]) % M;
            dp[i][j] = ((long long)x[i][j] + y[i][j] + z[i][j]) % M;
        }
    printf("%d\n", dp[h - 1][w - 1]);
}