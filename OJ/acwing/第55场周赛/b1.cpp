#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 200010, INF = 2e9;

//二分 O(nlogn)

int n, m;
int c[N], a[N], b[N];
int ans[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n + m; i ++ ) scanf("%d", &c[i]);
    for (int i = 0, j = 0, k = 0; i < n + m; i ++ ) {
        int t;
        scanf("%d", &t);
        if (t) b[ ++ j] = c[i];
        else a[ ++ k] = c[i];
    }

    b[0] = -INF, b[m + 1] = INF;
    for (int i = 1; i <= n; i ++ ) {
        int r = lower_bound(b, b + m + 2, a[i]) - b;
        if ((LL)a[i] - b[r - 1] <= (LL)b[r] - a[i]) ans[r - 1] ++ ;
        else ans[r] ++ ;
    }

    for (int i = 1; i <= m; i ++ )
        printf("%d ", ans[i]);

    return 0;
}