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


//模板题

//无向图：边连通 没有孤立边 而且所有点度数都是偶数
//有向图：边连通 没有孤立边 而且所有点的入度等于出度
//一般没必要加删表头的优化 但是小概率会被卡掉 此题就会被卡

//欧拉回路和孤立点没有关系 只和边有关系

const int N = 100010, M = 400010;//无向图 二倍边
int h[N], e[M], ne[M], idx;
bool used[M]; //标记边是否被用过
int ans[M], cnt; //cnt记录答案路径的长度
int din[N], dout[N]; //度数

int type;
int n, m;

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

void dfs(int u) {
    while (h[u] != -1) {
        int i = h[u]; //直接让i是表头即可
        if (used[i]) {
            h[u] = ne[i]; //删边
            continue;
        }

        h[u] = ne[i];
        used[i] = true;
        if (type == 1) used[i ^ 1] = true; //无向图标记反向边
        dfs(e[i]);
        //加边时候第一条边的编号是0开始 但是题目是边从1开始 注意！
        if (type == 1) {
            int t = i / 2 + 1; //无向图边的编号 t 因为每次都是加成对的边 但是输入只输入一条
            if (i & 1) t *= -1; //边的编号是奇数 说明是反向边 因为加边的时候是从0开始成对加
            ans[++cnt] = t;
        }
        else ans[++cnt] = i + 1;
    }
}

int main() {
    scanf("%d", &type);
    scanf("%d%d", &n, &m);
    memset(h, -1 , sizeof h);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        if (type == 1) add(b, a);

        din[b] ++, dout[a] ++;
    }

    //提前判断无解的情况
    if (type == 1) {
        for (int i = 1; i <= n; i++)
            if (din[i] + dout[i] & 1) {
                puts("NO");
                return 0;
            }
    }
    else {
        for (int i = 1; i <= n; i++)
            if (din[i] != dout[i]) {
                puts("NO");
                return 0;
            }
    }

    //找一个包含边的起点
    for (int i = 1; i <= n; i++)
        if (h[i] != -1) {
            dfs(i);
            break;
        }

    if (cnt < m) { //有孤立边
        puts("NO");
        return 0;
    }

    puts("YES");
    for (int i = cnt ; i ; i --) printf("%d ", ans[i]);
    puts("");

    return 0;
}
