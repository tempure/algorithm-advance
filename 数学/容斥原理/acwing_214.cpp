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

//多重集组合数 n堆取m个的不同集合数量
//对于组合数C(a,b)计算的次数由b大小决定，此题N很小，直接用组合数定义计算即可

const int N = 20;
ll a[N];
int down = 1; //组合数的不变部分

int qmi(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return res;
}

int C(ll a, ll b) { //逆元求组合数
    if (a < b) return 0;
    int up = 1;
    for (ll i = a; i > a - b; i--) up = 1ll * i % mod * up % mod;
    return 1ll * up * down % mod;
}

int calc(ll n, ll m) { //参数ll还是int由题而定
    for (int j = 1; j <= n - 1; j++) down = 1ll * j * down % mod;
    down = qmi(down, mod - 2, mod);
    int res = 0; //答案
    //容斥原理一共由1<<N项 直接枚举即可
    for (int i = 0; i  < 1 << n; i++) {
        ll aa = m + n - 1, b = n - 1;
        int sign = 1; //项的正负号
        for (int j = 0; j < n; j++)
            if (i >> j & 1) {
                sign *= -1;
                aa -= a[j] + 1;
            }
        res = (res + C(aa, b) * sign) % mod;
    }
    return (res + mod) % mod;
}

int main() {
    ll n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    //n堆取m个组成的不同集合数量
    cout << calc(n , m) << endl;
    return 0;
}