//最短编辑距离

/*
状态表示 dp[i][j]
集合 ： 所有吧a中的前i个字母 变成 b中前j个字母的集合的操作集合
属性 ： 所有操作中操作次数最少的方案的操作数

状态计算
状态划分 以对a中的第i个字母操作不同划分

在该字母之后添加
添加一个字母之后变得相同，说明没有添加前a的前i个已经和b的前j-1个已经相同
即 ： dp[i][j] = dp[i][j-1] + 1

删除该字母
删除该字母之后变得相同，说明没有删除前a中前i-1已经和b的前j个已经相同
即 ： dp[i][j] = dp[i-1][j] + 1

替换该字母
替换说明对应结尾字母不同，则看倒数第二个
即： dp[i][j] = dp[i-1][j-1] + 1

啥也不做
对应结尾字母相同，直接比较倒数第二个
即： dp[i][j] = dp[i-1][j-1]
*/

#include <iostream>
using namespace std;

const int N = 1010;
char a[N], b[N];
int f[N][N];

int main() {
    int n, m;
    cin >> n >> a + 1;
    cin >> m >> b + 1;

    for (int i = 1; i <= m; i++) f[0][i] = i;
    for (int i = 1; i <= n; i++) f[i][0] = i;


    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            f[i][j] = min(f[i - 1][j] + 1, f[i][j - 1] + 1);
            if (a[i] == b[j]) f[i][j] = min(f[i][j], f[i - 1][j - 1]);
            else f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
        }

    cout << f[n][m] << endl;


    return 0;
}