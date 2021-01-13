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

#define x first
#define y second

typedef pair<double, double> pdd;

const int N = 110;
const double INF = 0x3f3f3f3f;

int n, m;
pdd q[N]; //所有的点
bool g[N][N]; //邻接矩阵
double d[N][N], bd[N][N]; //d[][]记录欧几里得距离 bd是缩点的备份数组
int pre[N]; //pre记录每个点的前驱点
int dfn[N], low[N], ts, stk[N], top;
int id[N], cnt;
bool st[N], ins[N];

void dfs(int u) {
    st[u] = true;
    for (int i = 1; i <= n; i++)
        if (g[u][i] && !st[i])
            dfs(i);
}

double get_dist(int a, int b) {
    double dx = q[a].x - q[b].x;
    double dy = q[a].y - q[b].y;

    return sqrt(dx * dx + dy * dy);
}

bool check_con() { //检验连通性
    memset(st, 0, sizeof st);
    dfs(1);
    for (int i = 1; i <= n; i++)
        if (!st[i]) return false;
    return true;
}

void tarjan(int u) { //判断是否存在环
    dfn[u] = low[u] = ++ts;
    stk[++top] = u, ins[u] = true;

    int j = pre[u];
    if (!dfn[j]) {
        tarjan(j);
        low[u] = min(low[u], low[j]);
    } else if (ins[j]) low[u] = min(low[u], dfn[j]);

    if (low[u] == dfn[u]) {
        int y;
        ++cnt;
        do {
            y = stk[top --], ins[y] = false, id[y] = cnt;
        } while (y != u);
    }
}

double work() {
    double res = 0; //结果
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (g[i][j]) d[i][j] = get_dist(i, j);
            else d[i][j] = INF;

    while (1) { //迭代
        for (int i = 1; i <= n; i++) { //找出所有点入边权最小的入点
            pre[i] = i; //初始所有点的前驱点为自身
            for (int j = 1; j <= n; j++)
                if (d[pre[i]][i] > d[j][i])
                    pre[i] = j;
        }

        memset(dfn, 0, sizeof dfn);
        ts = cnt = 0;
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                tarjan(i);

        if (cnt == n) { //SCC数量等于点的数量 说明不存在环 算法结束
            for (int i = 2; i <= n; i++)
                res += d[pre[i]][i];
            break;
        }

        for (int i = 2; i <= n; i++) //加上所有环的边权
            if (id[pre[i]] == id[i])
                res += d[pre[i]][i];

        //初始化备份数组以及缩点
        for (int i = 1; i <= cnt; i++)
            for (int j = 1; j <= cnt; j++)
                bd[i][j] = INF; //初始化备份数组

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][j] < INF && id[i] != id[j]) { //i j不在同一个SCC中
                    /*
                    缩点时候，在一个SCC中的点，全部用该SCC的id来表示
                    存在bd[][]数组中，就相当于缩点了
                    */
                    int a = id[i], b = id[j];
                    if (id[pre[j]] == id[j]) //j在环中
                        bd[a][b] = min(bd[a][b], d[i][j] - d[pre[j]][j]);
                    else bd[a][b] = min(bd[a][b], d[i][j]); //普通边 不在环中
                }
        n = cnt;
        memcpy(d, bd, sizeof d);
    }

    return res;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++)
            scanf("%lf%lf", &q[i].x, &q[i].y);

        memset(g, 0, sizeof g);
        while (m --) {
            int a, b;
            scanf("%d%d", &a, &b);
            if (a != b && b != 1) g[a][b] = true; //注意判断自环 以及忽略指向起点的边
        }

        if (!check_con()) puts("poor snoopy"); //不连通 无解
        else printf("%.2lf\n", work());
    }

    return 0;
}