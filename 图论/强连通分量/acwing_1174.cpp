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

//如果暴力 可以在反图上遍历每个点是否能到其他所有点 复杂度O(N * (N + M)) 会超时
//Tarjan 强连通分量+缩点+拓扑图 拓扑图至少存在一个出度为0的点
//A认为B受欢迎，那么就从A向B连一条边
//对于缩点之后的拓扑图 如果存在2个及以上的出度为0的点 那么答案就是0 因为其中一个出度为0的点 肯定不会被另外一个出度为0的点欢迎
//如果只有一个出度为0的缩点 那么就是答案 这个缩点代表的强连通分量里面的缩点之前的点的个数就是答案

//没必要建立缩点之后的拓扑图 只需要遍历一下强连通分量 然后统计出边即可

const int N = 10010, M = 50010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp; //时间戳 low数组
int stk[N], top;  //栈和栈顶
bool in_stk[N]; //每个点是否在栈中
int id[N], scc_cnt, sz[N];  //每个点所属的强连通分量编号 强连通分量的总数 每个点所在强连通分量的点的数量
int dout[N]; //记录每个强连通分量的出度

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp; //初始化时间戳 和low数组 然后后期更新low数组
    stk[++top] = u, in_stk[u] = true; //入栈

    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j]) low[u] = min(low[u], dfn[j]); //如果已经在栈中了 就直接拿来更新low
    }

    if (dfn[u] == low[u]) { //找到强连通分量
        ++ scc_cnt; //数量+1
        int y;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt]++;
        } while (u != y); //弹出栈顶到u的所有元素 这些元素就组成一个强连通分量
    }
}


int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    while (m --) {
        int a, b ;
        scanf("%d%d", &a, &b);
        add(a, b);
    }

    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);

    //统计所有点的出度 同是处理缩边后的图的连通分量的出度
    for (int i = 1; i <= n; i++)
        for (int j = h[i]; j != -1; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) dout[a]++; //a b是两个不同强连通分量的编号 那么就在这个缩点图里面 a的出度加一
        }

    int zeros = 0, sum = 0; //出度为0的分量个数 以及所有这样分量内小的点的总数量

    for (int i = 1; i <= scc_cnt; i++)
        if (!dout[i]) {
            zeros ++;
            sum += sz[i];
            if (zeros > 1) { //没有符合条件的牛
                sum = 0;
                break;
            }
        }

    printf("%d\n", sum);

    return 0;
}