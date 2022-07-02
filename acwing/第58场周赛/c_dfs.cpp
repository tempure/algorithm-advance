#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010;

int n;
int h[N], w[N], e[N], ne[N], idx;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int dfs(int u, int c)
{
    int res = w[u] != c;
    for (int i = h[u]; ~i; i = ne[i])
        res += dfs(e[i], w[u]);
    return res;
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
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);

    printf("%d\n", dfs(1, 0));

    return 0;
}