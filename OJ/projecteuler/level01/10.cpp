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
//head

const int N = 2e6;
int primes[N], v[N];


int euler(int n) { //线性筛法 在 N = 1e7 级别的时候 比埃氏筛快一倍
    memset(v, 0, sizeof v);
    int cnt = 0;
    for (int i = 2; i <= n ; i++) {
        if (!v[i]) primes[cnt ++] = i; //i还没有被筛过 说明为质数
        for (int j = 0; primes[j] <= n / i; j++) { // 枚举所有比i小的质数
            v[primes[j] * i] = 1;
            if (i % primes[j] == 0) break; //如果primes[j] 也是i的质因子,一定是i的最小质因子，因为primes数组单调
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    euler(N);
    ll sum = 0;
    for (int i = 0; i < N; i++)
        sum += primes[i];

    cout << sum << endl;

    return 0;
}