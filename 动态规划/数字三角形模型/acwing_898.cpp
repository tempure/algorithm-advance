#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//自上而下顺序DP 需要特判一下循环内的边界

const int N = 510;
const int INF = 1e9;  //处理边界
int a[N][N], f[N][N];
//复杂度 = 状态数量 * 转移所需复杂度 本题为 n^2 * 1

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            cin >> a[i][j];

    memset(f, 0xcf, sizeof f); //将f全部初始化为－无穷

    f[1][1] = a[1][1];

    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= i; j++) {
            f[i][j] = f[i - 1][j] + a[i][j];
            if (j > 1) f[i][j] = a[i][j] + max(f[i - 1][j], f[i - 1][j - 1]);
        }


    int res = -INF;
    for (int i = 1; i <= n; i++)
        res = max(res, f[n][i]);

    cout << res << endl;

    return 0;
}


//从下到上倒序DP  不用考虑边界
//因为对于每一个位置的数字a[i][j]，都有左下a[i+1][j] 以及右下a[i+1][j+1]
//所以倒序不需要特判边界情况, 只需要预处理最后一行的初始状态

#include <iostream>
#include <cstring>
using namespace std;

const int N = 510;
int a[N][N], f[N][N];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            cin >> a[i][j];

    memset(f, 0xcf, sizeof f);

    for (int i = 1; i <= n; i++) f[n][i] = a[n][i];

    for (int i = n - 1; i >= 1; i--)
        for (int j = 1; j <= i; j++)
            f[i][j] = max(f[i + 1][j] + a[i][j], f[i + 1][j + 1] + a[i][j]);

    cout << f[1][1] << endl;

    return 0;
}