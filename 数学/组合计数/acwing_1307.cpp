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
显然，对于1≤i≤k+1,f[i]=i+11≤i≤k+1,f[i]=i+1
因为这些情况最多有一只牡牛。

假设有i头牛排队，我们考虑最后一头牛，是牡牛或者不是牡牛。

如果不是牡牛， 那么前i-1头牛任意排队就可以了， 方案为f[i - 1]。
如果是牡牛，那么第i - k 到 i - 1都不能是牡牛，这k个位置已经固定
所以此时的方案数由前面的1~i- k + 1头牛决定 为f[i - k - 1]

所以f[i] = f[i - 1] + f[i - k - 1]
*/

const int m = 5000011, N = 1e5 + 100;
int n, k, f[N];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k + 1; i ++)
        f[i] = i + 1;
    for (int i = k + 2; i <= n; i ++)
        f[i] = (f[i - 1] + f[i - k - 1]) % m;
    printf("%d\n", f[n]);
    return 0;
}
