#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 500010, M = 1000010;

int n, m;
int w[N], cnt[M];

//双指针 j 前 i 后

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);

    int res = 0, l, r;
    for (int i = 1, j = 1, t = 0; i <= n; i ++ ) //t 不同数的个数
    {
        if (cnt[w[i]] == 0) t ++ ;
        cnt[w[i]] ++ ;

        while (t > m)
        {
            if (cnt[w[j]] == 1) t -- ;
            cnt[w[j]] -- ;
            j ++ ;
        }

        if (i - j + 1 > res)
        {
            res = i - j + 1;
            l = j, r = i;
        }
    }

    printf("%d %d\n", l, r);
    return 0;
}

// 作者：yxc
// 链接：https://www.acwing.com/activity/content/code/content/3105982/
// 来源：AcWing
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。