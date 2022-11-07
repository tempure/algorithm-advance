#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006, INF = 0x3f3f3f3f, P = 1000000007;
int n, m, a[N], b[N], c[N], f[N][N], num;

//HDOJ5542
//树状数组优化DP
//细节看蓝书 讲的很清楚，就是每次状态转移只会多一个新插入的值
//不用每次都遍历O(N)查询，改为O(logN)
//复杂度O(N^2*logN)

void add(int x, int y) {
    while (x <= n + 1) {
        c[x] = (c[x] + y) % P;
        x += x & -x;
    }
}

int ask(int x) {
    int ans = 0;
    while (x) {
        ans = (ans + c[x]) % P;
        x -= x & -x;
    }
    return ans;
}

void The_Battle_of_Chibi() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    memcpy(b, a, sizeof(b));
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b + 1;
    a[0] = f[0][0] = 1;
    for (int i = 1; i <= m; i++) {
        memset(c, 0, sizeof(c)); //每次清空c，我的理解是，状态f[i][]只依赖上一个f[i-1][]？
        add(1, f[i - 1][0]);
        for (int j = 1; j <= n; j++) {
            f[i][j] = ask(a[j] - 1); // < a[j] 因为是严格递增
            add(a[j], f[i - 1][j]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = (ans + f[m][i]) % P;
    printf("Case #%d: %d\n", ++num, ans);
}

int main() {
    int t;
    cin >> t;
    while (t--) The_Battle_of_Chibi();
    return 0;
}

// 作者：lydrainbowcat
// 链接：https://www.acwing.com/activity/content/code/content/594739/
// 来源：AcWing
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。