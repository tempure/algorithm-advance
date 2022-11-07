/*给定n个整数（可能重复）从中挑选任意个整数求最大异或和
1<=n<=1e5,0<=Si<=2^63−1,只需让高斯消元后的所有基向量异或*/
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
/*N个整数构成的序列选一些（至少一个）进行异或,所有不同的结果中第k小的是多少*/
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
        reverse(a, a + k); //二进制系数从最低开始移位的所以要逆过来，最小的先算
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
                    if (x >> i & 1) res ^= a[i];
                printf("%lld\n", res);
            }
        }
    }
    return 0;
}