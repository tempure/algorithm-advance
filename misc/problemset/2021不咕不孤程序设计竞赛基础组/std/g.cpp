#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll a[10][10];
bool used[10];
ll dfs(int k, int t)
{
    if (k > n)
        return t % 2 ? -1 : 1;
    ll ans = 0;
    for (int i = n; i >= 1; i--)
    {
        if (used[i])
        {
            t++;
        }
        else
        {
            used[i] = true;
            ans += a[k][i] * dfs(k + 1, t);
            used[i] = false;
        }
    }
    return ans;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%lld", &a[i][j]);
        }
    }
    printf("%lld\n", dfs(1, 0));
    return 0;
}
