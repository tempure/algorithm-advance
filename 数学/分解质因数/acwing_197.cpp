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


//性质:N!分解之后的每个质因子都不会超过N，反证法:
//一个数如果是质数，那么分解质因子只有本身，
//如果一个数是偶数，那么它的所有质因子都不会超过自己，因为如果有一个超过自己的
//那么乘积就会大于本身，矛盾
//所以对于1~N的每个数，所有的质因子 都不会超过自己，那么N!的质因子也就不会超过N

//先筛一遍2~N中所有的质数
//答案：N!中质因子p的个数为 N / p + N / p^2 + ... + N / p^(logp(N))

const int N = 1000010;

int primes[N], cnt;
bool st[N];

void init(int n) {
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