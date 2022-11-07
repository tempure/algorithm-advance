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
请你写出一种数据结构，来维护一个长度为 n 的数列，其中需要提供以下操作：

1 l r x，查询整数 x 在区间 [l,r] 内的排名。
2 l r k，查询区间 [l,r] 内排名为 k 的值。
3 pos x，将 pos 位置的数修改为 x。
4 l r x，查询整数 x 在区间 [l,r] 内的前驱(前驱定义为小于 x，且最大的数)。
5 l r x，查询整数 x 在区间 [l,r] 内的后继(后继定义为大于 x，且最小的数)。
数列中的位置从左到右依次标号为 1∼n。

区间 [l,r] 表示从位置 l 到位置 r 之间（包括两端点）的所有数字。

区间内排名为 k 的值指区间内从小到大排在第 k 位的数值。（位次从 1 开始）
*/

const int N = 1500010, INF = 0x3f3f3f3f;

int n, m;

struct Node {
    int s[2], p, v;
    int size;

    void init(int _v, int _p) {
        v = _v, p = _p;
        size = 1;
    }
} tr[N];

int L[N], R[N], T[N], idx; //线段树
int w[N]; //原数组

void pushup(int x) { //splay pushup
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int &root, int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}

void insert(int &root, int v) {
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(root, u, 0);
}

int get_k(int root, int v) { //查询在当前线段树节点的splay中有多少元素比v小
    int u = root, res = 0;
    while (u) {
        if (tr[u].v < v) res += tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
        else u = tr[u].s[0];
    }
    return res;
}

int query(int u, int a, int b, int x) {//区间[a,b]中有多少元素比x小
    if (L[u] >= a && R[u] <= b) return get_k(T[u], x) - 1; //减去哨兵
    int mid = L[u] + R[u] >> 1, res = 0;
    if (a <= mid) res += query(u << 1, a, b, x);
    if (b > mid) res += query(u << 1 | 1, a, b, x);
    return res;
}

void update(int &root, int x, int y) { //在当前splay将x删除 插入y
    int u = root;
    while (u) {
        if (tr[u].v == x) break;
        if (tr[u].v < x) u = tr[u].s[1];
        else u = tr[u].s[0];
    }
    splay(root, u, 0);
    int l = tr[u].s[0], r = tr[u].s[1];
    while (tr[l].s[1]) l = tr[l].s[1]; //一直向右下查询后继
    while (tr[r].s[0]) r = tr[r].s[0]; //左下查询前驱
    splay(root, l, 0), splay(root, r, l);
    tr[r].s[0] = 0;
    pushup(r), pushup(l);
    insert(root, y);
}

void change(int u, int p, int x) { //更新当前线段树节点以及子节点
    update(T[u], w[p], x);
    if (L[u] == R[u]) return;
    int mid = L[u] + R[u] >> 1;
    if (p <= mid) change(u << 1, p, x);
    else change(u << 1 | 1, p, x);
}

int get_pre(int root, int v) { //查找一个splay中v的前驱
    int u = root, res = -INF;
    while (u) {
        if (tr[u].v < v) res = max(res, tr[u].v), u = tr[u].s[1];
        else u = tr[u].s[0];
    }
    return res;
}

int get_suc(int root, int v) { //查找一个splay中的后继
    int u = root, res = INF;
    while (u) {
        if (tr[u].v > v) res = min(res, tr[u].v), u = tr[u].s[0];
        else u = tr[u].s[1];
    }
    return res;
}

int query_pre(int u, int a, int b, int x) { //线段树区间[a,b]查询x的前驱
    //思路是用所有当前区间覆盖的splay的所有前驱/后继来更新
    if (L[u] >= a && R[u] <= b) return get_pre(T[u], x);
    int mid = L[u] + R[u] >> 1, res = -INF;
    if (a <= mid) res = max(res, query_pre(u << 1, a, b, x));
    if (b > mid) res = max(res, query_pre(u << 1 | 1, a, b, x));
    return res;
}

int query_suc(int u, int a, int b, int x) {
    if (L[u] >= a && R[u] <= b) return get_suc(T[u], x);
    int mid = L[u] + R[u] >> 1, res = INF;
    if (a <= mid) res = min(res, query_suc(u << 1, a, b, x));
    if (b > mid) res = min(res, query_suc(u << 1 |  1, a, b, x));
    return res;
}

void build(int u, int l, int r) { //线段树建树
    L[u] = l, R[u] = r;
    insert(T[u], -INF), insert(T[u], INF);
    for (int i = l; i <= r; i++) insert(T[u], w[i]);
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    build(1, 1, n);

    while (m --) {
        int op, a, b, x;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d%d", &a, &b, &x);
            printf("%d\n", query(1, a, b, x) + 1); //求出的是有多少数比x小 所以x排名要加一
        }
        else if (op == 2) {
            scanf("%d%d%d", &a, &b, &x);
            int l = 0, r = 1e8;
            while (l < r) { //二分x用第一个功能来判断排名
                int mid = l + r + 1 >> 1;
                if (query(1, a, b, mid) + 1 <= x) l = mid;
                else r = mid - 1;
            }
            printf("%d\n", r);
        }
        else if (op == 3) {
            scanf("%d%d", &a, &x);
            change(1, a, x);
            w[a] = x;
        }
        else if (op == 4) {
            scanf("%d%d%d", &a, &b, &x);
            printf("%d\n", query_pre(1, a, b, x)); //查找前驱
        }
        else {
            scanf("%d%d%d", &a, &b, &x);
            printf("%d\n", query_suc(1, a, b, x)); //查询后继
        }
    }

    return 0;
}