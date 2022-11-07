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

const int N = 100010;
bool v[N];
int primes[N];
int cnt;
int n;

//任何一个大于1的自然数N，如果N不为质数，那么N可以唯一分解为有限个质数的乘积。
//在图中a是b的质因子 那就a向b连边 显然只会质数向偶数连边 要求一条边的两个端点不能同色
//那么就是二分图了 质数在左边 合数在右边 需要的颜色种类 <=2
//把 价格 为质数的珠宝涂成1颜色，把 价格 不是质数的珠宝涂成2颜色，所以只需要两种颜色即可。

void prime(int n) {
    memset(v, 0, sizeof v);
    for (int i = 2; i <= n; i++) {
        if (!v[i]) primes[cnt ++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    scanf("%d", &n);

    //特判n == 1 和n == 2的情况
    if (n == 1) {
        puts("1");
        puts("1");
        return 0;
    }

    //n == 2就是 2，3互质只需要一种颜色
    if (n == 2) {
        puts("1");
        printf("1 1\n");
        return 0;
    }

    prime(n + 1);
    puts("2");
    for (int i = 2; i <= n + 1; i++)
        if (!v[i]) printf("1 ");
        else printf("2 ");

    return 0;
}