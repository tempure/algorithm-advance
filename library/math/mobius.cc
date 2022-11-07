/*给定整数a,b和d，有多少正整数对x,y满足x<=a，y<=b且gcd(x,y)=d*/
const int N = 50010;
int primes[N], cnt;
bool st[N];
int mobius[N], sum[N];
//线性筛处理mobius函数
void init(int n) {
    mobius[1] =  1;//0个质因子 0是偶数
    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
            mobius[i] = -1; //质数本身自身质因子
        }
        for (int j = 0; primes[j] <= n / i; j++) {
            int t = primes[j] * i;
            st[t] = true;
            if (i % primes[j] ==  0) {
                mobius[t] = 0; //有至少2个质因子primes[j]
                break;
            }
            //primes[j]是质数，所以t的质因子个数取决于i
            //t比i多了一个primes[j]而已
            mobius[t] = mobius[i] * -1;
        }
    }
    //求mobius前缀和
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + mobius[i];
}
int main() {
    init(N - 1);
    int T; scanf("%d", &T);
    while (T--) {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        a /= d, b /= d;
        ll res = 0;
        int n = min(a, b);
        for (int l = 1, r; l <= n; l = r + 1) {
            //l是每一小段的左端，r是g(x)经典函数
            r = min(n, min(a / (a / l), b / (b / l)));
            res += (sum[r] - sum[l - 1]) * 1ll * (a / l) * (b / l);
        }
        printf("%lld\n", res);
    }
    return 0;
}