#include<stdio.h>

//https://atcoder.jp/contests/abc184/submissions/18335818
//类似于逆向搜索的思路
//初态是未知的，这个搜索思路把初态当作最终的结束搜索状态
//反着搜，回溯的时候用搜到的结果更新，最后回溯到初态

double dp[101][101][101];
double f(int a, int b, int c) {
    if (dp[a][b][c])return dp[a][b][c];
    if (a == 100 || b == 100 || c == 100)return 0;
    double ans = 0;
    ans += (f(a + 1, b, c) + 1) * a / (a + b + c);
    ans += (f(a, b + 1, c) + 1) * b / (a + b + c);
    ans += (f(a, b, c + 1) + 1) * c / (a + b + c);
    dp[a][b][c] = ans;
    return ans;
}

int main() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    printf("%.9f\n", f(a, b, c));
}