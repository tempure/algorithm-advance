#include <bits/stdc++.h>
using namespace std;

/*
高斯消元+线性基性质：
由于是异或运算，将每个数都看成64位二进制放在矩阵中
先求所有向量的一组基，高斯消元即可

线性基能张成的空间在这里的运算法则被定义为异或
显然所有基向量异或起来得到最大，选取几个维度的向量异或能得到最小
也就是说一个基能异或出该向量空间的所有取值

最大值只需要让高斯消元后的所有基向量异或即可
*/

typedef long long ll;
const int N = 100010;

int n;
ll a[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);

    int k = 0; //当前消元到哪一行
    //枚举二进制每一位高斯消元
    for (int i = 62; i >= 0; i--) {
        for (int j = k; j < n; j++)
            if (a[j] >> i & 1) {
                swap(a[j], a[k]); //换到最上边来消该列
                break;
            }
        if (!(a[k] >> i & 1)) continue; //当前列全是0 直接下一列
        for (int j = 0; j < n; j++) //消去该列所有1
            if (j != k && (a[j] >> i & 1))
                a[j] ^= a[k];
        k ++;
        if (k == n) break;
    }

    ll res = 0;
    for (int i = 0; i < k; i++) res ^= a[i];
    printf("%lld\n", res);

    return 0;
}