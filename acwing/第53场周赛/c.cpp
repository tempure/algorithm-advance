#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010, INF = 2e9;

int n;
int h[N], e[N], ne[N], idx;
int s[N];
LL ans;


/*
只需要考虑偶数点和其父子节点构成的这一小块区域计算
所有的偶数点都被奇数点隔开互不影响
独立计算所有偶数点的区域求和即可
*/

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u, int depth, int last_s)
{
    if (depth % 2)
    {
        for (int i = h[u]; ~i; i = ne[i])
        {
            int j = e[i];
            dfs(j, depth + 1, s[u]);
        }
    }
    else
    {
        int p = INF;
        for (int i = h[u]; ~i; i = ne[i])
        {
            int j = e[i];
            p = min(p, s[j] - last_s); //不等式更新 p 取最小
            dfs(j, depth + 1, 0); //j是下一层奇数点，这一层偶数的last_s无所谓还没计算，赋值0就好，奇数点last_s没用
        }

        if (p < 0) ans = -1e18; //数据不合法，p点只能为负值

        for (int i = h[u]; ~i; i = ne[i])
        {
            int j = e[i];
            ans += s[j] - last_s - p;
        }

        if (p != INF) ans += p; //p不是叶子节点才考虑
    }
}

int main()
{
    scanf("%d", &n);
    memset(h, -1, sizeof h);

    for (int i = 2; i <= n; i ++ )
    {
        int p;
        scanf("%d", &p);
        add(p, i);
    }

    for (int i = 1; i <= n; i ++ ) scanf("%d", &s[i]);

    ans = s[1];
    dfs(1, 1, 0);

    if (ans < 0) ans = -1;

    printf("%lld\n", ans);

    return 0;
}

// 作者：yxc
// 链接：https://www.acwing.com/activity/content/code/content/3536388/
// 来源：AcWing
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。