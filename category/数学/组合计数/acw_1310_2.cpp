#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//对于边长为n,m的矩形，选三个所有点数量为C((n+1)*(m+1), 3)
//然后减掉所有三点共线的数量即可

/*
分类讨论: 平行坐标轴的 以及不平行的
不平行的先考虑斜率大于0的，然后乘2即可

思路：有很多枚举方法，可以枚举三个点中最左下角的一个，中间的一个，
或者最右上角的一个，或者直接枚举所有直角三角形的斜边，下面代码实现的是最后一种枚举方法

我们枚举所有直角边平行于坐标轴的直角三角形，斜边端点为2个确定点，然后乘此线段上
的整数坐标点即可。

定理：对于边长为i，j的直角边三角形，斜边上的整数点为 gcd(i,) + 1（包括2端点）
*/

ll C(int n) {
    return 1ll * n * (n - 1) * (n - 2) / 6;
}

void solve() {
    int n, m;
    cin >> n >> m;
    n ++, m++;
    ll res = 1ll * C(n * m) - 1ll * n * C(m) - 1ll * m * C(n);

    n --, m --;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            res -= 2ll * (__gcd(i, j) - 1) * (n - i + 1) * (m - j + 1);
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}
