#include <bits/stdc++.h>

//《算法竞赛进阶指南》,POJ1742,男人八题
//https://www.acwing.com/solution/content/11075/ 评论区作者
//和 lyd 视频讲的状态定义不一样，这个比较容易理解
//POJ会卡内存,要优化掉一维空间才行，这个是二维的写法

const int N = 1e2 + 5, M = 1e5 + 5;
int n, m, a[N], c[N], used[N][M];

int main() {
  while (scanf("%d %d", &n, &m) && n + m) {
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);

    // used[i][j]表示前i种硬币, 恰好组成j时, 至少需要多少枚第i种硬币.
    // (used[i][j]只可能取: -1, 0, 1, 2, ..., c[i]), 其中-1表示状态不可行, 前i种无论如何也组成不了j
    std::memset(used, -1, sizeof used);
    used[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j <= m; ++j) {
        // 一个也不选
        if (used[i - 1][j] >= 0)
          used[i][j] = 0;
        // 至少选一个
        else if (j - a[i] >= 0 && used[i][j - a[i]] >= 0 && used[i][j - a[i]] + 1 <= c[i])
          used[i][j] = used[i][j - a[i]] + 1;
        else
          used[i][j] = -1;
      }
    }
    int ans = 0;
    for (int j = 1; j <= m; ++j) {
      if (used[n][j] >= 0) ++ans;
    }
    printf("%d\n", ans);
  }
  return 0;
}