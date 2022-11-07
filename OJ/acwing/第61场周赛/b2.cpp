#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20;

int n;
int w[N];

//DFS解法 O(2^n)

bool dfs(int u, int s) //当前搜索第 u 个数，总和是 s
{
    if (u == n) return s % 360 == 0;

    if (dfs(u + 1, s + w[u])) return true;
    if (dfs(u + 1, s - w[u])) return true;
    return false;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i ++ ) cin >> w[i];

    if (dfs(0, 0)) puts("YES");
    else puts("NO");

    return 0;
}