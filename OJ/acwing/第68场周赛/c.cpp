#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

//https://www.acwing.com/problem/content/4617/
//https://www.acwing.com/video/4317/

const int N = 1 << 12, M = 110;

int n, m, q;
int w[12], weight[N];
int cnt[N], ans[N][M];

int get(char str[]) {
    reverse(str, str + n);
    int res = 0;
    for (int i = 0; i < n; i ++ )
        res = res * 2 + str[i] - '0';
    return res;
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n; i ++ ) scanf("%d", &w[i]);
    for (int i = 0; i < 1 << n; i ++ )
        for (int j = 0; j < n; j ++ )
            if (i >> j & 1)
                weight[i] += w[j]; //weight 是逆序过来二进制序列的 weight

    char str[20];
    while (m -- ) {
        scanf("%s", str);
        cnt[get(str)] ++ ;
    }

    int all = (1 << n) - 1;
    for (int i = 0; i < 1 << n; i ++ )
        for (int j = 0; j < 1 << n; j ++ )
        {
            int t = weight[i ^ j ^ all];
            if (t <= 100) ans[i][t] += cnt[j]; //和i匹配的j符合，j有cnt[j]个, 权重恰好为t
        }

    for (int i = 0; i < 1 << n; i ++ )
        for (int j = 1; j <= 100; j ++ )
            ans[i][j] += ans[i][j - 1]; //求前缀和，题目要求是 <= 100

    while (q -- ) {
        int k;
        scanf("%s%d", str, &k);
        printf("%d\n", ans[get(str)][k]);
    }

    return 0;
}