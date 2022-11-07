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

//gcd(a,b) = gcd(a, b-a) 差分

const int N = 500010;

int n, m;
ll w[N];

struct Node {
    int l, r;
    ll sum, d; //差分数组的区间和 以及gcd
} tr[N * 4];

void pushup(Node &u, Node &l, Node &r) {
    u.sum = l.sum + r.sum;
    u.d = gcd(l.d, r.d);
}

void pushup(int u) {
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r) {
    ll b = w[r] - w[r - 1]; //建议差分数组
    if (l == r) tr[u] = {l, r, b, b};
    else {
        tr[u].l = l, tr[u].r = r;
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int x, ll v) {
    if (tr[u].l == x && tr[u].r == x) {
        ll b = tr[u].sum + v;
        tr[u] = {x, x, b, b};
    }
    else {
        int mid = tr[u].l + tr[u].r >>  1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}

Node query(int u, int l, int r) {
    if (l > r) return {0};
    if (tr[u].l >= l && tr[u].r <= r) return tr[u];
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid) return query(u << 1, l, r);
        else if (l > mid) return query(u << 1 | 1, l, r);
        else {
            auto left = query(u << 1, l,  r);
            auto right = query(u << 1 | 1, l, r);
            Node res;
            pushup(res, left, right);
            return res;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &w[i]);
    build(1, 1, n);

    int l, r;
    ll d;
    char op[2];
    while (m --) {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'Q') {
            auto left = query(1, 1, l);
            Node right({0, 0, 0, 0});
            if (l + 1 <= r) right = query(1, l + 1, r);
            printf("%lld\n", abs(gcd(left.sum, right.d)));
        }
        else {
            scanf("%lld", &d);
            modify(1, l , d);
            if (r + 1 <= n)  modify(1, r + 1, -d);
        }
    }

    return 0;
}
