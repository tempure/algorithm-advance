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
const ll mod = 100003;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head

//容斥原理 补集思想
//所有的方案有m^n, 每个相邻的宗教都不相同的方案有m*(m-1)*(m-1)*.... = m*((m - 1) ^ (n - 1))

int main() {
    ll m, n;
    cin >> m >> n;
    //注意快速幂之后返回的答案时取模之后的，所以有可能相减是负数 
    cout << ((powmod(m , n) - (ll)m * powmod(m - 1, n - 1)) % mod + mod) % mod << endl;

    return 0;
}
