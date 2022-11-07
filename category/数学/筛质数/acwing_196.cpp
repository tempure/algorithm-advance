#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head

//范围是int范围 不能线性筛一次 会超时
//而且线性筛不能只筛一个区间 做不到
//切入点在于相邻质数区间长度不会超过1e6

//处理所有数的质因子，sqrt(INT_MAX) < 50000 处理50000以内的质数
//然后用埃氏筛筛掉所有[2~sqrt(R)]的合数 那么剩下的就是区间内所有的质数 然后逐个相邻比较即可

const int N = 1000010; //区间长度

int primes[N], cnt;
bool v[N];

void prime(int n) {
    memset(v, 0, sizeof v); //注意模板的这个一定要写 对于多组测试数据
    for (int i = 2; i <= n; i++) {
        if (!v[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    // prime(50000);

    int l, r;
    while (cin >> l >> r) {
        prime(50000);

        //复用v，primes数组
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
            if (!v[i] && i + l >= 2) primes[cnt++] = i + l; //复用primes数组 此时保存的是区间内的素数

        if (cnt < 2) puts("There are no adjacent primes."); //不足2个素数 就无解
        else {
            int minp = 0, maxp = 0; //枚举所有的相邻素数
            for (int i = 0; i + 1 < cnt; i++) {
                int d = primes[i + 1] - primes[i];
                if (d < primes[minp + 1] - primes[minp]) minp = i;
                if (d > primes[maxp + 1] - primes[maxp]) maxp = i;
            }
            printf("%d,%d are closest, %d,%d are most distant.\n", primes[minp], primes[minp + 1], primes[maxp], primes[maxp + 1]);
        }

    }

    return 0;
}
