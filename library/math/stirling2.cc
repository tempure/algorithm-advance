/*斯特林子集数{n,k}表示将n个两两不同的元素划分为k个非空子集的方案数
给定 n 和 k求方案数对1e9+7取模,1<=k<=n<=1000*/
/*f[n][k]表示将n个不同元素划分为k个非空子集
和第一类斯特林数不同的就是第二类不需要排列，只需要划分
同样O(N^2)递推：f[n][k] = f[n-1][k-1] + k*f[n-1][k]*/
typedef long long ll;
const int N = 1010, mod = 1e9 + 7;
int n, k;
int f[N][N];
int main() {
    scanf("%d%d", &n, &k);
    f[0][0] = 1; //规定的边界
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++)
            f[i][j] = (f[i - 1][j - 1] + (ll)j * f[i - 1][j]) % mod;
    printf("%d", f[n][k]);
    return 0;
}