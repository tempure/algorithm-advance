#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i = a; i< n; i++)
#define per(i,a,n) for(int i=n-1; i>=a; i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define x first
#define y second
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

//规定d[0] = 0 第0层的深度是0 ，以及跳出根节点后 f[x][k] = 0 这样跳出后就不会出界 而是继续判断
//若a是b的祖先 那么lca(a, b) 就是a

const int N = 40010, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], idx;
int depth[N], fa[N][16]; // k最大是log2(N)
int q[N]; //BFS队列

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void bfs(int root) {
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[root] = 1; //根节点所在的层数定义为1
    int hh = 0, tt = 0;
    q[0] = root;

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++tt] = j;
                fa[j][0] = t; //跳一步
                for (int k = 1; k <= 15; k++) //处理j的所有祖先
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
            }
        }
    }
}

int lca(int a, int b){
    if(depth[a] < depth[b]) swap(a, b); //从低的往高的跳
    //跳到同一层
    for(int k = 15; k >=0; k--)
        if(depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    if(a == b) return a; //或者return b 这种情况是b是a的祖先

    //同时往上跳
    for(int k = 15; k >= 0; k--)
        if(fa[a][k] != fa[b][k]){
            a = fa[a][k];
            b = fa[b][k];
        }
    return fa[a][0]; //或者 fa[b][0]
}

int main() {
    scanf("%d", &n);
    int root = 0;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (b == -1) root = a;
        else add(a, b), add(b, a);
    }
    bfs(root); //预处理depth数组和倍增数组

    scanf("%d", &m);
    while(m --){
        int a,b ;
        scanf("%d%d", &a, &b);
        int p = lca(a, b);
        if(p == a) puts("1");
        else if(p == b) puts("2");
        else puts("0");
    }
    
    return 0;
}