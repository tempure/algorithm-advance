#include <bits/stdc++.h>
using namespace std;
using ll = long long;


/*
该矩阵的本质:
一共有63列，每一列都有n个数，意思就是对于当前列代表的二进制位，这n个数的该二进制位的情况
最后高斯消元完毕后，每列唯一存在的元素就是基的一个元素, 每列只需要一个元素,来担任该二进制位为1的元素
注意在最后的xor求答案的过程中，循环到k还是n都可以，因为此时就是消元最后的那些元素了

为什么从62位后到前开始扫：
因为从高往低位扫，若当前扫到第i位，意味着可以保证答案的第i位为 1，且后面没有机会改变第i位。

为什么线性基xor就能的到最大值的正确性：https://oi-wiki.org/math/basis/
*/

//================old code=======================//

const int N = 100010;
int n;
ll a[N];

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    int k = 0;
    for (int i = 62; i >= 0; i--) {
        for (int j = k; j < n; j++)
            if (a[j] >> i & 1) {
                swap(a[j], a[k]);
                break;
            }
        if (!(a[k] >> i & 1)) continue;
        for (int j = 0; j < n; j++)
            if (j != k && (a[j] >> i & 1))
                a[j] ^= a[k];
        k++;
        if (k == n) break;
    }
    ll res = 0;
    for (int i = 0; i < k; i++) res ^= a[i]; //此时可以循环到n，也能AC
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}