#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

/*
移动一个行内的元素时候，会对列产生影响，但是不会对行之间产生影响
所以行列能否有解是完全独立的，可以分开求解，分别判断

将一列或者一行的某些位置交换邻行的元素，不同的数量就可以实现不同的加减，等价于经典的均分纸牌，但是是环形的
环形需要推公式，最后找出递推式结果的中位数就是最优解
*/

const int N = 1e5 + 10;
ll row[N], col[N], c[N];
ll n, m , t;

ll calc(ll a[], ll n) {
    for (int i = 2; i <= n; i++) {
        a[i] -= a[0] / n; //avg
        c[i] = c[i - 1] + a[i];
    }
    sort(c + 1, c + 1 + n);
    ll mid = n + 1 >> 1;

    ll ans = 0;
    for (int i = 1; i <= n; i++) ans += abs(c[i] - c[mid]); //中位数 最优解
    return ans;
}


int main() {
    cin >> n >> m >> t;

    while (t --) {
        int x, y;
        cin >> x >> y;
        row[x] ++, col[y] ++;
    }

    for (int i =  1; i <= n; i++) row[0] += row[i];
    for (int i = 1; i <= n; i++) col[0] += col[i];

    int flag1 = row[0] % n, flag2 = col[0] % m; //行列的和能否整除，判断是否有解

    if (!flag1 && !flag2) cout << "both " << calc(row, n) + calc(col, m);
    else if (!flag1) cout << "row " << calc(row, n);
    else if (!flag2) cout << "column " << calc(col, m);
    else cout << "impossible";

    return 0;
}