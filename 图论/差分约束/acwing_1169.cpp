#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <cstdio>
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

//求最小值，也就是求最长路，有解的条件是不存在正环 不然会 无穷迭代

const int N = 100010, M = 3 * N; //最坏的情况边数就是A=B 加上虚拟原点 就是三倍的点数

int n, m;
int h[N], e[M], w[M], ne[M], idx;
ll dist[N];
int q[N], cnt[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] =  b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++;
}

bool spfa() {
    int hh = 0, tt = 1;
    memset(dist, 0xcf, sizeof dist); //求最长路 初始为负无穷
    dist[0] = 0;
    q[0] = 0;
    st[0] = true;

    while (hh != tt) {
        int t = q[--tt]; //队列会超时 直接改为栈优化
        // if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n + 1) return false; //存在负环 则无解 加上虚拟原点后是n + 1个点
                if (!st[j]) {
                    q[tt++] = j;
                    // if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    while (m --) {
        int x, a, b;
        scanf("%d%d%d", &x, &a, &b);
        if (x == 1) add(b, a, 0), add(a, b, 0);
        else if (x == 2) add(a, b, 1);
        else if (x == 3) add(b, a, 0);
        else if (x == 4) add(b, a, 1);
        else add(a, b, 0);
    }

    for (int i = 1; i <= n; i++) add(0, i, 1); //从原点向每个点连一条边权为1的边 因为题意要求每个人都要分到

    if (!spfa()) puts("-1");
    else {
        ll res = 0;
        for (int i = 1; i <=  n; i++) res += dist[i];
        printf("%lld\n", res);
    }
    
    return 0;
}