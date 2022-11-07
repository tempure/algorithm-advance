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
找出(n,m)关于y=x+1的对称点(m−1,n+1)
每一条非法路径都对应一条(0,0)到(m−1,n+1)的路径，因此合法路径=总路径数-非法路径
答案就是C(n + m, n) - C(n + m, m - 1)
但是此题不是组合数取模，而且N上界5000，需要分解质因子+高精度乘法
*/


const int N = 100010; //高精度位数
int primes[N], cnt;
bool st[N]; //筛质数筛到10000 组合数最大n+m
int a[N], b[N];
// int sum[N]; //每个质因子出现的次数 就是幂次


void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = 1;
            if (i % primes[j] == 0) break;
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

void mul(int r[], int &len, int x) { //高精度乘法
    int t = 0;
    for (int i = 0; i < len; i++) {
        t += r[i] * x;
        r[i] = t % 10;
        t /= 10;

    }
    while (t) r[len++] = t % 10, t /= 10;
}

void sub(int a[], int al, int b[], int bl) { //高精度减法
    for (int i = 0, t = 0; i < al; i++) {
        a[i] -= t + b[i];
        if (a[i] < 0) a[i] += 10, t = 1;
        else t = 0;
    }
}

int C(int x, int y, int r[N]) {
    int len = 1;
    r[0] = 1;
    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        int s = get(x, p) - get(y, p) - get(x - y, p);
        while (s --) mul(r, len, p);
    }
    return len;
}

int main() {
    get_primes(N - 1);
    int n, m;
    cin >> n >> m;
    int al = C(n + m, n, a); //结果放入a中 al记录高精度结果的长度 便于减法高精度
    int bl = C(n + m, m - 1, b);

    sub(a, al, b, bl);

    int k = al - 1;
    while (!a[k] && k > 0) k--;
    while (k >= 0) printf("%d", a[k --]);

    return 0;
}