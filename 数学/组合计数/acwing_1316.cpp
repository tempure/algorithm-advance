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

/*
思路：对于1~2n从小到大枚举每个数是放在奇数项的位置还是偶数项的位置
对于当前已经枚举的序列，需要满足奇数项位置的数的数量>=偶数项位置的数的个数
反证法:如果奇数项个数小于偶数项，那么前面必定有奇数位置是空的，但是枚举的过程是递增
挨个数依次枚举的，所以最后一个枚举的偶数位置后边的数，就要放在前面，破坏递增，矛盾

对于挨个枚举的数，如果当前数放在奇数位置，那就标为1，放在偶数位置就标为0，问题转换为每个前缀需要1的个数>=0的个数
但是此题的模数P不一定是质数，也就是不能用逆元，所以需要用组合数的减法，也就是推到卡特兰数的上一步结果：C(2n,n) - C(2n,n-1)
不是质数模数就不能lucas，而且n是1e6，那么只能分解质因数+快速幂取模+组合数减法
*/

const int N = 2e6 + 10;
ll p; //模数
int primes[N], cnt;
bool st[N];
int n;

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
        while (s --) res  = res * pi % p; //一边求一边乘，不用写快速幂了
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