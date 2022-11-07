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

//二分图是 无向图的问题 但是有些有向图问题 本质还是 无向图

//二分边权 从冲突最大的开始 最终答案的取值范围为[0~1e9] 因为如果是二分图 那么就是0 如果是一个奇环 三个边都是1e9那么怎么分都是1e9
//所以每次二分mid 如果当前mid可以满足边权大于mid的点对都可以分开，也就是染色判定成功，那么就缩小mid

const int N = 20010, M = 200010; //无向边
int h[N], e[M], ne[M], w[M], idx;
int n, m;
int color[N]; //0 没有染色 1 白色 2 黑色

void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

bool dfs(int u, int c, int mid) {
    color[u] = c;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (w[i] <= mid) continue;
        if (color[j]) {
            if (color[j] == c) return false;
        }
        else if (!dfs(j, 3 - c, mid)) return false;
    }

    return true;
}

bool check(int mid) {
    memset(color, 0, sizeof color);
    for (int i = 1; i <= n; i++)
        if (!color[i])
            if (!dfs(i, 1, mid)) return false;
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    while (m --) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); add(b, a, c);
    }

    //二分
    int l = 0, r = 1e9;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    printf("%d\n", r);

    return 0;
}