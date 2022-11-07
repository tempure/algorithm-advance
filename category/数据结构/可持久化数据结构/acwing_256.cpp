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

//可持久化trie + 最大异或对
//可持久化trie记录 每个子树的元素在序列中的最大位置 如果位置<l-1那就不递归这个子树

const int N = 600010; //初始长度是N 然后有M个操作 每次都可能加 最多加2倍
const int M = N * 25; //二进制表示的节点总数

int n, m;
int tr[M][2]; //01二进制trie
int max_id[M];//每个子树最大的点在原序列中的下标是多大
int root[N];
int s[N];
int idx;

void insert(int i, int k, int p, int q) { //i是前缀和s下标 k当前处理的二进制位 p上一个版本 q最新版本
    if (k < 0) {
        max_id[q] = i;
        return;
    }
    int v = s[i] >> k & 1;
    if (p) tr[q][v ^ 1] = tr[p][v ^ 1]; //上一个版本的另外一位
    tr[q][v]  = ++idx;
    insert(i, k - 1, tr[p][v], tr[q][v]);
    max_id[q] = max(max_id[tr[q][0]], max_id[tr[q][1]]);
}

int query(int root, int c, int l) { //当前待匹配的查的值是c 左边界限制是l
    int p = root;
    for (int i = 23; i >= 0; i--) {
        int v = c >> i & 1;
        //如果二进制位相反的节点存在而且maxid满足条件
        if (max_id[tr[p][v ^ 1]] >= l) p = tr[p][v ^ 1];
        else p = tr[p][v];
    }

    return c ^ s[max_id[p]];
}

int main() {
    scanf("%d%d", &n , &m);
    max_id[0] = -1;
    root[0] = ++idx;

    insert(0, 23, 0, root[0]);

    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        s[i] = s[i - 1] ^ x;
        root[i] = ++idx;
        insert(i, 23, root[i - 1], root[i]);
    }

    char op[2];
    int l, r, x;
    while (m --) {
        scanf("%s", op);
        if (*op == 'A') {
            scanf("%d", &x);
            ++n;
            s[n] = s[n - 1] ^ x;
            root[n] = ++idx;
            insert(n, 23, root[n - 1], root[n]);
        }
        else {
            scanf("%d%d%d",  &l, &r, &x);
            printf("%d\n", query(root[r - 1], s[n] ^ x, l - 1));
        }
    }
    return 0;
}