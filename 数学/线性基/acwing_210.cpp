#include <bits/stdc++.h>
using namespace std;

/*
线性基异或第k小:

冷知识:比k小的非负整数有k个
先求出标准基，然后将K-1的二进制表示，表示后的每一位，就是所有基向量的系数
这里的表示都是左边是高位右边是低位的常规表示
基向量的顺序也是左边是1000.最大的基向量，那么系数相乘的结果，自然也是递减的，和二进制数k-1的增减性相同
最后乘上k-1二进制之后的系数异或即可

细节:如果不满秩，那么最小就可以取到0 如果满秩，那么异或就得不到0了
k-1表示二进制的系数，能求出前k-1小，加上0就是前k小
0~k-1恰好是k个，如果不能到0，那只能将k二进制表示了
*/

typedef long long ll;
const int N = 10010;

ll a[N];

int main() {
    int T;
    scanf("%d", &T);
    for (int C = 1; C <= T; C++) {
        printf("Case #%d:\n", C);
        int n; scanf("%d", &n);
        for (int i = 0; i < n ; i++) scanf("%lld", &a[i]);
        //高斯消元
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
        reverse(a, a + k); //二进制系数从第位开始移位的

        int m;
        scanf("%d", &m);
        while (m --) {
            ll x;
            scanf("%lld", &x);
            if (k < n) x --; //非满秩
            if (x >= (1ll << k))puts("-1"); //超出范围 无解
            else {
                ll res = 0;
                for (int i = 0; i < k; i++)
                    if (x >> i & 1)
                        res ^= a[i];
                printf("%lld\n", res);
            }
        }
    }
    return 0;
}