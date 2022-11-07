/*BZOJ3028:推导出的生成函数f(x)=x * 1/((1-x)^4)
母问题:给出n种物品，每个物品无限个，求选出k个物品的方案数
用隔板法求出组合数系数为C(n+k-1, n-1), 母问题的生成函数为1((1-x)^n)
所以对于此题的生成函数，f(x)的系数就是C(n+2,3)=(n+2)(n+1)n / 6
先算出n%p的值,对于高精度数取模，用秦九韶算法，从高位到低位：
假设已经算出前i位组成的数mod p的值为n，那么加上i+1位后的数 mod p
结果就是 (n * 10 + s[i+1]) % p*/
typedef long long ll;
const int N =  510, P = 10007;
char s[N]; //高精度整数
int main() {
    scanf("%s", s);
    ll n = 0;
    for (int i = 0; s[i]; i++)
        n = (n * 10 + s[i] - '0') % P;
    printf("%lld", n * (n + 1) * (n + 2) / 6 % P);
    return 0;
}