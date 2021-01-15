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
由于是对所有区间元素增加或者减小 直接记录一个偏移量delta即可
每次扣除工资操作就删除前缀小于 m - delta 的区间删去即可
*/

const int N = 100010, INF = 0x3f3f3f3f;

int n, m, delta;

struct Node {
    int s[2], p, v;
    int size;

    void init(int _v, int _p) {
        v = _v, p = _p;
        size = 1;
    }
} tr[N];

int root, idx;

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

void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}

int insert(int v) {
    int u = root, p = 0;
    //插入是每个点的val满足BST 不是节点的tr数组编号
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0);
    return u; //返回该点的tr数组编号
}

int lower_bound_(int v) { //返回val大于等于v的节点编号
    int u = root, res;
    while (u) {
        if (tr[u].v >= v) res = u, u = tr[u].s[0];
        else u = tr[u].s[1];
    }
    return res;
}

int get_k(int k) { //返回第k小的val
    int u = root;
    while (u) {
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 ==  k) return tr[u].v;
        else k -= tr[tr[u].s[0]].size + 1,  u = tr[u].s[1];
    }
    return -1; //没找到
}

int main() {
    scanf("%d%d", &n, &m);
    int L = insert(-INF), R = insert(INF); //哨兵 返回tr数组中的编号

    int tot = 0; //insert的员工总数量
    while (n --) {
        char op[2];
        int k;
        scanf("%s%d", op, &k);
        if (*op == 'I') {
            if (k >= m) k -= delta, insert(k), tot ++; //新员工的工资要先减去当前的偏移量，因为偏移量已经算上了该员工之前的加减工资操作
        }
        else if (*op == 'A') delta += k;
        else if (*op == 'S') {
            delta -= k;
            R = lower_bound_(m - delta); //R是>=m-delta的第一个数的编号
            splay(L, 0), splay(R, L); //这里的删除怎么写都行 只要记住L的中序肯定在R左边即可
            tr[R].s[0] = 0;
            pushup(R), pushup(L); //删去节点之后 要先pushup下边的节点 后pushup上边的
        }
        else {
            if (tr[root].size - 2 < k) puts("-1");
            else printf("%d\n", get_k(tr[root].size - k) + delta);
        }
    }

    printf("%d\n", tot - (tr[root].size - 2)); //减去哨兵 以及现存的人 就是离职的人数

    return 0;
}
