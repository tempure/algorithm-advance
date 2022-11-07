#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//https://zhuanlan.zhihu.com/p/491176044

inline int rd() {
    int x = 0;
    bool f = 0;
    char c = getchar();
    for (; !isdigit(c); c = getchar()) f |= (c == '-');
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    return f ? -x : x;
}

inline int gc() {
    char c = getchar();
    for (; !isdigit(c); c = getchar());
    return c - '0';
}

#define N 4007
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define pii pair<int, int>

bool a[N][N];

int sum[N][N], p[N][N];

inline void work() {
    int n = rd();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            a[i][j] = a[i + n][j] = a[i][j + n] = a[i + n][j + n] = gc();
    int m = (n << 1);
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= m; ++j) {
            sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + a[i][j];
            p[i][j] = p[i - 1][j - 1] + a[i][j];
        }
    int ans = n * n;
    for (int x = n; x <= m; ++x)
        for (int y = n; y <= m; ++y)
            ans = min(ans, sum[x][y] - sum[x - n][y] - sum[x][y - n] + sum[x - n][y - n] + n - 2 * (p[x][y] - p[x - n][y - n]));
    printf("%d\n", ans);
}

int main() {
    for (int t = rd(); t; --t) work();
    return 0;
}