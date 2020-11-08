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

//本质上还是差分约束问题：
//如果边权有负 那么spfa判负环
//如果边权>=0 强连通分量 判断正环
//如果边权全部>0 拓扑排序

//建议虚拟远点 由于最低100 那么就每个点和原点连一条100边权的边 这个可以初始就把点权设为100 做到
//最后求一下最长路即可

const int N = 10010, M = 20010;
int n, m;
int h[N], e[M], ne[M], idx;
int q[N];
int dist[N];
int d[N];

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx ++;
}

//手写队列的方法 只是指针移动模拟出队 但是拓扑排序的元素全部保留在了队列中
//如果用stl 需要开一个数组来存一下

bool topsort() {
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; i++)
        if (!d[i]) q[++tt] = i;

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0) q[++tt] = j;
        }
    }
    return tt == n - 1;
}

int main() {
    scanf("%d%d", &n , &m);
    memset(h, -1, sizeof h);

    while (m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(b, a); //注意这个是差分约束的问题 a >= b + 1是b到1连一条边
        d[a] ++;
    }

    if (!topsort()) puts("Poor Xed");
    else {
        for (int i = 1; i <= n; i++) dist[i] = 100;
        for (int i = 0; i < n; i++) {
            int j = q[i];
            for (int k = h[j]; k != -1; k = ne[k])
                dist[e[k]] = max(dist[e[k]], dist[j] + 1);
        }

        int res = 0;
        for (int i = 1; i <= n; i++) res += dist[i];

        printf("%d\n", res);
    }

    return 0;
}