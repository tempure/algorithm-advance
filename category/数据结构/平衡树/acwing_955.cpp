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

const int N = 500010, INF = 1e9;

int n, m;
struct Node {
    int s[2], p, v;
    int rev, same; //lazytag 反转 变成同一个数
    int size, sum, ms, ls, rs; //区间和/最大子段和/最大前缀和/最大后缀和

    void init(int vv, int pp) {
        s[0] = s[1] = 0, p = pp, v = vv;
        rev = same = 0;
        size = 1, sum = ms = v;
        ls = rs = max(v, 0);
    }
} tr[N];

int root;
int nodes[N], tt; //内存（节点）回收数组
int w[N]; //初始的数组用来build建树


void pushup(int x) {
    auto &u = tr[x], &l = tr[u.s[0]], &r = tr[u.s[1]];
    u.size = l.size + r.size + 1;
    u.sum = l.sum + r.sum + u.v;
    u.ls = max(l.ls, l.sum + u.v + r.ls); //最大前缀
    u.rs = max(r.rs, r.sum + u.v + l.rs);
    u.ms = max(max(l.ms, r.ms), l.rs + u.v + r.ls);
}

void pushdown(int x) {
    auto &u = tr[x], &l = tr[u.s[0]], &r = tr[u.s[1]];
    if (u.same) {
        u.same = u.rev = 0; //如果全部变为一个数，那么rev反转无意义
        if (u.s[0]) l.same = 1, l.v = u.v, l.sum = l.v * l.size;
        if (u.s[1]) r.same = 1, r.v = u.v, r.sum = r.v * r.size;
        if (u.v > 0) {
            if (u.s[0]) l.ms = l.ls = l.rs = l.sum;
            if (u.s[1]) r.ms = r.ls = r.rs = r.sum;
        }
        else {
            if (u.s[0]) l.ms = l.v, l.ls = l.rs = 0;
            if (u.s[1]) r.ms = r.v, r.ls = r.rs = 0;
        }
    }
    else if (u.rev) {
        //注意交换的是前后缀，不是简单交换所有的节点信息
        //所以先交换前后缀然后单纯交换"子节点的子节点"
        //到子节点的子节点pushdown的时候，直接交换前后缀就可以了
        u.rev = 0, l.rev ^= 1, r.rev ^= 1;
        swap(l.ls, l.rs), swap(r.ls, r.rs);
        swap(l.s[0], l.s[1]), swap(r.s[0], r.s[1]);
    }
}

int build(int l, int r, int p) { //p是建的树的root节点
    int mid = l + r >> 1;
    int u = nodes[tt--];
    tr[u].init(w[mid], p);
    if (l < mid) tr[u].s[0] = build(l, mid - 1, u);
    if (mid < r) tr[u].s[1] = build(mid + 1, r, u);
    pushup(u);
    return u;
}

void rotate(int x) { //左旋+右旋
    //拓扑序是 Z->Y->X
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x; // k=0表示x是y的左儿子；k=1表示x是y的右儿子 k=1右旋 否则左旋
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z; //z的子节点改为x x的父节点改为z
    //y的左节子点是x的右子节点，或者右子节点是x的左子节点 根据左右旋(k)而定
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y; //x的右(左)子节点的父亲是y
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);  //旋转之后先pushup(y) 后pushup(x)
    //此处不用push(z)因为pushup本题的操作只是维护size，而z的子树size没有改变
}

void splay(int x, int k) { //将x旋转到k的下边
    while (tr[x].p != k) {
        //拓扑序是Z->Y->X
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            //如果是折线状就旋转2次X
            //直线形状就先y后x
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x; //特判旋转后是root的情况
}

int get_k(int k) { //返回中序第k大的元素编号
    int u = root;
    while (u) {
        pushdown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
}

void dfs(int u) { //内存回收
    if (tr[u].s[0]) dfs(tr[u].s[0]);
    if (tr[u].s[1]) dfs(tr[u].s[1]);
    nodes[++tt] = u;
}

int main() {
    for (int i = 1; i < N; i++) nodes[++tt] = i;
    scanf("%d%d", &n, &m);
    tr[0].ms = w[0] = w[n + 1] = -INF;  //0号是哨兵
    for (int i = 1; i <=  n; i++) scanf("%d", &w[i]);
    root = build(0, n + 1, 0);

    char op[20];
    while (m --) {
        scanf("%s", op);
        if (!strcmp(op, "INSERT")) {
            int posi, tot;
            scanf("%d%d", &posi, &tot);
            for (int i = 0; i < tot; i++) scanf("%d", &w[i]);
            int l = get_k(posi + 1), r = get_k(posi + 2);
            splay(l, 0), splay(r, l);
            int u = build(0, tot - 1, r);
            tr[r].s[0] = u;
            pushup(r), pushup(l);
        }
        else if (!strcmp(op, "DELETE")) {
            int posi, tot;
            scanf("%d%d", &posi, &tot);
            int l = get_k(posi), r = get_k(posi + tot + 1);
            splay(l, 0), splay(r, l);
            dfs(tr[r].s[0]); //删除节点内存回收
            tr[r].s[0] = 0;
            pushup(r), pushup(l);
        }
        else if (!strcmp(op, "MAKE-SAME")) {
            int posi, tot, c;
            scanf("%d%d%d", &posi, &tot, &c);
            int l = get_k(posi), r = get_k(posi + tot + 1);
            splay(l, 0), splay(r, l);
            auto &son = tr[tr[r].s[0]];
            son.same = 1, son.v = c, son.sum = c * son.size; //打tag
            if (c > 0) son.ms = son.ls = son.rs = son.sum;
            else son.ms = c, son.ls = son.rs = 0; //数列至少有一个数
            pushup(r), pushup(l);
        }
        else if (!strcmp(op, "REVERSE")) {
            int posi, tot;
            scanf("%d%d", &posi, &tot);
            int l = get_k(posi), r = get_k(posi + tot + 1);
            splay(l, 0), splay(r, l);
            auto &son = tr[tr[r].s[0]];
            son.rev ^= 1;
            swap(son.ls, son.rs);
            swap(son.s[0], son.s[1]);
            pushup(r), pushup(l);
        }
        else if (!strcmp(op, "GET-SUM")) {
            int posi, tot;
            scanf("%d%d", &posi, &tot);
            int l = get_k(posi), r = get_k(posi + tot + 1);
            splay(l, 0), splay(r, l);
            printf("%d\n", tr[tr[r].s[0]].sum);
        }
        else printf("%d\n", tr[root].ms); //最大连续子段和
    }

    return 0;
}