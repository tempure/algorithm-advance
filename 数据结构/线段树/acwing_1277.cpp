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


//全部使用先乘再加的操作顺序 这样可以维护计算的表达式一致性
//x * a + b) * c +  d) * e + f
//开2个lazy tag 记录每次乘或者加即可

const int N = 100010;

int n, p, m;
int w[N];
struct Node {
    int l, r;
    int sum, add, mul;
} tr[N * 4];

void pushup(int u) {
    tr[u].sum = (tr[u << 1].sum + tr[u << 1 | 1].sum) % p;
}

void eval(Node &t, int add, int mul) {
    t.sum = ((ll)t.sum * mul + (ll)(t.r - t.l + 1) * add) % p;
    t.mul = (ll)t.mul * mul % p;
    t.add = ((ll)t.add * mul + add) % p;
}

void pushdown(int u) {
    eval(tr[u << 1], tr[u].add, tr[u].mul);
    eval(tr[u << 1 | 1], tr[u].add, tr[u].mul);
    tr[u].add = 0,  tr[u].mul = 1;
}

void modify(int u, int l, int r, int add, int mul) {
    if (tr[u].l >= l && tr[u].r <= r) eval(tr[u], add, mul);
    else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, add, mul);
        if (r > mid) modify(u << 1 | 1, l, r, add , mul);
        pushup(u);
    }
}

ll query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;

    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    ll sum = 0;
    if (l <= mid) sum = query(u << 1, l, r) % p;
    if (r > mid) sum = (sum + query(u << 1 | 1, l , r)) % p;
    return sum;
}

void build(int u, int l, int r) {
    if (l == r) tr[u] = {l, r, w[r], 0, 1}; //加0 乘1
    else {
        tr[u] = {l, r, 0, 0, 1};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

int main() {
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);

    build(1, 1, n);

    scanf("%d", &m);
    while (m --) {
        int t, l, r, d;
        scanf("%d%d%d", &t, &l, &r);
        if (t == 1) {
            scanf("%d", &d);
            modify(1, l, r, 0, d);
        }
        else if (t == 2) {
            scanf("%d", &d);
            modify(1, l, r, d, 1);
        }
        else printf("%d\n", query(1, l, r));
    }

    return 0;
}