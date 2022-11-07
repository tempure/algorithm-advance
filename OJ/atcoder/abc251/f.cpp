#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef basic_string<int> BI;
typedef long long ll;
typedef pair<int, int> PII;
typedef double db;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
// head

//https://atcoder.jp/contests/abc251/submissions/31666796
//题意就是第一颗生成树所有的非树边点的高度都不一样，要有子孙关系
//第二棵树就是所有所有非树边都不能有子孙关系，高度相同

//第一个就是输出DFS树 DFS树中所有非树边都是返祖边 都是非同层的，高度不一样
//第二个就是输出BFS树，BFS树中所有非树边都是同层的，没有子孙关系
//因为BFS时候，同层的边已经全部被加入队列，当前层的点不会把同层的点扫描加入队列

const int N = 201000;
int n, m, vis[N];
VI e[N];
void dfs(int u) {
    vis[u] = 1;
    for (auto v : e[u]) {
        if (!vis[v]) {
            printf("%d %d\n", u, v);
            dfs(v);
        }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    rep(i, 0, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].pb(v);
        e[v].pb(u);
    }
    dfs(1); //1是root 题目规定
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : e[u]) {
            if (!vis[v]) {
                q.push(v);
                vis[v] = 1;
                printf("%d %d\n", u, v);
            }
        }
    }
}
