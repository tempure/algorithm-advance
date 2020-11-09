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

//不是带依赖的背包 不一样

//这个是每个连通块看成一个物品 一个连通块内的物品每次都要全部买
//然后对所有连通块做一次01背包

//在求连通块的同时 维护每个连通块的总价钱和总价值  都用父亲节点来计算
//最后01背包时候只需要遍历每个并查集的父节点即可

const int N = 10010;
int n, m, vol; //vol是背包总体积
int v[N], w[N]; //体积和价值
int p[N];
int f[N];

int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}


int main() {
    cin >> n >> m >> vol;
    for (int i = 1; i <= n; i++) p[i] = i;

    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];

    while (m --) {
        int a, b;
        cin >> a >> b;
        int pa = find(a), pb = find(b);
        if (pa != pb) { //要判重 防止重复加
            v[pb] += v[pa];
            w[pb] += w[pa];
            p[pa] = pb;
        }
    }

    //01背包
    for (int i = 1; i <= n; i++)
        if (p[i] == i) //只有当点是父节点的时候 才进行操作
            for (int j = vol; j >= v[i]; j--)
                f[j] = max(f[j], f[j - v[i]] + w[i]);

    cout << f[vol] << endl;

    return 0;
}