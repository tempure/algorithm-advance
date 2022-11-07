/*给定一个整数n和m个不同的质数p1,p2,…,pm
求1~n中能被p1,p2,…,pm中的至少一个数整除的整数有多少*/
//集合S[i]:1到n中能被i整除的数的集合 然后 一共有m个集合 处理一个集合需要m次 最后复杂度O(2 ^ m * m)
//容斥原理 + 二进制状压
const int N = 20;
int n, m;
int p[N];
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) cin >> p[i];
    int res = 0;
    for (int i = 1; i < 1 << m; i++) {
        int t = 1, cnt = 0;
        for (int j = 0; j < m; j++)
            if (i >> j & 1) {
                cnt ++;
                if (1ll * t * p[j] > n) {
                    t = -1;
                    break;
                }
                t *= p[j];
            }
        if (t != -1) {
            if (cnt & 1) res += n / t;
            else res -= n / t;
        }
    }
    cout << res << endl;
    return 0;
}
//多重集组合数质数取模 n堆取m个的不同集合数量
//对于组合数C(a,b)计算的次数由b大小决定，此题N很小，直接用组合数定义计算即可
const int N = 20;
const ll mod = 1e9 + 7;
ll a[N];
int down = 1; //组合数的不变部分
int qmi(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return res;
}
int C(ll a, ll b) { //逆元求组合数
    if (a < b) return 0;
    int up = 1;
    for (ll i = a; i > a - b; i--) up = 1ll * i % mod * up % mod;
    return 1ll * up * down % mod;
}
int calc(ll n, ll m) { //参数ll还是int由题而定
    for (int j = 1; j <= n - 1; j++) down = 1ll * j * down % mod;
    down = qmi(down, mod - 2, mod);
    int res = 0; //答案
    //容斥原理一共由1<<N项 直接枚举即可
    for (int i = 0; i  < 1 << n; i++) {
        ll aa = m + n - 1, b = n - 1;
        int sign = 1; //项的正负号
        for (int j = 0; j < n; j++)
            if (i >> j & 1) {
                sign *= -1;
                aa -= a[j] + 1;
            }
        res = (res + C(aa, b) * sign) % mod;
    }
    return (res + mod) % mod;
}
int main() {
    ll n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    //n堆取m个组成的不同集合数量
    cout << calc(n , m) << endl;
    return 0;
}