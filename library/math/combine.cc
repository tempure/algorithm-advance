/*递推法 O(n^2)
给n组询问每组询问两个整数a,b;输出C(a,b)mod(1e9+7)的值
1 <= n <= 10000, 1 <= b <= a <= 2000*/
const int N = 2010, mod = 1e9 + 7;
int n;
int c[N][N];
void init() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
            if (!j) c[i][j] = 1;
            else c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
}
int main() {
    cin >> n; int a, b;
    init();
    while (n --) {
        cin >> a >> b;
        cout << c[a][b] << endl;
    }
    return 0;
}
/*预处理逆元 1 <= b <= a <= 1e5
1e9 + 7 是质数  复杂度 n * log n*/
const int N = 100010, mod = 1e9 + 7;
int fact[N], infact[N];  //阶乘和阶乘逆元 模 mod的值 预处理
ll qmi(int a, int k, int p) {
    int res = 1;
    while (k) {
        if (k & 1) res = (ll)res * a % p;
        a = (ll)a * a % p;
        k >>= 1;
    }
    return res;
}
int main() {
    int n; int a, b;
    cin >> n;
    fact[0] = infact[0] = 1;
    for (int i = 1; i <= N; i++) { //预处理
        fact[i] = 1ll * i * fact[i - 1] % mod;
        infact[i] = 1ll * infact[i - 1] * qmi(i, mod - 2, mod) % mod;
    }
    while (n -- ) {
        cin >> a >> b;
        cout << (1ll * fact[a] * infact[b]  % mod * infact[a - b]) % mod << endl;
    }
    return 0;
}
/*lucas定理求c(m,n)mod p,复杂度 O(p*logm)
1<=b<=a<=1e18,1<=p<=1e5,p是质数
可以预处理阶乘和逆元达到O(p+logm)*/
int p;
ll qmi(ll a, ll b) {
    ll res = 1; a %= p;
    while (b) {
        if (b & 1) res = res * a % p;
        b >>= 1;
        a = a * a % p;

    }
    return res;
}
int c(int a, int b) {
    //逆元求组合数
    if (a < b) return 0;
    int down = 1, up = 1;
    for (int i = a, j = 1; j <= b; i--, j++) {
        down = (ll)down * j % p;
        up = (ll)up * i % p;
    }
    return (ll)up * qmi(down, p - 2) % p;
}
ll lucas(ll a, ll b) { //递归求lucas
    if (a < p && b < p) return c(a, b);
    return c(a % p, b % p) * lucas(a / p, b / p) % p;
}
int main() {
    int n; cin >> n;
    ll a, b;
    while (n--) {
        cin >> a >> b >> p;
        cout << lucas(a, b) << endl;
    }
    return 0;
}
/*当需要求出组合数的真实值，而非对某个数的余数时，用分解质因数
    1. 筛法求出范围内的所有质数
    2. 通过 C(a, b) = a! / b! / (a - b)!求出每个质因子的次数
       n! 中p的次数是 n / p + n / p^2 + n / p^3 + ...
    3. 用高精度乘法将所有质因子相乘*/
