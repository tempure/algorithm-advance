#include <bits/stdc++.h>
using namespace std;

/*
polya定理可以公式算出每个置换的不动点的数量，前提是每个置换都互相独立
步骤是，考虑当前置换能分解成的所有循环置换，简称循环。
对于每个循环，就以染色为例，环上每个点都可以染m种颜色,当前置换可以被分解为k个循环
由于各个循环独立，乘法原理，该置换的不动点数量为m^k。

然后就是Burnside引理，所有的方案数是所有置换不动点数量的平均值
对于每个置换中各个循环不独立的情况，不能使用polya定理，只能用Burnside引理

此题有旋转和翻转2种置换： 设环上有n个点
1.旋转：假设旋转次数k=0,1,2...n-1同余计算出有gcd(n,k)种循环，每种旋转都是一种置换，一共n种置换
2.翻转：分n为奇数和偶数分别讨论对称轴的置换，然后求出循环次数 奇数和偶数都有n种置换

所以一共有2*n种置换，由Burnside引理求出所有置换不动点的平均值即可
*/

typedef long long ll;

int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main() {
    int m, n;
    while (cin >> m >> n, m || n) {
        ll res = 0;
        for (int i = 0; i < n; i++)
            res += power(m, __gcd(n, i)); //旋转

        //翻转
        if (n % 2) res += n * power(m, (n + 1) / 2); //奇数
        else
            res += n / 2 * (power(m, n / 2 + 1) + power(m, n / 2)); //偶数
        cout << res / n / 2 << endl;
    }

    return 0;
}