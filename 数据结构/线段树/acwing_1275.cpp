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

//直接在1~m区间建立线段树 每次末尾增加就是单点修改
//最大值就是区间查询

const int N = 200010;

int m, p;

struct Node {
    int l, r ;
    int v; //区间[l,r] 的最大值
} tr[N * 4];

//子节点更新父节点
void pushup(int u) {
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v; //查询的区间完全包含在树中的某个段区间内 段的最大值就是候选值

    int mid = tr[u].l + tr[u].r >> 1;
    int v = 0;
    if (l <= mid) v = query(u << 1, l, r); // 左边 有交集 递归向下查左边 注意l <= mid
    if (r > mid) v = max(v, query(u << 1 | 1, l , r)); //右边有交集 递归查右边
    return v;
}

void modify(int u, int x, int v) { //将x位置的点的值修改为v
    if (tr[u].l == x && tr[u].r == x) tr[u].v = v; //叶节点找到了直接修改
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x , v);
        else modify(u << 1 | 1, x, v);
        pushup(u); //修改之后要更新最大值 回溯的时候
    }
}

void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) return ;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

int main() {
    int n = 0, last = 0; //上一次查询的结果
    scanf("%d%d", &m, &p);
    build(1, 1, m);

    char op[2];
    int x;
    int l;
    while (m --) {
        scanf("%s%d", op, &x);
        if (*op == 'Q') {
            last = query(1, n - x + 1, n);
            printf("%d\n", last);
        }
        else {
            modify(1, n + 1, (last + x) % p);
            n ++;
        }
    }

    return 0;
}