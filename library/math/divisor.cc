/*倍数法求(1~N)每个数正约数集合O(N*logN)*/
const int N = 10000;
vector<int> factor[N];
int n;
void calc(int n) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n / i; j++)
            factor[i * j].push_back(i);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < factor[i].size(); j++)
            printf("%d ", factor[i][j]);
        puts("");
    }
}
/*试除法求一个数的正约数集合O(sqrt(n))*/
vector<int> get_divisors(int x) {
    vector<int> res;
    for (int i = 1; i <= x / i; i ++ )
        if (x % i == 0) {
            res.push_back(i);
            if (i != x / i) res.push_back(x / i);
        }
    sort(res.begin(), res.end());
    return res;
}
/*约数个数：
如果 N = p1^c1 * p2^c2 * ... *pk^ck
约数个数：(c1 + 1) * (c2 + 1) * ... * (ck + 1)
给定n个正整数ai，输出这些数的乘积的约数个数，答案对1e9+7取模*/
const int mod = 1e9 + 7;
//将每一个ai分解 然后把指数相加就是最后的乘积的质因数分解结果
//约数个数就是指数加1再相乘即可
int main() {
    int n; cin >> n; int x;
    unordered_map<int, int> primes;
    while (n --) {
        cin >> x;
        for (int i = 2; i <= x / i; i++)
            while (x % i == 0) {
                x /= i;
                primes[i] ++;
            }

        if (x > 1) primes[x] ++;
    }
    ll res  = 1;
    for (auto prime : primes) res = res * (prime.second + 1) % mod;
    cout << res << endl;
    return 0;
}
/*给定n个正整数ai求这些数的乘积的约数之和对1e9+7取模
(p1^0+p1^1+...+p1^c1)*...* (pk^0 + pk^1 + ... + pk^ck)*/
typedef long long ll;
const int mod = 1e9 + 7;
int main() {
    unordered_map<int , int > primes;
    int n, x; cin >> n;
    while (n --) {
        cin >> x;
        for (int i = 2; i <= x / i; i++)
            while (x % i == 0) {
                x /= i;
                primes[i] ++;
            }
        if (x > 1) primes[x] ++;
    }
    ll res = 1;
    for (auto prime : primes) {
        int p = prime.first,  a = prime.second;
        ll t = 1;  //等比数列求和 递推法
        while (a--) t = (t * p + 1) % mod;
        res  = res * t % mod;
    }
    cout << res << endl;
    return 0;
}