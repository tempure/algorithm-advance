#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 5;
int f[N], a[N], ma[N], ans[N];

//感觉根本没有必要记录 blockship 啊。。。。
//https://www.cnblogs.com/zdragon1104/p/12396167.html

int Find(int x) {
    if (x == f[x]) return x;
    return f[x] = Find(f[x]);
}


int main() {
    //freopen("in.txt","r",stdin);
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) f[i] = i;
    for (int i = 0, x, y; i < m; i++) {
        scanf("%d%d", &x, &y);
        a[x]++, a[y]++;
        f[Find(x)] = Find(y);
    }
    for (int i = 1; i <= n; i++) {
        ma[Find(i)]++;
    }
    for (int i = 1; i <= n; i++) {
        ans[i] = ma[f[i]] - a[i] - 1;
    }
    for (int i = 0, x, y; i < k; i++) {
        scanf("%d%d", &x, &y);
        if (f[x] == f[y]) ans[x]--, ans[y]--;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d%c", ans[i], i == n ? '\n' : ' ');
    }
    return 0;
}