#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head


//注意题目给的并以一定是连通图 所以 要先求一次所有连通块 然后分别处理每个连通块
//一共有cnt个连通块, 那么处理完一个连通块假设该连通块可以分为s个最多, 那么处理完该连通块的结果就是s + cnt - 1
//依次同样方法处理所有连通块即可

//求一个连通块的s: 判断割点

const int N = 10010, M = 30010;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int root, ans;

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;

    int cnt = 0; //记录u有多少子树
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (low[j] >= dfn[u]) //说明u是割点 而且此时的j是u的出边遍历中的一个子树 那么需要记录搜索树中子树的个数
                cnt ++;
        }
        else low[u] = min(low[u], dfn[j]);
    }

    //如果u是root节点 那么去掉u后直接加上子树的个数即可
    if (u != root && cnt) cnt ++; //u节点有cnt个子树 去掉u后 u的父亲连通块就会多出来 以及cnt个单独的子树

    ans = max(ans, cnt);
}

int main() {
    while (scanf("%d%d", &n, &m) , n || m) {
        memset(dfn, 0, sizeof dfn);
        memset(h, -1, sizeof h);
        idx = timestamp = 0;

        while (m --) {
            int a, b;
            scanf("%d%d", &a, &b);
            add(a, b); add(b, a);
        }

        int cnt = 0;
        ans = 0; //每次清空答案
        for (root = 0; root < n; root++) {
            if (!dfn[root]) {
                cnt ++;  //非连通图 tarjan还可以顺便求出连通块数量 因为tarjan的本质就是dfs
                tarjan(root);
            }
        }

        printf("%d\n", ans + cnt - 1);
    }
    return 0;
}