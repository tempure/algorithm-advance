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

//化简式子得：y = (n!)^2 / (x - n!)
//x,y都是正整数 ,那么也就是求的是x取什么值可以让分子整除分母
//易得x和y都是 > n! 不然题目的式子不能成立
//转化为 (n! ^ 2) 的约数个数
//由前面阶乘分解，可以求出所有质因子分解的结果，那么约数的个数 最终就是(2c2+1)*(2c2+1)*....*(2ck+1)

//线性筛一遍 然后 N/p + N/p^2 +.....可求出M!一个质因子p出现的次数

const int N = 1000010;
int primes[N], cnt;
bool st[N];
int n;

void init(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    scanf("%d", &n);
    init(n);

    int res = 1;
    for (int i = 0; i < cnt; i++) { //求出所有质因子p的幂次
        int p = primes[i];
        int s = 0;
        for (int j = n; j; j /= p) s += j / p;
        res = (ll)res * (2 * s + 1) % mod;
    }

    printf("%d\n", res);
    return 0;
}


