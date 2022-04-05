#include <cstdio>
#include <algorithm>
using namespace std;

//https://cloud.tencent.com/developer/article/1695794

int vis[1000010], a[200010], in[1000010];
int main() {
    int n, i, j, cnt, mn = 1000010, mx = 0, ans = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)scanf("%d", &a[i]), vis[a[i]]++, in[a[i]] = 1, mn = min(mn, a[i]), mx = max(mx, a[i]);
    for (i = 1; i <= n; i++) {
        cnt = 1;
        while (1) {
            cnt++;
            if (a[i]*cnt > mx)break;
            vis[a[i]*cnt]++;
        }
    }
    for (i = mn; i <= mx; i++)
        if (in[i] == 1 && vis[i] == 1)ans++;
    printf("%d\n", ans);
    return 0;
}