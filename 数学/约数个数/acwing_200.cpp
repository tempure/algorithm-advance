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

//lcm(x, b) = b1;那么说明x是b的约数 只要求出b的所有约数 就可以求出x了 同时判断是否满足gcd的关系即可
//试除法质因子分解，复杂度是和素数定理相关的O(n/ln(n)) 然后dfs搜出所有的约数
//求约数的暴力试除法sqrt(n)会超时 所以要用质因子分解+dfs求约数

const int N = 50010; //筛出sqrt(2e9)范围内的素数
int primes[N], cnt; //cnt是质数数量
bool st[N];
int fcnt; //质因子数量
int dividor[N], dcnt; //所有的约数 以及个数

struct Factor {
    int p, s;
} factor[N]; //存储质因子 以及幂次数

void init(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] * i <= n / i; j++) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

//枚举的质因子 以及约数 本质就是在枚举所有质因子的不同次幂乘积的组合
void dfs(int u, int p) {
    if (u == fcnt) {
        dividor[dcnt ++] = p;
        return;
    }

    for (int i = 0; i <= factor[u].s; i++) {
        dfs(u + 1, p);
        p *= factor[u].p;
    }
}

int main() {
    init(N - 1);
    int n;
    cin >> n;
    while (n --) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        fcnt = 0;

        int t = d;  //先质因子 分解d
        for (int i = 0; primes[i] <= t / primes[i]; i++) { //枚举到 sqrt(n) 级别
            int p = primes[i];
            if (t % p == 0) {
                int s = 0;
                while (t % p == 0) t /= p, s++;
                factor[fcnt ++] = {p, s};
            }
        }

        if (t > 1) factor[fcnt++] = {t, 1}; //本身就是素数
        dcnt = 0;
        dfs(0, 1);
        int res = 0;
        for (int i = 0; i < dcnt; i++) {
            int x = dividor[i];
            if (gcd(a, x) == b && (ll)c / gcd(c, x) * x == d) res ++;
        }

        cout << res << endl;
    }

    return 0;
}