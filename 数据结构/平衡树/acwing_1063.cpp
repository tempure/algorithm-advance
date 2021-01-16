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
用DSU维护所有splay的关系
初始每一个点就是一颗splay 然后合并
合并为启发式合并，size小的splay的所有点插入size大的splay中
本质上就是把小的splay的所有点复制一份插入大的splay然后更新并查集的p[]祖宗关系
每次查询只会查询祖宗节点所在DSU节点的`root`，也就是说，将小的splay插入到大的splay
之后，查询原来小的splay中的id时，find()函数返回的root会定位到合并之后的大的splay
*/

const int N = 1800010;

int n, m;
struct Node {
    int s[2], p, v, id;
    int size;

    void init(int _v, int _id, int _p) {
        v = _v, id = _id, p = _p;
        size = 1;
    }
} tr[N];

int root[N], idx; //root[]记录每一颗splay的根节点
int p[N]; //DSU的祖宗节点

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void pushup(int x) {
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

void splay(int x, int k, int b) { //将b集合中的x旋转到k下边
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root[b] = x;
}

void insert(int v, int id, int b) { //将id的点插入b集合
    int u =  root[b], p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, id, p);
    splay(u, 0, b);
}

int get_k(int k, int b) { //返回集合b中val第k小的id
    int u = root[b];
    while (u) {
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return tr[u].id;
        else k -=  tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;
}

void dfs(int u, int b) { //将u所在的集合所有点插入b集合
    if (tr[u].s[0]) dfs(tr[u].s[0], b);
    if (tr[u].s[1]) dfs(tr[u].s[1], b);
    insert(tr[u].v, tr[u].id, b);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        p[i] = root[i] = i;
        int v;
        scanf("%d", &v);
        tr[i].init(v, i, 0);
    }
    idx = n;

    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        a = find(a), b = find(b);
        if (a != b) {
            if (tr[root[a]].size > tr[root[b]].size) swap(a, b);
            dfs(root[a], b);
            p[a] = b;
        }
    }

    scanf("%d", &m);
    while (m --) {
        char op[2];
        int a, b;
        scanf("%s%d%d", op, &a, &b);
        if (*op == 'B') {
            a = find(a), b = find(b);
            if (a != b) {
                if (tr[root[a]].size > tr[root[b]].size) swap(a, b);
                dfs(root[a], b);
                p[a] = b;
            }
        }
        else {
            a = find(a);
            if (tr[root[a]].size < b) puts("-1");
            else printf("%d\n", get_k(b, a));
        }
    }

    return 0;
}