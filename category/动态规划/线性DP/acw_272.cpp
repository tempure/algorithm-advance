#include <bits/stdc++.h>
using namespace std;

//LCIS https://www.acwing.com/video/1979/
//重点在于状态转移优化的思路，每次最优决策的候选集和只会新加入一个 b[j-1]
//同时 b[j] == a[i]，那么比较的元素直接替换为 a[i], 可以直接省略一维循环
//lyd 写法和 yxc 思路不一样, 此代码为 lyd 写法

const int N =  3010;
int a[N], b[N], f[N][N];
int n;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)cin >> a[i];
    for (int i = 1; i <= n; i++)cin >> b[i];
    b[0] = -(1 << 30);
    for (int i = 1; i <= n; i++) f[i][0] = 0;

    for (int i = 1; i <= n; i++) {
        int S = 0;
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i - 1][j]; //a[i] != b[j], 同时要b[j] 结尾，选b[j]

            // int k = j-1; //最优决策待加入，判断是否可加入
            if (b[j - 1] < a[i]) S = max(S, f[i - 1][j - 1] + 1);
            if (a[i] == b[j]) f[i][j] = max(f[i][j], S); //只有 a[i]==b[j]才会更新状态
        }
    }
    int ans = 0;
    for (int j = 1; j <= n; j++) ans = max(ans, f[n][j]);
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}