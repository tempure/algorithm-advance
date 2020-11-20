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

//也就是求1~N中约数个数最多的最小的数
//反素数条件：必定是连续的最小的质数的乘积，而且幂次递减
//题目最大范围2e9 那么次幂最高不会超过30 而且质因子最大不会超过29
//直接dfs即可

int primes[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
int maxd, number;  //约数个数是maxd 数本身是number
int n;

//枚举到第几个质数，上一个质数的次数，乘积是多少，约数个数
void dfs(int u, int last, int p, int s) {
    //约数个数大于，或者等于而且乘积小于number 就更新
    if (s > maxd || s == maxd && p < number) {
        maxd = s;
        number = p;
    }

    if (u == 9)  return ;
    for (int i = 1; i <= last; i++) {
        if ((ll)p * primes[u] > n) break;
        p *= primes[u];
        dfs(u + 1, i, p, s * (i + 1));
    }
}

int main() {
    cin >> n;
    dfs(0, 30, 1, 1);

    cout << number << endl;

    return 0;
}

