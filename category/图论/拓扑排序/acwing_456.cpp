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

//本质上还是一个差分约束问题
//对于每个车次 在n个车站中选则停车，那么剩下的车站的级别肯定严格小于这些停车的车站
//剩余的每个点向停车的点连一条边，代表大小关系,但是考虑到 数据范围 由基本不等式 ab <= (a + b)^2 / 2 边数是平方级别的
//技巧:所有剩余的级别小的点放在左边 大的放在右边 中间放一个中间的虚拟点，然后左边的所有点和右边的所有点都和这个虚拟点连边
//左边到虚拟点的边权都是0 右边都是1 这样建图和每个左边的点都向右边每个点连一条边是等价的
//复杂度瞬间降为线性 由于本质上等价的边权都是大于0 所以可以用拓扑排序求出最长路

const int N = 2010, M = 1000010; //每个车次都要建一个虚拟中间点 每个车左右2边向虚拟点连边1000个 1000个车最多1e6条边
//第i辆车的虚拟中间点设置为n + i

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int q[N], d[N];
int dist[N];
bool st[N];

void add(int a, int b, int c) {
    d[b] ++; //注意处理入度
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

void topsort() {
    int hh = 0, tt = -1;
    for (int i = 1; i <= n + m; i++)
        if (!d[i]) q[++tt] = i;

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0) q[++tt] = j;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    for (int i = 1; i <= m; i++) {
        memset(st, 0, sizeof st);
        int cnt;
        scanf("%d", &cnt);

        int start = n, end = 1;
        while (cnt --) {
            int stop;
            scanf("%d", &stop);
            start = min(start, stop);
            end = max(end, stop);  //start要保存最小值 end最大
            st[stop] = true; //表示这个车站是要停靠的
        }

        int ver = n + i; //虚拟点
        for (int i = start; i <= end; i++)
            if (!st[i]) add(i, ver , 0);
            else add(ver, i, 1);
    }

    topsort();

    for (int i = 1; i <= n; i ++) dist[i] = 1; //最低为1级


    //拓扑排序求最长路 直接从前往后按照拓扑序迭代一次即可
    for (int i = 0; i < n + m; i++) { //n + m是n个车站和m个虚拟点 每趟车次处理都要加一个虚拟点
        int j = q[i];
        for (int k = h[j]; k != -1; k = ne[k])
            dist[e[k]] = max(dist[e[k]], dist[j] + w[k]);
    }

    int res = 0;
    //最长路就是最远的距离 也就是最高的级别 
    for (int i = 1 ; i <= n; i ++) res = max(res, dist[i]);

    printf("%d\n", res);

    return 0;

}