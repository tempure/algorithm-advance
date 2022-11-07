#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;


/*
先让第一个圆覆盖全部，然后每次抛出一个让另外一个圆覆盖
这样直到第一个圆抛出所有点全部让第二个圆覆盖，枚举了所有状态空间
一定会取到答案过程中

注意先排序
*/

typedef long long LL;
typedef pair<int, int> PII;

const int N = 2010;

int n;
PII s1, s2;
PII q[N];

LL dist(PII a, PII b)
{
    LL dx = a.x - b.x;
    LL dy = a.y - b.y;
    return dx * dx + dy * dy;
}

bool cmp(PII a, PII b)
{
    return dist(s1, a) < dist(s1, b);
}

int main()
{
    cin >> n >> s1.x >> s1.y >> s2.x >> s2.y;
    for (int i = 0; i < n; i ++ ) cin >> q[i].x >> q[i].y;

    sort(q, q + n, cmp);

    LL res = 1e18, r = 0;
    for (int i = n - 1; i >= 0; i -- )
    {
        res = min(res, dist(q[i], s1) + r); // r 表示第二个圆心和第一个圆抛出的点的距离
        r = max(r, dist(q[i], s2));
    }

    res = min(res, r);
    printf("%lld\n", res);
    return 0;
}