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

/*
详细题解：https://www.luogu.com.cn/problem/solution/P1908 第一篇
整数范围 显然要先离散化才能在树状数组add
由于会出现相同的元素，而且std::sort是不稳定排序
离散化之后的数是没有相同的，相同元素必须保持原来插入的顺序，不然会错
此时要用双关键字排序 保证了插入顺序在离散化之后也是递增
每次统计即可，比如现在遍历插入的第8个数，那么加上比当前数大的数的个数即可
*/

#define x first //元素的值
#define y second //第几个加入的
typedef pair<int, int> pii;
const int N = 100003;
pii a[N]; //所有的点 双关键字排序
int tr[N], rk[N]; //rk是离散化映射
int n;

//双关键字排序 值相同的按照加入顺序升序
bool cmp(pii a, pii b) {
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

int lowbit(int x) {
    return x & -x;
}

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

ll sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x; //x是val值
        a[i].y = i; //加入的顺序
    }
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
        rk[a[i].y] = i;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        add(rk[i], 1);
        ans += i - sum(rk[i]);
    }
    cout << ans << endl;
    return 0;
}