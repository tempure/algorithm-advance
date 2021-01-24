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
将所有的边以ai为关键字升序排序，然后枚举所有的边，加入当前的图中
如果成环，那么就删去环中最大的一个边即可，始终维护当前图为树结构
在加入边的过程中，维护起点和终点的连通关系，用并查集即可
如果起点能到达终点，那么开始更新答案

做法的正确性：由于保持了一个参数ai的单调，那么可以将ai看作函数的自变量，答案res看作因变量
对于不同的ai，其边的bi也不同，造成的答案也不同，时刻维护最小答案即可
当起点能到达终点以后，每次加入新的边，都会重新将1~n的路径建成splay来更新答案，splay的根节点保存当前子树的最大边权

由于LCT维护的splay都是维护点权，此题是边，技巧是每个边中间加入一个点，重新编号即可。
有m个ai，每次加入新边之后操作都是log，复杂度O(m*logn)
*/

const int N = 150010, INF = 0x3f3f3f3f;

int n, m;

struct Edge {
    int x, y, a, b;
    bool operator< (const Edge &t) {
        return a < t.a; //以a为关键字进行排序
    }
} e[N];

struct Node {
    int s[2], p, v;
    int mx, rev;
} tr[N];

int stk[N], p[N]; //stk是splay需要用到的栈

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void pushup(int x) { //模板中只有pushup不一样，根据需要维护的东西而定
    tr[x].mx = x;
    for (int i = 0; i < 2; i++)
        if (tr[tr[tr[x].s[i]].mx].v > tr[tr[x].mx].v)
            tr[x].mx = tr[tr[x].s[i]].mx;
}

void pushrev(int x) {
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].rev ^= 1;
}

void pushdown(int x) {
    if (tr[x].rev) {
        pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
        tr[x].rev = 0;
    }
}

bool isroot(int x) { //x是否是当前splay的树根
    return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x;
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    if (!isroot(y)) tr[z].s[tr[z].s[1] == y] = x; //splay的根的父亲节点的上边是虚边 可不敢乱旋转
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x) {
    int top = 0, r = x;
    stk[++top] = r;
    while (!isroot(r)) stk[++top] = r = tr[r].p;
    while (top) pushdown(stk[top --]);
    while (!isroot(x)) {
        int y = tr[x].p, z = tr[y].p;
        if (!isroot(y))
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
}

void access(int x) { // 建立一条从根到x的路径，同时将x变成splay的根节点
    int z = x;
    for (int y = 0; x; y = x, x = tr[x].p) {
        splay(x);
        tr[x].s[1] = y, pushup(x);
    }
    splay(z);
}

void makeroot(int x) {  // 将x变成原树的根节点
    access(x);
    pushrev(x);
}

int findroot(int x) { // 找到x所在原树的根节点, 再将原树的根节点旋转到splay的根节点
    access(x);
    while (tr[x].s[0]) pushdown(x), x = tr[x].s[0];
    splay(x);
    return x;
}

void split(int x, int y) {  // 给x和y之间的路径建立一个splay，其根节点是y
    makeroot(x);
    access(y);
}

void link(int x, int y) { // 如果x和y不连通，则加入一条x和y之间的边
    makeroot(x);
    if (findroot(y) != x) tr[x].p = y;
}

void cut(int x, int y) { // 如果x和y之间存在边，则删除该边
    makeroot(x);
    if (findroot(y) == x && tr[y].p == x && !tr[y].s[0]) {
        tr[x].s[1] = tr[y].p = 0;
        pushup(x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        e[i] = {x, y, a, b};
    }
    sort(e + 1, e + m + 1);
    for (int i = 1; i <= n + m; i++) {
        p[i] = i;
        if (i > n) tr[i].v = e[i - n].b; //2个点中间的边上加个点存放边权 这些点编号n + 1~n + m, splay的权值都在点上
        tr[i].mx = i; //初始的每个点都是一棵splay
    }

    int res = INF;

    for (int i = 1; i <= m; i++) {
        int x = e[i].x, y = e[i].y, a = e[i].a, b = e[i].b;
        if (find(x) == find(y)) {
            //加上这条边之后就成环了 删去环中最大的边
            split(x, y);
            int t = tr[y].mx;
            if (tr[t].v > b) {
                //每个边中间加入了新的点 要删去新点的左右2条边
                cut(e[t - n].x, t), cut(t, e[t - n].y);
                link(x, n + i), link(n + i, y);
            }
        }
        else { //未成环就直接加上这条边
            p[find(x)] = find(y);
            link(x, n + i), link(n + i, y);
        }

        if (find(1) == find(n)) { //此时已经起点和终点连通 那么就开始更新答案
            split(1, n);
            res = min(res, a + tr[tr[n].mx].v);
        }
    }
    if (res == INF) res = -1;
    cout << res << endl;

    return 0;
}
