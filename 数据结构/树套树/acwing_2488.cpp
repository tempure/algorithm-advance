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

const int N = 50010, M = N * 4, INF = 1e9; //线段树开4倍的点

int n, m;
struct Tree {
    int l, r;
    multiset<int> s;
} tr[M];

int w[M]; //存储初始元素用来建树

void build(int u, int l, int r) { //u是当前区间的编号 也就是节点的编号
    tr[u] = {l, r};
    tr[u].s.insert(-INF), tr[u].s.insert(INF); //避免边界值 找不到
    for (int i = l; i <= r; i++)  tr[u].s.insert(w[i]);
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

void change(int u, int p, int x) { //修改就是先删掉旧的 再插入新的
    tr[u].s.erase(tr[u].s.find(w[p]));  //find只找到第一个删掉 不是全部删除
    tr[u].s.insert(x);
    if (tr[u].l == tr[u].r) return;
    int mid = tr[u].l + tr[u].r >> 1;
    if (p <= mid) change(u << 1, p, x);
    else change(u << 1 | 1, p, x);
}

int query(int u, int a, int b, int x) {
    if (tr[u].l >= a && tr[u].r <= b) { //当前节点区间在所查区间内
        auto it = tr[u].s.lower_bound(x);
        -- it;
        return *it;
    }
    int mid = tr[u].l + tr[u].r >> 1,  res = -INF;
    if (a <= mid) res = max(res, query(u << 1, a, b, x));
    if (b > mid) res = max(res, query(u << 1 | 1, a, b, x));
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    build(1, 1, n); //1是root区间 也就是最大的区间

    while (m --) {
        int op, a, b, x;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &a, &x);
            change(1, a, x);
            w[a] = x;
        }
        else {
            scanf("%d%d%d", &a, &b, &x);
            printf("%d\n", query(1, a, b, x));
        }
    }

    return 0;
}