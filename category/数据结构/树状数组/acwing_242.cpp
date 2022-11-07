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

//树状数组只支持单点修改和区间求和
//但是这个题要区间修改和单点查询 直接转换为差分即可
//初始化add成差分数组即可 单点查询就是直接差分数组求前缀和

const int N = 1e5 + 10;

int n, m;
int a[N];
ll tr[N];

int lowbit(int x) {
    return x & -x;
}

void add(int x , int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

ll sum(int x) {
    ll res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1 ; i <= n; i++) scanf("%d", &a[i]);

    for (int i = 1; i <= n; i++) add(i, a[i] - a[i - 1]); //初始化差分数组 暴力方法建树

    while (m --) {
        char op[2];
        int l, r, d;
        scanf("%s%d", op, &l);
        if (*op == 'C') {
            scanf("%d%d", &r, &d);
            add(l, d); add(r + 1, -d);
        }
        else {
            printf("%lld\n", sum(l));
        }
    }

    return 0;

}