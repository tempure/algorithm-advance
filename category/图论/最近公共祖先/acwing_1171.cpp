#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i = a; i< n; i++)
#define per(i,a,n) for(int i=n-1; i>=a; i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
// #define x first
// #define y second
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

//在线做法 倍增 离线做法Tarjan算法 复杂度O(N + M) N是节点数量 M是询问数量 比倍增更快
//树上2点的最短距离 就是2点的路径长度 求出2个点到root节点的距离求和 然后减去lca到root距离的2倍

const int N = 20010, M = 2 * N; //无向边 开2倍

int n, m;
int h[N], e[M], w[M], ne[M], idx;
int p[N]; //并查集父节点
int res[N]; //询问的结果
int st[N]; //tarjan 过程中的标记数组

int dist[N]; //每个点和root的距离

vector<pii> query[N]; //询问 first 查询的另外一个点 second是查询编号

void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

void dfs(int u, int fa) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue; // 防止反向搜
        dist[j] = dist[u] + w[i];
        dfs(j, u);
    }
}

//正在搜的点标记为1 搜过的点也就是回溯过的点 标记为2  还没有搜过的点标记为0
void tarjan(int u) {
    st[u] = 1; //正在搜的点
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            tarjan(j);
            p[j] = u; //遍历u的所有相邻点 然后合并进并查集
        }
    }

    for(auto item : query[u]){ // 遍历所有和u相关的查询
        int y = item.first, id = item.second;
        if(st[y] == 2){ //如果要查询的点 以及被合并过了
            int anc = find(y);
            res[id] = dist[u] + dist[y] - dist[anc] * 2;
        }
    }
    st[u] = 2; //被遍历过了
}


int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    for (int i = 0; i < n - 1; i ++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); add(b, a, c);
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a != b) { //如果2节点相同 那就是0, res是全局数组 默认就是0
            query[a].pb({b, i}); //和a查询相关的点是b 查询编号是i
            query[b].pb({a, i});
        }
    }

    for (int i = 1; i <= n; i++) p[i] = i; //初始化并查集

    dfs(1, -1); ////随便拿一个点当root即可 从1号点开始
    tarjan(1); //假设1号就是root了

    for (int i = 0; i < m; i++) printf("%d\n", res[i]);

    return 0;
}