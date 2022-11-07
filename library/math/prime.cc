//试除法判定质数O(sqrt(n))
bool is_prime(int x) {
    if (x < 2) return false;
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0)
            return false;
    return true;
}
//试除法分解质因数
void divide(int x) {
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) x /= i, s ++ ;
            cout << i << ' ' << s << endl;
        }
    if (x > 1) cout << x << ' ' << 1 << endl;
    cout << endl;
}
/*阶乘分解：给定整数 N ，试把阶乘 N! 分解质因数
按照算术基本定理的形式输出分解结果中的 pi 和 ci 即可
1~N中质因子p的个数和为(N/p+N/(p^2)+....)*/
const int N = 1000010;
int primes[N], cnt;
bool st[N];
void init(int n) { //线性筛
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt ++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            st[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}
int main() {
    int n;
    scanf("%d", &n);
    init (n);
    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        int s = 0;
        for (int j = n; j; j /= p) s += j / p;
        printf("%d %d\n", p , s);
    }
    return 0;
}
//埃氏筛(1~n中所有的质数)
int primes[N], cnt; // primes[]存储所有素数
bool st[N];   // st[x]存储x是否被筛掉
void get_primes(int n) {
    for (int i = 2; i <= n; i ++ ) {
        if (st[i]) continue;
        primes[cnt ++ ] = i;//cnt记录素数个数
        for (int j = i + i; j <= n; j += i)
            st[j] = true;
    }
}
//线性筛(筛出1~n中所有的质数)
int primes[N], cnt; // primes[]存储所有素数
bool st[N]; // st[x]存储x是否被筛掉
void get_primes(int n) {
    for (int i = 2; i <= n; i ++ ) {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; j ++ ) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
/*例题:给出一个闭区间,求出区间内相邻最近和最远的质数对
如果存在多组，输出第一组 区间长度最多1e6 范围INT_MAX*/
//左右端点是int范围 不能线性筛一次 会超时
//而且线性筛不能只筛一个区间 做不到
//切入点在于相邻质数区间长度不会超过1e6
//处理所有数的质因子,sqrt(INT_MAX)<50000处理50000内的质数
//然后用埃氏筛筛掉所有[2~sqrt(R)]的合数,剩下的就是区间内所有的质数,逐个相邻比较即可
const int N = 1000010; //区间长度
int primes[N], cnt;
bool v[N];
void prime(int n) { //线性筛
    memset(v, 0, sizeof v);
    for (int i = 2; i <= n; i++) {
        if (!v[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}
int main() {
    int l, r;
    while (cin >> l >> r) {
        prime(50000);
        memset(v, 0, sizeof v);
        for (int i = 0; i < cnt; i++) {
            ll p = primes[i]; //质数的倍数可能会爆掉int
            // L / P 上取整 * p 就是第一个大于L的p的倍数
            //上取整可以ceil函数 也可以 (L + p - 1) / p
            //计算出第一个倍数j之后然后每次+p 取max是因为最少要二倍的倍数
            for (ll j = max(p * 2, (l + p - 1) / p * p); j <= r; j += p)
                v[j - l] = true;
        }
        cnt = 0;
        for (int i = 0; i <= r - l; i++)
            //过滤掉1 不是素数的特殊情况
            //复用primes数组 此时保存的是区间内的素数
            if (!v[i] && i + l >= 2) primes[cnt++] = i + l;
        if (cnt < 2) puts("There are no adjacent primes."); //不足2个素数 就无解
        else {
            int minp = 0, maxp = 0; //枚举所有的相邻素数
            for (int i = 0; i + 1 < cnt; i++) {
                int d = primes[i + 1] - primes[i];
                if (d < primes[minp + 1] - primes[minp])minp = i;
                if (d > primes[maxp + 1] - primes[maxp])maxp = i;
            }
            printf("%d,%d are closest, %d,%d are most distant.\n", primes[minp], primes[minp + 1], primes[maxp], primes[maxp + 1]);
        }
    }
    return 0;
}