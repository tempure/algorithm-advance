#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

//第一行 找右端点最小和左端点最大的区间
//枚举第二行 O(N)

const int INF = 1e9;

int main()
{
    int n, m;
    scanf("%d", &n);

    int a = INF, b = -INF;
    while (n -- )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        a = min(a, r);
        b = max(b, l);
    }

    scanf("%d", &m);

    int res = 0;
    while (m -- )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        if (b > r) res = max(res, b - r);
        if (a < l) res = max(res, l - a);
    }

    printf("%d\n", res);
    return 0;
}