const int N = 5010;
int primes[N], cnt;
int sum[N];
bool st[N];
int p;
void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}
int get(int n) { //求出n!中包含的p的个数
    int res = 0;
    while (n) {
        res += n / p;
        n /= p;
    }
    return res;
}
ll qmi(int a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res *= a;
        b >>= 1;
        a = a * a;
    }
    return res;
}
//高精度乘法
vector<int> mul(vector<int> &a, int b) {
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); i++) {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) {
        c.push_back(t % 10);
        t /= 10;
    }
    return c;
}
int main() {
    int a, b; cin >> a >> b;
    get_primes(a);  //求出1 ~ a 中所有质数
    for (int i = 0; i < cnt; i++) {
        p = primes[i];
        sum[i] = get(a) - get(b) - get(a - b); //p的次数,0就相当于不减
    }
    vector<int> res;  //高精度乘法
    res.push_back(1);
    for (int i = 0; i < cnt; i++)
        res = mul(res, qmi(primes[i], sum[i]));
    //输出答案
    for (int i = res.size() - 1 ; i >= 0; i--) cout << res[i];
    cout << endl;
    return 0;
}
/*卡特兰数：Cat(n)=c(2n,n)/(n+1)对质数取模
给定n个0和n个1，按照某种顺序排成长度为2n的序列，求排列成的所有序列中满足任意前缀序列中0的个数都不少于1的个数的序列有多少个。答案对1e9+7取模*/
const int p = 1e9 + 7;
typedef long long ll;
ll qmi(ll a, ll b, int p) {
    ll res = 1; a %= p;
    while (b) {
        if (b & 1) res = res * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return res;
}
int c(int a, int b) {
    // return res;
    if (a < b) return 0; //不管为了正确性还是时间来说都请加上这句话
    int down = 1, up = 1;
    for (int i = a, j = 1; j <= b; i--, j++) {
        down = (ll)down * j % p;
        up = (ll)up * i % p;
    }
    return (ll)up * qmi(down, p - 2) % p;
}
ll lucas(ll a, ll b) { //递归求lucas
    if (a < p && b < p) return c(a, b);
    return c(a % p, b % p) * lucas(a / p, b / p) % p;
}
int main() {
    int n; cin >> n;
    //除法取模，计算逆元，n+1<p，所以和p互质
    cout << lucas(2 * n, n) % p * qmi(n + 1, p - 2, p) % p << endl;
    return 0;
}
/*A(0,0) 点出发，只能向正右方或者正上方行走，且不能经过y=x左上方的点，即任何途径的点 (x,y) 都要满足 x≥y，问到达 B(n,m) 有多少种走法。*/
/*找出(n,m)关于y=x+1的对称点(m−1,n+1)
每一条非法路径都对应一条(0,0)到(m−1,n+1)的路径，因此合法路径=总路径数-非法路径
答案就是C(n + m, n) - C(n + m, m - 1)
但是此题不是组合数取模，而且N上界5000，需要分解质因子+高精度乘法*/
const int N = 100010; //高精度位数
int primes[N], cnt;
bool st[N]; //筛质数筛到10000 组合数最大n+m
int a[N], b[N];
void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}
int get(int n, int p) { //求出n!中包含的p的个数
    int res = 0;
    while (n) {
        res += n / p;
        n /= p;
    }
    return res;
}
void mul(int r[], int &len, int x) { //高精度乘法
    int t = 0;
    for (int i = 0; i < len; i++) {
        t += r[i] * x;
        r[i] = t % 10;
        t /= 10;

    }
    while (t) r[len++] = t % 10, t /= 10;
}
void sub(int a[], int al, int b[], int bl) { //高精度减法
    for (int i = 0, t = 0; i < al; i++) {
        a[i] -= t + b[i];
        if (a[i] < 0) a[i] += 10, t = 1;
        else t = 0;
    }
}
int C(int x, int y, int r[N]) {
    int len = 1;
    r[0] = 1;
    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        int s = get(x, p) - get(y, p) - get(x - y, p);
        while (s --) mul(r, len, p); //直接边求边乘
    }
    return len;
}
int main() {
    get_primes(N - 1);
    int n, m;
    cin >> n >> m;
    int al = C(n + m, n, a); //结果放入a中 al记录高精度结果的长度 便于减法高精度
    int bl = C(n + m, m - 1, b);
    sub(a, al, b, bl);
    int k = al - 1;
    while (!a[k] && k > 0) k--;
    while (k >= 0) printf("%d", a[k --]);
    return 0;
}
/*卡特兰数，对非质数取模 1<=n<=1e6,1<=p<=1e9 模数是p
分解质因数+快速幂取模+组合数减法C(2n,n) - C(2n,n-1)
阶乘分解质因数复杂度N*loglogN 该算法的复杂度不会超过O(N)*/
const int N = 2e6 + 10;
ll p; //模数
int primes[N], cnt;
bool st[N]; int n;
void init(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0)  break;
        }
    }
}
int get(int n, int p) { //求出n!中包含的p的个数
    int res = 0;
    while (n) {
        res += n / p;
        n /= p;
    }
    return res;
}
ll C(int x, int y) {
    ll res = 1;
    for (int i = 0; i < cnt; i++) {
        int pi = primes[i];
        int s = get(x, pi) - get(y, pi) - get(x - y, pi);
        while (s --) res  = res * pi % p; //一边求一边乘不用快速幂
    }
    return res;
}
int main() {
    scanf("%d", &n);
    init(n * 2);
    scanf("%d", &p);
    cout << ((C(n * 2, n) -  C(n * 2, n - 1)) % p + p) % p << endl;
    return 0;
}